# OutletTimer
A timer that powers something for up to 5 minutes designed for a small pool chemical feed

User Interface
==============
On powerup, the five time lights flash one at a time. Each time you push the button, a minute is added to the time left, starting the time as necessary. Each light turns off when its corresponding minute is over. The button has a light on it, which is on when the timer is running.

Wiring
======
Button between 5 and GND

Button Light between 8 and GND

  

*Time Lights:*

The anodes (negative sides) are strung together, grounded through a resistor.

The positive sides are connected to pins 3, 4, 6, 7, and 9.

  

*Reset Line:*

Connect a jumper wire between 2 and RESET

Simplifid code explanation
==========================
Reset() grounds pin 2, which is connected to the reset line

lights[] is the list of pins the lights are connected to

  

*Setup:*

Configure the pins and a serial port (for debugging)

Declare pin 2 as an input to avoid grounding the reset line

Initialize the lights, flashing them once to make sure they work

  

*Global Variables:*

minutes (const) is a minute in milliseconds.

btn mirrors the status of the button to determine if it was just pressed.

pump is the variable that controls the light on pin 8

offTime is the time to turn off at, when millis() >= offTime

downTime is the most recent time at which the button was pressed down.

  

*The timeLeft Function:*

Returns offTime-millis() in a data type that can actually go negative (long not *unsigned* long)

(because an *unsigned* long minus an *unsigned* long seems to be an *unsigned* long, wrapping around to practically infinity when negative)

Exploits a property of subtraction to avoid a reverse overflow.

  

*Loop:* (supposed to run a (practically) infinite number of times per second)

If the button was just pressed down, keep track of when, and add one minute to the timer.

If the time left ecceeds 5 minutes, shorten it to 5 minutes

If the time is going to overflow within 1000 minutes, reset the system, but if the timer is running, wait until it's finished before resetting.

Update the time lights based on how much time is left

Update the button light variable (pump)

If the button was down for a second, stop the timer

If the time left is negative, make it zero.

If the button variable says the button is down, check.

Set pin 8 based on the 'pump' variable

Finally, if debug mode is on, send the time left over the Serial.
