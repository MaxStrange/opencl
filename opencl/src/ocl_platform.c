/* ocl_platform.c 
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
#include <CL/cl_ext.h>

#include "xcl_structs.h"
#include "printcl.h"
#include "version.h"

#define min(a,b) ((a<b)?a:b)


void __do_discover_platforms();
static void __do_release_platforms();
void __do_get_nplatforms_avail(cl_uint* n);
void __do_get_platforms(cl_uint n, cl_platform_id* platformid);
void __do_get_default_platformid( cl_platform_id* platformid );
static void __do_get_platform_profile(cl_platform_id platformid, char** p_str);
static void __do_get_platform_version(cl_platform_id platformid, char** p_str);
static void __do_get_platform_name(cl_platform_id platformid, char** p_str);
static void __do_get_platform_vendor(cl_platform_id platformid, char** p_str);

static void __do_get_platform_extensions( 
	cl_platform_id platformid, char** p_str);

static void __do_get_platform_icd_suffix_khr(
	cl_platform_id platformid, char** p_str);


// Platform API Calls


cl_int 
_clGetPlatformIDs(
	cl_uint nplatforms,
	cl_platform_id* platforms,
	cl_uint* nplatforms_ret
)
{
    if (nplatforms_ret != NULL)
        *nplatforms_ret = 5;
    return CL_SUCCESS;
#if 0
	printcl( CL_DEBUG "clGetPlatformIDs");
	
	if (nplatforms == 0 && platforms) return(CL_INVALID_VALUE);

	if (!platforms && !nplatforms_ret) return(CL_INVALID_VALUE);

	cl_uint nplatforms_avail;

	__do_discover_platforms();

	__do_get_nplatforms_avail(&nplatforms_avail);

	printcl( CL_DEBUG "nplatforms_avail %d\n",nplatforms_avail);

	if (nplatforms) nplatforms = min(nplatforms,nplatforms_avail);
	else nplatforms = nplatforms_avail;

	if (platforms) __do_get_platforms(nplatforms,platforms);

	if (nplatforms_ret) *nplatforms_ret = nplatforms;

	return(CL_SUCCESS);
#endif
}

char __suffix_str[] = "_coprthr";

cl_int 
_clGetPlatformInfo(
	cl_platform_id platformid, 
	cl_platform_info param_name,
	size_t param_sz, 
	void* param_val,
	size_t* param_sz_ret
) 
{
    if (platformid == NULL)
        return CL_SUCCESS;//return CL_INVALID_PLATFORM;

    perror("blah.\n");
    char *info = NULL;
    switch (param_name)
    {
        case CL_PLATFORM_PROFILE:
            info = platformid->profile;
            break;
        case CL_PLATFORM_VERSION:
            info = platformid->version;
            break;
        case CL_PLATFORM_NAME:
            info = platformid->name;
            break;
        case CL_PLATFORM_VENDOR:
            info = platformid->vendor;
            break;
        case CL_PLATFORM_EXTENSIONS:
            info = platformid->extensions;
            break;
        case CL_PLATFORM_ICD_SUFFIX_KHR:
            info = "eocl";
            perror("Called with CL_PLATFORM_ICD_SUFFIX_KHR.\n");
            break;
        default:
            return CL_INVALID_VALUE;
    }

    size_t len = strlen(info);

    perror("Doing stuff.\n");

    if (param_val != NULL && param_sz < len)
        return CL_INVALID_VALUE;

    if (param_sz_ret !=NULL)
        *param_sz_ret = len;

    if (param_val != NULL)
        strncpy((char *)param_val, info, param_sz);

    perror("Success.\n");

    return CL_SUCCESS;
}



// Aliased Platform API Calls

cl_int
clGetPlatformIDs( cl_uint nplatforms, cl_platform_id* platforms,
   cl_uint* nplatforms_ret)
	__attribute__((alias("_clGetPlatformIDs")));

cl_int
clGetPlatformInfo( cl_platform_id platformid, cl_platform_info param_name,
   size_t param_sz, void* param_val, size_t* param_sz_ret)
	__attribute__((alias("_clGetPlatformInfo")));



// internal platform implementation calls

static struct _cl_platform_id* __ptab = 0;
static unsigned int __nplatforms = 0;

static unsigned int __ndevices = 0;
static struct _cl_device_id* __dtab = 0;


void __do_discover_platforms()
{
#if 0
   int i;

   if (__nplatforms > 0) return;

   __do_discover_devices(&__ndevices,&__dtab,0);

   __nplatforms = 1;
   __ptab = (struct _cl_platform_id*)malloc(sizeof(struct _cl_platform_id));

   __init_platform_id(__ptab);

	
   __ptab[0] = (struct _cl_platform_id){
		(void*)__icd_call_vector,
		"<profile>",
      COPRTHR_VERSION_STRING,
      "coprthr",
      "Brown Deer Technology, LLC.",
      "cl_khr_icd",
      __ndevices,__dtab
   };

   __init_platform_id(__ptab);

       for(i=0;i<__ndevices;i++)
          __dtab[0].ocldevinfo->platformid = __ptab;
#endif
}


static void __do_release_platforms()
{ 
#if 0
	if (__dtab) free(__dtab);
#endif
}


void __do_get_nplatforms_avail(cl_uint* n)
{
#if 0
    *n = __nplatforms;
#endif
}


void __do_get_platforms(cl_uint n, cl_platform_id* platformid)
{
#if 0
   int i;
   for(i=0;i<n;i++) platformid[i] = &__ptab[i];
#endif
}


void __do_get_default_platformid( cl_platform_id* platformid )
{
#if 0
    *platformid = &__ptab[0];
#endif
}

static void __do_get_platform_profile(cl_platform_id platformid, char** p_str)
{
#if 0
    *p_str = __resolve_platformid(platformid,profile);
#endif
}


static void __do_get_platform_version(cl_platform_id platformid, char** p_str)
{
#if 0
    *p_str = __resolve_platformid(platformid,version);
#endif
}


static void __do_get_platform_name(cl_platform_id platformid, char** p_str)
{
#if 0
    *p_str = __resolve_platformid(platformid,name);
#endif
}


static void __do_get_platform_vendor(cl_platform_id platformid, char** p_str)
{
#if 0
    *p_str = __resolve_platformid(platformid,vendor);
#endif
}


static void __do_get_platform_extensions(cl_platform_id platformid, char** p_str)
{
#if 0
    *p_str = __resolve_platformid(platformid,extensions);
#endif
}

static char __vendor_icd_ext_suffix[] = "\0";

static void __do_get_platform_icd_suffix_khr(
	cl_platform_id platformid, char** p_str)
{
#if 0
    *p_str = __vendor_icd_ext_suffix;
#endif
}

