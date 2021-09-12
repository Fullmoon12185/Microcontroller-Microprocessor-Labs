/*
 * led_display.c
 *
 *  Created on: Sep 12, 2021
 *      Author: Nguyet
 */

#include "main.h"
#include "led_display.h"

#define NUMBER_OF_DECIMAL_DIGITS			10
#define	NUMBER_OF_SEVEN_SEGMENT_LEDS		1


//common Anode
static uint8_t sevenSegmentLEDConversion[NUMBER_OF_DECIMAL_DIGITS] = {0x3f, 0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

//common Cathode
//uint8_t sevenSegmentLEDConversion[NUMBER_OF_DECIMAL_DIGITS] = {};

static uint8_t sevenSegmentLEDBuffer[NUMBER_OF_SEVEN_SEGMENT_LEDS];

uint8_t update_seven_segment_led_buffer(uint8_t val, uint8_t idx){
	if(idx >= NUMBER_OF_SEVEN_SEGMENT_LEDS) return 0;
	if(val > NUMBER_OF_DECIMAL_DIGITS) return 0;
	sevenSegmentLEDBuffer[idx] = val;
	return 1;
}


void seven_segment_led_driver(void){
	uint8_t temp = sevenSegmentLEDConversion[sevenSegmentLEDBuffer[0]];
	//if sevenSegmentLEDBuffer[0] = 0; what the value of temp? = sevenSegmentLEDConversion[0]
	//temp = 0x3f 0b00111111
	if(temp & 0x01){ //what is the value of temp & 0x01 = 0x01 --> TRUE
		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_A_PORT, SEVEN_SEGMENT_1_A, SET);
	} else{
		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_A_PORT, SEVEN_SEGMENT_1_A, RESET);
	}

	if(temp & 0x02){
		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_B_PORT, SEVEN_SEGMENT_1_B, SET);
	} else{
		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_B_PORT, SEVEN_SEGMENT_1_B, RESET);
	}

	if(temp & 0x04){
		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_C_PORT, SEVEN_SEGMENT_1_C, SET);
	} else{
		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_C_PORT, SEVEN_SEGMENT_1_C, RESET);
	}

	if(temp & 0x08){
		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_D_PORT, SEVEN_SEGMENT_1_D, SET);
	} else{
		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_D_PORT, SEVEN_SEGMENT_1_D, RESET);
	}

//	if(temp & 0x10){
//		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_E_PORT, SEVEN_SEGMENT_1_E, SET);
//	} else{
//		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_E_PORT, SEVEN_SEGMENT_1_E, RESET);
//	}
//
//	if(temp & 0x20){
//		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_F_PORT, SEVEN_SEGMENT_1_F, SET);
//	} else{
//		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_F_PORT, SEVEN_SEGMENT_1_F, RESET);
//	}
//	//temp = 0x3f
//	if(temp & 0x40){ //true or false?
// 		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_G_PORT, SEVEN_SEGMENT_1_G, SET);
//	} else{
//		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_G_PORT, SEVEN_SEGMENT_1_G, RESET);
//	}
//
//	if(temp & 0x80){
//		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_H_PORT, SEVEN_SEGMENT_1_H, SET);
//	} else{
//		HAL_GPIO_WritePin(SEVEN_SEGMENT_1_H_PORT, SEVEN_SEGMENT_1_H, RESET);
//	}

}
