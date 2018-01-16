/*
 * Event.cpp
 *
 *  Created on: 16.01.2018
 *      Author: dave
 */

#include "Event.h"

//Event::Event(std::string name,EventType eventType)
//{
//	this->name = name;
//	this->eventType = eventType;
//}

Event::Event(std::string name,EventType eventType, EventHandler* handler)
{
	this->name = name;
	this->eventType = eventType;
	this->handler = handler;
	this->callback = NULL;
}

Event::Event(std::string name,callback_t callback,EventHandler* handler)
{
	this->name = name;
	this->callback = callback;
	this->handler = handler;
	this->eventType = CallbackFunction;
}

Event::Event(std::string name,callback_t callback, unsigned int timeBevoreCall_ms,EventHandler* handler)
{
	this->name = name;
	this->callback = callback;
	this->handler = handler;
	this->eventType = CallbackFunction;
	this->reloadTime_ms = timeBevoreCall_ms;
	activate(timeBevoreCall_ms);
}


Event::Event(std::string name,std::function<void(void)> callbackMemberFunction,EventHandler* handler)
{
	this->name = name;
	this->callbackMemberFunction = callbackMemberFunction;
	this->handler = handler;
	this->eventType = CallbackMemberFunction;
	this->callback = NULL;
}

Event::Event(std::string name,std::function<void(void)> callbackMemberFunction,unsigned int timeBevoreCall_ms,EventHandler* handler)
{
	this->name = name;
	this->callbackMemberFunction = callbackMemberFunction;
	this->handler = handler;
	this->eventType = CallbackMemberFunction;
	this->reloadTime_ms = timeBevoreCall_ms;
	activate(timeBevoreCall_ms);
}

bool Event::call()
{
	if(this->requiersCalling && this->isActivated)
	{
		this->requiersCalling = false;
		this->isActivated = false;
		if(this->callback && (this->eventType == CallbackFunction))
			this->callback();

		else if(this->callbackMemberFunction &&  (this->eventType == CallbackMemberFunction))
			this->callbackMemberFunction();

		return true;
	}

	else
		return false;
}

bool Event::activate()
{
	if(reloadTime_ms)
		return activate(this->reloadTime_ms);
	else
		return false;
}

bool Event::activate(unsigned int timeBevoreCall_ms)
{
	this->reloadTime_ms = timeBevoreCall_ms;
	if(isActivated==false)
	{
		this->timeBevoreCall_ms = timeBevoreCall_ms;
		this->isActivated = true;
		this->requiersCalling = false;
		this->handler->add(this);
		return true;
	}

	else
		return false;

}

void Event::deactivate()
{
	this->isActivated = false;
}

void Event::tick()
{
	if(this->timeBevoreCall_ms>0)
	{
		timeBevoreCall_ms --;
		if(this->timeBevoreCall_ms==0)
		{
			this->requiersCalling = true;
		}
	 }
}

std::string Event::getName(void)
{
	return name;
}

void Event::setEventHandler(EventHandler* handler)
{
	this->handler = handler;
}

void Event::setReloadTime(unsigned int timeBevoreCall_ms)
{
	this->reloadTime_ms = timeBevoreCall_ms;
}

void Event::setCallbackFunction(callback_t callback)
{
	this->callback = callback;
}

void Event::setCallbackMemberFunction(std::function<void(void)> callbackMemberFunction)
{
	this->callbackMemberFunction = callbackMemberFunction;
}

Event::~Event() {
	// TODO Auto-generated destructor stub
}

