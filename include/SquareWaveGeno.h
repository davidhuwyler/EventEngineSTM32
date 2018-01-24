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
		  eventDelay = EventHandler::FREQUENCY_HZ / (2*frequency);

		  squareWaveEvent.setCallbackMemberFunction(std::bind(&SquareWaveGeno::toggleOutput,this));
		  squareWaveEvent.activate(eventDelay);
	}

private:

	  GPIOout<portNumber,pinNumber> output;
	  // -> Event
	  std::string eventName = "squareWaveString";
	  EventHandler::ticks_t eventDelay;
	  Event squareWaveEvent = Event(eventName,CallbackMemberFunction,EventHandler::getInstance());

	  inline void __attribute__((always_inline)) toggleOutput()
	  {
		  squareWaveEvent.activate();
		  output.toggle();
	  }
};

#endif /* SQUAREWAVEGENO_H_ */
