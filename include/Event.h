/*
 * Event.h
 *
 *  Created on: 16.01.2018
 *      Author: dave
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include "EventHandler.h"
#include <functional>

enum EventType
{
	CallbackFunction = 0,
	CallbackMemberFunction = 1
};


typedef void (*callback_t)();

class Event {
private:
	EventType eventType;
	callback_t callback;
	bool isActivated = false;
	bool requiersCalling = false;
	unsigned int timeBevoreCall_ms = 0;
	unsigned int reloadTime_ms = 0;
	EventHandler* handler;
	std::string name;
	std::function<void(void)> callbackMemberFunction;

public:
	//Event(std::string name,EventType eventType);
	Event(std::string name,EventType eventType, EventHandler* handler);

	Event(std::string name,callback_t callback,EventHandler* handler);
	Event(std::string name,callback_t callback, unsigned int timeBevoreCall_ms,EventHandler* handler);

	Event(std::string name,std::function<void(void)> callbackMemberFunction,EventHandler* handler);
	Event(std::string name,std::function<void(void)> callbackMemberFunction,unsigned int timeBevoreCall_ms,EventHandler* handler);


	bool call(void);
	void setReloadTime(unsigned int timeBevoreCall_ms);
	bool activate();
	bool activate(unsigned int timeBevoreCall_ms);
	void deactivate(void);
	void tick(void);
	std::string getName(void);

	void setEventHandler(EventHandler* handler);
	void setCallbackFunction(callback_t callback);
	void setCallbackMemberFunction(std::function<void(void)> callbackMemberFunction);


	virtual ~Event();
};

#endif /* EVENT_H_ */
