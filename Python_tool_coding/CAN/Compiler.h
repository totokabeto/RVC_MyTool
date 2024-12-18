#include <stdio.h> 

#ifndef COMPILER_H
#define COMPILER_H 
#endif

#include "Compiler_Cfg.h"


#define COMPILER_AR_RELEASE_MAJOR_VERSION 4
#define COMPILER_AR_RELEASE_MINOR_VERSION 0 
#define COMPILER_AR_RELEASE_REVISION_VERSION 3

#define CANTATAAPP

#define COMPILER_AR_MAJOR_VERSION 2
#define COMPILER_AR_MINOR_VERSION 2
#define COMPILER_AR_PATCH_VERSION 0
#define COMPILER_SW_MAJOR_VERSION 1
#define COMPILER_SW_MINOR_VERSION 0
#define COMPILER_SW_PATCH_VERSION 0




#define INLINE inline
#define LOCAL_INLINE static inline 
#define STATIC static

#ifndef _GREENHILLS_C_RH850_
  #define _GREENHILLS_C_RH850_
#endif

#ifndef NULL_PTR
  #define NULL_PTR ((void *)0)
#endif 

#define AUTOMATIC
#define TYPEDEF

#define FUNC(rettype, memclass) memclass type

#define FUNC_P2CONST(rettype, ptrclass, memclass) const ptrclass rettype * memclass

#define FUNC_P2VAR(rettype, ptrclass, memclass) ptrclass rettype * memclass

#define P2VAR(ptrtype, memclass, ptrclass) ptrclass ptrtype * memclass

#define P2CONST(ptrtype, memclass, ptrclass) \
                const ptrclass ptrtype * memclass

#define CONSTP2VAR (ptrtype, memclass, ptrclass) ptrclass ptrtype * const memclass

#define CONSTP2CONST(ptrtype, memclass, ptrclass) const memclass ptrtype * const ptrclass

#define P2FUNC(rettype, ptrclass, fctname) ptrclass rettype (*fctname)

#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)

#define CONST(consttype, memclass) const consttype

#define VAR(vartype, memclass) vartype

#define ASM_HALT()

#define ASM_NOP()







