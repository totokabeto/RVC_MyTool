 #ifndef CAN_REG_WRITE 
 #define CAN_REG_WRITE
 
 #define CAN_VERIFY_WRITE_REG(pWriteRegAddr, RegWriteValue, MaskValue, ApiId) \
  {\
  }


 #define CAN_WRITE_REG_ONLY(pWriteReqAddr, ReqWriteValue) \ 
 { \
    (*(pWriteReqAddr)) = (ReqWriteValue);\ 
 }

 #define CAN_WRITE_RAM_MIRROR(pMirrorAddr, RegWriteValue) \
{ \
}
#endif