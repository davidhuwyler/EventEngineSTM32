/*
 * Event.h
 *
 *  Created on: 16.01.2018
 *      Author: dave
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <cstdint>
#include <functional>
#include "EventHandler.h"


class Event {
private:
	std::function<void(void)> callbackFunction;
	bool isActivated = false;
	bool requiersCalling = false;
	std::uint32_t timeBevoreCall_ms = 0;
	std::uint32_t reloadTime_ms = 0;
	EventHandler* handler;

public:
	Event(/*EventType eventType,*/ EventHandler* handler);

	Event(std::function<void(void)> callbackFunction,EventHandler* handler);
	Event(std::function<void(void)> callbackFunction,std::uint32_t timeBevoreCall_ms,EventHandler* handler);

	bool call(void);										//Execute the Callback of the Event
	void setReloadTime(std::uint32_t timeBevoreCall_ms);	//Set the Delay before the Event gets called [ticks]
	bool activate();										//Activates the Event -> It gets called by the EventHandler after the specified Delay
	bool activate(std::uint32_t timeBevoreCall_ms);
	void deactivate(void);									//Stops the Event. It dosnt get called.
	void tick(void);										//Decrease the Delay by one Tick.

	void setEventHandler(EventHandler* handler);
	void setCallbackFunction(std::function<void(void)> callbackFunction);

	virtual ~Event();
};

#endif /* EVENT_H_ */
