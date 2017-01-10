#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __APPLE__
    #include "OpenCL/opencl.h"
#else
    #include "CL/cl.h"
#endif

#include "error_handling.h"


#define SEED            5

/*
 * Fills a given vector of ints (of size sz) with random numbers.
 */
static void random_ints(int *to_fill, size_t sz);


int main(int argc, char **argv)
{
    /*
     * We will be computing A + B = C
     * for vectors A and B of size VECTOR_SIZE, populated with random numbers
     */

    static const unsigned int VECTOR_SIZE = 512;

    //Allocate the necessary host-side memory
    int size = VECTOR_SIZE * sizeof(int);
    int *a = (int *)malloc(size);
    int *b = (int *)malloc(size);
    int *c = (int *)malloc(size);

    //Populate A and B
    random_ints(a, size);
    random_ints(b, size);

    //Number of work items in each local work group
    size_t local_size = 64;
    //Number of total work items
    size_t global_size = ceil(VECTOR_SIZE / (float)local_size) * local_size;

    /*
     * Set up the OpenCL stuff
     */

    cl_int err;

    //Bind to platform
    cl_platform_id platform;
    err = clGetPlatformIDs(1, &platform, NULL);
    handle_error_GetPlatformIDs(err, true, true);

    //Get ID for the device which must be an accelerator and there is only one
    //of them.
    cl_device_id device_id;
    #ifdef __APPLE__
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
    #else
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ACCELERATOR, 1, &device_id,
            NULL);
    #endif
    handle_error_GetDeviceIDs(err, true, true);

    //Create a context that has the properties of the platform,
    //is made of one device, the device is specified in device_id,
    //No callback function (and no parameters to the callback function)
    cl_context_properties props[] = {
        CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0
    };
    cl_context context = clCreateContext(props, 1, &device_id, NULL, NULL, &err);
    handle_error_CreateContext(err, true, true);

    //Create a command queue
    //cl_command_queue_properties cq_props[] = { (cl_command_queue_properties)0 };
    cl_command_queue queue = clCreateCommandQueue(context, device_id,
            0, &err);
    handle_error_CreateCommandQueue(err, true, true);

    //Create the OpenCL program kernel
    const char *kernel_source =
            "#pragma OPENCL EXTENSION cl_khr_icd : enable  \n"\
            "__kernel void add_vector(__global float *a,   \n"\
            "                         __global float *b,   \n"\
            "                         __global float *c,   \n"\
            "                         const unsigned int n)\n"\
            "{                                             \n"\
            "   //Get our global thread ID                 \n"\
            "   int id = get_global_id(0);                 \n"\
            "   //Make sure we do not go out of bounds     \n"\
            "   if (id < n)                                \n"\
            "       c[id] = a[id] + b[id];                 \n"\
            "}                                             \n";
    cl_program program = clCreateProgramWithSource(context, 1,
            (const char **) &kernel_source, NULL, &err);
    handle_error_CreateProgramWithSource(err, true, true);

    //Build the OpenCL program kernel
    const char *options = "-cl-finite-math-only -cl-no-signed-zeros";
    err = clBuildProgram(program, 1, &device_id, options, NULL, NULL);
    if (handle_error_BuildProgram(err, true, false))
    {
        //Get the size of the build log
        size_t log_size;
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
                0, NULL, &log_size);

        //Now read the log into the build log
        char *program_log = (char *)malloc(log_size + 1);
        program_log[log_size] = '\0';
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
                log_size + 1, program_log, NULL);

        printf("%s\n", program_log);
        free(program_log);
        exit(-1);
    }

    cl_kernel kernel = clCreateKernel(program, "add_vector", &err);
    handle_error_CreateKernel(err, true, true);

    cl_mem d_a = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &err);
    handle_error_CreateBuffer(err, true, true);
    cl_mem d_b = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &err);
    handle_error_CreateBuffer(err, true, true);
    cl_mem d_c = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &err);
    handle_error_CreateBuffer(err, true, true);

    err = clEnqueueWriteBuffer(queue, d_a, CL_TRUE, 0, size, a, 0, NULL, NULL);
    handle_error_EnqueueWriteBuffer(err, true, true);
    err = clEnqueueWriteBuffer(queue, d_b, CL_TRUE, 0, size, b, 0, NULL, NULL);
    handle_error_EnqueueWriteBuffer(err, true, true);

    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    handle_error_SetKernelArg(err, true, true);
    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
    handle_error_SetKernelArg(err, true, true);
    err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
    handle_error_SetKernelArg(err, true, true);
    err = clSetKernelArg(kernel, 3, sizeof(int), &VECTOR_SIZE);
    handle_error_SetKernelArg(err, true, true);

    clock_t start_time = clock();
    //Execute the kernel over the entire range of the data set
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size,
            &local_size, 0, NULL, NULL);

    //Wait for the command queue to get serviced before reading the results
    err = clFinish(queue);

    err = clEnqueueReadBuffer(queue, d_c, CL_TRUE, 0, size, c, 0, NULL, NULL);
    clock_t end_time = clock();


    //Free up all the stuff
    err = clReleaseMemObject(d_a);
    err = clReleaseMemObject(d_b);
    err = clReleaseMemObject(d_c);
    err = clReleaseProgram(program);
    err = clReleaseKernel(kernel);
    err = clReleaseCommandQueue(queue);
    err = clReleaseContext(context);

    free(a);
    free(b);
    free(c);

    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Total time taken for addition of %u random numbers: %f seconds\n",
            VECTOR_SIZE, total_time);

    return 0;
}

static void random_ints(int *to_fill, size_t sz)
{
    for (size_t i = 0; i < sz; i++)
    {
        int r = rand();
        to_fill[i] = r;
    }
}







