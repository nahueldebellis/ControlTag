int cant_tags;

struct tag{
  int id;
  String uuid_tag;
  bool is_valid;
};

tag _TT[] = {
  {1, "103 85 36 163", true},
  {2, "77 207 97 139", true},
  {3,  "197 42 7 27", true},
  {4, "224 45 249 27", true}
};

bool is_valid(String uuid_tag){
  for(int i=0;i<4;i++)
    if(_TT[i].uuid_tag == uuid_tag)
      return true;
  return false;
}
