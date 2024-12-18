/*============================================================================*/
/* Project      = AUTOSAR Renesas F1x MCAL Components                         */
/* Module       = Interrupt_VectorTable_F1KM.c                                */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c)   2017-2021 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains Interrupt Vector table for all MCAL modules.            */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        F1KM                                          */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * V1.0.0:  19-Jun-2017    : Initial Version
 * V1.0.1:  19-Jun-2017    : Interrupt VectorTable updated for LIN
 * V1.0.2:  22-Jun-2017    : Interrupt VectorTable updated for FR
 * V1.0.2:  23-Jun-2017    : Interrupt VectorTable updated for PWM
 * V1.0.3:  27-Jun-2017    : Interrupt VectorTable updated for GPT
 * V1.0.4:  28-Jun-2017    : Interrupt VectorTable updated for ADC
 * V1.0.5:  28-Jun-2017    : Interrupt VectorTable updated for ICU
 * V1.0.6:  28-Jun-2017    : Interrupt VectorTable updated for Fls
 * V1.0.7:  29-Jun-2017    : #ARDAABD-1938
 *                           1. Removed CANV2 IVT, single CAN IVT is correct
 * V1.0.8:  29-Jun-2017    : #ARDAABD -1938
 *                           1. Interrupt VectorTable updated for Cortst
 *
 * V1.2.0  07-Jul-2017:  #ARDAABD-1076
 *                       1. Add Can controller 7 IRQ handlers for F1KM-S4.
 *                       2. Added missing Can wakeup IRQs (channels 2->7).
 *                       3. Improved code style.
 * V1.2.1:  11-Jul-2017    : #ARDAABD-1726
 *                           1. Interrupt VectorTable updated for PWM-Diag
 * V1.2.2:  27-Jul-2017    : As part of F1K_F1KM Ver4.01.00_Ver42.01.00 few
 *                           changes are made,
 *                           1. ISR Definition and Vector table for WDG have
 *                              been modified and updated.
 * V1.2.3: 27-Jul-2017    : Interrupt VectorTable updated for Spi
 * V1.2.4: 07-Aug-2017    : Interrupt VectorTable updated for Mcu
 * V1.2.5: 07-Aug-2017    : Interrupt VectorTable updated for Adc and PWM
 * V1.2.6: 24-Aug-2017    : Interrupt 104 removed for MCU because is reserved
 * V1.2.7: 02-Oct-2017    : #ARDAABD-2489 Support is added for FLS DMA
 *                          interrupts of F1KM-S4 devices.
 * V1.2.8: 14-Jun-2018    : Following changes are amde:
 *                          1. Macro 'CAN_MAX_NUMBER_OF_HTH' condition check
 *                             is added inside CAN_CONTROLLERx_TX_ISR of CAN,
 *                             Ref: ARDAABD-2121.
 *                          2. Copyright information updated and committed.
 *                          3. External interrupt ISR are added as part of F1KM
 *                             automation for PWM module.
 *                          4. As part of JIRA ARDAABD-3831, Pre-compile switch
 *                             MCU_INTCWEND_ISR_ENABLE is added for
 *                             INTCWEND_ISR function.
 * V1.2.9: 27-Sep-2018    : 1.As part of ARDAABD-3992,added timer function
 *                            declaration for SPI module
 * V1.2.10: 30-Nov-2018   : 1.Add CSIH0/CSIG0 interrupt function in interrupt
 *                            vector table for F1KM-S4.
 * V1.2.11: 12-Jul-2019   : 1. Modify for CAN, FR, SPI re-design
 *                          2. Update Interrupt controller for OS mode
 * V1.2.12: 23-Nov-2021   : As part of ARDAABD-6342, the following changes
 *                          are made:
 *                          a) Added interrupt vector table of F1KM-S2 device.
 *                          b) Updated device variant name in 'Environment'.
 *                          c) Copyright information updated.
 */
/******************************************************************************/

/*****************************************************************************/
/*                Module Specific header file inclusions                     */
/*****************************************************************************/

#ifdef ADC_MODULE_TEST
#include "Adc.h"
#include "Adc_Irq.h"
#include "Adc_PBTypes.h"
#ifdef ADC_TEST_APP_CFG39
/* This is for the extern on the User Buffer Pointers*/
/* GddSetBuffGroup_CYCLIC, GddSetBuffGroup_CYCLIC_LP  */
#include "Adc_Defs_cfg39.h"
#endif
#ifdef ADC_TEST_APP_CFG41
/* This is for the extern on the User Buffer Pointers*/
/* GddSetBuffGroup_CYCLIC, GddSetBuffGroup_CYCLIC_LP  */
#include "Adc_Defs_cfg41.h"
#endif
#ifdef ADC_TEST_APP_CFG44
/* This is for the extern on the User Buffer Pointers*/
/* GddSetBuffGroup_CYCLIC, GddSetBuffGroup_CYCLIC_LP  */
#include "Adc_Defs_cfg44.h"
#endif
#ifdef ADC_TEST_APP_CFG45
/* This is for the extern on the User Buffer Pointers*/
/* GddSetBuffGroup_CYCLIC, GddSetBuffGroup_CYCLIC_LP  */
#include "Adc_Defs_cfg45.h"

#endif

#ifdef ADC_TEST_APP_CFG51
/* This is for the extern on the User Buffer Pointers*/
/* GddSetBuffGroup_CYCLIC, GddSetBuffGroup_CYCLIC_LP  */
#include "Adc_Defs_cfg51.h"

#endif

#ifdef ADC_TEST_APP_CFG61
/* This is for the extern on the User Buffer Pointers*/
/* GddSetBuffGroup_CYCLIC, GddSetBuffGroup_CYCLIC_LP  */
#include "Adc_Defs_cfg61.h"

#endif

#ifdef ADC_TEST_APP_CFG77
#include "Adc_Defs_cfg77.h"
#endif

#ifdef ADC_TEST_APP_CFG80
/* This is for the extern on the User Buffer Pointers*/
/* GddSetBuffGroup_CYCLIC, GddSetBuffGroup_CYCLIC_LP  */
#include "Adc_Defs_cfg80.h"

#endif

#ifdef ADC_TEST_APP_CFG81
/* This is for the extern on the User Buffer Pointers*/
/* GddSetBuffGroup_CYCLIC, GddSetBuffGroup_CYCLIC_LP  */
#include "Adc_Defs_cfg81.h"

#endif

#endif

#ifdef MCU_MODULE_TEST
#include "Mcu_Types.h"
#ifdef MCU_CANICUSTOP_INT
#include "mcu_cfg43_Device.h"
#endif
#if (MCU_LOW_POWER_SEQUENCER == STD_ON)
#ifdef MCU_CFG53_INT
/* MCU_CFG53_INT */
#include "mcu_cfg53_Device.h"
#endif
#include "Mcu_Irq.h"
/* (MCU_LOW_POWER_SEQUENCER == STD_ON) */
#endif
/* MCU_MODULE_TEST */
#endif

#ifdef PWM_MODULE_TEST
#include "Pwm.h"
#include "Pwm_Irq.h"

#ifdef PWM_TEST_APP
#include "INTP_Isr.h"
#endif
#endif

#ifdef ETH_MODULE_TEST
#include "Eth_59_Irq.h"
#endif

#ifdef GPT_MODULE_TEST
#include "Gpt.h"
#include "Gpt_Irq.h"
#endif

#ifdef ICU_MODULE_TEST
#include "Icu.h"
#include "Icu_Irq.h"
#include "Os.h"
#endif

#ifdef SPI_MODULE_TEST
#ifdef SPI_SAMPLE_TEST
#include "App_Spi_Common_Sample.h"
#endif
#ifdef SPI_TEST_APP
#include "Spi_Defs.h"
#include "Spi_Slave.h"
#endif
#include "Spi.h"
#include "Spi_Irq.h"
#include "Os.h"
#endif

#ifdef CAN_MODULE_TEST
#include "App_CAN_Device_Sample.h"
#include "Can.h"
#include "Can_Irq.h"
#endif

#ifdef FR_MODULE_TEST
#ifdef FR_SAMPLE_TEST
#include "App_Fr_Device_Sample.h"
#endif
#include "Fr_59_Renesas.h"
#ifdef FR_TEST_APP
#include "Fr_Defs_Device.h"
#endif
#endif

#ifdef LIN_MODULE_TEST
#include "Lin.h"
#include "Lin_Irq.h"
#ifdef LIN_SAMPLE_TEST
#include "App_Lin_Device_Sample.h"
#endif
#ifdef LIN_TEST_APP
#include "Lin_Def_cfg.h"
#endif
#endif

#ifdef FEE_MODULE_TEST
#ifdef FEE_SAMPLE_TEST
#include "App_Fee_Device_Sample.h"
#endif
#include "Fee.h"
#ifdef FEE_TEST_APP
#include "Common_App.h"
#endif
#endif

#ifdef MCU_TIMER_INT
#include "mcu_Common_Device.h"
#endif

#ifdef WDG_SAMPLE_TEST
    #include "Wdg_59_DriverA_Irq.h"
    #include "Wdg_59_DriverB_Irq.h"
#endif

#ifdef WDG_MODULE_TEST
  #ifdef WDG_DRIVER_A
    #include "Wdg_59_DriverA_Irq.h"
  #endif

  #ifdef WDG_DRIVER_B
    #include "Wdg_59_DriverB_Irq.h"
  #endif

  #ifdef WDG_DRIVER_AB
    #include "Wdg_59_DriverA_Irq.h"
    #include "Wdg_59_DriverB_Irq.h"
  #endif
#endif

#ifdef CORTST_MODULE_TEST
  #ifdef CORTST_SAMPLE_TEST
    #ifdef F1K
      #include "App_CorTst_F1K_Sample.h"
    #elif F1KM
      #include "App_CorTst_F1KM_Sample.h"
    #else
      #error "Used device is not F1K or F1KM, abort. Please check build system."
    #endif
  #endif
  #ifdef CORTST_TEST_APP
    #include "Common_App_Device.h"
  #endif
#include "CorTst.h"
#endif

#ifdef FLS_MODULE_TEST
#include "Fls.h"
#include "Fls_Irq.h"
#include "Fls_Cfg.h"
#include "Os.h"
#endif

#ifdef GLOBAL_MODULE_TEST
#include "Pwm.h"
#include "Pwm_Irq.h"
#include "Adc.h"
#include "Adc_Irq.h"
#include "Adc_PBTypes.h"
#endif

/* Set the linker to place in the opportune location (Deafult=0x200)  */
/*****************************************************************************/
/*                         ISR Definition                                    */
/*****************************************************************************/

#define DUMMY(ivtNumber) Dummy_ISR

#pragma ghs interrupt
__interrupt void Dummy_ISR(void)
{
  ;
}

#ifdef ADC_MODULE_TEST
#ifdef ADC_TEST_APP_CFG39


volatile uint8 CntIamHere_ch7;
volatile uint8 CntIamHere_ch15;
volatile uint8 CntIamHere_ch03;

Std_ReturnType GddReadGroup_Cyclic;
Std_ReturnType GddReadGroup_Cyclic_LP;

volatile boolean Adc_Group_Cyclic_Start=FALSE;

#pragma ghs interrupt
__interrupt void TAUD0_CH7_Isr(void) /* Adc_Timer_0, */
{

 CntIamHere_ch7++;

#if 1
 /*  ADC_GROUP_CYCLIC */
 if (Adc_Group_Cyclic_Start==TRUE)
 {
   Adc_StartGroupConversion(Adc_ADC_GROUP_CYCLIC);
   Adc_Group_Cyclic_Start=FALSE;
 }

  if (GucNotifCounter[1]>0)
  {
    /* Notification  Occurred */
  /*Read results  */
  GddReadGroup_Cyclic = Adc_ReadGroup(Adc_ADC_GROUP_CYCLIC, GddSetBuffGroup_CYCLIC);
  }
#endif

}


#pragma ghs interrupt
__interrupt void TAUD0_CH15_Isr(void)  /* Adc_Timer_1 */
{

 CntIamHere_ch15++;

}


__interrupt void TAUJ0_CH03_Isr(void)
{
 CntIamHere_ch03++;


}


#endif   /* When the test application is cfg39 */
#endif  /* Only For Adc */



/*****************************************************************************/
/*****************************************************************************/
/*                         F1KM-S1 IVT                                       */
/*****************************************************************************/
/*****************************************************************************/
#ifdef F1KM_S1_DEVICE
#pragma ghs section sdata=".inttable"

/*****************************************************************************/
/*                         ADC F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef ADC_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  /*018*/
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG1_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG1_CAT2_ISR) || defined (ADC0_SG1_CAT2_ISR)
        App_Os_ADC0_SG1_ISR,
      #else
        ADC0_SG1_ISR,
      #endif
    #else
      DUMMY(018),
    #endif /* #if (ADC0_SG1_ISR_API == STD_ON) */
  #else
    DUMMY(018),
  #endif
  /* 019 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG2_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG2_CAT2_ISR) || defined (ADC0_SG2_CAT2_ISR)
        App_Os_ADC0_SG2_ISR,
      #else
        ADC0_SG2_ISR,
      #endif
    #else
      DUMMY(019),
    #endif
  #else
    DUMMY(019),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
  /* 020 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG3_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG3_CAT2_ISR) || defined (ADC0_SG3_CAT2_ISR)
        App_Os_ADC0_SG3_ISR,
      #else
        ADC0_SG3_ISR,
      #endif
    #else
      DUMMY(020),
    #endif /* #if (ADC0_SG3_ISR_API == STD_ON) */
  #else
    DUMMY(020),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050),

  /*051*/
  #if defined ADC_TEST_APP_CFG41
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG51
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG44
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG45
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG39
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG61
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG77
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG80
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG81
    TAUD0_CH7_Isr,
  #else
    DUMMY(051),
  #endif

  DUMMY(052), DUMMY(053),DUMMY(054),

  /*055*/
  #if defined ADC_TEST_APP_CFG80
    TAUD0_CH15_Isr,
  #elif defined ADC_TEST_APP_CFG81
    TAUD0_CH15_Isr,
  #else
  DUMMY(055),/* Adc_Timer_1, */
  #endif
  /*056 */
  /* ADC_0 Error Interrupt */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC_ERROR_SUPPORT == STD_ON)
      #if defined (Os_ADC0_ERR_CAT2_ISR) || defined (ADC0_ERR_CAT2_ISR)
        App_Os_ADC0_ERR_ISR,
      #else
        ADC0_ERR_ISR,
      #endif
    #else
      DUMMY(056),
    #endif /*#if (ADC_ERROR_SUPPORT == STD_ON)*/
  #else
    DUMMY(056),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(057), DUMMY(058), DUMMY(059),

/* 60 */
  #if (ADC_DMA_ISR_CH00_API == STD_ON)
    #if defined (OS_ADC_DMA_CH00_CAT2_ISR) || defined (ADC_DMA_CH00_CAT2_ISR)
      App_Os_ADC_DMA_CH00_ISR,
    #else
      ADC_DMA_CH00_ISR,
    #endif
  #else
    DUMMY(060),
  #endif
/* 61 */
  #if (ADC_DMA_ISR_CH01_API == STD_ON)
    ADC_DMA_CH01_ISR,
  #else
   DUMMY(061),
  #endif
/* 62 */
  #if (ADC_DMA_ISR_CH02_API == STD_ON)
    ADC_DMA_CH02_ISR,
  #else
    DUMMY(062),
  #endif
/* 63 */
  #if (ADC_DMA_ISR_CH03_API == STD_ON)
    ADC_DMA_CH03_ISR,
  #else
   DUMMY(063),
  #endif
/* 64 */
  #if (ADC_DMA_ISR_CH04_API == STD_ON)
    ADC_DMA_CH04_ISR,
  #else
    DUMMY(064),
  #endif
/* 65 */
  #if (ADC_DMA_ISR_CH05_API == STD_ON)
    ADC_DMA_CH05_ISR,
  #else
    DUMMY(065),
  #endif
/* 66 */
  #if (ADC_DMA_ISR_CH06_API == STD_ON)
    ADC_DMA_CH06_ISR,
  #else
    DUMMY(066),
  #endif
/* 67 */
  #if (ADC_DMA_ISR_CH07_API == STD_ON)
    ADC_DMA_CH07_ISR,
  #else
    DUMMY(067),
  #endif
/* 68 */
  #if (ADC_DMA_ISR_CH08_API == STD_ON)
    ADC_DMA_CH08_ISR,
  #else
    DUMMY(068),
  #endif
/* 69 */
  #if (ADC_DMA_ISR_CH04_API == STD_ON)
    ADC_DMA_CH09_ISR,
  #else
   DUMMY(069),
  #endif
/* 70 */
  #if (ADC_DMA_ISR_CH10_API == STD_ON)
    ADC_DMA_CH10_ISR,
  #else
    DUMMY(070),
  #endif
/* 71 */
  #if (ADC_DMA_ISR_CH11_API == STD_ON)
    ADC_DMA_CH11_ISR,
  #else
    DUMMY(071),
  #endif
/* 72 */
  #if (ADC_DMA_ISR_CH12_API == STD_ON)
    ADC_DMA_CH12_ISR,
  #else
    DUMMY(072),
  #endif
/* 73 */
  #if (ADC_DMA_ISR_CH13_API == STD_ON)
    ADC_DMA_CH13_ISR,
  #else
    DUMMY(073),
  #endif
/* 74 */
  #if (ADC_DMA_ISR_CH14_API == STD_ON)
    ADC_DMA_CH14_ISR,
  #else
    DUMMY(074),
  #endif
/* 75 */
  #if (ADC_DMA_ISR_CH15_API == STD_ON)
    ADC_DMA_CH15_ISR,
  #else
    DUMMY(075),
  #endif


  DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082),

/* 83 */ /* Adc_Timer_1, */
  #if defined ADC_TEST_APP_CFG39
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG61
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG77
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG80
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG81
    TAUJ0_CH03_Isr,
  #else
    DUMMY(083), /* Adc_Timer_1, */
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090),

/* 91 */
  #if (ADC_PWSA_INT_QFULL_ISR == STD_ON)
    PWSA_QUE_ISR,
  #else
  DUMMY(091),
  #endif
  /*92*/
  DUMMY(092),



  DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211),

/* 212 */
  /* ADC_1 Error Interrupt */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC_ERROR_SUPPORT == STD_ON)
      #if defined (Os_ADC1_ERR_CAT2_ISR) || defined (ADC1_ERR_CAT2_ISR)
        App_Os_ADC1_ERR_ISR,
      #else
        ADC1_ERR_ISR,
      #endif
    #else
      DUMMY(212),
    #endif /*#if (ADC_ERROR_SUPPORT == STD_ON)*/
  #else
    DUMMY(212),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
/* 213 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC1_SG1_ISR_API == STD_ON)
      #if defined (Os_ADC1_SG1_CAT2_ISR) || defined (ADC1_SG1_CAT2_ISR)
         App_Os_ADC1_SG1_ISR,
      #else
         ADC1_SG1_ISR,
      #endif
    #else
      DUMMY(213),
    #endif
  #else
    DUMMY(213),
  #endif
/* 214 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC1_SG2_ISR_API == STD_ON)
      #if defined (Os_ADC1_SG2_CAT2_ISR) || defined (ADC1_SG2_CAT2_ISR)
        App_Os_ADC1_SG2_ISR,
      #else
        ADC1_SG2_ISR,
      #endif
    #else
      DUMMY(214),
    #endif
  #else
    DUMMY(214),
  #endif
/* 215 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC1_SG3_ISR_API == STD_ON)
      #if defined (Os_ADC1_SG3_CAT2_ISR) || defined (ADC1_SG3_CAT2_ISR)
        App_Os_ADC1_SG3_ISR,
      #else
        ADC1_SG3_ISR,
      #endif
    #else
      DUMMY(215),
    #endif
  #else
    DUMMY(215),
  #endif

  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef ADC_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         CAN F1KM-S1 IVT                                   */
/*****************************************************************************/
#if defined (CAN_MODULE_TEST) && (CAN_ISR_CATEGORY_2 == STD_OFF)
#define INT_VECTOR_051 Timer0_Interrupt
#if (CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON)
#ifndef Os_CAN_RSCAN0_RXFIFO_CAT2_ISR
#define INT_VECTOR_023 CAN_RSCAN0_RXFIFO_ISR /* 023 */
#else
#define INT_VECTOR_023 App_Os_CONTROLLER_RXFIFO0_ISR /* 023 */
#endif
#endif
#if (CAN_CONTROLLER0_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER0_BUSOFF_CAT2_ISR
#define INT_VECTOR_024  CAN_CONTROLLER0_BUSOFF_ISR /* 024 */
#else
#define INT_VECTOR_024 App_Os_CONTROLLER0_BUSOFF_ISR /* 024 */
#endif
#endif
#if (CAN_CONTROLLER0_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER0_RX_CAT2_ISR
#define INT_VECTOR_025  CAN_CONTROLLER0_RX_ISR /* 025 */
#else
#define INT_VECTOR_025 App_Os_CONTROLLER0_RX_ISR /* 025 */
#endif
#endif
#if (CAN_CONTROLLER0_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER0_TX_CAT2_ISR
#define INT_VECTOR_026  CAN_CONTROLLER0_TX_ISR /* 026 */
#else
#define INT_VECTOR_026 App_Os_CONTROLLER0_TX_ISR /* 026 */
#endif
#endif
#if ((CAN_CONTROLLER0_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER0_WAKEUP_CAT2_ISR
#define INT_VECTOR_037  CAN_CONTROLLER0_WAKEUP_ISR /* 037 */
#else
#define INT_VECTOR_037 App_Os_WAKEUP0_ISR /* 037 */
#endif
#endif
#if (CAN_CONTROLLER1_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER1_BUSOFF_CAT2_ISR
#define INT_VECTOR_113  CAN_CONTROLLER1_BUSOFF_ISR /* 113 */
#else
#define INT_VECTOR_113 App_Os_CONTROLLER1_BUSOFF_ISR /* 113 */
#endif
#endif
#if (CAN_CONTROLLER1_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER1_RX_CAT2_ISR
#define INT_VECTOR_114  CAN_CONTROLLER1_RX_ISR /* 114 */
#else
#define INT_VECTOR_114 App_Os_CONTROLLER1_RX_ISR /* 114 */
#endif
#endif
#if (CAN_CONTROLLER1_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER1_TX_CAT2_ISR
#define INT_VECTOR_115  CAN_CONTROLLER1_TX_ISR /* 115 */
#else
#define INT_VECTOR_115 App_Os_CONTROLLER1_TX_ISR /* 115 */
#endif
#endif
#if ((CAN_CONTROLLER1_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER1_WAKEUP_CAT2_ISR
#define INT_VECTOR_038  CAN_CONTROLLER1_WAKEUP_ISR /* 038 */
#else
#define INT_VECTOR_038 App_Os_WAKEUP1_ISR /* 038 */
#endif
#endif
#if (CAN_CONTROLLER2_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER2_BUSOFF_CAT2_ISR
#define INT_VECTOR_217  CAN_CONTROLLER2_BUSOFF_ISR /* 217 */
#else
#define INT_VECTOR_217  App_Os_CONTROLLER2_BUSOFF_ISR /* 217 */
#endif
#endif
#if (CAN_CONTROLLER2_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER2_RX_CAT2_ISR
#define INT_VECTOR_218  CAN_CONTROLLER2_RX_ISR /* 218 */
#else
#define INT_VECTOR_218  App_Os_CONTROLLER2_RX_ISR /* 218 */
#endif
#endif
#if (CAN_CONTROLLER2_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER2_TX_CAT2_ISR
#define INT_VECTOR_219  CAN_CONTROLLER2_TX_ISR /* 219 */
#else
#define INT_VECTOR_219  App_Os_CONTROLLER2_TX_ISR /* 219 */
#endif
#endif
#if ((CAN_CONTROLLER2_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER2_WAKEUP_CAT2_ISR
#define INT_VECTOR_039  CAN_CONTROLLER2_WAKEUP_ISR /* 039 */
#else
#define INT_VECTOR_039  App_Os_WAKEUP2_ISR /* 039 */
#endif
#endif
#if (CAN_CONTROLLER3_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER3_BUSOFF_CAT2_ISR
#define INT_VECTOR_220  CAN_CONTROLLER3_BUSOFF_ISR /* 220 */
#else
#define INT_VECTOR_220  App_Os_CONTROLLER3_BUSOFF_ISR /* 220 */
#endif
#endif
#if (CAN_CONTROLLER3_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER3_RX_CAT2_ISR
#define INT_VECTOR_221  CAN_CONTROLLER3_RX_ISR /* 221 */
#else
#define INT_VECTOR_221  App_Os_CONTROLLER3_RX_ISR /* 221 */
#endif
#endif
#if (CAN_CONTROLLER3_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER3_TX_CAT2_ISR
#define INT_VECTOR_222  CAN_CONTROLLER3_TX_ISR /* 222 */
#else
#define INT_VECTOR_222  App_Os_CONTROLLER3_TX_ISR /* 222 */
#endif
#endif
#if ((CAN_CONTROLLER3_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER3_WAKEUP_CAT2_ISR
#define INT_VECTOR_043  CAN_CONTROLLER3_WAKEUP_ISR /* 043 */
#else
#define INT_VECTOR_043  App_Os_WAKEUP3_ISR /* 043 */
#endif
#endif
#if (CAN_CONTROLLER4_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER4_BUSOFF_CAT2_ISR
#define INT_VECTOR_272  CAN_CONTROLLER4_BUSOFF_ISR /* 272 */
#else
#define INT_VECTOR_272  App_Os_CONTROLLER4_BUSOFF_ISR /* 272 */
#endif
#endif
#if (CAN_CONTROLLER4_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER4_RX_CAT2_ISR
#define INT_VECTOR_273  CAN_CONTROLLER4_RX_ISR /* 273 */
#else
#define INT_VECTOR_273  App_Os_CONTROLLER4_RX_ISR /* 273 */
#endif
#endif
#if (CAN_CONTROLLER4_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER4_TX_CAT2_ISR
#define INT_VECTOR_274  CAN_CONTROLLER4_TX_ISR /* 274 */
#else
#define INT_VECTOR_274  App_Os_CONTROLLER4_TX_ISR /* 274 */
#endif
#endif
#if ((CAN_CONTROLLER4_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER4_WAKEUP_CAT2_ISR
#define INT_VECTOR_044  CAN_CONTROLLER4_WAKEUP_ISR /* 044 */
#else
#define INT_VECTOR_044  App_Os_WAKEUP4_ISR /* 044 */
#endif
#endif
#if (CAN_CONTROLLER5_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER5_BUSOFF_CAT2_ISR
#define INT_VECTOR_287  CAN_CONTROLLER5_BUSOFF_ISR /* 287 */
#else
#define INT_VECTOR_287  App_Os_CONTROLLER5_BUSOFF_ISR /* 287 */
#endif
#endif
#if (CAN_CONTROLLER5_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER5_RX_CAT2_ISR
#define INT_VECTOR_288  CAN_CONTROLLER5_RX_ISR /* 288 */
#else
#define INT_VECTOR_288  App_Os_CONTROLLER5_RX_ISR /* 288 */
#endif
#endif
#if (CAN_CONTROLLER5_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER5_TX_CAT2_ISR
#define INT_VECTOR_289  CAN_CONTROLLER5_TX_ISR /* 289 */
#else
#define INT_VECTOR_289  App_Os_CONTROLLER5_TX_ISR /* 289 */
#endif
#endif
#if ((CAN_CONTROLLER5_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER5_WAKEUP_CAT2_ISR
#define INT_VECTOR_045  CAN_CONTROLLER5_WAKEUP_ISR /* 045 */
#else
#define INT_VECTOR_045  App_Os_WAKEUP5_ISR /* 045 */
#endif
#endif
#if (CAN_CONTROLLER6_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER6_BUSOFF_CAT2_ISR
#define INT_VECTOR_321  CAN_CONTROLLER6_BUSOFF_ISR /* 321 */
#else
#define INT_VECTOR_321  App_Os_CONTROLLER6_BUSOFF_ISR /* 321 */
#endif
#endif
#if (CAN_CONTROLLER6_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER6_RX_CAT2_ISR
#define INT_VECTOR_322  CAN_CONTROLLER6_RX_ISR /* 322 */
#else
#define INT_VECTOR_322  App_Os_CONTROLLER6_RX_ISR /* 322 */
#endif
#endif
#if (CAN_CONTROLLER6_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER6_TX_CAT2_ISR
#define INT_VECTOR_323  CAN_CONTROLLER6_TX_ISR /* 323 */
#else
#define INT_VECTOR_323  App_Os_CONTROLLER6_TX_ISR /* 323 */
#endif
#endif
#if ((CAN_CONTROLLER6_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER6_WAKEUP_CAT2_ISR
#define INT_VECTOR_128  CAN_CONTROLLER6_WAKEUP_ISR /* 128 */
#else
#define INT_VECTOR_128  App_Os_WAKEUP6_ISR /* 128 */
#endif
#endif
#if (CAN_CONTROLLER7_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER7_BUSOFF_CAT2_ISR
#define INT_VECTOR_332  CAN_CONTROLLER7_BUSOFF_ISR /* 332 */
#else
#define INT_VECTOR_332  App_Os_CONTROLLER7_BUSOFF_ISR /* 332 */
#endif
#endif
#if (CAN_CONTROLLER7_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER7_RX_CAT2_ISR
#define INT_VECTOR_333  CAN_CONTROLLER7_RX_ISR /* 333 */
#else
#define INT_VECTOR_333  App_Os_CONTROLLER7_RX_ISR /* 333 */
#endif
#endif
#if (CAN_CONTROLLER7_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER7_TX_CAT2_ISR
#define INT_VECTOR_334  CAN_CONTROLLER7_TX_ISR /* 334 */
#else
#define INT_VECTOR_334  App_Os_CONTROLLER7_TX_ISR /* 334 */
#endif
#endif
#if ((CAN_CONTROLLER7_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER7_WAKEUP_CAT2_ISR
#define INT_VECTOR_205  CAN_CONTROLLER7_WAKEUP_ISR /* 205 */
#else
#define INT_VECTOR_205  App_Os_WAKEUP7_ISR /* 205 */
#endif
#endif

/*****************************************************************************/
/*                         Interrupt Vector Table                            */
/*****************************************************************************/
#pragma ghs section sdata=".inttable"
void (*IntVectors[])(void) = {
#ifdef INT_VECTOR_000
  INT_VECTOR_000, /* 000 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_001
  INT_VECTOR_001, /* 001 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_002
  INT_VECTOR_002, /* 002 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_003
  INT_VECTOR_003, /* 003 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_004
  INT_VECTOR_004, /* 004 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_005
  INT_VECTOR_005, /* 005 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_006
  INT_VECTOR_006, /* 006 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_007
  INT_VECTOR_007, /* 007 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_008
  INT_VECTOR_008, /* 008 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_009
  INT_VECTOR_009, /* 009 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_010
  INT_VECTOR_010, /* 010 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_011
  INT_VECTOR_011, /* 011 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_012
  INT_VECTOR_012, /* 012 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_013
  INT_VECTOR_013, /* 013 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_014
  INT_VECTOR_014, /* 014 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_015
  INT_VECTOR_015, /* 015 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_016
  INT_VECTOR_016, /* 016 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_017
  INT_VECTOR_017, /* 017 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_018
  INT_VECTOR_018, /* 018 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_019
  INT_VECTOR_019, /* 019 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_020
  INT_VECTOR_020, /* 020 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_021
  INT_VECTOR_021, /* 021 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_022
  INT_VECTOR_022, /* 022 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_023
  INT_VECTOR_023, /* 023 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_024
  INT_VECTOR_024, /* 024 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_025
  INT_VECTOR_025, /* 025 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_026
  INT_VECTOR_026, /* 026 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_027
  INT_VECTOR_027, /* 027 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_028
  INT_VECTOR_028, /* 028 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_029
  INT_VECTOR_029, /* 029 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_030
  INT_VECTOR_030, /* 030 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_031
  INT_VECTOR_031, /* 031 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_032
  INT_VECTOR_032, /* 032 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_033
  INT_VECTOR_033, /* 033 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_034
  INT_VECTOR_034, /* 034 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_035
  INT_VECTOR_035, /* 035 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_036
  INT_VECTOR_036, /* 036 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_037
  INT_VECTOR_037, /* 037 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_038
  INT_VECTOR_038, /* 038 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_039
  INT_VECTOR_039, /* 039 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_040
  INT_VECTOR_040, /* 040 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_041
  INT_VECTOR_041, /* 041 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_042
  INT_VECTOR_042, /* 042 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_043
  INT_VECTOR_043, /* 043 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_044
  INT_VECTOR_044, /* 044 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_045
  INT_VECTOR_045, /* 045 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_046
  INT_VECTOR_046, /* 046 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_047
  INT_VECTOR_047, /* 047 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_048
  INT_VECTOR_048, /* 048 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_049
  INT_VECTOR_049, /* 049 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_050
  INT_VECTOR_050, /* 050 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_051
  INT_VECTOR_051, /* 051 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_052
  INT_VECTOR_052, /* 052 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_053
  INT_VECTOR_053, /* 053 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_054
  INT_VECTOR_054, /* 054 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_055
  INT_VECTOR_055, /* 055 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_056
  INT_VECTOR_056, /* 056 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_057
  INT_VECTOR_057, /* 057 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_058
  INT_VECTOR_058, /* 058 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_059
  INT_VECTOR_059, /* 059 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_060
  INT_VECTOR_060, /* 060 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_061
  INT_VECTOR_061, /* 061 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_062
  INT_VECTOR_062, /* 062 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_063
  INT_VECTOR_063, /* 063 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_064
  INT_VECTOR_064, /* 064 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_065
  INT_VECTOR_065, /* 065 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_066
  INT_VECTOR_066, /* 066 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_067
  INT_VECTOR_067, /* 067 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_068
  INT_VECTOR_068, /* 068 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_069
  INT_VECTOR_069, /* 069 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_070
  INT_VECTOR_070, /* 070 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_071
  INT_VECTOR_071, /* 071 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_072
  INT_VECTOR_072, /* 072 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_073
  INT_VECTOR_073, /* 073 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_074
  INT_VECTOR_074, /* 074 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_075
  INT_VECTOR_075, /* 075 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_076
  INT_VECTOR_076, /* 076 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_077
  INT_VECTOR_077, /* 077 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_078
  INT_VECTOR_078, /* 078 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_079
  INT_VECTOR_079, /* 079 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_080
  INT_VECTOR_080, /* 080 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_081
  INT_VECTOR_081, /* 081 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_082
  INT_VECTOR_082, /* 082 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_083
  INT_VECTOR_083, /* 083 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_084
  INT_VECTOR_084, /* 084 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_085
  INT_VECTOR_085, /* 085 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_086
  INT_VECTOR_086, /* 086 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_087
  INT_VECTOR_087, /* 087 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_088
  INT_VECTOR_088, /* 088 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_089
  INT_VECTOR_089, /* 089 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_090
  INT_VECTOR_090, /* 090 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_091
  INT_VECTOR_091, /* 091 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_092
  INT_VECTOR_092, /* 092 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_093
  INT_VECTOR_093, /* 093 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_094
  INT_VECTOR_094, /* 094 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_095
  INT_VECTOR_095, /* 095 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_096
  INT_VECTOR_096, /* 096 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_097
  INT_VECTOR_097, /* 097 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_098
  INT_VECTOR_098, /* 098 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_099
  INT_VECTOR_099, /* 099 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_100
  INT_VECTOR_100, /* 100 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_101
  INT_VECTOR_101, /* 101 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_102
  INT_VECTOR_102, /* 102 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_103
  INT_VECTOR_103, /* 103 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_104
  INT_VECTOR_104, /* 104 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_105
  INT_VECTOR_105, /* 105 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_106
  INT_VECTOR_106, /* 106 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_107
  INT_VECTOR_107, /* 107 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_108
  INT_VECTOR_108, /* 108 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_109
  INT_VECTOR_109, /* 109 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_110
  INT_VECTOR_110, /* 110 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_111
  INT_VECTOR_111, /* 111 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_112
  INT_VECTOR_112, /* 112 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_113
  INT_VECTOR_113, /* 113 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_114
  INT_VECTOR_114, /* 114 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_115
  INT_VECTOR_115, /* 115 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_116
  INT_VECTOR_116, /* 116 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_117
  INT_VECTOR_117, /* 117 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_118
  INT_VECTOR_118, /* 118 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_119
  INT_VECTOR_119, /* 119 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_120
  INT_VECTOR_120, /* 120 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_121
  INT_VECTOR_121, /* 121 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_122
  INT_VECTOR_122, /* 122 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_123
  INT_VECTOR_123, /* 123 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_124
  INT_VECTOR_124, /* 124 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_125
  INT_VECTOR_125, /* 125 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_126
  INT_VECTOR_126, /* 126 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_127
  INT_VECTOR_127, /* 127 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_128
  INT_VECTOR_128, /* 128 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_129
  INT_VECTOR_129, /* 129 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_130
  INT_VECTOR_130, /* 130 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_131
  INT_VECTOR_131, /* 131 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_132
  INT_VECTOR_132, /* 132 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_133
  INT_VECTOR_133, /* 133 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_134
  INT_VECTOR_134, /* 134 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_135
  INT_VECTOR_135, /* 135 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_136
  INT_VECTOR_136, /* 136 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_137
  INT_VECTOR_137, /* 137 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_138
  INT_VECTOR_138, /* 138 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_139
  INT_VECTOR_139, /* 139 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_140
  INT_VECTOR_140, /* 140 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_141
  INT_VECTOR_141, /* 141 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_142
  INT_VECTOR_142, /* 142 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_143
  INT_VECTOR_143, /* 143 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_144
  INT_VECTOR_144, /* 144 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_145
  INT_VECTOR_145, /* 145 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_146
  INT_VECTOR_146, /* 146 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_147
  INT_VECTOR_147, /* 147 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_148
  INT_VECTOR_148, /* 148 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_149
  INT_VECTOR_149, /* 149 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_150
  INT_VECTOR_150, /* 150 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_151
  INT_VECTOR_151, /* 151 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_152
  INT_VECTOR_152, /* 152 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_153
  INT_VECTOR_153, /* 153 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_154
  INT_VECTOR_154, /* 154 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_155
  INT_VECTOR_155, /* 155 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_156
  INT_VECTOR_156, /* 156 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_157
  INT_VECTOR_157, /* 157 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_158
  INT_VECTOR_158, /* 158 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_159
  INT_VECTOR_159, /* 159 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_160
  INT_VECTOR_160, /* 160 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_161
  INT_VECTOR_161, /* 161 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_162
  INT_VECTOR_162, /* 162 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_163
  INT_VECTOR_163, /* 163 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_164
  INT_VECTOR_164, /* 164 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_165
  INT_VECTOR_165, /* 165 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_166
  INT_VECTOR_166, /* 166 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_167
  INT_VECTOR_167, /* 167 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_168
  INT_VECTOR_168, /* 168 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_169
  INT_VECTOR_169, /* 169 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_170
  INT_VECTOR_170, /* 170 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_171
  INT_VECTOR_171, /* 171 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_172
  INT_VECTOR_172, /* 172 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_173
  INT_VECTOR_173, /* 173 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_174
  INT_VECTOR_174, /* 174 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_175
  INT_VECTOR_175, /* 175 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_176
  INT_VECTOR_176, /* 176 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_177
  INT_VECTOR_177, /* 177 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_178
  INT_VECTOR_178, /* 178 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_179
  INT_VECTOR_179, /* 179 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_180
  INT_VECTOR_180, /* 180 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_181
  INT_VECTOR_181, /* 181 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_182
  INT_VECTOR_182, /* 182 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_183
  INT_VECTOR_183, /* 183 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_184
  INT_VECTOR_184, /* 184 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_185
  INT_VECTOR_185, /* 185 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_186
  INT_VECTOR_186, /* 186 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_187
  INT_VECTOR_187, /* 187 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_188
  INT_VECTOR_188, /* 188 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_189
  INT_VECTOR_189, /* 189 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_190
  INT_VECTOR_190, /* 190 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_191
  INT_VECTOR_191, /* 191 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_192
  INT_VECTOR_192, /* 192 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_193
  INT_VECTOR_193, /* 193 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_194
  INT_VECTOR_194, /* 194 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_195
  INT_VECTOR_195, /* 195 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_196
  INT_VECTOR_196, /* 196 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_197
  INT_VECTOR_197, /* 197 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_198
  INT_VECTOR_198, /* 198 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_199
  INT_VECTOR_199, /* 199 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_200
  INT_VECTOR_200, /* 200 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_201
  INT_VECTOR_201, /* 201 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_202
  INT_VECTOR_202, /* 202 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_203
  INT_VECTOR_203, /* 203 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_204
  INT_VECTOR_204, /* 204 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_205
  INT_VECTOR_205, /* 205 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_206
  INT_VECTOR_206, /* 206 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_207
  INT_VECTOR_207, /* 207 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_208
  INT_VECTOR_208, /* 208 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_209
  INT_VECTOR_209, /* 209 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_210
  INT_VECTOR_210, /* 210 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_211
  INT_VECTOR_211, /* 211 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_212
  INT_VECTOR_212, /* 212 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_213
  INT_VECTOR_213, /* 213 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_214
  INT_VECTOR_214, /* 214 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_215
  INT_VECTOR_215, /* 215 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_216
  INT_VECTOR_216, /* 216 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_217
  INT_VECTOR_217, /* 217 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_218
  INT_VECTOR_218, /* 218 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_219
  INT_VECTOR_219, /* 219 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_220
  INT_VECTOR_220, /* 220 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_221
  INT_VECTOR_221, /* 221 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_222
  INT_VECTOR_222, /* 222 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_223
  INT_VECTOR_223, /* 223 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_224
  INT_VECTOR_224, /* 224 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_225
  INT_VECTOR_225, /* 225 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_226
  INT_VECTOR_226, /* 226 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_227
  INT_VECTOR_227, /* 227 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_228
  INT_VECTOR_228, /* 228 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_229
  INT_VECTOR_229, /* 229 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_230
  INT_VECTOR_230, /* 230 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_231
  INT_VECTOR_231, /* 231 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_232
  INT_VECTOR_232, /* 232 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_233
  INT_VECTOR_233, /* 233 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_234
  INT_VECTOR_234, /* 234 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_235
  INT_VECTOR_235, /* 235 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_236
  INT_VECTOR_236, /* 236 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_237
  INT_VECTOR_237, /* 237 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_238
  INT_VECTOR_238, /* 238 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_239
  INT_VECTOR_239, /* 239 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_240
  INT_VECTOR_240, /* 240 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_241
  INT_VECTOR_241, /* 241 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_242
  INT_VECTOR_242, /* 242 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_243
  INT_VECTOR_243, /* 243 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_244
  INT_VECTOR_244, /* 244 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_245
  INT_VECTOR_245, /* 245 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_246
  INT_VECTOR_246, /* 246 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_247
  INT_VECTOR_247, /* 247 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_248
  INT_VECTOR_248, /* 248 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_249
  INT_VECTOR_249, /* 249 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_250
  INT_VECTOR_250, /* 250 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_251
  INT_VECTOR_251, /* 251 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_252
  INT_VECTOR_252, /* 252 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_253
  INT_VECTOR_253, /* 253 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_254
  INT_VECTOR_254, /* 254 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_255
  INT_VECTOR_255, /* 255 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_256
  INT_VECTOR_256, /* 256 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_257
  INT_VECTOR_257, /* 257 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_258
  INT_VECTOR_258, /* 258 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_259
  INT_VECTOR_259, /* 259 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_260
  INT_VECTOR_260, /* 260 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_261
  INT_VECTOR_261, /* 261 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_262
  INT_VECTOR_262, /* 262 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_263
  INT_VECTOR_263, /* 263 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_264
  INT_VECTOR_264, /* 264 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_265
  INT_VECTOR_265, /* 265 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_266
  INT_VECTOR_266, /* 266 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_267
  INT_VECTOR_267, /* 267 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_268
  INT_VECTOR_268, /* 268 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_269
  INT_VECTOR_269, /* 269 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_270
  INT_VECTOR_270, /* 270 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_271
  INT_VECTOR_271, /* 271 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_272
  INT_VECTOR_272, /* 272 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_273
  INT_VECTOR_273, /* 273 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_274
  INT_VECTOR_274, /* 274 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_275
  INT_VECTOR_275, /* 275 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_276
  INT_VECTOR_276, /* 276 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_277
  INT_VECTOR_277, /* 277 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_278
  INT_VECTOR_278, /* 278 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_279
  INT_VECTOR_279, /* 279 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_280
  INT_VECTOR_280, /* 280 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_281
  INT_VECTOR_281, /* 281 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_282
  INT_VECTOR_282, /* 282 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_283
  INT_VECTOR_283, /* 283 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_284
  INT_VECTOR_284, /* 284 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_285
  INT_VECTOR_285, /* 285 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_286
  INT_VECTOR_286, /* 286 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_287
  INT_VECTOR_287, /* 287 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_288
  INT_VECTOR_288, /* 288 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_289
  INT_VECTOR_289, /* 289 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_290
  INT_VECTOR_290, /* 290 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_291
  INT_VECTOR_291, /* 291 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_292
  INT_VECTOR_292, /* 292 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_293
  INT_VECTOR_293, /* 293 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_294
  INT_VECTOR_294, /* 294 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_295
  INT_VECTOR_295, /* 295 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_296
  INT_VECTOR_296, /* 296 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_297
  INT_VECTOR_297, /* 297 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_298
  INT_VECTOR_298, /* 298 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_299
  INT_VECTOR_299, /* 299 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_300
  INT_VECTOR_300, /* 300 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_301
  INT_VECTOR_301, /* 301 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_302
  INT_VECTOR_302, /* 302 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_303
  INT_VECTOR_303, /* 303 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_304
  INT_VECTOR_304, /* 304 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_305
  INT_VECTOR_305, /* 305 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_306
  INT_VECTOR_306, /* 306 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_307
  INT_VECTOR_307, /* 307 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_308
  INT_VECTOR_308, /* 308 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_309
  INT_VECTOR_309, /* 309 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_310
  INT_VECTOR_310, /* 310 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_311
  INT_VECTOR_311, /* 311 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_312
  INT_VECTOR_312, /* 312 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_313
  INT_VECTOR_313, /* 313 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_314
  INT_VECTOR_314, /* 314 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_315
  INT_VECTOR_315, /* 315 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_316
  INT_VECTOR_316, /* 316 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_317
  INT_VECTOR_317, /* 317 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_318
  INT_VECTOR_318, /* 318 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_319
  INT_VECTOR_319, /* 319 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_320
  INT_VECTOR_320, /* 320 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_321
  INT_VECTOR_321, /* 321 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_322
  INT_VECTOR_322, /* 322 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_323
  INT_VECTOR_323, /* 323 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_324
  INT_VECTOR_324, /* 324 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_325
  INT_VECTOR_325, /* 325 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_326
  INT_VECTOR_326, /* 326 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_327
  INT_VECTOR_327, /* 327 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_328
  INT_VECTOR_328, /* 328 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_329
  INT_VECTOR_329, /* 329 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_330
  INT_VECTOR_330, /* 330 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_331
  INT_VECTOR_331, /* 331 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_332
  INT_VECTOR_332, /* 332 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_333
  INT_VECTOR_333, /* 333 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_334
  INT_VECTOR_334, /* 334 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_335
  INT_VECTOR_335, /* 335 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_336
  INT_VECTOR_336, /* 336 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_337
  INT_VECTOR_337, /* 337 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_338
  INT_VECTOR_338, /* 338 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_339
  INT_VECTOR_339, /* 339 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_340
  INT_VECTOR_340, /* 340 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_341
  INT_VECTOR_341, /* 341 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_342
  INT_VECTOR_342, /* 342 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_343
  INT_VECTOR_343, /* 343 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_344
  INT_VECTOR_344, /* 344 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_345
  INT_VECTOR_345, /* 345 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_346
  INT_VECTOR_346, /* 346 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_347
  INT_VECTOR_347, /* 347 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_348
  INT_VECTOR_348, /* 348 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_349
  INT_VECTOR_349, /* 349 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_350
  INT_VECTOR_350, /* 350 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_351
  INT_VECTOR_351, /* 351 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_352
  INT_VECTOR_352, /* 352 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_353
  INT_VECTOR_353, /* 353 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_354
  INT_VECTOR_354, /* 354 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_355
  INT_VECTOR_355, /* 355 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_356
  INT_VECTOR_356, /* 356 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_357
  INT_VECTOR_357 /* 357 */
#else
  Dummy_ISR
#endif
};
#pragma ghs section sdata=default
#endif

/*****************************************************************************/
/*                         CORTST F1KM-S1 IVT                                */
/*****************************************************************************/
#ifdef CORTST_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), Timer_Task, DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef CORTST_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         DIO F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef DIO_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef DIO_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         FLS F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef FLS_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  /* 60 */
  #if(FLS_DMA00_ISR_API == STD_ON)
    FLS_DMA00_ISR,
  #else
    DUMMY(060),
  #endif
  /* 61 */
  #if(FLS_DMA01_ISR_API == STD_ON)
    FLS_DMA01_ISR,
  #else
    DUMMY(061),
  #endif
  /* 62 */
  #if(FLS_DMA02_ISR_API == STD_ON)
    FLS_DMA02_ISR,
  #else
    DUMMY(062),
  #endif
  /* 63 */
  #if(FLS_DMA03_ISR_API == STD_ON)
    FLS_DMA03_ISR,
  #else
    DUMMY(063),
  #endif
  /* 64 */
  #if(FLS_DMA04_ISR_API == STD_ON)
    FLS_DMA04_ISR,
  #else
    DUMMY(064),
  #endif
  /* 65 */
  #if(FLS_DMA05_ISR_API == STD_ON)
    FLS_DMA05_ISR,
  #else
    DUMMY(065),
  #endif
  /* 66 */
  #if(FLS_DMA06_ISR_API == STD_ON)
    FLS_DMA06_ISR,
  #else
    DUMMY(066),
  #endif
  /* 67 */
  #if(FLS_DMA07_ISR_API == STD_ON)
    FLS_DMA07_ISR,
  #else
    DUMMY(067),
  #endif
  /* 68 */
  #if(FLS_DMA08_ISR_API == STD_ON)
    FLS_DMA08_ISR,
  #else
    DUMMY(068),
  #endif
  /* 69 */
  #if(FLS_DMA09_ISR_API == STD_ON)
    FLS_DMA09_ISR,
  #else
   DUMMY(069),
  #endif
  /* 70 */
  #if(FLS_DMA10_ISR_API == STD_ON)
    FLS_DMA10_ISR,
  #else
    DUMMY(070),
  #endif
  /* 71 */
  #if(FLS_DMA11_ISR_API == STD_ON)
    FLS_DMA11_ISR,
  #else
    DUMMY(071),
  #endif
  /* 72 */
  #if(FLS_DMA12_ISR_API == STD_ON)
    FLS_DMA12_ISR,
  #else
   DUMMY(072),
  #endif
  /* 73 */
  #if(FLS_DMA13_ISR_API == STD_ON)
    FLS_DMA13_ISR,
  #else
    DUMMY(073),
  #endif
  /* 74 */
  #if(FLS_DMA14_ISR_API == STD_ON)
    FLS_DMA14_ISR,
  #else
    DUMMY(074),
  #endif
  /* 75 */
  #if(FLS_DMA15_ISR_API == STD_ON)
    FLS_DMA15_ISR,
  #else
    DUMMY(075),
  #endif
  DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110),
  #if(FLS_INTERRUPT_MODE == STD_ON)
   #ifdef Os_FLS_FLENDNM_CAT2_ISR
   /* 111 */
   App_Os_FLS_FLENDNM_ISR,
   #else
   /* 111 */
   FLS_FLENDNM_ISR,
   #endif
   #else
   /* 111 */
   DUMMY(111),
  #endif
  DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef FLS_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         FLSTST F1KM-S1 IVT                                */
/*****************************************************************************/
#ifdef FLSTST_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef FLSTST_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         FR F1KM-S1 IVT                                    */
/*****************************************************************************/
#ifdef FR_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), INTFLXA0TIM0, DUMMY(182), INTFLXA0TIM2, DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef FR_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         GPT F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef GPT_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (GPT_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
    #else
      App_Os_TAUD0_CH00_ISR,
    #endif
  #else
    DUMMY(008),
  #endif

  #if (GPT_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (GPT_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (GPT_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (GPT_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (GPT_TAUD0_CH10_ISR_API == STD_ON)
  TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (GPT_TAUD0_CH12_ISR_API == STD_ON)
  TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (GPT_TAUD0_CH14_ISR_API == STD_ON)
  TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),

   #if (GPT_TAUD0_CH01_ISR_API == STD_ON)
   TAUD0_CH01_ISR,
   #else
    DUMMY(048),
   #endif

   #if (GPT_TAUD0_CH03_ISR_API == STD_ON)
   TAUD0_CH03_ISR,
   #else
    DUMMY(049),
   #endif

   #if (GPT_TAUD0_CH05_ISR_API == STD_ON)
    TAUD0_CH05_ISR,
   #else
    DUMMY(050),
   #endif

   #if (GPT_TAUD0_CH07_ISR_API == STD_ON)
      #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
        TAUD0_CH07_ISR,
      #else
       App_Os_TAUD0_CH07_ISR,
      #endif
   #else
      DUMMY(051),
   #endif

  #if (GPT_TAUD0_CH09_ISR_API == STD_ON)
   TAUD0_CH09_ISR,
  #else
   DUMMY(052),
  #endif

  #if (GPT_TAUD0_CH11_ISR_API == STD_ON)
   TAUD0_CH11_ISR,
  #else
   DUMMY(053),
  #endif

  #if (GPT_TAUD0_CH13_ISR_API == STD_ON)
   TAUD0_CH13_ISR,
  #else
   DUMMY(054),
  #endif

  #if (GPT_TAUD0_CH15_ISR_API == STD_ON)
   TAUD0_CH15_ISR,
  #else
   DUMMY(055),
  #endif


  DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079),

  #if (GPT_TAUJ0_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUJ0_CH00_ISR,
    #else
      App_Os_TAUJ0_CH00_ISR,
    #endif
  #else
    DUMMY(080),
  #endif

  #if (GPT_TAUJ0_CH01_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUJ0_CH01_ISR,
    #else
      App_Os_TAUJ0_CH01_ISR,
    #endif
  #else
    DUMMY(081),
  #endif

  #if (GPT_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(082),
  #endif

  #if (GPT_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(083),
  #endif

  #if (GPT_OSTM0_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      OSTM0_CH00_ISR,
    #else
      App_Os_OSTM0_CH01_ISR,
    #endif
  #else
    DUMMY(084),
  #endif

  DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141),

  #if (GPT_TAUB0_CH00_ISR_API == STD_ON)
   TAUB0_CH00_ISR,
  #else
   DUMMY(142),
  #endif

  #if (GPT_TAUB0_CH01_ISR_API == STD_ON)
   TAUB0_CH01_ISR,
  #else
   DUMMY(143),
  #endif

  #if (GPT_TAUB0_CH02_ISR_API == STD_ON)
   TAUB0_CH02_ISR,
  #else
   DUMMY(144),
  #endif

  #if (GPT_TAUB0_CH03_ISR_API == STD_ON)
   TAUB0_CH03_ISR,
  #else
   DUMMY(145),
  #endif

  #if (GPT_TAUB0_CH04_ISR_API == STD_ON)
   TAUB0_CH04_ISR,
  #else
   DUMMY(146),
  #endif

  #if (GPT_TAUB0_CH05_ISR_API == STD_ON)
   TAUB0_CH05_ISR,
  #else
   DUMMY(147),
  #endif

  #if (GPT_TAUB0_CH06_ISR_API == STD_ON)
   TAUB0_CH06_ISR,
  #else
   DUMMY(148),
  #endif

  #if (GPT_TAUB0_CH07_ISR_API == STD_ON)
   TAUB0_CH07_ISR,
  #else
   DUMMY(149),
  #endif

  #if (GPT_TAUB0_CH08_ISR_API == STD_ON)
   TAUB0_CH08_ISR,
  #else
   DUMMY(150),
  #endif

  #if (GPT_TAUB0_CH09_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUB0_CH09_ISR,
    #else
      App_Os_TAUB0_CH09_ISR,
    #endif
  #else
    DUMMY(151),
  #endif

  #if (GPT_TAUB0_CH10_ISR_API == STD_ON)
   TAUB0_CH10_ISR,
  #else
    DUMMY(152),
  #endif

  #if (GPT_TAUB0_CH11_ISR_API == STD_ON)
   TAUB0_CH11_ISR,
  #else
    DUMMY(153),
  #endif

  #if (GPT_TAUB0_CH12_ISR_API == STD_ON)
   TAUB0_CH12_ISR,
  #else
    DUMMY(154),
  #endif

  #if (GPT_TAUB0_CH13_ISR_API == STD_ON)
   TAUB0_CH13_ISR,
  #else
    DUMMY(155),
  #endif

  #if (GPT_TAUB0_CH14_ISR_API == STD_ON)
   TAUB0_CH14_ISR,
  #else
    DUMMY(156),
  #endif

  #if (GPT_TAUB0_CH15_ISR_API == STD_ON)
   TAUB0_CH15_ISR,
  #else
    DUMMY(157),
  #endif

  DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),DUMMY(162), DUMMY(163),
  DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (GPT_TAUJ1_CH00_ISR_API == STD_ON)
   TAUJ1_CH00_ISR,
  #else
   DUMMY(168),
  #endif

  #if (GPT_TAUJ1_CH01_ISR_API == STD_ON)
   TAUJ1_CH01_ISR,
  #else
   DUMMY(169),
  #endif

  #if (GPT_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
   DUMMY(170),
  #endif

  #if (GPT_TAUJ1_CH03_ISR_API == STD_ON)
   TAUJ1_CH03_ISR,
  #else
   DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276),

  #if (GPT_TAUJ2_CH00_ISR_API == STD_ON)
    TAUJ2_CH00_ISR,
  #else
    DUMMY(277),
  #endif

  #if (GPT_TAUJ2_CH01_ISR_API == STD_ON)
    TAUJ2_CH01_ISR,
  #else
    DUMMY(278),
  #endif

  #if (GPT_TAUJ2_CH02_ISR_API == STD_ON)
    TAUJ2_CH02_ISR,
  #else
    DUMMY(279),
  #endif

  #if (GPT_TAUJ2_CH03_ISR_API == STD_ON)
    TAUJ2_CH03_ISR,
  #else
    DUMMY(280),
  #endif

  #if (GPT_TAUJ3_CH00_ISR_API == STD_ON)
    TAUJ3_CH00_ISR,
  #else
    DUMMY(281),
  #endif

  #if (GPT_TAUJ3_CH01_ISR_API == STD_ON)
    TAUJ3_CH01_ISR,
  #else
    DUMMY(282),
  #endif

  #if (GPT_TAUJ3_CH02_ISR_API == STD_ON)
    TAUJ3_CH02_ISR,
  #else
    DUMMY(283),
  #endif

  #if (GPT_TAUJ3_CH03_ISR_API == STD_ON)
    TAUJ3_CH03_ISR,
  #else
    DUMMY(284),
  #endif

  DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef GPT_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         ICU F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef ICU_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (ICU_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
      #else
      App_Os_TAUD0_CH00_ISR,
      #endif
   #else
    DUMMY(008),
  #endif

  #if (ICU_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (ICU_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (ICU_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (ICU_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (ICU_TAUD0_CH10_ISR_API == STD_ON)
    TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (ICU_TAUD0_CH12_ISR_API == STD_ON)
    TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (ICU_TAUD0_CH14_ISR_API == STD_ON)
    TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017), DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021),
  DUMMY(022), DUMMY(023), DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027),
  DUMMY(028), DUMMY(029), DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033),
  DUMMY(034), DUMMY(035), DUMMY(036),

  #if (ICU_EXT_INTP_CH00_ISR_API == STD_ON)
  EXT_INTP_CH00_ISR,
  #else
    DUMMY(037),
  #endif

   #if (ICU_EXT_INTP_CH01_ISR_API == STD_ON)
   EXT_INTP_CH01_ISR,
   #else
    DUMMY(038),
   #endif

   #if (ICU_EXT_INTP_CH02_ISR_API == STD_ON)
     EXT_INTP_CH02_ISR,
   #else
    DUMMY(039),
   #endif

  DUMMY(040), DUMMY(041), DUMMY(042),

  #if (ICU_EXT_INTP_CH03_ISR_API == STD_ON)
    EXT_INTP_CH03_ISR,
   #else
    DUMMY(043),
   #endif

   #if (ICU_EXT_INTP_CH04_ISR_API == STD_ON)
       #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
       EXT_INTP_CH04_ISR,
       #else
       App_Os_EXT_INTP_CH04_ISR,
       #endif
   #else
    DUMMY(44),
   #endif

   #if (ICU_EXT_INTP_CH05_ISR_API == STD_ON)
     EXT_INTP_CH05_ISR,
   #else
    DUMMY(45),
   #endif

    #if (ICU_EXT_INTP_CH10_ISR_API == STD_ON)
     EXT_INTP_CH10_ISR,
   #else
    DUMMY(46),
   #endif

   #if (ICU_EXT_INTP_CH11_ISR_API == STD_ON)
     EXT_INTP_CH11_ISR,
   #else
    DUMMY(47),
   #endif

  #if (ICU_TAUD0_CH01_ISR_API == STD_ON)
    TAUD0_CH01_ISR,
  #else
    DUMMY(48),
  #endif

  #if (ICU_TAUD0_CH03_ISR_API == STD_ON)
    TAUD0_CH03_ISR,
  #else
    DUMMY(49),
  #endif

  #if (ICU_TAUD0_CH05_ISR_API == STD_ON)
    TAUD0_CH05_ISR,
  #else
    DUMMY(50),
  #endif

  #if (ICU_TAUD0_CH07_ISR_API == STD_ON)

    #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
        TAUD0_CH07_ISR,
    #else
        App_Os_TAUD0_CH07_ISR,
    #endif
  #else
    DUMMY(51),
  #endif

  #if (ICU_TAUD0_CH09_ISR_API == STD_ON)
    TAUD0_CH09_ISR,
  #else
    DUMMY(52),
  #endif

  #if (ICU_TAUD0_CH11_ISR_API == STD_ON)
    TAUD0_CH11_ISR,
  #else
    DUMMY(53),
  #endif

  #if (ICU_TAUD0_CH13_ISR_API == STD_ON)
    TAUD0_CH13_ISR,
  #else
    DUMMY(54),
  #endif

  #if (ICU_TAUD0_CH15_ISR_API == STD_ON)
    TAUD0_CH15_ISR,
  #else
    DUMMY(55),
  #endif

  DUMMY(56), DUMMY(57), DUMMY(58), DUMMY(59), DUMMY(60), DUMMY(61), DUMMY(62),
  DUMMY(63), DUMMY(64), DUMMY(65), DUMMY(66), DUMMY(67), DUMMY(68), DUMMY(69),
  DUMMY(70), DUMMY(71), DUMMY(72), DUMMY(73), DUMMY(74), DUMMY(75), DUMMY(76),
  DUMMY(77), DUMMY(78), DUMMY(79),

  #if (ICU_TAUJ0_CH00_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUJ0_CH00_ISR,
      #else
            App_Os_TAUJ0_CH00_ISR,
      #endif
  #else
    DUMMY(80),
  #endif

  #if (ICU_TAUJ0_CH01_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUJ0_CH01_ISR,
      #else
            App_Os_TAUJ0_CH01_ISR,
      #endif
  #else
    DUMMY(81),
  #endif

  #if (ICU_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(82),
  #endif

  #if (ICU_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(83),
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127),

   #if (ICU_EXT_INTP_CH06_ISR_API == STD_ON)
     EXT_INTP_CH06_ISR,
   #else
    DUMMY(128),
   #endif

   #if (ICU_EXT_INTP_CH07_ISR_API == STD_ON)
     EXT_INTP_CH07_ISR,
   #else
    DUMMY(129),
   #endif

   #if (ICU_EXT_INTP_CH08_ISR_API == STD_ON)
     EXT_INTP_CH08_ISR,
   #else
    DUMMY(130),
   #endif

   #if (ICU_EXT_INTP_CH12_ISR_API == STD_ON)
     EXT_INTP_CH12_ISR,
   #else
    DUMMY(131),
   #endif

  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141),

  #if (ICU_TAUB0_CH00_ISR_API == STD_ON)
    TAUB0_CH00_ISR,
  #else
    DUMMY(142),
  #endif

  #if (ICU_TAUB0_CH01_ISR_API == STD_ON)
    TAUB0_CH01_ISR,
  #else
    DUMMY(143),
  #endif

  #if (ICU_TAUB0_CH02_ISR_API == STD_ON)
    TAUB0_CH02_ISR,
  #else
    DUMMY(144),
  #endif

  #if (ICU_TAUB0_CH03_ISR_API == STD_ON)
    TAUB0_CH03_ISR,
  #else
    DUMMY(145),
  #endif

  #if (ICU_TAUB0_CH04_ISR_API == STD_ON)
    TAUB0_CH04_ISR,
  #else
    DUMMY(146),
  #endif

  #if (ICU_TAUB0_CH05_ISR_API == STD_ON)
    TAUB0_CH05_ISR,
  #else
    DUMMY(147),
  #endif

  #if (ICU_TAUB0_CH06_ISR_API == STD_ON)
    TAUB0_CH06_ISR,
  #else
    DUMMY(148),
  #endif

  #if (ICU_TAUB0_CH07_ISR_API == STD_ON)
    TAUB0_CH07_ISR,
  #else
    DUMMY(149),
  #endif

  #if (ICU_TAUB0_CH08_ISR_API == STD_ON)
    TAUB0_CH08_ISR,
  #else
    DUMMY(150),
  #endif

  #if (ICU_TAUB0_CH09_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUB0_CH09_ISR,
      #else
            App_Os_TAUB0_CH09_ISR,
      #endif
  #else
    DUMMY(151),
  #endif

  #if (ICU_TAUB0_CH10_ISR_API == STD_ON)
    TAUB0_CH10_ISR,
  #else
    DUMMY(152),
  #endif

  #if (ICU_TAUB0_CH11_ISR_API == STD_ON)
    TAUB0_CH11_ISR,
  #else
    DUMMY(153),
  #endif

  #if (ICU_TAUB0_CH12_ISR_API == STD_ON)
    TAUB0_CH12_ISR,
  #else
    DUMMY(154),
  #endif

  #if (ICU_TAUB0_CH13_ISR_API == STD_ON)
    TAUB0_CH13_ISR,
  #else
    DUMMY(155),
  #endif

  #if (ICU_TAUB0_CH14_ISR_API == STD_ON)
    TAUB0_CH14_ISR,
  #else
    DUMMY(156),
  #endif

  #if (ICU_TAUB0_CH15_ISR_API == STD_ON)
    TAUB0_CH15_ISR,
  #else
    DUMMY(157),
  #endif

  DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161), DUMMY(162), DUMMY(163),
  DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (ICU_TAUJ1_CH00_ISR_API == STD_ON)
    TAUJ1_CH00_ISR,
  #else
    DUMMY(168),
  #endif

  #if (ICU_TAUJ1_CH01_ISR_API == STD_ON)
    TAUJ1_CH01_ISR,
  #else
    DUMMY(169),
  #endif

  #if (ICU_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
    DUMMY(170),
  #endif

  #if (ICU_TAUJ1_CH03_ISR_API == STD_ON)
    TAUJ1_CH03_ISR,
  #else
    DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173), DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177),
  DUMMY(178), DUMMY(179), DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183),
  DUMMY(184), DUMMY(185), DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189),
  DUMMY(190), DUMMY(191), DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195),
  DUMMY(196), DUMMY(197), DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201),
  DUMMY(202), DUMMY(203), DUMMY(204),

   #if (ICU_EXT_INTP_CH09_ISR_API == STD_ON)
     EXT_INTP_CH09_ISR,
   #else
    DUMMY(205),
   #endif

   #if (ICU_EXT_INTP_CH13_ISR_API == STD_ON)
     EXT_INTP_CH13_ISR,
   #else
    DUMMY(206),
   #endif

   #if (ICU_EXT_INTP_CH14_ISR_API == STD_ON)
     EXT_INTP_CH14_ISR,
   #else
    DUMMY(207),
   #endif

   #if (ICU_EXT_INTP_CH15_ISR_API == STD_ON)
     EXT_INTP_CH15_ISR,
   #else
    DUMMY(208),
   #endif

  DUMMY(209), DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214),
  DUMMY(215), DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220),
  DUMMY(221), DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226),
  DUMMY(227), DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232),
  DUMMY(233), DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238),
  DUMMY(239), DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244),
  DUMMY(245), DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250),
  DUMMY(251), DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255),

  #if (ICU_TAUB1_CH00_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUB1_CH00_ISR,
      #else
            App_Os_TAUB1_CH00_ISR,
      #endif
  #else
    DUMMY(256),
  #endif

  #if (ICU_TAUB1_CH01_ISR_API == STD_ON)
    TAUB1_CH01_ISR,
  #else
    DUMMY(257),
  #endif

  #if (ICU_TAUB1_CH02_ISR_API == STD_ON)
    TAUB1_CH02_ISR,
  #else
    DUMMY(258),
  #endif

  #if (ICU_TAUB1_CH03_ISR_API == STD_ON)
    TAUB1_CH03_ISR,
  #else
    DUMMY(259),
  #endif

  #if (ICU_TAUB1_CH04_ISR_API == STD_ON)
    TAUB1_CH04_ISR,
  #else
    DUMMY(260),
  #endif

  #if (ICU_TAUB1_CH05_ISR_API == STD_ON)
    TAUB1_CH05_ISR,
  #else
    DUMMY(261),
  #endif

  #if (ICU_TAUB1_CH06_ISR_API == STD_ON)
    TAUB1_CH06_ISR,
  #else
    DUMMY(262),
  #endif

  #if (ICU_TAUB1_CH07_ISR_API == STD_ON)
    TAUB1_CH07_ISR,
  #else
    DUMMY(263),
  #endif

  #if (ICU_TAUB1_CH08_ISR_API == STD_ON)
    TAUB1_CH08_ISR,
  #else
    DUMMY(264),
  #endif

  #if (ICU_TAUB1_CH09_ISR_API == STD_ON)
    TAUB1_CH09_ISR,
  #else
    DUMMY(265),
  #endif

  #if (ICU_TAUB1_CH10_ISR_API == STD_ON)
    TAUB1_CH10_ISR,
  #else
    DUMMY(266),
  #endif

  #if (ICU_TAUB1_CH11_ISR_API == STD_ON)
    TAUB1_CH11_ISR,
  #else
    DUMMY(267),
  #endif

  #if (ICU_TAUB1_CH12_ISR_API == STD_ON)
    TAUB1_CH12_ISR,
  #else
    DUMMY(268),
  #endif

  #if (ICU_TAUB1_CH13_ISR_API == STD_ON)
    TAUB1_CH13_ISR,
  #else
    DUMMY(269),
  #endif

  #if (ICU_TAUB1_CH14_ISR_API == STD_ON)
    TAUB1_CH14_ISR,
  #else
    DUMMY(270),
  #endif

  #if (ICU_TAUB1_CH15_ISR_API == STD_ON)
    TAUB1_CH15_ISR,
  #else
    DUMMY(271),
  #endif

  DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275), DUMMY(276),

  #if (ICU_TAUJ2_CH00_ISR_API == STD_ON)
    TAUJ2_CH00_ISR,
  #else
    DUMMY(277),
  #endif

  #if (ICU_TAUJ2_CH01_ISR_API == STD_ON)
    TAUJ2_CH01_ISR,
  #else
    DUMMY(278),
  #endif

  #if (ICU_TAUJ2_CH02_ISR_API == STD_ON)
    TAUJ2_CH02_ISR,
  #else
    DUMMY(279),
  #endif

  #if (ICU_TAUJ2_CH03_ISR_API == STD_ON)
    TAUJ2_CH03_ISR,
  #else
    DUMMY(280),
  #endif

  #if (ICU_TAUJ3_CH00_ISR_API == STD_ON)
    TAUJ3_CH00_ISR,
  #else
    DUMMY(281),
  #endif

  #if (ICU_TAUJ3_CH01_ISR_API == STD_ON)
    TAUJ3_CH01_ISR,
  #else
    DUMMY(282),
  #endif

  #if (ICU_TAUJ3_CH02_ISR_API == STD_ON)
    TAUJ3_CH02_ISR,
  #else
    DUMMY(283),
  #endif

  #if (ICU_TAUJ3_CH03_ISR_API == STD_ON)
    TAUJ3_CH03_ISR,
  #else
    DUMMY(284),
  #endif

  DUMMY(285), DUMMY(286), DUMMY(287), DUMMY(288), DUMMY(289), DUMMY(290),
  DUMMY(291), DUMMY(292), DUMMY(293), DUMMY(294), DUMMY(295), DUMMY(296),
  DUMMY(297), DUMMY(298), DUMMY(299), DUMMY(300), DUMMY(301), DUMMY(302),
  DUMMY(303), DUMMY(304), DUMMY(305), DUMMY(306), DUMMY(307), DUMMY(308),
  DUMMY(309), DUMMY(310), DUMMY(311), DUMMY(312), DUMMY(313), DUMMY(314),
  DUMMY(315), DUMMY(316), DUMMY(317), DUMMY(318), DUMMY(319), DUMMY(320),
  DUMMY(321), DUMMY(322), DUMMY(323), DUMMY(324), DUMMY(325), DUMMY(326),
  DUMMY(327), DUMMY(328), DUMMY(329), DUMMY(330), DUMMY(331), DUMMY(332),
  DUMMY(333), DUMMY(334), DUMMY(335), DUMMY(336), DUMMY(337), DUMMY(338),
  DUMMY(339), DUMMY(340), DUMMY(341), DUMMY(342), DUMMY(343), DUMMY(344),
  DUMMY(345), DUMMY(346), DUMMY(347), DUMMY(348), DUMMY(349), DUMMY(350),
  DUMMY(351), DUMMY(352), DUMMY(353), DUMMY(354), DUMMY(355), DUMMY(355),
  DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359), DUMMY(360), DUMMY(361),
  DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365), DUMMY(366), DUMMY(367),
  DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371), DUMMY(372), DUMMY(373),
  DUMMY(374), DUMMY(375), DUMMY(376),
};
/* End of #ifdef ICU_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         LIN F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef LIN_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032),

  #if (LIN_CHANNEL12_CONFIGURED == STD_ON)
  /* 33 */
  LIN_CHANNEL12_ISR,
  #else
  DUMMY(033),
  #endif

  DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050),

  /* 51 */
  Timer0_Interrupt,

  DUMMY(052), DUMMY(053), DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057),

  #if (LIN_CHANNEL00_CONFIGURED == STD_ON)
  /* 58 */
  LIN_CHANNEL00_ISR,
  #else
  DUMMY(058),
  #endif
  #if (LIN_CHANNEL01_CONFIGURED == STD_ON)
  #if defined (Os_LIN_CHANNEL01_CAT2_ISR) || defined (LIN_CHANNEL01_CAT2_ISR)
  /* 59 */
  App_Os_LIN01_SG01_ISR,
  #else
  /* 59 */
  LIN_CHANNEL01_ISR,
  #endif
  #else
  DUMMY(059),
  #endif

  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),

  #if (LIN_CHANNEL13_CONFIGURED == STD_ON)
 /* 120 */
  LIN_CHANNEL13_ISR,
  #else
  DUMMY(120),
  #endif

  DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),

  #if (LIN_CHANNEL02_CONFIGURED == STD_ON)
  /*162*/
  LIN_CHANNEL02_ISR,
  #else
  DUMMY(162),
  #endif

  DUMMY(163),

  #if (LIN_CHANNEL14_CONFIGURED == STD_ON)
  /*164*/
  LIN_CHANNEL14_ISR,
  #else
  DUMMY(164),
  #endif

  DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),

  #if (LIN_CHANNEL15_CONFIGURED == STD_ON)
  /* 228 */
  LIN_CHANNEL15_ISR,
  #else
  DUMMY(228),
  #endif

  DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef LIN_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         MCU F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef MCU_MODULE_TEST
#pragma ghs startsda
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022),
#ifdef MCU_CANICUSTOP_INT
/* 23 */
   MCU_CAN_STOP,
#else
  DUMMY(023),
#endif
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079),
#ifdef MCU_TIMER_INT
/* 80 */
   TAUJ0_I0,
#else
/* 80 */
  DUMMY(80),
#endif
#ifdef MCU_TIMER_INT
/* 81 */
   TAUJ0_I1,
#else
/* 81 */
  DUMMY(81),
#endif
  DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104),
  DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111),
  /* 112 */
#if ((MCU_LOW_POWER_SEQUENCER == STD_ON)&&(MCU_INTCWEND_ISR_ENABLE == STD_ON))
#ifdef MCU_CFG53_INT
   MCU_INTCWEND_CFG53_ISR,
#else
   MCU_INTCWEND_ISR,
#endif
#else
  DUMMY(112),
#endif
  DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef MCU_MODULE_TEST */
#pragma ghs endsda
#endif


/*****************************************************************************/
/*                         PORT F1KM-S1 IVT                                  */
/*****************************************************************************/
#ifdef PORT_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef PORT_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         PWM F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef PWM_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (PWM_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
    #else
      App_Os_TAUD0_CH00_ISR,
    #endif
  #else
    DUMMY(008),
  #endif

  #if (PWM_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (PWM_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (PWM_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (PWM_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (PWM_TAUD0_CH10_ISR_API == STD_ON)
  TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (PWM_TAUD0_CH12_ISR_API == STD_ON)
  TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (PWM_TAUD0_CH14_ISR_API == STD_ON)
  TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),

   #if (PWM_TAUD0_CH01_ISR_API == STD_ON)
   TAUD0_CH01_ISR,
   #else
    DUMMY(048),
   #endif

   #if (PWM_TAUD0_CH03_ISR_API == STD_ON)
   TAUD0_CH03_ISR,
   #else
    DUMMY(049),
   #endif

   #if (PWM_TAUD0_CH05_ISR_API == STD_ON)
    TAUD0_CH05_ISR,
   #else
    DUMMY(050),
   #endif

   #if (PWM_TAUD0_CH07_ISR_API == STD_ON)
      #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
        TAUD0_CH07_ISR,
      #else
       App_Os_TAUD0_CH07_ISR,
      #endif
   #else
      DUMMY(051),
   #endif

  #if (PWM_TAUD0_CH09_ISR_API == STD_ON)
   TAUD0_CH09_ISR,
  #else
   DUMMY(052),
  #endif

  #if (PWM_TAUD0_CH11_ISR_API == STD_ON)
   TAUD0_CH11_ISR,
  #else
   DUMMY(053),
  #endif

  #if (PWM_TAUD0_CH13_ISR_API == STD_ON)
   TAUD0_CH13_ISR,
  #else
   DUMMY(054),
  #endif

  #if (PWM_TAUD0_CH15_ISR_API == STD_ON)
   TAUD0_CH15_ISR,
  #else
   DUMMY(055),
  #endif


  DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079),

  #if (PWM_TAUJ0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH00_ISR,
    #else
      App_Os_TAUJ0_CH00_ISR,
    #endif
  #else
    DUMMY(080),
  #endif

  #if (PWM_TAUJ0_CH01_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH01_ISR,
    #else
      App_Os_TAUJ0_CH01_ISR,
    #endif
  #else
    DUMMY(081),
  #endif

  #if (PWM_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(082),
  #endif

  #if (PWM_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(083),
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091),

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP00_ISR_API == STD_ON)
    PWM_INTPWGAG00_ISR,
    #else
     DUMMY(092),
    #endif
  #else
     DUMMY(092),
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP01_ISR_API == STD_ON)
    PWM_INTPWGAG01_ISR,
    #else
     DUMMY(093),
    #endif
  #else
     DUMMY(093),
  #endif

  DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141),

  #if (PWM_TAUB0_CH00_ISR_API == STD_ON)
   TAUB0_CH00_ISR,
  #else
   DUMMY(142),
  #endif

  #if (PWM_TAUB0_CH01_ISR_API == STD_ON)
   TAUB0_CH01_ISR,
  #else
   DUMMY(143),
  #endif

  #if (PWM_TAUB0_CH02_ISR_API == STD_ON)
   TAUB0_CH02_ISR,
  #else
   DUMMY(144),
  #endif

  #if (PWM_TAUB0_CH03_ISR_API == STD_ON)
   TAUB0_CH03_ISR,
  #else
   DUMMY(145),
  #endif

  #if (PWM_TAUB0_CH04_ISR_API == STD_ON)
   TAUB0_CH04_ISR,
  #else
   DUMMY(146),
  #endif

  #if (PWM_TAUB0_CH05_ISR_API == STD_ON)
   TAUB0_CH05_ISR,
  #else
   DUMMY(147),
  #endif

  #if (PWM_TAUB0_CH06_ISR_API == STD_ON)
   TAUB0_CH06_ISR,
  #else
   DUMMY(148),
  #endif

  #if (PWM_TAUB0_CH07_ISR_API == STD_ON)
   TAUB0_CH07_ISR,
  #else
   DUMMY(149),
  #endif

  #if (PWM_TAUB0_CH08_ISR_API == STD_ON)
   TAUB0_CH08_ISR,
  #else
   DUMMY(150),
  #endif

  #if (PWM_TAUB0_CH09_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUB0_CH09_ISR,
    #else
      App_Os_TAUB0_CH09_ISR,
    #endif
  #else
    DUMMY(151),
  #endif

  #if (PWM_TAUB0_CH10_ISR_API == STD_ON)
   TAUB0_CH10_ISR,
  #else
    DUMMY(152),
  #endif

  #if (PWM_TAUB0_CH11_ISR_API == STD_ON)
   TAUB0_CH11_ISR,
  #else
    DUMMY(153),
  #endif

  #if (PWM_TAUB0_CH12_ISR_API == STD_ON)
   TAUB0_CH12_ISR,
  #else
    DUMMY(154),
  #endif

  #if (PWM_TAUB0_CH13_ISR_API == STD_ON)
   TAUB0_CH13_ISR,
  #else
    DUMMY(155),
  #endif

  #if (PWM_TAUB0_CH14_ISR_API == STD_ON)
   TAUB0_CH14_ISR,
  #else
    DUMMY(156),
  #endif

  #if (PWM_TAUB0_CH15_ISR_API == STD_ON)
   TAUB0_CH15_ISR,
  #else
    DUMMY(157),
  #endif

  DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),DUMMY(162), DUMMY(163),
  DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (PWM_TAUJ1_CH00_ISR_API == STD_ON)
   TAUJ1_CH00_ISR,
  #else
   DUMMY(168),
  #endif

  #if (PWM_TAUJ1_CH01_ISR_API == STD_ON)
   TAUJ1_CH01_ISR,
  #else
   DUMMY(169),
  #endif

  #if (PWM_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
   DUMMY(170),
  #endif

  #if (PWM_TAUJ1_CH03_ISR_API == STD_ON)
   TAUJ1_CH03_ISR,
  #else
   DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276),

  #if (PWM_TAUJ2_CH00_ISR_API == STD_ON)
    TAUJ2_CH00_ISR,
  #else
    DUMMY(277),
  #endif

  #if (PWM_TAUJ2_CH01_ISR_API == STD_ON)
    TAUJ2_CH01_ISR,
  #else
    DUMMY(278),
  #endif

  #if (PWM_TAUJ2_CH02_ISR_API == STD_ON)
    TAUJ2_CH02_ISR,
  #else
    DUMMY(279),
  #endif

  #if (PWM_TAUJ2_CH03_ISR_API == STD_ON)
    TAUJ2_CH03_ISR,
  #else
    DUMMY(280),
  #endif

  #if (PWM_TAUJ3_CH00_ISR_API == STD_ON)
    TAUJ3_CH00_ISR,
  #else
    DUMMY(281),
  #endif

  #if (PWM_TAUJ3_CH01_ISR_API == STD_ON)
    TAUJ3_CH01_ISR,
  #else
    DUMMY(282),
  #endif

  #if (PWM_TAUJ3_CH02_ISR_API == STD_ON)
    TAUJ3_CH02_ISR,
  #else
    DUMMY(283),
  #endif

  #if (PWM_TAUJ3_CH03_ISR_API == STD_ON)
    TAUJ3_CH03_ISR,
  #else
    DUMMY(284),
  #endif

  DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef PWM_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         RAMTST F1KM-S1 IVT                                */
/*****************************************************************************/
#ifdef RAMTST_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef RAMTST_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         SPI F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef SPI_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),
  #if(SPI_TIMER == STD_ON)
  /* 8 */
  Timer_Task,
  #else
  /* 8 */
  DUMMY(008),
  #endif
  #if(SPI_TIMER2 == STD_ON)
  /* 9 */
  Timer_Task2,
  #else
  DUMMY(009),
  #endif
  DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026),
  #if(SPI_CSIG0_TIC_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIG0_TIC_CAT2_ISR
  /* 27 */
  App_Os_SPI_CSIG0_TIC_ISR,
  #else
  /* 27 */
  SPI_CSIG0_TIC_ISR,
  #endif
  #else
    #ifdef APP_SPI_CSIG0_SLAVE_ISR_ON
    /* 27 */
    APP_SPI_CSIG0_SLAVE_TX_ISR,
    #else
    /* 27 */
    DUMMY(027),
    #endif
  #endif
  #if(SPI_CSIG0_TIR_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIG0_TIR_CAT2_ISR
  /* 28 */
  App_Os_SPI_CSIG0_TIR_ISR,
  #else
  /* 28 */
  SPI_CSIG0_TIR_ISR,
  #endif
  #else
    #ifdef APP_SPI_CSIG0_SLAVE_ISR_ON
    /* 28 */
    APP_SPI_CSIG0_SLAVE_RX_ISR,
    #else
    /* 28 */
    DUMMY(028),
    #endif
  #endif
  #if(SPI_CSIH0_TIC_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIH0_TIC_CAT2_ISR
  /* 29 */
  App_Os_SPI_CSIH0_TIC_ISR,
  #else
  /* 29 */
  SPI_CSIH0_TIC_ISR,
  #endif
  #else
    #ifdef APP_SPI_CSIH0_SLAVE_ISR_ON
    /* 29 */
    APP_SPI_CSIH0_SLAVE_TX_ISR,
    #else
    /* 29 */
    DUMMY(029),
    #endif
  #endif
  #if(SPI_CSIH0_TIR_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIH0_TIR_CAT2_ISR
  /* 30 */
  App_Os_SPI_CSIH0_TIR_ISR,
  #else
  /* 30 */
  SPI_CSIH0_TIR_ISR,
  #endif
  #else
    #ifdef APP_SPI_CSIH0_SLAVE_ISR_ON
    /* 30 */
    APP_SPI_CSIH0_SLAVE_RX_ISR,
    #else
    /* 30 */
    DUMMY(030),
    #endif
  #endif
  /* 31 */
  DUMMY(031),
  /* 32 */
  DUMMY(032),
  DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  #if(SPI_TIMER1 == STD_ON)
  /* 48 */
  Timer_Task1,
  #else
  DUMMY(048),
  #endif
  #if(SPI_TIMER3 == STD_ON)
  /* 49 */
  Timer_Task3,
  #else
  /* 49 */
  DUMMY(049),
  #endif
  DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056),
  /* 57 */
  DUMMY(057),
  /* 58 */
  DUMMY(058),
  /* 59 */
  DUMMY(059),
  #if(SPI_DMA00_ISR_API == STD_ON)
  /* 60 */
  SPI_DMA00_ISR,
  #else
  /* 60 */
  DUMMY(060),
  #endif
  #if(SPI_DMA01_ISR_API == STD_ON)
  /* 61 */
  SPI_DMA01_ISR,
  #else
  /* 61 */
  DUMMY(061),
  #endif
  #if(SPI_DMA02_ISR_API == STD_ON)
  /* 62 */
  SPI_DMA02_ISR,
  #else
  /* 62 */
  DUMMY(062),
  #endif
  #if(SPI_DMA03_ISR_API == STD_ON)
  /* 63 */
  SPI_DMA03_ISR,
  #else
  /* 63 */
  DUMMY(063),
  #endif
  #if(SPI_DMA04_ISR_API == STD_ON)
  /* 64 */
  SPI_DMA04_ISR,
  #else
  /* 64 */
  DUMMY(064),
  #endif
  #if(SPI_DMA05_ISR_API == STD_ON)
  /* 65 */
  SPI_DMA05_ISR,
  #else
  /* 65 */
  DUMMY(065),
  #endif
  #if(SPI_DMA06_ISR_API == STD_ON)
  /* 66 */
  SPI_DMA06_ISR,
  #else
  /* 66 */
  DUMMY(066),
  #endif
  #if(SPI_DMA07_ISR_API == STD_ON)
  /* 67 */
  SPI_DMA07_ISR,
  #else
  /* 67 */
  DUMMY(067),
  #endif
  #if(SPI_DMA08_ISR_API == STD_ON)
  /* 68 */
  SPI_DMA08_ISR,
  #else
  /* 68 */
  DUMMY(068),
  #endif
  #if(SPI_DMA09_ISR_API == STD_ON)
  /* 69 */
  SPI_DMA09_ISR,
  #else
  /* 69 */
  DUMMY(069),
  #endif
  #if(SPI_DMA10_ISR_API == STD_ON)
  /* 70 */
  SPI_DMA10_ISR,
  #else
  /* 70 */
  DUMMY(070),
  #endif
  #if(SPI_DMA11_ISR_API == STD_ON)
  /* 71 */
  SPI_DMA11_ISR,
  #else
  /* 71 */
  DUMMY(071),
  #endif
  #if(SPI_DMA12_ISR_API == STD_ON)
  /* 72 */
  SPI_DMA12_ISR,
  #else
  /* 72 */
  DUMMY(072),
  #endif
  #if(SPI_DMA13_ISR_API == STD_ON)
  /* 73 */
  SPI_DMA13_ISR,
  #else
  /* 73 */
  DUMMY(073),
  #endif
  #if(SPI_DMA14_ISR_API == STD_ON)
  /* 74 */
  SPI_DMA14_ISR,
  #else
  /* 74 */
  DUMMY(074),
  #endif
  #if(SPI_DMA15_ISR_API == STD_ON)
  /* 75 */
  SPI_DMA15_ISR,
  #else
  /* 75 */
  DUMMY(075),
  #endif
  DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097),
  #if(SPI_CSIG4_TIC_ISR_API == STD_ON)
  /* 98 */
  SPI_CSIG4_TIC_ISR,
  #else
  DUMMY(098),
  #endif
  #if(SPI_CSIG4_TIR_ISR_API == STD_ON)
  /* 99 */
  SPI_CSIG4_TIR_ISR,
  #else
  DUMMY(099),
  #endif
  /* 100 */
  DUMMY(100),
  DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115),

  #ifdef APP_SPI_CSIH1_SLAVE_ISR_ON
    /* #if(SPI_CSIH1_TIC_ISR_API == STD_ON) */
  /* 116 */
  APP_SPI_CSIH1_SLAVE_TX_ISR, /* SPI_CSIH1_TIC_ISR, */
  #else
  #if(SPI_CSIH1_TIC_ISR_API == STD_ON)
  /* 116 */
  SPI_CSIH1_TIC_ISR,
  #else
  /* 116 */
  DUMMY(116),
  #endif
  #endif

  #ifdef APP_SPI_CSIH1_SLAVE_ISR_ON
    /* #if(SPI_CSIH1_TIR_ISR_API == STD_ON) */
  /* 117 */
  APP_SPI_CSIH1_SLAVE_RX_ISR, /* SPI_CSIH1_TIR_ISR, */
  #else
  #if(SPI_CSIH1_TIR_ISR_API == STD_ON)
  /* 117 */
  SPI_CSIH1_TIR_ISR,
  #else
  /* 117 */
  DUMMY(117),
  #endif
  #endif
  /* 118 */
  DUMMY(118),
  /* 119 */
  DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123),
  #if(SPI_CSIH4_TIC_ISR_API == STD_ON)
  /* 124 */
  SPI_CSIH4_TIC_ISR,
  #else
  DUMMY(124),
  #endif
  #if(SPI_CSIH4_TIR_ISR_API == STD_ON)
  /* 125 */
  SPI_CSIH4_TIR_ISR,
  #else
  DUMMY(125),
  #endif
  DUMMY(126),
  /* 127 */
  DUMMY(127),
  DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  #ifdef APP_SPI_CSIH2_SLAVE_ISR_ON
  /* 132 */
  APP_SPI_CSIH2_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIH2_TIC_ISR_API == STD_ON)
  /* 132 */
  SPI_CSIH2_TIC_ISR,
  #else
  /* 132 */
  DUMMY(132),
  #endif
  #endif

  #ifdef APP_SPI_CSIH2_SLAVE_ISR_ON
  /* 133 */
  APP_SPI_CSIH2_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIH2_TIR_ISR_API == STD_ON)
  /* 133 */
  SPI_CSIH2_TIR_ISR,
  #else
  /* 133 */
  DUMMY(133),
  #endif
  #endif
  /* 134 */
  DUMMY(134),
  /* 135 */
  DUMMY(135),
  DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157),

  #ifdef APP_SPI_CSIH3_SLAVE_ISR_ON
  /* 158 */
  APP_SPI_CSIH3_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIH3_TIC_ISR_API == STD_ON)
  /* 158 */
  SPI_CSIH3_TIC_ISR,
  #else
  /* 158 */
  DUMMY(158),
  #endif
  #endif

  #ifdef APP_SPI_CSIH3_SLAVE_ISR_ON
  /* 159 */
  APP_SPI_CSIH3_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIH3_TIR_ISR_API == STD_ON)
  /* 159 */
  SPI_CSIH3_TIR_ISR,
  #else
  /* 159 */
  DUMMY(159),
  #endif
  #endif
  /* 160 */
  DUMMY(160),
  /* 161 */
  DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222),

 #ifdef APP_SPI_CSIG1_SLAVE_ISR_ON
  /* 223 */
  APP_SPI_CSIG1_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIG1_TIC_ISR_API == STD_ON)
  /* 223 */
  SPI_CSIG1_TIC_ISR,
  #else
  /* 223 */
  DUMMY(223),
  #endif
  #endif
  #ifdef APP_SPI_CSIG1_SLAVE_ISR_ON
  /* 224 */
  APP_SPI_CSIG1_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIG1_TIR_ISR_API == STD_ON)
  /* 224 */
  SPI_CSIG1_TIR_ISR,
  #else
  /* 224 */
  DUMMY(224),
  #endif
  #endif
  /* 225 */
  DUMMY(225),
  DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325),

  #ifdef APP_SPI_CSIG2_SLAVE_ISR_ON
  /* 326 */
  APP_SPI_CSIG2_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIG2_TIC_ISR_API == STD_ON)
  /* 326 */
  SPI_CSIG2_TIC_ISR,
  #else
  /* 326 */
  DUMMY(326),
  #endif
  #endif

  #ifdef APP_SPI_CSIG2_SLAVE_ISR_ON
  /* 327 */
  APP_SPI_CSIG2_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIG2_TIR_ISR_API == STD_ON)
  /* 327 */
  SPI_CSIG2_TIR_ISR,
  #else
  /* 327 */
  DUMMY(327),
  #endif
  #endif
  /* 328 */
  DUMMY(328),
  #ifdef APP_SPI_CSIG3_SLAVE_ISR_ON
  /* 329 */
  APP_SPI_CSIG3_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIG3_TIC_ISR_API == STD_ON)
  /* 329 */
  SPI_CSIG3_TIC_ISR,
  #else
  /* 329 */
  DUMMY(329),
  #endif
  #endif

  #ifdef APP_SPI_CSIG3_SLAVE_ISR_ON
  /* 330 */
  APP_SPI_CSIG3_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIG3_TIR_ISR_API == STD_ON)
  /* 330 */
  SPI_CSIG3_TIR_ISR,
  #else
  /* 330 */
  DUMMY(330),
  #endif
  #endif
  /* 331 */
  DUMMY(331),
  DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef SPI_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         WDG F1KM-S1 IVT                                   */
/*****************************************************************************/
#ifdef WDG_MODULE_TEST
void (*IntVectors[])(void) = {

  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039),

/* 40 */
  #ifdef WDG_DRIVERA_INTERRUPT_ENABLE
  #ifndef Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR
  WDG_59_DRIVERA_TRIGGERFUNCTION_ISR,
  #else
 /* 40 */

 App_Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR,
  #endif
  #else
  DUMMY(040),
  #endif
/* 41 */

  #ifdef WDG_DRIVERB_INTERRUPT_ENABLE
  WDG_59_DRIVERB_TRIGGERFUNCTION_ISR,
  #else
  DUMMY(041),
  #endif
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef WDG_MODULE_TEST */
#endif

/*****************************************************************************/
/*               GLOBAL SAMPLE APPLICATION F1KM-S1 IVT                       */
/*****************************************************************************/
#ifdef GLOBAL_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357)
};
/* End of #ifdef GLOBAL_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         End of F1KM-S1 IVT                                */
/*****************************************************************************/



/*****************************************************************************/
/*****************************************************************************/
/*                         F1KM-S4 IVT                                       */
/*****************************************************************************/
/*****************************************************************************/
/* Continue: #ifdef F1KM_S1_DEVICE */
#elif defined F1KM_S4_DEVICE
#pragma ghs section sdata=".inttable"

/*****************************************************************************/
/*                         ADC F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef ADC_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),

  /*018*/
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG1_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG1_CAT2_ISR) || defined (ADC0_SG1_CAT2_ISR)
        App_Os_ADC0_SG1_ISR,
      #else
        ADC0_SG1_ISR,
      #endif
    #else
      DUMMY(018),
    #endif /* #if (ADC0_SG1_ISR_API == STD_ON) */
  #else
    DUMMY(018),
  #endif
  /* 019 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG2_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG2_CAT2_ISR) || defined (ADC0_SG2_CAT2_ISR)
        App_Os_ADC0_SG2_ISR,
      #else
        ADC0_SG2_ISR,
      #endif
    #else
      DUMMY(019),
    #endif
  #else
    DUMMY(019),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
  /* 020 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG3_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG3_CAT2_ISR) || defined (ADC0_SG3_CAT2_ISR)
        App_Os_ADC0_SG3_ISR,
      #else
        ADC0_SG3_ISR,
      #endif
    #else
      DUMMY(020),
    #endif /* #if (ADC0_SG3_ISR_API == STD_ON) */
  #else
    DUMMY(020),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050),

  /*051*/
  #if defined ADC_TEST_APP_CFG41
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG51
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG44
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG45
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG39
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG61
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG77
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG80
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG81
    TAUD0_CH7_Isr,
  #else
    DUMMY(051),
  #endif

  DUMMY(052), DUMMY(053),
  DUMMY(054),

  /*055*/
  #if defined ADC_TEST_APP_CFG80
    TAUD0_CH15_Isr,
  #elif defined ADC_TEST_APP_CFG81
    TAUD0_CH15_Isr,
  #else
  DUMMY(055),/* Adc_Timer_1, */
  #endif
  /*056 */
  /* ADC_0 Error Interrupt */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC_ERROR_SUPPORT == STD_ON)
      #if defined (Os_ADC0_ERR_CAT2_ISR) || defined (ADC0_ERR_CAT2_ISR)
        App_Os_ADC0_ERR_ISR,
      #else
        ADC0_ERR_ISR,
      #endif
    #else
      DUMMY(056),
    #endif /*#if (ADC_ERROR_SUPPORT == STD_ON)*/
  #else
    DUMMY(056),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(057), DUMMY(058), DUMMY(059),

/* 60 */
  #if (ADC_DMA_ISR_CH00_API == STD_ON)
    #if defined (OS_ADC_DMA_CH00_CAT2_ISR) || defined (ADC_DMA_CH00_CAT2_ISR)
      App_Os_ADC_DMA_CH00_ISR,
    #else
      ADC_DMA_CH00_ISR,
    #endif
  #else
    DUMMY(060),
  #endif
/* 61 */
  #if (ADC_DMA_ISR_CH01_API == STD_ON)
    ADC_DMA_CH01_ISR,
  #else
   DUMMY(061),
  #endif
/* 62 */
  #if (ADC_DMA_ISR_CH02_API == STD_ON)
    ADC_DMA_CH02_ISR,
  #else
    DUMMY(062),
  #endif
/* 63 */
  #if (ADC_DMA_ISR_CH03_API == STD_ON)
    ADC_DMA_CH03_ISR,
  #else
   DUMMY(063),
  #endif
/* 64 */
  #if (ADC_DMA_ISR_CH04_API == STD_ON)
    ADC_DMA_CH04_ISR,
  #else
    DUMMY(064),
  #endif
/* 65 */
  #if (ADC_DMA_ISR_CH05_API == STD_ON)
    ADC_DMA_CH05_ISR,
  #else
    DUMMY(065),
  #endif
/* 66 */
  #if (ADC_DMA_ISR_CH06_API == STD_ON)
    ADC_DMA_CH06_ISR,
  #else
    DUMMY(066),
  #endif
/* 67 */
  #if (ADC_DMA_ISR_CH07_API == STD_ON)
    ADC_DMA_CH07_ISR,
  #else
    DUMMY(067),
  #endif
/* 68 */
  #if (ADC_DMA_ISR_CH08_API == STD_ON)
    ADC_DMA_CH08_ISR,
  #else
    DUMMY(068),
  #endif
/* 69 */
  #if (ADC_DMA_ISR_CH04_API == STD_ON)
    ADC_DMA_CH09_ISR,
  #else
   DUMMY(069),
  #endif
/* 70 */
  #if (ADC_DMA_ISR_CH10_API == STD_ON)
    ADC_DMA_CH10_ISR,
  #else
    DUMMY(070),
  #endif
/* 71 */
  #if (ADC_DMA_ISR_CH11_API == STD_ON)
    ADC_DMA_CH11_ISR,
  #else
    DUMMY(071),
  #endif
/* 72 */
  #if (ADC_DMA_ISR_CH12_API == STD_ON)
    ADC_DMA_CH12_ISR,
  #else
    DUMMY(072),
  #endif
/* 73 */
  #if (ADC_DMA_ISR_CH13_API == STD_ON)
    ADC_DMA_CH13_ISR,
  #else
    DUMMY(073),
  #endif
/* 74 */
  #if (ADC_DMA_ISR_CH14_API == STD_ON)
    ADC_DMA_CH14_ISR,
  #else
    DUMMY(074),
  #endif
/* 75 */
  #if (ADC_DMA_ISR_CH15_API == STD_ON)
    ADC_DMA_CH15_ISR,
  #else
    DUMMY(075),
  #endif

  DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082),

  /* 83 */ /* Adc_Timer_1, */
  #if defined ADC_TEST_APP_CFG39
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG61
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG77
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG80
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG81
    TAUJ0_CH03_Isr,
  #else
    DUMMY(083), /* Adc_Timer_1, */
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090),

  /* 91 */
  #if (ADC_PWSA_INT_QFULL_ISR == STD_ON)
    PWSA_QUE_ISR,
  #else
  DUMMY(091),
  #endif

  DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211),


/* 212 */
  /* ADC_1 Error Interrupt */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC_ERROR_SUPPORT == STD_ON)
      #if defined (Os_ADC1_ERR_CAT2_ISR) || defined (ADC1_ERR_CAT2_ISR)
        App_Os_ADC1_ERR_ISR,
      #else
        ADC1_ERR_ISR,
      #endif
    #else
      DUMMY(212),
    #endif /*#if (ADC_ERROR_SUPPORT == STD_ON)*/
  #else
    DUMMY(212),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
/* 213 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC1_SG1_ISR_API == STD_ON)
      #if defined (Os_ADC1_SG1_CAT2_ISR) || defined (ADC1_SG1_CAT2_ISR)
         App_Os_ADC1_SG1_ISR,
      #else
         ADC1_SG1_ISR,
      #endif
    #else
      DUMMY(213),
    #endif
  #else
    DUMMY(213),
  #endif
/* 214 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC1_SG2_ISR_API == STD_ON)
      #if defined (Os_ADC1_SG2_CAT2_ISR) || defined (ADC1_SG2_CAT2_ISR)
        App_Os_ADC1_SG2_ISR,
      #else
        ADC1_SG2_ISR,
      #endif
    #else
      DUMMY(214),
    #endif
  #else
    DUMMY(214),
  #endif
/* 215 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC1_SG3_ISR_API == STD_ON)
      #if defined (Os_ADC1_SG3_CAT2_ISR) || defined (ADC1_SG3_CAT2_ISR)
        App_Os_ADC1_SG3_ISR,
      #else
        ADC1_SG3_ISR,
      #endif
    #else
      DUMMY(215),
    #endif
  #else
    DUMMY(215),
  #endif

  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297),

/* 298 */
  #if (ADC_DMA_ISR_CH16_API == STD_ON)
    ADC_DMA_CH16_ISR,
  #else
    DUMMY(298),
  #endif
/* 299 */
  #if (ADC_DMA_ISR_CH17_API == STD_ON)
    ADC_DMA_CH17_ISR,
  #else
    DUMMY(299),
  #endif
/* 300 */
  #if (ADC_DMA_ISR_CH18_API == STD_ON)
    ADC_DMA_CH18_ISR,
  #else
    DUMMY(300),
  #endif
/* 301 */
  #if (ADC_DMA_ISR_CH19_API == STD_ON)
    ADC_DMA_CH19_ISR,
  #else
    DUMMY(301),
  #endif
/* 302 */
  #if (ADC_DMA_ISR_CH20_API == STD_ON)
    ADC_DMA_CH20_ISR,
  #else
    DUMMY(302),
  #endif
/* 303 */
  #if (ADC_DMA_ISR_CH21_API == STD_ON)
    ADC_DMA_CH21_ISR,
  #else
    DUMMY(303),
  #endif
/* 304 */
  #if (ADC_DMA_ISR_CH22_API == STD_ON)
    ADC_DMA_CH22_ISR,
  #else
    DUMMY(304),
  #endif
/* 305 */
  #if (ADC_DMA_ISR_CH23_API == STD_ON)
    ADC_DMA_CH23_ISR,
  #else
    DUMMY(305),
  #endif
/* 306 */
  #if (ADC_DMA_ISR_CH24_API == STD_ON)
    ADC_DMA_CH24_ISR,
  #else
    DUMMY(306),
  #endif
/* 307 */
  #if (ADC_DMA_ISR_CH25_API == STD_ON)
    ADC_DMA_CH25_ISR,
  #else
    DUMMY(307),
  #endif
/* 308 */
  #if (ADC_DMA_ISR_CH26_API == STD_ON)
    ADC_DMA_CH26_ISR,
  #else
    DUMMY(308),
  #endif
/* 309 */
  #if (ADC_DMA_ISR_CH27_API == STD_ON)
    ADC_DMA_CH27_ISR,
  #else
    DUMMY(309),
  #endif
/* 310 */
  #if (ADC_DMA_ISR_CH28_API == STD_ON)
    ADC_DMA_CH28_ISR,
  #else
    DUMMY(310),
  #endif
/* 311 */
  #if (ADC_DMA_ISR_CH29_API == STD_ON)
    ADC_DMA_CH29_ISR,
  #else
    DUMMY(311),
  #endif
/* 312 */
  #if (ADC_DMA_ISR_CH30_API == STD_ON)
    ADC_DMA_CH30_ISR,
  #else
    DUMMY(312),
  #endif
/* 313 */
  #if (ADC_DMA_ISR_CH31_API == STD_ON)
    ADC_DMA_CH31_ISR,
  #else
    DUMMY(313),
  #endif

  DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef ADC_MODULE_TEST */
#endif

#pragma ghs section sdata=".inttable"

/*****************************************************************************/
/*                         CAN Interrupt Vector Table                        */
/*****************************************************************************/
#if defined (CAN_MODULE_TEST) && (CAN_ISR_CATEGORY_2 == STD_OFF)
#define INT_VECTOR_051 Timer0_Interrupt
#if(defined(F1KM) && defined(CAN_TEST_APP) && defined(smoketst))
#define INT_VECTOR_084 OSTM0_Interrupt
#endif
#if (CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON)
#ifndef Os_CAN_RSCAN0_RXFIFO_CAT2_ISR
#define INT_VECTOR_023 CAN_RSCAN0_RXFIFO_ISR /* 023 */
#else
#define INT_VECTOR_023 App_Os_CONTROLLER_RXFIFO0_ISR /* 023 */
#endif
#endif
#if (CAN_CONTROLLER0_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER0_BUSOFF_CAT2_ISR
#define INT_VECTOR_024  CAN_CONTROLLER0_BUSOFF_ISR /* 024 */
#else
#define INT_VECTOR_024 App_Os_CONTROLLER0_BUSOFF_ISR /* 024 */
#endif
#endif
#if (CAN_CONTROLLER0_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER0_RX_CAT2_ISR
#define INT_VECTOR_025  CAN_CONTROLLER0_RX_ISR /* 025 */
#else
#define INT_VECTOR_025 App_Os_CONTROLLER0_RX_ISR /* 025 */
#endif
#endif
#if (CAN_CONTROLLER0_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER0_TX_CAT2_ISR
#define INT_VECTOR_026  CAN_CONTROLLER0_TX_ISR /* 026 */
#else
#define INT_VECTOR_026 App_Os_CONTROLLER0_TX_ISR /* 026 */
#endif
#endif
#if ((CAN_CONTROLLER0_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER0_WAKEUP_CAT2_ISR
#define INT_VECTOR_037  CAN_CONTROLLER0_WAKEUP_ISR /* 037 */
#else
#define INT_VECTOR_037 App_Os_WAKEUP0_ISR /* 037 */
#endif
#endif
#if (CAN_CONTROLLER1_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER1_BUSOFF_CAT2_ISR
#define INT_VECTOR_113  CAN_CONTROLLER1_BUSOFF_ISR /* 113 */
#else
#define INT_VECTOR_113 App_Os_CONTROLLER1_BUSOFF_ISR /* 113 */
#endif
#endif
#if (CAN_CONTROLLER1_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER1_RX_CAT2_ISR
#define INT_VECTOR_114  CAN_CONTROLLER1_RX_ISR /* 114 */
#else
#define INT_VECTOR_114 App_Os_CONTROLLER1_RX_ISR /* 114 */
#endif
#endif
#if (CAN_CONTROLLER1_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER1_TX_CAT2_ISR
#define INT_VECTOR_115  CAN_CONTROLLER1_TX_ISR /* 115 */
#else
#define INT_VECTOR_115 App_Os_CONTROLLER1_TX_ISR /* 115 */
#endif
#endif
#if ((CAN_CONTROLLER1_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER1_WAKEUP_CAT2_ISR
#define INT_VECTOR_038  CAN_CONTROLLER1_WAKEUP_ISR /* 038 */
#else
#define INT_VECTOR_038 App_Os_WAKEUP1_ISR /* 038 */
#endif
#endif
#if (CAN_CONTROLLER2_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER2_BUSOFF_CAT2_ISR
#define INT_VECTOR_217  CAN_CONTROLLER2_BUSOFF_ISR /* 217 */
#else
#define INT_VECTOR_217  App_Os_CONTROLLER2_BUSOFF_ISR /* 217 */
#endif
#endif
#if (CAN_CONTROLLER2_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER2_RX_CAT2_ISR
#define INT_VECTOR_218  CAN_CONTROLLER2_RX_ISR /* 218 */
#else
#define INT_VECTOR_218  App_Os_CONTROLLER2_RX_ISR /* 218 */
#endif
#endif
#if (CAN_CONTROLLER2_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER2_TX_CAT2_ISR
#define INT_VECTOR_219  CAN_CONTROLLER2_TX_ISR /* 219 */
#else
#define INT_VECTOR_219  App_Os_CONTROLLER2_TX_ISR /* 219 */
#endif
#endif
#if ((CAN_CONTROLLER2_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER2_WAKEUP_CAT2_ISR
#define INT_VECTOR_039  CAN_CONTROLLER2_WAKEUP_ISR /* 039 */
#else
#define INT_VECTOR_039  App_Os_WAKEUP2_ISR /* 039 */
#endif
#endif
#if (CAN_CONTROLLER3_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER3_BUSOFF_CAT2_ISR
#define INT_VECTOR_220  CAN_CONTROLLER3_BUSOFF_ISR /* 220 */
#else
#define INT_VECTOR_220  App_Os_CONTROLLER3_BUSOFF_ISR /* 220 */
#endif
#endif
#if (CAN_CONTROLLER3_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER3_RX_CAT2_ISR
#define INT_VECTOR_221  CAN_CONTROLLER3_RX_ISR /* 221 */
#else
#define INT_VECTOR_221  App_Os_CONTROLLER3_RX_ISR /* 221 */
#endif
#endif
#if (CAN_CONTROLLER3_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER3_TX_CAT2_ISR
#define INT_VECTOR_222  CAN_CONTROLLER3_TX_ISR /* 222 */
#else
#define INT_VECTOR_222  App_Os_CONTROLLER3_TX_ISR /* 222 */
#endif
#endif
#if ((CAN_CONTROLLER3_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER3_WAKEUP_CAT2_ISR
#define INT_VECTOR_043  CAN_CONTROLLER3_WAKEUP_ISR /* 043 */
#else
#define INT_VECTOR_043  App_Os_WAKEUP3_ISR /* 043 */
#endif
#endif
#if (CAN_CONTROLLER4_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER4_BUSOFF_CAT2_ISR
#define INT_VECTOR_272  CAN_CONTROLLER4_BUSOFF_ISR /* 272 */
#else
#define INT_VECTOR_272  App_Os_CONTROLLER4_BUSOFF_ISR /* 272 */
#endif
#endif
#if (CAN_CONTROLLER4_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER4_RX_CAT2_ISR
#define INT_VECTOR_273  CAN_CONTROLLER4_RX_ISR /* 273 */
#else
#define INT_VECTOR_273  App_Os_CONTROLLER4_RX_ISR /* 273 */
#endif
#endif
#if (CAN_CONTROLLER4_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER4_TX_CAT2_ISR
#define INT_VECTOR_274  CAN_CONTROLLER4_TX_ISR /* 274 */
#else
#define INT_VECTOR_274  App_Os_CONTROLLER4_TX_ISR /* 274 */
#endif
#endif
#if ((CAN_CONTROLLER4_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER4_WAKEUP_CAT2_ISR
#define INT_VECTOR_044  CAN_CONTROLLER4_WAKEUP_ISR /* 044 */
#else
#define INT_VECTOR_044  App_Os_WAKEUP4_ISR /* 044 */
#endif
#endif
#if (CAN_CONTROLLER5_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER5_BUSOFF_CAT2_ISR
#define INT_VECTOR_287  CAN_CONTROLLER5_BUSOFF_ISR /* 287 */
#else
#define INT_VECTOR_287  App_Os_CONTROLLER5_BUSOFF_ISR /* 287 */
#endif
#endif
#if (CAN_CONTROLLER5_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER5_RX_CAT2_ISR
#define INT_VECTOR_288  CAN_CONTROLLER5_RX_ISR /* 288 */
#else
#define INT_VECTOR_288  App_Os_CONTROLLER5_RX_ISR /* 288 */
#endif
#endif
#if (CAN_CONTROLLER5_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER5_TX_CAT2_ISR
#define INT_VECTOR_289  CAN_CONTROLLER5_TX_ISR /* 289 */
#else
#define INT_VECTOR_289  App_Os_CONTROLLER5_TX_ISR /* 289 */
#endif
#endif
#if ((CAN_CONTROLLER5_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER5_WAKEUP_CAT2_ISR
#define INT_VECTOR_045  CAN_CONTROLLER5_WAKEUP_ISR /* 045 */
#else
#define INT_VECTOR_045  App_Os_WAKEUP5_ISR /* 045 */
#endif
#endif
#if (CAN_CONTROLLER6_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER6_BUSOFF_CAT2_ISR
#define INT_VECTOR_321  CAN_CONTROLLER6_BUSOFF_ISR /* 321 */
#else
#define INT_VECTOR_321  App_Os_CONTROLLER6_BUSOFF_ISR /* 321 */
#endif
#endif
#if (CAN_CONTROLLER6_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER6_RX_CAT2_ISR
#define INT_VECTOR_322  CAN_CONTROLLER6_RX_ISR /* 322 */
#else
#define INT_VECTOR_322  App_Os_CONTROLLER6_RX_ISR /* 322 */
#endif
#endif
#if (CAN_CONTROLLER6_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER6_TX_CAT2_ISR
#define INT_VECTOR_323  CAN_CONTROLLER6_TX_ISR /* 323 */
#else
#define INT_VECTOR_323  App_Os_CONTROLLER6_TX_ISR /* 323 */
#endif
#endif
#if ((CAN_CONTROLLER6_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER6_WAKEUP_CAT2_ISR
#define INT_VECTOR_128  CAN_CONTROLLER6_WAKEUP_ISR /* 128 */
#else
#define INT_VECTOR_128  App_Os_WAKEUP6_ISR /* 128 */
#endif
#endif
#if (CAN_CONTROLLER7_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER7_BUSOFF_CAT2_ISR
#define INT_VECTOR_332  CAN_CONTROLLER7_BUSOFF_ISR /* 332 */
#else
#define INT_VECTOR_332  App_Os_CONTROLLER7_BUSOFF_ISR /* 332 */
#endif
#endif
#if (CAN_CONTROLLER7_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER7_RX_CAT2_ISR
#define INT_VECTOR_333  CAN_CONTROLLER7_RX_ISR /* 333 */
#else
#define INT_VECTOR_333  App_Os_CONTROLLER7_RX_ISR /* 333 */
#endif
#endif
#if (CAN_CONTROLLER7_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER7_TX_CAT2_ISR
#define INT_VECTOR_334  CAN_CONTROLLER7_TX_ISR /* 334 */
#else
#define INT_VECTOR_334  App_Os_CONTROLLER7_TX_ISR /* 334 */
#endif
#endif
#if ((CAN_CONTROLLER7_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER7_WAKEUP_CAT2_ISR
#define INT_VECTOR_205  CAN_CONTROLLER7_WAKEUP_ISR /* 205 */
#else
#define INT_VECTOR_205  App_Os_WAKEUP7_ISR /* 205 */
#endif
#endif

/*****************************************************************************/
/*                         Interrupt Vector Table                            */
/*****************************************************************************/
#pragma ghs section sdata=".inttable"
void (*IntVectors[])(void) = {
#ifdef INT_VECTOR_000
  INT_VECTOR_000, /* 000 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_001
  INT_VECTOR_001, /* 001 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_002
  INT_VECTOR_002, /* 002 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_003
  INT_VECTOR_003, /* 003 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_004
  INT_VECTOR_004, /* 004 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_005
  INT_VECTOR_005, /* 005 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_006
  INT_VECTOR_006, /* 006 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_007
  INT_VECTOR_007, /* 007 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_008
  INT_VECTOR_008, /* 008 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_009
  INT_VECTOR_009, /* 009 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_010
  INT_VECTOR_010, /* 010 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_011
  INT_VECTOR_011, /* 011 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_012
  INT_VECTOR_012, /* 012 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_013
  INT_VECTOR_013, /* 013 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_014
  INT_VECTOR_014, /* 014 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_015
  INT_VECTOR_015, /* 015 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_016
  INT_VECTOR_016, /* 016 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_017
  INT_VECTOR_017, /* 017 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_018
  INT_VECTOR_018, /* 018 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_019
  INT_VECTOR_019, /* 019 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_020
  INT_VECTOR_020, /* 020 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_021
  INT_VECTOR_021, /* 021 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_022
  INT_VECTOR_022, /* 022 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_023
  INT_VECTOR_023, /* 023 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_024
  INT_VECTOR_024, /* 024 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_025
  INT_VECTOR_025, /* 025 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_026
  INT_VECTOR_026, /* 026 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_027
  INT_VECTOR_027, /* 027 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_028
  INT_VECTOR_028, /* 028 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_029
  INT_VECTOR_029, /* 029 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_030
  INT_VECTOR_030, /* 030 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_031
  INT_VECTOR_031, /* 031 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_032
  INT_VECTOR_032, /* 032 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_033
  INT_VECTOR_033, /* 033 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_034
  INT_VECTOR_034, /* 034 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_035
  INT_VECTOR_035, /* 035 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_036
  INT_VECTOR_036, /* 036 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_037
  INT_VECTOR_037, /* 037 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_038
  INT_VECTOR_038, /* 038 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_039
  INT_VECTOR_039, /* 039 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_040
  INT_VECTOR_040, /* 040 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_041
  INT_VECTOR_041, /* 041 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_042
  INT_VECTOR_042, /* 042 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_043
  INT_VECTOR_043, /* 043 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_044
  INT_VECTOR_044, /* 044 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_045
  INT_VECTOR_045, /* 045 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_046
  INT_VECTOR_046, /* 046 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_047
  INT_VECTOR_047, /* 047 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_048
  INT_VECTOR_048, /* 048 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_049
  INT_VECTOR_049, /* 049 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_050
  INT_VECTOR_050, /* 050 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_051
  INT_VECTOR_051, /* 051 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_052
  INT_VECTOR_052, /* 052 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_053
  INT_VECTOR_053, /* 053 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_054
  INT_VECTOR_054, /* 054 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_055
  INT_VECTOR_055, /* 055 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_056
  INT_VECTOR_056, /* 056 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_057
  INT_VECTOR_057, /* 057 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_058
  INT_VECTOR_058, /* 058 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_059
  INT_VECTOR_059, /* 059 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_060
  INT_VECTOR_060, /* 060 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_061
  INT_VECTOR_061, /* 061 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_062
  INT_VECTOR_062, /* 062 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_063
  INT_VECTOR_063, /* 063 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_064
  INT_VECTOR_064, /* 064 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_065
  INT_VECTOR_065, /* 065 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_066
  INT_VECTOR_066, /* 066 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_067
  INT_VECTOR_067, /* 067 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_068
  INT_VECTOR_068, /* 068 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_069
  INT_VECTOR_069, /* 069 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_070
  INT_VECTOR_070, /* 070 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_071
  INT_VECTOR_071, /* 071 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_072
  INT_VECTOR_072, /* 072 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_073
  INT_VECTOR_073, /* 073 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_074
  INT_VECTOR_074, /* 074 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_075
  INT_VECTOR_075, /* 075 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_076
  INT_VECTOR_076, /* 076 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_077
  INT_VECTOR_077, /* 077 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_078
  INT_VECTOR_078, /* 078 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_079
  INT_VECTOR_079, /* 079 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_080
  INT_VECTOR_080, /* 080 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_081
  INT_VECTOR_081, /* 081 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_082
  INT_VECTOR_082, /* 082 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_083
  INT_VECTOR_083, /* 083 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_084
  INT_VECTOR_084, /* 084 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_085
  INT_VECTOR_085, /* 085 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_086
  INT_VECTOR_086, /* 086 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_087
  INT_VECTOR_087, /* 087 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_088
  INT_VECTOR_088, /* 088 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_089
  INT_VECTOR_089, /* 089 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_090
  INT_VECTOR_090, /* 090 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_091
  INT_VECTOR_091, /* 091 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_092
  INT_VECTOR_092, /* 092 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_093
  INT_VECTOR_093, /* 093 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_094
  INT_VECTOR_094, /* 094 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_095
  INT_VECTOR_095, /* 095 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_096
  INT_VECTOR_096, /* 096 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_097
  INT_VECTOR_097, /* 097 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_098
  INT_VECTOR_098, /* 098 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_099
  INT_VECTOR_099, /* 099 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_100
  INT_VECTOR_100, /* 100 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_101
  INT_VECTOR_101, /* 101 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_102
  INT_VECTOR_102, /* 102 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_103
  INT_VECTOR_103, /* 103 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_104
  INT_VECTOR_104, /* 104 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_105
  INT_VECTOR_105, /* 105 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_106
  INT_VECTOR_106, /* 106 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_107
  INT_VECTOR_107, /* 107 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_108
  INT_VECTOR_108, /* 108 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_109
  INT_VECTOR_109, /* 109 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_110
  INT_VECTOR_110, /* 110 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_111
  INT_VECTOR_111, /* 111 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_112
  INT_VECTOR_112, /* 112 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_113
  INT_VECTOR_113, /* 113 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_114
  INT_VECTOR_114, /* 114 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_115
  INT_VECTOR_115, /* 115 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_116
  INT_VECTOR_116, /* 116 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_117
  INT_VECTOR_117, /* 117 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_118
  INT_VECTOR_118, /* 118 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_119
  INT_VECTOR_119, /* 119 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_120
  INT_VECTOR_120, /* 120 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_121
  INT_VECTOR_121, /* 121 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_122
  INT_VECTOR_122, /* 122 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_123
  INT_VECTOR_123, /* 123 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_124
  INT_VECTOR_124, /* 124 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_125
  INT_VECTOR_125, /* 125 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_126
  INT_VECTOR_126, /* 126 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_127
  INT_VECTOR_127, /* 127 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_128
  INT_VECTOR_128, /* 128 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_129
  INT_VECTOR_129, /* 129 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_130
  INT_VECTOR_130, /* 130 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_131
  INT_VECTOR_131, /* 131 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_132
  INT_VECTOR_132, /* 132 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_133
  INT_VECTOR_133, /* 133 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_134
  INT_VECTOR_134, /* 134 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_135
  INT_VECTOR_135, /* 135 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_136
  INT_VECTOR_136, /* 136 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_137
  INT_VECTOR_137, /* 137 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_138
  INT_VECTOR_138, /* 138 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_139
  INT_VECTOR_139, /* 139 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_140
  INT_VECTOR_140, /* 140 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_141
  INT_VECTOR_141, /* 141 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_142
  INT_VECTOR_142, /* 142 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_143
  INT_VECTOR_143, /* 143 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_144
  INT_VECTOR_144, /* 144 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_145
  INT_VECTOR_145, /* 145 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_146
  INT_VECTOR_146, /* 146 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_147
  INT_VECTOR_147, /* 147 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_148
  INT_VECTOR_148, /* 148 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_149
  INT_VECTOR_149, /* 149 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_150
  INT_VECTOR_150, /* 150 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_151
  INT_VECTOR_151, /* 151 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_152
  INT_VECTOR_152, /* 152 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_153
  INT_VECTOR_153, /* 153 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_154
  INT_VECTOR_154, /* 154 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_155
  INT_VECTOR_155, /* 155 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_156
  INT_VECTOR_156, /* 156 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_157
  INT_VECTOR_157, /* 157 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_158
  INT_VECTOR_158, /* 158 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_159
  INT_VECTOR_159, /* 159 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_160
  INT_VECTOR_160, /* 160 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_161
  INT_VECTOR_161, /* 161 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_162
  INT_VECTOR_162, /* 162 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_163
  INT_VECTOR_163, /* 163 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_164
  INT_VECTOR_164, /* 164 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_165
  INT_VECTOR_165, /* 165 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_166
  INT_VECTOR_166, /* 166 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_167
  INT_VECTOR_167, /* 167 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_168
  INT_VECTOR_168, /* 168 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_169
  INT_VECTOR_169, /* 169 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_170
  INT_VECTOR_170, /* 170 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_171
  INT_VECTOR_171, /* 171 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_172
  INT_VECTOR_172, /* 172 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_173
  INT_VECTOR_173, /* 173 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_174
  INT_VECTOR_174, /* 174 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_175
  INT_VECTOR_175, /* 175 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_176
  INT_VECTOR_176, /* 176 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_177
  INT_VECTOR_177, /* 177 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_178
  INT_VECTOR_178, /* 178 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_179
  INT_VECTOR_179, /* 179 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_180
  INT_VECTOR_180, /* 180 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_181
  INT_VECTOR_181, /* 181 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_182
  INT_VECTOR_182, /* 182 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_183
  INT_VECTOR_183, /* 183 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_184
  INT_VECTOR_184, /* 184 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_185
  INT_VECTOR_185, /* 185 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_186
  INT_VECTOR_186, /* 186 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_187
  INT_VECTOR_187, /* 187 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_188
  INT_VECTOR_188, /* 188 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_189
  INT_VECTOR_189, /* 189 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_190
  INT_VECTOR_190, /* 190 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_191
  INT_VECTOR_191, /* 191 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_192
  INT_VECTOR_192, /* 192 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_193
  INT_VECTOR_193, /* 193 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_194
  INT_VECTOR_194, /* 194 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_195
  INT_VECTOR_195, /* 195 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_196
  INT_VECTOR_196, /* 196 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_197
  INT_VECTOR_197, /* 197 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_198
  INT_VECTOR_198, /* 198 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_199
  INT_VECTOR_199, /* 199 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_200
  INT_VECTOR_200, /* 200 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_201
  INT_VECTOR_201, /* 201 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_202
  INT_VECTOR_202, /* 202 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_203
  INT_VECTOR_203, /* 203 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_204
  INT_VECTOR_204, /* 204 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_205
  INT_VECTOR_205, /* 205 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_206
  INT_VECTOR_206, /* 206 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_207
  INT_VECTOR_207, /* 207 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_208
  INT_VECTOR_208, /* 208 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_209
  INT_VECTOR_209, /* 209 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_210
  INT_VECTOR_210, /* 210 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_211
  INT_VECTOR_211, /* 211 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_212
  INT_VECTOR_212, /* 212 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_213
  INT_VECTOR_213, /* 213 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_214
  INT_VECTOR_214, /* 214 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_215
  INT_VECTOR_215, /* 215 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_216
  INT_VECTOR_216, /* 216 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_217
  INT_VECTOR_217, /* 217 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_218
  INT_VECTOR_218, /* 218 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_219
  INT_VECTOR_219, /* 219 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_220
  INT_VECTOR_220, /* 220 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_221
  INT_VECTOR_221, /* 221 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_222
  INT_VECTOR_222, /* 222 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_223
  INT_VECTOR_223, /* 223 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_224
  INT_VECTOR_224, /* 224 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_225
  INT_VECTOR_225, /* 225 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_226
  INT_VECTOR_226, /* 226 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_227
  INT_VECTOR_227, /* 227 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_228
  INT_VECTOR_228, /* 228 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_229
  INT_VECTOR_229, /* 229 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_230
  INT_VECTOR_230, /* 230 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_231
  INT_VECTOR_231, /* 231 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_232
  INT_VECTOR_232, /* 232 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_233
  INT_VECTOR_233, /* 233 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_234
  INT_VECTOR_234, /* 234 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_235
  INT_VECTOR_235, /* 235 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_236
  INT_VECTOR_236, /* 236 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_237
  INT_VECTOR_237, /* 237 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_238
  INT_VECTOR_238, /* 238 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_239
  INT_VECTOR_239, /* 239 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_240
  INT_VECTOR_240, /* 240 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_241
  INT_VECTOR_241, /* 241 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_242
  INT_VECTOR_242, /* 242 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_243
  INT_VECTOR_243, /* 243 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_244
  INT_VECTOR_244, /* 244 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_245
  INT_VECTOR_245, /* 245 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_246
  INT_VECTOR_246, /* 246 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_247
  INT_VECTOR_247, /* 247 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_248
  INT_VECTOR_248, /* 248 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_249
  INT_VECTOR_249, /* 249 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_250
  INT_VECTOR_250, /* 250 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_251
  INT_VECTOR_251, /* 251 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_252
  INT_VECTOR_252, /* 252 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_253
  INT_VECTOR_253, /* 253 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_254
  INT_VECTOR_254, /* 254 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_255
  INT_VECTOR_255, /* 255 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_256
  INT_VECTOR_256, /* 256 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_257
  INT_VECTOR_257, /* 257 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_258
  INT_VECTOR_258, /* 258 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_259
  INT_VECTOR_259, /* 259 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_260
  INT_VECTOR_260, /* 260 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_261
  INT_VECTOR_261, /* 261 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_262
  INT_VECTOR_262, /* 262 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_263
  INT_VECTOR_263, /* 263 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_264
  INT_VECTOR_264, /* 264 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_265
  INT_VECTOR_265, /* 265 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_266
  INT_VECTOR_266, /* 266 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_267
  INT_VECTOR_267, /* 267 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_268
  INT_VECTOR_268, /* 268 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_269
  INT_VECTOR_269, /* 269 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_270
  INT_VECTOR_270, /* 270 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_271
  INT_VECTOR_271, /* 271 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_272
  INT_VECTOR_272, /* 272 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_273
  INT_VECTOR_273, /* 273 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_274
  INT_VECTOR_274, /* 274 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_275
  INT_VECTOR_275, /* 275 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_276
  INT_VECTOR_276, /* 276 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_277
  INT_VECTOR_277, /* 277 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_278
  INT_VECTOR_278, /* 278 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_279
  INT_VECTOR_279, /* 279 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_280
  INT_VECTOR_280, /* 280 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_281
  INT_VECTOR_281, /* 281 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_282
  INT_VECTOR_282, /* 282 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_283
  INT_VECTOR_283, /* 283 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_284
  INT_VECTOR_284, /* 284 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_285
  INT_VECTOR_285, /* 285 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_286
  INT_VECTOR_286, /* 286 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_287
  INT_VECTOR_287, /* 287 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_288
  INT_VECTOR_288, /* 288 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_289
  INT_VECTOR_289, /* 289 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_290
  INT_VECTOR_290, /* 290 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_291
  INT_VECTOR_291, /* 291 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_292
  INT_VECTOR_292, /* 292 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_293
  INT_VECTOR_293, /* 293 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_294
  INT_VECTOR_294, /* 294 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_295
  INT_VECTOR_295, /* 295 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_296
  INT_VECTOR_296, /* 296 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_297
  INT_VECTOR_297, /* 297 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_298
  INT_VECTOR_298, /* 298 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_299
  INT_VECTOR_299, /* 299 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_300
  INT_VECTOR_300, /* 300 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_301
  INT_VECTOR_301, /* 301 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_302
  INT_VECTOR_302, /* 302 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_303
  INT_VECTOR_303, /* 303 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_304
  INT_VECTOR_304, /* 304 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_305
  INT_VECTOR_305, /* 305 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_306
  INT_VECTOR_306, /* 306 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_307
  INT_VECTOR_307, /* 307 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_308
  INT_VECTOR_308, /* 308 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_309
  INT_VECTOR_309, /* 309 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_310
  INT_VECTOR_310, /* 310 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_311
  INT_VECTOR_311, /* 311 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_312
  INT_VECTOR_312, /* 312 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_313
  INT_VECTOR_313, /* 313 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_314
  INT_VECTOR_314, /* 314 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_315
  INT_VECTOR_315, /* 315 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_316
  INT_VECTOR_316, /* 316 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_317
  INT_VECTOR_317, /* 317 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_318
  INT_VECTOR_318, /* 318 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_319
  INT_VECTOR_319, /* 319 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_320
  INT_VECTOR_320, /* 320 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_321
  INT_VECTOR_321, /* 321 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_322
  INT_VECTOR_322, /* 322 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_323
  INT_VECTOR_323, /* 323 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_324
  INT_VECTOR_324, /* 324 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_325
  INT_VECTOR_325, /* 325 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_326
  INT_VECTOR_326, /* 326 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_327
  INT_VECTOR_327, /* 327 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_328
  INT_VECTOR_328, /* 328 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_329
  INT_VECTOR_329, /* 329 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_330
  INT_VECTOR_330, /* 330 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_331
  INT_VECTOR_331, /* 331 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_332
  INT_VECTOR_332, /* 332 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_333
  INT_VECTOR_333, /* 333 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_334
  INT_VECTOR_334, /* 334 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_335
  INT_VECTOR_335, /* 335 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_336
  INT_VECTOR_336, /* 336 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_337
  INT_VECTOR_337, /* 337 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_338
  INT_VECTOR_338, /* 338 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_339
  INT_VECTOR_339, /* 339 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_340
  INT_VECTOR_340, /* 340 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_341
  INT_VECTOR_341, /* 341 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_342
  INT_VECTOR_342, /* 342 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_343
  INT_VECTOR_343, /* 343 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_344
  INT_VECTOR_344, /* 344 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_345
  INT_VECTOR_345, /* 345 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_346
  INT_VECTOR_346, /* 346 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_347
  INT_VECTOR_347, /* 347 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_348
  INT_VECTOR_348, /* 348 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_349
  INT_VECTOR_349, /* 349 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_350
  INT_VECTOR_350, /* 350 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_351
  INT_VECTOR_351, /* 351 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_352
  INT_VECTOR_352, /* 352 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_353
  INT_VECTOR_353, /* 353 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_354
  INT_VECTOR_354, /* 354 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_355
  INT_VECTOR_355, /* 355 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_356
  INT_VECTOR_356, /* 356 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_357
  INT_VECTOR_357 /* 357 */
#else
  Dummy_ISR
#endif
};
#pragma ghs section sdata=default
#endif

/*****************************************************************************/
/*                         CORTST F1KM-S4 IVT                                */
/*****************************************************************************/
#ifdef CORTST_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), Timer_Task, DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef CORTST_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         DIO F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef DIO_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef DIO_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         FLS F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef FLS_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  /* 60 */
  #if(FLS_DMA00_ISR_API == STD_ON)
    FLS_DMA00_ISR,
  #else
    DUMMY(060),
  #endif
  /* 61 */
  #if(FLS_DMA01_ISR_API == STD_ON)
    FLS_DMA01_ISR,
  #else
    DUMMY(061),
  #endif
  /* 62 */
  #if(FLS_DMA02_ISR_API == STD_ON)
    FLS_DMA02_ISR,
  #else
    DUMMY(062),
  #endif
  /* 63 */
  #if(FLS_DMA03_ISR_API == STD_ON)
    FLS_DMA03_ISR,
  #else
    DUMMY(063),
  #endif
  /* 64 */
  #if(FLS_DMA04_ISR_API == STD_ON)
    FLS_DMA04_ISR,
  #else
    DUMMY(064),
  #endif
  /* 65 */
  #if(FLS_DMA05_ISR_API == STD_ON)
    FLS_DMA05_ISR,
  #else
    DUMMY(065),
  #endif
  /* 66 */
  #if(FLS_DMA06_ISR_API == STD_ON)
    FLS_DMA06_ISR,
  #else
    DUMMY(066),
  #endif
  /* 67 */
  #if(FLS_DMA07_ISR_API == STD_ON)
    FLS_DMA07_ISR,
  #else
    DUMMY(067),
  #endif
  /* 68 */
  #if(FLS_DMA08_ISR_API == STD_ON)
    FLS_DMA08_ISR,
  #else
    DUMMY(068),
  #endif
  /* 69 */
  #if(FLS_DMA09_ISR_API == STD_ON)
    FLS_DMA09_ISR,
  #else
   DUMMY(069),
  #endif
  /* 70 */
  #if(FLS_DMA10_ISR_API == STD_ON)
    FLS_DMA10_ISR,
  #else
    DUMMY(070),
  #endif
  /* 71 */
  #if(FLS_DMA11_ISR_API == STD_ON)
    FLS_DMA11_ISR,
  #else
    DUMMY(071),
  #endif
  /* 72 */
  #if(FLS_DMA12_ISR_API == STD_ON)
    FLS_DMA12_ISR,
  #else
   DUMMY(072),
  #endif
  /* 73 */
  #if(FLS_DMA13_ISR_API == STD_ON)
    FLS_DMA13_ISR,
  #else
    DUMMY(073),
  #endif
  /* 74 */
  #if(FLS_DMA14_ISR_API == STD_ON)
    FLS_DMA14_ISR,
  #else
    DUMMY(074),
  #endif
  /* 75 */
  #if(FLS_DMA15_ISR_API == STD_ON)
    FLS_DMA15_ISR,
  #else
    DUMMY(075),
  #endif
  DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110),
  #if(FLS_INTERRUPT_MODE == STD_ON)
   #ifdef Os_FLS_FLENDNM_CAT2_ISR
   /* 111 */
   App_Os_FLS_FLENDNM_ISR,
   #else
   /* 111 */
   FLS_FLENDNM_ISR,
   #endif
   #else
   /* 111 */
   DUMMY(111),
  #endif
  DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297),
  /* 298 */
  #if(FLS_DMA16_ISR_API == STD_ON)
    FLS_DMA16_ISR,
  #else
    DUMMY(298),
  #endif
  /* 299 */
  #if(FLS_DMA17_ISR_API == STD_ON)
    FLS_DMA17_ISR,
  #else
    DUMMY(299),
  #endif
  /* 300 */
  #if(FLS_DMA18_ISR_API == STD_ON)
    FLS_DMA18_ISR,
  #else
    DUMMY(300),
  #endif
  /* 301 */
  #if(FLS_DMA19_ISR_API == STD_ON)
    FLS_DMA19_ISR,
  #else
    DUMMY(301),
  #endif
  /* 302 */
  #if(FLS_DMA20_ISR_API == STD_ON)
    FLS_DMA20_ISR,
  #else
    DUMMY(302),
  #endif
  /* 303 */
  #if(FLS_DMA21_ISR_API == STD_ON)
    FLS_DMA21_ISR,
  #else
    DUMMY(303),
  #endif
  /* 304 */
  #if(FLS_DMA22_ISR_API == STD_ON)
    FLS_DMA22_ISR,
  #else
    DUMMY(304),
  #endif
  /* 305 */
  #if(FLS_DMA23_ISR_API == STD_ON)
    FLS_DMA23_ISR,
  #else
    DUMMY(305),
  #endif
  /* 306 */
  #if(FLS_DMA24_ISR_API == STD_ON)
    FLS_DMA24_ISR,
  #else
    DUMMY(306),
  #endif
  /* 307 */
  #if(FLS_DMA25_ISR_API == STD_ON)
    FLS_DMA25_ISR,
  #else
    DUMMY(307),
  #endif
  /* 308 */
  #if(FLS_DMA26_ISR_API == STD_ON)
    FLS_DMA26_ISR,
  #else
    DUMMY(308),
  #endif
  /* 309 */
  #if(FLS_DMA27_ISR_API == STD_ON)
    FLS_DMA27_ISR,
  #else
    DUMMY(309),
  #endif
  /* 310 */
  #if(FLS_DMA28_ISR_API == STD_ON)
    FLS_DMA28_ISR,
  #else
    DUMMY(310),
  #endif
  /* 311 */
  #if(FLS_DMA29_ISR_API == STD_ON)
    FLS_DMA29_ISR,
  #else
    DUMMY(311),
  #endif
  /* 312 */
  #if(FLS_DMA30_ISR_API == STD_ON)
    FLS_DMA30_ISR,
  #else
    DUMMY(312),
  #endif
  /* 313 */
  #if(FLS_DMA31_ISR_API == STD_ON)
    FLS_DMA31_ISR,
  #else
    DUMMY(313),
  #endif
  DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef FLS_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         FLSTST F1KM-S4 IVT                                */
/*****************************************************************************/
#ifdef FLSTST_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef FLSTST_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         FR F1KM-S4 IVT                                    */
/*****************************************************************************/
#ifdef FR_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  #ifdef FR_SAMPLE_TEST
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), INTFLXA0TIM0, DUMMY(182), INTFLXA0TIM2, DUMMY(184), DUMMY(185),
  #else
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), INTFLXA0FDA,
  INTFLXA0FW, INTFLXA0IQE, INTFLXA0IQF, INTFLXA0OT, INTFLXA0OW, INTFLXA0LINE0,
  INTFLXA0LINE1, INTFLXA0TIM0, DUMMY(182), INTFLXA0TIM2, DUMMY(184), DUMMY(185),
  #endif
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef FR_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         GPT F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef GPT_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (GPT_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
    #else
      App_Os_TAUD0_CH00_ISR,
    #endif
  #else
    DUMMY(008),
  #endif

  #if (GPT_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (GPT_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (GPT_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (GPT_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (GPT_TAUD0_CH10_ISR_API == STD_ON)
  TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (GPT_TAUD0_CH12_ISR_API == STD_ON)
  TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (GPT_TAUD0_CH14_ISR_API == STD_ON)
  TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),

   #if (GPT_TAUD0_CH01_ISR_API == STD_ON)
   TAUD0_CH01_ISR,
   #else
    DUMMY(048),
   #endif

   #if (GPT_TAUD0_CH03_ISR_API == STD_ON)
   TAUD0_CH03_ISR,
   #else
    DUMMY(049),
   #endif

   #if (GPT_TAUD0_CH05_ISR_API == STD_ON)
    TAUD0_CH05_ISR,
   #else
    DUMMY(050),
   #endif

   #if (GPT_TAUD0_CH07_ISR_API == STD_ON)
      #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
        TAUD0_CH07_ISR,
      #else
       App_Os_TAUD0_CH07_ISR,
      #endif
   #else
      DUMMY(051),
   #endif

  #if (GPT_TAUD0_CH09_ISR_API == STD_ON)
   TAUD0_CH09_ISR,
  #else
   DUMMY(052),
  #endif

  #if (GPT_TAUD0_CH11_ISR_API == STD_ON)
   TAUD0_CH11_ISR,
  #else
   DUMMY(053),
  #endif

  #if (GPT_TAUD0_CH13_ISR_API == STD_ON)
   TAUD0_CH13_ISR,
  #else
   DUMMY(054),
  #endif

  #if (GPT_TAUD0_CH15_ISR_API == STD_ON)
   TAUD0_CH15_ISR,
  #else
   DUMMY(055),
  #endif


  DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079),

  #if (GPT_TAUJ0_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUJ0_CH00_ISR,
    #else
      App_Os_TAUJ0_CH00_ISR,
    #endif
  #else
    DUMMY(080),
  #endif

  #if (GPT_TAUJ0_CH01_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUJ0_CH01_ISR,
    #else
      App_Os_TAUJ0_CH01_ISR,
    #endif
  #else
    DUMMY(081),
  #endif

  #if (GPT_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(082),
  #endif

  #if (GPT_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(083),
  #endif

  #if (GPT_OSTM0_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      OSTM0_CH00_ISR,
    #else
      App_Os_OSTM0_CH01_ISR,
    #endif
  #else
    DUMMY(084),
  #endif

  DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141),

  #if (GPT_TAUB0_CH00_ISR_API == STD_ON)
   TAUB0_CH00_ISR,
  #else
   DUMMY(142),
  #endif

  #if (GPT_TAUB0_CH01_ISR_API == STD_ON)
   TAUB0_CH01_ISR,
  #else
   DUMMY(143),
  #endif

  #if (GPT_TAUB0_CH02_ISR_API == STD_ON)
   TAUB0_CH02_ISR,
  #else
   DUMMY(144),
  #endif

  #if (GPT_TAUB0_CH03_ISR_API == STD_ON)
   TAUB0_CH03_ISR,
  #else
   DUMMY(145),
  #endif

  #if (GPT_TAUB0_CH04_ISR_API == STD_ON)
   TAUB0_CH04_ISR,
  #else
   DUMMY(146),
  #endif

  #if (GPT_TAUB0_CH05_ISR_API == STD_ON)
   TAUB0_CH05_ISR,
  #else
   DUMMY(147),
  #endif

  #if (GPT_TAUB0_CH06_ISR_API == STD_ON)
   TAUB0_CH06_ISR,
  #else
   DUMMY(148),
  #endif

  #if (GPT_TAUB0_CH07_ISR_API == STD_ON)
   TAUB0_CH07_ISR,
  #else
   DUMMY(149),
  #endif

  #if (GPT_TAUB0_CH08_ISR_API == STD_ON)
   TAUB0_CH08_ISR,
  #else
   DUMMY(150),
  #endif

  #if (GPT_TAUB0_CH09_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUB0_CH09_ISR,
    #else
      App_Os_TAUB0_CH09_ISR,
    #endif
  #else
    DUMMY(151),
  #endif

  #if (GPT_TAUB0_CH10_ISR_API == STD_ON)
   TAUB0_CH10_ISR,
  #else
    DUMMY(152),
  #endif

  #if (GPT_TAUB0_CH11_ISR_API == STD_ON)
   TAUB0_CH11_ISR,
  #else
    DUMMY(153),
  #endif

  #if (GPT_TAUB0_CH12_ISR_API == STD_ON)
   TAUB0_CH12_ISR,
  #else
    DUMMY(154),
  #endif

  #if (GPT_TAUB0_CH13_ISR_API == STD_ON)
   TAUB0_CH13_ISR,
  #else
    DUMMY(155),
  #endif

  #if (GPT_TAUB0_CH14_ISR_API == STD_ON)
   TAUB0_CH14_ISR,
  #else
    DUMMY(156),
  #endif

  #if (GPT_TAUB0_CH15_ISR_API == STD_ON)
   TAUB0_CH15_ISR,
  #else
    DUMMY(157),
  #endif

  DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),DUMMY(162), DUMMY(163),
  DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (GPT_TAUJ1_CH00_ISR_API == STD_ON)
   TAUJ1_CH00_ISR,
  #else
   DUMMY(168),
  #endif

  #if (GPT_TAUJ1_CH01_ISR_API == STD_ON)
   TAUJ1_CH01_ISR,
  #else
   DUMMY(169),
  #endif

  #if (GPT_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
   DUMMY(170),
  #endif

  #if (GPT_TAUJ1_CH03_ISR_API == STD_ON)
   TAUJ1_CH03_ISR,
  #else
   DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255),

  #if (GPT_TAUB1_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUB1_CH00_ISR,
    #else
      App_Os_TAUB1_CH00_ISR,
    #endif
  #else
     DUMMY(256),
  #endif

  #if (GPT_TAUB1_CH01_ISR_API == STD_ON)
    TAUB1_CH01_ISR,
  #else
    DUMMY(257),
  #endif

  #if (GPT_TAUB1_CH02_ISR_API == STD_ON)
    TAUB1_CH02_ISR,
  #else
    DUMMY(258),
  #endif

  #if (GPT_TAUB1_CH03_ISR_API == STD_ON)
    TAUB1_CH03_ISR,
  #else
    DUMMY(259),
  #endif

  #if (GPT_TAUB1_CH04_ISR_API == STD_ON)
    TAUB1_CH04_ISR,
  #else
    DUMMY(260),
  #endif

  #if (GPT_TAUB1_CH05_ISR_API == STD_ON)
    TAUB1_CH05_ISR,
  #else
    DUMMY(261),
  #endif

  #if (GPT_TAUB1_CH06_ISR_API == STD_ON)
    TAUB1_CH06_ISR,
  #else
    DUMMY(262),
  #endif

  #if (GPT_TAUB1_CH07_ISR_API == STD_ON)
    TAUB1_CH07_ISR,
  #else
    DUMMY(263),
  #endif

  #if (GPT_TAUB1_CH08_ISR_API == STD_ON)
   TAUB1_CH08_ISR,
  #else
   DUMMY(264),
  #endif

  #if (GPT_TAUB1_CH09_ISR_API == STD_ON)
    TAUB1_CH09_ISR,
  #else
    DUMMY(265),
  #endif

  #if (GPT_TAUB1_CH10_ISR_API == STD_ON)
    TAUB1_CH10_ISR,
  #else
    DUMMY(266),
  #endif

  #if (GPT_TAUB1_CH11_ISR_API == STD_ON)
    TAUB1_CH11_ISR,
  #else
    DUMMY(267),
  #endif

  #if (GPT_TAUB1_CH12_ISR_API == STD_ON)
    TAUB1_CH12_ISR,
  #else
    DUMMY(268),
  #endif

  #if (GPT_TAUB1_CH13_ISR_API == STD_ON)
   TAUB1_CH13_ISR,
  #else
   DUMMY(269),
  #endif

  #if (GPT_TAUB1_CH14_ISR_API == STD_ON)
    TAUB1_CH14_ISR,
  #else
    DUMMY(270),
  #endif

  #if (GPT_TAUB1_CH15_ISR_API == STD_ON)
    TAUB1_CH15_ISR,
  #else
    DUMMY(271),
  #endif

  DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275), DUMMY(276),

  #if (GPT_TAUJ2_CH00_ISR_API == STD_ON)
    TAUJ2_CH00_ISR,
  #else
    DUMMY(277),
  #endif

  #if (GPT_TAUJ2_CH01_ISR_API == STD_ON)
    TAUJ2_CH01_ISR,
  #else
    DUMMY(278),
  #endif

  #if (GPT_TAUJ2_CH02_ISR_API == STD_ON)
    TAUJ2_CH02_ISR,
  #else
    DUMMY(279),
  #endif

  #if (GPT_TAUJ2_CH03_ISR_API == STD_ON)
    TAUJ2_CH03_ISR,
  #else
    DUMMY(280),
  #endif

  #if (GPT_TAUJ3_CH00_ISR_API == STD_ON)
    TAUJ3_CH00_ISR,
  #else
    DUMMY(281),
  #endif

  #if (GPT_TAUJ3_CH01_ISR_API == STD_ON)
    TAUJ3_CH01_ISR,
  #else
    DUMMY(282),
  #endif

  #if (GPT_TAUJ3_CH02_ISR_API == STD_ON)
    TAUJ3_CH02_ISR,
  #else
    DUMMY(283),
  #endif

  #if (GPT_TAUJ3_CH03_ISR_API == STD_ON)
    TAUJ3_CH03_ISR,
  #else
    DUMMY(284),
  #endif

  DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef GPT_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         ICU F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef ICU_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (ICU_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
      #else
      App_Os_TAUD0_CH00_ISR,
      #endif
   #else
    DUMMY(008),
  #endif

  #if (ICU_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (ICU_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (ICU_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (ICU_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (ICU_TAUD0_CH10_ISR_API == STD_ON)
    TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (ICU_TAUD0_CH12_ISR_API == STD_ON)
    TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (ICU_TAUD0_CH14_ISR_API == STD_ON)
    TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017), DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021),
  DUMMY(022), DUMMY(023), DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027),
  DUMMY(028), DUMMY(029), DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033),
  DUMMY(034), DUMMY(035), DUMMY(036),

  #if (ICU_EXT_INTP_CH00_ISR_API == STD_ON)
  EXT_INTP_CH00_ISR,
  #else
    DUMMY(037),
  #endif

   #if (ICU_EXT_INTP_CH01_ISR_API == STD_ON)
   EXT_INTP_CH01_ISR,
   #else
    DUMMY(038),
   #endif

   #if (ICU_EXT_INTP_CH02_ISR_API == STD_ON)
     EXT_INTP_CH02_ISR,
   #else
    DUMMY(039),
   #endif

  DUMMY(040), DUMMY(041), DUMMY(042),

  #if (ICU_EXT_INTP_CH03_ISR_API == STD_ON)
    EXT_INTP_CH03_ISR,
   #else
    DUMMY(043),
   #endif

   #if (ICU_EXT_INTP_CH04_ISR_API == STD_ON)
       #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
       EXT_INTP_CH04_ISR,
       #else
       App_Os_EXT_INTP_CH04_ISR,
       #endif
   #else
    DUMMY(44),
   #endif

   #if (ICU_EXT_INTP_CH05_ISR_API == STD_ON)
     EXT_INTP_CH05_ISR,
   #else
    DUMMY(45),
   #endif

    #if (ICU_EXT_INTP_CH10_ISR_API == STD_ON)
     EXT_INTP_CH10_ISR,
   #else
    DUMMY(46),
   #endif

   #if (ICU_EXT_INTP_CH11_ISR_API == STD_ON)
     EXT_INTP_CH11_ISR,
   #else
    DUMMY(47),
   #endif

  #if (ICU_TAUD0_CH01_ISR_API == STD_ON)
    TAUD0_CH01_ISR,
  #else
    DUMMY(48),
  #endif

  #if (ICU_TAUD0_CH03_ISR_API == STD_ON)
    TAUD0_CH03_ISR,
  #else
    DUMMY(49),
  #endif

  #if (ICU_TAUD0_CH05_ISR_API == STD_ON)
    TAUD0_CH05_ISR,
  #else
    DUMMY(50),
  #endif

  #if (ICU_TAUD0_CH07_ISR_API == STD_ON)

    #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
        TAUD0_CH07_ISR,
    #else
        App_Os_TAUD0_CH07_ISR,
    #endif
  #else
    DUMMY(51),
  #endif

  #if (ICU_TAUD0_CH09_ISR_API == STD_ON)
    TAUD0_CH09_ISR,
  #else
    DUMMY(52),
  #endif

  #if (ICU_TAUD0_CH11_ISR_API == STD_ON)
    TAUD0_CH11_ISR,
  #else
    DUMMY(53),
  #endif

  #if (ICU_TAUD0_CH13_ISR_API == STD_ON)
    TAUD0_CH13_ISR,
  #else
    DUMMY(54),
  #endif

  #if (ICU_TAUD0_CH15_ISR_API == STD_ON)
    TAUD0_CH15_ISR,
  #else
    DUMMY(55),
  #endif

  DUMMY(56), DUMMY(57), DUMMY(58), DUMMY(59), DUMMY(60), DUMMY(61), DUMMY(62),
  DUMMY(63), DUMMY(64), DUMMY(65), DUMMY(66), DUMMY(67), DUMMY(68), DUMMY(69),
  DUMMY(70), DUMMY(71), DUMMY(72), DUMMY(73), DUMMY(74), DUMMY(75), DUMMY(76),
  DUMMY(77), DUMMY(78), DUMMY(79),

  #if (ICU_TAUJ0_CH00_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUJ0_CH00_ISR,
      #else
            App_Os_TAUJ0_CH00_ISR,
      #endif
  #else
    DUMMY(80),
  #endif

  #if (ICU_TAUJ0_CH01_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUJ0_CH01_ISR,
      #else
            App_Os_TAUJ0_CH01_ISR,
      #endif
  #else
    DUMMY(81),
  #endif

  #if (ICU_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(82),
  #endif

  #if (ICU_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(83),
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127),

   #if (ICU_EXT_INTP_CH06_ISR_API == STD_ON)
     EXT_INTP_CH06_ISR,
   #else
    DUMMY(128),
   #endif

   #if (ICU_EXT_INTP_CH07_ISR_API == STD_ON)
     EXT_INTP_CH07_ISR,
   #else
    DUMMY(129),
   #endif

   #if (ICU_EXT_INTP_CH08_ISR_API == STD_ON)
     EXT_INTP_CH08_ISR,
   #else
    DUMMY(130),
   #endif

   #if (ICU_EXT_INTP_CH12_ISR_API == STD_ON)
     EXT_INTP_CH12_ISR,
   #else
    DUMMY(131),
   #endif

  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141),

  #if (ICU_TAUB0_CH00_ISR_API == STD_ON)
    TAUB0_CH00_ISR,
  #else
    DUMMY(142),
  #endif

  #if (ICU_TAUB0_CH01_ISR_API == STD_ON)
    TAUB0_CH01_ISR,
  #else
    DUMMY(143),
  #endif

  #if (ICU_TAUB0_CH02_ISR_API == STD_ON)
    TAUB0_CH02_ISR,
  #else
    DUMMY(144),
  #endif

  #if (ICU_TAUB0_CH03_ISR_API == STD_ON)
    TAUB0_CH03_ISR,
  #else
    DUMMY(145),
  #endif

  #if (ICU_TAUB0_CH04_ISR_API == STD_ON)
    TAUB0_CH04_ISR,
  #else
    DUMMY(146),
  #endif

  #if (ICU_TAUB0_CH05_ISR_API == STD_ON)
    TAUB0_CH05_ISR,
  #else
    DUMMY(147),
  #endif

  #if (ICU_TAUB0_CH06_ISR_API == STD_ON)
    TAUB0_CH06_ISR,
  #else
    DUMMY(148),
  #endif

  #if (ICU_TAUB0_CH07_ISR_API == STD_ON)
    TAUB0_CH07_ISR,
  #else
    DUMMY(149),
  #endif

  #if (ICU_TAUB0_CH08_ISR_API == STD_ON)
    TAUB0_CH08_ISR,
  #else
    DUMMY(150),
  #endif

  #if (ICU_TAUB0_CH09_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUB0_CH09_ISR,
      #else
            App_Os_TAUB0_CH09_ISR,
      #endif
  #else
    DUMMY(151),
  #endif

  #if (ICU_TAUB0_CH10_ISR_API == STD_ON)
    TAUB0_CH10_ISR,
  #else
    DUMMY(152),
  #endif

  #if (ICU_TAUB0_CH11_ISR_API == STD_ON)
    TAUB0_CH11_ISR,
  #else
    DUMMY(153),
  #endif

  #if (ICU_TAUB0_CH12_ISR_API == STD_ON)
    TAUB0_CH12_ISR,
  #else
    DUMMY(154),
  #endif

  #if (ICU_TAUB0_CH13_ISR_API == STD_ON)
    TAUB0_CH13_ISR,
  #else
    DUMMY(155),
  #endif

  #if (ICU_TAUB0_CH14_ISR_API == STD_ON)
    TAUB0_CH14_ISR,
  #else
    DUMMY(156),
  #endif

  #if (ICU_TAUB0_CH15_ISR_API == STD_ON)
    TAUB0_CH15_ISR,
  #else
    DUMMY(157),
  #endif

  DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161), DUMMY(162), DUMMY(163),
  DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (ICU_TAUJ1_CH00_ISR_API == STD_ON)
    TAUJ1_CH00_ISR,
  #else
    DUMMY(168),
  #endif

  #if (ICU_TAUJ1_CH01_ISR_API == STD_ON)
    TAUJ1_CH01_ISR,
  #else
    DUMMY(169),
  #endif

  #if (ICU_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
    DUMMY(170),
  #endif

  #if (ICU_TAUJ1_CH03_ISR_API == STD_ON)
    TAUJ1_CH03_ISR,
  #else
    DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173), DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177),
  DUMMY(178), DUMMY(179), DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183),
  DUMMY(184), DUMMY(185), DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189),
  DUMMY(190), DUMMY(191), DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195),
  DUMMY(196), DUMMY(197), DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201),
  DUMMY(202), DUMMY(203), DUMMY(204),

   #if (ICU_EXT_INTP_CH09_ISR_API == STD_ON)
     EXT_INTP_CH09_ISR,
   #else
    DUMMY(205),
   #endif

   #if (ICU_EXT_INTP_CH13_ISR_API == STD_ON)
     EXT_INTP_CH13_ISR,
   #else
    DUMMY(206),
   #endif

   #if (ICU_EXT_INTP_CH14_ISR_API == STD_ON)
     EXT_INTP_CH14_ISR,
   #else
    DUMMY(207),
   #endif

   #if (ICU_EXT_INTP_CH15_ISR_API == STD_ON)
     EXT_INTP_CH15_ISR,
   #else
    DUMMY(208),
   #endif

  DUMMY(209), DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214),
  DUMMY(215), DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220),
  DUMMY(221), DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226),
  DUMMY(227), DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232),
  DUMMY(233), DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238),
  DUMMY(239), DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244),
  DUMMY(245), DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250),
  DUMMY(251), DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255),

  #if (ICU_TAUB1_CH00_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUB1_CH00_ISR,
      #else
            App_Os_TAUB1_CH00_ISR,
      #endif
  #else
    DUMMY(256),
  #endif

  #if (ICU_TAUB1_CH01_ISR_API == STD_ON)
    TAUB1_CH01_ISR,
  #else
    DUMMY(257),
  #endif

  #if (ICU_TAUB1_CH02_ISR_API == STD_ON)
    TAUB1_CH02_ISR,
  #else
    DUMMY(258),
  #endif

  #if (ICU_TAUB1_CH03_ISR_API == STD_ON)
    TAUB1_CH03_ISR,
  #else
    DUMMY(259),
  #endif

  #if (ICU_TAUB1_CH04_ISR_API == STD_ON)
    TAUB1_CH04_ISR,
  #else
    DUMMY(260),
  #endif

  #if (ICU_TAUB1_CH05_ISR_API == STD_ON)
    TAUB1_CH05_ISR,
  #else
    DUMMY(261),
  #endif

  #if (ICU_TAUB1_CH06_ISR_API == STD_ON)
    TAUB1_CH06_ISR,
  #else
    DUMMY(262),
  #endif

  #if (ICU_TAUB1_CH07_ISR_API == STD_ON)
    TAUB1_CH07_ISR,
  #else
    DUMMY(263),
  #endif

  #if (ICU_TAUB1_CH08_ISR_API == STD_ON)
    TAUB1_CH08_ISR,
  #else
    DUMMY(264),
  #endif

  #if (ICU_TAUB1_CH09_ISR_API == STD_ON)
    TAUB1_CH09_ISR,
  #else
    DUMMY(265),
  #endif

  #if (ICU_TAUB1_CH10_ISR_API == STD_ON)
    TAUB1_CH10_ISR,
  #else
    DUMMY(266),
  #endif

  #if (ICU_TAUB1_CH11_ISR_API == STD_ON)
    TAUB1_CH11_ISR,
  #else
    DUMMY(267),
  #endif

  #if (ICU_TAUB1_CH12_ISR_API == STD_ON)
    TAUB1_CH12_ISR,
  #else
    DUMMY(268),
  #endif

  #if (ICU_TAUB1_CH13_ISR_API == STD_ON)
    TAUB1_CH13_ISR,
  #else
    DUMMY(269),
  #endif

  #if (ICU_TAUB1_CH14_ISR_API == STD_ON)
    TAUB1_CH14_ISR,
  #else
    DUMMY(270),
  #endif

  #if (ICU_TAUB1_CH15_ISR_API == STD_ON)
    TAUB1_CH15_ISR,
  #else
    DUMMY(271),
  #endif

  DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275), DUMMY(276),

  #if (ICU_TAUJ2_CH00_ISR_API == STD_ON)
    TAUJ2_CH00_ISR,
  #else
    DUMMY(277),
  #endif

  #if (ICU_TAUJ2_CH01_ISR_API == STD_ON)
    TAUJ2_CH01_ISR,
  #else
    DUMMY(278),
  #endif

  #if (ICU_TAUJ2_CH02_ISR_API == STD_ON)
    TAUJ2_CH02_ISR,
  #else
    DUMMY(279),
  #endif

  #if (ICU_TAUJ2_CH03_ISR_API == STD_ON)
    TAUJ2_CH03_ISR,
  #else
    DUMMY(280),
  #endif

  #if (ICU_TAUJ3_CH00_ISR_API == STD_ON)
    TAUJ3_CH00_ISR,
  #else
    DUMMY(281),
  #endif

  #if (ICU_TAUJ3_CH01_ISR_API == STD_ON)
    TAUJ3_CH01_ISR,
  #else
    DUMMY(282),
  #endif

  #if (ICU_TAUJ3_CH02_ISR_API == STD_ON)
    TAUJ3_CH02_ISR,
  #else
    DUMMY(283),
  #endif

  #if (ICU_TAUJ3_CH03_ISR_API == STD_ON)
    TAUJ3_CH03_ISR,
  #else
    DUMMY(284),
  #endif

  DUMMY(285), DUMMY(286), DUMMY(287), DUMMY(288), DUMMY(289), DUMMY(290),
  DUMMY(291), DUMMY(292), DUMMY(293), DUMMY(294), DUMMY(295), DUMMY(296),
  DUMMY(297), DUMMY(298), DUMMY(299), DUMMY(300), DUMMY(301), DUMMY(302),
  DUMMY(303), DUMMY(304), DUMMY(305), DUMMY(306), DUMMY(307), DUMMY(308),
  DUMMY(309), DUMMY(310), DUMMY(311), DUMMY(312), DUMMY(313), DUMMY(314),
  DUMMY(315), DUMMY(316), DUMMY(317), DUMMY(318), DUMMY(319), DUMMY(320),
  DUMMY(321), DUMMY(322), DUMMY(323), DUMMY(324), DUMMY(325), DUMMY(326),
  DUMMY(327), DUMMY(328), DUMMY(329), DUMMY(330), DUMMY(331), DUMMY(332),
  DUMMY(333), DUMMY(334), DUMMY(335), DUMMY(336), DUMMY(337), DUMMY(338),
  DUMMY(339), DUMMY(340), DUMMY(341), DUMMY(342), DUMMY(343), DUMMY(344),
  DUMMY(345), DUMMY(346), DUMMY(347), DUMMY(348), DUMMY(349), DUMMY(350),
  DUMMY(351), DUMMY(352), DUMMY(353), DUMMY(354), DUMMY(355), DUMMY(355),
  DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359), DUMMY(360), DUMMY(361),
  DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365), DUMMY(366), DUMMY(367),

  #if (ICU_EXT_INTP_CH16_ISR_API == STD_ON)
    EXT_INTP_CH16_ISR,
  #else
    DUMMY(368),
  #endif

  #if (ICU_EXT_INTP_CH17_ISR_API == STD_ON)
    EXT_INTP_CH17_ISR,
  #else
    DUMMY(369),
  #endif

  #if (ICU_EXT_INTP_CH18_ISR_API == STD_ON)
    EXT_INTP_CH18_ISR,
  #else
    DUMMY(370),
  #endif

  #if (ICU_EXT_INTP_CH19_ISR_API == STD_ON)
    EXT_INTP_CH19_ISR,
  #else
    DUMMY(371),
  #endif

  #if (ICU_EXT_INTP_CH20_ISR_API == STD_ON)
    EXT_INTP_CH20_ISR,
  #else
    DUMMY(372),
  #endif

  #if (ICU_EXT_INTP_CH21_ISR_API == STD_ON)
    EXT_INTP_CH21_ISR,
  #else
    DUMMY(373),
  #endif

  #if (ICU_EXT_INTP_CH22_ISR_API == STD_ON)
    EXT_INTP_CH22_ISR,
  #else
    DUMMY(374),
  #endif

  #if (ICU_EXT_INTP_CH23_ISR_API == STD_ON)
    EXT_INTP_CH23_ISR,
  #else
    DUMMY(375),
  #endif

  DUMMY(376),
};
/* End of #ifdef ICU_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         LIN F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef LIN_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032),

  #if (LIN_CHANNEL16_CONFIGURED == STD_ON)
  /* 33 */
  LIN_CHANNEL16_ISR,
  #else
  DUMMY(033),
  #endif

  DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050),

  /* 51 */
  Timer0_Interrupt,

  DUMMY(052), DUMMY(053), DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057),

  #if (LIN_CHANNEL00_CONFIGURED == STD_ON)
  /* 58 */
  LIN_CHANNEL00_ISR,
  #else
  DUMMY(058),
  #endif
  #if (LIN_CHANNEL01_CONFIGURED == STD_ON)
  #if defined (Os_LIN_CHANNEL01_CAT2_ISR) || defined (LIN_CHANNEL01_CAT2_ISR)
  /* 59 */
  App_Os_LIN01_SG01_ISR,
  #else
  /* 59 */
  LIN_CHANNEL01_ISR,
  #endif
  #else
  DUMMY(059),
  #endif

  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),

  #if (LIN_CHANNEL17_CONFIGURED == STD_ON)
 /* 120 */
  LIN_CHANNEL17_ISR,
  #else
  DUMMY(120),
  #endif

  DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),

  #if (LIN_CHANNEL02_CONFIGURED == STD_ON)
  /*162*/
  LIN_CHANNEL02_ISR,
  #else
  DUMMY(162),
  #endif
  #if (LIN_CHANNEL03_CONFIGURED == STD_ON)
  /*163*/
  LIN_CHANNEL03_ISR,
  #else
  DUMMY(163),
  #endif
  #if (LIN_CHANNEL18_CONFIGURED == STD_ON)
  /*164*/
  LIN_CHANNEL18_ISR,
  #else
  DUMMY(164),
  #endif

  DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225),

  #if (LIN_CHANNEL04_CONFIGURED == STD_ON)
  /* 226 */
  LIN_CHANNEL04_ISR,
  #else
  DUMMY(226),
  #endif
  #if (LIN_CHANNEL05_CONFIGURED == STD_ON)
  /* 227 */
  LIN_CHANNEL05_ISR,
  #else
  DUMMY(227),
  #endif
  #if (LIN_CHANNEL19_CONFIGURED == STD_ON)
  /* 228 */
  LIN_CHANNEL19_ISR,
  #else
  DUMMY(228),
  #endif

  DUMMY(229), DUMMY(230), DUMMY(231),

  #if (LIN_CHANNEL20_CONFIGURED == STD_ON)
  /*232*/
  LIN_CHANNEL20_ISR,
  #else
  DUMMY(232),
  #endif

  DUMMY(233), DUMMY(234), DUMMY(235),

  #if (LIN_CHANNEL21_CONFIGURED == STD_ON)
  /*236*/
  LIN_CHANNEL21_ISR,
  #else
  DUMMY(236),
  #endif

  DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274),

  #if (LIN_CHANNEL06_CONFIGURED == STD_ON)
  /*275*/
  LIN_CHANNEL06_ISR,
  #else
  DUMMY(275),
  #endif
  #if (LIN_CHANNEL07_CONFIGURED == STD_ON)
   /*276*/
  LIN_CHANNEL07_ISR,
  #else
  DUMMY(276),
  #endif

  DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284),

  #if (LIN_CHANNEL08_CONFIGURED == STD_ON)
  /*285*/
  LIN_CHANNEL08_ISR,
  #else
  DUMMY(285),
  #endif
  #if (LIN_CHANNEL09_CONFIGURED == STD_ON)
  /*286*/
  LIN_CHANNEL09_ISR,
  #else
  DUMMY(286),
  #endif

  DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),

  #if (LIN_CHANNEL10_CONFIGURED == STD_ON)
  /*324*/
  LIN_CHANNEL10_ISR,
  #else
  DUMMY(324),
  #endif
  #if (LIN_CHANNEL11_CONFIGURED == STD_ON)
  /*325*/
  LIN_CHANNEL11_ISR,
  #else
  DUMMY(325),
  #endif

  DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),

  #if (LIN_CHANNEL22_CONFIGURED == STD_ON)
  /* 360 */
  LIN_CHANNEL22_ISR,
  #else
  DUMMY(360),
  #endif

  DUMMY(361), DUMMY(362), DUMMY(363),

  #if (LIN_CHANNEL23_CONFIGURED == STD_ON)
  /* 364 */
  LIN_CHANNEL23_ISR,
  #else
  DUMMY(364),
  #endif

  DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef LIN_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         MCU F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef MCU_MODULE_TEST
#pragma ghs startsda
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022),
#ifdef MCU_CANICUSTOP_INT
/* 23 */
   MCU_CAN_STOP,
#else
  DUMMY(023),
#endif
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079),
#ifdef MCU_TIMER_INT
/* 80 */
   TAUJ0_I0,
#else
/* 80 */
  DUMMY(80),
#endif
#ifdef MCU_TIMER_INT
/* 81 */
   TAUJ0_I1,
#else
/* 81 */
  DUMMY(81),
#endif
  DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104),
  DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111),
  /* 112 */
#if (MCU_LOW_POWER_SEQUENCER == STD_ON)
#ifdef MCU_CFG53_INT
   MCU_INTCWEND_CFG53_ISR,
#else
   MCU_INTCWEND_ISR,
#endif
#else
  DUMMY(112),
#endif
  DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef MCU_MODULE_TEST */
#pragma ghs endsda
#endif

/*****************************************************************************/
/*                         PORT F1KM-S4 IVT                                  */
/*****************************************************************************/
#ifdef PORT_MODULE_TEST
#pragma ghs startsda
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef PORT_MODULE_TEST */
#pragma ghs endsda
#endif

/*****************************************************************************/
/*                         PWM F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef PWM_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (PWM_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
    #else
      App_Os_TAUD0_CH00_ISR,
    #endif
  #else
    DUMMY(008),
  #endif

  #if (PWM_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (PWM_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (PWM_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (PWM_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (PWM_TAUD0_CH10_ISR_API == STD_ON)
  TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (PWM_TAUD0_CH12_ISR_API == STD_ON)
  TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (PWM_TAUD0_CH14_ISR_API == STD_ON)
  TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017), DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021),
  DUMMY(022), DUMMY(023), DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027),
  DUMMY(028), DUMMY(029), DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033),
  DUMMY(034), DUMMY(035), DUMMY(036),

  #ifdef PWM_TEST_APP
   INTP0_Isr,
  #else
   DUMMY(037),
  #endif

  #ifdef PWM_TEST_APP
   INTP1_Isr,
  #else
   DUMMY(038),
  #endif

  #ifdef PWM_TEST_APP
   INTP2_Isr,
  #else
   DUMMY(039),
  #endif

  DUMMY(040), DUMMY(041), DUMMY(042),

  #ifdef PWM_TEST_APP
   INTP3_Isr,
  #else
   DUMMY(043),
  #endif

  #ifdef PWM_TEST_APP
   INTP4_Isr,
  #else
   DUMMY(044),
  #endif

  #ifdef PWM_TEST_APP
   INTP5_Isr,
  #else
   DUMMY(045),
  #endif

  #ifdef PWM_TEST_APP
   INTP10_Isr,
  #else
   DUMMY(046),
  #endif

  #ifdef PWM_TEST_APP
   INTP11_Isr,
  #else
   DUMMY(047),
  #endif

   #if (PWM_TAUD0_CH01_ISR_API == STD_ON)
   TAUD0_CH01_ISR,
   #else
    DUMMY(048),
   #endif

   #if (PWM_TAUD0_CH03_ISR_API == STD_ON)
   TAUD0_CH03_ISR,
   #else
    DUMMY(049),
   #endif

   #if (PWM_TAUD0_CH05_ISR_API == STD_ON)
    TAUD0_CH05_ISR,
   #else
    DUMMY(050),
   #endif

   #if (PWM_TAUD0_CH07_ISR_API == STD_ON)
      #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
        TAUD0_CH07_ISR,
      #else
       App_Os_TAUD0_CH07_ISR,
      #endif
   #else
      DUMMY(051),
   #endif

  #if (PWM_TAUD0_CH09_ISR_API == STD_ON)
   TAUD0_CH09_ISR,
  #else
   DUMMY(052),
  #endif

  #if (PWM_TAUD0_CH11_ISR_API == STD_ON)
   TAUD0_CH11_ISR,
  #else
   DUMMY(053),
  #endif

  #if (PWM_TAUD0_CH13_ISR_API == STD_ON)
   TAUD0_CH13_ISR,
  #else
   DUMMY(054),
  #endif

  #if (PWM_TAUD0_CH15_ISR_API == STD_ON)
   TAUD0_CH15_ISR,
  #else
   DUMMY(055),
  #endif


  DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059), DUMMY(060), DUMMY(061),
  DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065), DUMMY(066), DUMMY(067),
  DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071), DUMMY(072), DUMMY(073),
  DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077), DUMMY(078), DUMMY(079),

  #if (PWM_TAUJ0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH00_ISR,
    #else
      App_Os_TAUJ0_CH00_ISR,
    #endif
  #else
    DUMMY(080),
  #endif

  #if (PWM_TAUJ0_CH01_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH01_ISR,
    #else
      App_Os_TAUJ0_CH01_ISR,
    #endif
  #else
    DUMMY(081),
  #endif

  #if (PWM_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(082),
  #endif

  #if (PWM_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(083),
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091),

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP00_ISR_API == STD_ON)
    PWM_INTPWGAG00_ISR,
    #else
     DUMMY(092),
    #endif
  #else
    DUMMY(092),
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP01_ISR_API == STD_ON)
    PWM_INTPWGAG01_ISR,
    #else
     DUMMY(093),
    #endif
  #else
    DUMMY(093),
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP02_ISR_API == STD_ON)
    PWM_INTPWGAG02_ISR,
    #else
     DUMMY(094),
    #endif
  #else
    DUMMY(094),
  #endif

  DUMMY(095), DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100),
  DUMMY(101), DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106),
  DUMMY(107), DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112),
  DUMMY(113), DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118),
  DUMMY(119), DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124),
  DUMMY(125), DUMMY(126), DUMMY(127),

  #ifdef PWM_TEST_APP
   INTP6_Isr,
  #else
   DUMMY(128),
  #endif

  #ifdef PWM_TEST_APP
   INTP7_Isr,
  #else
   DUMMY(129),
  #endif

  #ifdef PWM_TEST_APP
   INTP8_Isr,
  #else
   DUMMY(130),
  #endif

  #ifdef PWM_TEST_APP
   INTP12_Isr,
  #else
   DUMMY(131),
  #endif

  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141),

  #if (PWM_TAUB0_CH00_ISR_API == STD_ON)
   TAUB0_CH00_ISR,
  #else
   DUMMY(142),
  #endif

  #if (PWM_TAUB0_CH01_ISR_API == STD_ON)
   TAUB0_CH01_ISR,
  #else
   DUMMY(143),
  #endif

  #if (PWM_TAUB0_CH02_ISR_API == STD_ON)
   TAUB0_CH02_ISR,
  #else
   DUMMY(144),
  #endif

  #if (PWM_TAUB0_CH03_ISR_API == STD_ON)
   TAUB0_CH03_ISR,
  #else
   DUMMY(145),
  #endif

  #if (PWM_TAUB0_CH04_ISR_API == STD_ON)
   TAUB0_CH04_ISR,
  #else
   DUMMY(146),
  #endif

  #if (PWM_TAUB0_CH05_ISR_API == STD_ON)
   TAUB0_CH05_ISR,
  #else
   DUMMY(147),
  #endif

  #if (PWM_TAUB0_CH06_ISR_API == STD_ON)
   TAUB0_CH06_ISR,
  #else
   DUMMY(148),
  #endif

  #if (PWM_TAUB0_CH07_ISR_API == STD_ON)
   TAUB0_CH07_ISR,
  #else
   DUMMY(149),
  #endif

  #if (PWM_TAUB0_CH08_ISR_API == STD_ON)
   TAUB0_CH08_ISR,
  #else
   DUMMY(150),
  #endif

  #if (PWM_TAUB0_CH09_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUB0_CH09_ISR,
    #else
      App_Os_TAUB0_CH09_ISR,
    #endif
  #else
    DUMMY(151),
  #endif

  #if (PWM_TAUB0_CH10_ISR_API == STD_ON)
   TAUB0_CH10_ISR,
  #else
    DUMMY(152),
  #endif

  #if (PWM_TAUB0_CH11_ISR_API == STD_ON)
   TAUB0_CH11_ISR,
  #else
    DUMMY(153),
  #endif

  #if (PWM_TAUB0_CH12_ISR_API == STD_ON)
   TAUB0_CH12_ISR,
  #else
    DUMMY(154),
  #endif

  #if (PWM_TAUB0_CH13_ISR_API == STD_ON)
   TAUB0_CH13_ISR,
  #else
    DUMMY(155),
  #endif

  #if (PWM_TAUB0_CH14_ISR_API == STD_ON)
   TAUB0_CH14_ISR,
  #else
    DUMMY(156),
  #endif

  #if (PWM_TAUB0_CH15_ISR_API == STD_ON)
   TAUB0_CH15_ISR,
  #else
    DUMMY(157),
  #endif

  DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),DUMMY(162), DUMMY(163),
  DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (PWM_TAUJ1_CH00_ISR_API == STD_ON)
   TAUJ1_CH00_ISR,
  #else
   DUMMY(168),
  #endif

  #if (PWM_TAUJ1_CH01_ISR_API == STD_ON)
   TAUJ1_CH01_ISR,
  #else
   DUMMY(169),
  #endif

  #if (PWM_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
   DUMMY(170),
  #endif

  #if (PWM_TAUJ1_CH03_ISR_API == STD_ON)
   TAUJ1_CH03_ISR,
  #else
   DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173), DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177),
  DUMMY(178), DUMMY(179), DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183),
  DUMMY(184), DUMMY(185), DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189),
  DUMMY(190), DUMMY(191), DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195),
  DUMMY(196), DUMMY(197), DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201),
  DUMMY(202), DUMMY(203), DUMMY(204),

  #ifdef PWM_TEST_APP
   INTP9_Isr,
  #else
   DUMMY(205),
  #endif

  #ifdef PWM_TEST_APP
   INTP13_Isr,
  #else
   DUMMY(206),
  #endif

  #ifdef PWM_TEST_APP
   INTP14_Isr,
  #else
   DUMMY(207),
  #endif

  #ifdef PWM_TEST_APP
   INTP15_Isr,
  #else
   DUMMY(208),
  #endif

  DUMMY(209), DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214),
  DUMMY(215), DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220),
  DUMMY(221), DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226),
  DUMMY(227), DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232),
  DUMMY(233), DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238),
  DUMMY(239), DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244),
  DUMMY(245), DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250),
  DUMMY(251), DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255),

  #if (PWM_TAUB1_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUB1_CH00_ISR,
    #else
      App_Os_TAUB1_CH00_ISR,
    #endif
  #else
     DUMMY(256),
  #endif

  #if (PWM_TAUB1_CH01_ISR_API == STD_ON)
    TAUB1_CH01_ISR,
  #else
    DUMMY(257),
  #endif

  #if (PWM_TAUB1_CH02_ISR_API == STD_ON)
    TAUB1_CH02_ISR,
  #else
    DUMMY(258),
  #endif

  #if (PWM_TAUB1_CH03_ISR_API == STD_ON)
    TAUB1_CH03_ISR,
  #else
    DUMMY(259),
  #endif

  #if (PWM_TAUB1_CH04_ISR_API == STD_ON)
    TAUB1_CH04_ISR,
  #else
    DUMMY(260),
  #endif

  #if (PWM_TAUB1_CH05_ISR_API == STD_ON)
    TAUB1_CH05_ISR,
  #else
    DUMMY(261),
  #endif

  #if (PWM_TAUB1_CH06_ISR_API == STD_ON)
    TAUB1_CH06_ISR,
  #else
    DUMMY(262),
  #endif

  #if (PWM_TAUB1_CH07_ISR_API == STD_ON)
    TAUB1_CH07_ISR,
  #else
    DUMMY(263),
  #endif

  #if (PWM_TAUB1_CH08_ISR_API == STD_ON)
   TAUB1_CH08_ISR,
  #else
   DUMMY(264),
  #endif

  #if (PWM_TAUB1_CH09_ISR_API == STD_ON)
    TAUB1_CH09_ISR,
  #else
    DUMMY(265),
  #endif

  #if (PWM_TAUB1_CH10_ISR_API == STD_ON)
    TAUB1_CH10_ISR,
  #else
    DUMMY(266),
  #endif

  #if (PWM_TAUB1_CH11_ISR_API == STD_ON)
    TAUB1_CH11_ISR,
  #else
    DUMMY(267),
  #endif

  #if (PWM_TAUB1_CH12_ISR_API == STD_ON)
    TAUB1_CH12_ISR,
  #else
    DUMMY(268),
  #endif

  #if (PWM_TAUB1_CH13_ISR_API == STD_ON)
   TAUB1_CH13_ISR,
  #else
   DUMMY(269),
  #endif

  #if (PWM_TAUB1_CH14_ISR_API == STD_ON)
    TAUB1_CH14_ISR,
  #else
    DUMMY(270),
  #endif

  #if (PWM_TAUB1_CH15_ISR_API == STD_ON)
    TAUB1_CH15_ISR,
  #else
    DUMMY(271),
  #endif

  DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275), DUMMY(276),

  #if (PWM_TAUJ2_CH00_ISR_API == STD_ON)
    TAUJ2_CH00_ISR,
  #else
    DUMMY(277),
  #endif

  #if (PWM_TAUJ2_CH01_ISR_API == STD_ON)
    TAUJ2_CH01_ISR,
  #else
    DUMMY(278),
  #endif

  #if (PWM_TAUJ2_CH02_ISR_API == STD_ON)
    TAUJ2_CH02_ISR,
  #else
    DUMMY(279),
  #endif

  #if (PWM_TAUJ2_CH03_ISR_API == STD_ON)
    TAUJ2_CH03_ISR,
  #else
    DUMMY(280),
  #endif

  #if (PWM_TAUJ3_CH00_ISR_API == STD_ON)
    TAUJ3_CH00_ISR,
  #else
    DUMMY(281),
  #endif

  #if (PWM_TAUJ3_CH01_ISR_API == STD_ON)
    TAUJ3_CH01_ISR,
  #else
    DUMMY(282),
  #endif

  #if (PWM_TAUJ3_CH02_ISR_API == STD_ON)
    TAUJ3_CH02_ISR,
  #else
    DUMMY(283),
  #endif

  #if (PWM_TAUJ3_CH03_ISR_API == STD_ON)
    TAUJ3_CH03_ISR,
  #else
    DUMMY(284),
  #endif

  DUMMY(285), DUMMY(286), DUMMY(287), DUMMY(288), DUMMY(289), DUMMY(290),
  DUMMY(291), DUMMY(292), DUMMY(293), DUMMY(294), DUMMY(295), DUMMY(296),
  DUMMY(297), DUMMY(298), DUMMY(299), DUMMY(300), DUMMY(301), DUMMY(302),
  DUMMY(303), DUMMY(304), DUMMY(305), DUMMY(306), DUMMY(307), DUMMY(308),
  DUMMY(309), DUMMY(310), DUMMY(311), DUMMY(312), DUMMY(313), DUMMY(314),
  DUMMY(315), DUMMY(316), DUMMY(317), DUMMY(318), DUMMY(319), DUMMY(320),
  DUMMY(321), DUMMY(322), DUMMY(323), DUMMY(324), DUMMY(325), DUMMY(326),
  DUMMY(327), DUMMY(328), DUMMY(329), DUMMY(330), DUMMY(331), DUMMY(332),
  DUMMY(333), DUMMY(334), DUMMY(335), DUMMY(336), DUMMY(337), DUMMY(338),
  DUMMY(339), DUMMY(340), DUMMY(341), DUMMY(342), DUMMY(343), DUMMY(344),
  DUMMY(345), DUMMY(346), DUMMY(347), DUMMY(348), DUMMY(349), DUMMY(350),
  DUMMY(351), DUMMY(352), DUMMY(353), DUMMY(354), DUMMY(355), DUMMY(356),
  DUMMY(357), DUMMY(358), DUMMY(359), DUMMY(360), DUMMY(361), DUMMY(362),
  DUMMY(363), DUMMY(364), DUMMY(365), DUMMY(366), DUMMY(367), DUMMY(368),
  DUMMY(369), DUMMY(370), DUMMY(371), DUMMY(372), DUMMY(373), DUMMY(374),
  DUMMY(375), DUMMY(376)
};
/* End of #ifdef PWM_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         RAMTST F1KM-S4 IVT                                */
/*****************************************************************************/
#ifdef RAMTST_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef RAMTST_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         SPI F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef SPI_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),
  #if(SPI_TIMER == STD_ON)
  /* 8 */
  Timer_Task,
  #else
  /* 8 */
  DUMMY(08),
  #endif
 #if(SPI_TIMER2 == STD_ON)
  /* 9 */
  Timer_Task2,
  #else
  /* 9 */
  DUMMY(09),
  #endif
  /* 10 */
  DUMMY(010),
  /* 11 */
  DUMMY(011),
  /* 12 */
  DUMMY(012),
  /* 13 */
  DUMMY(013),
  /* 14 */
  DUMMY(014),
  /* 15 */
  DUMMY(015),
  /* 16 */
  DUMMY(016),
  /* 17 */
  DUMMY(017),
  /* 18 */
  DUMMY(018),
  /* 19 */
  DUMMY(019),
  /* 20 */
  DUMMY(020),
  /* 21 */
  DUMMY(021),
  /* 22 */
  DUMMY(022),
  /* 23 */
  DUMMY(023),
  /* 24 */
  DUMMY(024),
  /* 25 */
  DUMMY(025),
  /* 26 */
  DUMMY(026),
  #if(SPI_CSIG0_TIC_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIG0_TIC_CAT2_ISR
  /* 27 */
  App_Os_SPI_CSIG0_TIC_ISR,
  #else
  /* 27 */
  SPI_CSIG0_TIC_ISR,
  #endif
  #else
    #ifdef APP_SPI_CSIG0_SLAVE_ISR_ON
    /* 27 */
    APP_SPI_CSIG0_SLAVE_TX_ISR,
    #else
    /* 27 */
    DUMMY(027),
    #endif
  #endif
  #if(SPI_CSIG0_TIR_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIG0_TIR_CAT2_ISR
  /* 28 */
  App_Os_SPI_CSIG0_TIR_ISR,
  #else
  /* 28 */
  SPI_CSIG0_TIR_ISR,
  #endif
  #else
  /* 28 */
    #ifdef APP_SPI_CSIG0_SLAVE_ISR_ON
    /* 28 */
    APP_SPI_CSIG0_SLAVE_RX_ISR,
    #else
    /* 28 */
    DUMMY(028),
    #endif
  #endif
  #if(SPI_CSIH0_TIC_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIH0_TIC_CAT2_ISR
  /* 29 */
  App_Os_SPI_CSIH0_TIC_ISR,
  #else
  /* 29 */
  SPI_CSIH0_TIC_ISR,
  #endif
  #else
    #ifdef APP_SPI_CSIH0_SLAVE_ISR_ON
    /* 29 */
    APP_SPI_CSIH0_SLAVE_TX_ISR,
    #else
    /* 29 */
    DUMMY(029),
    #endif
  #endif
  #if(SPI_CSIH0_TIR_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIH0_TIR_CAT2_ISR
  /* 30 */
  App_Os_SPI_CSIH0_TIR_ISR,
  #else
  /* 30 */
  SPI_CSIH0_TIR_ISR,
  #endif
  #else
  /* 30 */
    #ifdef APP_SPI_CSIH0_SLAVE_ISR_ON
    /* 30 */
    APP_SPI_CSIH0_SLAVE_RX_ISR,
    #else
    /* 30 */
    DUMMY(030),
    #endif
  #endif
  /* 31 */
  DUMMY(031),
  /* 32 */
  DUMMY(032),
  DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  #if(SPI_TIMER1 == STD_ON)
  /* 48 */
  Timer_Task1,
  #else
  DUMMY(048),
  #endif
  #if(SPI_TIMER3 == STD_ON)
  /* 49 */
  Timer_Task3,
  #else
  /* 49 */
  DUMMY(049),
  #endif
  DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056),
  /* 57 */
  DUMMY(057),
  /* 58 */
  DUMMY(058),
  /* 59 */
  DUMMY(059),
  #if(SPI_DMA00_ISR_API == STD_ON)
  /* 60 */
  SPI_DMA00_ISR,
  #else
  /* 60 */
  DUMMY(060),
  #endif
  #if(SPI_DMA01_ISR_API == STD_ON)
  /* 61 */
  SPI_DMA01_ISR,
  #else
  /* 61 */
  DUMMY(061),
  #endif
  #if(SPI_DMA02_ISR_API == STD_ON)
  /* 62 */
  SPI_DMA02_ISR,
  #else
  /* 62 */
  DUMMY(062),
  #endif
  #if(SPI_DMA03_ISR_API == STD_ON)
  /* 63 */
  SPI_DMA03_ISR,
  #else
  /* 63 */
  DUMMY(063),
  #endif
  #if(SPI_DMA04_ISR_API == STD_ON)
  /* 64 */
  SPI_DMA04_ISR,
  #else
  /* 64 */
  DUMMY(064),
  #endif
  #if(SPI_DMA05_ISR_API == STD_ON)
  /* 65 */
  SPI_DMA05_ISR,
  #else
  /* 65 */
  DUMMY(065),
  #endif
  #if(SPI_DMA06_ISR_API == STD_ON)
  /* 66 */
  SPI_DMA06_ISR,
  #else
  /* 66 */
  DUMMY(066),
  #endif
  #if(SPI_DMA07_ISR_API == STD_ON)
  /* 67 */
  SPI_DMA07_ISR,
  #else
  /* 67 */
  DUMMY(067),
  #endif
  #if(SPI_DMA08_ISR_API == STD_ON)
  /* 68 */
  SPI_DMA08_ISR,
  #else
  /* 68 */
  DUMMY(068),
  #endif
  #if(SPI_DMA09_ISR_API == STD_ON)
  /* 69 */
  SPI_DMA09_ISR,
  #else
  /* 69 */
  DUMMY(069),
  #endif
  #if(SPI_DMA10_ISR_API == STD_ON)
  /* 70 */
  SPI_DMA10_ISR,
  #else
  /* 70 */
  DUMMY(070),
  #endif
  #if(SPI_DMA11_ISR_API == STD_ON)
  /* 71 */
  SPI_DMA11_ISR,
  #else
  /* 71 */
  DUMMY(071),
  #endif
  #if(SPI_DMA12_ISR_API == STD_ON)
  /* 72 */
  SPI_DMA12_ISR,
  #else
  /* 72 */
  DUMMY(072),
  #endif
  #if(SPI_DMA13_ISR_API == STD_ON)
  /* 73 */
  SPI_DMA13_ISR,
  #else
  /* 73 */
  DUMMY(073),
  #endif
  #if(SPI_DMA14_ISR_API == STD_ON)
  /* 74 */
  SPI_DMA14_ISR,
  #else
  /* 74 */
  DUMMY(074),
  #endif
  #if(SPI_DMA15_ISR_API == STD_ON)
  /* 75 */
  SPI_DMA15_ISR,
  #else
  /* 75 */
  DUMMY(075),
  #endif
  DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115),
  #ifdef APP_SPI_CSIH1_SLAVE_ISR_ON
    /* #if(SPI_CSIH1_TIC_ISR_API == STD_ON) */
  /* 116 */
  APP_SPI_CSIH1_SLAVE_TX_ISR, /* SPI_CSIH1_TIC_ISR, */
  #else
  #if(SPI_CSIH1_TIC_ISR_API == STD_ON)
  /* 116 */
  SPI_CSIH1_TIC_ISR,
  #else
  /* 116 */
  DUMMY(116),
  #endif
  #endif

  #ifdef APP_SPI_CSIH1_SLAVE_ISR_ON
    /* #if(SPI_CSIH1_TIR_ISR_API == STD_ON) */
  /* 117 */
  APP_SPI_CSIH1_SLAVE_RX_ISR, /* SPI_CSIH1_TIR_ISR, */
  #else
  #if(SPI_CSIH1_TIR_ISR_API == STD_ON)
  /* 117 */
  SPI_CSIH1_TIR_ISR,
  #else
  /* 117 */
  DUMMY(117),
  #endif
  #endif
  /* 118 */
  DUMMY(118),
  /* 119 */
  DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  #ifdef APP_SPI_CSIH2_SLAVE_ISR_ON
  /* 132 */
  APP_SPI_CSIH2_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIH2_TIC_ISR_API == STD_ON)
  /* 132 */
  SPI_CSIH2_TIC_ISR,
  #else
  /* 132 */
  DUMMY(132),
  #endif
  #endif

  #ifdef APP_SPI_CSIH2_SLAVE_ISR_ON
  /* 133 */
  APP_SPI_CSIH2_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIH2_TIR_ISR_API == STD_ON)
  /* 133 */
  SPI_CSIH2_TIR_ISR,
  #else
  /* 133 */
  DUMMY(133),
  #endif
  #endif
  /* 134 */
  DUMMY(134),
  /* 135 */
  DUMMY(135),
  DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157),
  #ifdef APP_SPI_CSIH3_SLAVE_ISR_ON
  /* 158 */
  APP_SPI_CSIH3_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIH3_TIC_ISR_API == STD_ON)
  /* 158 */
  SPI_CSIH3_TIC_ISR,
  #else
  /* 158 */
  DUMMY(158),
  #endif
  #endif

  #ifdef APP_SPI_CSIH3_SLAVE_ISR_ON
  /* 159 */
  APP_SPI_CSIH3_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIH3_TIR_ISR_API == STD_ON)
  /* 159 */
  SPI_CSIH3_TIR_ISR,
  #else
  /* 159 */
  DUMMY(159),
  #endif
  #endif
  /* 160 */
  DUMMY(160),
  /* 161 */
   DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222),
  #ifdef APP_SPI_CSIG1_SLAVE_ISR_ON
  /* 223 */
  APP_SPI_CSIG1_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIG1_TIC_ISR_API == STD_ON)
  /* 223 */
  SPI_CSIG1_TIC_ISR,
  #else
  /* 223 */
  DUMMY(223),
  #endif
  #endif
  #ifdef APP_SPI_CSIG1_SLAVE_ISR_ON
  /* 224 */
  APP_SPI_CSIG1_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIG1_TIR_ISR_API == STD_ON)
  /* 224 */
  SPI_CSIG1_TIR_ISR,
  #else
  /* 224 */
  DUMMY(224),
  #endif
  #endif
  /* 225 */
  DUMMY(225),
  DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325),
  #ifdef APP_SPI_CSIG2_SLAVE_ISR_ON
  /* 326 */
  APP_SPI_CSIG2_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIG2_TIC_ISR_API == STD_ON)
  /* 326 */
  SPI_CSIG2_TIC_ISR,
  #else
  /* 326 */
  DUMMY(326),
  #endif
  #endif

  #ifdef APP_SPI_CSIG2_SLAVE_ISR_ON
  /* 327 */
  APP_SPI_CSIG2_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIG2_TIR_ISR_API == STD_ON)
  /* 327 */
  SPI_CSIG2_TIR_ISR,
  #else
  /* 327 */
  DUMMY(327),
  #endif
  #endif
  /* 328 */
  DUMMY(328),
  #ifdef APP_SPI_CSIG3_SLAVE_ISR_ON
  /* 329 */
  APP_SPI_CSIG3_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIG3_TIC_ISR_API == STD_ON)
  /* 329 */
  SPI_CSIG3_TIC_ISR,
  #else
  /* 329 */
  DUMMY(329),
  #endif
  #endif

  #ifdef APP_SPI_CSIG3_SLAVE_ISR_ON
  /* 330 */
  APP_SPI_CSIG3_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIG3_TIR_ISR_API == STD_ON)
  /* 330 */
  SPI_CSIG3_TIR_ISR,
  #else
  /* 330 */
  DUMMY(330),
  #endif
  #endif
  /* 331 */
  DUMMY(331),
  DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef SPI_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         WDG F1KM-S4 IVT                                   */
/*****************************************************************************/
#ifdef WDG_MODULE_TEST
/*****************************************************************************/
/*                         WDG Interrupt Vector Table                        */
/*****************************************************************************/
#ifdef WDG_59_DRIVERA_AR_VERSION
#if ((WDG_59_DRIVERA_AR_VERSION == WDG_59_DRIVERA_AR_FOUR_ZERO_THREE) || \
     (WDG_59_DRIVERA_AR_VERSION == WDG_59_DRIVERA_AR_FOUR_TWO_TWO))
#define WDG_DRIVERA_INTERRUPT_ENABLE
#endif
#endif

#ifdef WDG_59_DRIVERB_AR_VERSION
#if ((WDG_59_DRIVERB_AR_VERSION == WDG_59_DRIVERB_AR_FOUR_ZERO_THREE) || \
     (WDG_59_DRIVERB_AR_VERSION == WDG_59_DRIVERB_AR_FOUR_TWO_TWO))
#define WDG_DRIVERB_INTERRUPT_ENABLE
#endif
#endif

 #if defined WDG_DRIVERA_INTERRUPT_ENABLE || \
                                            defined WDG_DRIVERB_INTERRUPT_ENABLE

#pragma ghs section sdata=".inttable"
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039),

/* 40 */
  #ifdef WDG_DRIVERA_INTERRUPT_ENABLE
  #ifndef Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR
  WDG_59_DRIVERA_TRIGGERFUNCTION_ISR,
  #else
 /* 40 */

 App_Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR,
  #endif
  #else
  DUMMY(040),
  #endif
/* 41 */

  #ifdef WDG_DRIVERB_INTERRUPT_ENABLE
  WDG_59_DRIVERB_TRIGGERFUNCTION_ISR,
  #else
  DUMMY(041),
  #endif
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
#pragma ghs section sdata=default
#endif
#endif /* #ifdef WDG_MODULE_TEST */


/*****************************************************************************/
/*               GLOBAL SAMPLE APPLICATION F1KM-S4 IVT                       */
/*****************************************************************************/
#ifdef GLOBAL_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (PWM_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
    #else
      App_Os_TAUD0_CH00_ISR,
    #endif
  #else
    DUMMY(008),
  #endif

  #if (PWM_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (PWM_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (PWM_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (PWM_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (PWM_TAUD0_CH10_ISR_API == STD_ON)
  TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (PWM_TAUD0_CH12_ISR_API == STD_ON)
  TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (PWM_TAUD0_CH14_ISR_API == STD_ON)
  TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017),

  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG1_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG1_CAT2_ISR) || defined (ADC0_SG1_CAT2_ISR)
        App_Os_ADC0_SG1_ISR,
      #else
        ADC0_SG1_ISR,
      #endif
    #else
      DUMMY(018),
    #endif /* #if (ADC0_SG1_ISR_API == STD_ON) */
  #else
    DUMMY(018),
  #endif
  /* 019 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG2_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG2_CAT2_ISR) || defined (ADC0_SG2_CAT2_ISR)
        App_Os_ADC0_SG2_ISR,
      #else
        ADC0_SG2_ISR,
      #endif
    #else
      DUMMY(019),
    #endif
  #else
    DUMMY(019),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
  /* 020 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG3_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG3_CAT2_ISR) || defined (ADC0_SG3_CAT2_ISR)
        App_Os_ADC0_SG3_ISR,
      #else
        ADC0_SG3_ISR,
      #endif
    #else
      DUMMY(020),
    #endif /* #if (ADC0_SG3_ISR_API == STD_ON) */
  #else
    DUMMY(020),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039),

  /* 40 */
  #ifdef WDG_DRIVERA_INTERRUPT_ENABLE
  #ifndef Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR
  WDG_59_DRIVERA_TRIGGERFUNCTION_ISR,
  #else
  /* 40 */
  App_Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR,
  #endif
  #else
  DUMMY(040),
  #endif

  /* 41 */

  #ifdef WDG_DRIVERB_INTERRUPT_ENABLE
  WDG_59_DRIVERB_TRIGGERFUNCTION_ISR,
  #else
  DUMMY(041),
  #endif

  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),

  #if (PWM_TAUD0_CH01_ISR_API == STD_ON)
  TAUD0_CH01_ISR,
  #else
   DUMMY(048),
  #endif

  #if (PWM_TAUD0_CH03_ISR_API == STD_ON)
  TAUD0_CH03_ISR,
  #else
   DUMMY(049),
  #endif

  #if (PWM_TAUD0_CH05_ISR_API == STD_ON)
   TAUD0_CH05_ISR,
  #else
   DUMMY(050),
  #endif

  #if (PWM_TAUD0_CH07_ISR_API == STD_ON)
     #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
       TAUD0_CH07_ISR,
     #else
      App_Os_TAUD0_CH07_ISR,
     #endif
  #else
     DUMMY(051),
  #endif

  #if (PWM_TAUD0_CH09_ISR_API == STD_ON)
   TAUD0_CH09_ISR,
  #else
   DUMMY(052),
  #endif

  #if (PWM_TAUD0_CH11_ISR_API == STD_ON)
   TAUD0_CH11_ISR,
  #else
   DUMMY(053),
  #endif

  #if (PWM_TAUD0_CH13_ISR_API == STD_ON)
   TAUD0_CH13_ISR,
  #else
   DUMMY(054),
  #endif

  #if (PWM_TAUD0_CH15_ISR_API == STD_ON)
   TAUD0_CH15_ISR,
  #else
   DUMMY(055),
  #endif

  /* ADC_0 Error Interrupt */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC_ERROR_SUPPORT == STD_ON)
      #if defined (Os_ADC0_ERR_CAT2_ISR) || defined (ADC0_ERR_CAT2_ISR)
        App_Os_ADC0_ERR_ISR,
      #else
        ADC0_ERR_ISR,
      #endif
    #else
      DUMMY(056),
    #endif /*#if (ADC_ERROR_SUPPORT == STD_ON)*/
  #else
    DUMMY(056),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(057), DUMMY(058), DUMMY(059),

  /* 60 */
  #if (ADC_DMA_ISR_CH00_API == STD_ON)
    #if defined (OS_ADC_DMA_CH00_CAT2_ISR) || defined (ADC_DMA_CH00_CAT2_ISR)
      App_Os_ADC_DMA_CH00_ISR,
    #else
      ADC_DMA_CH00_ISR,
    #endif
  #else
    DUMMY(060),
  #endif
  /* 61 */
  #if (ADC_DMA_ISR_CH01_API == STD_ON)
    ADC_DMA_CH01_ISR,
  #else
   DUMMY(061),
  #endif
  /* 62 */
  #if (ADC_DMA_ISR_CH02_API == STD_ON)
    ADC_DMA_CH02_ISR,
  #else
    DUMMY(062),
  #endif
  /* 63 */
  #if (ADC_DMA_ISR_CH03_API == STD_ON)
    ADC_DMA_CH03_ISR,
  #else
   DUMMY(063),
  #endif

  DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079),

  #if (PWM_TAUJ0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH00_ISR,
    #else
      App_Os_TAUJ0_CH00_ISR,
    #endif
  #else
    DUMMY(080),
  #endif

  #if (PWM_TAUJ0_CH01_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH01_ISR,
    #else
      App_Os_TAUJ0_CH01_ISR,
    #endif
  #else
    DUMMY(081),
  #endif

  #if (PWM_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(082),
  #endif

  #if (PWM_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(083),
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091),

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP00_ISR_API == STD_ON)
    PWM_INTPWGAG00_ISR,
    #else
     DUMMY(092),
    #endif
  #else
     DUMMY(092),
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP01_ISR_API == STD_ON)
    PWM_INTPWGAG01_ISR,
    #else
     DUMMY(093),
    #endif
  #else
     DUMMY(093),
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP02_ISR_API == STD_ON)
    PWM_INTPWGAG02_ISR,
    #else
     DUMMY(094),
    #endif
  #else
     DUMMY(094),
  #endif

  DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (PWM_TAUJ1_CH00_ISR_API == STD_ON)
   TAUJ1_CH00_ISR,
  #else
   DUMMY(168),
  #endif

  #if (PWM_TAUJ1_CH01_ISR_API == STD_ON)
   TAUJ1_CH01_ISR,
  #else
   DUMMY(169),
  #endif

  #if (PWM_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
   DUMMY(170),
  #endif

  #if (PWM_TAUJ1_CH03_ISR_API == STD_ON)
   TAUJ1_CH03_ISR,
  #else
   DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255),

  #if (PWM_TAUB1_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUB1_CH00_ISR,
    #else
      App_Os_TAUB1_CH00_ISR,
    #endif
  #else
     DUMMY(256),
  #endif

  #if (PWM_TAUB1_CH01_ISR_API == STD_ON)
    TAUB1_CH01_ISR,
  #else
    DUMMY(257),
  #endif

  #if (PWM_TAUB1_CH02_ISR_API == STD_ON)
    TAUB1_CH02_ISR,
  #else
    DUMMY(258),
  #endif

  #if (PWM_TAUB1_CH03_ISR_API == STD_ON)
    TAUB1_CH03_ISR,
  #else
    DUMMY(259),
  #endif

  #if (PWM_TAUB1_CH04_ISR_API == STD_ON)
    TAUB1_CH04_ISR,
  #else
    DUMMY(260),
  #endif

  #if (PWM_TAUB1_CH05_ISR_API == STD_ON)
    TAUB1_CH05_ISR,
  #else
    DUMMY(261),
  #endif

  #if (PWM_TAUB1_CH06_ISR_API == STD_ON)
    TAUB1_CH06_ISR,
  #else
    DUMMY(262),
  #endif

  #if (PWM_TAUB1_CH07_ISR_API == STD_ON)
    TAUB1_CH07_ISR,
  #else
    DUMMY(263),
  #endif

  #if (PWM_TAUB1_CH08_ISR_API == STD_ON)
   TAUB1_CH08_ISR,
  #else
   DUMMY(264),
  #endif

  #if (PWM_TAUB1_CH09_ISR_API == STD_ON)
    TAUB1_CH09_ISR,
  #else
    DUMMY(265),
  #endif

  #if (PWM_TAUB1_CH10_ISR_API == STD_ON)
    TAUB1_CH10_ISR,
  #else
    DUMMY(266),
  #endif

  #if (PWM_TAUB1_CH11_ISR_API == STD_ON)
    TAUB1_CH11_ISR,
  #else
    DUMMY(267),
  #endif

  #if (PWM_TAUB1_CH12_ISR_API == STD_ON)
    TAUB1_CH12_ISR,
  #else
    DUMMY(268),
  #endif

  #if (PWM_TAUB1_CH13_ISR_API == STD_ON)
   TAUB1_CH13_ISR,
  #else
   DUMMY(269),
  #endif

  #if (PWM_TAUB1_CH14_ISR_API == STD_ON)
    TAUB1_CH14_ISR,
  #else
    DUMMY(270),
  #endif

  #if (PWM_TAUB1_CH15_ISR_API == STD_ON)
    TAUB1_CH15_ISR,
  #else
    DUMMY(271),
  #endif

  DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376)
};
/* End of #ifdef GLOBAL_MODULE_TEST */
#endif



/*****************************************************************************/
/*****************************************************************************/
/*                         F1KM-S2 IVT                                       */
/*****************************************************************************/
/*****************************************************************************/
/* Continue: #ifdef F1KM_S1_DEVICE */
#elif defined F1KM_S2_DEVICE
#pragma ghs section sdata=".inttable"

/*****************************************************************************/
/*                         ADC F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef ADC_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),

  /*018*/
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG1_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG1_CAT2_ISR) || defined (ADC0_SG1_CAT2_ISR)
        App_Os_ADC0_SG1_ISR,
      #else
        ADC0_SG1_ISR,
      #endif
    #else
      DUMMY(018),
    #endif /* #if (ADC0_SG1_ISR_API == STD_ON) */
  #else
    DUMMY(018),
  #endif
  /* 019 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG2_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG2_CAT2_ISR) || defined (ADC0_SG2_CAT2_ISR)
        App_Os_ADC0_SG2_ISR,
      #else
        ADC0_SG2_ISR,
      #endif
    #else
      DUMMY(019),
    #endif
  #else
    DUMMY(019),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
  /* 020 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG3_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG3_CAT2_ISR) || defined (ADC0_SG3_CAT2_ISR)
        App_Os_ADC0_SG3_ISR,
      #else
        ADC0_SG3_ISR,
      #endif
    #else
      DUMMY(020),
    #endif /* #if (ADC0_SG3_ISR_API == STD_ON) */
  #else
    DUMMY(020),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050),

  /*051*/
  #if defined ADC_TEST_APP_CFG41
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG51
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG44
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG45
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG39
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG61
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG77
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG80
    TAUD0_CH7_Isr,
  #elif defined ADC_TEST_APP_CFG81
    TAUD0_CH7_Isr,
  #else
    DUMMY(051),
  #endif

  DUMMY(052), DUMMY(053),
  DUMMY(054),

  /*055*/
  #if defined ADC_TEST_APP_CFG80
    TAUD0_CH15_Isr,
  #elif defined ADC_TEST_APP_CFG81
    TAUD0_CH15_Isr,
  #else
  DUMMY(055),/* Adc_Timer_1, */
  #endif
  /*056 */
  /* ADC_0 Error Interrupt */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC_ERROR_SUPPORT == STD_ON)
      #if defined (Os_ADC0_ERR_CAT2_ISR) || defined (ADC0_ERR_CAT2_ISR)
        App_Os_ADC0_ERR_ISR,
      #else
        ADC0_ERR_ISR,
      #endif
    #else
      DUMMY(056),
    #endif /*#if (ADC_ERROR_SUPPORT == STD_ON)*/
  #else
    DUMMY(056),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(057), DUMMY(058), DUMMY(059),

/* 60 */
  #if (ADC_DMA_ISR_CH00_API == STD_ON)
    #if defined (OS_ADC_DMA_CH00_CAT2_ISR) || defined (ADC_DMA_CH00_CAT2_ISR)
      App_Os_ADC_DMA_CH00_ISR,
    #else
      ADC_DMA_CH00_ISR,
    #endif
  #else
    DUMMY(060),
  #endif
/* 61 */
  #if (ADC_DMA_ISR_CH01_API == STD_ON)
    ADC_DMA_CH01_ISR,
  #else
   DUMMY(061),
  #endif
/* 62 */
  #if (ADC_DMA_ISR_CH02_API == STD_ON)
    ADC_DMA_CH02_ISR,
  #else
    DUMMY(062),
  #endif
/* 63 */
  #if (ADC_DMA_ISR_CH03_API == STD_ON)
    ADC_DMA_CH03_ISR,
  #else
   DUMMY(063),
  #endif
/* 64 */
  #if (ADC_DMA_ISR_CH04_API == STD_ON)
    ADC_DMA_CH04_ISR,
  #else
    DUMMY(064),
  #endif
/* 65 */
  #if (ADC_DMA_ISR_CH05_API == STD_ON)
    ADC_DMA_CH05_ISR,
  #else
    DUMMY(065),
  #endif
/* 66 */
  #if (ADC_DMA_ISR_CH06_API == STD_ON)
    ADC_DMA_CH06_ISR,
  #else
    DUMMY(066),
  #endif
/* 67 */
  #if (ADC_DMA_ISR_CH07_API == STD_ON)
    ADC_DMA_CH07_ISR,
  #else
    DUMMY(067),
  #endif
/* 68 */
  #if (ADC_DMA_ISR_CH08_API == STD_ON)
    ADC_DMA_CH08_ISR,
  #else
    DUMMY(068),
  #endif
/* 69 */
  #if (ADC_DMA_ISR_CH04_API == STD_ON)
    ADC_DMA_CH09_ISR,
  #else
   DUMMY(069),
  #endif
/* 70 */
  #if (ADC_DMA_ISR_CH10_API == STD_ON)
    ADC_DMA_CH10_ISR,
  #else
    DUMMY(070),
  #endif
/* 71 */
  #if (ADC_DMA_ISR_CH11_API == STD_ON)
    ADC_DMA_CH11_ISR,
  #else
    DUMMY(071),
  #endif
/* 72 */
  #if (ADC_DMA_ISR_CH12_API == STD_ON)
    ADC_DMA_CH12_ISR,
  #else
    DUMMY(072),
  #endif
/* 73 */
  #if (ADC_DMA_ISR_CH13_API == STD_ON)
    ADC_DMA_CH13_ISR,
  #else
    DUMMY(073),
  #endif
/* 74 */
  #if (ADC_DMA_ISR_CH14_API == STD_ON)
    ADC_DMA_CH14_ISR,
  #else
    DUMMY(074),
  #endif
/* 75 */
  #if (ADC_DMA_ISR_CH15_API == STD_ON)
    ADC_DMA_CH15_ISR,
  #else
    DUMMY(075),
  #endif

  DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082),

  /* 83 */ /* Adc_Timer_1, */
  #if defined ADC_TEST_APP_CFG39
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG61
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG77
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG80
    TAUJ0_CH03_Isr,
  #elif defined ADC_TEST_APP_CFG81
    TAUJ0_CH03_Isr,
  #else
    DUMMY(083), /* Adc_Timer_1, */
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090),

  /* 91 */
  #if (ADC_PWSA_INT_QFULL_ISR == STD_ON)
    PWSA_QUE_ISR,
  #else
  DUMMY(091),
  #endif

  DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211),


/* 212 */
  /* ADC_1 Error Interrupt */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC_ERROR_SUPPORT == STD_ON)
      #if defined (Os_ADC1_ERR_CAT2_ISR) || defined (ADC1_ERR_CAT2_ISR)
        App_Os_ADC1_ERR_ISR,
      #else
        ADC1_ERR_ISR,
      #endif
    #else
      DUMMY(212),
    #endif /*#if (ADC_ERROR_SUPPORT == STD_ON)*/
  #else
    DUMMY(212),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
/* 213 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC1_SG1_ISR_API == STD_ON)
      #if defined (Os_ADC1_SG1_CAT2_ISR) || defined (ADC1_SG1_CAT2_ISR)
         App_Os_ADC1_SG1_ISR,
      #else
         ADC1_SG1_ISR,
      #endif
    #else
      DUMMY(213),
    #endif
  #else
    DUMMY(213),
  #endif
/* 214 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC1_SG2_ISR_API == STD_ON)
      #if defined (Os_ADC1_SG2_CAT2_ISR) || defined (ADC1_SG2_CAT2_ISR)
        App_Os_ADC1_SG2_ISR,
      #else
        ADC1_SG2_ISR,
      #endif
    #else
      DUMMY(214),
    #endif
  #else
    DUMMY(214),
  #endif
/* 215 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC1_SG3_ISR_API == STD_ON)
      #if defined (Os_ADC1_SG3_CAT2_ISR) || defined (ADC1_SG3_CAT2_ISR)
        App_Os_ADC1_SG3_ISR,
      #else
        ADC1_SG3_ISR,
      #endif
    #else
      DUMMY(215),
    #endif
  #else
    DUMMY(215),
  #endif

  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297),

/* 298 */
  #if (ADC_DMA_ISR_CH16_API == STD_ON)
    ADC_DMA_CH16_ISR,
  #else
    DUMMY(298),
  #endif
/* 299 */
  #if (ADC_DMA_ISR_CH17_API == STD_ON)
    ADC_DMA_CH17_ISR,
  #else
    DUMMY(299),
  #endif
/* 300 */
  #if (ADC_DMA_ISR_CH18_API == STD_ON)
    ADC_DMA_CH18_ISR,
  #else
    DUMMY(300),
  #endif
/* 301 */
  #if (ADC_DMA_ISR_CH19_API == STD_ON)
    ADC_DMA_CH19_ISR,
  #else
    DUMMY(301),
  #endif
/* 302 */
  #if (ADC_DMA_ISR_CH20_API == STD_ON)
    ADC_DMA_CH20_ISR,
  #else
    DUMMY(302),
  #endif
/* 303 */
  #if (ADC_DMA_ISR_CH21_API == STD_ON)
    ADC_DMA_CH21_ISR,
  #else
    DUMMY(303),
  #endif
/* 304 */
  #if (ADC_DMA_ISR_CH22_API == STD_ON)
    ADC_DMA_CH22_ISR,
  #else
    DUMMY(304),
  #endif
/* 305 */
  #if (ADC_DMA_ISR_CH23_API == STD_ON)
    ADC_DMA_CH23_ISR,
  #else
    DUMMY(305),
  #endif
/* 306 */
  #if (ADC_DMA_ISR_CH24_API == STD_ON)
    ADC_DMA_CH24_ISR,
  #else
    DUMMY(306),
  #endif
/* 307 */
  #if (ADC_DMA_ISR_CH25_API == STD_ON)
    ADC_DMA_CH25_ISR,
  #else
    DUMMY(307),
  #endif
/* 308 */
  #if (ADC_DMA_ISR_CH26_API == STD_ON)
    ADC_DMA_CH26_ISR,
  #else
    DUMMY(308),
  #endif
/* 309 */
  #if (ADC_DMA_ISR_CH27_API == STD_ON)
    ADC_DMA_CH27_ISR,
  #else
    DUMMY(309),
  #endif
/* 310 */
  #if (ADC_DMA_ISR_CH28_API == STD_ON)
    ADC_DMA_CH28_ISR,
  #else
    DUMMY(310),
  #endif
/* 311 */
  #if (ADC_DMA_ISR_CH29_API == STD_ON)
    ADC_DMA_CH29_ISR,
  #else
    DUMMY(311),
  #endif
/* 312 */
  #if (ADC_DMA_ISR_CH30_API == STD_ON)
    ADC_DMA_CH30_ISR,
  #else
    DUMMY(312),
  #endif
/* 313 */
  #if (ADC_DMA_ISR_CH31_API == STD_ON)
    ADC_DMA_CH31_ISR,
  #else
    DUMMY(313),
  #endif

  DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef ADC_MODULE_TEST */
#endif

#pragma ghs section sdata=".inttable"

/*****************************************************************************/
/*                         CAN Interrupt Vector Table                        */
/*****************************************************************************/
#if defined (CAN_MODULE_TEST) && (CAN_ISR_CATEGORY_2 == STD_OFF)
#define INT_VECTOR_051 Timer0_Interrupt
#if(defined(F1KM) && defined(CAN_TEST_APP) && defined(smoketst))
#define INT_VECTOR_084 OSTM0_Interrupt
#endif
#if (CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON)
#ifndef Os_CAN_RSCAN0_RXFIFO_CAT2_ISR
#define INT_VECTOR_023 CAN_RSCAN0_RXFIFO_ISR /* 023 */
#else
#define INT_VECTOR_023 App_Os_CONTROLLER_RXFIFO0_ISR /* 023 */
#endif
#endif
#if (CAN_CONTROLLER0_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER0_BUSOFF_CAT2_ISR
#define INT_VECTOR_024  CAN_CONTROLLER0_BUSOFF_ISR /* 024 */
#else
#define INT_VECTOR_024 App_Os_CONTROLLER0_BUSOFF_ISR /* 024 */
#endif
#endif
#if (CAN_CONTROLLER0_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER0_RX_CAT2_ISR
#define INT_VECTOR_025  CAN_CONTROLLER0_RX_ISR /* 025 */
#else
#define INT_VECTOR_025 App_Os_CONTROLLER0_RX_ISR /* 025 */
#endif
#endif
#if (CAN_CONTROLLER0_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER0_TX_CAT2_ISR
#define INT_VECTOR_026  CAN_CONTROLLER0_TX_ISR /* 026 */
#else
#define INT_VECTOR_026 App_Os_CONTROLLER0_TX_ISR /* 026 */
#endif
#endif
#if ((CAN_CONTROLLER0_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER0_WAKEUP_CAT2_ISR
#define INT_VECTOR_037  CAN_CONTROLLER0_WAKEUP_ISR /* 037 */
#else
#define INT_VECTOR_037 App_Os_WAKEUP0_ISR /* 037 */
#endif
#endif
#if (CAN_CONTROLLER1_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER1_BUSOFF_CAT2_ISR
#define INT_VECTOR_113  CAN_CONTROLLER1_BUSOFF_ISR /* 113 */
#else
#define INT_VECTOR_113 App_Os_CONTROLLER1_BUSOFF_ISR /* 113 */
#endif
#endif
#if (CAN_CONTROLLER1_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER1_RX_CAT2_ISR
#define INT_VECTOR_114  CAN_CONTROLLER1_RX_ISR /* 114 */
#else
#define INT_VECTOR_114 App_Os_CONTROLLER1_RX_ISR /* 114 */
#endif
#endif
#if (CAN_CONTROLLER1_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER1_TX_CAT2_ISR
#define INT_VECTOR_115  CAN_CONTROLLER1_TX_ISR /* 115 */
#else
#define INT_VECTOR_115 App_Os_CONTROLLER1_TX_ISR /* 115 */
#endif
#endif
#if ((CAN_CONTROLLER1_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER1_WAKEUP_CAT2_ISR
#define INT_VECTOR_038  CAN_CONTROLLER1_WAKEUP_ISR /* 038 */
#else
#define INT_VECTOR_038 App_Os_WAKEUP1_ISR /* 038 */
#endif
#endif
#if (CAN_CONTROLLER2_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER2_BUSOFF_CAT2_ISR
#define INT_VECTOR_217  CAN_CONTROLLER2_BUSOFF_ISR /* 217 */
#else
#define INT_VECTOR_217  App_Os_CONTROLLER2_BUSOFF_ISR /* 217 */
#endif
#endif
#if (CAN_CONTROLLER2_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER2_RX_CAT2_ISR
#define INT_VECTOR_218  CAN_CONTROLLER2_RX_ISR /* 218 */
#else
#define INT_VECTOR_218  App_Os_CONTROLLER2_RX_ISR /* 218 */
#endif
#endif
#if (CAN_CONTROLLER2_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER2_TX_CAT2_ISR
#define INT_VECTOR_219  CAN_CONTROLLER2_TX_ISR /* 219 */
#else
#define INT_VECTOR_219  App_Os_CONTROLLER2_TX_ISR /* 219 */
#endif
#endif
#if ((CAN_CONTROLLER2_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER2_WAKEUP_CAT2_ISR
#define INT_VECTOR_039  CAN_CONTROLLER2_WAKEUP_ISR /* 039 */
#else
#define INT_VECTOR_039  App_Os_WAKEUP2_ISR /* 039 */
#endif
#endif
#if (CAN_CONTROLLER3_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER3_BUSOFF_CAT2_ISR
#define INT_VECTOR_220  CAN_CONTROLLER3_BUSOFF_ISR /* 220 */
#else
#define INT_VECTOR_220  App_Os_CONTROLLER3_BUSOFF_ISR /* 220 */
#endif
#endif
#if (CAN_CONTROLLER3_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER3_RX_CAT2_ISR
#define INT_VECTOR_221  CAN_CONTROLLER3_RX_ISR /* 221 */
#else
#define INT_VECTOR_221  App_Os_CONTROLLER3_RX_ISR /* 221 */
#endif
#endif
#if (CAN_CONTROLLER3_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER3_TX_CAT2_ISR
#define INT_VECTOR_222  CAN_CONTROLLER3_TX_ISR /* 222 */
#else
#define INT_VECTOR_222  App_Os_CONTROLLER3_TX_ISR /* 222 */
#endif
#endif
#if ((CAN_CONTROLLER3_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER3_WAKEUP_CAT2_ISR
#define INT_VECTOR_043  CAN_CONTROLLER3_WAKEUP_ISR /* 043 */
#else
#define INT_VECTOR_043  App_Os_WAKEUP3_ISR /* 043 */
#endif
#endif
#if (CAN_CONTROLLER4_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER4_BUSOFF_CAT2_ISR
#define INT_VECTOR_272  CAN_CONTROLLER4_BUSOFF_ISR /* 272 */
#else
#define INT_VECTOR_272  App_Os_CONTROLLER4_BUSOFF_ISR /* 272 */
#endif
#endif
#if (CAN_CONTROLLER4_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER4_RX_CAT2_ISR
#define INT_VECTOR_273  CAN_CONTROLLER4_RX_ISR /* 273 */
#else
#define INT_VECTOR_273  App_Os_CONTROLLER4_RX_ISR /* 273 */
#endif
#endif
#if (CAN_CONTROLLER4_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER4_TX_CAT2_ISR
#define INT_VECTOR_274  CAN_CONTROLLER4_TX_ISR /* 274 */
#else
#define INT_VECTOR_274  App_Os_CONTROLLER4_TX_ISR /* 274 */
#endif
#endif
#if ((CAN_CONTROLLER4_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER4_WAKEUP_CAT2_ISR
#define INT_VECTOR_044  CAN_CONTROLLER4_WAKEUP_ISR /* 044 */
#else
#define INT_VECTOR_044  App_Os_WAKEUP4_ISR /* 044 */
#endif
#endif
#if (CAN_CONTROLLER5_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER5_BUSOFF_CAT2_ISR
#define INT_VECTOR_287  CAN_CONTROLLER5_BUSOFF_ISR /* 287 */
#else
#define INT_VECTOR_287  App_Os_CONTROLLER5_BUSOFF_ISR /* 287 */
#endif
#endif
#if (CAN_CONTROLLER5_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER5_RX_CAT2_ISR
#define INT_VECTOR_288  CAN_CONTROLLER5_RX_ISR /* 288 */
#else
#define INT_VECTOR_288  App_Os_CONTROLLER5_RX_ISR /* 288 */
#endif
#endif
#if (CAN_CONTROLLER5_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER5_TX_CAT2_ISR
#define INT_VECTOR_289  CAN_CONTROLLER5_TX_ISR /* 289 */
#else
#define INT_VECTOR_289  App_Os_CONTROLLER5_TX_ISR /* 289 */
#endif
#endif
#if ((CAN_CONTROLLER5_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER5_WAKEUP_CAT2_ISR
#define INT_VECTOR_045  CAN_CONTROLLER5_WAKEUP_ISR /* 045 */
#else
#define INT_VECTOR_045  App_Os_WAKEUP5_ISR /* 045 */
#endif
#endif
#if (CAN_CONTROLLER6_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER6_BUSOFF_CAT2_ISR
#define INT_VECTOR_321  CAN_CONTROLLER6_BUSOFF_ISR /* 321 */
#else
#define INT_VECTOR_321  App_Os_CONTROLLER6_BUSOFF_ISR /* 321 */
#endif
#endif
#if (CAN_CONTROLLER6_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER6_RX_CAT2_ISR
#define INT_VECTOR_322  CAN_CONTROLLER6_RX_ISR /* 322 */
#else
#define INT_VECTOR_322  App_Os_CONTROLLER6_RX_ISR /* 322 */
#endif
#endif
#if (CAN_CONTROLLER6_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER6_TX_CAT2_ISR
#define INT_VECTOR_323  CAN_CONTROLLER6_TX_ISR /* 323 */
#else
#define INT_VECTOR_323  App_Os_CONTROLLER6_TX_ISR /* 323 */
#endif
#endif
#if ((CAN_CONTROLLER6_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER6_WAKEUP_CAT2_ISR
#define INT_VECTOR_128  CAN_CONTROLLER6_WAKEUP_ISR /* 128 */
#else
#define INT_VECTOR_128  App_Os_WAKEUP6_ISR /* 128 */
#endif
#endif
#if (CAN_CONTROLLER7_BUSOFF_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER7_BUSOFF_CAT2_ISR
#define INT_VECTOR_332  CAN_CONTROLLER7_BUSOFF_ISR /* 332 */
#else
#define INT_VECTOR_332  App_Os_CONTROLLER7_BUSOFF_ISR /* 332 */
#endif
#endif
#if (CAN_CONTROLLER7_RX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER7_RX_CAT2_ISR
#define INT_VECTOR_333  CAN_CONTROLLER7_RX_ISR /* 333 */
#else
#define INT_VECTOR_333  App_Os_CONTROLLER7_RX_ISR /* 333 */
#endif
#endif
#if (CAN_CONTROLLER7_TX_INTERRUPT == STD_ON)
#ifndef Os_CAN_CONTROLLER7_TX_CAT2_ISR
#define INT_VECTOR_334  CAN_CONTROLLER7_TX_ISR /* 334 */
#else
#define INT_VECTOR_334  App_Os_CONTROLLER7_TX_ISR /* 334 */
#endif
#endif
#if ((CAN_CONTROLLER7_WAKEUP_INTERRUPT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON))
#ifndef Os_CAN_CONTROLLER7_WAKEUP_CAT2_ISR
#define INT_VECTOR_205  CAN_CONTROLLER7_WAKEUP_ISR /* 205 */
#else
#define INT_VECTOR_205  App_Os_WAKEUP7_ISR /* 205 */
#endif
#endif

/*****************************************************************************/
/*                         Interrupt Vector Table                            */
/*****************************************************************************/
#pragma ghs section sdata=".inttable"
void (*IntVectors[])(void) = {
#ifdef INT_VECTOR_000
  INT_VECTOR_000, /* 000 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_001
  INT_VECTOR_001, /* 001 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_002
  INT_VECTOR_002, /* 002 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_003
  INT_VECTOR_003, /* 003 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_004
  INT_VECTOR_004, /* 004 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_005
  INT_VECTOR_005, /* 005 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_006
  INT_VECTOR_006, /* 006 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_007
  INT_VECTOR_007, /* 007 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_008
  INT_VECTOR_008, /* 008 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_009
  INT_VECTOR_009, /* 009 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_010
  INT_VECTOR_010, /* 010 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_011
  INT_VECTOR_011, /* 011 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_012
  INT_VECTOR_012, /* 012 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_013
  INT_VECTOR_013, /* 013 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_014
  INT_VECTOR_014, /* 014 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_015
  INT_VECTOR_015, /* 015 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_016
  INT_VECTOR_016, /* 016 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_017
  INT_VECTOR_017, /* 017 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_018
  INT_VECTOR_018, /* 018 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_019
  INT_VECTOR_019, /* 019 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_020
  INT_VECTOR_020, /* 020 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_021
  INT_VECTOR_021, /* 021 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_022
  INT_VECTOR_022, /* 022 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_023
  INT_VECTOR_023, /* 023 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_024
  INT_VECTOR_024, /* 024 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_025
  INT_VECTOR_025, /* 025 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_026
  INT_VECTOR_026, /* 026 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_027
  INT_VECTOR_027, /* 027 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_028
  INT_VECTOR_028, /* 028 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_029
  INT_VECTOR_029, /* 029 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_030
  INT_VECTOR_030, /* 030 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_031
  INT_VECTOR_031, /* 031 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_032
  INT_VECTOR_032, /* 032 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_033
  INT_VECTOR_033, /* 033 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_034
  INT_VECTOR_034, /* 034 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_035
  INT_VECTOR_035, /* 035 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_036
  INT_VECTOR_036, /* 036 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_037
  INT_VECTOR_037, /* 037 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_038
  INT_VECTOR_038, /* 038 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_039
  INT_VECTOR_039, /* 039 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_040
  INT_VECTOR_040, /* 040 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_041
  INT_VECTOR_041, /* 041 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_042
  INT_VECTOR_042, /* 042 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_043
  INT_VECTOR_043, /* 043 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_044
  INT_VECTOR_044, /* 044 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_045
  INT_VECTOR_045, /* 045 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_046
  INT_VECTOR_046, /* 046 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_047
  INT_VECTOR_047, /* 047 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_048
  INT_VECTOR_048, /* 048 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_049
  INT_VECTOR_049, /* 049 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_050
  INT_VECTOR_050, /* 050 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_051
  INT_VECTOR_051, /* 051 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_052
  INT_VECTOR_052, /* 052 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_053
  INT_VECTOR_053, /* 053 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_054
  INT_VECTOR_054, /* 054 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_055
  INT_VECTOR_055, /* 055 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_056
  INT_VECTOR_056, /* 056 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_057
  INT_VECTOR_057, /* 057 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_058
  INT_VECTOR_058, /* 058 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_059
  INT_VECTOR_059, /* 059 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_060
  INT_VECTOR_060, /* 060 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_061
  INT_VECTOR_061, /* 061 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_062
  INT_VECTOR_062, /* 062 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_063
  INT_VECTOR_063, /* 063 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_064
  INT_VECTOR_064, /* 064 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_065
  INT_VECTOR_065, /* 065 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_066
  INT_VECTOR_066, /* 066 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_067
  INT_VECTOR_067, /* 067 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_068
  INT_VECTOR_068, /* 068 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_069
  INT_VECTOR_069, /* 069 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_070
  INT_VECTOR_070, /* 070 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_071
  INT_VECTOR_071, /* 071 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_072
  INT_VECTOR_072, /* 072 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_073
  INT_VECTOR_073, /* 073 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_074
  INT_VECTOR_074, /* 074 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_075
  INT_VECTOR_075, /* 075 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_076
  INT_VECTOR_076, /* 076 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_077
  INT_VECTOR_077, /* 077 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_078
  INT_VECTOR_078, /* 078 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_079
  INT_VECTOR_079, /* 079 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_080
  INT_VECTOR_080, /* 080 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_081
  INT_VECTOR_081, /* 081 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_082
  INT_VECTOR_082, /* 082 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_083
  INT_VECTOR_083, /* 083 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_084
  INT_VECTOR_084, /* 084 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_085
  INT_VECTOR_085, /* 085 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_086
  INT_VECTOR_086, /* 086 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_087
  INT_VECTOR_087, /* 087 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_088
  INT_VECTOR_088, /* 088 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_089
  INT_VECTOR_089, /* 089 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_090
  INT_VECTOR_090, /* 090 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_091
  INT_VECTOR_091, /* 091 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_092
  INT_VECTOR_092, /* 092 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_093
  INT_VECTOR_093, /* 093 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_094
  INT_VECTOR_094, /* 094 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_095
  INT_VECTOR_095, /* 095 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_096
  INT_VECTOR_096, /* 096 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_097
  INT_VECTOR_097, /* 097 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_098
  INT_VECTOR_098, /* 098 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_099
  INT_VECTOR_099, /* 099 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_100
  INT_VECTOR_100, /* 100 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_101
  INT_VECTOR_101, /* 101 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_102
  INT_VECTOR_102, /* 102 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_103
  INT_VECTOR_103, /* 103 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_104
  INT_VECTOR_104, /* 104 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_105
  INT_VECTOR_105, /* 105 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_106
  INT_VECTOR_106, /* 106 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_107
  INT_VECTOR_107, /* 107 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_108
  INT_VECTOR_108, /* 108 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_109
  INT_VECTOR_109, /* 109 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_110
  INT_VECTOR_110, /* 110 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_111
  INT_VECTOR_111, /* 111 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_112
  INT_VECTOR_112, /* 112 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_113
  INT_VECTOR_113, /* 113 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_114
  INT_VECTOR_114, /* 114 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_115
  INT_VECTOR_115, /* 115 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_116
  INT_VECTOR_116, /* 116 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_117
  INT_VECTOR_117, /* 117 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_118
  INT_VECTOR_118, /* 118 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_119
  INT_VECTOR_119, /* 119 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_120
  INT_VECTOR_120, /* 120 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_121
  INT_VECTOR_121, /* 121 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_122
  INT_VECTOR_122, /* 122 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_123
  INT_VECTOR_123, /* 123 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_124
  INT_VECTOR_124, /* 124 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_125
  INT_VECTOR_125, /* 125 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_126
  INT_VECTOR_126, /* 126 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_127
  INT_VECTOR_127, /* 127 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_128
  INT_VECTOR_128, /* 128 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_129
  INT_VECTOR_129, /* 129 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_130
  INT_VECTOR_130, /* 130 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_131
  INT_VECTOR_131, /* 131 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_132
  INT_VECTOR_132, /* 132 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_133
  INT_VECTOR_133, /* 133 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_134
  INT_VECTOR_134, /* 134 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_135
  INT_VECTOR_135, /* 135 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_136
  INT_VECTOR_136, /* 136 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_137
  INT_VECTOR_137, /* 137 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_138
  INT_VECTOR_138, /* 138 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_139
  INT_VECTOR_139, /* 139 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_140
  INT_VECTOR_140, /* 140 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_141
  INT_VECTOR_141, /* 141 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_142
  INT_VECTOR_142, /* 142 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_143
  INT_VECTOR_143, /* 143 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_144
  INT_VECTOR_144, /* 144 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_145
  INT_VECTOR_145, /* 145 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_146
  INT_VECTOR_146, /* 146 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_147
  INT_VECTOR_147, /* 147 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_148
  INT_VECTOR_148, /* 148 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_149
  INT_VECTOR_149, /* 149 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_150
  INT_VECTOR_150, /* 150 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_151
  INT_VECTOR_151, /* 151 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_152
  INT_VECTOR_152, /* 152 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_153
  INT_VECTOR_153, /* 153 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_154
  INT_VECTOR_154, /* 154 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_155
  INT_VECTOR_155, /* 155 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_156
  INT_VECTOR_156, /* 156 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_157
  INT_VECTOR_157, /* 157 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_158
  INT_VECTOR_158, /* 158 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_159
  INT_VECTOR_159, /* 159 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_160
  INT_VECTOR_160, /* 160 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_161
  INT_VECTOR_161, /* 161 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_162
  INT_VECTOR_162, /* 162 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_163
  INT_VECTOR_163, /* 163 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_164
  INT_VECTOR_164, /* 164 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_165
  INT_VECTOR_165, /* 165 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_166
  INT_VECTOR_166, /* 166 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_167
  INT_VECTOR_167, /* 167 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_168
  INT_VECTOR_168, /* 168 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_169
  INT_VECTOR_169, /* 169 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_170
  INT_VECTOR_170, /* 170 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_171
  INT_VECTOR_171, /* 171 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_172
  INT_VECTOR_172, /* 172 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_173
  INT_VECTOR_173, /* 173 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_174
  INT_VECTOR_174, /* 174 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_175
  INT_VECTOR_175, /* 175 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_176
  INT_VECTOR_176, /* 176 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_177
  INT_VECTOR_177, /* 177 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_178
  INT_VECTOR_178, /* 178 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_179
  INT_VECTOR_179, /* 179 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_180
  INT_VECTOR_180, /* 180 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_181
  INT_VECTOR_181, /* 181 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_182
  INT_VECTOR_182, /* 182 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_183
  INT_VECTOR_183, /* 183 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_184
  INT_VECTOR_184, /* 184 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_185
  INT_VECTOR_185, /* 185 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_186
  INT_VECTOR_186, /* 186 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_187
  INT_VECTOR_187, /* 187 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_188
  INT_VECTOR_188, /* 188 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_189
  INT_VECTOR_189, /* 189 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_190
  INT_VECTOR_190, /* 190 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_191
  INT_VECTOR_191, /* 191 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_192
  INT_VECTOR_192, /* 192 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_193
  INT_VECTOR_193, /* 193 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_194
  INT_VECTOR_194, /* 194 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_195
  INT_VECTOR_195, /* 195 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_196
  INT_VECTOR_196, /* 196 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_197
  INT_VECTOR_197, /* 197 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_198
  INT_VECTOR_198, /* 198 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_199
  INT_VECTOR_199, /* 199 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_200
  INT_VECTOR_200, /* 200 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_201
  INT_VECTOR_201, /* 201 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_202
  INT_VECTOR_202, /* 202 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_203
  INT_VECTOR_203, /* 203 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_204
  INT_VECTOR_204, /* 204 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_205
  INT_VECTOR_205, /* 205 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_206
  INT_VECTOR_206, /* 206 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_207
  INT_VECTOR_207, /* 207 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_208
  INT_VECTOR_208, /* 208 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_209
  INT_VECTOR_209, /* 209 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_210
  INT_VECTOR_210, /* 210 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_211
  INT_VECTOR_211, /* 211 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_212
  INT_VECTOR_212, /* 212 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_213
  INT_VECTOR_213, /* 213 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_214
  INT_VECTOR_214, /* 214 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_215
  INT_VECTOR_215, /* 215 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_216
  INT_VECTOR_216, /* 216 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_217
  INT_VECTOR_217, /* 217 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_218
  INT_VECTOR_218, /* 218 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_219
  INT_VECTOR_219, /* 219 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_220
  INT_VECTOR_220, /* 220 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_221
  INT_VECTOR_221, /* 221 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_222
  INT_VECTOR_222, /* 222 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_223
  INT_VECTOR_223, /* 223 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_224
  INT_VECTOR_224, /* 224 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_225
  INT_VECTOR_225, /* 225 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_226
  INT_VECTOR_226, /* 226 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_227
  INT_VECTOR_227, /* 227 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_228
  INT_VECTOR_228, /* 228 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_229
  INT_VECTOR_229, /* 229 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_230
  INT_VECTOR_230, /* 230 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_231
  INT_VECTOR_231, /* 231 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_232
  INT_VECTOR_232, /* 232 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_233
  INT_VECTOR_233, /* 233 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_234
  INT_VECTOR_234, /* 234 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_235
  INT_VECTOR_235, /* 235 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_236
  INT_VECTOR_236, /* 236 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_237
  INT_VECTOR_237, /* 237 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_238
  INT_VECTOR_238, /* 238 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_239
  INT_VECTOR_239, /* 239 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_240
  INT_VECTOR_240, /* 240 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_241
  INT_VECTOR_241, /* 241 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_242
  INT_VECTOR_242, /* 242 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_243
  INT_VECTOR_243, /* 243 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_244
  INT_VECTOR_244, /* 244 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_245
  INT_VECTOR_245, /* 245 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_246
  INT_VECTOR_246, /* 246 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_247
  INT_VECTOR_247, /* 247 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_248
  INT_VECTOR_248, /* 248 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_249
  INT_VECTOR_249, /* 249 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_250
  INT_VECTOR_250, /* 250 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_251
  INT_VECTOR_251, /* 251 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_252
  INT_VECTOR_252, /* 252 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_253
  INT_VECTOR_253, /* 253 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_254
  INT_VECTOR_254, /* 254 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_255
  INT_VECTOR_255, /* 255 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_256
  INT_VECTOR_256, /* 256 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_257
  INT_VECTOR_257, /* 257 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_258
  INT_VECTOR_258, /* 258 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_259
  INT_VECTOR_259, /* 259 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_260
  INT_VECTOR_260, /* 260 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_261
  INT_VECTOR_261, /* 261 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_262
  INT_VECTOR_262, /* 262 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_263
  INT_VECTOR_263, /* 263 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_264
  INT_VECTOR_264, /* 264 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_265
  INT_VECTOR_265, /* 265 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_266
  INT_VECTOR_266, /* 266 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_267
  INT_VECTOR_267, /* 267 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_268
  INT_VECTOR_268, /* 268 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_269
  INT_VECTOR_269, /* 269 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_270
  INT_VECTOR_270, /* 270 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_271
  INT_VECTOR_271, /* 271 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_272
  INT_VECTOR_272, /* 272 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_273
  INT_VECTOR_273, /* 273 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_274
  INT_VECTOR_274, /* 274 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_275
  INT_VECTOR_275, /* 275 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_276
  INT_VECTOR_276, /* 276 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_277
  INT_VECTOR_277, /* 277 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_278
  INT_VECTOR_278, /* 278 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_279
  INT_VECTOR_279, /* 279 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_280
  INT_VECTOR_280, /* 280 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_281
  INT_VECTOR_281, /* 281 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_282
  INT_VECTOR_282, /* 282 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_283
  INT_VECTOR_283, /* 283 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_284
  INT_VECTOR_284, /* 284 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_285
  INT_VECTOR_285, /* 285 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_286
  INT_VECTOR_286, /* 286 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_287
  INT_VECTOR_287, /* 287 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_288
  INT_VECTOR_288, /* 288 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_289
  INT_VECTOR_289, /* 289 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_290
  INT_VECTOR_290, /* 290 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_291
  INT_VECTOR_291, /* 291 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_292
  INT_VECTOR_292, /* 292 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_293
  INT_VECTOR_293, /* 293 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_294
  INT_VECTOR_294, /* 294 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_295
  INT_VECTOR_295, /* 295 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_296
  INT_VECTOR_296, /* 296 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_297
  INT_VECTOR_297, /* 297 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_298
  INT_VECTOR_298, /* 298 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_299
  INT_VECTOR_299, /* 299 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_300
  INT_VECTOR_300, /* 300 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_301
  INT_VECTOR_301, /* 301 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_302
  INT_VECTOR_302, /* 302 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_303
  INT_VECTOR_303, /* 303 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_304
  INT_VECTOR_304, /* 304 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_305
  INT_VECTOR_305, /* 305 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_306
  INT_VECTOR_306, /* 306 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_307
  INT_VECTOR_307, /* 307 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_308
  INT_VECTOR_308, /* 308 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_309
  INT_VECTOR_309, /* 309 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_310
  INT_VECTOR_310, /* 310 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_311
  INT_VECTOR_311, /* 311 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_312
  INT_VECTOR_312, /* 312 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_313
  INT_VECTOR_313, /* 313 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_314
  INT_VECTOR_314, /* 314 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_315
  INT_VECTOR_315, /* 315 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_316
  INT_VECTOR_316, /* 316 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_317
  INT_VECTOR_317, /* 317 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_318
  INT_VECTOR_318, /* 318 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_319
  INT_VECTOR_319, /* 319 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_320
  INT_VECTOR_320, /* 320 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_321
  INT_VECTOR_321, /* 321 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_322
  INT_VECTOR_322, /* 322 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_323
  INT_VECTOR_323, /* 323 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_324
  INT_VECTOR_324, /* 324 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_325
  INT_VECTOR_325, /* 325 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_326
  INT_VECTOR_326, /* 326 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_327
  INT_VECTOR_327, /* 327 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_328
  INT_VECTOR_328, /* 328 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_329
  INT_VECTOR_329, /* 329 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_330
  INT_VECTOR_330, /* 330 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_331
  INT_VECTOR_331, /* 331 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_332
  INT_VECTOR_332, /* 332 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_333
  INT_VECTOR_333, /* 333 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_334
  INT_VECTOR_334, /* 334 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_335
  INT_VECTOR_335, /* 335 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_336
  INT_VECTOR_336, /* 336 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_337
  INT_VECTOR_337, /* 337 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_338
  INT_VECTOR_338, /* 338 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_339
  INT_VECTOR_339, /* 339 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_340
  INT_VECTOR_340, /* 340 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_341
  INT_VECTOR_341, /* 341 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_342
  INT_VECTOR_342, /* 342 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_343
  INT_VECTOR_343, /* 343 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_344
  INT_VECTOR_344, /* 344 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_345
  INT_VECTOR_345, /* 345 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_346
  INT_VECTOR_346, /* 346 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_347
  INT_VECTOR_347, /* 347 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_348
  INT_VECTOR_348, /* 348 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_349
  INT_VECTOR_349, /* 349 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_350
  INT_VECTOR_350, /* 350 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_351
  INT_VECTOR_351, /* 351 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_352
  INT_VECTOR_352, /* 352 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_353
  INT_VECTOR_353, /* 353 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_354
  INT_VECTOR_354, /* 354 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_355
  INT_VECTOR_355, /* 355 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_356
  INT_VECTOR_356, /* 356 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_357
  INT_VECTOR_357 /* 357 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_358
  INT_VECTOR_358 /* 358 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_359
  INT_VECTOR_359 /* 359 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_360
  INT_VECTOR_360 /* 360 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_361
  INT_VECTOR_361 /* 361 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_362
  INT_VECTOR_362 /* 362 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_363
  INT_VECTOR_363 /* 363 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_364
  INT_VECTOR_364 /* 364 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_365
  INT_VECTOR_365 /* 365 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_366
  INT_VECTOR_366 /* 366 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_367
  INT_VECTOR_367 /* 367 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_368
  INT_VECTOR_368 /* 368 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_369
  INT_VECTOR_369 /* 369 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_370
  INT_VECTOR_370 /* 370 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_371
  INT_VECTOR_371 /* 371 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_372
  INT_VECTOR_372 /* 372 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_373
  INT_VECTOR_373 /* 373 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_374
  INT_VECTOR_374 /* 374 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_375
  INT_VECTOR_375 /* 375 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_376
  INT_VECTOR_376 /* 376 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_377
  INT_VECTOR_377 /* 377 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_378
  INT_VECTOR_378 /* 378 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_379
  INT_VECTOR_379 /* 379 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_380
  INT_VECTOR_380 /* 380 */
#else
  Dummy_ISR,
#endif
#ifdef INT_VECTOR_381
  INT_VECTOR_381 /* 381 */
#else
  Dummy_ISR,
#endif
};
#pragma ghs section sdata=default
#endif

/*****************************************************************************/
/*                         CORTST F1KM-S2 IVT                                */
/*****************************************************************************/
#ifdef CORTST_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), Timer_Task, DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef CORTST_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         DIO F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef DIO_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef DIO_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         FLS F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef FLS_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  /* 60 */
  #if(FLS_DMA00_ISR_API == STD_ON)
    FLS_DMA00_ISR,
  #else
    DUMMY(060),
  #endif
  /* 61 */
  #if(FLS_DMA01_ISR_API == STD_ON)
    FLS_DMA01_ISR,
  #else
    DUMMY(061),
  #endif
  /* 62 */
  #if(FLS_DMA02_ISR_API == STD_ON)
    FLS_DMA02_ISR,
  #else
    DUMMY(062),
  #endif
  /* 63 */
  #if(FLS_DMA03_ISR_API == STD_ON)
    FLS_DMA03_ISR,
  #else
    DUMMY(063),
  #endif
  /* 64 */
  #if(FLS_DMA04_ISR_API == STD_ON)
    FLS_DMA04_ISR,
  #else
    DUMMY(064),
  #endif
  /* 65 */
  #if(FLS_DMA05_ISR_API == STD_ON)
    FLS_DMA05_ISR,
  #else
    DUMMY(065),
  #endif
  /* 66 */
  #if(FLS_DMA06_ISR_API == STD_ON)
    FLS_DMA06_ISR,
  #else
    DUMMY(066),
  #endif
  /* 67 */
  #if(FLS_DMA07_ISR_API == STD_ON)
    FLS_DMA07_ISR,
  #else
    DUMMY(067),
  #endif
  /* 68 */
  #if(FLS_DMA08_ISR_API == STD_ON)
    FLS_DMA08_ISR,
  #else
    DUMMY(068),
  #endif
  /* 69 */
  #if(FLS_DMA09_ISR_API == STD_ON)
    FLS_DMA09_ISR,
  #else
   DUMMY(069),
  #endif
  /* 70 */
  #if(FLS_DMA10_ISR_API == STD_ON)
    FLS_DMA10_ISR,
  #else
    DUMMY(070),
  #endif
  /* 71 */
  #if(FLS_DMA11_ISR_API == STD_ON)
    FLS_DMA11_ISR,
  #else
    DUMMY(071),
  #endif
  /* 72 */
  #if(FLS_DMA12_ISR_API == STD_ON)
    FLS_DMA12_ISR,
  #else
   DUMMY(072),
  #endif
  /* 73 */
  #if(FLS_DMA13_ISR_API == STD_ON)
    FLS_DMA13_ISR,
  #else
    DUMMY(073),
  #endif
  /* 74 */
  #if(FLS_DMA14_ISR_API == STD_ON)
    FLS_DMA14_ISR,
  #else
    DUMMY(074),
  #endif
  /* 75 */
  #if(FLS_DMA15_ISR_API == STD_ON)
    FLS_DMA15_ISR,
  #else
    DUMMY(075),
  #endif
  DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110),
  #if(FLS_INTERRUPT_MODE == STD_ON)
   #ifdef Os_FLS_FLENDNM_CAT2_ISR
   /* 111 */
   App_Os_FLS_FLENDNM_ISR,
   #else
   /* 111 */
   FLS_FLENDNM_ISR,
   #endif
   #else
   /* 111 */
   DUMMY(111),
  #endif
  DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297),
  /* 298 */
  #if(FLS_DMA16_ISR_API == STD_ON)
    FLS_DMA16_ISR,
  #else
    DUMMY(298),
  #endif
  /* 299 */
  #if(FLS_DMA17_ISR_API == STD_ON)
    FLS_DMA17_ISR,
  #else
    DUMMY(299),
  #endif
  /* 300 */
  #if(FLS_DMA18_ISR_API == STD_ON)
    FLS_DMA18_ISR,
  #else
    DUMMY(300),
  #endif
  /* 301 */
  #if(FLS_DMA19_ISR_API == STD_ON)
    FLS_DMA19_ISR,
  #else
    DUMMY(301),
  #endif
  /* 302 */
  #if(FLS_DMA20_ISR_API == STD_ON)
    FLS_DMA20_ISR,
  #else
    DUMMY(302),
  #endif
  /* 303 */
  #if(FLS_DMA21_ISR_API == STD_ON)
    FLS_DMA21_ISR,
  #else
    DUMMY(303),
  #endif
  /* 304 */
  #if(FLS_DMA22_ISR_API == STD_ON)
    FLS_DMA22_ISR,
  #else
    DUMMY(304),
  #endif
  /* 305 */
  #if(FLS_DMA23_ISR_API == STD_ON)
    FLS_DMA23_ISR,
  #else
    DUMMY(305),
  #endif
  /* 306 */
  #if(FLS_DMA24_ISR_API == STD_ON)
    FLS_DMA24_ISR,
  #else
    DUMMY(306),
  #endif
  /* 307 */
  #if(FLS_DMA25_ISR_API == STD_ON)
    FLS_DMA25_ISR,
  #else
    DUMMY(307),
  #endif
  /* 308 */
  #if(FLS_DMA26_ISR_API == STD_ON)
    FLS_DMA26_ISR,
  #else
    DUMMY(308),
  #endif
  /* 309 */
  #if(FLS_DMA27_ISR_API == STD_ON)
    FLS_DMA27_ISR,
  #else
    DUMMY(309),
  #endif
  /* 310 */
  #if(FLS_DMA28_ISR_API == STD_ON)
    FLS_DMA28_ISR,
  #else
    DUMMY(310),
  #endif
  /* 311 */
  #if(FLS_DMA29_ISR_API == STD_ON)
    FLS_DMA29_ISR,
  #else
    DUMMY(311),
  #endif
  /* 312 */
  #if(FLS_DMA30_ISR_API == STD_ON)
    FLS_DMA30_ISR,
  #else
    DUMMY(312),
  #endif
  /* 313 */
  #if(FLS_DMA31_ISR_API == STD_ON)
    FLS_DMA31_ISR,
  #else
    DUMMY(313),
  #endif
  DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef FLS_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         FLSTST F1KM-S2 IVT                                */
/*****************************************************************************/
#ifdef FLSTST_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef FLSTST_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         FR F1KM-S2 IVT                                    */
/*****************************************************************************/
#ifdef FR_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  #ifdef FR_SAMPLE_TEST
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), INTFLXA0TIM0, DUMMY(182), INTFLXA0TIM2, DUMMY(184), DUMMY(185),
  #else
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), INTFLXA0FDA,
  INTFLXA0FW, INTFLXA0IQE, INTFLXA0IQF, INTFLXA0OT, INTFLXA0OW, INTFLXA0LINE0,
  INTFLXA0LINE1, INTFLXA0TIM0, DUMMY(182), INTFLXA0TIM2, DUMMY(184), DUMMY(185),
  #endif
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef FR_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         GPT F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef GPT_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (GPT_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
    #else
      App_Os_TAUD0_CH00_ISR,
    #endif
  #else
    DUMMY(008),
  #endif

  #if (GPT_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (GPT_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (GPT_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (GPT_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (GPT_TAUD0_CH10_ISR_API == STD_ON)
  TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (GPT_TAUD0_CH12_ISR_API == STD_ON)
  TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (GPT_TAUD0_CH14_ISR_API == STD_ON)
  TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),

   #if (GPT_TAUD0_CH01_ISR_API == STD_ON)
   TAUD0_CH01_ISR,
   #else
    DUMMY(048),
   #endif

   #if (GPT_TAUD0_CH03_ISR_API == STD_ON)
   TAUD0_CH03_ISR,
   #else
    DUMMY(049),
   #endif

   #if (GPT_TAUD0_CH05_ISR_API == STD_ON)
    TAUD0_CH05_ISR,
   #else
    DUMMY(050),
   #endif

   #if (GPT_TAUD0_CH07_ISR_API == STD_ON)
      #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
        TAUD0_CH07_ISR,
      #else
       App_Os_TAUD0_CH07_ISR,
      #endif
   #else
      DUMMY(051),
   #endif

  #if (GPT_TAUD0_CH09_ISR_API == STD_ON)
   TAUD0_CH09_ISR,
  #else
   DUMMY(052),
  #endif

  #if (GPT_TAUD0_CH11_ISR_API == STD_ON)
   TAUD0_CH11_ISR,
  #else
   DUMMY(053),
  #endif

  #if (GPT_TAUD0_CH13_ISR_API == STD_ON)
   TAUD0_CH13_ISR,
  #else
   DUMMY(054),
  #endif

  #if (GPT_TAUD0_CH15_ISR_API == STD_ON)
   TAUD0_CH15_ISR,
  #else
   DUMMY(055),
  #endif


  DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079),

  #if (GPT_TAUJ0_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUJ0_CH00_ISR,
    #else
      App_Os_TAUJ0_CH00_ISR,
    #endif
  #else
    DUMMY(080),
  #endif

  #if (GPT_TAUJ0_CH01_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUJ0_CH01_ISR,
    #else
      App_Os_TAUJ0_CH01_ISR,
    #endif
  #else
    DUMMY(081),
  #endif

  #if (GPT_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(082),
  #endif

  #if (GPT_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(083),
  #endif

  #if (GPT_OSTM0_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      OSTM0_CH00_ISR,
    #else
      App_Os_OSTM0_CH01_ISR,
    #endif
  #else
    DUMMY(084),
  #endif

  DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141),

  #if (GPT_TAUB0_CH00_ISR_API == STD_ON)
   TAUB0_CH00_ISR,
  #else
   DUMMY(142),
  #endif

  #if (GPT_TAUB0_CH01_ISR_API == STD_ON)
   TAUB0_CH01_ISR,
  #else
   DUMMY(143),
  #endif

  #if (GPT_TAUB0_CH02_ISR_API == STD_ON)
   TAUB0_CH02_ISR,
  #else
   DUMMY(144),
  #endif

  #if (GPT_TAUB0_CH03_ISR_API == STD_ON)
   TAUB0_CH03_ISR,
  #else
   DUMMY(145),
  #endif

  #if (GPT_TAUB0_CH04_ISR_API == STD_ON)
   TAUB0_CH04_ISR,
  #else
   DUMMY(146),
  #endif

  #if (GPT_TAUB0_CH05_ISR_API == STD_ON)
   TAUB0_CH05_ISR,
  #else
   DUMMY(147),
  #endif

  #if (GPT_TAUB0_CH06_ISR_API == STD_ON)
   TAUB0_CH06_ISR,
  #else
   DUMMY(148),
  #endif

  #if (GPT_TAUB0_CH07_ISR_API == STD_ON)
   TAUB0_CH07_ISR,
  #else
   DUMMY(149),
  #endif

  #if (GPT_TAUB0_CH08_ISR_API == STD_ON)
   TAUB0_CH08_ISR,
  #else
   DUMMY(150),
  #endif

  #if (GPT_TAUB0_CH09_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUB0_CH09_ISR,
    #else
      App_Os_TAUB0_CH09_ISR,
    #endif
  #else
    DUMMY(151),
  #endif

  #if (GPT_TAUB0_CH10_ISR_API == STD_ON)
   TAUB0_CH10_ISR,
  #else
    DUMMY(152),
  #endif

  #if (GPT_TAUB0_CH11_ISR_API == STD_ON)
   TAUB0_CH11_ISR,
  #else
    DUMMY(153),
  #endif

  #if (GPT_TAUB0_CH12_ISR_API == STD_ON)
   TAUB0_CH12_ISR,
  #else
    DUMMY(154),
  #endif

  #if (GPT_TAUB0_CH13_ISR_API == STD_ON)
   TAUB0_CH13_ISR,
  #else
    DUMMY(155),
  #endif

  #if (GPT_TAUB0_CH14_ISR_API == STD_ON)
   TAUB0_CH14_ISR,
  #else
    DUMMY(156),
  #endif

  #if (GPT_TAUB0_CH15_ISR_API == STD_ON)
   TAUB0_CH15_ISR,
  #else
    DUMMY(157),
  #endif

  DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),DUMMY(162), DUMMY(163),
  DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (GPT_TAUJ1_CH00_ISR_API == STD_ON)
   TAUJ1_CH00_ISR,
  #else
   DUMMY(168),
  #endif

  #if (GPT_TAUJ1_CH01_ISR_API == STD_ON)
   TAUJ1_CH01_ISR,
  #else
   DUMMY(169),
  #endif

  #if (GPT_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
   DUMMY(170),
  #endif

  #if (GPT_TAUJ1_CH03_ISR_API == STD_ON)
   TAUJ1_CH03_ISR,
  #else
   DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255),

  #if (GPT_TAUB1_CH00_ISR_API == STD_ON)
    #ifndef APP_GPT_INTERRUPT_TYPE_CAT2
      TAUB1_CH00_ISR,
    #else
      App_Os_TAUB1_CH00_ISR,
    #endif
  #else
     DUMMY(256),
  #endif

  #if (GPT_TAUB1_CH01_ISR_API == STD_ON)
    TAUB1_CH01_ISR,
  #else
    DUMMY(257),
  #endif

  #if (GPT_TAUB1_CH02_ISR_API == STD_ON)
    TAUB1_CH02_ISR,
  #else
    DUMMY(258),
  #endif

  #if (GPT_TAUB1_CH03_ISR_API == STD_ON)
    TAUB1_CH03_ISR,
  #else
    DUMMY(259),
  #endif

  #if (GPT_TAUB1_CH04_ISR_API == STD_ON)
    TAUB1_CH04_ISR,
  #else
    DUMMY(260),
  #endif

  #if (GPT_TAUB1_CH05_ISR_API == STD_ON)
    TAUB1_CH05_ISR,
  #else
    DUMMY(261),
  #endif

  #if (GPT_TAUB1_CH06_ISR_API == STD_ON)
    TAUB1_CH06_ISR,
  #else
    DUMMY(262),
  #endif

  #if (GPT_TAUB1_CH07_ISR_API == STD_ON)
    TAUB1_CH07_ISR,
  #else
    DUMMY(263),
  #endif

  #if (GPT_TAUB1_CH08_ISR_API == STD_ON)
   TAUB1_CH08_ISR,
  #else
   DUMMY(264),
  #endif

  #if (GPT_TAUB1_CH09_ISR_API == STD_ON)
    TAUB1_CH09_ISR,
  #else
    DUMMY(265),
  #endif

  #if (GPT_TAUB1_CH10_ISR_API == STD_ON)
    TAUB1_CH10_ISR,
  #else
    DUMMY(266),
  #endif

  #if (GPT_TAUB1_CH11_ISR_API == STD_ON)
    TAUB1_CH11_ISR,
  #else
    DUMMY(267),
  #endif

  #if (GPT_TAUB1_CH12_ISR_API == STD_ON)
    TAUB1_CH12_ISR,
  #else
    DUMMY(268),
  #endif

  #if (GPT_TAUB1_CH13_ISR_API == STD_ON)
   TAUB1_CH13_ISR,
  #else
   DUMMY(269),
  #endif

  #if (GPT_TAUB1_CH14_ISR_API == STD_ON)
    TAUB1_CH14_ISR,
  #else
    DUMMY(270),
  #endif

  #if (GPT_TAUB1_CH15_ISR_API == STD_ON)
    TAUB1_CH15_ISR,
  #else
    DUMMY(271),
  #endif

  DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275), DUMMY(276),

  #if (GPT_TAUJ2_CH00_ISR_API == STD_ON)
    TAUJ2_CH00_ISR,
  #else
    DUMMY(277),
  #endif

  #if (GPT_TAUJ2_CH01_ISR_API == STD_ON)
    TAUJ2_CH01_ISR,
  #else
    DUMMY(278),
  #endif

  #if (GPT_TAUJ2_CH02_ISR_API == STD_ON)
    TAUJ2_CH02_ISR,
  #else
    DUMMY(279),
  #endif

  #if (GPT_TAUJ2_CH03_ISR_API == STD_ON)
    TAUJ2_CH03_ISR,
  #else
    DUMMY(280),
  #endif

  #if (GPT_TAUJ3_CH00_ISR_API == STD_ON)
    TAUJ3_CH00_ISR,
  #else
    DUMMY(281),
  #endif

  #if (GPT_TAUJ3_CH01_ISR_API == STD_ON)
    TAUJ3_CH01_ISR,
  #else
    DUMMY(282),
  #endif

  #if (GPT_TAUJ3_CH02_ISR_API == STD_ON)
    TAUJ3_CH02_ISR,
  #else
    DUMMY(283),
  #endif

  #if (GPT_TAUJ3_CH03_ISR_API == STD_ON)
    TAUJ3_CH03_ISR,
  #else
    DUMMY(284),
  #endif

  DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef GPT_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         ICU F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef ICU_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (ICU_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
      #else
      App_Os_TAUD0_CH00_ISR,
      #endif
   #else
    DUMMY(008),
  #endif

  #if (ICU_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (ICU_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (ICU_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (ICU_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (ICU_TAUD0_CH10_ISR_API == STD_ON)
    TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (ICU_TAUD0_CH12_ISR_API == STD_ON)
    TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (ICU_TAUD0_CH14_ISR_API == STD_ON)
    TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017), DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021),
  DUMMY(022), DUMMY(023), DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027),
  DUMMY(028), DUMMY(029), DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033),
  DUMMY(034), DUMMY(035), DUMMY(036),

  #if (ICU_EXT_INTP_CH00_ISR_API == STD_ON)
  EXT_INTP_CH00_ISR,
  #else
    DUMMY(037),
  #endif

   #if (ICU_EXT_INTP_CH01_ISR_API == STD_ON)
   EXT_INTP_CH01_ISR,
   #else
    DUMMY(038),
   #endif

   #if (ICU_EXT_INTP_CH02_ISR_API == STD_ON)
     EXT_INTP_CH02_ISR,
   #else
    DUMMY(039),
   #endif

  DUMMY(040), DUMMY(041), DUMMY(042),

  #if (ICU_EXT_INTP_CH03_ISR_API == STD_ON)
    EXT_INTP_CH03_ISR,
   #else
    DUMMY(043),
   #endif

   #if (ICU_EXT_INTP_CH04_ISR_API == STD_ON)
       #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
       EXT_INTP_CH04_ISR,
       #else
       App_Os_EXT_INTP_CH04_ISR,
       #endif
   #else
    DUMMY(44),
   #endif

   #if (ICU_EXT_INTP_CH05_ISR_API == STD_ON)
     EXT_INTP_CH05_ISR,
   #else
    DUMMY(45),
   #endif

    #if (ICU_EXT_INTP_CH10_ISR_API == STD_ON)
     EXT_INTP_CH10_ISR,
   #else
    DUMMY(46),
   #endif

   #if (ICU_EXT_INTP_CH11_ISR_API == STD_ON)
     EXT_INTP_CH11_ISR,
   #else
    DUMMY(47),
   #endif

  #if (ICU_TAUD0_CH01_ISR_API == STD_ON)
    TAUD0_CH01_ISR,
  #else
    DUMMY(48),
  #endif

  #if (ICU_TAUD0_CH03_ISR_API == STD_ON)
    TAUD0_CH03_ISR,
  #else
    DUMMY(49),
  #endif

  #if (ICU_TAUD0_CH05_ISR_API == STD_ON)
    TAUD0_CH05_ISR,
  #else
    DUMMY(50),
  #endif

  #if (ICU_TAUD0_CH07_ISR_API == STD_ON)

    #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
        TAUD0_CH07_ISR,
    #else
        App_Os_TAUD0_CH07_ISR,
    #endif
  #else
    DUMMY(51),
  #endif

  #if (ICU_TAUD0_CH09_ISR_API == STD_ON)
    TAUD0_CH09_ISR,
  #else
    DUMMY(52),
  #endif

  #if (ICU_TAUD0_CH11_ISR_API == STD_ON)
    TAUD0_CH11_ISR,
  #else
    DUMMY(53),
  #endif

  #if (ICU_TAUD0_CH13_ISR_API == STD_ON)
    TAUD0_CH13_ISR,
  #else
    DUMMY(54),
  #endif

  #if (ICU_TAUD0_CH15_ISR_API == STD_ON)
    TAUD0_CH15_ISR,
  #else
    DUMMY(55),
  #endif

  DUMMY(56), DUMMY(57), DUMMY(58), DUMMY(59), DUMMY(60), DUMMY(61), DUMMY(62),
  DUMMY(63), DUMMY(64), DUMMY(65), DUMMY(66), DUMMY(67), DUMMY(68), DUMMY(69),
  DUMMY(70), DUMMY(71), DUMMY(72), DUMMY(73), DUMMY(74), DUMMY(75), DUMMY(76),
  DUMMY(77), DUMMY(78), DUMMY(79),

  #if (ICU_TAUJ0_CH00_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUJ0_CH00_ISR,
      #else
            App_Os_TAUJ0_CH00_ISR,
      #endif
  #else
    DUMMY(80),
  #endif

  #if (ICU_TAUJ0_CH01_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUJ0_CH01_ISR,
      #else
            App_Os_TAUJ0_CH01_ISR,
      #endif
  #else
    DUMMY(81),
  #endif

  #if (ICU_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(82),
  #endif

  #if (ICU_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(83),
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127),

   #if (ICU_EXT_INTP_CH06_ISR_API == STD_ON)
     EXT_INTP_CH06_ISR,
   #else
    DUMMY(128),
   #endif

   #if (ICU_EXT_INTP_CH07_ISR_API == STD_ON)
     EXT_INTP_CH07_ISR,
   #else
    DUMMY(129),
   #endif

   #if (ICU_EXT_INTP_CH08_ISR_API == STD_ON)
     EXT_INTP_CH08_ISR,
   #else
    DUMMY(130),
   #endif

   #if (ICU_EXT_INTP_CH12_ISR_API == STD_ON)
     EXT_INTP_CH12_ISR,
   #else
    DUMMY(131),
   #endif

  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141),

  #if (ICU_TAUB0_CH00_ISR_API == STD_ON)
    TAUB0_CH00_ISR,
  #else
    DUMMY(142),
  #endif

  #if (ICU_TAUB0_CH01_ISR_API == STD_ON)
    TAUB0_CH01_ISR,
  #else
    DUMMY(143),
  #endif

  #if (ICU_TAUB0_CH02_ISR_API == STD_ON)
    TAUB0_CH02_ISR,
  #else
    DUMMY(144),
  #endif

  #if (ICU_TAUB0_CH03_ISR_API == STD_ON)
    TAUB0_CH03_ISR,
  #else
    DUMMY(145),
  #endif

  #if (ICU_TAUB0_CH04_ISR_API == STD_ON)
    TAUB0_CH04_ISR,
  #else
    DUMMY(146),
  #endif

  #if (ICU_TAUB0_CH05_ISR_API == STD_ON)
    TAUB0_CH05_ISR,
  #else
    DUMMY(147),
  #endif

  #if (ICU_TAUB0_CH06_ISR_API == STD_ON)
    TAUB0_CH06_ISR,
  #else
    DUMMY(148),
  #endif

  #if (ICU_TAUB0_CH07_ISR_API == STD_ON)
    TAUB0_CH07_ISR,
  #else
    DUMMY(149),
  #endif

  #if (ICU_TAUB0_CH08_ISR_API == STD_ON)
    TAUB0_CH08_ISR,
  #else
    DUMMY(150),
  #endif

  #if (ICU_TAUB0_CH09_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUB0_CH09_ISR,
      #else
            App_Os_TAUB0_CH09_ISR,
      #endif
  #else
    DUMMY(151),
  #endif

  #if (ICU_TAUB0_CH10_ISR_API == STD_ON)
    TAUB0_CH10_ISR,
  #else
    DUMMY(152),
  #endif

  #if (ICU_TAUB0_CH11_ISR_API == STD_ON)
    TAUB0_CH11_ISR,
  #else
    DUMMY(153),
  #endif

  #if (ICU_TAUB0_CH12_ISR_API == STD_ON)
    TAUB0_CH12_ISR,
  #else
    DUMMY(154),
  #endif

  #if (ICU_TAUB0_CH13_ISR_API == STD_ON)
    TAUB0_CH13_ISR,
  #else
    DUMMY(155),
  #endif

  #if (ICU_TAUB0_CH14_ISR_API == STD_ON)
    TAUB0_CH14_ISR,
  #else
    DUMMY(156),
  #endif

  #if (ICU_TAUB0_CH15_ISR_API == STD_ON)
    TAUB0_CH15_ISR,
  #else
    DUMMY(157),
  #endif

  DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161), DUMMY(162), DUMMY(163),
  DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (ICU_TAUJ1_CH00_ISR_API == STD_ON)
    TAUJ1_CH00_ISR,
  #else
    DUMMY(168),
  #endif

  #if (ICU_TAUJ1_CH01_ISR_API == STD_ON)
    TAUJ1_CH01_ISR,
  #else
    DUMMY(169),
  #endif

  #if (ICU_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
    DUMMY(170),
  #endif

  #if (ICU_TAUJ1_CH03_ISR_API == STD_ON)
    TAUJ1_CH03_ISR,
  #else
    DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173), DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177),
  DUMMY(178), DUMMY(179), DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183),
  DUMMY(184), DUMMY(185), DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189),
  DUMMY(190), DUMMY(191), DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195),
  DUMMY(196), DUMMY(197), DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201),
  DUMMY(202), DUMMY(203), DUMMY(204),

   #if (ICU_EXT_INTP_CH09_ISR_API == STD_ON)
     EXT_INTP_CH09_ISR,
   #else
    DUMMY(205),
   #endif

   #if (ICU_EXT_INTP_CH13_ISR_API == STD_ON)
     EXT_INTP_CH13_ISR,
   #else
    DUMMY(206),
   #endif

   #if (ICU_EXT_INTP_CH14_ISR_API == STD_ON)
     EXT_INTP_CH14_ISR,
   #else
    DUMMY(207),
   #endif

   #if (ICU_EXT_INTP_CH15_ISR_API == STD_ON)
     EXT_INTP_CH15_ISR,
   #else
    DUMMY(208),
   #endif

  DUMMY(209), DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214),
  DUMMY(215), DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220),
  DUMMY(221), DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226),
  DUMMY(227), DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232),
  DUMMY(233), DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238),
  DUMMY(239), DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244),
  DUMMY(245), DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250),
  DUMMY(251), DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255),

  #if (ICU_TAUB1_CH00_ISR_API == STD_ON)
      #ifndef APP_ICU_INTERRUPT_TYPE_CAT2
            TAUB1_CH00_ISR,
      #else
            App_Os_TAUB1_CH00_ISR,
      #endif
  #else
    DUMMY(256),
  #endif

  #if (ICU_TAUB1_CH01_ISR_API == STD_ON)
    TAUB1_CH01_ISR,
  #else
    DUMMY(257),
  #endif

  #if (ICU_TAUB1_CH02_ISR_API == STD_ON)
    TAUB1_CH02_ISR,
  #else
    DUMMY(258),
  #endif

  #if (ICU_TAUB1_CH03_ISR_API == STD_ON)
    TAUB1_CH03_ISR,
  #else
    DUMMY(259),
  #endif

  #if (ICU_TAUB1_CH04_ISR_API == STD_ON)
    TAUB1_CH04_ISR,
  #else
    DUMMY(260),
  #endif

  #if (ICU_TAUB1_CH05_ISR_API == STD_ON)
    TAUB1_CH05_ISR,
  #else
    DUMMY(261),
  #endif

  #if (ICU_TAUB1_CH06_ISR_API == STD_ON)
    TAUB1_CH06_ISR,
  #else
    DUMMY(262),
  #endif

  #if (ICU_TAUB1_CH07_ISR_API == STD_ON)
    TAUB1_CH07_ISR,
  #else
    DUMMY(263),
  #endif

  #if (ICU_TAUB1_CH08_ISR_API == STD_ON)
    TAUB1_CH08_ISR,
  #else
    DUMMY(264),
  #endif

  #if (ICU_TAUB1_CH09_ISR_API == STD_ON)
    TAUB1_CH09_ISR,
  #else
    DUMMY(265),
  #endif

  #if (ICU_TAUB1_CH10_ISR_API == STD_ON)
    TAUB1_CH10_ISR,
  #else
    DUMMY(266),
  #endif

  #if (ICU_TAUB1_CH11_ISR_API == STD_ON)
    TAUB1_CH11_ISR,
  #else
    DUMMY(267),
  #endif

  #if (ICU_TAUB1_CH12_ISR_API == STD_ON)
    TAUB1_CH12_ISR,
  #else
    DUMMY(268),
  #endif

  #if (ICU_TAUB1_CH13_ISR_API == STD_ON)
    TAUB1_CH13_ISR,
  #else
    DUMMY(269),
  #endif

  #if (ICU_TAUB1_CH14_ISR_API == STD_ON)
    TAUB1_CH14_ISR,
  #else
    DUMMY(270),
  #endif

  #if (ICU_TAUB1_CH15_ISR_API == STD_ON)
    TAUB1_CH15_ISR,
  #else
    DUMMY(271),
  #endif

  DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275), DUMMY(276),

  #if (ICU_TAUJ2_CH00_ISR_API == STD_ON)
    TAUJ2_CH00_ISR,
  #else
    DUMMY(277),
  #endif

  #if (ICU_TAUJ2_CH01_ISR_API == STD_ON)
    TAUJ2_CH01_ISR,
  #else
    DUMMY(278),
  #endif

  #if (ICU_TAUJ2_CH02_ISR_API == STD_ON)
    TAUJ2_CH02_ISR,
  #else
    DUMMY(279),
  #endif

  #if (ICU_TAUJ2_CH03_ISR_API == STD_ON)
    TAUJ2_CH03_ISR,
  #else
    DUMMY(280),
  #endif

  #if (ICU_TAUJ3_CH00_ISR_API == STD_ON)
    TAUJ3_CH00_ISR,
  #else
    DUMMY(281),
  #endif

  #if (ICU_TAUJ3_CH01_ISR_API == STD_ON)
    TAUJ3_CH01_ISR,
  #else
    DUMMY(282),
  #endif

  #if (ICU_TAUJ3_CH02_ISR_API == STD_ON)
    TAUJ3_CH02_ISR,
  #else
    DUMMY(283),
  #endif

  #if (ICU_TAUJ3_CH03_ISR_API == STD_ON)
    TAUJ3_CH03_ISR,
  #else
    DUMMY(284),
  #endif

  DUMMY(285), DUMMY(286), DUMMY(287), DUMMY(288), DUMMY(289), DUMMY(290),
  DUMMY(291), DUMMY(292), DUMMY(293), DUMMY(294), DUMMY(295), DUMMY(296),
  DUMMY(297), DUMMY(298), DUMMY(299), DUMMY(300), DUMMY(301), DUMMY(302),
  DUMMY(303), DUMMY(304), DUMMY(305), DUMMY(306), DUMMY(307), DUMMY(308),
  DUMMY(309), DUMMY(310), DUMMY(311), DUMMY(312), DUMMY(313), DUMMY(314),
  DUMMY(315), DUMMY(316), DUMMY(317), DUMMY(318), DUMMY(319), DUMMY(320),
  DUMMY(321), DUMMY(322), DUMMY(323), DUMMY(324), DUMMY(325), DUMMY(326),
  DUMMY(327), DUMMY(328), DUMMY(329), DUMMY(330), DUMMY(331), DUMMY(332),
  DUMMY(333), DUMMY(334), DUMMY(335), DUMMY(336), DUMMY(337), DUMMY(338),
  DUMMY(339), DUMMY(340), DUMMY(341), DUMMY(342), DUMMY(343), DUMMY(344),
  DUMMY(345), DUMMY(346), DUMMY(347), DUMMY(348), DUMMY(349), DUMMY(350),
  DUMMY(351), DUMMY(352), DUMMY(353), DUMMY(354), DUMMY(355), DUMMY(355),
  DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359), DUMMY(360), DUMMY(361),
  DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365), DUMMY(366), DUMMY(367),

  #if (ICU_EXT_INTP_CH16_ISR_API == STD_ON)
    EXT_INTP_CH16_ISR,
  #else
    DUMMY(368),
  #endif

  #if (ICU_EXT_INTP_CH17_ISR_API == STD_ON)
    EXT_INTP_CH17_ISR,
  #else
    DUMMY(369),
  #endif

  #if (ICU_EXT_INTP_CH18_ISR_API == STD_ON)
    EXT_INTP_CH18_ISR,
  #else
    DUMMY(370),
  #endif

  #if (ICU_EXT_INTP_CH19_ISR_API == STD_ON)
    EXT_INTP_CH19_ISR,
  #else
    DUMMY(371),
  #endif

  #if (ICU_EXT_INTP_CH20_ISR_API == STD_ON)
    EXT_INTP_CH20_ISR,
  #else
    DUMMY(372),
  #endif

  #if (ICU_EXT_INTP_CH21_ISR_API == STD_ON)
    EXT_INTP_CH21_ISR,
  #else
    DUMMY(373),
  #endif

  #if (ICU_EXT_INTP_CH22_ISR_API == STD_ON)
    EXT_INTP_CH22_ISR,
  #else
    DUMMY(374),
  #endif

  #if (ICU_EXT_INTP_CH23_ISR_API == STD_ON)
    EXT_INTP_CH23_ISR,
  #else
    DUMMY(375),
  #endif

  DUMMY(376), DUMMY(377), DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef ICU_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         LIN F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef LIN_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032),

  #if (LIN_CHANNEL16_CONFIGURED == STD_ON)
  /* 33 */
  LIN_CHANNEL16_ISR,
  #else
  DUMMY(033),
  #endif

  DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050),

  /* 51 */
  Timer0_Interrupt,

  DUMMY(052), DUMMY(053), DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057),

  #if (LIN_CHANNEL00_CONFIGURED == STD_ON)
  /* 58 */
  LIN_CHANNEL00_ISR,
  #else
  DUMMY(058),
  #endif
  #if (LIN_CHANNEL01_CONFIGURED == STD_ON)
  #if defined (Os_LIN_CHANNEL01_CAT2_ISR) || defined (LIN_CHANNEL01_CAT2_ISR)
  /* 59 */
  App_Os_LIN01_SG01_ISR,
  #else
  /* 59 */
  LIN_CHANNEL01_ISR,
  #endif
  #else
  DUMMY(059),
  #endif

  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),

  #if (LIN_CHANNEL17_CONFIGURED == STD_ON)
 /* 120 */
  LIN_CHANNEL17_ISR,
  #else
  DUMMY(120),
  #endif

  DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),

  #if (LIN_CHANNEL02_CONFIGURED == STD_ON)
  /*162*/
  LIN_CHANNEL02_ISR,
  #else
  DUMMY(162),
  #endif
  #if (LIN_CHANNEL03_CONFIGURED == STD_ON)
  /*163*/
  LIN_CHANNEL03_ISR,
  #else
  DUMMY(163),
  #endif
  #if (LIN_CHANNEL18_CONFIGURED == STD_ON)
  /*164*/
  LIN_CHANNEL18_ISR,
  #else
  DUMMY(164),
  #endif

  DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225),

  #if (LIN_CHANNEL04_CONFIGURED == STD_ON)
  /* 226 */
  LIN_CHANNEL04_ISR,
  #else
  DUMMY(226),
  #endif
  #if (LIN_CHANNEL05_CONFIGURED == STD_ON)
  /* 227 */
  LIN_CHANNEL05_ISR,
  #else
  DUMMY(227),
  #endif
  #if (LIN_CHANNEL19_CONFIGURED == STD_ON)
  /* 228 */
  LIN_CHANNEL19_ISR,
  #else
  DUMMY(228),
  #endif

  DUMMY(229), DUMMY(230), DUMMY(231),

  #if (LIN_CHANNEL20_CONFIGURED == STD_ON)
  /*232*/
  LIN_CHANNEL20_ISR,
  #else
  DUMMY(232),
  #endif

  DUMMY(233), DUMMY(234), DUMMY(235),

  #if (LIN_CHANNEL21_CONFIGURED == STD_ON)
  /*236*/
  LIN_CHANNEL21_ISR,
  #else
  DUMMY(236),
  #endif

  DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274),

  #if (LIN_CHANNEL06_CONFIGURED == STD_ON)
  /*275*/
  LIN_CHANNEL06_ISR,
  #else
  DUMMY(275),
  #endif
  #if (LIN_CHANNEL07_CONFIGURED == STD_ON)
   /*276*/
  LIN_CHANNEL07_ISR,
  #else
  DUMMY(276),
  #endif

  DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284),

  #if (LIN_CHANNEL08_CONFIGURED == STD_ON)
  /*285*/
  LIN_CHANNEL08_ISR,
  #else
  DUMMY(285),
  #endif
  #if (LIN_CHANNEL09_CONFIGURED == STD_ON)
  /*286*/
  LIN_CHANNEL09_ISR,
  #else
  DUMMY(286),
  #endif

  DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),

  #if (LIN_CHANNEL10_CONFIGURED == STD_ON)
  /*324*/
  LIN_CHANNEL10_ISR,
  #else
  DUMMY(324),
  #endif
  #if (LIN_CHANNEL11_CONFIGURED == STD_ON)
  /*325*/
  LIN_CHANNEL11_ISR,
  #else
  DUMMY(325),
  #endif

  DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),

  #if (LIN_CHANNEL22_CONFIGURED == STD_ON)
  /* 360 */
  LIN_CHANNEL22_ISR,
  #else
  DUMMY(360),
  #endif

  DUMMY(361), DUMMY(362), DUMMY(363),

  #if (LIN_CHANNEL23_CONFIGURED == STD_ON)
  /* 364 */
  LIN_CHANNEL23_ISR,
  #else
  DUMMY(364),
  #endif

  DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef LIN_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         MCU F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef MCU_MODULE_TEST
#pragma ghs startsda
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022),
#ifdef MCU_CANICUSTOP_INT
/* 23 */
   MCU_CAN_STOP,
#else
  DUMMY(023),
#endif
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079),
#ifdef MCU_TIMER_INT
/* 80 */
   TAUJ0_I0,
#else
/* 80 */
  DUMMY(80),
#endif
#ifdef MCU_TIMER_INT
/* 81 */
   TAUJ0_I1,
#else
/* 81 */
  DUMMY(81),
#endif
  DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104),
  DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111),
  /* 112 */
#if (MCU_LOW_POWER_SEQUENCER == STD_ON)
#ifdef MCU_CFG53_INT
   MCU_INTCWEND_CFG53_ISR,
#else
   MCU_INTCWEND_ISR,
#endif
#else
  DUMMY(112),
#endif
  DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef MCU_MODULE_TEST */
#pragma ghs endsda
#endif

/*****************************************************************************/
/*                         PORT F1KM-S2 IVT                                  */
/*****************************************************************************/
#ifdef PORT_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef PORT_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         PWM F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef PWM_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (PWM_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
    #else
      App_Os_TAUD0_CH00_ISR,
    #endif
  #else
    DUMMY(008),
  #endif

  #if (PWM_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (PWM_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (PWM_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (PWM_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (PWM_TAUD0_CH10_ISR_API == STD_ON)
  TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (PWM_TAUD0_CH12_ISR_API == STD_ON)
  TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (PWM_TAUD0_CH14_ISR_API == STD_ON)
  TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017), DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021),
  DUMMY(022), DUMMY(023), DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027),
  DUMMY(028), DUMMY(029), DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033),
  DUMMY(034), DUMMY(035), DUMMY(036),

  #ifdef PWM_TEST_APP
   INTP0_Isr,
  #else
   DUMMY(037),
  #endif

  #ifdef PWM_TEST_APP
   INTP1_Isr,
  #else
   DUMMY(038),
  #endif

  #ifdef PWM_TEST_APP
   INTP2_Isr,
  #else
   DUMMY(039),
  #endif

  DUMMY(040), DUMMY(041), DUMMY(042),

  #ifdef PWM_TEST_APP
   INTP3_Isr,
  #else
   DUMMY(043),
  #endif

  #ifdef PWM_TEST_APP
   INTP4_Isr,
  #else
   DUMMY(044),
  #endif

  #ifdef PWM_TEST_APP
   INTP5_Isr,
  #else
   DUMMY(045),
  #endif

  #ifdef PWM_TEST_APP
   INTP10_Isr,
  #else
   DUMMY(046),
  #endif

  #ifdef PWM_TEST_APP
   INTP11_Isr,
  #else
   DUMMY(047),
  #endif

   #if (PWM_TAUD0_CH01_ISR_API == STD_ON)
   TAUD0_CH01_ISR,
   #else
    DUMMY(048),
   #endif

   #if (PWM_TAUD0_CH03_ISR_API == STD_ON)
   TAUD0_CH03_ISR,
   #else
    DUMMY(049),
   #endif

   #if (PWM_TAUD0_CH05_ISR_API == STD_ON)
    TAUD0_CH05_ISR,
   #else
    DUMMY(050),
   #endif

   #if (PWM_TAUD0_CH07_ISR_API == STD_ON)
      #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
        TAUD0_CH07_ISR,
      #else
       App_Os_TAUD0_CH07_ISR,
      #endif
   #else
      DUMMY(051),
   #endif

  #if (PWM_TAUD0_CH09_ISR_API == STD_ON)
   TAUD0_CH09_ISR,
  #else
   DUMMY(052),
  #endif

  #if (PWM_TAUD0_CH11_ISR_API == STD_ON)
   TAUD0_CH11_ISR,
  #else
   DUMMY(053),
  #endif

  #if (PWM_TAUD0_CH13_ISR_API == STD_ON)
   TAUD0_CH13_ISR,
  #else
   DUMMY(054),
  #endif

  #if (PWM_TAUD0_CH15_ISR_API == STD_ON)
   TAUD0_CH15_ISR,
  #else
   DUMMY(055),
  #endif


  DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059), DUMMY(060), DUMMY(061),
  DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065), DUMMY(066), DUMMY(067),
  DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071), DUMMY(072), DUMMY(073),
  DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077), DUMMY(078), DUMMY(079),

  #if (PWM_TAUJ0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH00_ISR,
    #else
      App_Os_TAUJ0_CH00_ISR,
    #endif
  #else
    DUMMY(080),
  #endif

  #if (PWM_TAUJ0_CH01_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH01_ISR,
    #else
      App_Os_TAUJ0_CH01_ISR,
    #endif
  #else
    DUMMY(081),
  #endif

  #if (PWM_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(082),
  #endif

  #if (PWM_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(083),
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091),

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP00_ISR_API == STD_ON)
    PWM_INTPWGAG00_ISR,
    #else
     DUMMY(092),
    #endif
  #else
    DUMMY(092),
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP01_ISR_API == STD_ON)
    PWM_INTPWGAG01_ISR,
    #else
     DUMMY(093),
    #endif
  #else
    DUMMY(093),
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP02_ISR_API == STD_ON)
    PWM_INTPWGAG02_ISR,
    #else
     DUMMY(094),
    #endif
  #else
    DUMMY(094),
  #endif

  DUMMY(095), DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100),
  DUMMY(101), DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106),
  DUMMY(107), DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112),
  DUMMY(113), DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118),
  DUMMY(119), DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124),
  DUMMY(125), DUMMY(126), DUMMY(127),

  #ifdef PWM_TEST_APP
   INTP6_Isr,
  #else
   DUMMY(128),
  #endif

  #ifdef PWM_TEST_APP
   INTP7_Isr,
  #else
   DUMMY(129),
  #endif

  #ifdef PWM_TEST_APP
   INTP8_Isr,
  #else
   DUMMY(130),
  #endif

  #ifdef PWM_TEST_APP
   INTP12_Isr,
  #else
   DUMMY(131),
  #endif

  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141),

  #if (PWM_TAUB0_CH00_ISR_API == STD_ON)
   TAUB0_CH00_ISR,
  #else
   DUMMY(142),
  #endif

  #if (PWM_TAUB0_CH01_ISR_API == STD_ON)
   TAUB0_CH01_ISR,
  #else
   DUMMY(143),
  #endif

  #if (PWM_TAUB0_CH02_ISR_API == STD_ON)
   TAUB0_CH02_ISR,
  #else
   DUMMY(144),
  #endif

  #if (PWM_TAUB0_CH03_ISR_API == STD_ON)
   TAUB0_CH03_ISR,
  #else
   DUMMY(145),
  #endif

  #if (PWM_TAUB0_CH04_ISR_API == STD_ON)
   TAUB0_CH04_ISR,
  #else
   DUMMY(146),
  #endif

  #if (PWM_TAUB0_CH05_ISR_API == STD_ON)
   TAUB0_CH05_ISR,
  #else
   DUMMY(147),
  #endif

  #if (PWM_TAUB0_CH06_ISR_API == STD_ON)
   TAUB0_CH06_ISR,
  #else
   DUMMY(148),
  #endif

  #if (PWM_TAUB0_CH07_ISR_API == STD_ON)
   TAUB0_CH07_ISR,
  #else
   DUMMY(149),
  #endif

  #if (PWM_TAUB0_CH08_ISR_API == STD_ON)
   TAUB0_CH08_ISR,
  #else
   DUMMY(150),
  #endif

  #if (PWM_TAUB0_CH09_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUB0_CH09_ISR,
    #else
      App_Os_TAUB0_CH09_ISR,
    #endif
  #else
    DUMMY(151),
  #endif

  #if (PWM_TAUB0_CH10_ISR_API == STD_ON)
   TAUB0_CH10_ISR,
  #else
    DUMMY(152),
  #endif

  #if (PWM_TAUB0_CH11_ISR_API == STD_ON)
   TAUB0_CH11_ISR,
  #else
    DUMMY(153),
  #endif

  #if (PWM_TAUB0_CH12_ISR_API == STD_ON)
   TAUB0_CH12_ISR,
  #else
    DUMMY(154),
  #endif

  #if (PWM_TAUB0_CH13_ISR_API == STD_ON)
   TAUB0_CH13_ISR,
  #else
    DUMMY(155),
  #endif

  #if (PWM_TAUB0_CH14_ISR_API == STD_ON)
   TAUB0_CH14_ISR,
  #else
    DUMMY(156),
  #endif

  #if (PWM_TAUB0_CH15_ISR_API == STD_ON)
   TAUB0_CH15_ISR,
  #else
    DUMMY(157),
  #endif

  DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),DUMMY(162), DUMMY(163),
  DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (PWM_TAUJ1_CH00_ISR_API == STD_ON)
   TAUJ1_CH00_ISR,
  #else
   DUMMY(168),
  #endif

  #if (PWM_TAUJ1_CH01_ISR_API == STD_ON)
   TAUJ1_CH01_ISR,
  #else
   DUMMY(169),
  #endif

  #if (PWM_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
   DUMMY(170),
  #endif

  #if (PWM_TAUJ1_CH03_ISR_API == STD_ON)
   TAUJ1_CH03_ISR,
  #else
   DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173), DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177),
  DUMMY(178), DUMMY(179), DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183),
  DUMMY(184), DUMMY(185), DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189),
  DUMMY(190), DUMMY(191), DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195),
  DUMMY(196), DUMMY(197), DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201),
  DUMMY(202), DUMMY(203), DUMMY(204),

  #ifdef PWM_TEST_APP
   INTP9_Isr,
  #else
   DUMMY(205),
  #endif

  #ifdef PWM_TEST_APP
   INTP13_Isr,
  #else
   DUMMY(206),
  #endif

  #ifdef PWM_TEST_APP
   INTP14_Isr,
  #else
   DUMMY(207),
  #endif

  #ifdef PWM_TEST_APP
   INTP15_Isr,
  #else
   DUMMY(208),
  #endif

  DUMMY(209), DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214),
  DUMMY(215), DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220),
  DUMMY(221), DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226),
  DUMMY(227), DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232),
  DUMMY(233), DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238),
  DUMMY(239), DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244),
  DUMMY(245), DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250),
  DUMMY(251), DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255),

  #if (PWM_TAUB1_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUB1_CH00_ISR,
    #else
      App_Os_TAUB1_CH00_ISR,
    #endif
  #else
     DUMMY(256),
  #endif

  #if (PWM_TAUB1_CH01_ISR_API == STD_ON)
    TAUB1_CH01_ISR,
  #else
    DUMMY(257),
  #endif

  #if (PWM_TAUB1_CH02_ISR_API == STD_ON)
    TAUB1_CH02_ISR,
  #else
    DUMMY(258),
  #endif

  #if (PWM_TAUB1_CH03_ISR_API == STD_ON)
    TAUB1_CH03_ISR,
  #else
    DUMMY(259),
  #endif

  #if (PWM_TAUB1_CH04_ISR_API == STD_ON)
    TAUB1_CH04_ISR,
  #else
    DUMMY(260),
  #endif

  #if (PWM_TAUB1_CH05_ISR_API == STD_ON)
    TAUB1_CH05_ISR,
  #else
    DUMMY(261),
  #endif

  #if (PWM_TAUB1_CH06_ISR_API == STD_ON)
    TAUB1_CH06_ISR,
  #else
    DUMMY(262),
  #endif

  #if (PWM_TAUB1_CH07_ISR_API == STD_ON)
    TAUB1_CH07_ISR,
  #else
    DUMMY(263),
  #endif

  #if (PWM_TAUB1_CH08_ISR_API == STD_ON)
   TAUB1_CH08_ISR,
  #else
   DUMMY(264),
  #endif

  #if (PWM_TAUB1_CH09_ISR_API == STD_ON)
    TAUB1_CH09_ISR,
  #else
    DUMMY(265),
  #endif

  #if (PWM_TAUB1_CH10_ISR_API == STD_ON)
    TAUB1_CH10_ISR,
  #else
    DUMMY(266),
  #endif

  #if (PWM_TAUB1_CH11_ISR_API == STD_ON)
    TAUB1_CH11_ISR,
  #else
    DUMMY(267),
  #endif

  #if (PWM_TAUB1_CH12_ISR_API == STD_ON)
    TAUB1_CH12_ISR,
  #else
    DUMMY(268),
  #endif

  #if (PWM_TAUB1_CH13_ISR_API == STD_ON)
   TAUB1_CH13_ISR,
  #else
   DUMMY(269),
  #endif

  #if (PWM_TAUB1_CH14_ISR_API == STD_ON)
    TAUB1_CH14_ISR,
  #else
    DUMMY(270),
  #endif

  #if (PWM_TAUB1_CH15_ISR_API == STD_ON)
    TAUB1_CH15_ISR,
  #else
    DUMMY(271),
  #endif

  DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275), DUMMY(276),

  #if (PWM_TAUJ2_CH00_ISR_API == STD_ON)
    TAUJ2_CH00_ISR,
  #else
    DUMMY(277),
  #endif

  #if (PWM_TAUJ2_CH01_ISR_API == STD_ON)
    TAUJ2_CH01_ISR,
  #else
    DUMMY(278),
  #endif

  #if (PWM_TAUJ2_CH02_ISR_API == STD_ON)
    TAUJ2_CH02_ISR,
  #else
    DUMMY(279),
  #endif

  #if (PWM_TAUJ2_CH03_ISR_API == STD_ON)
    TAUJ2_CH03_ISR,
  #else
    DUMMY(280),
  #endif

  #if (PWM_TAUJ3_CH00_ISR_API == STD_ON)
    TAUJ3_CH00_ISR,
  #else
    DUMMY(281),
  #endif

  #if (PWM_TAUJ3_CH01_ISR_API == STD_ON)
    TAUJ3_CH01_ISR,
  #else
    DUMMY(282),
  #endif

  #if (PWM_TAUJ3_CH02_ISR_API == STD_ON)
    TAUJ3_CH02_ISR,
  #else
    DUMMY(283),
  #endif

  #if (PWM_TAUJ3_CH03_ISR_API == STD_ON)
    TAUJ3_CH03_ISR,
  #else
    DUMMY(284),
  #endif

  DUMMY(285), DUMMY(286), DUMMY(287), DUMMY(288), DUMMY(289), DUMMY(290),
  DUMMY(291), DUMMY(292), DUMMY(293), DUMMY(294), DUMMY(295), DUMMY(296),
  DUMMY(297), DUMMY(298), DUMMY(299), DUMMY(300), DUMMY(301), DUMMY(302),
  DUMMY(303), DUMMY(304), DUMMY(305), DUMMY(306), DUMMY(307), DUMMY(308),
  DUMMY(309), DUMMY(310), DUMMY(311), DUMMY(312), DUMMY(313), DUMMY(314),
  DUMMY(315), DUMMY(316), DUMMY(317), DUMMY(318), DUMMY(319), DUMMY(320),
  DUMMY(321), DUMMY(322), DUMMY(323), DUMMY(324), DUMMY(325), DUMMY(326),
  DUMMY(327), DUMMY(328), DUMMY(329), DUMMY(330), DUMMY(331), DUMMY(332),
  DUMMY(333), DUMMY(334), DUMMY(335), DUMMY(336), DUMMY(337), DUMMY(338),
  DUMMY(339), DUMMY(340), DUMMY(341), DUMMY(342), DUMMY(343), DUMMY(344),
  DUMMY(345), DUMMY(346), DUMMY(347), DUMMY(348), DUMMY(349), DUMMY(350),
  DUMMY(351), DUMMY(352), DUMMY(353), DUMMY(354), DUMMY(355), DUMMY(356),
  DUMMY(357), DUMMY(358), DUMMY(359), DUMMY(360), DUMMY(361), DUMMY(362),
  DUMMY(363), DUMMY(364), DUMMY(365), DUMMY(366), DUMMY(367), DUMMY(368),
  DUMMY(369), DUMMY(370), DUMMY(371), DUMMY(372), DUMMY(373), DUMMY(374),
  DUMMY(375), DUMMY(376), DUMMY(377), DUMMY(378), DUMMY(379), DUMMY(380),
  DUMMY(381)
};
/* End of #ifdef PWM_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         RAMTST F1KM-S2 IVT                                */
/*****************************************************************************/
#ifdef RAMTST_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef RAMTST_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         SPI F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef SPI_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),
  #if(SPI_TIMER == STD_ON)
  /* 8 */
  Timer_Task,
  #else
  /* 8 */
  DUMMY(08),
  #endif
 #if(SPI_TIMER2 == STD_ON)
  /* 9 */
  Timer_Task2,
  #else
  /* 9 */
  DUMMY(09),
  #endif
  /* 10 */
  DUMMY(010),
  /* 11 */
  DUMMY(011),
  /* 12 */
  DUMMY(012),
  /* 13 */
  DUMMY(013),
  /* 14 */
  DUMMY(014),
  /* 15 */
  DUMMY(015),
  /* 16 */
  DUMMY(016),
  /* 17 */
  DUMMY(017),
  /* 18 */
  DUMMY(018),
  /* 19 */
  DUMMY(019),
  /* 20 */
  DUMMY(020),
  /* 21 */
  DUMMY(021),
  /* 22 */
  DUMMY(022),
  /* 23 */
  DUMMY(023),
  /* 24 */
  DUMMY(024),
  /* 25 */
  DUMMY(025),
  /* 26 */
  DUMMY(026),
  #if(SPI_CSIG0_TIC_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIG0_TIC_CAT2_ISR
  /* 27 */
  App_Os_SPI_CSIG0_TIC_ISR,
  #else
  /* 27 */
  SPI_CSIG0_TIC_ISR,
  #endif
  #else
    #ifdef APP_SPI_CSIG0_SLAVE_ISR_ON
    /* 27 */
    APP_SPI_CSIG0_SLAVE_TX_ISR,
    #else
    /* 27 */
    DUMMY(027),
    #endif
  #endif
  #if(SPI_CSIG0_TIR_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIG0_TIR_CAT2_ISR
  /* 28 */
  App_Os_SPI_CSIG0_TIR_ISR,
  #else
  /* 28 */
  SPI_CSIG0_TIR_ISR,
  #endif
  #else
  /* 28 */
    #ifdef APP_SPI_CSIG0_SLAVE_ISR_ON
    /* 28 */
    APP_SPI_CSIG0_SLAVE_RX_ISR,
    #else
    /* 28 */
    DUMMY(028),
    #endif
  #endif
  #if(SPI_CSIH0_TIC_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIH0_TIC_CAT2_ISR
  /* 29 */
  App_Os_SPI_CSIH0_TIC_ISR,
  #else
  /* 29 */
  SPI_CSIH0_TIC_ISR,
  #endif
  #else
    #ifdef APP_SPI_CSIH0_SLAVE_ISR_ON
    /* 29 */
    APP_SPI_CSIH0_SLAVE_TX_ISR,
    #else
    /* 29 */
    DUMMY(029),
    #endif
  #endif
  #if(SPI_CSIH0_TIR_ISR_API == STD_ON)
  #ifdef Os_SPI_CSIH0_TIR_CAT2_ISR
  /* 30 */
  App_Os_SPI_CSIH0_TIR_ISR,
  #else
  /* 30 */
  SPI_CSIH0_TIR_ISR,
  #endif
  #else
  /* 30 */
    #ifdef APP_SPI_CSIH0_SLAVE_ISR_ON
    /* 30 */
    APP_SPI_CSIH0_SLAVE_RX_ISR,
    #else
    /* 30 */
    DUMMY(030),
    #endif
  #endif
  /* 31 */
  DUMMY(031),
  /* 32 */
  DUMMY(032),
  DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039), DUMMY(040), DUMMY(041),
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  #if(SPI_TIMER1 == STD_ON)
  /* 48 */
  Timer_Task1,
  #else
  DUMMY(048),
  #endif
  #if(SPI_TIMER3 == STD_ON)
  /* 49 */
  Timer_Task3,
  #else
  /* 49 */
  DUMMY(049),
  #endif
  DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056),
  /* 57 */
  DUMMY(057),
  /* 58 */
  DUMMY(058),
  /* 59 */
  DUMMY(059),
  #if(SPI_DMA00_ISR_API == STD_ON)
  /* 60 */
  SPI_DMA00_ISR,
  #else
  /* 60 */
  DUMMY(060),
  #endif
  #if(SPI_DMA01_ISR_API == STD_ON)
  /* 61 */
  SPI_DMA01_ISR,
  #else
  /* 61 */
  DUMMY(061),
  #endif
  #if(SPI_DMA02_ISR_API == STD_ON)
  /* 62 */
  SPI_DMA02_ISR,
  #else
  /* 62 */
  DUMMY(062),
  #endif
  #if(SPI_DMA03_ISR_API == STD_ON)
  /* 63 */
  SPI_DMA03_ISR,
  #else
  /* 63 */
  DUMMY(063),
  #endif
  #if(SPI_DMA04_ISR_API == STD_ON)
  /* 64 */
  SPI_DMA04_ISR,
  #else
  /* 64 */
  DUMMY(064),
  #endif
  #if(SPI_DMA05_ISR_API == STD_ON)
  /* 65 */
  SPI_DMA05_ISR,
  #else
  /* 65 */
  DUMMY(065),
  #endif
  #if(SPI_DMA06_ISR_API == STD_ON)
  /* 66 */
  SPI_DMA06_ISR,
  #else
  /* 66 */
  DUMMY(066),
  #endif
  #if(SPI_DMA07_ISR_API == STD_ON)
  /* 67 */
  SPI_DMA07_ISR,
  #else
  /* 67 */
  DUMMY(067),
  #endif
  #if(SPI_DMA08_ISR_API == STD_ON)
  /* 68 */
  SPI_DMA08_ISR,
  #else
  /* 68 */
  DUMMY(068),
  #endif
  #if(SPI_DMA09_ISR_API == STD_ON)
  /* 69 */
  SPI_DMA09_ISR,
  #else
  /* 69 */
  DUMMY(069),
  #endif
  #if(SPI_DMA10_ISR_API == STD_ON)
  /* 70 */
  SPI_DMA10_ISR,
  #else
  /* 70 */
  DUMMY(070),
  #endif
  #if(SPI_DMA11_ISR_API == STD_ON)
  /* 71 */
  SPI_DMA11_ISR,
  #else
  /* 71 */
  DUMMY(071),
  #endif
  #if(SPI_DMA12_ISR_API == STD_ON)
  /* 72 */
  SPI_DMA12_ISR,
  #else
  /* 72 */
  DUMMY(072),
  #endif
  #if(SPI_DMA13_ISR_API == STD_ON)
  /* 73 */
  SPI_DMA13_ISR,
  #else
  /* 73 */
  DUMMY(073),
  #endif
  #if(SPI_DMA14_ISR_API == STD_ON)
  /* 74 */
  SPI_DMA14_ISR,
  #else
  /* 74 */
  DUMMY(074),
  #endif
  #if(SPI_DMA15_ISR_API == STD_ON)
  /* 75 */
  SPI_DMA15_ISR,
  #else
  /* 75 */
  DUMMY(075),
  #endif
  DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115),
  #ifdef APP_SPI_CSIH1_SLAVE_ISR_ON
    /* #if(SPI_CSIH1_TIC_ISR_API == STD_ON) */
  /* 116 */
  APP_SPI_CSIH1_SLAVE_TX_ISR, /* SPI_CSIH1_TIC_ISR, */
  #else
  #if(SPI_CSIH1_TIC_ISR_API == STD_ON)
  /* 116 */
  SPI_CSIH1_TIC_ISR,
  #else
  /* 116 */
  DUMMY(116),
  #endif
  #endif

  #ifdef APP_SPI_CSIH1_SLAVE_ISR_ON
    /* #if(SPI_CSIH1_TIR_ISR_API == STD_ON) */
  /* 117 */
  APP_SPI_CSIH1_SLAVE_RX_ISR, /* SPI_CSIH1_TIR_ISR, */
  #else
  #if(SPI_CSIH1_TIR_ISR_API == STD_ON)
  /* 117 */
  SPI_CSIH1_TIR_ISR,
  #else
  /* 117 */
  DUMMY(117),
  #endif
  #endif
  /* 118 */
  DUMMY(118),
  /* 119 */
  DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  #ifdef APP_SPI_CSIH2_SLAVE_ISR_ON
  /* 132 */
  APP_SPI_CSIH2_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIH2_TIC_ISR_API == STD_ON)
  /* 132 */
  SPI_CSIH2_TIC_ISR,
  #else
  /* 132 */
  DUMMY(132),
  #endif
  #endif

  #ifdef APP_SPI_CSIH2_SLAVE_ISR_ON
  /* 133 */
  APP_SPI_CSIH2_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIH2_TIR_ISR_API == STD_ON)
  /* 133 */
  SPI_CSIH2_TIR_ISR,
  #else
  /* 133 */
  DUMMY(133),
  #endif
  #endif
  /* 134 */
  DUMMY(134),
  /* 135 */
  DUMMY(135),
  DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157),
  #ifdef APP_SPI_CSIH3_SLAVE_ISR_ON
  /* 158 */
  APP_SPI_CSIH3_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIH3_TIC_ISR_API == STD_ON)
  /* 158 */
  SPI_CSIH3_TIC_ISR,
  #else
  /* 158 */
  DUMMY(158),
  #endif
  #endif

  #ifdef APP_SPI_CSIH3_SLAVE_ISR_ON
  /* 159 */
  APP_SPI_CSIH3_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIH3_TIR_ISR_API == STD_ON)
  /* 159 */
  SPI_CSIH3_TIR_ISR,
  #else
  /* 159 */
  DUMMY(159),
  #endif
  #endif
  /* 160 */
  DUMMY(160),
  /* 161 */
   DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222),
  #ifdef APP_SPI_CSIG1_SLAVE_ISR_ON
  /* 223 */
  APP_SPI_CSIG1_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIG1_TIC_ISR_API == STD_ON)
  /* 223 */
  SPI_CSIG1_TIC_ISR,
  #else
  /* 223 */
  DUMMY(223),
  #endif
  #endif
  #ifdef APP_SPI_CSIG1_SLAVE_ISR_ON
  /* 224 */
  APP_SPI_CSIG1_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIG1_TIR_ISR_API == STD_ON)
  /* 224 */
  SPI_CSIG1_TIR_ISR,
  #else
  /* 224 */
  DUMMY(224),
  #endif
  #endif
  /* 225 */
  DUMMY(225),
  DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325),
  #ifdef APP_SPI_CSIG2_SLAVE_ISR_ON
  /* 326 */
  APP_SPI_CSIG2_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIG2_TIC_ISR_API == STD_ON)
  /* 326 */
  SPI_CSIG2_TIC_ISR,
  #else
  /* 326 */
  DUMMY(326),
  #endif
  #endif

  #ifdef APP_SPI_CSIG2_SLAVE_ISR_ON
  /* 327 */
  APP_SPI_CSIG2_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIG2_TIR_ISR_API == STD_ON)
  /* 327 */
  SPI_CSIG2_TIR_ISR,
  #else
  /* 327 */
  DUMMY(327),
  #endif
  #endif
  /* 328 */
  DUMMY(328),
  #ifdef APP_SPI_CSIG3_SLAVE_ISR_ON
  /* 329 */
  APP_SPI_CSIG3_SLAVE_TX_ISR,
  #else
  #if(SPI_CSIG3_TIC_ISR_API == STD_ON)
  /* 329 */
  SPI_CSIG3_TIC_ISR,
  #else
  /* 329 */
  DUMMY(329),
  #endif
  #endif

  #ifdef APP_SPI_CSIG3_SLAVE_ISR_ON
  /* 330 */
  APP_SPI_CSIG3_SLAVE_RX_ISR,
  #else
  #if(SPI_CSIG3_TIR_ISR_API == STD_ON)
  /* 330 */
  SPI_CSIG3_TIR_ISR,
  #else
  /* 330 */
  DUMMY(330),
  #endif
  #endif
  /* 331 */
  DUMMY(331),
  DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef SPI_MODULE_TEST */
#endif

/*****************************************************************************/
/*                         WDG F1KM-S2 IVT                                   */
/*****************************************************************************/
#ifdef WDG_MODULE_TEST
/*****************************************************************************/
/*                         WDG Interrupt Vector Table                        */
/*****************************************************************************/
#ifdef WDG_59_DRIVERA_AR_VERSION
#if ((WDG_59_DRIVERA_AR_VERSION == WDG_59_DRIVERA_AR_FOUR_ZERO_THREE) || \
     (WDG_59_DRIVERA_AR_VERSION == WDG_59_DRIVERA_AR_FOUR_TWO_TWO))
#define WDG_DRIVERA_INTERRUPT_ENABLE
#endif
#endif

#ifdef WDG_59_DRIVERB_AR_VERSION
#if ((WDG_59_DRIVERB_AR_VERSION == WDG_59_DRIVERB_AR_FOUR_ZERO_THREE) || \
     (WDG_59_DRIVERB_AR_VERSION == WDG_59_DRIVERB_AR_FOUR_TWO_TWO))
#define WDG_DRIVERB_INTERRUPT_ENABLE
#endif
#endif

 #if defined WDG_DRIVERA_INTERRUPT_ENABLE || \
                                            defined WDG_DRIVERB_INTERRUPT_ENABLE

#pragma ghs section sdata=".inttable"
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007), DUMMY(008), DUMMY(009), DUMMY(010), DUMMY(011),
  DUMMY(012), DUMMY(013), DUMMY(014), DUMMY(015), DUMMY(016), DUMMY(017),
  DUMMY(018), DUMMY(019), DUMMY(020), DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039),

/* 40 */
  #ifdef WDG_DRIVERA_INTERRUPT_ENABLE
  #ifndef Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR
  WDG_59_DRIVERA_TRIGGERFUNCTION_ISR,
  #else
 /* 40 */

 App_Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR,
  #endif
  #else
  DUMMY(040),
  #endif
/* 41 */

  #ifdef WDG_DRIVERB_INTERRUPT_ENABLE
  WDG_59_DRIVERB_TRIGGERFUNCTION_ISR,
  #else
  DUMMY(041),
  #endif
  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),
  DUMMY(048), DUMMY(049), DUMMY(050), DUMMY(051), DUMMY(052), DUMMY(053),
  DUMMY(054), DUMMY(055), DUMMY(056), DUMMY(057), DUMMY(058), DUMMY(059),
  DUMMY(060), DUMMY(061), DUMMY(062), DUMMY(063), DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079), DUMMY(080), DUMMY(081), DUMMY(082), DUMMY(083),
  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091), DUMMY(092), DUMMY(093), DUMMY(094), DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),
  DUMMY(168), DUMMY(169), DUMMY(170), DUMMY(171), DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255), DUMMY(256), DUMMY(257),
  DUMMY(258), DUMMY(259), DUMMY(260), DUMMY(261), DUMMY(262), DUMMY(263),
  DUMMY(264), DUMMY(265), DUMMY(266), DUMMY(267), DUMMY(268), DUMMY(269),
  DUMMY(270), DUMMY(271), DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
#pragma ghs section sdata=default
#endif
#endif /* #ifdef WDG_MODULE_TEST */


/*****************************************************************************/
/*               GLOBAL SAMPLE APPLICATION F1KM-S2 IVT                       */
/*****************************************************************************/
#ifdef GLOBAL_MODULE_TEST
void (*IntVectors[])(void) = {
  DUMMY(000), DUMMY(001), DUMMY(002), DUMMY(003), DUMMY(004), DUMMY(005),
  DUMMY(006), DUMMY(007),

  #if (PWM_TAUD0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUD0_CH00_ISR,
    #else
      App_Os_TAUD0_CH00_ISR,
    #endif
  #else
    DUMMY(008),
  #endif

  #if (PWM_TAUD0_CH02_ISR_API == STD_ON)
    TAUD0_CH02_ISR,
  #else
    DUMMY(009),
  #endif

  #if (PWM_TAUD0_CH04_ISR_API == STD_ON)
    TAUD0_CH04_ISR,
  #else
    DUMMY(010),
  #endif

  #if (PWM_TAUD0_CH06_ISR_API == STD_ON)
    TAUD0_CH06_ISR,
  #else
    DUMMY(011),
  #endif

  #if (PWM_TAUD0_CH08_ISR_API == STD_ON)
    TAUD0_CH08_ISR,
  #else
    DUMMY(012),
  #endif

  #if (PWM_TAUD0_CH10_ISR_API == STD_ON)
  TAUD0_CH10_ISR,
  #else
    DUMMY(013),
  #endif

  #if (PWM_TAUD0_CH12_ISR_API == STD_ON)
  TAUD0_CH12_ISR,
  #else
    DUMMY(014),
  #endif

  #if (PWM_TAUD0_CH14_ISR_API == STD_ON)
  TAUD0_CH14_ISR,
  #else
    DUMMY(015),
  #endif

  DUMMY(016), DUMMY(017),

  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG1_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG1_CAT2_ISR) || defined (ADC0_SG1_CAT2_ISR)
        App_Os_ADC0_SG1_ISR,
      #else
        ADC0_SG1_ISR,
      #endif
    #else
      DUMMY(018),
    #endif /* #if (ADC0_SG1_ISR_API == STD_ON) */
  #else
    DUMMY(018),
  #endif
  /* 019 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG2_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG2_CAT2_ISR) || defined (ADC0_SG2_CAT2_ISR)
        App_Os_ADC0_SG2_ISR,
      #else
        ADC0_SG2_ISR,
      #endif
    #else
      DUMMY(019),
    #endif
  #else
    DUMMY(019),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
  /* 020 */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC0_SG3_ISR_API == STD_ON)
      #if defined (Os_ADC0_SG3_CAT2_ISR) || defined (ADC0_SG3_CAT2_ISR)
        App_Os_ADC0_SG3_ISR,
      #else
        ADC0_SG3_ISR,
      #endif
    #else
      DUMMY(020),
    #endif /* #if (ADC0_SG3_ISR_API == STD_ON) */
  #else
    DUMMY(020),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(021), DUMMY(022), DUMMY(023),
  DUMMY(024), DUMMY(025), DUMMY(026), DUMMY(027), DUMMY(028), DUMMY(029),
  DUMMY(030), DUMMY(031), DUMMY(032), DUMMY(033), DUMMY(034), DUMMY(035),
  DUMMY(036), DUMMY(037), DUMMY(038), DUMMY(039),

  /* 40 */
  #ifdef WDG_DRIVERA_INTERRUPT_ENABLE
  #ifndef Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR
  WDG_59_DRIVERA_TRIGGERFUNCTION_ISR,
  #else
  /* 40 */
  App_Os_WDG_59_DRIVERA_TRIGGERFUNCTION_CAT2_ISR,
  #endif
  #else
  DUMMY(040),
  #endif

  /* 41 */

  #ifdef WDG_DRIVERB_INTERRUPT_ENABLE
  WDG_59_DRIVERB_TRIGGERFUNCTION_ISR,
  #else
  DUMMY(041),
  #endif

  DUMMY(042), DUMMY(043), DUMMY(044), DUMMY(045), DUMMY(046), DUMMY(047),

  #if (PWM_TAUD0_CH01_ISR_API == STD_ON)
  TAUD0_CH01_ISR,
  #else
   DUMMY(048),
  #endif

  #if (PWM_TAUD0_CH03_ISR_API == STD_ON)
  TAUD0_CH03_ISR,
  #else
   DUMMY(049),
  #endif

  #if (PWM_TAUD0_CH05_ISR_API == STD_ON)
   TAUD0_CH05_ISR,
  #else
   DUMMY(050),
  #endif

  #if (PWM_TAUD0_CH07_ISR_API == STD_ON)
     #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
       TAUD0_CH07_ISR,
     #else
      App_Os_TAUD0_CH07_ISR,
     #endif
  #else
     DUMMY(051),
  #endif

  #if (PWM_TAUD0_CH09_ISR_API == STD_ON)
   TAUD0_CH09_ISR,
  #else
   DUMMY(052),
  #endif

  #if (PWM_TAUD0_CH11_ISR_API == STD_ON)
   TAUD0_CH11_ISR,
  #else
   DUMMY(053),
  #endif

  #if (PWM_TAUD0_CH13_ISR_API == STD_ON)
   TAUD0_CH13_ISR,
  #else
   DUMMY(054),
  #endif

  #if (PWM_TAUD0_CH15_ISR_API == STD_ON)
   TAUD0_CH15_ISR,
  #else
   DUMMY(055),
  #endif

  /* ADC_0 Error Interrupt */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    #if (ADC_ERROR_SUPPORT == STD_ON)
      #if defined (Os_ADC0_ERR_CAT2_ISR) || defined (ADC0_ERR_CAT2_ISR)
        App_Os_ADC0_ERR_ISR,
      #else
        ADC0_ERR_ISR,
      #endif
    #else
      DUMMY(056),
    #endif /*#if (ADC_ERROR_SUPPORT == STD_ON)*/
  #else
    DUMMY(056),
  #endif /* #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  DUMMY(057), DUMMY(058), DUMMY(059),

  /* 60 */
  #if (ADC_DMA_ISR_CH00_API == STD_ON)
    #if defined (OS_ADC_DMA_CH00_CAT2_ISR) || defined (ADC_DMA_CH00_CAT2_ISR)
      App_Os_ADC_DMA_CH00_ISR,
    #else
      ADC_DMA_CH00_ISR,
    #endif
  #else
    DUMMY(060),
  #endif
  /* 61 */
  #if (ADC_DMA_ISR_CH01_API == STD_ON)
    ADC_DMA_CH01_ISR,
  #else
   DUMMY(061),
  #endif
  /* 62 */
  #if (ADC_DMA_ISR_CH02_API == STD_ON)
    ADC_DMA_CH02_ISR,
  #else
    DUMMY(062),
  #endif
  /* 63 */
  #if (ADC_DMA_ISR_CH03_API == STD_ON)
    ADC_DMA_CH03_ISR,
  #else
   DUMMY(063),
  #endif

  DUMMY(064), DUMMY(065),
  DUMMY(066), DUMMY(067), DUMMY(068), DUMMY(069), DUMMY(070), DUMMY(071),
  DUMMY(072), DUMMY(073), DUMMY(074), DUMMY(075), DUMMY(076), DUMMY(077),
  DUMMY(078), DUMMY(079),

  #if (PWM_TAUJ0_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH00_ISR,
    #else
      App_Os_TAUJ0_CH00_ISR,
    #endif
  #else
    DUMMY(080),
  #endif

  #if (PWM_TAUJ0_CH01_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUJ0_CH01_ISR,
    #else
      App_Os_TAUJ0_CH01_ISR,
    #endif
  #else
    DUMMY(081),
  #endif

  #if (PWM_TAUJ0_CH02_ISR_API == STD_ON)
    TAUJ0_CH02_ISR,
  #else
    DUMMY(082),
  #endif

  #if (PWM_TAUJ0_CH03_ISR_API == STD_ON)
    TAUJ0_CH03_ISR,
  #else
    DUMMY(083),
  #endif

  DUMMY(084), DUMMY(085), DUMMY(086), DUMMY(087), DUMMY(088), DUMMY(089),
  DUMMY(090), DUMMY(091),

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP00_ISR_API == STD_ON)
    PWM_INTPWGAG00_ISR,
    #else
     DUMMY(092),
    #endif
  #else
     DUMMY(092),
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP01_ISR_API == STD_ON)
    PWM_INTPWGAG01_ISR,
    #else
     DUMMY(093),
    #endif
  #else
     DUMMY(093),
  #endif

  #if (PWM_DIAG_UNIT_USED == STD_ON)
    #if (PWM_PWGA_CHGRP02_ISR_API == STD_ON)
    PWM_INTPWGAG02_ISR,
    #else
     DUMMY(094),
    #endif
  #else
     DUMMY(094),
  #endif

  DUMMY(095),
  DUMMY(096), DUMMY(097), DUMMY(098), DUMMY(099), DUMMY(100), DUMMY(101),
  DUMMY(102), DUMMY(103), DUMMY(104), DUMMY(105), DUMMY(106), DUMMY(107),
  DUMMY(108), DUMMY(109), DUMMY(110), DUMMY(111), DUMMY(112), DUMMY(113),
  DUMMY(114), DUMMY(115), DUMMY(116), DUMMY(117), DUMMY(118), DUMMY(119),
  DUMMY(120), DUMMY(121), DUMMY(122), DUMMY(123), DUMMY(124), DUMMY(125),
  DUMMY(126), DUMMY(127), DUMMY(128), DUMMY(129), DUMMY(130), DUMMY(131),
  DUMMY(132), DUMMY(133), DUMMY(134), DUMMY(135), DUMMY(136), DUMMY(137),
  DUMMY(138), DUMMY(139), DUMMY(140), DUMMY(141), DUMMY(142), DUMMY(143),
  DUMMY(144), DUMMY(145), DUMMY(146), DUMMY(147), DUMMY(148), DUMMY(149),
  DUMMY(150), DUMMY(151), DUMMY(152), DUMMY(153), DUMMY(154), DUMMY(155),
  DUMMY(156), DUMMY(157), DUMMY(158), DUMMY(159), DUMMY(160), DUMMY(161),
  DUMMY(162), DUMMY(163), DUMMY(164), DUMMY(165), DUMMY(166), DUMMY(167),

  #if (PWM_TAUJ1_CH00_ISR_API == STD_ON)
   TAUJ1_CH00_ISR,
  #else
   DUMMY(168),
  #endif

  #if (PWM_TAUJ1_CH01_ISR_API == STD_ON)
   TAUJ1_CH01_ISR,
  #else
   DUMMY(169),
  #endif

  #if (PWM_TAUJ1_CH02_ISR_API == STD_ON)
    TAUJ1_CH02_ISR,
  #else
   DUMMY(170),
  #endif

  #if (PWM_TAUJ1_CH03_ISR_API == STD_ON)
   TAUJ1_CH03_ISR,
  #else
   DUMMY(171),
  #endif

  DUMMY(172), DUMMY(173),
  DUMMY(174), DUMMY(175), DUMMY(176), DUMMY(177), DUMMY(178), DUMMY(179),
  DUMMY(180), DUMMY(181), DUMMY(182), DUMMY(183), DUMMY(184), DUMMY(185),
  DUMMY(186), DUMMY(187), DUMMY(188), DUMMY(189), DUMMY(190), DUMMY(191),
  DUMMY(192), DUMMY(193), DUMMY(194), DUMMY(195), DUMMY(196), DUMMY(197),
  DUMMY(198), DUMMY(199), DUMMY(200), DUMMY(201), DUMMY(202), DUMMY(203),
  DUMMY(204), DUMMY(205), DUMMY(206), DUMMY(207), DUMMY(208), DUMMY(209),
  DUMMY(210), DUMMY(211), DUMMY(212), DUMMY(213), DUMMY(214), DUMMY(215),
  DUMMY(216), DUMMY(217), DUMMY(218), DUMMY(219), DUMMY(220), DUMMY(221),
  DUMMY(222), DUMMY(223), DUMMY(224), DUMMY(225), DUMMY(226), DUMMY(227),
  DUMMY(228), DUMMY(229), DUMMY(230), DUMMY(231), DUMMY(232), DUMMY(233),
  DUMMY(234), DUMMY(235), DUMMY(236), DUMMY(237), DUMMY(238), DUMMY(239),
  DUMMY(240), DUMMY(241), DUMMY(242), DUMMY(243), DUMMY(244), DUMMY(245),
  DUMMY(246), DUMMY(247), DUMMY(248), DUMMY(249), DUMMY(250), DUMMY(251),
  DUMMY(252), DUMMY(253), DUMMY(254), DUMMY(255),

  #if (PWM_TAUB1_CH00_ISR_API == STD_ON)
    #ifndef APP_PWM_INTERRUPT_TYPE_CAT2
      TAUB1_CH00_ISR,
    #else
      App_Os_TAUB1_CH00_ISR,
    #endif
  #else
     DUMMY(256),
  #endif

  #if (PWM_TAUB1_CH01_ISR_API == STD_ON)
    TAUB1_CH01_ISR,
  #else
    DUMMY(257),
  #endif

  #if (PWM_TAUB1_CH02_ISR_API == STD_ON)
    TAUB1_CH02_ISR,
  #else
    DUMMY(258),
  #endif

  #if (PWM_TAUB1_CH03_ISR_API == STD_ON)
    TAUB1_CH03_ISR,
  #else
    DUMMY(259),
  #endif

  #if (PWM_TAUB1_CH04_ISR_API == STD_ON)
    TAUB1_CH04_ISR,
  #else
    DUMMY(260),
  #endif

  #if (PWM_TAUB1_CH05_ISR_API == STD_ON)
    TAUB1_CH05_ISR,
  #else
    DUMMY(261),
  #endif

  #if (PWM_TAUB1_CH06_ISR_API == STD_ON)
    TAUB1_CH06_ISR,
  #else
    DUMMY(262),
  #endif

  #if (PWM_TAUB1_CH07_ISR_API == STD_ON)
    TAUB1_CH07_ISR,
  #else
    DUMMY(263),
  #endif

  #if (PWM_TAUB1_CH08_ISR_API == STD_ON)
   TAUB1_CH08_ISR,
  #else
   DUMMY(264),
  #endif

  #if (PWM_TAUB1_CH09_ISR_API == STD_ON)
    TAUB1_CH09_ISR,
  #else
    DUMMY(265),
  #endif

  #if (PWM_TAUB1_CH10_ISR_API == STD_ON)
    TAUB1_CH10_ISR,
  #else
    DUMMY(266),
  #endif

  #if (PWM_TAUB1_CH11_ISR_API == STD_ON)
    TAUB1_CH11_ISR,
  #else
    DUMMY(267),
  #endif

  #if (PWM_TAUB1_CH12_ISR_API == STD_ON)
    TAUB1_CH12_ISR,
  #else
    DUMMY(268),
  #endif

  #if (PWM_TAUB1_CH13_ISR_API == STD_ON)
   TAUB1_CH13_ISR,
  #else
   DUMMY(269),
  #endif

  #if (PWM_TAUB1_CH14_ISR_API == STD_ON)
    TAUB1_CH14_ISR,
  #else
    DUMMY(270),
  #endif

  #if (PWM_TAUB1_CH15_ISR_API == STD_ON)
    TAUB1_CH15_ISR,
  #else
    DUMMY(271),
  #endif

  DUMMY(272), DUMMY(273), DUMMY(274), DUMMY(275),
  DUMMY(276), DUMMY(277), DUMMY(278), DUMMY(279), DUMMY(280), DUMMY(281),
  DUMMY(282), DUMMY(283), DUMMY(284), DUMMY(285), DUMMY(286), DUMMY(287),
  DUMMY(288), DUMMY(289), DUMMY(290), DUMMY(291), DUMMY(292), DUMMY(293),
  DUMMY(294), DUMMY(295), DUMMY(296), DUMMY(297), DUMMY(298), DUMMY(299),
  DUMMY(300), DUMMY(301), DUMMY(302), DUMMY(303), DUMMY(304), DUMMY(305),
  DUMMY(306), DUMMY(307), DUMMY(308), DUMMY(309), DUMMY(310), DUMMY(311),
  DUMMY(312), DUMMY(313), DUMMY(314), DUMMY(315), DUMMY(316), DUMMY(317),
  DUMMY(318), DUMMY(319), DUMMY(320), DUMMY(321), DUMMY(322), DUMMY(323),
  DUMMY(324), DUMMY(325), DUMMY(326), DUMMY(327), DUMMY(328), DUMMY(329),
  DUMMY(330), DUMMY(331), DUMMY(332), DUMMY(333), DUMMY(334), DUMMY(335),
  DUMMY(336), DUMMY(337), DUMMY(338), DUMMY(339), DUMMY(340), DUMMY(341),
  DUMMY(342), DUMMY(343), DUMMY(344), DUMMY(345), DUMMY(346), DUMMY(347),
  DUMMY(348), DUMMY(349), DUMMY(350), DUMMY(351), DUMMY(352), DUMMY(353),
  DUMMY(354), DUMMY(355), DUMMY(356), DUMMY(357), DUMMY(358), DUMMY(359),
  DUMMY(360), DUMMY(361), DUMMY(362), DUMMY(363), DUMMY(364), DUMMY(365),
  DUMMY(366), DUMMY(367), DUMMY(368), DUMMY(369), DUMMY(370), DUMMY(371),
  DUMMY(372), DUMMY(373), DUMMY(374), DUMMY(375), DUMMY(376), DUMMY(377),
  DUMMY(378), DUMMY(379), DUMMY(380), DUMMY(381)
};
/* End of #ifdef GLOBAL_MODULE_TEST */
#endif

/* Continue: #ifdef F1KM_S1_DEVICE #elif defined F1KM_S4_DEVICE
   #elif defined F1KM_S2_DEVICE*/
#else
  #error "Unknown device family used for compilation. Abort."
/* End: #ifdef F1KM_S1_DEVICE */
#endif

/******************************************************************************
**                          End of File                                      **
*******************************************************************************/
