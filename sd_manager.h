#include <SD.h>
#define SD_CARD 3

File tag_control_permanent_save;


void write_sd(String tag_string){
  
  tag_control_permanent_save = SD.open("p.txt", FILE_WRITE);
  
  cant_tags++;  
  tag t = {cant_tags,tag_string,1}; ///Si hay control horario modificar lo que se escribe en la tarjeta sd cuando se agrega aca
  
  if (tag_control_permanent_save)           
    tag_control_permanent_save.println(tag_to_string(t));  
  tag_control_permanent_save.close();

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
