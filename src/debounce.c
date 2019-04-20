/*==================[inclusions]=============================================*/
#include "debounce.h"
#include "leds.h"
#include "sapi.h"

/*==================[macros and definitions]=================================*/

//Define time on each state
#define TIME_TEC_PUSH 40   //time on milisecond sysTick initialized at 1 ms.
#define TIME_FINISH   ON
#define TIME_RUNNING  OFF
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
typedef enum{
			init,
			adq,
	        }stateFsm_t;
/*==================[external data definition]===============================*/
extern  stateFsm_t fsmState;
/*==================[internal functions definition]==========================*/
void fsmButtonInit( fsmButtonStateBoard_t* fsmButtonState,gpioMap_t TEC)
{
	fsmButtonState->ButtonState=BUTTON_UP_s;
	fsmButtonState->countTick=0;
	fsmButtonState->TEC=TEC;
	delayInit(&(fsmButtonState->delayTEC),TIME_TEC_PUSH);

}

/*bool_t fsmButtonDelay(fsmButtonStateBoard_t* fsmButtonState)
{
	bool_t back=TIME_RUNNING;

	 if(!delayRead(&(fsmButtonState->delayTEC)))
		 back=TIME_RUNNING;
	 else{
		 delayInit(&(fsmButtonState->delayTEC),TIME_TEC_PUSH);
		 back=TIME_FINISH;
	 }
	 return back;
}
*/

void  fsmButtonError ( fsmButtonStateBoard_t* fsmButtonState,gpioMap_t TEC)
{
	fsmButtonState->ButtonState=BUTTON_UP_s;
	fsmButtonState->countTick=0;
	fsmButtonState->TEC=TEC;
	delayInit(&(fsmButtonState->delayTEC),TIME_TEC_PUSH);
}

void fsmButtonUpdate(fsmButtonStateBoard_t* fsmButtonState)
{


	switch(fsmButtonState->ButtonState)
		{
		case BUTTON_UP_s:
			if(!gpioRead(fsmButtonState->TEC))
				fsmButtonState->ButtonState=BUTTON_FALLING_s;
			break;

		case BUTTON_DOWN_s:
			if(gpioRead(fsmButtonState->TEC))
				fsmButtonState->ButtonState=BUTTON_RISING_s;
			break;

		case BUTTON_FALLING_s:
//			if(fsmButtonDelay(fsmButtonState))
			if(delayRead(&(fsmButtonState->delayTEC)))
				if(!gpioRead(fsmButtonState->TEC))
				{
					fsmButtonState->ButtonState=BUTTON_DOWN_s;
					buttonPressed(fsmButtonState->TEC);             //action TEC1
					fsmButtonState->countTick=0;
				}
				else
					fsmButtonState->ButtonState=BUTTON_UP_s;

			//fsmButtonState->countTick++;*/
			break;

		case BUTTON_RISING_s:
//			if(fsmButtonDelay(fsmButtonState))
			if(delayRead(&(fsmButtonState->delayTEC)))
				if(gpioRead(fsmButtonState->TEC))
				{
					fsmButtonState->ButtonState=BUTTON_UP_s;
					buttonReleased();
					fsmButtonState->countTick=0;
				}
				else
					fsmButtonState->ButtonState=BUTTON_DOWN_s;

			//fsmButtonState->countTick++;*/
			break;

		default:
			 fsmButtonInit(fsmButtonState,fsmButtonState->TEC);
		}

}



void buttonPressed  ( gpioMap_t key )
{


	switch(key)
	{
	case TEC1:
		//led1();
		fsmState=adq;
		break;
	case TEC2:
		led2();
		break;
	case TEC3:
		led3();
		break;
	case TEC4:
		//ledG();
		fsmState=init;
		break;
	}

}
void buttonReleased ( void )
{
	ledsOff();

}


/*==================[external functions definition]==========================*/






