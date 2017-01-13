/* ocl_device.c 
 *
 * Copyright (c) 2009-2013 Brown Deer Technology, LLC.  All Rights Reserved.
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

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <CL/cl.h>

#include "xcl_structs.h"
#include "printcl.h"
#include "version.h"

#define min(a,b) ((a<b)?a:b)

// Device API Calls

cl_int 
_clGetDeviceIDs(
	cl_platform_id platformid,
	cl_device_type devtype,
	cl_uint ndev,  
	cl_device_id* devices,
	cl_uint* ndev_ret
)
{
    if (platformid == NULL)
        return CL_INVALID_PLATFORM;
    else if (ndev == 0 && devices != NULL)
        return CL_INVALID_VALUE;
    else if (devices != NULL && ndev_ret != NULL)
        return CL_INVALID_VALUE;

    cl_uint num_devs = platformid->ndevices;
    if (num_devs == 0)
        return CL_DEVICE_NOT_FOUND;

    if (ndev_ret != NULL)
        *ndev_ret = num_devs;
    else
        *devices = platformid->dtab;

    return CL_SUCCESS;
}


cl_int 
_clGetDeviceInfo(
	cl_device_id devid,
	cl_device_info param_name,
	size_t param_sz, 
	void* param_val,
	size_t* param_sz_ret
) 
{
    if (devid == NULL)
        return CL_INVALID_DEVICE;

    if (param_sz_ret == NULL && param_val == NULL)
        return CL_INVALID_VALUE;

    if (param_val != NULL && param_sz == 0)
        return CL_INVALID_VALUE;

    char *info = NULL;
    bool info_string = false;
    switch (param_name) {
        case CL_DEVICE_TYPE:
            if (param_val != NULL)
                *((cl_device_type *)param_val) = devid->devtype;
            else
                *param_sz_ret = sizeof(devid->devtype);
            break;
        case CL_DEVICE_VENDOR_ID:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->vendorid;
            else
                *param_sz_ret = sizeof(devid->vendorid);
            break;
        case CL_DEVICE_MAX_COMPUTE_UNITS:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->max_compute_units;
            else
                *param_sz_ret = sizeof(devid->max_compute_units);
            break;
        case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->max_wi_dim;
            else
                *param_sz_ret = sizeof(devid->max_wi_dim);
            break;
        case CL_DEVICE_MAX_WORK_ITEM_SIZES:
            if (param_val != NULL)
                *((size_t **)param_val) = devid->max_wi_sz;
            else
                *param_sz_ret = sizeof(devid->max_wi_sz[0] * 4);
            break;
        case CL_DEVICE_MAX_WORK_GROUP_SIZE:
            if (param_val != NULL)
                *((size_t *)param_val) = devid->max_wg_sz;
            else
                *param_sz_ret = sizeof(devid->max_wg_sz); 
            break;
        case CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->pref_charn;
            else
                *param_sz_ret = sizeof(devid->pref_charn);
            break;
        case CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->pref_shortn;
            else
                *param_sz_ret = sizeof(devid->pref_shortn);
            break;
        case CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->pref_intn;
            else
                *param_sz_ret = sizeof(devid->pref_intn);
            break;
        case CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->pref_longn;
            else
                *param_sz_ret = sizeof(devid->pref_longn);
            break;
        case CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->pref_floatn;
            else
                *param_sz_ret = sizeof(devid->pref_floatn);
            break;
        case CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->pref_doublen;
            else
                *param_sz_ret = sizeof(devid->pref_doublen);
            break;
        case CL_DEVICE_MAX_CLOCK_FREQUENCY:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->max_freq;
            else
                *param_sz_ret = sizeof(devid->max_freq);
            break;
        case CL_DEVICE_ADDRESS_BITS:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->addr_bits;
            else
                *param_sz_ret = sizeof(devid->addr_bits);
            break;
        case CL_DEVICE_MAX_MEM_ALLOC_SIZE:
            if (param_val != NULL)
                *((cl_ulong *)param_val) = devid->max_mem_alloc_sz;
            else
                *param_sz_ret = sizeof(devid->max_mem_alloc_sz);
            break;
        case CL_DEVICE_IMAGE_SUPPORT:
            if (param_val != NULL)
                *((cl_bool *)param_val) = devid->supp_img;
            else
                *param_sz_ret = sizeof(devid->supp_img);
            break;
        case CL_DEVICE_MAX_READ_IMAGE_ARGS:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->img_max_narg_r;
            else
                *param_sz_ret = sizeof(devid->img_max_narg_r);
            break;
        case CL_DEVICE_MAX_WRITE_IMAGE_ARGS:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->img_max_narg_w;
            else
                *param_sz_ret = sizeof(devid->img_max_narg_w);
            break;
        case CL_DEVICE_IMAGE2D_MAX_WIDTH:
            if (param_val != NULL)
                *((size_t *)param_val) = devid->img2d_max_width;
            else
                *param_sz_ret = sizeof(devid->img2d_max_width);
            break;
        case CL_DEVICE_IMAGE2D_MAX_HEIGHT:
            if (param_val != NULL)
                *((size_t *)param_val) = devid->img2d_max_height;
            else
                *param_sz_ret = sizeof(devid->img2d_max_height);
            break;
        case CL_DEVICE_IMAGE3D_MAX_WIDTH:
            if (param_val != NULL)
                *((size_t *)param_val) = devid->img3d_max_width;
            else
                *param_sz_ret = sizeof(devid->img3d_max_width);
            break;
        case CL_DEVICE_IMAGE3D_MAX_HEIGHT:
            if (param_val != NULL)
                *((size_t *)param_val) = devid->img3d_max_height;
            else
                *param_sz_ret = sizeof(devid->img3d_max_height);
            break;
        case CL_DEVICE_IMAGE3D_MAX_DEPTH:
            if (param_val != NULL)
                *((size_t *)param_val) = devid->img3d_max_depth;
            else
                *param_sz_ret = sizeof(devid->img3d_max_depth);
            break;
        case CL_DEVICE_MAX_SAMPLERS:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->max_samplers;
            else
                *param_sz_ret = sizeof(devid->max_samplers);
            break;
        case CL_DEVICE_MAX_PARAMETER_SIZE:
            if (param_val != NULL)
                *((size_t *)param_val) = devid->max_param_sz;
            else
                *param_sz_ret = sizeof(devid->max_param_sz);
            break;
        case CL_DEVICE_MEM_BASE_ADDR_ALIGN:	
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->mem_align_bits;
            else
                *param_sz_ret = sizeof(devid->mem_align_bits);
            break;
        case CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->datatype_align_sz;
            else
                *param_sz_ret = sizeof(devid->datatype_align_sz);
            break;
        case CL_DEVICE_SINGLE_FP_CONFIG:
            if (param_val != NULL)
                *((cl_device_fp_config *)param_val) = devid->single_fp_config;
            else
                *param_sz_ret = sizeof(devid->single_fp_config);
            break;
        case CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:
            if (param_val != NULL)
                *((cl_device_mem_cache_type *)param_val) =
                        devid->global_mem_cache_type;
            else
                *param_sz_ret = sizeof(devid->global_mem_cache_type);
            break;
        case CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:
            if (param_val != NULL)
                *((cl_uint *)param_val) = devid->global_mem_cacheline_sz;
            else
                *param_sz_ret = sizeof(devid->global_mem_cacheline_sz);
            break;
        case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:
            if (param_val != NULL)
                *((cl_ulong *)param_val) = devid->global_mem_cache_sz;
            else
                *param_sz_ret = sizeof(devid->global_mem_cache_sz);
            break;
        case CL_DEVICE_GLOBAL_MEM_SIZE:
            if (param_val != NULL)
                *((cl_ulong *)param_val) = devid->global_mem_sz;
            else
                *param_sz_ret = sizeof(devid->global_mem_sz);
            break;
        case CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:
            if (param_val != NULL)
                *((cl_ulong *)param_val) = devid->max_const_buffer_sz;
            else
                *param_sz_ret = sizeof(devid->max_const_buffer_sz);
            break;
        case CL_DEVICE_MAX_CONSTANT_ARGS:
            if (param_val != NULL)
                *((cl_ulong *)param_val) = devid->max_const_narg;
            else
                *param_sz_ret = sizeof(devid->max_const_narg);
            break;
        case CL_DEVICE_LOCAL_MEM_TYPE:
            if (param_val != NULL)
                *((cl_device_local_mem_type *)param_val) = devid->local_mem_type;
            else
                *param_sz_ret = sizeof(devid->local_mem_type);
            break;
        case CL_DEVICE_LOCAL_MEM_SIZE:
            if (param_val != NULL)
                *((cl_ulong *)param_val) = devid->local_mem_sz;
            else
                *param_sz_ret = sizeof(devid->local_mem_sz);
            break;
        case CL_DEVICE_ERROR_CORRECTION_SUPPORT:
            if (param_val != NULL)
                *((cl_bool *)param_val) = devid->supp_ec;
            else
                *param_sz_ret = sizeof(devid->supp_ec);
            break;
        case CL_DEVICE_PROFILING_TIMER_RESOLUTION:
            if (param_val != NULL)
                *((size_t *)param_val) = devid->prof_timer_res;
            else
                *param_sz_ret = sizeof(devid->prof_timer_res);
            break;
        case CL_DEVICE_ENDIAN_LITTLE:
            if (param_val != NULL)
                *((cl_bool *)param_val) = devid->endian_little;
            else
                *param_sz_ret = sizeof(devid->endian_little);
            break;
        case CL_DEVICE_AVAILABLE:
            if (param_val != NULL)
                *((cl_bool *)param_val) = devid->avail;
            else
                *param_sz_ret = sizeof(devid->avail);
            break;
        case CL_DEVICE_COMPILER_AVAILABLE:
            if (param_val != NULL)
                *((cl_bool *)param_val) = devid->compiler_avail;
            else
                *param_sz_ret = sizeof(devid->compiler_avail);
            break;
        case CL_DEVICE_EXECUTION_CAPABILITIES:
            if (param_val != NULL)
                *((cl_device_exec_capabilities *)param_val) =
                        devid->supp_exec_cap;
            else
                *param_sz_ret = sizeof(devid->supp_exec_cap);
            break;
        case CL_DEVICE_QUEUE_PROPERTIES:
            if (param_val != NULL)
                *((cl_command_queue_properties *)param_val) =
                        devid->cmdq_prop;
            else
                *param_sz_ret = sizeof(devid->cmdq_prop);
            break;
        case CL_DEVICE_PLATFORM:
            if (param_val != NULL)
                *((cl_platform_id *)param_val) = devid->platformid;
            else
                *param_sz_ret = sizeof(devid->platformid);
            break;
        case CL_DEVICE_NAME:
            if (param_val != NULL)
                strncpy((char *)param_val, EOCL_DEVICE_NAME, param_sz);
            else
                *param_sz_ret = strlen(EOCL_DEVICE_NAME);
            break;
        case CL_DEVICE_VENDOR:
            if (param_val != NULL)
                strncpy((char *)param_val, EOCL_DEVICE_VENDOR, param_sz);
            else
                *param_sz_ret = strlen(EOCL_DEVICE_NAME);
            break;
        case CL_DRIVER_VERSION:
            if (param_val != NULL)
                strncpy((char *)param_val, EOCL_DRIVER_VERSION, param_sz);
            else
                *param_sz_ret = strlen(EOCL_DRIVER_VERSION);
            break;
        case CL_DEVICE_PROFILE:
            if (param_val != NULL)
                strncpy((char *)param_val, EOCL_DEVICE_PROFILE, param_sz);
            else
                *param_sz_ret = strlen(EOCL_DEVICE_PROFILE);
            break;
        case CL_DEVICE_VERSION:
            if (param_val != NULL)
                strncpy((char *)param_val, EOCL_DEVICE_VERSION, param_sz);
            else
                *param_sz_ret = strlen(EOCL_DEVICE_VERSION);
            break;
        case CL_DEVICE_EXTENSIONS:
            if (param_val != NULL)
                strncpy((char *)param_val, devid->extensions, param_sz);
            else
                *param_sz_ret = strlen(devid->extensions);
            break;
        default:
            return CL_INVALID_VALUE;
    }

    if (info_string)
    {
        size_t len = strlen(info);

        if (param_val != NULL)
            strncpy((char *)param_val, info, param_sz);
    }

    return CL_SUCCESS;
}


// Aliased Device APi Calls

cl_int
clGetDeviceIDs( cl_platform_id platformid, cl_device_type devtype, 
	cl_uint ndev, cl_device_id* devices, cl_uint* ndev_ret)
	__attribute__((alias("_clGetDeviceIDs")));


cl_int
clGetDeviceInfo( cl_device_id devid, cl_device_info param_name,
   size_t param_sz, void* param_val, size_t* param_sz_ret)
	__attribute__((alias("_clGetDeviceInfo")));



/*
 * Internal device implementation calls
 */

void __do_discover_devices(
	unsigned int* p_ndevices, 
	struct _cl_device_id** p_dtab, 
	int flag
)
{
#if 0
	int i;

	printcl( CL_DEBUG "__do_discover_devices %p",*p_dtab);

	if (*p_dtab) return;

	struct coprthr_device** devtab = 0;

	__do_discover_devices_1(p_ndevices,&devtab,flag);

	struct _cl_device_id* dtab = *p_dtab = (struct _cl_device_id*)
      malloc(*p_ndevices*sizeof(struct _cl_device_id));

	for(i = 0; i<(*p_ndevices); i++) {
		__init_device_id(dtab+i);
		dtab[i].codev = devtab[i];
	}

	for(i = 0; i<(*p_ndevices); i++) {

		dtab[i].ocldevinfo = (struct opencl_device_info*)
			malloc(sizeof(struct opencl_device_info));

		switch(dtab[i].codev->devinfo->arch_id) {

			case COPRTHR_ARCH_ID_X86_64:
				printcl( CL_DEBUG "DEVICE %d is arch x86_64",i);
				__do_discover_opencl_device_info_x86_64(dtab[i].codev,
					dtab[i].ocldevinfo);
				break;

			case COPRTHR_ARCH_ID_E32:
				printcl( CL_DEBUG "DEVICE %d is arch e32",i);
				__do_discover_opencl_device_info_e32(dtab[i].codev,
					dtab[i].ocldevinfo);
				break;

			default:
				break;
		}
	}

	printcl( CL_DEBUG "__do_discover_devices ndevices %d",*p_ndevices);
#endif
}


void __do_get_ndevices(
	cl_platform_id platformid, cl_device_type devtype, cl_uint* ndev 
)
{
#if 0
	unsigned int ndevices = __resolve_platformid(platformid,ndevices);
	struct _cl_device_id* dtab = __resolve_platformid(platformid,dtab);

	printcl( CL_DEBUG "ndevices = %d",ndevices);

	int devnum;
	unsigned int n = 0;

	for(devnum=0;devnum<ndevices;devnum++) {
		printcl( CL_DEBUG "match devtype %d %d",
			dtab[devnum].ocldevinfo->devtype,devtype);
		if (dtab[devnum].ocldevinfo->devtype & devtype) n++;
	}

	printcl( CL_DEBUG "n = %d",n);

	*ndev = n;
#endif
}



void __do_get_devices(
	cl_platform_id platformid, cl_device_type devtype, 
	cl_uint ndev, cl_device_id* devices)
{
#if 0
	unsigned int ndevices = __resolve_platformid(platformid,ndevices);
	struct _cl_device_id* dtab = __resolve_platformid(platformid,dtab);

	int devnum;
	int n = 0;

	for(devnum=0;devnum<ndevices;devnum++) 
		if (n<ndev && dtab[devnum].ocldevinfo->devtype & devtype) 
			devices[n++] = &__resolve_platformid(platformid,dtab[devnum]);
#endif
}


