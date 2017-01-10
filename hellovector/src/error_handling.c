#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
    #include "OpenCL/opencl.h"
#else
    #include "CL/cl.h"
#endif

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

bool handle_error_CreateBuffer(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_VALUE:
            error = true;
            err_str = "Flags are not valid in call to CreateBuffer.\n";
            break;
        case CL_INVALID_BUFFER_SIZE:
            error = true;
            err_str = "Size is 0 or is greater than CL_DEVICE_MAX_MEM_ALLOC_SIZE in call to CreateBuffer.\n";
            break;
        case CL_INVALID_HOST_PTR:
            error = true;
            err_str = "host_ptr is NULL and CL_MEM_USE_HOST_PTR or CL_MEM_COPY_HOST_PTR are set in flags or host_ptr is not NULL but CL_MEM_COPY_HOST_PTR or CL_MEM_USE_HOST_PTR are not set in flags in call to CreateBuffer.\n";
            break;
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:
            error = true;
            err_str = "Failure to allocate the memory for the buffer in call to CreateBuffer.\n";
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

bool handle_error_EnqueueWriteBuffer(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_MEM_OBJECT:
            error = true;
            err_str = "Buffer is not a valid buffer object in call to EnqueueWriteBuffer.\n";
            break;
        case CL_INVALID_VALUE:
            error = true;
            err_str = "The region being written to is out of bounds or ptr is a NULL value for call to EnqueueWriteBuffer.\n";
            break;
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:
            error = true;
            err_str = "Failure to allocate memory for data store in call to EnqueueWriteBuffer.\n";
            break;
        case CL_INVALID_EVENT_WAIT_LIST:
            error = true;
            err_str = "Event_wait_list is NULL and num_events_in_wait_list is greater than 0 or event_wait_list is not NULL and num_events_in_wait_list is 0 or event objects in event_wait_list are not valid events in call to EnqueueWriteBuffer.\n";
            break;
    }

    print_or_exit(error, print_error, err_str, exit_prog);
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

bool handle_error_SetKernelArg(cl_int err, bool print_error, bool exit_prog)
{
    bool error = false;
    char *err_str;
    switch (err)
    {
        case CL_INVALID_ARG_INDEX:
            err_str = "Argument index is not valid in call to SetKernelArg.\n";
            error = true;
            break;
        case CL_INVALID_ARG_VALUE:
            err_str = "arg_value is NULL for an argument that is not declared with the __local qualifier or vice versa in call to SetKernelArg.\n";
            error = true;
            break;
        case CL_INVALID_MEM_OBJECT:
            err_str = "An argument has been declared to be a memory object but is not a valid one in call to SetKernelArg.\n";
            error = true;
            break;
        case CL_INVALID_SAMPLER:
            err_str = "An argument has been declared to be a sampler_t, but it is not a valid one in call to SetKernelArg.\n";
            error = true;
            break;
        case CL_INVALID_ARG_SIZE:
            err_str = "arg_size does not match the size of the data type for an argument that is not a memory object or the argument is a memory object and arg_size != sizeof(cl_mem) or arg_size is 0 and the argument is declared with the __local qualifier or the argument is a sampler and arg_size != sizeof(cl_sampler).\n";
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
        case CL_INVALID_COMMAND_QUEUE:
            err_str = "Invalid command queue.\n";
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







