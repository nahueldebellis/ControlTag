int cant_tags;

struct horario{
  int inicio;
  int fin;
};

struct tag{
  int id;
  String uuid_tag;
  bool is_valid;
  horario sem[6];
};


String tag_to_string(tag t){
  return String(t.id)+","+t.uuid_tag+","+String(t.is_valid)+",";
}

tag string_to_tag(String t){
  char corte = ',';
  String r[4];
  int j=0;
  
  for(int i=0;i<4;i++){
    String aux;
    
    while(t[j] != corte){       
       aux = aux+String(t[j]);
       j++;
    }
    j++; //salteo la coma
    r[i] = aux;
  }
  //r[3] = "830. 2100. 830. 2100. 830. 2100. 830. 2100. 830. 2100. 830. 2100. 830. 2100";
  tag ret = {r[0].toInt(), r[1], r[2]=="1"};
  return ret;
}
