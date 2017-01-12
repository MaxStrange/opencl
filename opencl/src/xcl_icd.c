/* xcl_icd.c 
 *
 * Copyright (c) 2009-2013 Brown Deer Technology, LLC.  All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3 (LGPLv3)
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <CL/cl.h>

#include "version.h"
#include "xcl_structs.h"
#include "printcl.h"

#ifndef min
#define min(a,b) ((a<b)?a:b)
#endif

// ICD stuff 

//extern void * __icd_call_vector;
static struct opencl_device_info device_info;

static struct _cl_device_id device_id;

static struct _cl_platform_id platform_id;

static void initialize_dev_info(void);

cl_int 
clIcdGetPlatformIDsKHR( 
	cl_uint nplatforms, 
	cl_platform_id *platforms, 
	cl_uint *nplatforms_ret
)
{
    perror("clIcdGetPlatformIDsKHR called.\n");

    if (nplatforms == 0 && platforms !=NULL)
        return CL_INVALID_VALUE;
    else if (platforms == NULL && nplatforms_ret == NULL)
        return CL_INVALID_VALUE;

    initialize_dev_info();

    device_id.dispatch= NULL;//(void *) __icd_call_vector;
    device_id.ocldevinfo = &device_info;

    platform_id.dispatch= NULL;//(void *) __icd_call_vector;
    platform_id.profile = "<profile>";
    platform_id.version = VERSION_STRING;
    platform_id.name = "eocl";
    platform_id.vendor = "Max Strange";
    platform_id.extensions = "cl_khr_icd";
    platform_id.ndevices = 1;
    platform_id.dtab = &device_id;

    if (platforms != NULL)
    {
        *platforms = (cl_platform_id)(&platform_id);
    }
    if (nplatforms_ret != NULL)
    {
        *nplatforms_ret = 1;
    }

    perror("Successful call to clIcdGetPlatformIDsKHR.\n");

    return CL_SUCCESS;
}

static void initialize_dev_info(void)
{
    static size_t dims[4] = {1, 1, 1, 0};
    device_info.devtype = CL_DEVICE_TYPE_ACCELERATOR;
    device_info.vendorid = 0;
    device_info.max_compute_units = 1;          /* max_compute_units */
    device_info.max_wi_dim = 3;
    device_info.max_wi_sz[0] = 1; /* max_wi_dim,max_wi_sz[] */
    device_info.max_wi_sz[1] = 1; /* max_wi_dim,max_wi_sz[] */
    device_info.max_wi_sz[2] = 1; /* max_wi_dim,max_wi_sz[] */
    device_info.max_wi_sz[3] = 0; /* max_wi_dim,max_wi_sz[] */
    device_info.max_wg_sz = 16;           /* max_wg_sz */
    device_info.pref_charn = 4;
    device_info.pref_shortn = 2;
    device_info.pref_intn = 1;
    device_info.pref_longn = 1;
    device_info.pref_floatn = 1;
    device_info.pref_doublen = 1;   /* pref_char/short/int/long/float/double/n */
    device_info.max_freq = 0;          /* max_freq */
    device_info.addr_bits = 32;        /* bits */
    device_info.max_mem_alloc_sz = 1024*1024*1024;    /* max_mem_alloc_sz */
    device_info.supp_img = CL_FALSE;   /* supp_img */
    device_info.img_max_narg_r = 0;
    device_info.img_max_narg_w = 0;          /* img_max_narg_r, img_max_narg_w */
    device_info.img2d_max_width = 0;
    device_info.img2d_max_height = 0;        /* img2d_max_width, img2d_max_height */
    device_info.img3d_max_width = 0;
    device_info.img3d_max_height = 0;
    device_info.img3d_max_depth = 0;/* img3d_max_width,img3d_max_height,img3d_max_depth*/
    device_info.max_samplers = 0;         /* max_samplers */
    device_info.max_param_sz = 256;          /* max_param_sz */
    device_info.mem_align_bits = 32;         /* mem_align_bits */
    device_info.datatype_align_sz = 8;          /* datatype_align_sz */
    device_info.single_fp_config = CL_FP_ROUND_TO_NEAREST|CL_FP_INF_NAN; /* single_fp_config */
    device_info.global_mem_cache_type = CL_NONE;   /* global_mem_cache_type */
    device_info.global_mem_cacheline_sz = 0;          /* global_mem_cacheline_sz */
    device_info.global_mem_cache_sz = 0;        /* global_mem_cache_sz */
    device_info.global_mem_sz = 1024*1024;  /* global_mem_sz *///TODO: Look this up later
    device_info.max_const_buffer_sz = 0;       /* cl_ulong max_const_buffer_sz */
    device_info.max_const_narg = 0;          /* max_const_narg */
    device_info.local_mem_type = CL_GLOBAL;  /* local_mem_type */
    device_info.local_mem_sz = 1024;     /* local_mem_sz *///TODO: look this up
    device_info.supp_ec = CL_FALSE; /* supp_ec */
    device_info.prof_timer_res = 0;          /* prof_timer_res */
    device_info.endian_little = CL_TRUE;     /* endian_little */
    device_info.supp_exec_cap = CL_EXEC_KERNEL; /* supp_exec_cap */
    device_info.cmdq_prop = CL_QUEUE_PROFILING_ENABLE; /* cmdq_prop */
    device_info.platformid = (cl_platform_id)(-1); /* platformid */
}


void*
clGetExtensionFunctionAddress( const char* funcname )
{
    perror("clGetExtensionFunctionAddress called.\n");

    if (funcname == NULL)
        return NULL;
    else if (!strcmp("clIcdGetPlatformIDsKHR", funcname))
        return &clIcdGetPlatformIDsKHR;
    else
        return NULL;
}


