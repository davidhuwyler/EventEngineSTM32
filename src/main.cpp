#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"

#include "EventHandler.h"
#include "Event.h"

//Prototypes
void ledOnFunction(void);
void ledOffFunction(void);

namespace
{
  // Event definitions:
  EventHandler handler;

  // -> ledOnEvent
  std::string onEventName = "onEvent";
  Timer::ticks_t onEventDelay = Timer::FREQUENCY_HZ / 5000;
  Event onEvent = Event(onEventName,ledOnFunction,onEventDelay,&handler);

  // -> ledOnEvent
  std::string offEventName = "offEvent";
  Timer::ticks_t offEventDelay = Timer::FREQUENCY_HZ / 5000;
  Event offEvent = Event(offEventName,ledOffFunction,offEventDelay,&handler);

  //Timer and LED objects
  Timer timer;
  BlinkLed blinkLed;
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
  timer.start();
  timer.setEventHandler(&handler);
  blinkLed.powerUp();

  while (1)
    {
	  handler.execute();
    }
}

void ledOnFunction(void)
{
	offEvent.activate();
	//trace_printf("Turn On LED");
	blinkLed.turnOn();
}
void ledOffFunction(void)
{
	onEvent.activate();
	//trace_printf("Turn Off LED");
	blinkLed.turnOff();
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
