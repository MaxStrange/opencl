#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <CL/cl.h>

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
    if (err < 0)
    {
        perror("Couldn't find any platforms.\n");
        exit(-1);
    }

    //Get ID for the device
    cl_device_id device_ids[2];
//    err = clGetDeviceInfo(platform, CL_DEVICE_TYPE_ALL, 2, device_ids, NULL);
    if (err < 0)
    {
        perror("Couldn't find any devices.\n");
        exit(-1);
    }


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







