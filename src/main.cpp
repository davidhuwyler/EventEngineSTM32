#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "GPIOout.h"
#include "SquareWaveGeno.h"
#include "EventHandler.h"
#include "Event.h"


//Prototypes
void ledOnFunction(void);
void ledOffFunction(void);

namespace
{
  // -> ledOnEvent
  EventHandler::ticks_t onEventDelay = EventHandler::FREQUENCY_HZ / 5000;
  Event onEvent = Event(ledOnFunction,onEventDelay,EventHandler::getInstance());

  // -> ledOnEvent
  EventHandler::ticks_t offEventDelay = EventHandler::FREQUENCY_HZ / 5000;
  Event offEvent = Event(ledOffFunction,offEventDelay,EventHandler::getInstance());

  //Port definitions
  GPIOout<2,13> portC13;

  //Add SquareWafe Geno on Pin C14
  SquareWaveGeno<2,14,500> sqrWaveGenoC14;
  SquareWaveGeno<0,0,777>  sqrWaveGenoA0;
  SquareWaveGeno<0,1,150>  sqrWaveGenoA1;
  SquareWaveGeno<0,2,333>  sqrWaveGenoA2;
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
  trace_printf("System clock: %u Hz\n", SystemCoreClock);

  while (1)
    {
	  EventHandler::getInstance()->executePendingEvents();
    }
}

void ledOnFunction(void)
{
	offEvent.activate();
	//trace_printf("Turn On LED");
	portC13.toggle();
}
void ledOffFunction(void)
{
	onEvent.activate();
	//trace_printf("Turn Off LED");
	portC13.toggle();
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
