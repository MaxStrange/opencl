/* xcl_structs.h 
 *
 * Copyright (c) 2009-2012 Brown Deer Technology, LLC.  All Rights Reserved.
 *
 * This software was developed by Brown Deer Technology, LLC.
 * For more information contact info@browndeertechnology.com
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

/* DAR */

#ifndef _XCL_STRUCTS_H
#define _XCL_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <CL/cl.h>

#include "printcl.h"



#define CL_ENOTSUP	-255
#define __CLMAXSTR_LEN 1023
#define __CLMAXSTR_BUFSZ (__CLMAXSTR_LEN+1)


/* notice that __free() ensures the ptr is set null, failure to do this
 * can lead to lockups with bad CL code -DAR */

#define __free(p) do { if (p) { free(p); p=0; } } while(0)

/* 
 * platform 
 */

struct _cl_platform_id {
    void* dispatch;
    char* profile;
    char* version;
    char* name;
    char* vendor;
    char* extensions;
    unsigned int ndevices;
    struct _cl_device_id* dtab;
};

/* 
 * device 
 */

struct opencl_device_info {
    cl_device_type devtype;
    cl_uint vendorid;
    cl_uint max_compute_units;
    cl_uint max_wi_dim;
    size_t max_wi_sz[4];
    size_t max_wg_sz;
    cl_uint pref_charn;
    cl_uint pref_shortn;
    cl_uint pref_intn;
    cl_uint pref_longn;
    cl_uint pref_floatn;
    cl_uint pref_doublen;
    cl_uint max_freq;
    cl_uint addr_bits;
    cl_ulong max_mem_alloc_sz;
    cl_bool supp_img;
    cl_uint img_max_narg_r;
    cl_uint img_max_narg_w;
    size_t img2d_max_width;
    size_t img2d_max_height;
    size_t img3d_max_width;
    size_t img3d_max_height;
    size_t img3d_max_depth;
    cl_uint max_samplers;
    size_t max_param_sz;
    cl_uint mem_align_bits;
    cl_uint datatype_align_sz;
    cl_device_fp_config single_fp_config;
    cl_device_mem_cache_type global_mem_cache_type;
    cl_uint global_mem_cacheline_sz;
    cl_ulong global_mem_cache_sz;
    cl_ulong global_mem_sz;
    cl_ulong max_const_buffer_sz;
    cl_uint max_const_narg;
    cl_device_local_mem_type local_mem_type;
    cl_ulong local_mem_sz;
    cl_bool supp_ec;
    size_t prof_timer_res;
    cl_bool endian_little;
    cl_device_exec_capabilities supp_exec_cap;
    cl_command_queue_properties cmdq_prop;
    cl_platform_id platformid;

    cl_bool avail;
    cl_bool compiler_avail;

    char* extensions;
};

struct _cl_device_id {
    void* dispatch;
    struct opencl_device_info* ocldevinfo;
};


/* 
 * context 
 */

struct _cl_context {
    void* dispatch;
    cl_uint refc;
    cl_context_properties* prop;
    cl_uint ndev;
    cl_device_id* devices;
    void (*pfn_notify)(const char*, const void*, size_t, void*);
    void* user_data;
};

/* 
 * command queue 
 */

struct _cl_command_queue {
    void* dispatch;
    cl_uint refc;
    cl_context ctx;
    cl_device_id devid;
    cl_command_queue_properties prop;
    unsigned int devnum;
    struct coprthr_command_queue* ptr_imp;
};

/* 
 * memobj
 */

struct _cl_mem {
    void* dispatch;
    cl_context ctx;
    size_t sz;
    size_t width;
    size_t height;
    size_t pitch;
    void* host_ptr;
    cl_mem_object_type type;
    cl_mem_flags flags;
    cl_uint refc;
    cl_uint mapc;
    struct coprthr_mem** mem1;
};

struct _cl_mapped_ptr_info {
};

/* 
 * program 
 */

struct _cl_program {
    void* dispatch;
    cl_uint refc;
    cl_context ctx;
    cl_uint ndev;
    cl_device_id* devices;
    size_t src_sz;
    char* src;
    unsigned int nkrn;
    struct coprthr_program** prg1;
};


/* 
 * kernel 
 */

struct _cl_kernel {
    void* dispatch;
    cl_uint refc;
    cl_context ctx;
    cl_program prg;
    unsigned char* name;
    cl_uint narg;
    struct coprthr_kernel** krn1;
};


/* 
 * event 
 */

struct _cl_event {
    void* dispatch;
    cl_uint refc;
    cl_context ctx;
    cl_command_queue cmdq;
    cl_command_type cmd;
    struct coprthr_device* dev;
    struct coprthr_event* ev1;
};

/* 
 * sampler 
 */

struct _cl_sampler {
    void* dispatch;
    cl_uint refc;
    cl_context ctx;
    cl_bool norm_coords;
    cl_addressing_mode amode;
    cl_filter_mode fmode;
};

/* 
 * locators
 */

static inline 
cl_uint 
__get_devnum_in_program(
	struct _cl_program* prg, struct _cl_device_id* devid
)
{
    int i;
    for(i=0;i<prg->ndev;i++) if (prg->devices[i]==devid) return(i);
    return((cl_uint)-1);
}

#endif

