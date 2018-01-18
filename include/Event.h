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

enum EventType
{
	CallbackFunction = 0,			//Callback is no MemberFunction
	CallbackMemberFunction = 1		//Callback is MemberFunction
};

typedef void (*callback_t)();

class Event {
private:
	EventType eventType;
	callback_t callback;
	std::function<void(void)> callbackMemberFunction;
	bool isActivated = false;
	bool requiersCalling = false;
	std::uint32_t timeBevoreCall_ms = 0;
	std::uint32_t reloadTime_ms = 0;
	EventHandler* handler;
	std::string name;


public:
	Event(std::string name,EventType eventType, EventHandler* handler);

	Event(std::string name,callback_t callback,EventHandler* handler);
	Event(std::string name,callback_t callback, std::uint32_t timeBevoreCall_ms,EventHandler* handler);

	Event(std::string name,std::function<void(void)> callbackMemberFunction,EventHandler* handler);
	Event(std::string name,std::function<void(void)> callbackMemberFunction,std::uint32_t timeBevoreCall_ms,EventHandler* handler);

	bool call(void);										//Execute the Callback of the Event
	void setReloadTime(std::uint32_t timeBevoreCall_ms);	//Set the Delay before the Event gets called [ticks]
	bool activate();										//Activates the Event -> It gets called by the EventHandler after the specified Delay
	bool activate(std::uint32_t timeBevoreCall_ms);
	void deactivate(void);									//Stops the Event. It dosnt get called.
	void tick(void);										//Decrease the Delay by one Tick.
	std::string getName(void);								//Returns the Event Name

	void setEventHandler(EventHandler* handler);
	void setCallbackFunction(callback_t callback);
	void setCallbackMemberFunction(std::function<void(void)> callbackMemberFunction);

	virtual ~Event();
};

#endif /* EVENT_H_ */
