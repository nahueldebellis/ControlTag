char borrar='n', crear='n';

char detect_key(int val, char letter, int button, int top){
  if(val >= button and val <= top)
    return letter;
}

String check(char incomin, String tag_id, char esperado){
  if(incomin == esperado)
    tag_id += incomin;
  return tag_id;
}

void add_tag(){
  Serial.println("add tag");
  while(true){
    
    if(rfid_1.PICC_IsNewCardPresent()){
      rfid_1.PICC_ReadCardSerial();
      String uidString = String(rfid_1.uid.uidByte[0])+" "+String(rfid_1.uid.uidByte[1])+" "+String(rfid_1.uid.uidByte[2])+ " "+String(rfid_1.uid.uidByte[3]);
      write_sd(uidString);
    }
    else if( rfid_2.PICC_IsNewCardPresent()){
      rfid_2.PICC_ReadCardSerial();
      String uidString = String(rfid_2.uid.uidByte[0])+" "+String(rfid_2.uid.uidByte[1])+" "+String(rfid_2.uid.uidByte[2])+ " "+String(rfid_2.uid.uidByte[3]);
      write_sd(uidString);
    }
    delay(100);
    
    int val = 0;
    for(int i=1;i<=20;i++)
      val += analogRead(A3);
      
    int prom = val/20;
    
    if(detect_key(prom, 'D', 0, 10) == 'D')
      break;
  }
}

void erase_tag(){
  String tag_id;
  Serial.println("erase tag");
  while(true){
    char tmp;
    int val=0;
    
    for(int i=1;i<=20;i++)
      val += analogRead(A3);
    
    int prom = val/20;
    
    if(detect_key(prom, 'D', 0, 10) == 'D')
      break;
    
    tmp = detect_key(prom, '0', 160, 170);
    tag_id = check(tmp, tag_id, '0');
    
    tmp = detect_key(prom, '9', 185, 220);
    tag_id = check(tmp, tag_id, '9');
    
    tmp = detect_key(prom, '8', 255, 265);
    tag_id = check(tmp, tag_id, '8');
    
    tmp = detect_key(prom, '7', 310, 315);
    tag_id = check(tmp, tag_id, '7');
    
    tmp = detect_key(prom, '6', 325, 390);
    tag_id = check(tmp, tag_id, '6');
    
    tmp = detect_key(prom, '5', 400, 410);
    tag_id = check(tmp, tag_id, '5');
    
    tmp = detect_key(prom, '4', 440, 442);
    tag_id = check(tmp, tag_id, '4');

    tmp = detect_key(prom, '3', 460, 475);
    tag_id = check(tmp, tag_id, '3');
    
    tmp = detect_key(prom, '2', 500, 510);
    tag_id = check(tmp, tag_id, '2');
    
    tmp = detect_key(prom, '1', 515, 550);
    tag_id = check(tmp, tag_id, '1');
  }

  delete_sd();
  

}

void new_key() {
    Serial.println("new key");
    int val=0;
    for(int i=1;i<=20;i++)
      val += analogRead(A3);
    
    int prom = val/20;
    
    crear = detect_key(prom, 'C', 101, 150);
    borrar = detect_key(prom, 'B', 320, 324);
    
    if(crear != 'n')
      add_tag();
    else if(borrar != 'n')
      erase_tag();
      
    crear = borrar = 'n';   
    
}
