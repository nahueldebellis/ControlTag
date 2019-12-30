#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include "tag.h"
#include "sd_manager.h";

#define SDA 10
#define SDA_2 8
#define RST 9
#define RELE 4
#define SD_CARD 3


//keys[4] = "197 239 203 45";

MFRC522 rfid_1(SDA, RST); 
MFRC522 rfid_2(SDA_2, RST);

void setup() {
  Serial.begin(9600);
  
  SPI.begin();
  rfid_1.PCD_Init(); 
  rfid_2.PCD_Init(); 
  if(!SD.begin(SD_CARD))
    Serial.println("Error initializing sd card");
  Serial.println("Working.....");

}

void loop(){
  if(rfid_1.PICC_IsNewCardPresent()){
     rfid_1.PICC_ReadCardSerial();
     check_incomin_tag(rfid_1);
  }
  else if( rfid_2.PICC_IsNewCardPresent()){
    rfid_2.PICC_ReadCardSerial();
    check_incomin_tag(rfid_2); 
  }
  delay(100);
}

void check_incomin_tag (MFRC522 rfid){
    Serial.println("Scanned PICC's UID:");
    String uidString = String(rfid.uid.uidByte[0])+" "+String(rfid.uid.uidByte[1])+" "+String(rfid.uid.uidByte[2])+ " "+String(rfid.uid.uidByte[3]);
    Serial.println(uidString);
    if(check_valid_tag(uidString)){
      digitalWrite(RELE, HIGH);
      delay(2000);
      digitalWrite(RELE, LOW);
    }
}
