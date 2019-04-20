/* Copyright 2016, Alejandro Permingeat.
 * Copyright 2016, Eric Pernia.
 * Copyright 2018, Sergio Renato De Jesus Melean <sergiordj@gmail.com>.
 *
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Date: 2018-07-06 */

/*==================[inclusions]=============================================*/
#include  "sapi.h"               // <= sAPI header
#include  "ciaaI2C.h"
#include  "ds3231.h"
#include  "string.h"
#include "../../sd_card/inc/sd_spi.h"   // <= own header (optional)
#include "ff.h"                         // <= Biblioteca FAT FS
#include "fssdc.h"                     // API de bajo nivel para unidad "SDC:" en FAT FS
#include "conversions.h"
#include "leds.h"
#include  "debounce.h"
/*==================[macros and definitions]=================================*/
//#define bytes_to_u16(MSB,LSB) (((uint16_t) ((uint8_t) MSB)) & 255)<<8 | (((uint8_t) LSB)&255)


#define FILENAME "SDC:/hola.txt"
static FATFS fs;           // <-- FatFs work area needed for each volume
static FIL fp;             // <-- File object needed for each open file
/*==================[internal data declaration]==============================*/
//Key status
typedef enum{
			init,
			adq,
	        }stateFsm_t;

 stateFsm_t fsmState=init;


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/


void diskTickHook( void *ptr );

/*==================[external functions definition]==========================*/
void diskTickHook( void *ptr ){
   disk_timerproc();   // Disk timer process
}

fsmButtonStateBoard_t fsmButtonStateTEC1;
fsmButtonStateBoard_t fsmButtonStateTEC2;
fsmButtonStateBoard_t fsmButtonStateTEC3;
fsmButtonStateBoard_t fsmButtonStateTEC4;
/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){
   /* ------------- INICIALIZACIONES ------------- */




   /*Board Config*/
   boardConfig();

   fsmState=init;
   fsmButtonInit(&fsmButtonStateTEC1,TEC1);
   fsmButtonInit(&fsmButtonStateTEC2,TEC2);
   fsmButtonInit(&fsmButtonStateTEC3,TEC3);
   fsmButtonInit(&fsmButtonStateTEC4,TEC4);


   /* Inicializar UART_USB a 115200 baudios */
   uartConfig( UART_USB, 115200 );

   // using I2C for communication
   // starting the I2C bus
   ciaaI2CInit();


   // SPI configuration
   spiConfig( SPI0 );
   // Inicializar el conteo de Ticks con resolucion de 10ms,
   // con tickHook diskTickHook
   tickConfig( 1 );
   tickCallbackSet( diskTickHook, NULL );


   // ------ PROGRAMA QUE ESCRIBE EN LA SD -------
   UINT nbytes;
   // Initialize SD card driver
   FSSDC_InitSPI ();
   // Give a work area to the default drive
   if( f_mount( &fs, "SDC:", 0 ) != FR_OK ) {
   // If this fails, it means that the function could
   // not register a file system object.
   // Check whether the SD card is correctly connected
    }


   uint8_t msj[40];   //msj to save the filename
   uint8_t dato;


   uint16_t pp=5555;
   uint8_t uartBuff[10];


   delay_t delayLedInit;
   delay_t delayLedStop;
   tm Current_time;

   uint16_t i=0;

   //delayConfig( &delayTec, 40 );
   delayInit( &delayLedInit, 200 );
   delayInit( &delayLedStop, 1000 );

/*   f_open( &fp, FILENAME, FA_WRITE | FA_OPEN_APPEND );
   	    	 for(i=0;i<1000;i++){
   	    		itoa(i, uartBuff, 10);
   	    		strcat (uartBuff, "\r\n");
   	    	 f_write( &fp,uartBuff,strlen(uartBuff), &nbytes );
  // 	    	 delay(20);
   	    	 gpioToggle(LED2);}
   f_close(&fp);
*/

   printf("Entrando a modo Init. Presione TEC1 para iniciar. \r\n");
   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(TRUE){
	   fsmButtonUpdate(&fsmButtonStateTEC1);
	   fsmButtonUpdate(&fsmButtonStateTEC2);
	   fsmButtonUpdate(&fsmButtonStateTEC3);
	   fsmButtonUpdate(&fsmButtonStateTEC4);

	   switch(fsmState){
	      case init:
	    	 if(delayRead(&delayLedInit))
	    	   gpioToggle(LED1);
	      break;

	      case adq:
	    	  /* Si recibe un byte de la UART_USB lo guardarlo en la variable dato. */
	    	   if(  uartReadByte( UART_USB, &dato )){
	    		   printf("recibiendo byte n:%d\r\n",i);
	    	       /* Se reenvíael dato a la UART_USB realizando un eco de lo que llega */
	    		   //uartWriteByte( UART_USB, dato);

	    		   if(i<2048 && i>0){
	    		  	 if( f_open( &fp, msj, FA_WRITE | FA_OPEN_APPEND ) == FR_OK ){
//	   		    	 itoa(pp, uartBuff, 10);
	    		     uartBuff[0]=dato;
	    		     uartBuff[1]='\0';
	    		     strcat (uartBuff, "\r\n");
	    		  	 f_write( &fp,uartBuff,strlen(uartBuff), &nbytes );
	    		     f_close(&fp);

	    		     if( nbytes == strlen(uartBuff) ){
	    		  	 // Turn ON LEDG if the write operation was successful
	    		  	  gpioToggle(LEDB);
	    		  	  }
	    		     else
	    		    	 gpioWrite(LEDR,ON);
	    		  	 }
	    		  	  i++;
	    		   }

	    		   else if(i==0){
	    		   //Get hour and print it
	    		   	  if (ds3231_getTime(&Current_time)){
	    		   	  nameFile(msj, &Current_time);
	    		   	  printf("archivo a guardar en microSD %s \r\n",msj);


	    		   	  if( f_open( &fp, msj, FA_WRITE | FA_OPEN_APPEND ) == FR_OK ){
 //       		   	  itoa(pp, uartBuff, 10);
	    		   	uartBuff[0]=dato;
	    		   	  uartBuff[1]='\0';
	    		   	  strcat (uartBuff, "\r\n");
	    		   	  f_write( &fp,uartBuff,strlen(uartBuff), &nbytes );
	    		   	  f_close(&fp);

	    		      if( nbytes == strlen(uartBuff) ){
	    		   	  // Turn ON LEDG if the write operation was successful
	    		   	  gpioToggle(LEDB);
	    		   	  }
	    		      else
	    		        gpioWrite(LEDR,ON);
	    		   	  }
	    		   	  i++;
	    		   	  }
	    		   }
	    		   else
	    	 	       i=0;


	    	   }
	    	   if(delayRead(&delayLedStop))
	    	     gpioToggle(LED3);
	      break;
	    }

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
