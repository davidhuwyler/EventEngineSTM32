/*
 * EventHandler.cpp
 *
 *  Created on: 16.01.2018
 *      Author: dave
 */

#include "EventHandler.h"
#include "Event.h"

EventHandler::EventHandler()
{

}

bool EventHandler::add(Event* event)
{
	unsigned int i = 0;
	bool eventFound = false;

	while(i < (this->eventIndex))
	{
		if(eventArray[i]->getName().compare(event->getName())==0)
		{
			this->eventArray[i] = event;
			return true;
		}
		i++;
	}

	if(!eventFound && (this->eventIndex < (MAX_NOF_EVENTS-1)))
	{
		this->eventArray[eventIndex] = event;
		this->eventIndex ++;
		return true;
	}

	return false;

}

void EventHandler::tick(void)
{
	while(true)
	{
		for(int i = 0 ; i< this->eventIndex ; i++)
		{
			eventArray[i]->tick();
		}
	}
}

void EventHandler::execute(void)
{
	unsigned int i = 0;
	bool eventHandeled = false;

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






