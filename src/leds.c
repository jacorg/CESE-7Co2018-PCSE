/*==================[inclusions]=============================================*/
#include "leds.h"
#include "sapi.h"
#include <stdint.h>
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void ledsOff(void)
{
	gpioWrite(LED1,OFF);
	gpioWrite(LED2,OFF);
	gpioWrite(LED3,OFF);

	gpioWrite(LEDR,OFF);
	gpioWrite(LEDG,OFF);
	gpioWrite(LEDB,OFF);
}
void ledsRgbOff(void)
{
	gpioWrite(LEDR,OFF);
	gpioWrite(LEDG,OFF);
	gpioWrite(LEDB,OFF);
}
void led1 (void)
{
	gpioWrite(LED1,ON);
	gpioWrite(LED2,OFF);
	gpioWrite(LED3,OFF);

}
void led2(void)
{
	gpioWrite(LED1,OFF);
	gpioWrite(LED2,ON);
	gpioWrite(LED3,OFF);

}
void led3 ( void)
{
	gpioWrite(LED1,OFF);
	gpioWrite(LED2,OFF);
	gpioWrite(LED3,ON);

}
void ledR ( void )
{
	gpioWrite(LEDR,ON);
	gpioWrite(LEDG,OFF);
	gpioWrite(LEDB,OFF);

}
void ledG ( void )
{
	gpioWrite(LEDR,OFF);
	gpioWrite(LEDG,ON);
	gpioWrite(LEDB,OFF);

}
void ledB ( void )
{
	gpioWrite(LEDR,OFF);
	gpioWrite(LEDG,OFF);
	gpioWrite(LEDB,ON);

}




