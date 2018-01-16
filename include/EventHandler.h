/*
 * EventHandler.h
 *
 *  Created on: 16.01.2018
 *      Author: dave
 */

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <string>
#include <chrono>

#define MAX_NOF_EVENTS 20

typedef void (*callback_t)();
class Event;
class EventHandler {

private:
	Event* eventArray[MAX_NOF_EVENTS];
	unsigned int eventIndex = 0;

public:
	EventHandler(void);
	void tick(void);
	void execute(void);
	bool add(Event* event);

	virtual ~EventHandler();
};

#endif /* EVENTHANDLER_H_ */
