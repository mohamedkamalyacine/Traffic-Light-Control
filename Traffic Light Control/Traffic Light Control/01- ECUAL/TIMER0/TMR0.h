#ifndef _ECUAL_TMR0_H_
#define _ECUAL_TMR0_H_

typedef unsigned char uint8_t;
typedef unsigned long uint32_t;

//Configuartion of Timer/Counter Control Register
#define TCCR0 *((volatile uint8_t*)0x53)
    #define FOC0  7
    #define WGM00 6
    #define COM01 5
    #define COM00 4
    #define WGM01 3
    #define CS02  2
    #define CS01  1
    #define CS00  0

//Timer/Counter Register
#define TCNT0 *((volatile uint8_t*)0x52)

//Configuration of TIFR Timer/Counter Interrupt Flag Register
#define TIFR *((volatile uint8_t*)0x58)
    #define OCF0 1  //Timer0 Output Compare Match Flag bit ( 0 --> no overflow / 1 --> Compare Match occured )
    #define TOV0 0  //Timer0 overflow Flag bit ( 0 --> no overflow / 1 --> Timer0 has overflowed )

#define TIMSK *((volatile uint8_t*)0x59)
    #define OCIE0 1     //Compare Match Interrupt Enable
    #define TOIE0 0     //Timer0 Interrupt Enable

#define SREG *((volatile uint8_t*)0x5F)

//Timer0 Clock Selector CS02:00
#define TMR0_STOP_CLK            0x00
#define TMR0_CPU_CLK             0x01
#define TMR0_PRESCALER_8         0x02
#define TMR0_PRESCALER_64        0x03
#define TMR0_PRESCALER_256       0x04
#define TMR0_PRESCALER_1024      0x05

typedef enum EN_TMR0Mode_t
{
    NORMAL_MODE = 0,
    CTC_MODE,
    PWM_PHASE_CORRECT,
    FAST_PWM,
    ERROR
}EN_TMR0Mode_t;

EN_TMR0Mode_t TMR0_init(EN_TMR0Mode_t mode);
EN_TMR0Mode_t TMR0_start(uint8_t preScaler);
EN_TMR0Mode_t TMR0_delay(uint8_t preScaler);
/*void TMR0_delay(uint32_t timeDelay, uint8_t prescaler);*/
EN_TMR0Mode_t TMR0_blink(uint8_t preScaler);
void TMR0_loadTCNT0(uint8_t value);
uint8_t TMR0_getTCNT0(void);
EN_TMR0Mode_t TMR0_stop(void);
#endif