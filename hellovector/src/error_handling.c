#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>

#include "error_handling.h"


static bool handle_error_common(cl_int err, bool print_error, bool exit_prog);


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
    if (error)
    {
        if (print_error)
            perror(err_str);
        if (exit_prog)
            exit(-1);
    }

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
    if (error)
    {
        if (print_error)
            perror(err_str);
        if (exit_prog)
            exit(-1);
    }

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
    if (error)
    {
        if (print_error)
            perror(err_str);
        if (exit_prog)
            exit(-1);
    }

    return error || handle_error_common(err, print_error, exit_prog);
}

static bool handle_error_common(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
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
    }

    if (error)
    {
        if (print_error)
            perror(err_str);
        if (exit_prog)
            exit(-1);
    }

    return error;
}




