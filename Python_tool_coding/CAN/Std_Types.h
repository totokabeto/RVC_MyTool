#ifndef STD_TYPES_H
#define STD_TYPES_H 

#include "Compiler.h" 
#include "Platform_Types.h" 

/*
 * AUTOSAR specification version information
 */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define STD_TYPES_AR_RELEASE_MINOR_VERSION     2
#define STD_TYPES_AR_RELEASE_REVISION_VERSION  2

/*
 * File version information
 */
#define STD_TYPES_SW_MAJOR_VERSION  1
#define STD_TYPES_SW_MINOR_VERSION  0
#define STD_TYPES_SW_PATCH_VERSION  0

/************************************************/

#ifndef STATUSTYPEDEFINED 
    #define STATUSTYPEDEFINED 
    #define E_OK 0U 
    typedef unsigned char StatusType; 
#endif 

typedef uint8 Std_ReturnType; 
#define E_NOT_OK 1U 

typedef struct
{
    uint16 vendorID; 
    uint16 moduleID; 
    uint8 sw_major_version; 
    uint8 sw_minor_version; 
    uint8 sw_patch_version;
} Std_VersionInfoType; 

#define STD_HIGH 1U 
#define STD_LOW 0U 

#define STD_ACTIVE 1U 
#define STD_IDLE 0U 

#define STD_ON 1U 
#define STD_OFF 0U 

#endif 
