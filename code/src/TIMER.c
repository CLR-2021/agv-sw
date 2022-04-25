/**************************************************************************
 * @file    TIMER.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Timer driver for ATMEGA128 microcontroller.
 * @version 1.0.0
 * @date    2022-02-11
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_reg.h"
#include "SREG.h"
#include "GIE.h"
#include "TIMER.h"

/**************************************************************************
 *                              CALLBACKS                                 *
 **************************************************************************/
static void (*TIMER0_OVF_CBK_PTR)(void)     = NULL;
static void (*TIMER0_COMP_CBK_PTR)(void)    = NULL;
 
static void (*TIMER1_OVF_CBK_PTR)(void)     = NULL;
static void (*TIMER1_COMPA_CBK_PTR)(void)   = NULL;
static void (*TIMER1_COMPB_CBK_PTR)(void)   = NULL;
static void (*TIMER1_COMPC_CBK_PTR)(void)   = NULL;
static void (*TIMER1_CAPT_CBK_PTR)(void)    = NULL;
 
static void (*TIMER2_OVF_CBK_PTR)(void)     = NULL;
static void (*TIMER2_COMP_CBK_PTR)(void)    = NULL;
 
static void (*TIMER3_OVF_CBK_PTR)(void)     = NULL;
static void (*TIMER3_COMPA_CBK_PTR)(void)   = NULL;
static void (*TIMER3_COMPB_CBK_PTR)(void)   = NULL;
static void (*TIMER3_COMPC_CBK_PTR)(void)   = NULL;
static void (*TIMER3_CAPT_CBK_PTR)(void)    = NULL;

void TIMER0_SetCallBack(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER0_OVF_CBK_PTR = ptr;
}

void TIMER0_SetCompareCallBack(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER0_COMP_CBK_PTR = ptr;
}

void TIMER1_SetCallBack(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER1_OVF_CBK_PTR = ptr;
}

void TIMER1_SetCompareCallBackA(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER1_COMPA_CBK_PTR = ptr;
}

void TIMER1_SetCompareCallBackB(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER1_COMPB_CBK_PTR = ptr;
}

void TIMER1_SetCompareCallBackC(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER1_COMPC_CBK_PTR = ptr;
}

void TIMER1_SetCaptureCallBack(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER1_CAPT_CBK_PTR = ptr;
}

void TIMER2_SetCallBack(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER2_OVF_CBK_PTR = ptr;
}

void TIMER2_SetCompareCallBack(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER2_COMP_CBK_PTR = ptr;
}

void TIMER3_SetCallBack(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER3_OVF_CBK_PTR = ptr;
}

void TIMER3_SetCompareCallBackA(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER3_COMPA_CBK_PTR = ptr;
}

void TIMER3_SetCompareCallBackB(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER3_COMPB_CBK_PTR = ptr;
}

void TIMER3_SetCompareCallBackC(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER3_COMPC_CBK_PTR = ptr;
}

void TIMER3_SetCaptureCallBack(void (*ptr)(void)) {
    /* Set the call back function */
    TIMER3_CAPT_CBK_PTR = ptr;
}

/*----------------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS                                 */
/*----------------------------------------------------------------------------*/

/*************************************************************************
 *                          Timer0 Functions
 ************************************************************************/

static void TIMER0_ConfigClock(TIMER_CLOCK_t clock) {
    /* Set the clock */
    switch(clock) {
        case NO_CLOCK:
            /* No clock source */
            CLR_BIT(TCCR0, CS00);
            CLR_BIT(TCCR0, CS01);
            CLR_BIT(TCCR0, CS02);
            break;
        case F_CPU_CLOCK:
            /* No prescaling */
            SET_BIT(TCCR0, CS00);
            CLR_BIT(TCCR0, CS01);
            CLR_BIT(TCCR0, CS02);
            break;
        case F_CPU_8:
            /* Prescaling by 8 */
            CLR_BIT(TCCR0, CS00);
            SET_BIT(TCCR0, CS01);
            CLR_BIT(TCCR0, CS02);
            break;
        case F_CPU_32:
            /* Prescaling by 32 */
            SET_BIT(TCCR0, CS00);
            SET_BIT(TCCR0, CS01);
            CLR_BIT(TCCR0, CS02);
            break;
        case F_CPU_64:
            /* Prescaling by 64 */
            CLR_BIT(TCCR0, CS00);
            CLR_BIT(TCCR0, CS01);
            SET_BIT(TCCR0, CS02);
            break;
        case F_CPU_128:
            /* Prescaling by 128 */
            SET_BIT(TCCR0, CS00);
            CLR_BIT(TCCR0, CS01);
            SET_BIT(TCCR0, CS02);
            break;
        case F_CPU_256:
            /* Prescaling by 256 */
            CLR_BIT(TCCR0, CS00);
            SET_BIT(TCCR0, CS01);
            SET_BIT(TCCR0, CS02);
            break;
        case F_CPU_1024:
            /* Prescaling by 1024 */
            SET_BIT(TCCR0, CS00);
            SET_BIT(TCCR0, CS01);
            SET_BIT(TCCR0, CS02);
            break;
        default:
            /* TODO: DEBUG    */
            break;
    }
}

static void TIMER0_ConfigMode(TIMER_MODE_t timerMode) {
    /* Set the timer mode */
    switch(timerMode) {
        case TIMER_MODE_NORMAL:       /* Normal mode */
            CLR_BIT(TCCR0, WGM00);
            CLR_BIT(TCCR0, WGM01);
            /* Set force output compare mode with non-PWM mode */
            SET_BIT(TCCR0, FOC0);
            break;
        case TIMER_MODE_CTC:          /* Clear Timer on Compare Match mode */
            CLR_BIT(TCCR0, WGM00);
            SET_BIT(TCCR0, WGM01);
            /* Set force output compare mode with non-PWM mode */
            SET_BIT(TCCR0, FOC0);
            break;
        case TIMER_MODE_FAST_PWM:     /* Fast PWM mode */
            SET_BIT(TCCR0, WGM00);
            SET_BIT(TCCR0, WGM01);
            break;
        case TIMER_MODE_PHASE_CORRECT_PWM:    /* Phase Correct PWM mode */
            SET_BIT(TCCR0, WGM00);
            CLR_BIT(TCCR0, WGM01);
            break;
        default:                
            /* TODO: DEBUG    */
            break;
    }
}

static void TIMER0_ConfigOC(TIMER_MODE_t timerMode, TIMER_OC_t compareMode) {
    /* Set the compare mode */
    switch (compareMode) {
        case NO_OC:    /* Normal compare mode */
            CLR_BIT(TCCR0, COM00);
            CLR_BIT(TCCR0, COM01);
            break;
        case TOGGLE_OC:
            if((timerMode == TIMER_MODE_NORMAL) || (timerMode == TIMER_MODE_CTC)) {
                /* Toggle compare mode */
                SET_BIT(TCCR0, COM00);
                CLR_BIT(TCCR0, COM01);
            }
            else{
                /* TODO: DEBUG    */
            }
            break;
        case CLEAR_OC: /* Clear compare mode: Non-Inverting mode */
            CLR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
            break;
        case SET_OC:   /* Set compare mode: Inverting mode */
            SET_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
            break;
        default:
            /* TODO: DEBUG    */
            break;
    }
}

/*************************************************************************
 *                          Timer1 Functions
 ************************************************************************/

static void TIMER1_ConfigClock(TIMER_CLOCK_t timerClock) {
    /* Set the clock source */
    switch(timerClock) {
        case NO_CLOCK:
            /* No clock source */
            CLR_BIT(TCCR1B, CS10);
            CLR_BIT(TCCR1B, CS11);
            CLR_BIT(TCCR1B, CS12);
            break;
        case F_CPU_CLOCK:
            /* No prescaling */
            SET_BIT(TCCR1B, CS10);
            CLR_BIT(TCCR1B, CS11);
            CLR_BIT(TCCR1B, CS12);
            break;
        case F_CPU_8:
            /* Prescaling by 8 */
            CLR_BIT(TCCR1B, CS10);
            SET_BIT(TCCR1B, CS11);
            CLR_BIT(TCCR1B, CS12);
            break;
        case F_CPU_64:
            /* Prescaling by 64 */
            SET_BIT(TCCR1B, CS10);
            SET_BIT(TCCR1B, CS11);
            CLR_BIT(TCCR1B, CS12);
            break;
        case F_CPU_256:
            /* Prescaling by 256 */
            CLR_BIT(TCCR1B, CS10);
            CLR_BIT(TCCR1B, CS11);
            SET_BIT(TCCR1B, CS12);
            break;
        case F_CPU_1024:
            /* Prescaling by 1024 */
            SET_BIT(TCCR1B, CS10);
            CLR_BIT(TCCR1B, CS11);
            SET_BIT(TCCR1B, CS12);
            break;
        case F_CPU_EXT_CLK_FALLING:
            /* External clock on T1 pin, falling edge */
            CLR_BIT(TCCR1B, CS10);
            SET_BIT(TCCR1B, CS11);
            SET_BIT(TCCR1B, CS12);
            break;
        case F_CPU_EXT_CLK_RISING:
            /* External clock on T1 pin, rising edge */
            SET_BIT(TCCR1B, CS10);
            SET_BIT(TCCR1B, CS11);
            SET_BIT(TCCR1B, CS12);
            break;
        default:
            break;
    }
}

static void TIMER1_ConfigMode(TIMER_MODE_t timerMode) {
    /* Set the timer mode */
    switch (timerMode) {
        case TIMER_MODE_NORMAL:                 /* Normal mode */
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_PHASE_CORRECT_PWM_8:    /* Phase Correct PWM mode 8 */
            SET_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_PHASE_CORRECT_PWM_9:    /* Phase Correct PWM mode 9 */
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_PHASE_CORRECT_PWM_10:   /* Phase Correct PWM mode 10 */
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_CTC_OCR:                /* CTC mode */
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_FAST_PWM_8:             /* Fast PWM mode 8 */
            SET_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_FAST_PWM_9:             /* Fast PWM mode 9 */
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_FAST_PWM_10:            /* Fast PWM mode 10 */
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            CLR_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_PHASE_FREQ_CORRECT_ICR: /* Phase and Frequency Correct PWM mode */
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_PHASE_FREQ_CORRECT_OCR: /* Phase and Frequency Correct PWM mode */
            SET_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_PHASE_CORRECT_PWM_ICR:  /* Phase Correct PWM mode */
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_PHASE_CORRECT_PWM_OCR:  /* Phase Correct PWM mode */
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            CLR_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_CTC_ICR:                /* CTC mode */
            CLR_BIT(TCCR1A, WGM10);
            CLR_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_FAST_PWM_ICR:           /* Fast PWM mode */
            CLR_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
            break;
        case TIMER_MODE_FAST_PWM_OCR:           /* Fast PWM mode */
            SET_BIT(TCCR1A, WGM10);
            SET_BIT(TCCR1A, WGM11);
            SET_BIT(TCCR1B, WGM12);
            SET_BIT(TCCR1B, WGM13);
            break;
        default:
            break;
    }
}

static void TIMER1_ConfigOCA(TIMER_OC_t timerOC) {
    /* Set the output compare mode */
    switch (timerOC) {
        case NO_OC:
            /* Disable output compare */
            CLR_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
            break;
        case TOGGLE_OC:
            /* Toggle output compare */
            SET_BIT(TCCR1A, COM1A0);
            CLR_BIT(TCCR1A, COM1A1);
            /* 
                WGMn3:0 = 15: Toggle OCA on Compare Match, OCB/OCC disconnected 
                (normal port operation).
                For all other WGMn settings, normal port operation, 
                OCA/OCB/OCC disconnected. 
            */
            /* 
                WGMn3:0 = 9 or 11: Toggle OCnA on Compare Match, OCnB/OCnC 
                disconnected (normal port operation). 
                For all other WGMn settings, normal port operation, 
                OCnA/OCnB/OCnC disconnected.
            */
            break;
        case CLEAR_OC:
            /* Clear output compare */
            CLR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
            break;
        case SET_OC:
            /* Set output compare */
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
            break;
        default:
            break;
    }
}

static void TIMER1_ConfigOCB(TIMER_OC_t timerOC) {
    /* Set the output compare mode */
    switch (timerOC) {
        case NO_OC:
            /* Disable output compare */
            CLR_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
            break;
        case TOGGLE_OC:
            /* Toggle output compare */
            SET_BIT(TCCR1A, COM1B0);
            CLR_BIT(TCCR1A, COM1B1);
            /* 
                WGMn3:0 = 15: Toggle OCA on Compare Match, OCB/OCC disconnected 
                (normal port operation).
                For all other WGMn settings, normal port operation, 
                OCA/OCB/OCC disconnected. 
            */
            /* 
                WGMn3:0 = 9 or 11: Toggle OCnA on Compare Match, OCnB/OCnC 
                disconnected (normal port operation). 
                For all other WGMn settings, normal port operation, 
                OCnA/OCnB/OCnC disconnected.
            */
            break;
        case CLEAR_OC:
            /* Clear output compare */
            CLR_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
            break;
        case SET_OC:
            /* Set output compare */
            SET_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
            break;
        default:
            break;
    }
}

static void TIMER1_ConfigOCC(TIMER_OC_t timerOC) {
    /* Set the output compare mode */
    switch (timerOC) {
        case NO_OC:
            /* Disable output compare */
            CLR_BIT(TCCR1A, COM1C0);
            CLR_BIT(TCCR1A, COM1C1);
            break;
        case TOGGLE_OC:
            /* Toggle output compare */
            SET_BIT(TCCR1A, COM1C0);
            CLR_BIT(TCCR1A, COM1C1);
            /* 
                WGMn3:0 = 15: Toggle OCA on Compare Match, OCB/OCC disconnected 
                (normal port operation).
                For all other WGMn settings, normal port operation, 
                OCA/OCB/OCC disconnected. 
            */
            /* 
                WGMn3:0 = 9 or 11: Toggle OCnA on Compare Match, OCnB/OCnC 
                disconnected (normal port operation). 
                For all other WGMn settings, normal port operation, 
                OCnA/OCnB/OCnC disconnected.
            */
            break;
        case CLEAR_OC:
            /* Clear output compare */
            CLR_BIT(TCCR1A, COM1C0);
            SET_BIT(TCCR1A, COM1C1);
            break;
        case SET_OC:
            /* Set output compare */
            SET_BIT(TCCR1A, COM1C0);
            SET_BIT(TCCR1A, COM1C1);
            break;
        default:
            break;
    }
}


/*---------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                             */
/*---------------------------------------------------------------------------*/

/*******************************************************************************
 *                  TIMER0 Implementations
 ******************************************************************************/
void TIMER0_Init(u8 initValue, TIMER_CLOCK_t clock, TIMER_MODE_t timerMode, TIMER_OC_t compareMode) {
    /* Set the timer initial value */
    TCNT0 = initValue;

    /* Set the clock */
    TIMER0_ConfigClock(clock);

    /* Set the timer mode */
    TIMER0_ConfigMode(timerMode);

    /* Set the compare mode */
    TIMER0_ConfigOC(timerMode, compareMode);
}

void TIMER0_SetCompareValue(u8 u8CompareValue) {
    OCR0 = u8CompareValue;
}

void TIMER0_SetTimer(u8 u8TimerValue) {
    TCNT0 = u8TimerValue;
}

void TIMER0_EnableOverflowInterrupt(void (*callBackPtr)(void)) {
    TIMER0_SetCallBack(callBackPtr);

    /* Enable the overflow interrupt */
    SET_BIT(TIMER_u8TIMSK_REG, TOIE0);

    /* Enable global interrupt */
    GIE_Enable();
}

void TIMER0_DisableOverflowInterrupt(void) {
    /* Disable the overflow interrupt */
    CLR_BIT(TIMER_u8TIMSK_REG, TOIE0);
}

void TIMER0_EnableCompareMatchInterrupt(void (*callBackPtr)(void)) {
    TIMER0_SetCompareCallBack(callBackPtr);

    /* Enable the compare match interrupt */
    SET_BIT(TIMER_u8TIMSK_REG, OCIE0);

    /* Enable global interrupt */
    GIE_Enable();
}

void TIMER0_DisableCompareMatchInterrupt(void) {
    /* Disable the compare match interrupt */
    CLR_BIT(TIMER_u8TIMSK_REG, OCIE0);
}

u8 TIMER0_GetTimerValue(void) {
    return TCNT0;
}

void PWM0_Write(u8 dutyPercentage) {
    u8 ocr = 0;

    ocr = (dutyPercentage * (u16) 255) / 100;

    TIMER0_SetCompareValue(ocr);
}

/*******************************************************************************
 *                          TIMER1 Implementations
 ******************************************************************************/
void TIMER1_Init(u16 initValue, TIMER_CLOCK_t clock, TIMER_MODE_t timerMode, TIMER_OC_t compareMode, TIMER_OCx_t OCx) {
    /* Set the timer initial value */
    /* Upper register must be written first */
    TCNT1H = (u8)(initValue >> 8);
    TCNT1L = (u8)(initValue);

    /* Set the clock */
    TIMER1_ConfigClock(clock);

    /* Set the timer mode */
    TIMER1_ConfigMode(timerMode);

    /* Set the compare mode */
    switch(OCx) {
        case TIMER_OCA:
            TIMER1_ConfigOCA(compareMode);
            break;
        case TIMER_OCB:
            TIMER1_ConfigOCB(compareMode);
            break;
        case TIMER_OCC:
            TIMER1_ConfigOCC(compareMode);
            break;
        default:
            break;
    }
}

void TIMER1_SetCompareValue(u16 u16CompareValue, TIMER_OCx_t OCx) {
    u8 sreg = SREG;

    GIE_Disable();

    switch(OCx) {
        case TIMER_OCA:
            OCR1AH = (u8)(u16CompareValue >> 8);
            OCR1AL = (u8)(u16CompareValue);
            break;
        case TIMER_OCB:
            OCR1BH = (u8)(u16CompareValue >> 8);
            OCR1BL = (u8)(u16CompareValue);
            break;
        case TIMER_OCC:
            OCR1CH = (u8)(u16CompareValue >> 8);
            OCR1CL = (u8)(u16CompareValue);
            break;
        default:
            break;
    }

    SREG = sreg;
}

void TIMER1_SetTimer(u16 u16TimerValue) {
    u8 sreg = SREG;

    GIE_Disable();

    TCNT1H = u16TimerValue >> 8;
    TCNT1L = u16TimerValue;

    SREG = sreg;
}

void TIMER1_EnableOverflowInterrupt(void (*callBackPtr)(void)) {
    TIMER1_SetCallBack(callBackPtr);

    /* Enable the overflow interrupt */
    SET_BIT(TIMER_u8TIMSK_REG, TOIE1);

    /* Enable global interrupt */
    GIE_Enable();
}

void TIMER1_DisableOverflowInterrupt(void) {
    u8 sreg = SREG;

    GIE_Disable();

    /* Disable the overflow interrupt */
    CLR_BIT(TIMER_u8TIMSK_REG, TOIE1);

    SREG = sreg;
}

void TIMER1_EnableCompareMatchInterrupt(TIMER_OCx_t OCx, void (*callBackPtr)(void)) {
    switch(OCx) {
        case TIMER_OCA:
            TIMER1_SetCompareCallBackA(callBackPtr);
            SET_BIT(TIMER_u8TIMSK_REG, OCIE1A);
            break;
        case TIMER_OCB:
            TIMER1_SetCompareCallBackB(callBackPtr);
            SET_BIT(TIMER_u8TIMSK_REG, OCIE1B);
            break;
        case TIMER_OCC:
            TIMER1_SetCompareCallBackC(callBackPtr);
            SET_BIT(TIMER_u8ETIMSK_REG, OCIE1C);
            break;
        default:
            break;
    }    

    /* Enable global interrupt */
    GIE_Enable();
}

void TIMER1_DisableCompareMatchInterrupt(TIMER_OCx_t OCx) {
    u8 sreg = SREG;

    GIE_Disable();

    switch(OCx) {
        case TIMER_OCA:
            CLR_BIT(TIMER_u8TIMSK_REG, OCIE1A);
            break;
        case TIMER_OCB:
            CLR_BIT(TIMER_u8TIMSK_REG, OCIE1B);
            break;
        case TIMER_OCC:
            CLR_BIT(TIMER_u8ETIMSK_REG, OCIE1C);
            break;
        default:
            break;
    }

    SREG = sreg;
}

void TIMER1_EnableCaptureInterrupt(void (*callBackPtr)(void)) {
    TIMER1_SetCaptureCallBack(callBackPtr);

    /* Enable the capture interrupt */
    SET_BIT(TIMER_u8TIMSK_REG, TICIE1);

    /* Enable global interrupt */
    GIE_Enable();
}

void TIMER1_DisableCaptureInterrupt(void) {
    u8 sreg = SREG;

    GIE_Disable();

    /* Disable the capture interrupt */
    CLR_BIT(TIMER_u8TIMSK_REG, TICIE1);

    SREG = sreg;
}

u16 TIMER1_GetTimerValue(void) {
    u16 u16TimerValue = 0;
    u8 sreg = 0;

    sreg = SREG;
    GIE_Disable();

    /* Lower register must be read first */
    u16TimerValue = (u16)TCNT1L;
    u16TimerValue |= (u16)(TCNT1H << 8);

    SREG = sreg;

    return (u16TimerValue);
}

/*---------------------------------------------------------------------------*/
/*                              PWM FUNCTIONS                                */
/*---------------------------------------------------------------------------*/

void PWM_Init(PWM_t channel, u32 frequency) {
    TIMER_CLOCK_t clock;
    u16 prescaler = 0;
    
    prescaler = F_CPU / ((u32)256 * frequency);

    if(prescaler / 1024) {
        clock = F_CPU_1024;
    }else if(prescaler / 256) {
        clock = F_CPU_256;
    }else if(prescaler / 64) {
        clock = F_CPU_64;
    }else if(prescaler / 8) {
        clock = F_CPU_8;
    }else{
        clock = F_CPU_CLOCK;
    }

    switch(channel) {
        case PWM_0:
            TIMER0_Init(0, clock, TIMER_MODE_FAST_PWM, CLEAR_OC);
            break;
        case PWM_1:
            TIMER1_Init(0, clock, TIMER_MODE_FAST_PWM_8, CLEAR_OC, TIMER_OCA);
            break;
        case PWM_2:
            TIMER1_Init(0, clock, TIMER_MODE_FAST_PWM_8, CLEAR_OC, TIMER_OCB);
            break;
        case PWM_3:
            TIMER1_Init(0, clock, TIMER_MODE_FAST_PWM_8, CLEAR_OC, TIMER_OCC);
            break;
        /* TODO: implement cases for Timer 2 and 3  */
        default:
            /* DEBUG    */
            break;
    }
}

void PWM_Write(PWM_t channel, u8 dutyPercentage) {
    u16 ocr = 0;

    ocr = (dutyPercentage * (u16) 255) / 100;   /* 255 as working on 8 bits PWM */

    switch(channel) {
        case PWM_0:
            TIMER0_SetCompareValue(ocr);
            break;
        case PWM_1:
            TIMER1_SetCompareValue(ocr, TIMER_OCA);
            break;
        case PWM_2:
            TIMER1_SetCompareValue(ocr, TIMER_OCB);
            break;
        case PWM_3:
            TIMER1_SetCompareValue(ocr, TIMER_OCC);
            break;
        /* TODO: implement cases for Timer 2 and 3  */
        default:
            /* DEBUG    */
            break;
    }
}

/*---------------------------------------------------------------------------*/
/*                              ISR FUNCTIONS                                */
/*---------------------------------------------------------------------------*/

/* ISR of TIMER0 Overflow */
void __vector_16(void) __attribute__((signal));
void __vector_16(void) {
    GIE_Disable();

    TIMER0_OVF_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8TIFR_REG, TOV0);

    GIE_Enable();
}

/* ISR of TIMER0 Compare Match */
void __vector_15(void) __attribute__((signal));
void __vector_15(void) {
    GIE_Disable();

    TIMER0_COMP_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8TIFR_REG, OCF0);

    GIE_Enable();
}

/* ISR of TIMER1 Overflow */
void __vector_14(void) __attribute__((signal));
void __vector_14(void) {
    GIE_Disable();

    TIMER1_OVF_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8TIFR_REG, TOV1);

    GIE_Enable();
}

/* ISR of TIMER1 Compare Match B */
void __vector_13(void) __attribute__((signal));
void __vector_13(void) {
    GIE_Disable();

    TIMER1_COMPB_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8TIFR_REG, OCF1B);

    GIE_Enable();
}

/* ISR of TIMER1 Compare Match A */
void __vector_12(void) __attribute__((signal));
void __vector_12(void) {
    GIE_Disable();

    TIMER1_COMPA_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8TIFR_REG, OCF1A);

    GIE_Enable();
}

/* ISR of TIMER1 Compare Match C */
void __vector_24(void) __attribute__((signal));
void __vector_24(void) {
    GIE_Disable();

    TIMER1_COMPC_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8ETIFR_REG, OCF1C);

    GIE_Enable();
}

/* ISR of TIMER1 Capture Event */
void __vector_11(void) __attribute__((signal));
void __vector_11(void) {
    GIE_Disable();

    TIMER1_CAPT_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8TIFR_REG, ICF1);

    GIE_Enable();
}

/* ISR of TIMER2 Overflow */
void __vector_10(void) __attribute__((signal));
void __vector_10(void) {
    GIE_Disable();

    TIMER2_OVF_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8TIFR_REG, TOV2);

    GIE_Enable();
}

/* ISR of TIMER2 Compare Match */
void __vector_9(void) __attribute__((signal));
void __vector_9(void) {
    GIE_Disable();

    TIMER2_COMP_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8TIFR_REG, OCF2);

    GIE_Enable();
}

/* ISR of TIMER3 Overflow */
void __vector_29(void) __attribute__((signal));
void __vector_29(void) {
    GIE_Disable();

    TIMER3_OVF_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8ETIFR_REG, TOV3);

    GIE_Enable();
}

/* ISR of TIMER3 Compare Match C */
void __vector_28(void) __attribute__((signal));
void __vector_28(void) {
    GIE_Disable();

    TIMER3_COMPC_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8ETIFR_REG, OCF3C);

    GIE_Enable();
}

/* ISR of TIMER3 Compare Match B */
void __vector_27(void) __attribute__((signal));
void __vector_27(void) {
    GIE_Disable();

    TIMER3_COMPB_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8ETIFR_REG, OCF3B);

    GIE_Enable();
}

/* ISR of TIMER3 Compare Match A */
void __vector_26(void) __attribute__((signal));
void __vector_26(void) {
    GIE_Disable();

    TIMER3_COMPA_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8ETIFR_REG, OCF3A);

    GIE_Enable();
}

/* ISR of TIMER3 Capture Event */
void __vector_25(void) __attribute__((signal));
void __vector_25(void) {
    GIE_Disable();

    TIMER3_CAPT_CBK_PTR();

    /* Clear the interrupt flag */
    SET_BIT(TIMER_u8ETIFR_REG, ICF3);

    GIE_Enable();
}
