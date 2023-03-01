#include "../../00- Common/Bit_Math.h"
#include "../DIO/DIO.h"
#include "EXTI.h"

EN_dioReturn_t EXTI_init(EN_interrupt_t interruptPin, EN_senseControl_t senseControl)
{
    //1-Enable Global Interrupt bit in SREG
    SET_BIT(SREG, I);

    //2- Choose Interrupt Sense Control
    switch(interruptPin)
    {
        case PIN_INT0:
            SET_BIT(GICR, INT0);
            if(senseControl == FALLING_EDGE)
            {
                SET_BIT(MCUCR, ISC01);
                CLR_BIT(MCUCR, ISC00);
				//DIO_writePin(PIN2, GPIOD, HIGH);
            }
            else if(senseControl == RISING_EDGE)
            {
                SET_BIT(MCUCR, ISC01);
                SET_BIT(MCUCR, ISC00);                
            }
            else if(senseControl == LOW_LEVEL)
            {
                CLR_BIT(MCUCR, ISC01);
                CLR_BIT(MCUCR, ISC00);
            }
            else if(senseControl == ANY_LOGICAL_CHANGE)
            {
                SET_BIT(MCUCR, ISC00);
                CLR_BIT(MCUCR, ISC01);               
            }
            else
            {
                return ERROR_SENSE_CONTROL;
            }
        break;

        case PIN_INT1:
            SET_BIT(GICR, INT1);
            if(senseControl == FALLING_EDGE)
            {
                SET_BIT(MCUCR, ISC11);
                CLR_BIT(MCUCR, ISC10);
            }
            else if(senseControl == RISING_EDGE)
            {
                SET_BIT(MCUCR, ISC11);
                SET_BIT(MCUCR, ISC10);                
            }
            else if(senseControl == LOW_LEVEL)
            {
                CLR_BIT(MCUCR, ISC11);
                CLR_BIT(MCUCR, ISC10);
            }
            else if(senseControl == ANY_LOGICAL_CHANGE)
            {
                SET_BIT(MCUCR, ISC10);
                CLR_BIT(MCUCR, ISC11);               
            }
            else
            {
                return ERROR_SENSE_CONTROL;
            }
        break;

        case PIN_INT2:
            SET_BIT(GICR, INT2);
            if(senseControl == FALLING_EDGE)
            {
                CLR_BIT(MCUCSR, ISC2);
            }
            else if(senseControl == RISING_EDGE)
            {
                SET_BIT(MCUCSR, ISC2);
            }
            else
            {
                return ERROR_SENSE_CONTROL;
            }
        break;

        default:
        break;
    }
}