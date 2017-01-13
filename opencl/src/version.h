#ifndef _VERSION_H
#define _VERSION_H


#define EOCL_PLATFORM_NAME          "eocl"
#define EOCL_PLATFORM_VENDOR        "Max Strange"
#define EOCL_PLATFORM_EXTENSIONS    "cl_khr_icd"
#define EOCL_PLATFORM_VERSION       "OpenCL 2.0"
#define EOCL_PLATFORM_PROFILE       "EMBEDDED_PROFILE"

#define EOCL_DEVICE_NAME            "epiphany coprocessor"
#define EOCL_DEVICE_VENDOR          "parallella"
#define EOCL_DRIVER_VERSION         "Version 0.1"
#define EOCL_DEVICE_PROFILE         "EMBEDDED_PROFILE"
#define EOCL_DEVICE_VERSION         "OpenCL 2.0"


#define COPRTHR_VERSION_CODE \
	((COPRTHR_VERSION<<16)|(COPRTHR_REVISION<<8)|(COPRTHR_RELEASE))


#define GPL3_NOTICE \
"This program is free software; you may redistribute it under the terms of\n"\
"the GNU General Public License version 3 (GPLv3). This program has\n"\
"absolutely no warranty.\n"


#endif


