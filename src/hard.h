/*
 * hard.h
 *
 *  Created on: 28/11/2013
 *      Author: Mariano
 */

#ifndef HARD_H_
#define HARD_H_

#include "stm32f0xx_adc.h"

//--- Board Configuration ---------------------------------------//
//----------- Defines For Configuration -------------
//----------- Hardware Board Version -------------
//#define HARD_1_0
#define HARD_2_0

//----------- Software Version -------------
//#define SOFT_2_0			//coincide con Hard 2.0
#define SOFT_2_1				//nuevo ajuste puntas y programa 13-10-17

//-------- Type of Program ----------------
//#define RELAY_OFF_WITH_DOOR_OPEN		//apaga el relay de temp cuando se abre la puerta
										//tambien apaga el led indicador
#define RELAY_ALWAYS_ON		//apaga el relay solo por temperatura

//-------- Type of Temparature determination ----------------
//#define SIMPLE_VECTOR_TEMP
#define OPEN_LOOP

//-------- Clock Frequency ------------------------------------
// #define CLOCK_FREQ_48_MHZ
#define CLOCK_FREQ_8_MHZ


//-------- Hardware and Soft resources for Type of Program ----------------
#ifdef SOFT_2_1
#define LARGO_FILTRO_POTE 16
#define DIVISOR_POTE      4  		//2 elevado al divisor = largo filtro
#define UPDATE_FILTRO_POTE 10		//total de 160ms

#define LARGO_FILTRO_TEMP 32
#define DIVISOR_TEMP      5   //2 elevado al divisor = largo filtro
//#define UPDATE_FILTRO_TEMP 312		//total de 10 segundos
#define UPDATE_FILTRO_TEMP 32		//total de 1 segundos
#endif


#ifdef SIMPLE_VECTOR_TEMP
#define USE_SUBSCRIBE
#endif

#ifdef SETPOINT_PLUS_HYST
#define USE_DMX
#endif

#ifdef OPEN_LOOP
//#define USE_DMX
#endif


//--- End Board Configuration -----------------------------------//


//para GPIO 1 solo bit uso Port bit set/reset register (GPIOx_BSRR) (x=A..G)
//GPIOA pin1
//#define DOOR ((GPIOA->IDR & 0x0002) == 0)
#define DOOR ((GPIOA->IDR & 0x0002) != 0)

//GPIOA pin2
#define LIGHT ((GPIOA->ODR & 0x0004) != 0)
#define LIGHT_ON GPIOA->BSRR = 0x00000004
#define LIGHT_OFF GPIOA->BSRR = 0x00040000

//GPIOA pin3
#define RELAY ((GPIOA->ODR & 0x0008) != 0)
#define RELAY_ON GPIOA->BSRR = 0x00000008
#define RELAY_OFF GPIOA->BSRR = 0x00080000

//GPIOA pin4
#define LED ((GPIOA->ODR & 0x0010) != 0)
#define LED_ON	GPIOA->BSRR = 0x00000010
#define LED_OFF GPIOA->BSRR = 0x00100000

//GPIOA pin5
//GPIOA pin6
//GPIOA pin7

#ifdef HARD_2_0
#define SYNC		((GPIOA->ODR & 0x0080) != 0)
#define SYNC_ON		GPIOA->BSRR = 0x00000080
#define SYNC_OFF	GPIOA->BSRR = 0x00800000

//GPIOA pin9

//GPIOA pin10
#define EDGE_PIN ((GPIOA->IDR & 0x0400) != 0)
#endif

#define CH_IN_POTE ADC_Channel_5
#define CH_IN_TEMP ADC_Channel_0

#define DOOR_ROOF	200
#define DOOR_THRESH	180


//ESTADOS DEL PROGRAMA PRINCIPAL
#define NORMAL	0
#define GO_TO_STOP	1
#define STOPPED	2
#define TO_NEVER	3
#define NEVER	4
#define TO_ALWAYS	5
#define ALWAYS	6

//ESTADOS DEL LED
#define START_BLINKING	0
#define WAIT_TO_OFF	1
#define WAIT_TO_ON	2
#define WAIT_NEW_CYCLE	3

//--- Temas con el sync de relay
#define TT_DELAYED_OFF		5600
#define TT_DELAYED_ON		6560
#define TT_RELAY			60		//timeout de espera antes de pegar o despegar el relay
#define TT_MINUTES_DAY_ON	1415
#define TT_MINUTES_DAY_OFF	25

enum Relay_State {

	ST_OFF = 0,
	ST_WAIT_ON,
	ST_DELAYED_ON,
	ST_ON,
	ST_WAIT_OFF,
	ST_DELAYED_OFF

};

typedef enum Parts {

	ZERO_BIPS = 0,
	ONE_BIP,	//1
	TWO_BIPS,	//2
	THREE_BIPS,	//3
	FOUR_BIPS,	//4
	FIVE_BIPS,	//5
	SIX_BIPS	//6
} pote_range_t;

//TEMPERATURAS DE UN NTC TT103 COLOCADO EN EL INTERIOR DE LA HELADERA
//AL LADO DEL TAPON SOBRE EL FONDO
#define TEMP_12 		1063		//0.856
#define TEMP_10 		1118		//0.9V en NTC interno heladera
#define TEMP_08 		1209		//0.975
#define TEMP_06 		1311		//1.05	medidos posta
#define TEMP_04 		1389		//1.12	calculado
#define TEMP_02 		1489		//1.2		calculado


/* Module Functions ------------------------------------------------------------*/
void RelayOn (void);
void RelayOff (void);
void UpdateRelay (void);
unsigned char RelayIsOn (void);
unsigned char RelayIsOff (void);
void ResetLed (void);
void UpdateLed (unsigned char);


#endif /* HARD_H_ */
