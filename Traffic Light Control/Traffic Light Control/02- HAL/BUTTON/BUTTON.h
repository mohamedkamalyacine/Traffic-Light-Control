#ifndef _HAL_BUTTON_H_
#define _HAL_BUTTON_H_

#include "../../01- ECUAL/DIO/DIO.h"

void BUTTON_init(EN_PINx_t pinNum, EN_GPIOx_t portnum);
EN_pinState_t BUTTON_read(EN_PINx_t pinNum, EN_GPIOx_t portnum);

#endif