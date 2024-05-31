#include <Adafruit_CircuitPlayground.h>
volatile int mode = 5;
volatile bool rbott = 0;
volatile bool lbott = 0;
volatile bool swonchflag = 0;
bool stop = 0;
int t = 0;
void setup() {
  CircuitPlayground.begin();
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(5, INPUT_PULLDOWN);
  attachInterrupt(7, swonch, CHANGE);
  attachInterrupt(5, decreas, RISING);
  attachInterrupt(4, up, RISING);
}

void loop() {
  if (rbott) {
    delay(5);
    mode--;
    rbott = 0;
  }
  if (lbott) {
    delay(5);
    mode++;
    lbott = 0;
  }
  if (swonchflag) {
    delay(5);
    swonchflag = 0;
    stop = !stop;
  }
  if (mode > 4) {
    mode = 0;
  }

  if (mode < 0) {
    mode = 4;
  }

  if (stop == 0) {
    switch (mode) {
      case 0:
        rainbowCycle(100, 10);
        break;
      case 1:
        blue(10);
        break;
      case 2:
        blink(5);
        break;
      case 3:
        random2(4);
        break;
      case 4:
        snake(100);
        break;
      default:
        Serial.println("massive trolling");
        break;
    }
  } else {
    CircuitPlayground.clearPixels();
  }
}
void sparkle(int delayTime) {
  int rand = random(9);
  int rando = random(9);

  while (rand == rando) {
    rand = random(9);
    rando = random(9);
  }
  CircuitPlayground.setPixelColor(rando, 0xFFFFFF);
  CircuitPlayground.setPixelColor(rand, 0xF0F0F);
  delay(delayTime / 2);
  CircuitPlayground.setPixelColor(rand, 0x000000);
  CircuitPlayground.setPixelColor(rando, 0x000000);
  delay(delayTime / 2);
}

void rainbowCycle(int currentSpeed, int stripLen) {

  // Make an offset based on the current millisecond count scaled by the current speed.

  uint32_t offset = millis() / currentSpeed;

  // Loop through each pixel and set it to an incremental color wheel value.

  for (int i = 0; i < 10; ++i) {

    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / stripLen) + offset) & 255));
  }
}
void blue(int loop) {
  uint32_t color = millis() / loop;

  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255);
  }
}
void blink(int loop) {
  uint32_t color = millis() / loop;
  int crand = random(9);
  int crand0 = random(9);
  while (crand0 == crand) {
    crand0 = random(9);
    crand = random(9);
  }
  for (int i = 0; i < 10; i++) {
    delay(loop);


    if (crand0 == i) {
      uint32_t rc = random(225);
      CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(rc));
    } else if (crand == i) {
      uint32_t trc = random(225);
      CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(trc));
    } else {
      CircuitPlayground.setPixelColor(i, 500);
    }
  }
}
void random2(int lit) {
  for (int i = 0; i < 10; i++) {
    delay(lit);
    uint32_t ran = random(255);
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(ran));
  }
}
void snake(int del) {
  for (int i = 0; i < 10; i++) {
      t = -1;
    for (int l = 0; l < 10; l++) {

      if (l == i) {
        CircuitPlayground.setPixelColor(l, CircuitPlayground.colorWheel(255));
      } else {
        CircuitPlayground.setPixelColor(l, CircuitPlayground.colorWheel(133));
      }

    }
    delay(del);
  }
}

void up() {
  lbott = 1;
}
void decreas() {
  rbott = 1;
}
void swonch() {
  swonchflag = 1;
}