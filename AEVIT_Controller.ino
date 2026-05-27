/*
 * AEVIT Mobility throttle and brake driver with serial monitoring
 * Initial Release - 5-19-2020
 * VERSIONS
 * 1.2 - Initial button functionality on PIN 1
 * 1.1 - Removed delay(5); left over from testing build and changed setAccelerator/BrakeRange to create a deadzone between throttle and brake
 * 1.0 - First working prototype, throttle is a full axis, brake is single axis for some reason?
*/

/*
*WIRING
*Per https://github.com/PalladinoMarco/AlignedJoystick/wiki/Wiring-joystick the pots need to be wired with a shared VCC and Ground connection
*In the controller, the brown and white wires are tied together for VCC. They come from the upper and 
*middle pots when the controller is laying on its side with the pot stack facing upwards.  The purple and white/red wires are tied together for
*ground and go to the ground pin on the Aruino.  The signal pins (A0 and A2) go to the yellow wire on the middle pot and the green wire on the upper pot
*The reason for the shared wiring is the single VCC and GND pins.  The reason for using two pots instead of one (therefore requiring that each
*VCC and ground be tied together [GND to GND and VCC to VCC]) is that each pot seems to only register one direction of travel, so in order to build a 
*gas AND brake function, one pot serves as the gas, and one as the brake.  This is definable by the firmware below, and usually mappable in any direcion
*in most sim software, so the actual direction doesnt matter much, as long as both throws of the lever result in a readable joystick movement.
*There is a single button tied to the other ground and pin 9 that is there to be able to get through the windows joystick calibration process      
*/

// INCLUDE LIBRARY
#include <AlignedJoy.h>
#include "Joystick.h"
#include <Keypad.h>

//chan-ged from JOYSTICK_TYPE_MULIT_AXIS to GAMEPAD
Joystick_ AEVIT(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 1, 0,
  false, false, false, false, false, false,
  false, false, true, true, false);  //1 BUTTON, 0 HATS, Accelerator and Brake only

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = true;

const int pinToButtonMap = 9; //Map the button to pin 9


// PINs DEFINITION
// joystick 1
#define PIN_JOY1_X   0  //(up  down) PIN 0 GREEN OUTER POT ON AEVIT
#define PIN_JOY1_Y   1  //(left  right) DISCONNECTED, PROBABLY GARBAGE DATA
// joystick 2
#define PIN_JOY2_X   2  //(up  down)PIN 2 YELLOW MIDDLE POT ON AEVIT
#define PIN_JOY2_Y   3  //(left  right) DISCONNECTED, PROBABLY GARBAGE DATA


// CLASS CONSTRUCTORs
// new joystick object
AlignedJoy joystick_1(PIN_JOY1_X, PIN_JOY1_Y);
AlignedJoy joystick_2(PIN_JOY2_X, PIN_JOY2_Y);


void setup() {
  pinMode(pinToButtonMap, INPUT_PULLUP);   // Initialize Button Pins
  AEVIT.setAcceleratorRange(120, 465); //deadzone programmed in, acc doesnt start until 465, in reality its anwhere from 515-460
  AEVIT.setBrakeRange(540, 850); //same deadzone setup for brake
  AEVIT.begin();
 // SERIAL SETUP FOR DEBUG
 //Serial.begin(9600); //UNCOMMENT TO ENABLE SERIAL DEBUG
//while(!Serial){}  //UNCOMMENT TO ENABLE SERIAL DEBUG
}

int lastButtonState = 0; // Last state of the button

void loop() {
  //BEGIN BUTTON HANDLING
  int currentButtonState = !digitalRead(pinToButtonMap);
  if (currentButtonState != lastButtonState)
  {
    AEVIT.setButton(0, currentButtonState);
    lastButtonState = currentButtonState;
  }
  //END BUTTON HANDLING
  
 // for read axis value use "read" method. For x axis -> objectname.read(X); for y axis -> objectname.read(Y).
 // print joystick 1 axes value
//Serial.print("joystick_1 X -> "); //UNCOMMENT TO ENABLE SERIAL DEBUG
//Serial.print(joystick_1.read(X)); //UNCOMMENT TO ENABLE SERIAL DEBUG
 AEVIT.setAccelerator(joystick_1.read(X));
//Serial.print(" | Y -> "); //UNUSED
//Serial.print(joystick_1.read(Y)); //UNUSED
 
 // print joystick 1 axes value
 //Serial.print(" -|- joystick_2 X -> "); //UNCOMMENT TO ENABLE SERIAL DEBUG
 //Serial.println(joystick_2.read(X)); //UNCOMMENT TO ENABLE SERIAL DEBUG
  AEVIT.setBrake(joystick_2.read(X));
 //Serial.print(" | Y -> "); //UNUSED
 //Serial.println(joystick_2.read(Y)); //UNUSED
 //delay(5);
}
