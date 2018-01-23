/*
 * GPIO.h
 *
 *  Created on: 23.01.2018
 *      Author: dave
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <cstdint>
#include "stm32f10x.h"

#define BLINK_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define BLINK_PIN_MASK(_N)              (1 << (_N))
#define BLINK_RCC_MASKx(_N)             (RCC_APB2Periph_GPIOA << (_N))


// Port numbers: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, ...
template	<const std::uint8_t portNumber,
			 const std::uint8_t pinNumber>
class GPIOout {
public:
	  __attribute__((always_inline)) GPIOout()
	  {
		  RCC_APB2PeriphClockCmd(BLINK_RCC_MASKx(portNumber), ENABLE);

		  GPIO_InitTypeDef GPIO_InitStructure;

		  // Configure pin in output push/pull mode
		  GPIO_InitStructure.GPIO_Pin = BLINK_PIN_MASK(pinNumber);
		  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		  GPIO_Init(BLINK_GPIOx(portNumber), &GPIO_InitStructure);

		  low();
	  }

	  inline void __attribute__((always_inline)) high()
	  {
		  GPIO_SetBits(BLINK_GPIOx(portNumber),BLINK_PIN_MASK(pinNumber));
	  }

	  inline void __attribute__((always_inline)) low()
	  {
		  GPIO_ResetBits(BLINK_GPIOx(portNumber),BLINK_PIN_MASK(pinNumber));
	  }

	  inline void __attribute__((always_inline)) toggle()
	  {
		  if(GPIO_ReadOutputDataBit(BLINK_GPIOx(portNumber),BLINK_PIN_MASK(pinNumber)))
			 low();
		  else
			 high();
	  }
};

#endif /* GPIO_H_ */
