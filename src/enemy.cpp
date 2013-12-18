#include <allegro.h>
#include "enemy.h"
#include "collision.h"
#include "bitmap_load.h"
#include "setup.h"
#include "global.h"

//short enemy_number;

Enemy::Enemy()
 {
 }

void Enemy::create()
 {
       speed = 1;
       w = 50;
       h = 50;
      // enemy[a].health = 100;
      // enemy[a].full_health = 100;
       exists = 1;

       y = rand_num(1);  //getting the y random numberr
      
       x = rand_num(0);  //getting the x random number

       enemy_number++;

       
     /*  num = (rand()%1)+1;
       
       if(enemy[a].x <= 400 && num == 1)
       {
        enemy[a].angle = behave[0][0];
       }  
       if(enemy[a].x <= 400 && num == 2)
       {
        enemy[a].angle = behave[2][0];
       }
       else if(enemy[a].x > 400)
       {
        enemy[a].angle = behave[1][0];
       }  
  
       e_collision(a);
  
       if(e_move == true)
       {
       enemy[a].exists = LIVE;
       enemy[a].iter = 1;
       enemy[a].unit = 0;
       enemy[a].type = 0;
       enemy_number++;
       counter = 0;
       
       break;
       }
       else if(e_move == false)
        {
         enemy[a].exists = ENEMY_HIT;
         kill_enemy();
         break;
        }
         
       
       }
      }  */
 }

void Enemy::destroy()
 {
  short fenemy_number;

  speed = 0;
  w = 0;
  h = 0;
  exists = 0;
  y = 0;
  x = 0;

  /* same process below is used for destorying the bullets
     see bullet.cpp */

  for(int i = 0; i < enemy_number; i++)
   {
    if(enemy[i].exists = 1)
     fenemy_number = i;
   }

  enemy_number = fenemy_number;

 }


void Enemy::redraw()
 {
  //  draw_sprite(buffer, player1_bmp.sprite, (int)x, (int)y);
  rotate_sprite(buffer, enemy1_bmp.sprite, (int)enemy[0].x, (int)enemy[0].y, ftofix(enemy[0].angle));
 }

