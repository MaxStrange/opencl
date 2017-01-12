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

/* DAR */


#include <CL/cl.h>

#include "xcl_structs.h"
#include "printcl.h"

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
#if 0
	if (__invalid_device_id(devid)) return(CL_INVALID_DEVICE);

	size_t sz;

	switch (param_name) {

		case CL_DEVICE_TYPE:

			__case_get_param(sizeof(cl_device_type),
				&__resolve_devid_ocldevinfo(devid,devtype));

			break;

		case CL_DEVICE_VENDOR_ID:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,vendorid));

			break;

		case CL_DEVICE_MAX_COMPUTE_UNITS:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,max_compute_units));

			break;
		case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,max_wi_dim));

			break;

		case CL_DEVICE_MAX_WORK_ITEM_SIZES:

			__case_get_param(
				__resolve_devid_ocldevinfo(devid,max_wi_dim)*sizeof(size_t*),
				&__resolve_devid_ocldevinfo(devid,max_wi_sz));

			break;

		case CL_DEVICE_MAX_WORK_GROUP_SIZE:

			__case_get_param(sizeof(size_t),
				&__resolve_devid_ocldevinfo(devid,max_wg_sz));

			break;

		case CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,pref_charn));

			break;

		case CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,pref_shortn));

			break;

		case CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,pref_intn));

			break;

		case CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,pref_longn));

			break;

		case CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,pref_floatn));

			break;

		case CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,pref_doublen));

			break;

		case CL_DEVICE_MAX_CLOCK_FREQUENCY:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,max_freq));

			break;

		case CL_DEVICE_ADDRESS_BITS:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,addr_bits));

			break;

		case CL_DEVICE_MAX_MEM_ALLOC_SIZE:

			__case_get_param(sizeof(cl_ulong),
				&__resolve_devid_ocldevinfo(devid,max_mem_alloc_sz));

			break;

		case CL_DEVICE_IMAGE_SUPPORT:

			__case_get_param(sizeof(cl_bool),
				&__resolve_devid_ocldevinfo(devid,supp_img));

			break;

		case CL_DEVICE_MAX_READ_IMAGE_ARGS:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,img_max_narg_r));

			break;

		case CL_DEVICE_MAX_WRITE_IMAGE_ARGS:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,img_max_narg_w));

			break;

		case CL_DEVICE_IMAGE2D_MAX_WIDTH:

			__case_get_param(sizeof(size_t),
				&__resolve_devid_ocldevinfo(devid,img2d_max_width));

			break;

		case CL_DEVICE_IMAGE2D_MAX_HEIGHT:

			__case_get_param(sizeof(size_t),
				&__resolve_devid_ocldevinfo(devid,img2d_max_height));

			break;

		case CL_DEVICE_IMAGE3D_MAX_WIDTH:

			__case_get_param(sizeof(size_t),
				&__resolve_devid_ocldevinfo(devid,img3d_max_width));

			break;

		case CL_DEVICE_IMAGE3D_MAX_HEIGHT:


			__case_get_param(sizeof(size_t),
				&__resolve_devid_ocldevinfo(devid,img3d_max_height));

			break;

		case CL_DEVICE_IMAGE3D_MAX_DEPTH:

			__case_get_param(sizeof(size_t),
				&__resolve_devid_ocldevinfo(devid,img3d_max_depth));

			break;

		case CL_DEVICE_MAX_SAMPLERS:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,max_samplers));

			break;

		case CL_DEVICE_MAX_PARAMETER_SIZE:

			__case_get_param(sizeof(size_t),
				&__resolve_devid_ocldevinfo(devid,max_param_sz));

			break;

		case CL_DEVICE_MEM_BASE_ADDR_ALIGN:	

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,mem_align_bits)); 

			break;


		case CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,datatype_align_sz));

			break;

		case CL_DEVICE_SINGLE_FP_CONFIG:

			__case_get_param(sizeof(cl_device_fp_config),
				&__resolve_devid_ocldevinfo(devid,single_fp_config));

			break;

		case CL_DEVICE_GLOBAL_MEM_CACHE_TYPE:

			__case_get_param(sizeof(cl_device_mem_cache_type),
				&__resolve_devid_ocldevinfo(devid,global_mem_cache_type));

			break;

		case CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,global_mem_cacheline_sz));

			break;

		case CL_DEVICE_GLOBAL_MEM_CACHE_SIZE:

			__case_get_param(sizeof(cl_ulong),
				&__resolve_devid_ocldevinfo(devid,global_mem_cache_sz));

			break;

		case CL_DEVICE_GLOBAL_MEM_SIZE:

			__case_get_param(sizeof(cl_ulong),
				&__resolve_devid_ocldevinfo(devid,global_mem_sz));

			break;

		case CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE:

			__case_get_param(sizeof(cl_ulong),
				&__resolve_devid_ocldevinfo(devid,max_const_buffer_sz));

			break;

		case CL_DEVICE_MAX_CONSTANT_ARGS:

			__case_get_param(sizeof(cl_uint),
				&__resolve_devid_ocldevinfo(devid,max_const_narg));

			break;

		case CL_DEVICE_LOCAL_MEM_TYPE:

			__case_get_param(sizeof(cl_device_local_mem_type),
				&__resolve_devid_ocldevinfo(devid,local_mem_type));

			break;

		case CL_DEVICE_LOCAL_MEM_SIZE:

			__case_get_param(sizeof(cl_ulong),
				&__resolve_devid_ocldevinfo(devid,local_mem_sz));

			break;

		case CL_DEVICE_ERROR_CORRECTION_SUPPORT:

			__case_get_param(sizeof(cl_bool),
				&__resolve_devid_ocldevinfo(devid,supp_ec));

			break;

		case CL_DEVICE_PROFILING_TIMER_RESOLUTION:

			__case_get_param(sizeof(size_t),
				&__resolve_devid_ocldevinfo(devid,prof_timer_res));

			break;

		case CL_DEVICE_ENDIAN_LITTLE:

			__case_get_param(sizeof(cl_bool),
				&__resolve_devid_ocldevinfo(devid,endian_little));

			break;

		case CL_DEVICE_AVAILABLE:

			__case_get_param(sizeof(cl_bool),
				&__resolve_devid_ocldevinfo(devid,avail));

			break;

		case CL_DEVICE_COMPILER_AVAILABLE:

			__case_get_param(sizeof(cl_bool),
				&__resolve_devid_ocldevinfo(devid,compiler_avail));

			break;

		case CL_DEVICE_EXECUTION_CAPABILITIES:

			__case_get_param(sizeof(cl_device_exec_capabilities),
				&__resolve_devid_ocldevinfo(devid,supp_exec_cap));

			break;

		case CL_DEVICE_QUEUE_PROPERTIES:

			__case_get_param(sizeof(cl_command_queue_properties),
				&__resolve_devid_ocldevinfo(devid,cmdq_prop));

			break;

		case CL_DEVICE_PLATFORM:

			__case_get_param(sizeof(cl_platform_id),
				&__resolve_devid_ocldevinfo(devid,platformid));

			break;

		case CL_DEVICE_NAME:

			__case_get_param(
				1+strnlen(__resolve_devid_devinfo(devid,name),__CLMAXSTR_BUFSZ),
				__resolve_devid_devinfo(devid,name));

			break;

		case CL_DEVICE_VENDOR:

			__case_get_param(
				1+strnlen(__resolve_devid_devinfo(devid,vendor),__CLMAXSTR_BUFSZ),
				__resolve_devid_devinfo(devid,vendor));

			break;

		case CL_DRIVER_VERSION:

			__case_get_param(
				1+strnlen(__resolve_devid_devinfo(devid,drv_version),__CLMAXSTR_BUFSZ),
				__resolve_devid_devinfo(devid,drv_version));

			break;

		case CL_DEVICE_PROFILE:

			__case_get_param(
				1+strnlen(__resolve_devid_devinfo(devid,profile),__CLMAXSTR_BUFSZ),
				__resolve_devid_devinfo(devid,profile));

			break;

		case CL_DEVICE_VERSION:

			__case_get_param(
				1+strnlen(__resolve_devid_devinfo(devid,version),__CLMAXSTR_BUFSZ),
				__resolve_devid_devinfo(devid,version));

			break;

		case CL_DEVICE_EXTENSIONS:

			__case_get_param(
				1+strnlen(__resolve_devid_ocldevinfo(devid,extensions),__CLMAXSTR_BUFSZ),
				__resolve_devid_ocldevinfo(devid,extensions));

			break;

		default:

			return(CL_INVALID_VALUE);

	}

	return(CL_SUCCESS);
#endif
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


