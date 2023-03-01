#include "../../00- Common/Bit_Math.h"
#include "TMR0.h"

#define NUM_OF_OVERFLOWS_5SEC			  153
#define NUM_OF_BLINK_OVERFLOWS_200ms      16

EN_TMR0Mode_t TMR0_init(EN_TMR0Mode_t mode)
{
    switch(mode)
    {
        case NORMAL_MODE:
            CLR_BIT(TCCR0, WGM00);
            CLR_BIT(TCCR0, WGM01);
        break;

        case CTC_MODE:
            CLR_BIT(TCCR0, WGM00);
            SET_BIT(TCCR0, WGM01);
        break;

        case PWM_PHASE_CORRECT:
            SET_BIT(TCCR0, WGM00);
            CLR_BIT(TCCR0, WGM01);
        break;

        case FAST_PWM:
            SET_BIT(TCCR0, WGM00);
            SET_BIT(TCCR0, WGM01);
        break;

        default:
            return ERROR;
        break;
    }
}

EN_TMR0Mode_t TMR0_delay(uint8_t preScaler)
{
	uint8_t overflowCount = 0;
	TCCR0 &= 0xF8;
	TCCR0 |= preScaler;
	
	while(overflowCount < NUM_OF_OVERFLOWS_5SEC)
	{
		while(GET_BIT(TIFR, TOV0) == 0);
		SET_BIT(TIFR, TOV0);
		overflowCount++;
	}
}

// void TMR0_delay(uint32_t timeDelay, uint8_t preScaler)
// {
// 	uint32_t timeTick = 0, timeMaxDelay = 0, numOfOverFlows = 0;
// 	uint32_t timerInitVal = 0, overFlowCounter = 0;
// 	
// 	switch(preScaler)
// 	{
// 		case TMR0_CPU_CLK:
// 			timeTick = 1/8000000;
// 			timeMaxDelay = timeTick * 256;
// 			
// 			if(timeDelay < timeMaxDelay)
// 			{
// 				timerInitVal = (uint8_t)(((timeMaxDelay - timeDelay) / timeTick )+ 1);
// 				TMR0_loadTCNT0(timerInitVal);
// 				while(GET_BIT(TIFR, TOV0) == 0);
// 				SET_BIT(TIFR, TOV0);
// 			}
// 			else if(timeDelay == timeMaxDelay)
// 			{
// 				TMR0_loadTCNT0(0);
// 				while(GET_BIT(TIFR, TOV0) == 0);
// 				SET_BIT(TIFR, TOV0);
// 				/*TMR0_start(preScaler);*/
// 			}
// 			else if(timeDelay > timeMaxDelay)
// 			{
// 				numOfOverFlows = (uint32_t)((timeDelay / timeMaxDelay) + 1);
// 				timerInitVal = (uint8_t)((256 - ((timeDelay / timeTick) / numOfOverFlows)) + 1 );
// 				TMR0_loadTCNT0(timerInitVal);
// 				/*TMR0_start(preScaler);*/
// 				while(overFlowCounter < numOfOverFlows)
// 				{
// 					while(GET_BIT(TIFR, TOV0) == 0);
// 					SET_BIT(TIFR, TOV0);
// 					overFlowCounter++;
// 				}
// 			}
// 			else
// 			{
// 				//Do_Nothing
// 			}
// 		break;
// 		
// 		case TMR0_PRESCALER_8:
// 		timeTick = 8/8000000;
// 		timeMaxDelay = timeTick * 256;
// 		
// 		if(timeDelay < timeMaxDelay)
// 		{
// 			timerInitVal = (uint8_t)(((timeMaxDelay - timeDelay) / timeTick )+ 1);
// 			TMR0_loadTCNT0(timerInitVal);
// 			while(GET_BIT(TIFR, TOV0) == 0);
// 			SET_BIT(TIFR, TOV0);
// 		}
// 		else if(timeDelay == timeMaxDelay)
// 		{
// 			TMR0_loadTCNT0(0);
// 			while(GET_BIT(TIFR, TOV0) == 0);
// 			SET_BIT(TIFR, TOV0);
// 			/*TMR0_start(preScaler);*/
// 		}
// 		else if(timeDelay > timeMaxDelay)
// 		{
// 			numOfOverFlows = (uint32_t)((timeDelay / timeMaxDelay) + 1);
// 			timerInitVal = (uint8_t)((256 - ((timeDelay / timeTick) / numOfOverFlows)) + 1 );
// 			TMR0_loadTCNT0(timerInitVal);
// 			/*TMR0_start(preScaler);*/
// 			while(overFlowCounter < numOfOverFlows)
// 			{
// 				while(GET_BIT(TIFR, TOV0) == 0);
// 				SET_BIT(TIFR, TOV0);
// 				overFlowCounter++;
// 			}
// 		}
// 		else
// 		{
// 			//Do_Nothing
// 		}
// 		break;
// 
// 		case TMR0_PRESCALER_64:
// 		timeTick = 64/8000000;
// 		timeMaxDelay = timeTick * 256;
// 		
// 		if(timeDelay < timeMaxDelay)
// 		{
// 			timerInitVal = (uint8_t)(((timeMaxDelay - timeDelay) / timeTick )+ 1);
// 			TMR0_loadTCNT0(timerInitVal);
// 			while(GET_BIT(TIFR, TOV0) == 0);
// 			SET_BIT(TIFR, TOV0);
// 		}
// 		else if(timeDelay == timeMaxDelay)
// 		{
// 			TMR0_loadTCNT0(0);
// 			while(GET_BIT(TIFR, TOV0) == 0);
// 			SET_BIT(TIFR, TOV0);
// 			/*TMR0_start(preScaler);*/
// 		}
// 		else if(timeDelay > timeMaxDelay)
// 		{
// 			numOfOverFlows = (uint32_t)((timeDelay / timeMaxDelay) + 1);
// 			timerInitVal = (uint8_t)((256 - ((timeDelay / timeTick) / numOfOverFlows)) + 1 );
// 			TMR0_loadTCNT0(timerInitVal);
// 			/*TMR0_start(preScaler);*/
// 			while(overFlowCounter < numOfOverFlows)
// 			{
// 				while(GET_BIT(TIFR, TOV0) == 0);
// 				SET_BIT(TIFR, TOV0);
// 				overFlowCounter++;
// 			}
// 		}
// 		else
// 		{
// 			//Do_Nothing
// 		}
// 		break;
// 		
// 		case TMR0_PRESCALER_256:
// 		timeTick = 256/8000000;
// 		timeMaxDelay = timeTick * 256;
// 		
// 		if(timeDelay < timeMaxDelay)
// 		{
// 			timerInitVal = (uint8_t)(((timeMaxDelay - timeDelay) / timeTick )+ 1);
// 			TMR0_loadTCNT0(timerInitVal);
// 			while(GET_BIT(TIFR, TOV0) == 0);
// 			SET_BIT(TIFR, TOV0);
// 		}
// 		else if(timeDelay == timeMaxDelay)
// 		{
// 			TMR0_loadTCNT0(0);
// 			while(GET_BIT(TIFR, TOV0) == 0);
// 			SET_BIT(TIFR, TOV0);
// 			/*TMR0_start(preScaler);*/
// 		}
// 		else if(timeDelay > timeMaxDelay)
// 		{
// 			numOfOverFlows = (uint32_t)((timeDelay / timeMaxDelay) + 1);
// 			timerInitVal = (uint8_t)((256 - ((timeDelay / timeTick) / numOfOverFlows)) + 1 );
// 			TMR0_loadTCNT0(timerInitVal);
// 			/*TMR0_start(preScaler);*/
// 			while(overFlowCounter < numOfOverFlows)
// 			{
// 				while(GET_BIT(TIFR, TOV0) == 0);
// 				SET_BIT(TIFR, TOV0);
// 				overFlowCounter++;
// 			}
// 		}
// 		else
// 		{
// 			//Do_Nothing
// 		}
// 		break;
// 		
// 		case TMR0_PRESCALER_1024:
// 			timeTick = 1024/8000000;
// 			timeMaxDelay = timeTick * 256;
// 			
// 			if(timeDelay < timeMaxDelay)
// 			{
// 				timerInitVal = (uint8_t)(((timeMaxDelay - timeDelay) / timeTick )+ 1);
// 				TMR0_loadTCNT0(timerInitVal);
// 				while(GET_BIT(TIFR, TOV0) == 0);
// 				SET_BIT(TIFR, TOV0);
// 			}
// 			else if(timeDelay == timeMaxDelay)
// 			{
// 				TMR0_loadTCNT0(0);
// 				while(GET_BIT(TIFR, TOV0) == 0);
// 				SET_BIT(TIFR, TOV0);
// 				/*TMR0_start(preScaler);*/
// 			}
// 			else if(timeDelay > timeMaxDelay)
// 			{
// 				numOfOverFlows = (uint32_t)((timeDelay / timeMaxDelay) + 1);
// 				timerInitVal = (uint8_t)((256 - ((timeDelay / timeTick) / numOfOverFlows)) + 1 );
// 				TMR0_loadTCNT0(timerInitVal);
// 				/*TMR0_start(preScaler);*/
// 				while(overFlowCounter < numOfOverFlows)
// 				{
// 					while(GET_BIT(TIFR, TOV0) == 0);
// 					SET_BIT(TIFR, TOV0);
// 					overFlowCounter++;
// 				}
// 			}
// 			else
// 			{
// 				//Do_Nothing
// 			}
// 		break;
// 		default:
// 		break;
// 	}
// 	/*TMR0_start(preScaler);*/
// }

EN_TMR0Mode_t TMR0_start(uint8_t preScaler)
{
	TCCR0 &= 0xF8;
	TCCR0 |= preScaler;
}

EN_TMR0Mode_t TMR0_blink(uint8_t preScaler)
{
	uint8_t overflowBlinkCount = 0;
	TCCR0 &= 0xF8;
	TCCR0 |= preScaler;
	
	while(overflowBlinkCount < NUM_OF_BLINK_OVERFLOWS_200ms)
	{
		while(GET_BIT(TIFR, TOV0) == 0);
		SET_BIT(TIFR, TOV0);
		overflowBlinkCount++;
	}
}

void TMR0_loadTCNT0(uint8_t value)
{
    TCNT0 = value;
}

uint8_t TMR0_getTCNT0(void)
{
	return TCNT0;
}

EN_TMR0Mode_t TMR0_stop(void)
{
    TCCR0 &= 0xF8;
}