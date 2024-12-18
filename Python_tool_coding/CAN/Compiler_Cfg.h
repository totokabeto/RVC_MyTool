
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#define COMPILER_CFG_AR_RELEASE_MAJOR_VERSION     4
#define COMPILER_CFG_AR_RELEASE_MINOR_VERSION     0
#define COMPILER_CFG_AR_RELEASE_REVISION_VERSION  3

/* AUTOSAR specification version information as per R3.2.2 */
#define COMPILER_CFG_AR_MAJOR_VERSION  2
#define COMPILER_CFG_AR_MINOR_VERSION  2
#define COMPILER_CFG_AR_PATCH_VERSION  0
#define COMPILER_CFG_SW_MAJOR_VERSION  1
#define COMPILER_CFG_SW_MINOR_VERSION  0
#define COMPILER_CFG_SW_PATCH_VERSION  0


/* ---------------------------------------------------------------------------*/
/*                   CAN                                                      */
/* ---------------------------------------------------------------------------*/

#define CAN_RSCAN_PUBLIC_CODE          /* API functions                       */
#define CAN_RSCAN_PUBLIC_CONST         /* API constants                       */

#define CAN_RSCAN_PRIVATE_CODE         /* Internal functions                  */

#define CAN_RSCAN_PRIVATE_DATA         /* Module internal data                */
#define CAN_RSCAN_PRIVATE_CONST        /* Internal ROM Data                   */

#define CAN_RSCAN_APPL_CODE            /* callbacks of the Application        */
#define CAN_RSCAN_APPL_CONST           /* Applications' ROM Data              */
#define CAN_RSCAN_APPL_DATA            /* Applications' RAM Data              */
#define CAN_RSCAN_FAST_DATA            /* 'Near' RAM Data                     */

#define CAN_RSCAN_FAST_CODE            /* API functions                       */
#define CAN_RSCAN_FAST_CONST           /* API constants                       */

#define CAN_RSCAN_CONFIG_CONST         /* Desc. Tables -> Config-dependent    */
#define CAN_RSCAN_CONFIG_DATA          /* Config. dependent (reg. size) data  */

#define CAN_RSCAN_INIT_DATA            /* Data which is initialized during
                                          Startup                             */
#define CAN_RSCAN_NOINIT_DATA          /* Data which is not initialized during
                                          Startup                             */
#define CAN_RSCAN_CONST                /* Data Constants                      */
#define CAN_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define CAN_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */


/* ---------------------------------------------------------------------------*/
/*                   LIN                                                      */
/* ---------------------------------------------------------------------------*/

#define LIN_PUBLIC_CODE                /* API functions                       */
#define LIN_PUBLIC_CONST               /* API constants                       */

#define LIN_PRIVATE_CODE               /* Internal functions                  */

#define LIN_PRIVATE_DATA               /* Module internal data                */
#define LIN_PRIVATE_CONST              /* Internal ROM Data                   */

#define LIN_APPL_CODE                  /* callbacks of the Application        */
#define LIN_APPL_CONST                 /* Applications' ROM Data              */
#define LIN_APPL_DATA                  /* Applications' RAM Data              */
#define LIN_FAST_DATA                  /* 'Near' RAM Data                     */

#define LIN_FAST_CODE                   /* API functions                       */
#define LIN_FAST_CONST                  /* API constants                       */
#define LIN_FAST_DATA                   /* API constants                       */

#define LIN_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define LIN_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define LIN_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define LIN_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define LIN_CONST                      /* Data Constants                      */
#define LIN_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define LIN_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */
/* ---------------------------------------------------------------------------*/
/*                   ETH                                                      */
/* ---------------------------------------------------------------------------*/

#define ETH_59_PUBLIC_CODE                /* API functions                       */
#define ETH_59_PUBLIC_CONST               /* API constants                       */

#define ETH_59_PRIVATE_CODE               /* Internal functions                  */

#define ETH_59_PRIVATE_DATA               /* Module internal data                */
#define ETH_59_PRIVATE_CONST              /* Internal ROM Data                   */

#define ETH_59_APPL_CODE                  /* callbacks of the Application        */
#define ETH_59_APPL_CONST                 /* Applications' ROM Data              */
#define ETH_59_APPL_DATA                  /* Applications' RAM Data              */
#define ETH_59_FAST_DATA                  /* 'Near' RAM Data                     */

#define ETH_59_FAST_CODE                   /* API functions                       */
#define ETH_59_FAST_CONST                  /* API constants                       */
#define ETH_59_FAST_DATA                   /* API constants                       */

#define ETH_59_CONFIG_CONST               /* Desc. Tables -> Config-dependent    */
#define ETH_59_CONFIG_DATA                /* Config. dependent (reg. size) data  */

#define ETH_59_INIT_DATA                  /* Data which is initialized during
                                          Startup                             */
#define ETH_59_NOINIT_DATA                /* Data which is not initialized during
                                          Startup                             */
#define ETH_59_CONST                      /* Data Constants                      */
#define ETH_59_VAR                        /* Memory class for global variables   */
                                       /* which are initialized after every   */
                                       /* reset                               */
#define ETH_59_VAR_NOINIT                 /* Memory class for global variables   */
                                       /* which are initialized by driver     */


#endif 