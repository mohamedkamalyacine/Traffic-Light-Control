#include "../../00- Common/Bit_Math.h"
#include "../../01- ECUAL/DIO/DIO.h"

EN_dioReturn_t LED_Init(EN_PINx_t pinNum, EN_GPIOx_t portNum)
{
    DIO_setPin(pinNum, portNum, OUTPUT);
}

EN_dioReturn_t LED_On(EN_PINx_t pinNum, EN_GPIOx_t portNum)
{
    DIO_writePin(pinNum, portNum, HIGH);
}

EN_dioReturn_t LED_Off(EN_PINx_t pinNum, EN_GPIOx_t portNum)
{
    DIO_writePin(pinNum, portNum, LOW);
}

EN_dioReturn_t LED_Toggle(EN_PINx_t pinNum, EN_GPIOx_t portNum)
{
    DIO_Toggle(pinNum, portNum);
}