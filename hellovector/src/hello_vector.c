#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <CL/cl.h>

#include "error_handling.h"


#define SEED            5
#define VECTOR_SIZE     512

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

    //Allocate the necessary host-side memory
    int size = VECTOR_SIZE * sizeof(int);
    int *a = (int *)malloc(size);
    int *b = (int *)malloc(size);
    int *c = (int *)malloc(size);

    //Populate A and B
    random_ints(a, size);
    random_ints(b, size);

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
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ACCELERATOR, 1, &device_id,
            NULL);
    handle_error_GetDeviceIDs(err, true, true);

    //Create a context that has the properties of the platform,
    //is made of one device, the device is specified in device_id,
    //No callback function (and no parameters to the callback function)
    cl_context_properties props[] = {
        CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0
    };
    cl_context context = clCreateContext(props, 1, &device_id, NULL, NULL, &err);
    handle_error_CreateContext(err, true, true);

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







