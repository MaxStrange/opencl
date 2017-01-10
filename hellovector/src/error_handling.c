#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>

#include "error_handling.h"


static bool handle_error_common(cl_int err, bool print_error, bool exit_prog);
static void print_or_exit(cl_int err, bool print_error, const char *err_str,
        bool exit_prog);


bool handle_error_BuildProgram(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_VALUE:
            error = true;
            err_str = "pfn_notify is NULL but user_data is not NULL or device_list is NULL and num_devices is greater than zero, or device_list is not NULL and num_devices is zero in call to BuildProgram.\n";
            break;
        case CL_INVALID_BINARY:
            error = true;
            err_str = "Invalid program binary in call to BuildProgram.\n";
            break;
        case CL_INVALID_BUILD_OPTIONS:
            error = true;
            err_str = "Invalid build options in call to BuildProgram.\n";
            break;
        case CL_INVALID_OPERATION:
            error = true;
            err_str = "The build of a previous executable is not done in call to BuildProgram.\n";
            break;
        case CL_COMPILER_NOT_AVAILABLE:
            error = true;
            err_str = "No compiler available in call to BuildProgram.\n";
            break;
        case CL_BUILD_PROGRAM_FAILURE:
            error = true;
            err_str = "The program failed to build in call to BuildProgram.\n";
            break;
    }

    print_or_exit(err, print_error, err_str, exit_prog);
    return error || handle_error_common(err, print_error, exit_prog);
}

bool handle_error_CreateCommandQueue(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_VALUE:
            err_str = "Properties value is not valid in call to CreateCommandQueue\n";
            error = true;
            break;
        case CL_INVALID_QUEUE_PROPERTIES:
            err_str = "Properties value is valid, but not supported by this device in call to CreateCommandQueue.\n";
            error = true;
            break;
    }

    print_or_exit(err, print_error, err_str, exit_prog);
    return error || handle_error_common(err, print_error, exit_prog);
}

bool handle_error_CreateContext(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_VALUE:
            err_str = "In call to CreateContext: Context properties are incorrect, devices is NULL, num_devices is equal to 0, or pfn_notify is NULL but user_data is not NULL\n";
            break;
    }

    print_or_exit(err, print_error, err_str, exit_prog);
    return error || handle_error_common(err, print_error, exit_prog);
}

bool handle_error_CreateKernel(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_VALUE:
            error = true;
            err_str = "Kernel name is NULL in call to CreateKernel.\n";
            break;
        case CL_INVALID_KERNEL_DEFINITION:
            error = true;
            err_str = "Function definition for __kernel function given by kernel_name is such that the number of arguments or the argument types given are not the same for all devices for which the program executable has been built in call to CreateKernel.\n";
            break;
        case CL_INVALID_KERNEL_NAME:
            error = true;
            err_str = "Kernel name is not found in program in call to CreateKernel.\n";
            break;
    }

    print_or_exit(err, print_error, err_str, exit_prog);
    return error || handle_error_common(err, print_error, exit_prog);
}

bool handle_error_CreateProgramWithSource(cl_int err, bool print_error,
        bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_VALUE:
            err_str = "Count is zero or strings or an entry in strings is NULL in call to CreateProgramWithSource\n";
            error = true;
            break;
    }

    print_or_exit(err, print_error, err_str, exit_prog);
    return error || handle_error_common(err, print_error, exit_prog);
}

bool handle_error_GetDeviceIDs(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_DEVICE_TYPE:
            err_str = "Invalid device type in call to GetDeviceIDs.\n";
            error = true;
            break;
        case CL_INVALID_VALUE:
            err_str = "num_entries is equal to zero and device_type is not NULL or both num_devices and device_type are NULL in call to GetDeviceIDs.\n";
            error = true;
            break;
        case CL_DEVICE_NOT_FOUND:
            err_str = "No OpenCL device matching device_type was found in call to GetDeviceIDs.\n";
            error = true;
            break;
    }

    print_or_exit(error, print_error, err_str, exit_prog);
    return error || handle_error_common(err, print_error, exit_prog);
}

bool handle_error_GetPlatformIDs(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_VALUE:
            err_str = "num_entries is 0 and platforms is non NULL or both num_platforms and platforms are NULL in call ot GetPlatformIDs.\n";
            error = true;
            break;
    }

    print_or_exit(error, print_error, err_str, exit_prog);
    return error || handle_error_common(err, print_error, exit_prog);
}

static bool handle_error_common(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_PROGRAM:
            err_str = "Invalid program.\n";
            error = true;
            break;
        case CL_INVALID_CONTEXT:
            err_str = "Invalid context.\n";
            error = true;
            break;
        case CL_INVALID_PLATFORM:
            err_str = "Invalid platform.\n";
            error = true;
            break;
        case CL_INVALID_DEVICE:
            err_str = "Invalid device for this platform.\n";
            error = true;
            break;
        case CL_DEVICE_NOT_AVAILABLE:
            err_str = "Device not available.\n";
            error = true;
            break;
        case CL_OUT_OF_HOST_MEMORY:
            err_str = "Out of host memory.\n";
            error = true;
            break;
        case CL_INVALID_PROGRAM_EXECUTABLE:
            err_str = "Invalid program executable.\n";
            error = true;
            break;
    }

    print_or_exit(error, print_error, err_str, exit_prog);
    return error;
}

static void print_or_exit(cl_int err, bool print_error, const char *err_str,
        bool exit_prog)
{
    if (err)
    {
        if (print_error)
            perror(err_str);
        if (exit_prog)
            exit(-1);
    }
}







