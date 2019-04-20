/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

#ifndef _DEBOUNCE_H_
#define _DEBOUNCE_H_

/*==================[inclusiones]============================================*/
#include <stdio.h>
#include "sapi.h"

/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[tipos de datos declarados por el usuario]===============*/

typedef enum{
   BUTTON_UP_s,
   BUTTON_DOWN_s,
   BUTTON_FALLING_s,
   BUTTON_RISING_s
}fsmButtonState_t;

typedef struct{
	fsmButtonState_t ButtonState;
	uint32_t countTick;
	gpioMap_t TEC;
	delay_t delayTEC;
}fsmButtonStateBoard_t;



/*==================[declaraciones de datos externos]========================*/
extern fsmButtonStateBoard_t fsmButtonStateTEC1;
extern fsmButtonStateBoard_t fsmButtonStateTEC2;
extern fsmButtonStateBoard_t fsmButtonStateTEC3;
extern fsmButtonStateBoard_t fsmButtonStateTEC4;

/*==================[declaraciones de funciones externas]====================*/

void fsmButtonError ( fsmButtonStateBoard_t*,gpioMap_t);
void fsmButtonInit  ( fsmButtonStateBoard_t*,gpioMap_t);
bool_t fsmButtonDelay(fsmButtonStateBoard_t*);
void fsmButtonUpdate( fsmButtonStateBoard_t*);
void buttonPressed  ( gpioMap_t);
void buttonReleased ( void );

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _DEBOUNCE_H_ */
