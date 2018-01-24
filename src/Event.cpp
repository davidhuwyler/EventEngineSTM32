/*
 * Event.cpp
 *
 *  Created on: 16.01.2018
 *      Author: dave
 */

#include "Event.h"

Event::Event(EventHandler* handler)
{
	this->handler = handler;
}

Event::Event(std::function<void(void)> callbackFunction,EventHandler* handler)
{
	this->callbackFunction = callbackFunction;
	this->handler = handler;
}

Event::Event(std::function<void(void)> callbackFunction,std::uint32_t timeBevoreCall_ms,EventHandler* handler)
{
	this->callbackFunction = callbackFunction;
	this->handler = handler;
	this->reloadTime_ms = timeBevoreCall_ms;
	activate(timeBevoreCall_ms);
}

bool Event::call()
{
	if(this->requiersCalling && this->isActivated)
	{
		this->requiersCalling = false;
		this->isActivated = false;
		if(this->callbackFunction)
			this->callbackFunction();

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

bool Event::activate(std::uint32_t timeBevoreCall_ms)
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


void Event::setEventHandler(EventHandler* handler)
{
	this->handler = handler;
}

void Event::setReloadTime(std::uint32_t timeBevoreCall_ms)
{
	this->reloadTime_ms = timeBevoreCall_ms;
}

void Event::setCallbackFunction(std::function<void(void)> callbackFunction)
{
	this->callbackFunction = callbackFunction;
}

Event::~Event() {
	// TODO Auto-generated destructor stub
}

