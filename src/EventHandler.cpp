/*
 * EventHandler.cpp
 *
 *  Created on: 16.01.2018
 *      Author: dave
 */

#include "EventHandler.h"
#include "Event.h"
#include "cortexm/ExceptionHandlers.h"
#include "cmsis_device.h"


Event* 			EventHandler::eventArray[EventHandler::MAX_NOF_EVENTS];
std::uint32_t 	EventHandler::eventIndex = 0;
EventHandler* 	EventHandler::handlerInstance;

EventHandler* EventHandler::getInstance()
{
	static bool init = true;
	//Init:
	if(init)
	{
		SysTick_Config(SystemCoreClock / EventHandler::FREQUENCY_HZ);
		init = false;
	}

	return EventHandler::handlerInstance;
}

bool EventHandler::add(Event* event)
{
	std::uint32_t i = 0;
	while(i < (EventHandler::eventIndex))
	{
		if(EventHandler::eventArray[i] == event)
		{
			return true;		//EventAlready in the EventHandler
		}
		i++;
	}

	if(EventHandler::eventIndex < (EventHandler::MAX_NOF_EVENTS-1))
	{
		EventHandler::eventArray[EventHandler::eventIndex] = event;
		EventHandler::eventIndex ++;
		return true;			//Event successfully added
	}

	return false;				//Even not added... EventHanlder is full

}

void EventHandler::tick(void)
{
	for(std::uint32_t i = 0 ; i< EventHandler::eventIndex ; i++)
	{
		EventHandler::eventArray[i]->tick();
	}
}

void EventHandler::executePendingEvents(void)
{
	bool eventHandeled = false;

	std::uint32_t i = 0;
	while(!eventHandeled && i<EventHandler::eventIndex)
	{
		if(EventHandler::eventArray[i]->call())
			eventHandeled = true;

		i++;
	}
}

EventHandler::~EventHandler() {
	// TODO Auto-generated destructor stub
}



// Sys Tick Handler:
extern "C" void SysTick_Handler(void)
{
	EventHandler::getInstance()->tick();
}
