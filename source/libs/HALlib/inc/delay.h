/*
 * \file delay.h
 *
 * \date 13/06/2010
 *
 */

#ifndef DELAY_H_
#define DELAY_H_

void delay_init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void start_counting_ms_c1(uint32_t ms);
void start_counting_ms_c2(uint32_t ms);
uint8_t is_c1_off(void);
uint8_t is_c2_off(void);

#endif /* DELAY_H_ */
