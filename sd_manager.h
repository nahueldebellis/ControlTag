#include <SD.h>
#define SD_CARD 3

File tag_control_permanent_save;
File tmp;

void _rename(){
  String line;
  tmp = SD.open("tmp.txt");
  tag_control_permanent_save = SD.open("p.txt", FILE_WRITE);
  while(tmp.available()){
    line = tmp.readStringUntil('\n');
    tag_control_permanent_save.println(line);
  }
  tag_control_permanent_save.close();
  SD.remove("tmp.txt");
  tmp.close();

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

int calculate_id(){
  int last_id;
  String line;
  tag_control_permanent_save = SD.open("p.txt"); 
   
  while(tag_control_permanent_save.available())
    line = tag_control_permanent_save.readStringUntil('\n');
  
  tag t = string_to_tag(line);
  last_id = t.id;
  tag_control_permanent_save.close();
  return last_id+1;
}

void write_sd(String tag_string){  
  int id = calculate_id();
  
  Serial.println("El nuevo id del tag ingresado es ");
  Serial.println(id);
  
  tag t = {id,tag_string,1}; ///Si hay control horario modificar lo que se escribe en la tarjeta sd cuando se agrega aca
  
  tag_control_permanent_save = SD.open("p.txt", FILE_WRITE);
  if (tag_control_permanent_save)           
    tag_control_permanent_save.println(tag_to_string(t));  
  tag_control_permanent_save.close();

}

void delete_sd(int target){

  tmp = SD.open("tmp.txt", FILE_WRITE);
  Serial.println(target);
  String line;
  tag_control_permanent_save = SD.open("p.txt");
  while(tag_control_permanent_save.available()){
    line = tag_control_permanent_save.readStringUntil('\n');
    tag tg = string_to_tag(line);
    
    if(tg.id != target)
      tmp.println(line);
    else
      continue;     
  }
  tag_control_permanent_save.close();
  SD.remove("p.txt");
  tmp.close();


  _rename(); 
}



bool check_valid_tag(String incomin_tag){
  tag comp;
  bool is_valid = false;
  cant_tags = calculate_tags();  
  tag_control_permanent_save = SD.open("p.txt");
  
  for(int i=0;i<cant_tags;i++){
    String line;
    
    line = tag_control_permanent_save.readStringUntil('\n');
          
    if(line.indexOf(',')>-1)
      comp = string_to_tag(line);
    if(comp.uuid_tag == incomin_tag){
      is_valid  = true;
      break;
    }
  }

  tag_control_permanent_save.close();
  return is_valid;
}
