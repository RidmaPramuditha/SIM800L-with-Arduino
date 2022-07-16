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

  // Configuring module in TEXT mode
  mySerial.println("AT+CMGF=1");
  updateSerial();

  // to send message use these 3 statements, upto write(26)
  // change ZZ with country code and xxxxxxxxxxx with phone number to sms
  mySerial.println("AT+CMGS=\"+ZZxxxxxxxxxx\""); // 1)
  updateSerial();
  mySerial.print("MERCURY LABS"); // 2) text content 
  updateSerial();
  mySerial.write(26); // 3)
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
