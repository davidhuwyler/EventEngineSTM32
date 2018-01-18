/*
 * EventHandler.cpp
 *
 *  Created on: 16.01.2018
 *      Author: dave
 */

#include "EventHandler.h"
#include "Event.h"

bool EventHandler::add(Event* event)
{
	std::uint32_t i = 0;
	while(i < (this->eventIndex))
	{
		if(eventArray[i]->getName().compare(event->getName())==0)
		{
			this->eventArray[i] = event;
			return true;		//EventAlready in the EventHandler
		}
		i++;
	}

	if(this->eventIndex < (MAX_NOF_EVENTS-1))
	{
		this->eventArray[eventIndex] = event;
		this->eventIndex ++;
		return true;			//Event sucessfully added
	}

	return false;				//Even not added... EventHanlder is full

}

void EventHandler::tick(void)
{
	for(std::uint32_t i = 0 ; i< this->eventIndex ; i++)
	{
		eventArray[i]->tick();
	}
}

void EventHandler::execute(void)
{
	bool eventHandeled = false;

	std::uint32_t i = 0;
	while(!eventHandeled && i<this->eventIndex)
	{
		if(eventArray[i]->call())
			eventHandeled = true;

		i++;
	}
}

EventHandler::~EventHandler() {
	// TODO Auto-generated destructor stub
}






