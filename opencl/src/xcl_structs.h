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


extern void* __icd_call_vector;


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
	void* _reserved;
	char* profile;
   char* version;
   char* name;
   char* vendor;
   char* extensions;
   unsigned int ndevices;
   struct _cl_device_id* dtab;
};

#define __init_platform_id(platformid) do { \
	platformid->_reserved = (void*)__icd_call_vector; \
	} while(0)

#define __free_platformid(platformid) do { \
	__free_platform_id(platformid); \
	} while(0)

#define __invalid_platform_id(platformid) (!platformid)

#define __resolve_platformid(p,m) ((p)->m)


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
	void* _reserved;
	struct opencl_device_info* ocldevinfo;
};


/* 
 * context 
 */

struct _cl_context {
	void* _reserved;
	cl_uint refc;
	cl_context_properties* prop;
	cl_uint ndev;
	cl_device_id* devices;
	void (*pfn_notify)(const char*, const void*, size_t, void*);
	void* user_data;
};

#define __init_context(ctx) do { \
	ctx->_reserved = (void*)__icd_call_vector; \
	ctx->refc = 0; \
	ctx->prop = 0; \
	ctx->ndev = 0; \
	ctx->devices = 0; \
	ctx->pfn_notify = 0; \
	ctx->user_data = 0; \
	} while(0)

#define __free_context(ctx) do { \
	__free(ctx->prop); \
	__free(ctx->devices); \
	__free(ctx); \
	} while(0)

#define __invalid_context(ctx) (!ctx)




/* 
 * command queue 
 */

struct _cl_command_queue {
	void* _reserved;
	cl_uint refc;
	cl_context ctx;
	cl_device_id devid;
	cl_command_queue_properties prop;
	unsigned int devnum;
	struct coprthr_command_queue* ptr_imp;
};

#define __init_command_queue(cmdq) do { \
	cmdq->_reserved = (void*)__icd_call_vector; \
	cmdq->refc = 0; \
	cmdq->ctx = (cl_context)0; \
	cmdq->devid = (cl_device_id)0; \
	cmdq->prop = (cl_command_queue_properties)0; \
	cmdq->ptr_imp = 0; \
	} while(0)

#define __free_command_queue(cmdq) do { \
	printcl( CL_DEBUG "before __coprthr_free_command_queue"); \
	__coprthr_free_command_queue(cmdq->devid->codev->devstate->cmdq); \
	printcl( CL_DEBUG "after __coprthr_free_command_queue"); \
	cmdq->ptr_imp = 0; \
	__free(cmdq); \
	} while(0)

#define __invalid_command_queue(cmdq) (!cmdq)



/* 
 * memobj
 */

struct _cl_mem {
	void* _reserved;
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

#define __init_memobj(memobj) do { \
	memobj->_reserved = (void*)__icd_call_vector; \
	memobj->ctx = (cl_context)0; \
	memobj->sz = 0; \
	memobj->width = 0; \
	memobj->height = 0; \
	memobj->pitch = 0; \
	memobj->host_ptr = 0; \
	memobj->type = (cl_mem_object_type)0; \
	memobj->flags = 0; \
	memobj->refc = 0; \
	memobj->mapc = 0; \
	} while(0)

#define __free_memobj(memobj) do { \
	__free(memobj); \
	} while(0) 

#define __invalid_memobj(memobj) (!memobj)

#define __invalid_membuf(membuf) \
	(!membuf || membuf->type != CL_MEM_OBJECT_BUFFER)

#define __invalid_image(image) \
	(!image || (image->type != CL_MEM_OBJECT_IMAGE2D \
		&& image->type != CL_MEM_OBJECT_IMAGE3D) )

#define __invalid_mapped_ptr(ptr) (!ptr)

#define __retain_memobj(memobj) do { \
	++memobj->refc; \
	} while(0)

#define __release_memobj(memobj) do { \
	if (--memobj->refc == 0) { \
	__do_release_memobj(memobj); \
	__free_memobj(memobj); \
	} \
	} while(0)



/* 
 * program 
 */

struct _cl_program {
	void* _reserved;
	cl_uint refc;
	cl_context ctx;
	cl_uint ndev;
	cl_device_id* devices;
	size_t src_sz;
	char* src;
	unsigned int nkrn;
	struct coprthr_program** prg1;
};

#define __init_program(prg) do { \
	prg->_reserved = (void*)__icd_call_vector; \
	prg->refc = 0; \
	prg->ctx = (cl_context)0; \
	prg->ndev = 0; \
	prg->devices = 0; \
	prg->src_sz = 0; \
	prg->src = 0; \
	prg->nkrn = 0; \
	prg->prg1 = 0; \
	} while(0)

#define __free_program(prg) do { \
	__free(prg->devices); \
	__free(prg->src); \
	__free(prg); \
	} while(0)

#define __invalid_program(prg) (!prg)

#define __invalid_executable(prg) (0) /* XXX no check force error -DAR */

#define __retain_program(prg) do { \
	++prg->refc; \
	} while(0)

#define __release_program(prg) do { \
	if (--prg->refc == 0) { \
	__do_release_program(prg); \
	__free_program(prg); \
	} \
	} while(0)



/* 
 * kernel 
 */

struct _cl_kernel {
	void* _reserved;
	cl_uint refc;
	cl_context ctx;
	cl_program prg;
	unsigned char* name;
	cl_uint narg;
	struct coprthr_kernel** krn1;
};

#define __init_kernel(krn) do { \
	krn->_reserved = (void*)__icd_call_vector; \
	krn->refc = 0; \
	krn->ctx = (cl_context)0; \
	krn->prg = (cl_program)0; \
	krn->name = 0; \
	krn->narg = 0; \
	krn->krn1 = 0; \
	} while(0)

#define __free_kernel(krn) do { \
	__free(krn); \
	} while(0)

#define __invalid_kernel(krn) (!krn)

#define __invalid_kernel_args(krn) (0) /* XXX no check force error -DAR */

#define __retain_kernel(krn) do { \
	++krn->refc; \
	} while(0)

#define __release_kernel(krn) do { \
	if (--krn->refc == 0) { \
	__release_program(krn->prg); \
	__do_release_kernel(krn); \
	__free_kernel(krn); \
	} \
	} while(0)



/* 
 * event 
 */

struct _cl_event {
	void* _reserved;
	cl_uint refc;
	cl_context ctx;
	cl_command_queue cmdq;
	cl_command_type cmd;
	struct coprthr_device* dev;
	struct coprthr_event* ev1;
};

#define __init_event(ev) do { \
	ev->_reserved = (void*)__icd_call_vector; \
	ev->refc = 0; \
	ev->ctx = (cl_context)0; \
	ev->cmdq = (cl_command_queue)0; \
	ev->cmd = (cl_command_type)0; \
	ev->ev1 = (struct coprthr_event*)malloc(sizeof(struct coprthr_event));\
	__coprthr_init_event(ev->ev1); \
	} while(0)

#define __free_event(ev) do { \
	__coprthr_free_event(ev->ev1); \
	__free(ev); \
	} while(0)

#define __invalid_event(ev) (!ev)


/* refc MUST NOT be manipulated directly, use these macros */
/* XXX this should be propagated to other objects with refc -DAR */

#define __retain_event(ev) do { \
	++ev->refc; \
	} while(0)

#define __release_event(ev) do { \
	if (--ev->refc == 0) { \
	printcl( CL_DEBUG "__release_event: do release"); \
	__do_release_event(ev); \
	__free_event(ev); \
	} else __unlock_event(ev); \
	} while(0)

	

/* 
 * sampler 
 */

struct _cl_sampler {
	void* _reserved;
	cl_uint refc;
	cl_context ctx;
	cl_bool norm_coords;
	cl_addressing_mode amode;
	cl_filter_mode fmode;
};

#define __init_sampler(smp) do { \
	smp->_reserved = (void*)__icd_call_vector; \
	smp->refc = 0; \
	smp->ctx = (cl_context)0; \
	} while(0)

#define __free_sampler(smp) do { \
	__free(smp); \
	} while(0)

#define __invalid_sampler(smp) (!smp)


/* 
 * error 
 */

#define __success() do { if (err_ret) *err_ret = CL_SUCCESS; } while(0)

#define __error(ERR) do { if (err_ret) *err_ret = ERR; } while(0)

#define __error_return(ERR,rtype) \
	do { if (err_ret) *err_ret = ERR; return((rtype)0); } while(0)



/* 
 * get param 
 */

#define __case_get_param(s,p) do { \
	sz = s; \
	if (param_sz_ret) *param_sz_ret = sz; \
	if (param_sz < sz && param_val) return(CL_INVALID_VALUE); \
	else if (param_val) memcpy(param_val,p,sz); \
	} while(0)



/* 
 * waitlist 
 */

#define __check_waitlist(nwaitlist,waitlist,ctx) do { \
   if (nwaitlist > 0 && !waitlist) return(CL_INVALID_EVENT_WAIT_LIST); \
   if (nwaitlist == 0 && waitlist) return(CL_INVALID_EVENT_WAIT_LIST); \
   int i; for(i=0;i<nwaitlist;i++) { \
      if (__invalid_event(waitlist[i])) return(CL_INVALID_EVENT_WAIT_LIST); \
      if (__invalid_context(waitlist[i]->ctx)) return(CL_INVALID_CONTEXT); \
      if (waitlist[i]->ctx != ctx) return(CL_INVALID_CONTEXT); \
   	} \
	} while(0)



/* 
 * event 
 */

#define __set_cmd_read_buffer(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_READ_BUFFER; \
	} while(0)

#define __set_cmd_write_buffer(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_WRITE_BUFFER; \
	} while(0)

#define __set_cmd_copy_buffer(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_COPY_BUFFER; \
	} while(0)

#define __set_cmd_read_image(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_READ_IMAGE; \
	} while(0)

#define __set_cmd_write_image(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_WRITE_IMAGE; \
	} while(0)

#define __set_cmd_copy_image(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_COPY_IMAGE; \
	} while(0)

#define __set_cmd_copy_image_to_buffer(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_COPY_IMAGE_TO_BUFFER; \
	} while(0)

#define __set_cmd_copy_buffer_to_image(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_COPY_BUFFER_TO_IMAGE; \
	} while(0)

#define __set_cmd_map_buffer(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_MAP_BUFFER; \
	} while(0)

#define __set_cmd_map_image(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_MAP_IMAGE; \
	} while(0)

#define __set_cmd_unmap_mem_object(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_UNMAP_MEM_OBJECT; \
	} while(0)

#define __set_cmd_ndrange_kernel(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_NDRANGE_KERNEL; \
	} while(0)

#define __set_cmd_task(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_TASK; \
	} while(0)

#define __set_cmd_native_kernel(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_NATIVE_KERNEL; \
	} while(0)

#define __set_cmd_marker(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_MARKER; \
	} while(0)

#define __set_cmd_wait_for_events(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_WAIT_FOR_EVENTS; \
	} while(0)

#define __set_cmd_barrier(ev) do { \
	ev->refc = 1; \
	ev->cmd = __CL_COMMAND_BARRIER; \
	} while(0)

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

