#include <allegro.h>
#include "bullet.h"
//#include "player.h"
#include "global.h"
#include "bitmap_load.h"
#include "setup.h"
#include "enemy.h"

//short bullets_number;
//short enemy_number;

Bullet::Bullet()
 {
 }

void Bullet::create(float fx, float fy, short fw, short fh, float fangle)
 {
       exists = 1;
       speed = 4;
       w = fw, h = fh;
       angle = fangle;
    
       velx = sin(angle);
       vely = cos(angle);

      /* bullet[a].x = player.x + (PLAYER_WIDTH / 2) + 40 * sin(player.angle);
       bullet[a].y = player.y + (PLAYER_HEIGHT / 2) - 40 * cos(player.angle);
    
       bullet[a].y -= bullet[a].vely + (bullet[a].speed * bullet[a].vely);
       bullet[a].x += bullet[a].velx + (bullet[a].speed * bullet[a].velx);    */
      
       x = fx + (w/2) + ((w/2) * velx);
       y = fy + (h/2) - ((h/2) * vely);
    
       y -= vely + (speed * vely);
       x += velx + (speed * velx);
 
      // gun[selected_gun].ammo--;
       bullets_number++;
 }


bool Bullet::collision(float fx, float fy, short fw, short fh, float fangle)
 {
  float nx[5];    //array of x
  float ny[5];    //array of y
  short w_d=fw/2, h_d=fh/2;  //width and height divided by 2
  float ex[5];    //enemy array of x and y
  float ey[5];    //                     ^

  nx[0] = (fx - sin(angle)) + (w_d); //+ 40 * sin(player.angle);
  ny[0] = (fy + cos(angle)) + (h_d); //- 40; //- 40 * cos(player.angle);
  nx[1] = nx[0] - w_d; //* sin(player.angle);
  ny[1] = ny[0] - h_d; //* -cos(player.angle);
  nx[2] = nx[0] - w_d; //* sin(player.angle);
  ny[2] = ny[0] + h_d; //* -cos(player.angle);
  nx[3] = nx[0] + w_d; //* sin(player.angle);
  ny[3] = ny[0] - h_d; //* -cos(player.angle);
  nx[4] = nx[0] + w_d; //* sin(player.angle);
  ny[4] = ny[0] + h_d; //* -cos(player.angle);

  for(int i = 0; i < enemy_number; i++)
   {
    if(enemy[i].exists == 1)
     {
      ex[i] = enemy[i].x + (enemy[i].w / 2);
      ey[i] = enemy[i].y + (enemy[i].h / 2);
      ex[i] = ex[i] - (enemy[i].w / 2);
      ey[i] = ey[i] - (enemy[i].h / 2);
      ex[i] = ex[i] - (enemy[i].w / 2);
      ey[i] = ey[i] + (enemy[i].h / 2);
      ex[i] = ex[i] + (enemy[i].w / 2);
      ey[i] = ey[i] - (enemy[i].h / 2);
      ex[i] = ex[i] + (enemy[i].w / 2);
      ey[i] = ey[i] + (enemy[i].h / 2);
     }
   }

  for(short num = 1; num < 5; num++)
   {
    if(nx[num] < W_LEFT || nx[num] > W_RIGHT || ny[num] < W_UP || ny[num] > W_DOWN)
     {
      return false;
     }
   }

  for(short b = 0; b < enemy_number; b++)
   {
    for(short num = 0; num < 5; num++)
     {
      if(enemy[b].exists == 1)
       {
        if((nx[num] >= ex[num] && nx[num] <= (ex[num] + (enemy[num].w/2)))
           && (ny[num] >= ey[num] && ny[num] <= (ey[num] + (enemy[num].h/2))))
         {
          enemy[b].destroy();
          return false;
         }
        }
      }
    }

    return true;
 }

bool Bullet::move()
 {

 if(collision(x, y, w, h, angle) == true)
   {
    y -= vely + (speed * vely);
    x += velx + (speed * velx);;
    return true;
   }

  destroy();

  return false;
 }

void Bullet::destroy()
 {
  short fbullets_number;

  /*setting all of this bullet object's info back to zero*/

  exists = 0;
  speed = 0;
  w = 0;
  h = 0;
  angle = 0;
    
  velx = 0;
  vely = 0;
      
  x = 0;
  y = 0;

  /* this next check for existing bullets is so that
     the bullets number only goes as high as the
     high bullet number is...this will save
     some processes on the bullet collision routines
     when the bullet number is lower
  */

 /* for(short i = 0; i < bullets_number; i++)
    {
     if(bullet[i].exists == 1)
       fbullets_number = i;
    }

  bullets_number = fbullets_number;    */

 }

void Bullet::redraw()
 {
  //  draw_sprite(buffer, player1_bmp.sprite, (int)x, (int)y);
  rotate_sprite(buffer, bullets_bmp.sprite, (int)x, (int)y, ftofix(angle));
 }

