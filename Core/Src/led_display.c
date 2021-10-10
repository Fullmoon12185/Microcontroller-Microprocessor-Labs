/*
 * led_display.c
 *
 *  Created on: Sep 12, 2021
 *      Author: Nguyet
 */

#include "main.h"
#include "led_display.h"

#define NUMBER_OF_DECIMAL_DIGITS			10
#define	NUMBER_OF_SEVEN_SEGMENT_LEDS		8



//common Anode
static uint8_t sevenSegmentLEDConversion[NUMBER_OF_DECIMAL_DIGITS] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

//common Cathode
//uint8_t sevenSegmentLEDConversion[NUMBER_OF_DECIMAL_DIGITS] = {};

static uint8_t sevenSegmentLEDBuffer[NUMBER_OF_SEVEN_SEGMENT_LEDS];


static uint16_t sevenSegmentControlPin[NUMBER_OF_SEVEN_SEGMENT_LEDS] = {
		RED_LED_0_Pin,
		RED_LED_1_Pin,
		RED_LED_2_Pin,
		RED_LED_3_Pin,
		RED_LED_4_Pin,
		RED_LED_5_Pin,
		RED_LED_6_Pin,
		RED_LED_7_Pin
};
static GPIO_TypeDef * sevenSegmentControlPort[NUMBER_OF_SEVEN_SEGMENT_LEDS] = {
		RED_LED_0_GPIO_Port,
		RED_LED_1_GPIO_Port,
		RED_LED_2_GPIO_Port,
		RED_LED_3_GPIO_Port,
		RED_LED_4_GPIO_Port,
		RED_LED_5_GPIO_Port,
		RED_LED_6_GPIO_Port,
		RED_LED_7_GPIO_Port,
};
static uint16_t sevenSegmentDataPin[8] = {
		A_SEGMENT_Pin,
		B_SEGMENT_Pin,
		C_SEGMENT_Pin,
		D_SEGMENT_Pin,
		E_SEGMENT_Pin,
		F_SEGMENT_Pin,
		G_SEGMENT_Pin,
		DOT_SEGMENT_Pin
};
static GPIO_TypeDef * sevenSegmentDataPort[8] = {
		A_SEGMENT_GPIO_Port,
		B_SEGMENT_GPIO_Port,
		C_SEGMENT_GPIO_Port,
		D_SEGMENT_GPIO_Port,
		E_SEGMENT_GPIO_Port,
		F_SEGMENT_GPIO_Port,
		G_SEGMENT_GPIO_Port,
		DOT_SEGMENT_GPIO_Port
};
uint8_t update_seven_segment_led_buffer(uint8_t idx, uint8_t val){
	if(idx >= NUMBER_OF_SEVEN_SEGMENT_LEDS) return 0;
	if(val > NUMBER_OF_DECIMAL_DIGITS) return 0;
	sevenSegmentLEDBuffer[idx] = val;
	return 1;
}


void seven_segment_data_out(uint8_t val){
	uint8_t idx;
	for(idx = 0; idx < 8; idx ++){
		if((val>>idx) & 0x01){
			HAL_GPIO_WritePin(sevenSegmentDataPort[idx], sevenSegmentDataPin[idx], GPIO_PIN_RESET);
		} else {
			HAL_GPIO_WritePin(sevenSegmentDataPort[idx], sevenSegmentDataPin[idx], GPIO_PIN_SET);
		}
	}

}
void clear_previous_seven_segment_led(uint8_t index){
	if(index >= NUMBER_OF_SEVEN_SEGMENT_LEDS) return;
	HAL_GPIO_WritePin(sevenSegmentControlPort[index], sevenSegmentControlPin[index], GPIO_PIN_RESET);
}

void set_current_seven_segment_led(uint8_t index){
	if(index >= NUMBER_OF_SEVEN_SEGMENT_LEDS) return;
	HAL_GPIO_WritePin(sevenSegmentControlPort[index], sevenSegmentControlPin[index], GPIO_PIN_SET);
}


void seven_segment_led_driver(void){
	static uint8_t ledIndex = 0;
	uint8_t tempData;
	clear_previous_seven_segment_led(ledIndex);
	ledIndex = (ledIndex + 1)%NUMBER_OF_SEVEN_SEGMENT_LEDS;
	tempData = sevenSegmentLEDConversion[sevenSegmentLEDBuffer[ledIndex]];
	seven_segment_data_out(tempData);
	set_current_seven_segment_led(ledIndex);
}
