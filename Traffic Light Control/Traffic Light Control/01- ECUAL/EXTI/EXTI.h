#ifndef _ECUAL_EXTI_H_
#define _ECUAL_EXTI_H_

#include "../DIO/DIO.h"

typedef unsigned char uint8_t;

#define SREG *((volatile uint8_t*)0x5F)
    #define I 7

//Configuration of GICR
#define GICR *((volatile uint8_t*)0x5B)
    #define INT1 7
    #define INT0 6
    #define INT2 5

//Cofiguration of GIFR
#define GIFR *((volatile uint8_t*)0x5A)
    #define INTF1 7
    #define INTF0 6
    #define INTF2 5

//Configuration of MCUCR and Interrupt Sense Control Bits
#define MCUCR *((volatile uint8_t*)0x55)
    #define ISC11 3
    #define ISC10 2
    #define ISC01 1
    #define ISC00 0

//Configuration of MCUCSR Interrupt Sense Control for INT2
#define MCUCSR *((volatile uint8_t*)0x54)
    #define ISC2 6

//Macros for External Interrupts
#define EXTI_INT_0 __vector_1
#define EXTI_INT_1 __vector_2
#define EXTI_INT_2 __vector_3

typedef enum EN_interrupt_t
{
    PIN_INT0 = 0,
    PIN_INT1,
    PIN_INT2
}EN_interrupt_t;

typedef enum EN_senseControl_t
{
    FALLING_EDGE = 0,
    RISING_EDGE,
    LOW_LEVEL,
    ANY_LOGICAL_CHANGE,
    ERROR_SENSE_CONTROL
}EN_senseControl_t;

EN_dioReturn_t EXTI_init(EN_interrupt_t interruptPin, EN_senseControl_t senseControl);

#define ISR(INT_VECT)void INT_VECT(void) __attribute__ ((signal, used));\
void INT_VECT(void)

#endif