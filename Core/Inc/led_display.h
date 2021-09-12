/*
 * led_display.h
 *
 *  Created on: Sep 12, 2021
 *      Author: Nguyet
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

uint8_t update_seven_segment_led_buffer(uint8_t val, uint8_t idx);
void seven_segment_led_driver(void);

#endif /* INC_LED_DISPLAY_H_ */
