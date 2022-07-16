#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);

  // Send attention command to check if all fine, it returns OK
  mySerial.println("AT");
  updateSerial();

  // Signal quality test, value range is 0 - 31 , 31 is the Excellent
  mySerial.println("AT+CSQ");
  updateSerial();

  // Used to read the ICCID from the SIM, if returns means SIM is plugged
  mySerial.println("AT+CCID");
  updateSerial();

  // Check whether it has registered on the network
  mySerial.println("AT+CREG?");
  updateSerial();
}

void loop() {
  updateSerial();
}

// For data transmission from Serial to Software Serial port & vice versa
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }

  while (mySerial.available()) {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
