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

const bool testing = true;

#define TEST (testing*SECONDS)

void setup() {
  pinMode(SIGA, OUTPUT);
  pinMode(SIGB, OUTPUT);

  pinMode(PB1, INPUT);
  pinMode(PB2, INPUT);
}

void signal(unsigned int pulse_width, unsigned int rest_width, unsigned int pulse_count, unsigned int block_rest, bool direction) {


  for (int i = 0; i++; i < pulse_count) {
    int x = direction * pulse_count;

    delayMicroseconds((pulse_width + (50 * (abs(x - i))))*TEST);
  }
}


void loop() {

  switch (MODE) {
    case 1:
      delayMicroseconds(A);
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    default:

      break;
  }

}
