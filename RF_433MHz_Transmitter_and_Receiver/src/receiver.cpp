#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

const int BLUE_LED = 7;
const int RED_LED = 8;

const int BUZZER = 5;

int alarm = 0;
bool alarmSound = false;





void setup() {
  Serial.begin(9600); // Debugging only

  pinMode(BLUE_LED, OUTPUT); 
  pinMode(RED_LED, OUTPUT); 
  
  if (!driver.init()) {
    Serial.println("init failed");  
  }
}





void loop() {
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);
  
  // Non-blocking
  if (driver.recv(buf, &buflen)) {
    int i;

    // Message with a good checksum received, dump it.
    Serial.print("Message: ");
    Serial.println((char*)buf);

    // alarmSound = true;

    alarm = alarm + 1;
    
    // if (alarm >= 4) {
    //   alarm = 0;
    // }

    switch (alarm)
    {
      case 0:
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(RED_LED, LOW);
        break;

      case 1:
        digitalWrite(RED_LED, LOW);
        digitalWrite(BLUE_LED, HIGH);
        break;

      case 2:
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        break;

      case 3:
        digitalWrite(BLUE_LED, HIGH);
        digitalWrite(RED_LED, HIGH);
        alarmSound = true;
        break;
    
      default:
        break;
    }
  }

  if (alarmSound == true) {
    digitalWrite(BUZZER, LOW);
    delay(500);
    digitalWrite(BUZZER, HIGH);
    delay(500);
  }
}