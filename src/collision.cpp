#include <allegro.h>
#include "collision.h"




Collision::Collision()
 {
 }



bool Collision::pl(float fx, float fy, short fw, short fh, float fangle)
 {
  float x[5];    //array of x
  float y[5];    //array of y
  short w_d=fw/2, h_d=fh/2;  //width and height divided by 2

  x[0] = (fx - sin(fangle)) + (fw / 2); //+ 40 * sin(player.angle);
  y[0] = (fy + cos(fangle)) + (fh / 2); //- 40; //- 40 * cos(player.angle);
  x[1] = x[0] - w_d; //* sin(player.angle);
  y[1] = y[0] - h_d; //* -cos(player.angle);
  x[2] = x[0] - w_d; //* sin(player.angle);
  y[2] = y[0] + h_d; //* -cos(player.angle);
  x[3] = x[0] + w_d; //* sin(player.angle);
  y[3] = y[0] - h_d; //* -cos(player.angle);
  x[4] = x[0] + w_d; //* sin(player.angle);
  y[4] = y[0] + h_d; //* -cos(player.angle);

  for(short num = 1; num < 5; num++)
  {
   if(x[num] < W_LEFT || x[num] > W_RIGHT || y[num] < W_UP || y[num] > W_DOWN)
    {

     return false;
    }
  }

    return true;
 }
