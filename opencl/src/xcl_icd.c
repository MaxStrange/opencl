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

/* DAR */


#include <CL/cl.h>

#include "xcl_structs.h"
#include "printcl.h"

#ifndef min
#define min(a,b) ((a<b)?a:b)
#endif


// ICD stuff 


cl_int 
clIcdGetPlatformIDsKHR( 
	cl_uint nplatforms, 
	cl_platform_id *platforms, 
	cl_uint *nplatforms_ret
)
{
    if (nplatforms == 0 && platforms !=NULL)
        return CL_INVALID_VALUE;
    else if (platforms == NULL && nplatforms_ret == NULL)
        return CL_INVALID_VALUE;
#if 0
    cl_uint nplatforms_avail;
    __do_discover_platforms();
    __do_get_nplatforms_avail(&nplatforms_avail);

    if (platforms != NULL)
        __do_get_platforms(nplatforms, platforms);

    if (nplatforms_ret != NULL)
        *nplatforms_ret = nplatforms;
#endif
    return CL_SUCCESS;
}


void*
clGetExtensionFunctionAddress( const char* funcname )
{
    if (funcname == NULL)
        return NULL;
    else if (!strcmp("clIcdGetPlatformIDsKHR", funcname))
        return &clIcdGetPlatformIDsKHR;
    else
        return NULL;
}


