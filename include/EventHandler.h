/*
 * EventHandler.h
 *
 *  Created on: 16.01.2018
 *      Author: dave
 */

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <string>
#include <cstdint>

class Event;
class EventHandler {

private:
	typedef void (*callback_t)();
	static EventHandler* handlerInstance;
	static constexpr std::uint32_t MAX_NOF_EVENTS = 20;
	static Event* eventArray[MAX_NOF_EVENTS];			// Array of all Events in the Handler
	static std::uint32_t eventIndex;					// Current number of Events in the EventHandler



public:
	typedef uint32_t ticks_t;
	static constexpr ticks_t FREQUENCY_HZ = 5000u;

	static EventHandler* getInstance();
	bool add(Event* event);				//Add an Event to the EventHandler if possible
	void tick(void);					//Decrease the "time bevore call" of all Events by 1 tick. Called by Timer
	void executePendingEvents(void);	//Execute the next Event in the eventArray which needs to be called --> Events with low indexes in the eventArray have higher prio. Called in main

	virtual ~EventHandler();
};

#endif /* EVENTHANDLER_H_ */
