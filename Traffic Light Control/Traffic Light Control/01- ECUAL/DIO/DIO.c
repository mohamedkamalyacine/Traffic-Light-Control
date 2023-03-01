#include "../../00- Common/Bit_Math.h"
#include "DIO.h"

EN_dioReturn_t DIO_setPin(EN_PINx_t pinNum, EN_GPIOx_t portNum, EN_pinMode_t pinMode)
{
    switch(portNum)
    {
        case GPIOA:
            if(pinMode == INPUT)
            {
                CLR_BIT(DDRA, pinNum);
            }
            else if(pinMode == OUTPUT)
            {
                SET_BIT(DDRA, pinNum);
            }
            else
            {
                return PIN_MODE_ERROR;
            }
        break;

        case GPIOB:
            if(pinMode == INPUT)
            {
                CLR_BIT(DDRB, pinNum);
            }
            else if(pinMode == OUTPUT)
            {
                SET_BIT(DDRB, pinNum);
            }
            else
            {
                return PIN_MODE_ERROR;
            }
        break;

        case GPIOC:
            if(pinMode == INPUT)
            {
                CLR_BIT(DDRC, pinNum);
            }
            else if(pinMode == OUTPUT)
            {
                SET_BIT(DDRC, pinNum);
            }
            else
            {
                return PIN_MODE_ERROR;
            }
        break;

        case GPIOD:
            if(pinMode == INPUT)
            {
                CLR_BIT(DDRD, pinNum);
            }
            else if(pinMode == OUTPUT)
            {
                SET_BIT(DDRD, pinNum);
            }
            else
            {
                return PIN_MODE_ERROR;
            }
        break;

        default:
            return PORT_NOT_FOUND;
        break;
    }
}

EN_dioReturn_t DIO_writePin(EN_PINx_t pinNum, EN_GPIOx_t portNum, EN_pinState_t pinState)
{
    switch(portNum)
    {
        case GPIOA:
        if(pinState == LOW)
        {
            CLR_BIT(PORTA, pinNum);
        }
        else if(pinState == HIGH)
        {
            SET_BIT(PORTA, pinNum);
        }
        else
        {
            return STATE_ERROR;
        }
        break;

        case GPIOB:
        if(pinState == LOW)
        {
            CLR_BIT(PORTB, pinNum);
        }
        else if(pinState == HIGH)
        {
            SET_BIT(PORTB, pinNum);
        }
        else
        {
            return STATE_ERROR;
        }
        break;

        case GPIOC:
        if(pinState == LOW)
        {
            CLR_BIT(PORTC, pinNum);
        }
        else if(pinState == HIGH)
        {
            SET_BIT(PORTC, pinNum);
        }
        else
        {
            return STATE_ERROR;
        }
        break;

        case GPIOD:
        if(pinState == LOW)
        {
            CLR_BIT(PORTD, pinNum);
        }
        else if(pinState == HIGH)
        {
            SET_BIT(PORTD, pinNum);
        }
        else
        {
            return STATE_ERROR;
        }
        break;

        default:
            return PORT_NOT_FOUND;
        break;
    }
}

EN_dioReturn_t DIO_Toggle(EN_PINx_t pinNum, EN_GPIOx_t portNum)
{
    switch(portNum)
    {
        case GPIOA:
            TOG_BIT(PORTA, pinNum);
        break;

        case GPIOB:
            TOG_BIT(PORTB, pinNum);
        break;

        case GPIOC:
            TOG_BIT(PORTC, pinNum);
        break;

        case GPIOD:
            TOG_BIT(PORTD, pinNum);
        break;

        default:
            return PORT_NOT_FOUND;
        break;
    }
}

EN_pinState_t DIO_readpin(EN_PINx_t pinNum, EN_GPIOx_t portNum)
{
	EN_pinState_t pinState;
    switch(portNum)
    {
        case GPIOA:
            pinState = GET_BIT(PINA, pinNum);
        break;

        case GPIOB:
            pinState = GET_BIT(PINB, pinNum);
        break;

        case GPIOC:
            pinState = GET_BIT(PINC, pinNum);
        break;

        case GPIOD:
            pinState = GET_BIT(PIND, pinNum);
        break;

        default:
            return PORT_NOT_FOUND;
        break;
    }

    return pinState;
}