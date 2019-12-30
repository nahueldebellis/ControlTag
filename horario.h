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

int weekday_to_number(char w){
  switch(w){
    case 'D': return 1;
      break;
    case 'L': return 2;
      break;
    case 'M': return 3;
      break;
    case 'E': return 4;
      break;
    case 'J': return 5;
      break;
    case 'V': return 6;
      break;
    case 'S': return 7;
      break;
  }
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

bool is_valid_time_inicio(tmElements_t tm_inicio){
  if(hour(today) > tm_inicio.Hour)
    return true;
  if(hour(today) == tm_inicio.Hour)
    if(minute(today) >= tm_inicio.Minute)
      return true;
  return false;
}

bool is_valid_time_fin(tmElements_t tm_fin){
  if(hour(today) < tm_fin.Hour)
    return true;
  if(hour(today) == tm_fin.Hour)
    if(minute(today) <= tm_fin.Minute)
      return true;
  return false;
}

bool is_valid_date(tmElements_t tm_inicio, tmElements_t tm_fin){
   bool r = false;
   if(is_valid_day(tm_inicio, tm_fin))
    r = true;
   if(weekday(today) == tm_inicio.Wday)
     r = is_valid_time_inicio(tm_inicio);
   if(weekday(today) == tm_fin.Wday)
     r = is_valid_time_fin(tm_fin);
   return r;
}
