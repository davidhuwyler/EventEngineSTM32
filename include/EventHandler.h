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

typedef void (*callback_t)();

constexpr std::uint32_t MAX_NOF_EVENTS = 20;

class Event;
class EventHandler {

private:
	Event* eventArray[MAX_NOF_EVENTS];
	std::uint32_t eventIndex = 0;		// Current number of Events in the EventHandler

public:
	EventHandler(void) = default;
	bool add(Event* event);				//Add an Event to the EventHandler if possible
	void tick(void);					//Decrease the "time bevore call" of all Events by 1 tick. Called by Timer
	void execute(void);					//Execute the next Event in the eventArray which needs to be called --> Events with low indexes in the eventArray have higher prio. Called in main

	virtual ~EventHandler();
};

#endif /* EVENTHANDLER_H_ */
