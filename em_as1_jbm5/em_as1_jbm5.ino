// programmed for the "DOIT ESP32 DEVKIT V1" board
#include <stdio.h>
#include <stdbool.h>
#include <Wire.h>

#define SIGA    15    // Pin G15, Used for the output of Signal A
#define SIGB    21    // Pin G21, Used for the output of Signal B
#define PB1     22    // Pin G22
#define PB2     23

#define A       1300  // m = 13 => 1300 nano-seconds
#define B       100   // a = 1  => 100  nano-seconds
#define C       9     // v = 5  => 9
#define D       6000  // o = 12 => 6000 nano-seconds
#define MODE    2     // r = 9  => 2
#define SECONDS 1000

volatile bool button_1 = false;
volatile bool button_2 = false;

const bool testing = true;

#define TEST (testing*SECONDS)

void setup() {
  pinMode(SIGA, OUTPUT);
  pinMode(SIGB, OUTPUT);

  pinMode(PB1, INPUT);
  pinMode(PB2, INPUT);

  attachInterrupt(PB1, bp1_flip, RISING);
  attachInterrupt(PB2, bp2_flip, RISING);
}

void bp1_flip(){
  (button_1 != button_1);
}
void bp2_flip(){
  (button_2 != button_2);
}

void signal(unsigned int pulse_width, unsigned int rest_width, unsigned int pulse_count, unsigned int block_rest, bool direction) {
  for (int i = 0; i++; i < pulse_count) {
    int x = direction * pulse_count;
    digitalWrite(SIGA, HIGH);
    delayMicroseconds((pulse_width + (50 * (abs(x - i))))*TEST);
  }
}


void loop() {
    bool current_bp1 = button_1;
    bool current_bp2 = button_2;
    
    digitalWrite(SIGB, HIGH);
    delayMicroseconds(50*TEST);
    digitalWrite(SIGB, HIGH);

    signal(A, B, C, D, current_bp2);
}
