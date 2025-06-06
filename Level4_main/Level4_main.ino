//Arduino Uno
#include <Wire.h>
#include <avr/wdt.h>

uint32_t Data = 0;
/*-----------------------------------------------*/
void setup() {
  Serial.begin(9600);  //set the baud rate for serial communication
  NeopixelSetup();
  ServoSetup();
  ServoHome();
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.println("Level 4");
  LcdSetup();
}
/*-----------------------------------------------*/
void loop() {
  if (Serial.available() > 0) {
    int newData = Serial.parseInt();
    if (newData != 0) {
      Data = newData;
    }
  }
  switch (Data) {
    case 1:
      HandRightGripe(0);
      break;

    case 2:
      HandRightRelease(0);
      break;

    case 3:
      break;

    case 4:
      Rainbow(15);
      NeopixelClose();
      break;

    case 5:
      HandLeftGripe(0);
      HandRightGripe(0);
      delay(3000);



      break;

    case 6:
      HandLeftRelease(0);
      break;

    case 7:
      Color(255, 0, 0);
      delay(500);
  


      break;

    case 8:  //Stop
      DisplayLcd(6, "STOP", 0, "");
      ServoStop();
      NeopixelClose();
      break;

    case 9:  //Reset
      DisplayLcd(5, "RESET", 0, "");
      resetFunc();
      break;

    case 13:  //GrapDetectmove
    TheaterChaseRainbow(500) ;
    //TheaterChase(100, 50);
    //RainbowCycle(500);
    //ColorWipe(5000, 50);
      break;
  }
}

void resetFunc() {  // Restart
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {}
}
