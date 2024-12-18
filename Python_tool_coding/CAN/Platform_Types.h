#ifndef PLATFORM_TYPES_H 
#define PLATFORM_TYPES_H 

#define PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define PLATFORM_TYPES_AR_RELEASE_MINOR_VERSION     0
#define PLATFORM_TYPES_AR_RELEASE_REVISION_VERSION  3

/* AUTOSAR specification version information as per R3.2.2 */
#define PLATFORM_TYPES_AR_MAJOR_VERSION  2
#define PLATFORM_TYPES_AR_MINOR_VERSION  3
#define PLATFORM_TYPES_AR_PATCH_VERSION  1

/* File version information */
#define PLATFORM_TYPES_SW_MAJOR_VERSION  1
#define PLATFORM_TYPES_SW_MINOR_VERSION  0
#define PLATFORM_TYPES_SW_PATCH_VERSION  0

/*******************************************************************************
**                      Global Symbols                                        **
********************************************************************************/
#define CPU_TYPE_8          8
#define CPU_TYPE_16         16 
#define CPU_TYPE_32         32

#define MSB_FIRST           0  /* Big endian bit ordering       */
#define LSB_FIRST           1   /* Little endian bit ordering    */

#define HIGH_BYTE_FIRST     0 
#define LOW_BYTE_FIRST      1

#define HIGH_WORD_FIRST     0 
#define LOW_WORD_FIRST      1 

#define CPU_TYPE    CPU_TYPE_32
#define CPU_BIT_ORDER   LSB_FIRST
#define CPU_BYTE_ORDER   LOW_BYTE_FIRST
#define CPU_WORD_ORDER   LOW_WORD_FIRST

#define MCAL_ISR_TYPE_TOOLCHAIN     1 
#define MCAL_ISR_TYPE_OS            2 
#define MCAL_ISR_TYPE_NONE          3 

typedef signed  char sint8; 
typedef unsigned char uint8; 
typedef signed short sint16; 
typedef unsigned short uint16; 
typedef signed long sint32; 
typedef unsigned long uint32; 
typedef float float32; 
typedef double float64; 

typedef unsigned long uint8_least; 
typedef unsigned long uint16_least; 
typedef unsigned long uint32_least; 
typedef signed long sint8_least; 
typedef signed long sint16_least; 
typedef signed long sint32_least; 
typedef unsigned char boolean; 

#ifndef TRUE
    #define TRUE       1u 
#endif 

#ifndef FALSE
    #define FALSE       0u 
#endif 

#endif 

