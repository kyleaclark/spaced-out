#include <allegro.h>
#include "player.h"
#include "global.h"
#include "bitmap_load.h"
#include "bullet.h"
#include "setup.h"

Player::Player(float fx, float fy)
 {
  x = fx;
  y = fy;
  w = 80;
  h = 80;
  speed = 5;
 }

bool Player::collision(float fx, float fy, short fw, short fh, float fangle)
 {
  float nx[5];    //array of x
  float ny[5];    //array of y
  short w_d=fw/2, h_d=fh/2;  //width and height divided by 2

  nx[0] = (fx - sin(fangle)) + (fw / 2); //+ 40 * sin(player.angle);
  ny[0] = (fy + cos(fangle)) + (fh / 2); //- 40; //- 40 * cos(player.angle);
  nx[1] = nx[0] - w_d; //* sin(player.angle);
  ny[1] = ny[0] - h_d; //* -cos(player.angle);
  nx[2] = nx[0] - w_d; //* sin(player.angle);
  ny[2] = ny[0] + h_d; //* -cos(player.angle);
  nx[3] = nx[0] + w_d; //* sin(player.angle);
  ny[3] = ny[0] - h_d; //* -cos(player.angle);
  nx[4] = nx[0] + w_d; //* sin(player.angle);
  ny[4] = ny[0] + h_d; //* -cos(player.angle);

  for(short num = 1; num < 5; num++)
  {
   if(nx[num] < W_LEFT || nx[num] > W_RIGHT || ny[num] < W_UP || ny[num] > W_DOWN)
    {
     return false;
    }
  }

    return true;
 }

bool Player::move()
 {
 float fx=x, fy=y;     //x & y
 float fangle=angle;    //angle & turn
 float fvelx=0, fvely=0;    //velx & vely
 float fspeed=speed, fturn=2;            //speed

  if(key[KEY_UP])
   {
    fvelx = sin(fangle);
    fvely = cos(fangle);
    
    fy -= fvely + (fspeed * fvely);
    fx += fvelx + (fspeed * fvelx);

   // fy -= 2;
   }
  else if(key[KEY_DOWN])
   {
    fvelx = sin(fangle);
    fvely = cos(fangle);
    
    fy += fvely + (fspeed * fvely);
    fx -= fvelx + (fspeed * fvelx);
   }
  else if(key[KEY_LEFT])
   { 
    if(fangle <= 256 && fangle - fturn >= 0 )
     {
     fangle -= fturn;
     }
    else if(fangle == 256 || fangle == 0)
     {
     fangle = 256 - fturn;
     }
   }
  else if(key[KEY_RIGHT])
   { 
    if(fangle + fturn <= 256 && fangle >= 0)
     {
      fangle += fturn;
     }
    else if(fangle == 256 || fangle == 0)
     {
      fangle = fturn;
     }
   }
  //to move directly left
  else if(key[KEY_COMMA])
   {   
    fx -= (speed/2);
   }
  //to move directly right
  else if(key[KEY_STOP])  //period key
   {
    fx += (speed/2);
   }
  else if(key[KEY_SPACE])
   {
    for(short i = 0; i < SCR_MAX_BULLETS; i++)
     {
      if(bullet[i].exists == 0)
       {
         bullet[i].create(x, y, w, h, angle);
         bullet[i].move();
         break;
       }
      }
    }


 if(collision(fx, fy, w, h, fangle) == true)
   {
    x = fx;
    y = fy;
    angle = fangle;
    return true;
   }

  return false;
 }


void Player::redraw()
 {
  //  draw_sprite(buffer, player1_bmp.sprite, (int)x, (int)y);
  rotate_sprite(buffer, player1_bmp.sprite, (int)x, (int)y, ftofix(angle));
 }

