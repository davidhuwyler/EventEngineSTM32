/*
 * SquareWaveGeno.h
 *
 *  Created on: 24.01.2018
 *      Author: dave
 */

#ifndef SQUAREWAVEGENO_H_
#define SQUAREWAVEGENO_H_

#include <cstdint>
#include "GPIOout.h"
#include "Event.h"

// Port numbers: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, ...
template	<const std::uint8_t portNumber,
			 const std::uint8_t pinNumber,
			 const std::uint16_t frequency>

class SquareWaveGeno{
public:
	SquareWaveGeno()
	{
		sqrWaveEvent.setCallbackFunction(std::bind(&SquareWaveGeno::toggleOutput,this));
		sqrWaveEvent.activate(EventHandler::FREQUENCY_HZ / (2*frequency));
	}

private:
	  GPIOout<portNumber,pinNumber> output;
	  Event sqrWaveEvent = Event(EventHandler::getInstance());

	  //Toggle Function
	  inline void __attribute__((always_inline)) toggleOutput()
	  {
		  sqrWaveEvent.activate();
		  output.toggle();
	  }
};

#endif /* SQUAREWAVEGENO_H_ */
