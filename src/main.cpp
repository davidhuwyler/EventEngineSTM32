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
  // ----- Timing definitions -------------------------------------------------

  // Keep the LED on for 2/3 of a second.
  constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
  constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ
      - BLINK_ON_TICKS;


  // Event definitions:
  EventHandler handler;

  // -> ledOnEvent
  std::string onEventName = "onEvent";
  Timer::ticks_t onEventDelay = Timer::FREQUENCY_HZ / 500; // 100ms
  Event onEvent = Event(onEventName,ledOnFunction,onEventDelay,&handler);

  // -> ledOnEvent
  std::string offEventName = "offEvent";
  Timer::ticks_t offEventDelay = Timer::FREQUENCY_HZ / 1000; // 50ms
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

  uint32_t seconds = 0;

  while (1)
    {
	  handler.execute();
    }
}


void ledOnFunction(void)
{
	offEvent.activate();
	trace_printf("Turn On LED");
	blinkLed.turnOn();
}
void ledOffFunction(void)
{
	onEvent.activate();
	trace_printf("Turn Off LED");
	blinkLed.turnOff();
}


#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
