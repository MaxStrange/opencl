/*
 * This module provides error handling for OpenCL, since it is extensive.
 *
 * All of the API functions for this module check the given error value
 * and compare it to the documentation's listed possible error conditions.
 *
 * If everything checks out, nothing is done and false is returned.
 * If an error is detected, the error is printed via
 * perror if print_error is true, and the program exits if exit_prog is true
 * if the program does not exit, true is returned.
 *
 * SO: FALSE -> NO ERROR
 */
#ifndef __ERROR_HANDLING_H__
#define __ERROR_HANDLING_H__

#include <stdbool.h>

bool handle_error_BuildProgram(cl_int err, bool print_error, bool exit_prog);
bool handle_error_CreateBuffer(cl_int err, bool print_error, bool exit_prog);
bool handle_error_CreateCommandQueue(cl_int err, bool print_error,
        bool exit_prog);
bool handle_error_CreateContext(cl_int err, bool print_error, bool exit_prog);
bool handle_error_CreateKernel(cl_int err, bool print_error, bool exit_prog);
bool handle_error_CreateProgramWithSource(cl_int err, bool print_error,
        bool exit_prog);
bool handle_error_EnqueueNDRangeKernel(cl_int err, bool print_error,
        bool exit_prog);
bool handle_error_EnqueueReadBuffer(cl_int err, bool print_error,
        bool exit_prog);
bool handle_error_EnqueueWriteBuffer(cl_int err, bool print_error,
        bool exit_prog);
bool handle_error_Finish(cl_int err, bool print_error, bool exit_prog);
bool handle_error_GetDeviceIDs(cl_int err, bool print_error, bool exit_prog);
bool handle_error_GetPlatformIDs(cl_int err, bool print_error, bool exit_prog);
bool handle_error_ReleaseCommandQueue(cl_int err, bool print_error,
        bool exit_prog);
bool handle_error_ReleaseContext(cl_int err, bool print_error, bool exit_prog);
bool handle_error_ReleaseKernel(cl_int err, bool print_error, bool exit_prog);
bool handle_error_ReleaseMemObject(cl_int err, bool print_error, bool exit_prog);
bool handle_error_ReleaseProgram(cl_int err, bool print_error, bool exit_prog);
bool handle_error_SetKernelArg(cl_int err, bool print_error, bool exit_prog);

#endif //header guard




