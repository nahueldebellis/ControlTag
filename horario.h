#include <TimeLib.h>

time_t today = now();
/*
   tm.Second  Segundos   0 to 59
   tm.Minute  Minutos    0 to 59
   tm.Hour    Horas      0 to 23
   tm.Wday    Dia semana 0 to 6
*/

void set_time_arduino(int hr, int mn, int d, int mnth, int yr){ // example: set_time_arduino(12, 30, 1, 1, 2020); --> 12:30 1/1/2020 
  setTime(hr, mn, 00, d, mnth, yr);
}
   
tmElements_t format_tag_time(char wd, int h, int m){
  tmElements_t tm;
  tm.Minute = m;
  tm.Hour = h;
  tm.Wday = weekday_to_number(wd);
  return tm;
}

int parseo(int a){
  if(a == 0)
    return 7;
  return a;
}
bool is_valid_day(tmElements_t tm_inicio, tmElements_t tm_fin){
  return weekday(today) > tm_inicio.Wday && weekday(today) < tm_fin.Wday;
}

bool dday(tag t){
  int dini = t.sem[weekday(today)].inicio;
  int dfin = t.sem[weekday(today)].fin;
  check_horario();
}
