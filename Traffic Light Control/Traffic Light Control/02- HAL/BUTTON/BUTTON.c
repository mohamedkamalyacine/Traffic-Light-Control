#include "../../01- ECUAL/DIO/DIO.h"
#include "BUTTON.h"

void BUTTON_init(EN_PINx_t pinNum, EN_GPIOx_t portnum)
{
    DIO_setPin(pinNum, portnum, INPUT);
}

EN_pinState_t BUTTON_read(EN_PINx_t pinNum, EN_GPIOx_t portnum)
{
    return DIO_readpin(pinNum, portnum);
}