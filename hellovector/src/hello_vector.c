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
 * Loads the kernel source into a malloc'd char array. The caller is
 * responsible for freeing this array.
 */
static char* load_kernel_source(size_t *program_size);
/*
 * Fills a given vector of ints (of size sz) with random numbers.
 */
static void random_ints(int *to_fill, size_t sz);

int main(void)
{
    /*
     * We will be computing A + B = C
     * for vectors A and B of size VECTOR_SIZE, populated with random numbers
     */

    static const unsigned int VECTOR_SIZE = 512;

    //Allocate the necessary host-side memory
    printf("Allocating necessary host-side memory...\n");
    int size = VECTOR_SIZE * sizeof(int);
    int *A = (int *)malloc(size);
    int *B = (int *)malloc(size);
    int *C = (int *)malloc(size);

    //Populate A and B
    printf("Populating A and B with random integers...\n");
    random_ints(A, size);
    random_ints(B, size);

    //Number of work items in each local work group
    size_t local_size = 64;
    //Number of total work items
    size_t global_size = ceil(VECTOR_SIZE / (float)local_size) * local_size;

    /*
     * Set up the OpenCL stuff
     */

    cl_int err;

    //Bind to platform
    cl_uint num_platforms;
    clGetPlatformIDs(0, NULL, &num_platforms);
    printf("Found: %u platforms.\n", num_platforms);

    cl_platform_id platforms[5];
    err = clGetPlatformIDs(5, platforms, NULL);
    handle_error_GetPlatformIDs(err, true, true);
    cl_platform_id platform = platforms[0];
    printf("About to call clGetDeviceIDs.\n");

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

#if 0
    //Display the information found about this device
    cl_uint addrsz;
    clGetDeviceInfo(device_id, CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint), &addrsz,
            NULL);
    size_t exten_len;
    clGetDeviceInfo(device_id, CL_DEVICE_EXTENSIONS, 0, NULL, &exten_len);
    char *extensions = (char *)malloc(exten_len * sizeof(char));
    clGetDeviceInfo(device_id, CL_DEVICE_EXTENSIONS, exten_len * sizeof(char),
            extensions, NULL);
    cl_uint maxcompute;
    clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint),
            &maxcompute, NULL);
    size_t name_len;
    clGetDeviceInfo(device_id, CL_DEVICE_NAME, 0, NULL, &name_len);
    char *dev_name = (char *)malloc(name_len * sizeof(char));
    clGetDeviceInfo(device_id, CL_DEVICE_NAME, name_len * sizeof(char),
            dev_name, NULL);
    printf("Found device: %s with address width %u, max compute units of %u, and "\
            "extensions %s.\n", dev_name, addrsz, maxcompute, extensions);
    free(dev_name);
    free(extensions);

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
    printf("Creating the command queue...\n");
    cl_command_queue queue = clCreateCommandQueue(context, device_id,
            0, &err);
    handle_error_CreateCommandQueue(err, true, true);

    //Create the OpenCL program kernel
    printf("Loading the kernel source...\n");
    size_t program_size;
    char *kernel_source = load_kernel_source(&program_size);
    printf("Here is the loaded kernel source: \n%s\n", kernel_source);
    printf("Kernel source has been loaded, now creating the Kernel\n");
    cl_program program = clCreateProgramWithSource(context, 1,
            (const char **) &kernel_source, NULL, &err);
    handle_error_CreateProgramWithSource(err, true, true);

    //Build the OpenCL program kernel
    printf("Building the kernel from the loaded source...\n");
    const char *options = "-cl-finite-math-only -cl-no-signed-zeros";
    err = clBuildProgram(program, 1, &device_id, options, NULL, NULL);
    if (handle_error_BuildProgram(err, true, false))
    {
        printf("Error in building the program: \n");
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

    printf("Creating the kernel...\n");
    cl_kernel kernel = clCreateKernel(program, "add_vector", &err);
    handle_error_CreateKernel(err, true, true);

    printf("Making the buffers...\n");
    cl_mem d_A = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &err);
    handle_error_CreateBuffer(err, true, true);
    cl_mem d_B = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &err);
    handle_error_CreateBuffer(err, true, true);
    cl_mem d_C = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &err);
    handle_error_CreateBuffer(err, true, true);

    printf("Enqueueing the write buffers...\n");
    err = clEnqueueWriteBuffer(queue, d_A, CL_TRUE, 0, size, A, 0, NULL, NULL);
    handle_error_EnqueueWriteBuffer(err, true, true);
    err = clEnqueueWriteBuffer(queue, d_B, CL_TRUE, 0, size, B, 0, NULL, NULL);
    handle_error_EnqueueWriteBuffer(err, true, true);

    printf("Setting kernel args...\n");
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_A);
    handle_error_SetKernelArg(err, true, true);
    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_B);
    handle_error_SetKernelArg(err, true, true);
    err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_C);
    handle_error_SetKernelArg(err, true, true);
    err = clSetKernelArg(kernel, 3, sizeof(int), &VECTOR_SIZE);
    handle_error_SetKernelArg(err, true, true);

    printf("Executing the kernel code and timing it...\n");
    clock_t start_time = clock();
    //Execute the kernel over the entire range of the data set
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size,
            &local_size, 0, NULL, NULL);
    handle_error_EnqueueNDRangeKernel(err, true, true);

    //Wait for the command queue to get serviced before reading the results
    err = clFinish(queue);
    handle_error_Finish(err, true, true);

    err = clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, size, C, 0, NULL, NULL);
    handle_error_EnqueueReadBuffer(err, true, true);
    clock_t end_time = clock();


    //Free up all the stuff
    printf("Done, now cleaning up...\n");
    err = clReleaseMemObject(d_A);
    handle_error_ReleaseMemObject(err, true, false);
    err = clReleaseMemObject(d_B);
    handle_error_ReleaseMemObject(err, true, false);
    err = clReleaseMemObject(d_C);
    handle_error_ReleaseMemObject(err, true, false);
    err = clReleaseProgram(program);
    handle_error_ReleaseProgram(err, true, false);
    err = clReleaseKernel(kernel);
    handle_error_ReleaseKernel(err, true, false);
    err = clReleaseCommandQueue(queue);
    handle_error_ReleaseCommandQueue(err, true, false);
    err = clReleaseContext(context);
    handle_error_ReleaseContext(err, true, false);

    free(A);
    free(B);
    free(C);
    free(kernel_source);

    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Total time taken for addition of %u random numbers: %f seconds\n",
            VECTOR_SIZE, total_time);
#endif
    return 0;
}

static char* load_kernel_source(size_t *sz)
{
    FILE *program_handle = fopen("./src/kernel_add_vector.cl", "r");
    fseek(program_handle, 0, SEEK_END);
    size_t program_size = ftell(program_handle);
    rewind(program_handle);

    char *program_buffer = (char *)malloc(program_size + 1);
    program_buffer[program_size] = '\0';
    fread(program_buffer, sizeof(char), program_size, program_handle);
    fclose(program_handle);

    *sz = program_size;
    return program_buffer;
}

static void random_ints(int *to_fill, size_t sz)
{
    for (size_t i = 0; i < sz; i++)
    {
        int r = rand();
        to_fill[i] = r;
    }
}







