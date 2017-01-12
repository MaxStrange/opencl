#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "CL/cl.h"

#include "icd_dispatch.h"


extern cl_int _clGetPlatformIDs(cl_uint, cl_platform_id*, cl_uint*);
extern cl_int _clGetPlatformInfo(cl_platform_id,cl_platform_info,size_t,
        void*,size_t*);
extern cl_int _clGetDeviceIDs(cl_platform_id, cl_device_type, cl_uint,
        cl_device_id*, cl_uint*);
//This file is the actual implementation of the KHRicdVendorDispatchRec
//It points is a struct of pointers to my implemenations of API functions

KHRicdVendorDispatch the_dispatch_vector = {
    /* OpenCL 1.0 */
    .clGetPlatformIDs                                   = &_clGetPlatformIDs,
    .clGetPlatformInfo                                  = &_clGetPlatformInfo,
    .clGetDeviceIDs                                     = &_clGetDeviceIDs,
    .clGetDeviceInfo                                    = NULL,
    .clCreateContext                                    = NULL,
    .clCreateContextFromType                            = NULL,
    .clRetainContext                                    = NULL,
    .clReleaseContext                                   = NULL,
    .clGetContextInfo                                   = NULL,
    .clCreateCommandQueue                               = NULL,
    .clRetainCommandQueue                               = NULL,
    .clReleaseCommandQueue                              = NULL,
    .clGetCommandQueueInfo                              = NULL,
    .clSetCommandQueueProperty                          = NULL,
    .clCreateBuffer                                     = NULL,
    .clCreateImage2D                                    = NULL,
    .clCreateImage3D                                    = NULL,
    .clRetainMemObject                                  = NULL,
    .clReleaseMemObject                                 = NULL,
    .clGetSupportedImageFormats                         = NULL,
    .clGetMemObjectInfo                                 = NULL,
    .clGetImageInfo                                     = NULL,
    .clCreateSampler                                    = NULL,
    .clRetainSampler                                    = NULL,
    .clReleaseSampler                                   = NULL,
    .clGetSamplerInfo                                   = NULL,
    .clCreateProgramWithSource                          = NULL,
    .clCreateProgramWithBinary                          = NULL,
    .clRetainProgram                                    = NULL,
    .clReleaseProgram                                   = NULL,
    .clBuildProgram                                     = NULL,
    .clUnloadCompiler                                   = NULL,
    .clGetProgramInfo                                   = NULL,
    .clGetProgramBuildInfo                              = NULL,
    .clCreateKernel                                     = NULL,
    .clCreateKernelsInProgram                           = NULL,
    .clRetainKernel                                     = NULL,
    .clReleaseKernel                                    = NULL,
    .clSetKernelArg                                     = NULL,
    .clGetKernelInfo                                    = NULL,
    .clGetKernelWorkGroupInfo                           = NULL,
    .clWaitForEvents                                    = NULL,
    .clGetEventInfo                                     = NULL,
    .clRetainEvent                                      = NULL,
    .clReleaseEvent                                     = NULL,
    .clGetEventProfilingInfo                            = NULL,
    .clFlush                                            = NULL,
    .clFinish                                           = NULL,
    .clEnqueueReadBuffer                                = NULL,
    .clEnqueueWriteBuffer                               = NULL,
    .clEnqueueCopyBuffer                                = NULL,
    .clEnqueueReadImage                                 = NULL,
    .clEnqueueWriteImage                                = NULL,
    .clEnqueueCopyImage                                 = NULL,
    .clEnqueueCopyImageToBuffer                         = NULL,
    .clEnqueueCopyBufferToImage                         = NULL,
    .clEnqueueMapBuffer                                 = NULL,
    .clEnqueueMapImage                                  = NULL,
    .clEnqueueUnmapMemObject                            = NULL,
    .clEnqueueNDRangeKernel                             = NULL,
    .clEnqueueTask                                      = NULL,
    .clEnqueueNativeKernel                              = NULL,
    .clEnqueueMarker                                    = NULL,
    .clEnqueueWaitForEvents                             = NULL,
    .clEnqueueBarrier                                   = NULL,
    .clGetExtensionFunctionAddress                      = NULL,
    .clCreateFromGLBuffer                               = NULL,
    .clCreateFromGLTexture2D                            = NULL,
    .clCreateFromGLTexture3D                            = NULL,
    .clCreateFromGLRenderbuffer                         = NULL,
    .clGetGLObjectInfo                                  = NULL,
    .clGetGLTextureInfo                                 = NULL,
    .clEnqueueAcquireGLObjects                          = NULL,
    .clEnqueueReleaseGLObjects                          = NULL,
    .clGetGLContextInfoKHR                              = NULL,

    /* cl_khr_d3d10_sharing */
    .clGetDeviceIDsFromD3D10KHR                         = NULL,
    .clCreateFromD3D10BufferKHR                         = NULL,
    .clCreateFromD3D10Texture2DKHR                      = NULL,
    .clCreateFromD3D10Texture3DKHR                      = NULL,
    .clEnqueueAcquireD3D10ObjectsKHR                    = NULL,
    .clEnqueueReleaseD3D10ObjectsKHR                    = NULL,

    /* OpenCL 1.1 */
    .clSetEventCallback                                 = NULL,
    .clCreateSubBuffer                                  = NULL,
    .clSetMemObjectDestructorCallback                   = NULL,
    .clCreateUserEvent                                  = NULL,
    .clSetUserEventStatus                               = NULL,
    .clEnqueueReadBufferRect                            = NULL,
    .clEnqueueWriteBufferRect                           = NULL,
    .clEnqueueCopyBufferRect                            = NULL,

    /* cl_ext_device_fission */
    .clCreateSubDevicesEXT                              = NULL,
    .clRetainDeviceEXT                                  = NULL,
    .clReleaseDeviceEXT                                 = NULL,

    /* cl_khr_gl_event */
    .clCreateEventFromGLsyncKHR                         = NULL,

    /* OpenCL 1.2 */
    .clCreateSubDevices                                 = NULL,
    .clRetainDevice                                     = NULL,
    .clReleaseDevice                                    = NULL,
    .clCreateImage                                      = NULL,
    .clCreateProgramWithBuiltInKernels                  = NULL,
    .clCompileProgram                                   = NULL,
    .clLinkProgram                                      = NULL,
    .clUnloadPlatformCompiler                           = NULL,
    .clGetKernelArgInfo                                 = NULL,
    .clEnqueueFillBuffer                                = NULL,
    .clEnqueueFillImage                                 = NULL,
    .clEnqueueMigrateMemObjects                         = NULL,
    .clEnqueueMarkerWithWaitList                        = NULL,
    .clEnqueueBarrierWithWaitList                       = NULL,
    .clGetExtensionFunctionAddressForPlatform           = NULL,
    .clCreateFromGLTexture                              = NULL,

    /* cl_khr_d3d11_sharing */
    .clGetDeviceIDsFromD3D11KHR                         = NULL,
    .clCreateFromD3D11BufferKHR                         = NULL,
    .clCreateFromD3D11Texture2DKHR                      = NULL,
    .clCreateFromD3D11Texture3DKHR                      = NULL,
    .clCreateFromDX9MediaSurfaceKHR                     = NULL,
    .clEnqueueAcquireD3D11ObjectsKHR                    = NULL,
    .clEnqueueReleaseD3D11ObjectsKHR                    = NULL,

    /* cl_khr_dx9_media_sharing */
    .clGetDeviceIDsFromDX9MediaAdapterKHR               = NULL,
    .clEnqueueAcquireDX9MediaSurfacesKHR                = NULL,
    .clEnqueueReleaseDX9MediaSurfacesKHR                = NULL,

    /* cl_khr_egl_image */
    .clCreateFromEGLImageKHR                            = NULL,
    .clEnqueueAcquireEGLObjectsKHR                      = NULL,
    .clEnqueueReleaseEGLObjectsKHR                      = NULL,

    /* cl_khr_egl_event */
    .clCreateEventFromEGLSyncKHR                        = NULL,

    /* OpenCL 2.0 */
    .clCreateCommandQueueWithProperties                 = NULL,
    .clCreatePipe                                       = NULL,
    .clGetPipeInfo                                      = NULL,
    .clSVMAlloc                                         = NULL,
    .clSVMFree                                          = NULL,
    .clEnqueueSVMFree                                   = NULL,
    .clEnqueueSVMMemcpy                                 = NULL,
    .clEnqueueSVMMemFill                                = NULL,
    .clEnqueueSVMMap                                    = NULL,
    .clEnqueueSVMUnmap                                  = NULL,
    .clCreateSamplerWithProperties                      = NULL,
    .clSetKernelArgSVMPointer                           = NULL,
    .clSetKernelExecInfo                                = NULL,

    /* cl_khr_sub_groups */
    .clGetKernelSubGroupInfoKHR                         = NULL,

    /* OpenCL 2.1 */
    .clCloneKernel                                      = NULL,
    .clCreateProgramWithIL                              = NULL,
    .clEnqueueSVMMigrateMem                             = NULL,
    .clGetDeviceAndHostTimer                            = NULL,
    .clGetHostTimer                                     = NULL,
    .clGetKernelSubGroupInfo                            = NULL,
    .clSetDefaultDeviceCommandQueue                     = NULL,
};
