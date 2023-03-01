#include "../00- Common/Bit_Math.h"
#include "../01- ECUAL/DIO/DIO.h"
#include "../01- ECUAL/TIMER0/TMR0.h"
#include "../01- ECUAL/EXTI/EXTI.h"
#include "../02- HAL/BUTTON/BUTTON.h"
#include "../02- HAL/LED/LED.h"
#include "APP.h"

// #define  F_CPU 8000000UL
// #include "util/delay.h"
uint8_t blink = 0;

uint8_t getPressedButton = 0;
/*#define  GET_PRESSED 1*/
#define  NUM_OF_OVERFLOWS_20ms	10


void APP_init(void)
{	
    //Traffic LEDs
    LED_Init(PIN0, GPIOA);
	LED_Init(PIN1, GPIOA);
	LED_Init(PIN2, GPIOA);

   //Pedestrain LEDs
    LED_Init(PIN0, GPIOB);
	LED_Init(PIN1, GPIOB);
	LED_Init(PIN2, GPIOB);

	//Initialization Button
	BUTTON_init(PIN2, GPIOD);
	
	//Initialize INT0 Pin as an input
	DIO_setPin(PIN2, GPIOD, INPUT);
	DIO_writePin(PIN2, GPIOD, HIGH);
    //INitialization of Timer0
    TMR0_init(NORMAL_MODE);

    //Load TCNT0 with initial value
    TMR0_loadTCNT0(0x00);
	TMR0_start(TMR0_PRESCALER_1024);
	
	//External Interrupt Initialization
	EXTI_init(PIN_INT0, FALLING_EDGE);
}

uint8_t blinkYellowLed(void)
{
	blink = 0;
	TMR0_loadTCNT0(0x0C);
	while(blink != 10)
	{
		LED_Toggle(PIN1, GPIOA);
		LED_Toggle(PIN1, GPIOB);
		TMR0_blink(TMR0_PRESCALER_1024);
		//LED_Toggle(PIN1, GPIOA);
		blink++;
	}
	LED_Off(PIN1, GPIOA);
	LED_Off(PIN1, GPIOB);
	blink = 0;
}

void trafficLightMode(void)
{
    LED_On(PIN2, GPIOA);	//Cars Green led
	LED_On(PIN0, GPIOB);	//pedstrain Red led
	
    TMR0_delay(TMR0_PRESCALER_1024);
	
	//Yellow Led is blinking for 5 seconds
	blinkYellowLed();
	LED_Off(PIN2, GPIOA);
 	LED_Off(PIN0, GPIOB);

	
	LED_On(PIN0, GPIOA);	//Cars Red led
	LED_On(PIN2, GPIOB);	//pedstrain green led
	TMR0_delay(TMR0_PRESCALER_1024);
	//Yellow Led is blinking for 5 seconds
	blinkYellowLed();
	LED_Off(PIN0, GPIOA);
	LED_Off(PIN2, GPIOB);
}

void APP_start(void)
{
    trafficLightMode();
}

ISR(EXTI_INT_0)
{
	getPressedButton++;
	
	uint8_t count = 0;
	while(BUTTON_read(PIN2, GPIOD) == LOW && getPressedButton <= 2)
	{
		if(count < NUM_OF_OVERFLOWS_20ms)
		{
			while(GET_BIT(TIFR, TOV0) == 0);
			SET_BIT(TIFR, TOV0);
			count++;
		}
		else
		{
			break;
		}
	}
	
	count = 0;
	while(BUTTON_read(PIN2, GPIOD) == HIGH && getPressedButton <= 2)
	{
		if(count < NUM_OF_OVERFLOWS_20ms)
		{
			while(GET_BIT(TIFR, TOV0) == 0);
			SET_BIT(TIFR, TOV0);
			count++;
		}
		else if(GET_BIT(PIN0, GPIOA) == HIGH)
		{
			getPressedButton = 0;
			break;
		}
		else
		{
			getPressedButton = 0;
			break;
		}
	}
	
	if(BUTTON_read(PIN2, GPIOD) == HIGH && getPressedButton < 2)
	{
		if((GET_BIT(PINA, PIN2) == HIGH))
		{
			//LED_On(PIN0, GPIOB);	//pedestrain red led on
			blinkYellowLed();		//blink and delay 5 sec
			LED_Off(PIN2, GPIOA);	//cars green led off
			LED_On(PIN0, GPIOA);	//cars red led on
			
			LED_Off(PIN0, GPIOB);	//pedestrain red led off
			LED_On(PIN2, GPIOB);	//pedestrain green led on
			TMR0_delay(TMR0_PRESCALER_1024);
			blinkYellowLed();
			LED_Off(PIN0, GPIOA);
			LED_Off(PIN2, GPIOB);
			// 		//returen to pervoius state before interrupt
			LED_On(PIN2, GPIOA);	//Cars Green led
			LED_On(PIN0, GPIOB);	//pedstrain Red led
		}
		else if( ( blink > 1) && (GET_BIT(PIN2, GPIOA) == 1) )
		{
			blinkYellowLed();
			LED_Off(PIN2, GPIOA);
			LED_On(PIN0, GPIOA);
			
			LED_Off(PIN0, GPIOB);
			LED_On(PIN2, GPIOB);
			TMR0_delay(TMR0_PRESCALER_1024);
		}
		else
		{
			//Do_Nothing
		}
	}
}