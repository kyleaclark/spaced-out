#include <allegro.h>
#include "global.h"

short bullets_number;
short enemy_number;

short rand_num(bool type)
 {
  short var=0;

  srand(time(NULL));
  if(type == 1)
   var = (unsigned int) W_UP+rand()%(W_DOWN-W_UP+1);
  else
   var = (unsigned int) W_LEFT+rand()%(W_RIGHT-W_LEFT+1);

  return var;
 }
