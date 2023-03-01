#ifndef _HAL_LED_H_
#define _HAL_LED_H_

#include "../../01- ECUAL/DIO/DIO.h"

//Initialization for LED
EN_dioReturn_t LED_Init(EN_PINx_t pinNum, EN_GPIOx_t portNum);

//Write High on the connected Pin for LED
EN_dioReturn_t LED_On(EN_PINx_t pinNum, EN_GPIOx_t portNum);

//Write Low on the connected Pin for LED
EN_dioReturn_t LED_Off(EN_PINx_t pinNum, EN_GPIOx_t portNum);

//Toggle the connected Pin for LED
EN_dioReturn_t LED_Toggle(EN_PINx_t pinNum, EN_GPIOx_t portNum);

#endif