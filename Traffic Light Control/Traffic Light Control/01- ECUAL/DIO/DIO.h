#ifndef _ECAUL_DIO_H_
#define _ECAUL_DIO_H_

typedef unsigned char uint8_t;

//Configuration of DDRx
#define DDRA    *((volatile uint8_t*)0x3A)
#define DDRB    *((volatile uint8_t*)0x37)
#define DDRC    *((volatile uint8_t*)0x34)
#define DDRD    *((volatile uint8_t*)0x31)

//Configuration of PORTx
#define PORTA   *((volatile uint8_t*)0x3B)
#define PORTB   *((volatile uint8_t*)0x38)
#define PORTC   *((volatile uint8_t*)0x35)
#define PORTD   *((volatile uint8_t*)0x32)

//Configuration of PINx
#define PINA    *((volatile uint8_t*)0x39)
#define PINB    *((volatile uint8_t*)0x36)
#define PINC    *((volatile uint8_t*)0x33)
#define PIND    *((volatile uint8_t*)0x30)

//Selection for Ports
typedef enum EN_GPIOx_t
{
    GPIOA = 0,
    GPIOB,
    GPIOC,
    GPIOD
}EN_GPIOx_t;

//Selection for Pin used
typedef enum EN_PINx_t
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}EN_PINx_t;

//Selection for Pin Direction
typedef enum EN_pinMode_t
{
    INPUT = 0,
    OUTPUT
}EN_pinMode_t;

//Selection for Pin State
typedef enum EN_pinState_t
{
    LOW = 0,
    HIGH
}EN_pinState_t;

typedef enum EN_dioReturn_t
{
    PORT_NOT_FOUND = -4,
    PIN_NOT_FOUND,
    PIN_MODE_ERROR,
    STATE_ERROR,
    OK
}EN_dioReturn_t;

//Set Pinx Mode if it Input or Output
EN_dioReturn_t DIO_setPin(EN_PINx_t pinNum, EN_GPIOx_t portNum, EN_pinMode_t pinMode);

//Write HIGH ot LOW on Pinx
EN_dioReturn_t DIO_writePin(EN_PINx_t pinNum, EN_GPIOx_t portNum, EN_pinState_t pinState);

//Toggle Pinx
EN_dioReturn_t DIO_Toggle(EN_PINx_t pinNum, EN_GPIOx_t portNum);

//Read Pinx State
EN_pinState_t DIO_readpin(EN_PINx_t pinNum, EN_GPIOx_t portNum);
#endif