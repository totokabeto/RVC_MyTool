
#include "Compiler.h"
#include "Compiler_Cfg.h"
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Can_Reg_Write.h"
/* AUTOSAR release version information */
#define CAN_C_AR_RELEASE_MAJOR_VERSION CAN_AR_RELEASE_MAJOR_VERSION
#define CAN_C_AR_RELEASE_MINOR_VERSION CAN_AR_RELEASE_MINOR_VERSION
#define CAN_C_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION

/* File version information */
#define CAN_C_SW_MAJOR_VERSION    CAN_SW_MAJOR_VERSION
#define CAN_C_SW_MINOR_VERSION    CAN_SW_MINOR_VERSION

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (CAN_C_AR_RELEASE_MAJOR_VERSION != CAN_AR_RELEASE_MAJOR_VERSION_VALUE)
  #error "Can.c : Mismatch in Release Major Version"
#endif
#if (CAN_C_AR_RELEASE_MINOR_VERSION != CAN_AR_RELEASE_MINOR_VERSION_VALUE)
  #error "Can.c : Mismatch in Release Minor Version"
#endif
#if (CAN_C_AR_RELEASE_REVISION_VERSION != CAN_AR_RELEASE_REVISION_VERSION_VALUE)
  #error "Can.c : Mismatch in Release Revision Version"
#endif

#if (CAN_C_SW_MAJOR_VERSION != CAN_SW_MAJOR_VERSION_VALUE)
  #error "Can.c : Mismatch in Software Major Version"
#endif
#if (CAN_C_SW_MINOR_VERSION != CAN_SW_MINOR_VERSION_VALUE)
  #error "Can.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
** Function Name         : Can_VerifyWriteReg
**
** Description           : This function is to check write verify.
**
** Input Parameters      : LpWriteRegAddr, LulRegWriteValue, LulMaskValue,
**                         LucApiId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : None
**
** Functions invoked     : None
*******************************************************************************/

#define CAN_RSCAN_START_SEC_PRIVATE_CODE

#include CAN_MEMMAP_FILE

#if(CAN_WRITE_VERIFY != CAN_WV_DISABLE)
static INLINE FUNC(void,CAN_RSCAN_START_SEC_PRIVATE_CODE)Can_VerifyWriteReg(
   CONSTP2CONST(volatile,uint32, AUTOMATIC,REFSPACE) LpWriteRegAddr,
   CONST(uint32, AUTOMATIC) LulRegWriteValue,
   CONST(uint32, AUTOMATIC) LulMaskValue,
   CONST(uint8, AUTOMATIC) LucApiId)
  {
    CAN_VERIFY_WRITE_REG(LpWriteRegAddr, LulRegWriteValue, LulMaskValue, LucApiId)
  }
 
#endif
#define CAN_RSCAN_STOP_SEC_PRIVATE_CODE

#include CAN_MEMMAP_FILE

#if (CAN_WRITE_VERIFY != CAN_WV_DISABLE)
    #define CAN_WRITE_VERIFY_INIT(pWriteRegAddr,\
                                 RegWriteValue, MaskValue,ApiID)\
            { \
                CAN_WRITE_REG_ONLY(pWriteRegAddr,RegWriteValue) \ 
                Can_VerifyWriteReg(pWriteRegAddr, RegWriteValue,MaskValue,ApiId); \
            }
    #define CAN_WRITE_VERIFY_MIRROR_INIT(pWriteRegAddr,\
                                        ReqgWriteValue, RegWriteValue, pMirrorAddr, MaskValue,ApiId)\
                                        {\
                                          CAN_WRITE_REG_ONLY(pWriteRegAddr,ReqWriteValue)\
                                          Can_VerifyWriteReq(pWriteAddr, ReqWriteValue, MaskValue, ApiId); \
                                          CAN_WRITE_RAM_MIRROR(pMirrorAddr, ReqWriteValue) \ 
                                        }
#else 
    #define CAN_WRITE_VERIFY_INIT(pWriteReqAddr, \
                                  ReqWriteValue, MaskValue, ApiId) \
                                  { \
                                      CAN_WRITE_REG_ONLY(pWriteReqAddr, ReqWriteValue) \ 
                                  } 
    #define CAN_WRITE_VERIFY_MIRROR_INIT(pWriteReqAddr, \ 
                                          ReqWriteValue, pMirrorAddr, MaskValue, ApiId ) \ 
                                          {\
                                            CAN_WRITE_REG_ONLY(pWriteReqAddr, ReqWriteValue) \ 
                                            CAN_WRITE_RAM_MIRROR(pMirrorAddr, ReqWriteVlaue)\ 
                                          }
#endif

#define CAN_RSCAN_START_SEC_PRIVATE_CODE


#include CAN_MEMMAP_FILE

