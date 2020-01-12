/* File: startup_stm32l475xx.c
 * Purpose: startup file for STM32L475 devices.
 *          Should be used with GCC 'GNU Tools ARM Embedded'
 * Version: V1.01
 * Date: 12 June 2014
 *
 */
/* Copyright (c) 2011 - 2014 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------
  Linker generated Symbols
 *----------------------------------------------------------------------------*/
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __copy_table_start__;
extern uint32_t __copy_table_end__;
extern uint32_t __zero_table_start__;
extern uint32_t __zero_table_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackTop;

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc ) (void);


/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
#ifndef __START
extern void
_start (void) __attribute__((noreturn));    /* PreeMain (C library entry point) */
#else
extern int  __START(void) __attribute__((noreturn));    /* main entry point */
#endif

#ifndef __NO_SYSTEM_INIT
extern void SystemInit (void);            /* CMSIS System Initialization      */
#endif

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void Default_Handler (void);              /* Default empty handler */
void Reset_Handler (void);                /* Reset Handler */


/*----------------------------------------------------------------------------
  User Initial Stack & Heap
 *----------------------------------------------------------------------------*/
#ifndef __STACK_SIZE
#define    __STACK_SIZE  0x00000400
#endif
static uint8_t stack[__STACK_SIZE] __attribute__ ((aligned(8), used, section(".stack")));

#ifndef __HEAP_SIZE
#define    __HEAP_SIZE   0x00000C00
#endif
#if __HEAP_SIZE > 0
static uint8_t heap[__HEAP_SIZE]   __attribute__ ((aligned(8), used, section(".heap")));
#endif


/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Cortex-M4 Processor Exceptions */
void NMI_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler (void) __attribute__ ((weak, alias("Default_Handler")));

/* STM32L475 Specific Interrupts */
void WWDG_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_PVM_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
TAMP_STAMP_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
RTC_WKUP_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA1_Channel1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA1_Channel2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA1_Channel3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA1_Channel4_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA1_Channel5_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA1_Channel6_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA1_Channel7_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
CAN1_RX0_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
CAN1_RX1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
CAN1_SCE_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
TIM1_BRK_TIM15_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
TIM1_UP_TIM16_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
TIM1_TRG_COM_TIM17_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
EXTI15_10_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
RTC_Alarm_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DFSDM1_FLT3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
TIM8_BRK_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
TIM8_TRG_COM_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void FMC_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void SDMMC1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
TIM6_DAC_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA2_Channel1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA2_Channel2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA2_Channel3_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA2_Channel4_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA2_Channel5_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DFSDM1_FLT0_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DFSDM1_FLT1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DFSDM1_FLT2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void LPTIM1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void LPTIM2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA2_Channel6_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void
DMA2_Channel7_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void LPUART1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void QUADSPI_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void SAI1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void SAI2_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void SWPMI1_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void TSC_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void RNG_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler (void) __attribute__ ((weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
const pFunc __Vectors[] __attribute__ ((section(".vectors"))) = {
    /* STM32L475 Exceptions Handler */
    (pFunc)&__StackTop,                       /*      Initial Stack Pointer     */
    Reset_Handler,                            /*      Reset Handler             */
    NMI_Handler,                              /*      NMI Handler               */
    HardFault_Handler,                        /*      Hard Fault Handler        */
    MemManage_Handler,                        /*      MPU Fault Handler         */
    BusFault_Handler,                         /*      Bus Fault Handler         */
    UsageFault_Handler,                       /*      Usage Fault Handler       */
    0,                                        /*      Reserved                  */
    0,                                        /*      Reserved                  */
    0,                                        /*      Reserved                  */
    0,                                        /*      Reserved                  */
    SVC_Handler,                              /*      SVCall Handler            */
    DebugMon_Handler,                         /*      Debug Monitor Handler     */
    0,                                        /*      Reserved                  */
    PendSV_Handler,                           /*      PendSV Handler            */
    SysTick_Handler,                          /*      SysTick Handler           */

    /* External interrupts */
    WWDG_IRQHandler,                          /*   0 Interrupt 0 */
    PVD_PVM_IRQHandler,                       /*   1 Interrupt 0 */
    TAMP_STAMP_IRQHandler,                    /*   2 Interrupt 0 */
    RTC_WKUP_IRQHandler,                      /*   3 Interrupt 0 */
    FLASH_IRQHandler,                         /*   4 Interrupt 0 */
    RCC_IRQHandler,                           /*   5 Interrupt 0 */
    EXTI0_IRQHandler,                         /*   6 Interrupt 0 */
    EXTI1_IRQHandler,                         /*   7 Interrupt 0 */
    EXTI2_IRQHandler,                         /*   8 Interrupt 0 */
    EXTI3_IRQHandler,                         /*   9 Interrupt 0 */
    EXTI4_IRQHandler,                         /*   10 Interrupt 0 */
    DMA1_Channel1_IRQHandler,                 /*   11 Interrupt 0 */
    DMA1_Channel2_IRQHandler,                 /*   12 Interrupt 0 */
    DMA1_Channel3_IRQHandler,                 /*   13 Interrupt 0 */
    DMA1_Channel4_IRQHandler,                 /*   14 Interrupt 0 */
    DMA1_Channel5_IRQHandler,                 /*   15 Interrupt 0 */
    DMA1_Channel6_IRQHandler,                 /*   16 Interrupt 0 */
    DMA1_Channel7_IRQHandler,                 /*   17 Interrupt 0 */
    ADC1_2_IRQHandler,                        /*   18 Interrupt 0 */
    CAN1_TX_IRQHandler,                       /*   19 Interrupt 0 */
    CAN1_RX0_IRQHandler,                      /*   20 Interrupt 0 */
    CAN1_RX1_IRQHandler,                      /*   21 Interrupt 0 */
    CAN1_SCE_IRQHandler,                      /*   22 Interrupt 0 */
    EXTI9_5_IRQHandler,                       /*   23 Interrupt 0 */
    TIM1_BRK_TIM15_IRQHandler,                /*   24 Interrupt 0 */
    TIM1_UP_TIM16_IRQHandler,                 /*   25 Interrupt 0 */
    TIM1_TRG_COM_TIM17_IRQHandler,            /*   26 Interrupt 0 */
    TIM1_CC_IRQHandler,                       /*   27 Interrupt 0 */
    TIM2_IRQHandler,                          /*   28 Interrupt 0 */
    TIM3_IRQHandler,                          /*   29 Interrupt 0 */
    TIM4_IRQHandler,                          /*   30 Interrupt 0 */
    I2C1_EV_IRQHandler,                       /*   31 Interrupt 0 */
    I2C1_ER_IRQHandler,                       /*   32 Interrupt 0 */
    I2C2_EV_IRQHandler,                       /*   33 Interrupt 0 */
    I2C2_ER_IRQHandler,                       /*   34 Interrupt 0 */
    SPI1_IRQHandler,                          /*   35 Interrupt 0 */
    SPI2_IRQHandler,                          /*   36 Interrupt 0 */
    USART1_IRQHandler,                        /*   37 Interrupt 0 */
    USART2_IRQHandler,                        /*   38 Interrupt 0 */
    USART3_IRQHandler,                        /*   39 Interrupt 0 */
    EXTI15_10_IRQHandler,                     /*   40 Interrupt 0 */
    RTC_Alarm_IRQHandler,                     /*   41 Interrupt 0 */
    DFSDM1_FLT3_IRQHandler,                   /*   42 Interrupt 0 */
    TIM8_BRK_IRQHandler,                      /*   43 Interrupt 0 */
    TIM8_UP_IRQHandler,                       /*   44 Interrupt 0 */
    TIM8_TRG_COM_IRQHandler,                  /*   45 Interrupt 0 */
    TIM8_CC_IRQHandler,                       /*   46 Interrupt 0 */
    ADC3_IRQHandler,                          /*   47 Interrupt 0 */
    FMC_IRQHandler,                           /*   48 Interrupt 0 */
    SDMMC1_IRQHandler,                        /*   49 Interrupt 0 */
    TIM5_IRQHandler,                          /*   50 Interrupt 0 */
    SPI3_IRQHandler,                          /*   51 Interrupt 0 */
    UART4_IRQHandler,                         /*   52 Interrupt 0 */
    UART5_IRQHandler,                         /*   53 Interrupt 0 */
    TIM6_DAC_IRQHandler,                      /*   54 Interrupt 0 */
    TIM7_IRQHandler,                          /*   55 Interrupt 0 */
    DMA2_Channel1_IRQHandler,                 /*   56 Interrupt 0 */
    DMA2_Channel2_IRQHandler,                 /*   57 Interrupt 0 */
    DMA2_Channel3_IRQHandler,                 /*   58 Interrupt 0 */
    DMA2_Channel4_IRQHandler,                 /*   59 Interrupt 0 */
    DMA2_Channel5_IRQHandler,                 /*   60 Interrupt 0 */
    DFSDM1_FLT0_IRQHandler,                   /*   61 Interrupt 0 */
    DFSDM1_FLT1_IRQHandler,                   /*   62 Interrupt 0 */
    DFSDM1_FLT2_IRQHandler,                   /*   63 Interrupt 0 */
    COMP_IRQHandler,                          /*   64 Interrupt 0 */
    LPTIM1_IRQHandler,                        /*   65 Interrupt 0 */
    LPTIM2_IRQHandler,                        /*   66 Interrupt 0 */
    OTG_FS_IRQHandler,                        /*   67 Interrupt 0 */
    DMA2_Channel6_IRQHandler,                 /*   68 Interrupt 0 */
    DMA2_Channel7_IRQHandler,                 /*   69 Interrupt 0 */
    LPUART1_IRQHandler,                       /*   70 Interrupt 0 */
    QUADSPI_IRQHandler,                       /*   71 Interrupt 0 */
    I2C3_EV_IRQHandler,                       /*   72 Interrupt 0 */
    I2C3_ER_IRQHandler,                       /*   73 Interrupt 0 */
    SAI1_IRQHandler,                          /*   74 Interrupt 0 */
    SAI2_IRQHandler,                          /*   75 Interrupt 0 */
    SWPMI1_IRQHandler,                        /*   76 Interrupt 0 */
    TSC_IRQHandler,                           /*   77 Interrupt 0 */
    0,                                        /*     Reserved */
    0,                                        /*     Reserved */
    RNG_IRQHandler,                           /*   78 Interrupt 0 */
    FPU_IRQHandler                            /*   79 Interrupt 0 */
    /* Interrupts 80 .. 223 are left out */
};

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler (void)
{
  uint32_t *pSrc, *pDest;
  uint32_t *pTable __attribute__((unused));

  /*  Firstly it copies data from read only memory to RAM. There are two schemes
   *  to copy. One can copy more than one sections. Another can only copy
   *  one section.  The former scheme needs more instructions and read-only
   *  data to implement than the latter.
   *  Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.  */

  #ifdef __STARTUP_COPY_MULTIPLE
  /*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of triplets, each of which specify:
 *    offset 0: LMA of start of a section to copy from
 *    offset 4: VMA of start of a section to copy to
 *    offset 8: size of the section to copy. Must be multiply of 4
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
  pTable = &__copy_table_start__;

  for (; pTable < &__copy_table_end__; pTable = pTable + 3) {
        pSrc  = (uint32_t*)*(pTable + 0);
        pDest = (uint32_t*)*(pTable + 1);
        for (; pDest < (uint32_t*)(*(pTable + 1) + *(pTable + 2)) ; ) {
      *pDest++ = *pSrc++;
        }
    }
  #else
  /*  Single section scheme.
   *
   *  The ranges of copy from/to are specified by following symbols
   *    __etext: LMA of start of the section to copy from. Usually end of text
   *    __data_start__: VMA of start of the section to copy to
   *    __data_end__: VMA of end of the section to copy to
   *
   *  All addresses must be aligned to 4 bytes boundary.
   */
  pSrc = &__etext;
  pDest = &__data_start__;

  for (; pDest < &__data_end__;)
    {
      *pDest++ = *pSrc++;
    }
  #endif /*__STARTUP_COPY_MULTIPLE */

  /*  This part of work usually is done in C library startup code. Otherwise,
   *  define this macro to enable it in this startup.
   *
   *  There are two schemes too. One can clear multiple BSS sections. Another
   *  can only clear one section. The former is more size expensive than the
   *  latter.
   *
   *  Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
   *  Otherwise efine macro __STARTUP_CLEAR_BSS to choose the later.
   */
  #ifdef __STARTUP_CLEAR_BSS_MULTIPLE
  /*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of tuples specifying:
 *    offset 0: Start of a BSS section
 *    offset 4: Size of this BSS section. Must be multiply of 4
 */
  pTable = &__zero_table_start__;

  for (; pTable < &__zero_table_end__; pTable = pTable + 2) {
        pDest = (uint32_t*)*(pTable + 0);
        for (; pDest < (uint32_t*)(*(pTable + 0) + *(pTable + 1)) ; ) {
      *pDest++ = 0;
        }
    }
  #elif defined (__STARTUP_CLEAR_BSS)
  /*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
  pDest = &__bss_start__;

  for ( ; pDest < &__bss_end__ ; ) {
    *pDest++ = 0ul;
  }
  #endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

  #ifndef __NO_SYSTEM_INIT
  SystemInit ();
  #endif

  #ifndef __START
  #define __START _start
  #endif
  __START ();

}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler (void)
{
  while (1);
}
