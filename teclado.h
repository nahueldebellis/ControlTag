
char detect_key(int val, char letter, int button, int top){
  if(val >= button and val <= top)
    return letter;
  return 'n';
}

String check(char incomin, String tag_id, char esperado){
  if(incomin == esperado)
    tag_id += incomin;
  delay(100);
  return tag_id;
}

void add_tag(){

  while(true){
    Serial.println("Ingrese tag");
    if(rfid_1.PICC_IsNewCardPresent()){
      rfid_1.PICC_ReadCardSerial();
      String uidString = String(rfid_1.uid.uidByte[0])+" "+String(rfid_1.uid.uidByte[1])+" "+String(rfid_1.uid.uidByte[2])+ " "+String(rfid_1.uid.uidByte[3]);
      write_sd(uidString);
      break;
    }
    else if( rfid_2.PICC_IsNewCardPresent()){
      rfid_2.PICC_ReadCardSerial();
      String uidString = String(rfid_2.uid.uidByte[0])+" "+String(rfid_2.uid.uidByte[1])+" "+String(rfid_2.uid.uidByte[2])+ " "+String(rfid_2.uid.uidByte[3]);
      write_sd(uidString);
      break;
    }
    delay(100);
    
    if(Serial.available() > 0)
      if(Serial.readString() == "D\n")
        break;
  }
  Serial.println("Guardado");
}

void erase_tag(){
  String tag_id;
  Serial.println("erase tag");

  while(true){
    if(Serial.available() > 0){
      tag_id = Serial.readString();
      break;
    }     
  }
  delete_sd(tag_id.toInt());
}

void new_key() {
    
    int val=0;
    for(int i=1;i<=20;i++)
      val += analogRead(A3);
    
    int prom = val/20;
    if(Serial.available() > 0){
      String letter = Serial.readString();
      if(letter == "C\n")
        add_tag();     
      else if(letter == "B\n")
        erase_tag();
    }

    
}
