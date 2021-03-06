// programmed for the "DOIT ESP32 DEVKIT V1" board
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <Wire.h>

// pin assignments
#define SIGA    15    // Pin G15, Used for the output of Signal A
#define SIGB    21    // Pin G21, Used for the output of Signal B
#define PB1     22    // Pin G22, Used for the input of Button 1
#define PB2     23    // Pin G23, Used for the input of Button 2

// constants used to define the waveform
#define A       1300  // m = 13 => 1300 microseconds
#define B       100   // a = 1  => 100  microseconds
#define C       9     // v = 5  => 9
#define D       6000  // o = 12 => 6000 microseconds
#define MODE    2     // r = 9  => 2
#define SECONDS 1000  // microseconds to milliseconds (for non-oscilloscope testing)

// boolien variables to log the button state and prevent bouncing
volatile bool button_1 = false;
volatile bool button_2 = false;
volatile bool debounce_button_1 = false;
volatile bool debounce_button_2 = false;

// constant to easily allow for the switching between LED (true) and oscilloscope (false) testing
const bool testing = false;

// modifier to allow change the pulse timing
#define TEST (int)pow(SECONDS, testing)

// interupt functions for flipping the button variables
void BP1_flip(){
  if(button_1 && debounce_button_1){
    (button_1 = false);
  }else{
    (button_1 = true);
  }
  debounce_button_1 = false;
}
void BP2_flip(){
  if(button_2 && debounce_button_2){
    (button_2 = false);
  }else{
    (button_2 = true);
  }
  debounce_button_2 = false;
}

void setup() {
  // serial output, used for testing purposes
  if(testing) Serial.begin(230400);
  
  // configure the signal pins to work as output pins
  pinMode(SIGA, OUTPUT);
  pinMode(SIGB, OUTPUT);

  // configure the button pins to work as input pins
  pinMode(PB1, INPUT);
  pinMode(PB2, INPUT);

  // setup the push buttons to be triggered on a raising edge
  attachInterrupt(PB1, BP1_flip, RISING);
  attachInterrupt(PB2, BP2_flip, RISING);
}

/*  function used to create a signal based on the inputs
*   pulse_width   :- (int)  The base pulse width of the high signal pulses
*   rest_width    :- (int)  The width of the low signal pulses between the pulses
*   pulse_count   :- (int)  The number of high pulses per block
*   block_rest    :- (int)  The width of the low signal pulse at the end of a block
*   active        :- (bool) Is the signal waveform active (used to retain the trigger signal timings)
*   modified      :- (bool) determines if the signal is the regular version (false) or the modified version (true)
*/
void signal(unsigned int pulse_width, unsigned int rest_width, unsigned int pulse_count, unsigned int block_rest, bool active, bool modified) {
  int x;
  // loop creating the signal pulses
  for (int i = 0; i < pulse_count; i++) {

    // calculate the modification to the width of the current pulse
    if(modified){
      x = (pulse_count-1) - i;
    } else {
      x = i;
    }
    
    // serial output, user for testing purposes
    if(testing){
      Serial.print(button_1);
      Serial.print("\t");
      Serial.print(button_2);
      Serial.print("\t");
      Serial.print(modified);
      Serial.print("\t");
      Serial.print(pulse_count);
      Serial.print("\t");
      Serial.print(x);
      Serial.print("\n");
    }
    
    if(active) digitalWrite(SIGA, HIGH);                // start high pulse
    delayMicroseconds((pulse_width + (50 * x))*TEST);   // delay for the duration of the pulse
    if(active) digitalWrite(SIGA, LOW);                 // end high pulse
    delayMicroseconds(rest_width*TEST);                 // delay for low pulse
  }

  // end on block low pulse
  delayMicroseconds(block_rest*TEST);
}


void loop() {
  // update the signal only at the restarting point of the cycle
  bool current_bp1;
  bool current_bp2;

  debounce_button_1 = true;
  debounce_button_2 = true;
  
  current_bp1 = button_1;
  current_bp2 = button_2;

  // oscilloscope trigger signal (Signal B)
  digitalWrite(SIGB, HIGH);
  delayMicroseconds(50*TEST);
  digitalWrite(SIGB, LOW);

  // generated signal (Signal A)
  signal(A, B, C, D, current_bp1, current_bp2);
}
