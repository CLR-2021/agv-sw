/******************************************************************************
 * @file    TIMER.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Interfaces header file for \ref TIMER.c
 * @version 1.0.0
 * @date    2022-03-20
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#ifndef TIMER_H
#define TIMER_H

/*---------------------------------------------------------------------------*/
/*                              TYPE DEFINITIONS                             */
/*---------------------------------------------------------------------------*/

typedef enum{
    NO_CLOCK,       /* No clock source: Timer/Counter stopped */
    F_CPU_CLOCK,    /* F_CPU clock source: no prescaling */
    F_CPU_8,        /* F_CPU/8 clock source: from prescaler */
    F_CPU_32,       /* F_CPU/32 clock source: from prescaler */
    F_CPU_64,       /* F_CPU/64 clock source: from prescaler */
    F_CPU_128,      /* F_CPU/128 clock source: from prescaler */
    F_CPU_256,      /* F_CPU/256 clock source: from prescaler */
    F_CPU_1024,     /* F_CPU/1024 clock source: from prescaler */
    F_CPU_EXT_CLK_FALLING,  /* F_CPU/EXTERNAL_CLOCK_FALLING clock source: from prescaler */
    F_CPU_EXT_CLK_RISING    /* F_CPU/EXTERNAL_CLOCK_RISING clock source: from prescaler */
}TIMER_CLOCK_t;

typedef enum{
    TIMER_MODE_NORMAL,      /* Normal mode: counter is incremented on the rising edge of the OCn pin */
    TIMER_MODE_CTC,         /* Clear Timer on Compare Match (CTC) mode: counter is cleared when the counter matches the OCRn register */
    TIMER_MODE_CTC_OCR,     /* Clear Timer on Compare Match (CTC) mode: counter is cleared when the counter matches the OCRn register */
    TIMER_MODE_CTC_ICR,     /* Clear Timer on Compare Match (CTC) mode: counter is cleared when the counter matches the ICRn register */
    TIMER_MODE_FAST_PWM,    /* Fast PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_8,  /* Fast PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_9,  /* Fast PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_10, /* Fast PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_ICR,/* Fast PWM mode: counter is incremented on the rising edge of the OCn pin, and the ICRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_OCR,/* Fast PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM,       /* Phase Correct PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_8,     /* Phase Correct PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_9,     /* Phase Correct PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_10,    /* Phase Correct PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_ICR,   /* Phase Correct PWM mode: counter is incremented on the rising edge of the OCn pin, and the ICRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_OCR,   /* Phase Correct PWM mode: counter is incremented on the rising edge of the OCn pin, and the OCRn register is used as TOP value */
    TIMER_MODE_PHASE_FREQ_CORRECT_ICR,  /* Phase and Frequency Correct ICR mode: counter is incremented on the rising edge of the ICR1 register */
    TIMER_MODE_PHASE_FREQ_CORRECT_OCR,  /* Phase and Frequency Correct OCR mode: counter is incremented on the rising edge of the OCR1 register */
}TIMER_MODE_t;

typedef enum{
    NO_OC,         /* No output compare: OCn disconnected */
    TOGGLE_OC,     /* Toggle OCn on compare match: OCn is set when the counter matches the OCR0 register, and cleared at the next OCR0 match */
    CLEAR_OC,      /* Clear OCn on compare match: OCn is cleared when the counter matches the OCR0 register, and set at the next OCR0 match */
    SET_OC         /* Set OCn on compare match: OCn is set when the counter matches the OCR0 register, and cleared at the next OCR0 match */
}TIMER_OC_t;

typedef enum{
    TIMER_OCA,     /* Output Compare A */
    TIMER_OCB,     /* Output Compare B */
    TIMER_OCC,     /* Output Compare C */
}TIMER_OCx_t;

typedef enum{
    PWM_0,    /* Connected with pin --> OC0      */
    PWM_1,    /* Connected with pin --> OC1A     */
    PWM_2,    /* Connected with pin --> OC1B     */
    PWM_3,    /* Connected with pin --> OC1C     */
    PWM_4,    /* Connected with pin --> OC2      */
    PWM_5,    /* Connected with pin --> OC3A     */
    PWM_6,    /* Connected with pin --> OC3B     */
    PWM_7,    /* Connected with pin --> OC3C     */
}PWM_t;

/*---------------------------------------------------------------------------*/
/*                              FUNCTION PROTOTYPES                          */
/*---------------------------------------------------------------------------*/

/******************************************************************************
 *                      Prototypes of Timer 0 functions
 *****************************************************************************/
void TIMER0_Init(u8 initValue, TIMER_CLOCK_t clock, TIMER_MODE_t timerMode, TIMER_OC_t compareMode);
void TIMER0_SetCompareValue(u8 u8CompareValue);
void TIMER0_SetTimer(u8 u8TimerValue);
void TIMER0_EnableOverflowInterrupt(void (*callBackPtr)(void));
void TIMER0_DisableOverflowInterrupt(void);
void TIMER0_EnableCompareMatchInterrupt(void (*callBackPtr)(void));
void TIMER0_DisableCompareMatchInterrupt(void);
u8 TIMER0_GetTimerValue(void);
void PWM_Init(PWM_t channel, u32 frequency);
void PWM_Write(PWM_t channel, u8 dutyPercentage);


/******************************************************************************
 *                      Prototypes of Timer 1 functions
 *****************************************************************************/
void TIMER1_Init(u16 initValue, TIMER_CLOCK_t clock, TIMER_MODE_t timerMode, TIMER_OC_t compareMode, TIMER_OCx_t OCx);
void TIMER1_SetCompareValue(u16 u16CompareValue, TIMER_OCx_t OCx);
void TIMER1_SetTimer(u16 u16TimerValue);
void TIMER1_EnableOverflowInterrupt(void (*callBackPtr)(void));
void TIMER1_DisableOverflowInterrupt(void);
void TIMER1_EnableCompareMatchInterrupt(TIMER_OCx_t OCx, void (*callBackPtr)(void));
void TIMER1_DisableCompareMatchInterrupt(TIMER_OCx_t OCx);
void TIMER1_EnableCaptureInterrupt(void (*callBackPtr)(void));
void TIMER1_DisableCaptureInterrupt(void);
u16 TIMER1_GetTimerValue(void);

#endif  /* TIMER_H */   
