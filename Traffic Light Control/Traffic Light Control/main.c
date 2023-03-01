/*
 * Traffic Light Control.c
 *
 * Created: 05-Oct-22 5:37:11 PM
 * Author : hp
 */ 

#include "00- Common/Bit_Math.h"
#include "01- ECUAL/DIO/DIO.h"
#include "01- ECUAL/TIMER0/TMR0.h"
#include "01- ECUAL/EXTI/EXTI.h"
#include "02- HAL/LED/LED.h"
#include "02- HAL/BUTTON/BUTTON.h"
#include "03- APP/APP.h"



int main(void)
{	
	APP_init();

    while (1) 
    {
		APP_start();
    }
}

