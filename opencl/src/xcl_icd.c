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
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <CL/cl.h>

#include "version.h"
#include "xcl_structs.h"
#include "version.h"
#include "printcl.h"

#ifndef min
#define min(a,b) ((a<b)?a:b)
#endif

// ICD stuff 

static struct _cl_device_id device_id;
static struct _cl_platform_id platform_id;

static void initialize_dev_info(void);

extern KHRicdVendorDispatch the_dispatch_vector;

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

    platform_id.dispatch = &the_dispatch_vector;
    platform_id.profile = "<profile>";
    platform_id.version = EOCL_PLATFORM_VERSION;
    platform_id.name = EOCL_PLATFORM_NAME;
    platform_id.vendor = EOCL_PLATFORM_VENDOR;
    platform_id.extensions = EOCL_PLATFORM_EXTENSIONS;
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
    device_id.dispatch = &the_dispatch_vector;
    device_id.devtype = CL_DEVICE_TYPE_ACCELERATOR;
    device_id.vendorid = 0;
    device_id.max_compute_units = 1;          /* max_compute_units */
    device_id.max_wi_dim = 3;
    device_id.max_wi_sz[0] = 1; /* max_wi_dim,max_wi_sz[] */
    device_id.max_wi_sz[1] = 1; /* max_wi_dim,max_wi_sz[] */
    device_id.max_wi_sz[2] = 1; /* max_wi_dim,max_wi_sz[] */
    device_id.max_wi_sz[3] = 0; /* max_wi_dim,max_wi_sz[] */
    device_id.max_wg_sz = 16;           /* max_wg_sz */
    device_id.pref_charn = 4;
    device_id.pref_shortn = 2;
    device_id.pref_intn = 1;
    device_id.pref_longn = 1;
    device_id.pref_floatn = 1;
    device_id.pref_doublen = 1;   /* pref_char/short/int/long/float/double/n */
    device_id.max_freq = 0;          /* max_freq */
    device_id.addr_bits = 32;        /* bits */
    device_id.max_mem_alloc_sz = 1024*1024*1024;    /* max_mem_alloc_sz */
    device_id.supp_img = CL_FALSE;   /* supp_img */
    device_id.img_max_narg_r = 0;
    device_id.img_max_narg_w = 0;          /* img_max_narg_r, img_max_narg_w */
    device_id.img2d_max_width = 0;
    device_id.img2d_max_height = 0;        /* img2d_max_width, img2d_max_height */
    device_id.img3d_max_width = 0;
    device_id.img3d_max_height = 0;
    device_id.img3d_max_depth = 0;/* img3d_max_width,img3d_max_height,img3d_max_depth*/
    device_id.max_samplers = 0;         /* max_samplers */
    device_id.max_param_sz = 256;          /* max_param_sz */
    device_id.mem_align_bits = 32;         /* mem_align_bits */
    device_id.datatype_align_sz = 8;          /* datatype_align_sz */
    device_id.single_fp_config = CL_FP_ROUND_TO_NEAREST|CL_FP_INF_NAN; /* single_fp_config */
    device_id.global_mem_cache_type = CL_NONE;   /* global_mem_cache_type */
    device_id.global_mem_cacheline_sz = 0;          /* global_mem_cacheline_sz */
    device_id.global_mem_cache_sz = 0;        /* global_mem_cache_sz */
    device_id.global_mem_sz = 1024*1024;  /* global_mem_sz *///TODO: Look this up later
    device_id.max_const_buffer_sz = 0;       /* cl_ulong max_const_buffer_sz */
    device_id.max_const_narg = 0;          /* max_const_narg */
    device_id.local_mem_type = CL_GLOBAL;  /* local_mem_type */
    device_id.local_mem_sz = 1024;     /* local_mem_sz *///TODO: look this up
    device_id.supp_ec = CL_FALSE; /* supp_ec */
    device_id.prof_timer_res = 0;          /* prof_timer_res */
    device_id.endian_little = CL_TRUE;     /* endian_little */
    device_id.supp_exec_cap = CL_EXEC_KERNEL; /* supp_exec_cap */
    device_id.cmdq_prop = CL_QUEUE_PROFILING_ENABLE; /* cmdq_prop */
    device_id.platformid = (cl_platform_id)(-1); /* platformid */

    device_id.avail = true;
    device_id.compiler_avail = true;
    device_id.extensions = EOCL_PLATFORM_EXTENSIONS;
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


