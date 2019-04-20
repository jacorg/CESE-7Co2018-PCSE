/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

#ifndef _LEDS_H_
#define _LEDS_H_

/*==================[inclusiones]============================================*/
#include <stdio.h>
#include "sapi.h"
#include <stdint.h>
/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/


/*==================[tipos de datos declarados por el usuario]===============*/



/*==================[declaraciones de datos externos]========================*/



/*==================[declaraciones de funciones externas]====================*/

void ledsOff(void);
void ledRgbOff(void);
void led1 (void);
void led2(void);
void led3 ( void);
void ledR ( void );
void ledG ( void );
void ledB ( void );


/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _LEDS_H_ */
