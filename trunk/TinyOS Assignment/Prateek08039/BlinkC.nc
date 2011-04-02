#include "Timer.h"

module BlinkC @safe()
{
    uses interface Timer<TMilli> as Timer0;
    uses interface Leds;
    uses interface Boot;
}
implementation
{
    event void Boot.booted()
    {
        call Timer0.startPeriodic( 1000 );
    }

    event void Timer0.fired()
    {

        call Leds.led0Toggle();
        dbg("BlinkC", "Timer 0 fired led0 @ %s.\n", sim_time_string());
        call Leds.led1Toggle();
        dbg("BlinkC", "Timer 0 fired led1 @ %s.\n", sim_time_string());
        call Leds.led2Toggle();
        dbg("BlinkC", "Timer 0 fired led2@ %s.\n", sim_time_string());
    }
}
