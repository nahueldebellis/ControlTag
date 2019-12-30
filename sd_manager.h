#include <SD.h>
#define SD_CARD 3

File tag_control_permanent_save;

tag string_to_tag(String t){
  char corte = ',';
  String r[3];
  int j=0;
  
  for(int i=0;i<3;i++){
    String aux;
    
    while(t[j] != corte){       
       aux = aux+String(t[j]);
       j++;
    }
    j++; //salteo la coma
    r[i] = aux;
  }

  tag ret = {r[0].toInt(), r[1], r[2]=="1"};
  return ret;
}

int calculate_tags(){
  int i=0;
  tag_control_permanent_save = SD.open("p.txt");
  while(tag_control_permanent_save.available()){
    char char_tag;
    char_tag = tag_control_permanent_save.read();
    if(char_tag == '\n')
      i++;
  }
  tag_control_permanent_save.close();
  return i;
}

bool check_valid_tag(String incomin_tag){
  tag comp;
  bool is_valid = false;
  cant_tags = calculate_tags();  
  tag_control_permanent_save = SD.open("p.txt");
  
  for(int i=0;i<cant_tags;i++){
    String line;
    while(tag_control_permanent_save.available()){
      char char_tag;
      char_tag = tag_control_permanent_save.read();
      line += char_tag;
      if(char_tag == '\n')
        break;
    }
    
    if(line.indexOf(',')>-1)
      comp = string_to_tag(line);
    Serial.println(comp.uuid_tag);
    if(comp.uuid_tag == incomin_tag){
      is_valid  = true;
      break;
    }
  }
  
  Serial.println("closing file");
  tag_control_permanent_save.close();
  return is_valid;
}



String tag_to_string(tag t){
  return String(t.id)+","+t.uuid_tag+","+String(t.is_valid)+",";
}
