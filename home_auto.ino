#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h> 

#define SS_PIN    10
#define RST_PIN   9
#define SERVO_PIN 3
#define SENSOR_PIN 5
#define RELAY_PIN 4

LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 rfid(SS_PIN, RST_PIN);
Servo servo;

byte authorizedUID[4] = {0xF3, 0x07, 0x1D, 0x11};//F3 07 1D 11
int angle = 110; // the current angle of servo motor

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  servo.attach(SERVO_PIN);
  servo.write(0); // rotate servo motor to 0°
  Serial.println("Tap RFID/NFC Tag on reader");

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0); // column, row
  lcd.print(" Scan Your RFID "); 
  lcd.setCursor(0,1); // column, row
  lcd.print("   Door Locked   ");

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT); 

}

void loop() {


  if (rfid.PICC_IsNewCardPresent()) { //look for newcard
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

      if (rfid.uid.uidByte[0] == authorizedUID[0] &&
          rfid.uid.uidByte[1] == authorizedUID[1] &&
          rfid.uid.uidByte[2] == authorizedUID[2] &&
          rfid.uid.uidByte[3] == authorizedUID[3] ) {
        Serial.println("Authorized Tag");
        lcd.clear();
        lcd.setCursor(0,1); // column, row
        lcd.print(" Door Un-Locked ");

        // change angle of servo motor
        angle = 0;
        servo.write(angle);
        delay(1000);
        angle = 90;
        servo.write(angle);
        
        
      } else {

        Serial.print("Unauthorized Tag with UID:");
        lcd.clear();
        lcd.setCursor(0,1); // column, row
        lcd.print("Invalid RFID Tag");
        

        for (int i = 0; i < rfid.uid.size; i++) {
          Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(rfid.uid.uidByte[i], HEX);
        }
        Serial.println();
      }

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  } 

  int sensorValue = digitalRead(SENSOR_PIN);  
    if (sensorValue == HIGH)
  {
    digitalWrite(RELAY_PIN, LOW);  // write LOW to switch on the light
  
        
  }
  else
  {
    digitalWrite(RELAY_PIN, HIGH);    
  }
  
} 















