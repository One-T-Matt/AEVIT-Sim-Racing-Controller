# AEVIT Sim Racing Controller
An AEVIT Mobility throttle and brake driver with serial monitoring

This project is an effort to bring some small portion of the automotive mobility world into the Sim Racing world with hopes to assist those with physical disabilities in their efforts to Sim Race.

An AEVIT throttle and brake controller is commonly used in vehicles that are modified to allow persons with physical disabilities to control the throttle and brake of their vehicle by hand

<img width="3660" height="2440" alt="EMC00099-3" src="https://github.com/user-attachments/assets/01758382-c051-4357-9fa6-93ff71bde7c2" />

This software will, when combined with an Arduino, allow an AEVIT throttle and brake controller to appear in Windows as a two axis joystick, which can be mapped in many popular sim racing packages as a throttle and brake.

This sofware was written for and tested on the AEVIT model AEVIT-DL-002.  It may work with other automotive mobility controllers, and may work with other AEVIT throttle controllers, but compatibility is not tested.

## Requirements
- AEVIT-DL-002 throttle and brake controller with intact potentiometers (and their wiring).  No further electronics or controls from the mobility hardware are required
- An Arduino.  This software was written for and tested on the Arduino Leonardo clones commonly available (Example https://www.amazon.com/dp/B01MTU9GOB). Wiring instructions are based around the Leonardo clone.
- A USB breakout cable to make cabling cleaner and easier (Example https://www.amazon.com/YACSEJAO-Female-Scanner-Extension-Straight/dp/B0DNMPDZH1)

## Software Build Requirements
The Arduino IDE will need to have access to the following libraries:
- Alignedjoy.h - https://github.com/PalladinoMarco/AlignedJoystick
- Joystick.h - https://github.com/mheironimus/arduinojoysticklibrary
- Keypad.h - https://docs.arduino.cc/libraries/keypad/

All are as of the time of this writing, available in the Arduino Library Manager

## Wiring
Per https://github.com/PalladinoMarco/AlignedJoystick/wiki/Wiring-joystick the pots need to be wired with a shared VCC and Ground connection (https://raw.githubusercontent.com/PalladinoMarco/AlignedJoystick/master/wiring2_bb.png [Note that in this example image, the joystick has two axes and requires two signal wires, in the AEVIT, each pot has a single signal wire]). In the controller, the brown and white wires are tied together for VCC. They come from the upper and 
middle pots when the controller is laying on its side with the pot stack facing upwards.  The purple and white/red wires are tied together for ground and go to the ground pin on the Aruino.  The signal pins (A0 and A2) go to the yellow wire on the middle pot and the green wire on the upper pot

The reason for the shared wiring is the single VCC and GND pins.  

The reason for using two pots instead of one (therefore requiring that each VCC and ground be tied together [GND to GND and VCC to VCC]) is that each pot seems to only register one direction of travel, so in order to build a gas AND brake function, one pot serves as the gas, and one as the brake.  This is definable in the Arduino sketch, and usually mappable in any direcion in most sim software, so the actual direction doesnt matter much, as long as both throws of the lever result in a readable joystick movement.

There is a single button tied to the other ground and pin 9 that is there to be able to get through the windows joystick calibration process

## Serial Monitoring
Uncomment the noted lines to enable serial monitoring in the Arduino IDE serial console.  This can be helpful in verifying wiring, as well as setting your deadzones, which are likely to be different on each and every controller

## Software peculiarities

### Deadzones
The AEVIT controller potentiometers are quite noisy and jittery.  There must be some filtering done in the form of deadzones in order to quiet that noise at 0% throttle and brake.  Without setting the deadzones, or with improperly set deadzones (Note that it is very likely that every AEVIT controller is different and will require custom deadzone values), the throttle and brake will activate randomly as the potentiometer jitter triggers them.

In order to set your deadzones, first enable the serial monitoring in the Arduino IDE.  It may be helpful to only enable serial monitoring for one axis at a time, in order to make troubleshooting easier.  With the serial console enabled, and the throttle/brake in its neutral position, note the values that the axis returns.
