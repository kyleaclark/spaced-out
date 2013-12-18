#include <allegro.h>
#include <fstream.h>
#include <iostream.h> 
#include "setup.h"
#include "load.h"

void redraw();
int random_stars(short star_amount);
void player_data();

void enemy_creation();
void kill_enemy();
void enemy_movement();
int enemy_shoot(int num);
//int find_dir(int number, short bad_dir);

void set_player_data();
void set_gun_values();

void set_gun_values();

void update_bullets();
void kill_bullet();
void player_movement();
int collision();
int e_collision(int number);

int rand_mid(short low, short high);

int hb_pixel(BITMAP *bmp, int mid, int color);

void move_up();
void move_down();



struct GUNS
 {
// int type;
 short speed;
 long int ammo;
 short power;
 }gun[2];

struct PLAYERS
 {
 float x;
 float y;
 short exists;
 int type;
 short gun;
 short frame;
 int speed;
 int power;
 int angle;
 int turn;
 long int points;
 short health;
 short full_health;
 float velx;
 float vely;
 }bullet[PL_MAX_BULLETS], player;
  
struct ENEMIES
 {
 float x;
 float y;
 short exists;
 int type;
 short frame;
 int speed;
 int power;
 int width;
 int height;
// short dir;   //this is for passing the direction of which way the enemy is going to move
// short tries; //this is to have the enemy try a different move if a move is "bad"
 int angle;
 int turn;
 float velx;
 float vely;
 int iter;
 int unit;
 short health;
 short full_health;
 }e_bullet[MAX_BULLETS], enemy[MAX_ENEMIES];
 
int enemy_number = 1;  //to show what the value is of the max enemy
long int pl_bullet_number = 0;   //to show how many bullets have been shot
long int e_bullet_number = 0;   //this is to see how many for loop iterations need to take place
bool pl_move, e_move;  //to see if a move is valid by either the player or enemy
//bool creation;
int var = 0;

float oldred;
float tored;
float newred;

int selected_gun = 0; //to show the value of what gun is being selected by the player


long int check;

int num;
short rand_num = 1; //for the incr/decr number being added to var
bool incr = 1;      //to see whether rand_num should be incr or decr

char printstr[50];



int main() 
{ 
 setup(); 
 bitmap_loading(); 
 sound_loading();
 ai_loading();
 
 set_gun_values();
 set_player_data();
 
 for(int a = 0; a < PL_MAX_BULLETS; a++)
  {
  bullet[a].speed = gun[selected_gun].speed;
  }

 enemy_creation();
 redraw();
 counter = 0;
 // Looping until the ESCape key is pressed.
 while(! key[KEY_ESC])
 {
 
 if(keypressed())
 {
 player_movement();
 }
 update_bullets();
 if(counter > 180)
 {
 enemy_creation();
 counter = 0;
 }    
 enemy_movement();
 redraw();
 }
    
/* counter = 0;
  while(counter < 60)
  {
  //simulate_keypress(key[KEY_SPACE]);
  player_movement();
  update_bullets();
  enemy_movement();
  redraw();
  check++;
  }
  ofstream filelog("log.txt");
  filelog << check;
  filelog.close();  */
 
 // Exit program. 
 allegro_exit();
 return 0;     
}     

// Some Allegro magic to deal with WinMain().
END_OF_MAIN();

 
void update_bullets()
{
 float x[5];
  float y[5];
  float ex[enemy_number][5];
  float ey[enemy_number][5];


for(int i = 0; i < enemy_number; i++)
 {
 
  if(enemy[i].exists == LIVE)
  {
  ex[i][0] = enemy[i].x + (enemy[i].width / 2); 
  ey[i][0] = enemy[i].y + (enemy[i].height / 2);
  ex[i][1] = ex[i][0] - (enemy[i].width / 2); 
  ey[i][1] = ey[i][0] - (enemy[i].height / 2); 
  ex[i][2] = ex[i][0] - (enemy[i].width / 2);; 
  ey[i][2] = ey[i][0] + (enemy[i].height / 2); 
  ex[i][3] = ex[i][0] + (enemy[i].width / 2); 
  ey[i][3] = ey[i][0] - (enemy[i].height / 2); 
  ex[i][4] = ex[i][0] + (enemy[i].width / 2);
  ey[i][4] = ey[i][0] + (enemy[i].height / 2);
  }
 }
 
 x[0] = player.x + (PLAYER_WIDTH / 2); //+ 40 * sin(player.angle);
 y[0] = player.y + (PLAYER_HEIGHT / 2); //- 40; //- 40 * cos(player.angle);
 x[1] = x[0] - 40; //* sin(player.angle);
 y[1] = y[0] - 40; //* -cos(player.angle);
 x[2] = x[0] - 40; //* sin(player.angle);
 y[2] = y[0] + 40; //* -cos(player.angle);
 x[3] = x[0] + 40; //* sin(player.angle);
 y[3] = y[0] - 40; //* -cos(player.angle);
 x[4] = x[0] + 40; //* sin(player.angle);
 y[4] = y[0] + 40; //* -cos(player.angle);

   // Delete bullets that hit player
   for(int a = 0; a < MAX_BULLETS; a++)
    {
     if(e_bullet[a].exists == LIVE)
      {
      if((e_bullet[a].x >= HIT_PLAYER_LEFT && e_bullet[a].x <= HIT_PLAYER_RIGHT) 
         && (e_bullet[a].y >= HIT_PLAYER_UP && e_bullet[a].y <= HIT_PLAYER_DOWN))
        {
        e_bullet[a].exists = ENEMY_HIT;
        }  
       }  
     }    
     
   for(int a = 0; a < e_bullet_number; a++)
    {
     for(short num = 0; num < 5; num++)
      { 
       if(e_bullet[a].exists == LIVE)
        {      
        if((e_bullet[a].x >= x[num] && e_bullet[a].x <= (x[num] + (PLAYER_WIDTH/2))) 
          && (e_bullet[a].y >= y[num] && e_bullet[a].y <= (y[num] + (PLAYER_HEIGHT/2))))
          {
          e_bullet[a].exists = ENEMY_HIT;
          }
        }
      }
     }
     
  // Delete bullets that go past screen
  for(int a = 0; a < e_bullet_number; a++)
    {
     if(e_bullet[a].exists == LIVE)
      { 
      if(e_bullet[a].x <= MARGIN || e_bullet[a].x >= SCREEN_W - MARGIN
        || e_bullet[a].y <= MARGIN || e_bullet[a].y >= SCREEN_H - MARGIN)
       {
       e_bullet[a].exists = DEAD;
       }
      }
    }
    
  // Update the coordinates of enemy bullets
   for(int a = 0; a < e_bullet_number; a++)
    {
     if(e_bullet[a].exists == LIVE)
      { 
       e_bullet[a].y += e_bullet[a].speed;
      }
    }     
          
    ////////////////Player Data///////////////////////
    
    
   // Delete bullets that hit enemies
   for(long int a = 0; a < pl_bullet_number; a++)
    {
    for(int b = 0; b < enemy_number; b++)
     {
     for(short num = 0; num < 5; num++)
      { 
       if(bullet[a].exists == LIVE && enemy[b].exists == LIVE)
        {      
        if((bullet[a].x >= ex[b][num] && bullet[a].x <= (ex[b][num] + (enemy[b].width/2))) 
          && (bullet[a].y >= ey[b][num] && bullet[a].y <= (ey[b][num] + (enemy[b].height/2))))
          {
          stop_sample(SHOT_WAV);
          bullet[a].exists = GONE;
          
          kill_bullet();
          enemy[b].health -= gun[bullet[a].type].power;
          player.points += 1; 
          
          if(enemy[b].health == 0)
          {
          enemy[b].exists = ENEMY_HIT;       
          kill_enemy();
          player.points += 3;
          }
          
          play_sample(SHOT_WAV, 255, 255, 1000, 0);
          
          }
        }
       }
      }
     }      
     
  // Delete bullets that go past screen
  for(long int a = 0; a < pl_bullet_number; a++)
    {
     if(bullet[a].exists == LIVE)
      { 
      if(bullet[a].x <= MARGIN || bullet[a].x >= SCREEN_W - MARGIN
        || bullet[a].y <= MARGIN || bullet[a].y >= SCREEN_H - MARGIN)
       {
       bullet[a].exists = GONE;
       kill_bullet();
       }
      }
    }       
    
  // Update the coordinates of player bullets
   for(long int a = 0; a < pl_bullet_number; a++)
    {
     if(bullet[a].exists == LIVE)
      {     
      bullet[a].y -= bullet[a].vely + (bullet[a].speed * bullet[a].vely);
      bullet[a].x += bullet[a].velx + (bullet[a].speed * bullet[a].velx);;
      }
    }    
}

void player_movement()
 {
  if(key[KEY_LEFT])
   { 
   collision();
    if(pl_move == true)
    {
     if(player.angle <= 256 && player.angle - player.turn >= 0 )
     {
     player.angle -= player.turn;
     }
     else if(player.angle == 256 || player.angle == 0)
     {
     player.angle = 256 - player.turn;
     }     
    }
   }
  //to move directly left
  else if(key[KEY_COMMA])
   {   
   collision();
    if(pl_move == true)
    {
     player.x -= (player.speed/2);   
    }
   }
  else if(key[KEY_RIGHT])
   { 
   collision();
    if(pl_move == true)
    {
     if(player.angle + player.turn <= 256 && player.angle >= 0)
     {
     player.angle += player.turn;
     }     
     else if(player.angle == 256 || player.angle == 0)
     {
     player.angle = player.turn;
     } 
    }
   }
   //to move directly right
  else if(key[KEY_STOP])  //period key
   {
   collision();
    if(pl_move == true)
    {
     player.x += (player.speed/2);   
    }
   }
  else if(key[KEY_UP])
   {
   move_up();
   collision();
   if(pl_move == false)
    {
    move_down();
    }
   }
  else if(key[KEY_DOWN])
   {   
   move_down();
   collision();
   if(pl_move == false)
    {
    move_up();
    }
   }
   
  else if(key[KEY_SPACE] && gun[selected_gun].ammo > 0)
   {
    for(long int a = 0; a <= pl_bullet_number+1; a++)
     {
      if(bullet[a].exists == DEAD)
       {
       
       bullet[a].exists = LIVE;
       bullet[a].angle = player.angle;
    
       bullet[a].velx = sin(bullet[a].angle); 
       bullet[a].vely = cos(bullet[a].angle); 
      
       bullet[a].x = player.x + (PLAYER_WIDTH / 2) + 40 * sin(player.angle);
       bullet[a].y = player.y + (PLAYER_HEIGHT / 2) - 40 * cos(player.angle);
    
       bullet[a].y -= bullet[a].vely + (bullet[a].speed * bullet[a].vely);
       bullet[a].x += bullet[a].velx + (bullet[a].speed * bullet[a].velx);
 
       gun[selected_gun].ammo--;
       pl_bullet_number++;
   //    clear_keybuf();
       break;
       }
      }
   }
   
/*  else if(key[KEY_G])
   {
  // clear_keybuf();
   
   selected_gun = FAST_GUN;
   player.gun = FAST_GUN;
   for(long int a = pl_bullet_number; a < (gun[selected_gun].ammo + pl_bullet_number); a++)
    {
    if(bullet[a].exists == DEAD)
    {
    bullet[a].speed = gun[selected_gun].speed;
    bullet[a].type = selected_gun;
    }
    }
   }  */
   
  else if(key[KEY_V])
   {
  // clear_keybuf();
   
   selected_gun = FAST_GUN;
   player.gun = FAST_GUN;
   for(long int a = pl_bullet_number; a < (gun[selected_gun].ammo + pl_bullet_number); a++)
    {
    if(bullet[a].exists == DEAD)
    {
    bullet[a].speed = gun[selected_gun].speed;
    bullet[a].type = selected_gun;
    }
    }
   }  
 
  else if(key[KEY_N])
   {
  // clear_keybuf();
   
   selected_gun = NORMAL_GUN;
   player.gun = NORMAL_GUN;
   for(long int a = pl_bullet_number; a < (gun[selected_gun].ammo + pl_bullet_number); a++)
    {
    if(bullet[a].exists == DEAD)
    {
    bullet[a].speed = gun[selected_gun].speed;
    bullet[a].type = selected_gun;
    }
    }
   }  
 }
 
void move_up()
 {
  player.velx = sin(player.angle);  
  player.vely = cos(player.angle);  
    
  player.y -= player.vely + (player.speed * player.vely);
  player.x += player.velx + (player.speed * player.velx);
  
  collision();
  if(pl_move == false)
  {
  move_down();
  }

 }
 
void move_down()
 {
  player.velx = sin(player.angle);  
  player.vely = cos(player.angle);   
    
  player.y += player.vely + (player.speed * player.vely);
  player.x -= player.velx + (player.speed * player.velx);
  
  collision();
  if(pl_move == false)
  {
  move_up();
  }
 }
 
int collision()
 {
 float x[5];
 float y[5];
 float ex[enemy_number][5];
 float ey[enemy_number][5];
 
 pl_move = true;
 
 for(int i = 0; i < enemy_number; i++)
 {
  if(enemy[i].exists == LIVE)
  {
  ex[i][0] = (enemy[i].x - sin(enemy[i].angle)) + (enemy[i].width / 2); 
  ey[i][0] = (enemy[i].y + cos(enemy[i].angle)) + (enemy[i].height / 2);
  ex[i][1] = ex[i][0] - (enemy[i].width / 2); 
  ey[i][1] = ey[i][0] - (enemy[i].height / 2); 
  ex[i][2] = ex[i][0] - (enemy[i].width / 2);; 
  ey[i][2] = ey[i][0] + (enemy[i].height / 2); 
  ex[i][3] = ex[i][0] + (enemy[i].width / 2); 
  ey[i][3] = ey[i][0] - (enemy[i].height / 2); 
  ex[i][4] = ex[i][0] + (enemy[i].width / 2);
  ey[i][4] = ey[i][0] + (enemy[i].height / 2);
  }
 }
 
 x[0] = (player.x - sin(player.angle)) + (PLAYER_WIDTH / 2); //+ 40 * sin(player.angle);
 y[0] = (player.y + cos(player.angle)) + (PLAYER_HEIGHT / 2); //- 40; //- 40 * cos(player.angle);
 x[1] = x[0] - 40; //* sin(player.angle);
 y[1] = y[0] - 40; //* -cos(player.angle);
 x[2] = x[0] - 40; //* sin(player.angle);
 y[2] = y[0] + 40; //* -cos(player.angle);
 x[3] = x[0] + 40; //* sin(player.angle);
 y[3] = y[0] - 40; //* -cos(player.angle);
 x[4] = x[0] + 40; //* sin(player.angle);
 y[4] = y[0] + 40; //* -cos(player.angle);

 for(int num = 1; num < 5; num++)
  {
  if(x[num] <= MARGIN || x[num] >= SCREEN_W - (MARGIN + PLAYER_WIDTH)
     || y[num] <= MARGIN || y[num] >= SCREEN_H - (MARGIN + PLAYER_HEIGHT)) 
       {
       pl_move = false;
       break;
       } 
  }
 for(int a = 0; a < enemy_number; a++)
  {
   if(enemy[a].exists == LIVE)
    {

      if(x[3] >= ex[a][1] && x[1] <= ex[a][3]
        && y[1] <= ey[a][2] && y[4] >= ey[a][3])
        {
        e_move = false;
        enemy[a].exists = ENEMY_DIE; 
        vline(HEALTH_BAR, player.health+7, 0, 20, makecol(255, 0, 0));
        hb_pixel(HEALTH_BAR, player.health+7, makecol(255, 0, 255));
        player.health -= 5;
        break;
        }
      }
   }      
  
   return pl_move; 
  }
       
void redraw()
 {
 int new_angle = 0;
 float delta_x = 0, delta_y = 0;
 short alpha_level;
// bool new_stars = 0;
// short star_amount = 0;

 float hbar_x = 0, hbar_y = 0;
 
 clear_bitmap(buffer);
/* if(counter < 20)
 {
 star_amount = 1+rand()%20;
 random_stars(star_amount);
 }
 else if(counter >= 20 && counter < 40)
 {
// new_stars = 1;
 star_amount = 1+rand()%15;
 random_stars(star_amount);
// counter = 0;
 }
 else if(counter >= 40)
 {
 star_amount = 1+rand()%10;
 random_stars(star_amount);
  if(counter >= 60)
   counter = 0;
 }           */
                     
/*  switch (counter)	
  {	   
   case 1: counter < 20;
    amount = 3;
    random_stars(amount);
  //  break;	
    
   case 2: counter >= 20 && counter < 40;
    amount = 2;
    random_stars(amount);
  //  break;
   
   case 3: counter >= 40;
    amount = 1;
    random_stars(amount);
    counter = 0;
  //  break;		 

   default:
    break; 
   }    */
   
// hbar_x = (player.x + (10 * (sin(player.angle)));
 //hbar_y = (player.y + (PLAYER_HEIGHT * (cos(player.angle)));
 
 if(player.angle == 0)
  {
  masked_blit(PLAYER_BMP, buffer, 0, 0, (int)player.x, (int)player.y, SCREEN_W, SCREEN_H);
//  masked_blit(HEALTH_BAR, buffer, 0, 0, (int)player.x+10, (int)player.y+PLAYER_HEIGHT, SCREEN_W, SCREEN_H);
  }
 else if(player.angle != 0)
  {
  rotate_sprite(buffer, PLAYER_BMP, (int)player.x, (int)player.y, itofix(player.angle));
 // rotate_sprite(buffer, HEALTH_BAR, (int)hbar_x, (int)hbar_y, itofix(player.angle));
  }
 
 //draw_sprite(buffer, PLAYER_BMP, player.x, player.y);
 for(int a = 0; a < pl_bullet_number; a++)
     {
      if(bullet[a].exists == LIVE)
       { 
        if(bullet[a].type == NORMAL_GUN)
       // if(player.angle == 0)
      // masked_blit(BULLET_BMP, buffer, 0, 0, (int)bullet[a].x, (int)bullet[a].y, SCREEN_W, SCREEN_H);
       rotate_sprite(buffer, BULLET_BMP, (int)bullet[a].x, (int)bullet[a].y, itofix(bullet[a].angle));
        else if(bullet[a].type == FAST_GUN)
       // masked_blit(FAST_BMP, buffer, 0, 0, (int)bullet[a].x, (int)bullet[a].y, SCREEN_W, SCREEN_H);
        rotate_sprite(buffer, FAST_BMP, (int)bullet[a].x, (int)bullet[a].y, itofix(bullet[a].angle));
        
                
       }
      }
     
  for(int a = 0; a < e_bullet_number; a++)
   {
    if(e_bullet[a].exists == LIVE)
     rotate_sprite(buffer, FAST_BMP, (int)e_bullet[a].x, (int)e_bullet[a].y, itofix(e_bullet[a].angle));
    }
               
    for(int a = 0; a < enemy_number; a++)
     {
       if(enemy[a].exists == LIVE)
       {
        if(enemy[a].x <= player.x && enemy[a].y <= player.y)
         {
           
            delta_x = (player.x - enemy[a].x);
            delta_y = (player.y - enemy[a].y);
           
           new_angle = int(64 + (atan(delta_y/delta_x)));                  
           
         }
        else if(enemy[a].x <= player.x && enemy[a].y >= player.y)
         {
         delta_x = (player.x - enemy[a].x);
            delta_y = (player.y - enemy[a].y);
          new_angle = int(64 + (atan(delta_y/delta_x))); 
         }
        else if(enemy[a].x > player.x && enemy[a].y < player.y)
         {
          delta_x = (player.x - enemy[a].x);
            delta_y = (player.y - enemy[a].y);
          new_angle = int(192 + (atan(delta_y/delta_x))); 
         }
        else if(enemy[a].x > player.x && enemy[a].y > player.y)
         {
          delta_x = (player.x - enemy[a].x);
            delta_y = (player.y - enemy[a].y);
          new_angle = int(192 + (atan(delta_y/delta_x))); 
         } 
      // masked_blit(ENEMY_BMP, buffer, 0, 0, (int)enemy[a].x, (int)enemy[a].y, SCREEN_W, SCREEN_H);
       //draw_sprite(buffer, ENEMY_BMP, enemy[a].x, enemy[a].y);
       
      // rectfill(RED_BMP, 0, 0, 50, 50, makecol(255, 0, 0));
       
     //   set_alpha_blender();
      // set_add_blender(5, 0, 0, 225);
     //  set_dissolve_blender(132, 132, 132, 0);
        
     //   draw_sprite(RED_BMP, ENEMY_BMP, 0, 0);   
       
    //   draw_lit_sprite(RED_BMP, ENEMY_BMP, 0, 0, makecol(132, 132, 132));
       
    //   set_multiply_blender(132, 132, 132, 0);
      
     //  draw_lit_sprite(RED_BMP, ENEMY_BMP, 0, 0, makecol(132, 132, 132));
       
    
//draw_gouraud_sprite(RED_BMP, ENEMY_BMP, 0, 0, makecol(255, 225, 225), makecol(255, 225, 255), makecol(255, 0, 0), makecol(255, 0, 255));
       
       set_trans_blender( 255, 0, 0, 0 ); 
       
 // alpha_level = static_cast< int >( static_cast< double >( 100 - enemy[a].health )/static_cast< double >( 100 ) * 255.0 );
  
 //  alpha_level = (255*14-enemy[a].health)/14;
 
 tored=(255*enemy[a].full_health-enemy[a].health)/enemy[a].full_health;
 newred = tored - (255 * ((enemy[a].health*2.5)/(enemy[a].full_health*2.5)));
// newred=255-((255-oldred)-(255-tored));
 oldred=newred;
            
//int alpha_level = static_cast< int >( static_cast< double >( maxhp - hp )/static_cast< double >( maxhp ) * 255.0 );
draw_lit_sprite( RED_BMP, ENEMY_BMP, 0, 0, (int)newred);
       
       
       
    /*    if(player.angle > 0 && player.angle < 90 && enemy[a].y < player.y && enemy[a].x <= player.x) 
         rotate_sprite(buffer, ENEMY_BMP, (int)enemy[a].x, (int)enemy[a].y, itofix(new_angle));
        else 
         rotate_sprite(buffer, ENEMY_BMP, (int)enemy[a].x, (int)enemy[a].y, itofix(new_angle));  */  
         
        rotate_sprite(buffer, RED_BMP, (int)enemy[a].x, (int)enemy[a].y, itofix(new_angle));  
           
       }
      }
 /*for(int a = 0; a < MAX_ENEMIES; a++)
  {
      if(enemy[a].exists == LIVE)
       {
       // masked_blit(ENEMY_BMP, buffer, 0, 0, enemy[a].x, enemy[a].y, SCREEN_W, SCREEN_H);
       draw_sprite(buffer, ENEMY_BMP, enemy[a].x, enemy[a].y);
       }
  }   */
 player_data();
 blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); 
 } 
 
int random_stars(short star_amount)
 {
 unsigned short x = 0;
 unsigned short y = 0;
 short left_x[40];
 short left_y[40];
 char num = 0;
 
 y = 1+rand()%20;
 
 for(short star = 0; star < 40; star++)
  {
  x += 1+rand()%80;
   if(x > 785)
    {
    y += 1+rand()%60;
    x = 1+rand()%40;
    }
   
  left_x[star] = x;
  left_y[star] = y;
  
  } 
  
  for(short star = 0; star < 40; star++)
   {
    num = 1+rand()%(5-1+1);
    if(num == 1)
     {
   //  putpixel(buffer, x, y, makecol(100, 100, 100));
     draw_sprite(buffer, STAR1, left_x[star], left_y[star]);
     }
    else if(num == 2)
     {
     draw_sprite(buffer, STAR2, left_x[star], left_y[star]);
     }
    else if(num == 3)
     {
     draw_sprite(buffer, STAR3, left_x[star], left_y[star]);
     }
    else if(num == 4)
     {
     draw_sprite(buffer, STAR4, left_x[star], left_y[star]);
     }
    } 
 }
 
void player_data()
 {
 
  if(selected_gun == NORMAL_GUN)
   {
   textout_centre(buffer, font, "Default Gun in Use", 650, 380, makecol(100, 100, 100));
   sprintf(printstr, "Ammo Remaining %d", gun[selected_gun].ammo);
   textout_centre(buffer, font, printstr, 650, 390, makecol(100, 100, 100));
   }
  else if(selected_gun == FAST_GUN)
   {
   textout_centre(buffer, font, "Rapid Gun in Use", 650, 380, makecol(100, 100, 100)); 
   sprintf(printstr, "Ammo Remaining %d", gun[selected_gun].ammo);
   textout_centre(buffer, font, printstr, 650, 390, makecol(100, 100, 100));
   }
   
   sprintf(printstr, "Total Points %d", player.points);
   textout_centre(buffer, font, printstr, 650, 440, makecol(100, 100, 100));
   
  // rectfill(HEALTH_BAR, 0, 0, 60, 20, makecol(0, 255, 0));
 //ellipsefill(HEALTH_BAR, 30, 8, 30, 8, makecol(0, 225, 0));
  
  masked_blit(CONST_BAR, HEALTH_BAR, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
 
  if(player.health == 100)
 // vline(HEALTH_BAR, player.health+7, 0, 20, makecol(255, 0, 255));
  floodfill(HEALTH_BAR, player.health+6, 8, makecol(0, 225, 0));
 // floodfill(HEALTH_BAR, player.health+8, 8, makecol(255, 0, 0));
 
  else if(player.health < 100 && player.health > 0)
  {
  vline(HEALTH_BAR, player.health+7, 0, 20, makecol(255, 0, 255));
  floodfill(HEALTH_BAR, player.health+6, 8, makecol(0, 225, 0));
  floodfill(HEALTH_BAR, player.health+8, 8, makecol(255, 0, 0));
  }
  
  else if(player.health == 0)
  floodfill(HEALTH_BAR, player.health+6, 8, makecol(225, 0, 0));
    
  clear_to_color(TEXT_BMP, makecol(255, 0, 255));
  
  text_mode(-1);
 
  
  
 // textprintf_centre(TEXT_BMP, font, 0, 5, makecol(0, 225, 0), "Health %d", "100");

  textprintf_centre(TEXT_BMP, font, 50, 5, makecol(0, 0, 235), "Health %d", player.health);
  
 // text_mode(0);
  
  masked_blit(TEXT_BMP, HEALTH_BAR, 0, 0, 7, 0, SCREEN_W, SCREEN_H);

  masked_blit(HEALTH_BAR, buffer, 0, 0, 650, 400, SCREEN_W, SCREEN_H);

 }   
   
void set_player_data()
 {
  player.y = SCREEN_H / 2;
  player.x = SCREEN_W / 2;
  player.speed = 5;
  player.gun = NORMAL_GUN;
  player.angle = 0;
  player.turn = 4;
  player.health = 100;
  player.points = 0;
 } 
     
void set_gun_values()
 {  
  gun[NORMAL_GUN].speed = 3;
  gun[NORMAL_GUN].power = 7;
  gun[NORMAL_GUN].ammo = 200;
  gun[FAST_GUN].speed = 4;
  gun[FAST_GUN].power = 5;
  gun[FAST_GUN].ammo = 200;
 } 
 
void enemy_creation()
 {
 int num = 0;
 
  for(int a = 0; a < MAX_ENEMIES; a++)
     {
      if(enemy[a].exists == DEAD)
       {
       enemy[a].speed = 1;
       enemy[a].width = 50;
       enemy[a].height = 50; 
       enemy[a].health = 100; 
       enemy[a].full_health = 100;     
       enemy[a].exists = LIVE;

       rand_mid(1, 10);
       enemy[a].y = var * 15; 
      
       rand_mid(1, 10);       
       enemy[a].x = var * 70;
       
       num = (rand()%1)+1;
       
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
      }
  }
 
void enemy_movement()
 {
 short imperfection = 0;
 
  for(int a = 0; a < enemy_number; a++)
   {
    if(enemy[a].exists == LIVE)
    {
    
    e_collision(a);
    
    if(e_move == false)
     kill_enemy();
     
    else if(e_move == true)
    {
    
    enemy[a].angle = behave[enemy[a].type][enemy[a].unit];
    enemy[a].iter++;
    
    if(enemy[a].iter++ >= 20)
     {
      if(enemy[a].unit != 29)
       {
       enemy[a].unit++;
       enemy[a].iter = 0;
    //   enemy_shoot(a);
       }
     }
    
    enemy[a].velx = sin(enemy[a].angle);
    enemy[a].vely = cos(enemy[a].angle);
    
    imperfection = (1+rand()%100) / 100;
   // imperfection = 0;
    enemy[a].x -= enemy[a].velx + imperfection + (enemy[a].speed * enemy[a].velx);
    
    imperfection = (1+rand()%100) / 100;
   // imperfection = 0;   
    enemy[a].y += enemy[a].vely + imperfection + (enemy[a].speed * enemy[a].vely);
   
    } 
    
    
           
    }
   }
  }
  
int enemy_shoot(int num)
 {
   for(long int a = 0; a <= e_bullet_number+1; a++)
     {
      if(e_bullet[a].exists == DEAD)
       {
       
       e_bullet[a].exists = LIVE;
       e_bullet[a].angle = enemy[num].angle;
       e_bullet[a].speed = 2;
    
       e_bullet[a].velx = sin(e_bullet[a].angle); 
       e_bullet[a].vely = cos(e_bullet[a].angle); 
      
       e_bullet[a].x = enemy[num].x + (enemy[num].width / 2) + 40 * sin(e_bullet[a].angle);
       e_bullet[a].y = enemy[num].y + (enemy[num].height / 2) - 40 * cos(e_bullet[a].angle);
    
       e_bullet[a].y -= e_bullet[a].vely + (e_bullet[a].speed * e_bullet[a].vely);
       e_bullet[a].x += e_bullet[a].velx + (e_bullet[a].speed * e_bullet[a].velx);
 
    //   gun[selected_gun].ammo--;
       e_bullet_number++;
   //    clear_keybuf();
       break;
       }
      }
 }

int hb_pixel(BITMAP *bmp, int mid, int color)
 {
  putpixel(bmp, mid, 0, color);
  putpixel(bmp, mid, 19, color);
 }   
 
int e_collision(int number)
 {
  float x[5];
  float y[5];
  float ex[enemy_number][5];
  float ey[enemy_number][5];
 
 e_move = true;
 
 for(int i = 0; i < enemy_number; i++)
 { 
  if(enemy[i].exists == LIVE)
  {
/* |-----|
   |1   2|
   |  O  |
   |4   3|
   |-----| */ 
  ex[i][0] = (enemy[i].x - sin(enemy[i].angle)) + (enemy[i].width / 2);    //0.0 (midpoint 0)
  ey[i][0] = (enemy[i].y + cos(enemy[i].angle)) + (enemy[i].height / 2);
  ex[i][1] = ex[i][0] - (enemy[i].width / 2);   //1.1   (corner 1)
  ey[i][1] = ey[i][0] - (enemy[i].height / 2);  
  ex[i][2] = ex[i][0] - (enemy[i].width / 2);;  //1.4   (corner 4)
  ey[i][2] = ey[i][0] + (enemy[i].height / 2);  
  ex[i][3] = ex[i][0] + (enemy[i].width / 2);   //2.2    (corner 2)
  ey[i][3] = ey[i][0] - (enemy[i].height / 2); 
  ex[i][4] = ex[i][0] + (enemy[i].width / 2);   //3.3    (corner 3)
  ey[i][4] = ey[i][0] + (enemy[i].height / 2); 
  }
 }
 
 x[0] = (player.x - sin(player.angle)) + (PLAYER_WIDTH / 2); //+ 40 * sin(player.angle);
 y[0] = (player.y + cos(player.angle)) + (PLAYER_HEIGHT / 2); //- 40; //- 40 * cos(player.angle);
 x[1] = x[0] - 40; //* sin(player.angle);
 y[1] = y[0] - 40; //* -cos(player.angle);
 x[2] = x[0] - 40; //* sin(player.angle);
 y[2] = y[0] + 40; //* -cos(player.angle);
 x[3] = x[0] + 40; //* sin(player.angle);
 y[3] = y[0] - 40; //* -cos(player.angle);
 x[4] = x[0] + 40; //* sin(player.angle);
 y[4] = y[0] + 40; //* -cos(player.angle);

  for(short num = 0; num < 5; num++)
   { 
   
   if((ey[number][num] <= y[num] + PLAYER_HEIGHT) 
           && (ey[number][num] + enemy[number].height >= y[num])
           && (ex[number][num] <= x[num] + PLAYER_WIDTH)
           && (ex[number][num] + enemy[number].width >= x[num]))
       {
       e_move = false;
       enemy[number].exists = ENEMY_DIE; 
       //creating the health bar b/c the player loses damage here
       vline(HEALTH_BAR, player.health+7, 0, 20, makecol(255, 0, 0));
       hb_pixel(HEALTH_BAR, player.health+7, makecol(255, 0, 255));
       player.health -= 5;
       break;
       }
      //if the enemy goes up too far on the screen
   else if(ey[number][num] <= MARGIN)
       {
       e_move = false;
       enemy[number].exists = ENEMY_DIE;
       break;
       }
      //if the enemy tries to move too far down (this lets the enemy die)
   else if(ey[number][num] >= SCREEN_H - MARGIN)
       {
       e_move = false;
       enemy[number].exists = ENEMY_DIE;
       break;
       }
       //if the enemy tries to move too far to the left
   else if(ex[number][num] <= MARGIN)
        {
        e_move = false;
        enemy[number].exists = ENEMY_DIE;
        break;
        }
       //if the enemy tries to move too far to the right
   else if(ex[number][num] >= SCREEN_W - MARGIN)
        {
        e_move = false;
        enemy[number].exists = ENEMY_DIE;
        break;
        }
       
    }
    
  if(e_move == true)
   {
   for(long e = 0; e < enemy_number; e++)
   { 
    for(short num = 0; num < 5; num++)
    {
    if(e != number)
    {
   
    if((ey[number][num] <= ey[e][num] + enemy[e].height) 
           && (ey[number][num] + enemy[number].height >= ey[e][num])
           && (ex[number][num] <= ex[e][num] + enemy[e].width)
           && (ex[number][num] + enemy[number].width >= ex[e][num]))
       {
       e_move = false;
       enemy[number].exists = ENEMY_DIE; 
       kill_enemy();
       break;
       }
   /* if((ey[number][num] <= y[num] + PLAYER_HEIGHT + 1) 
           && (ey[number][num] + enemy[number].height >= y[num] - 1)
           && (ex[number][num] <= x[num] + PLAYER_WIDTH + 1)
           && (ex[number][num] + enemy[number].width >= x[num] - 1)  */ 
 /*   if((ey[e][num] <= enemy[e].y && ey[e][num] >= enemy[e].y + enemy[e].height)
       && (ex[e][num] >= enemy[e].x && ex[e][num] <= enemy[e].x + enemy[e].width))
     {
       e_move = false;
       enemy[number].exists = ENEMY_DIE;
       kill_enemy() 
       break; 
     }   */        
    }
   }
  }
  }
     
  return e_move;
  
}      
      
int rand_mid(short low, short high)
{
   srand(time(NULL));
   var = (unsigned int) low+rand()%(high-low+1);
   
   if(var == 1)
    {
    var = 10;
    var -= rand_num;
    }
   else if(var == 2)
    {
    var = 9;
    var -= rand_num;
    }
   else if(var == 3)
    {
    var = 8;
    var -= rand_num;
    }
   else if(var == 4)
    {
    var = 7;
    var -= rand_num;
    }
   else if(var == 5)
    {
    var = rand_num;
    }
   else if(var == 6)
    {
    var = 4;
    var += rand_num;
    }
   else if(var == 7)
    {
    var = 3;
    var += rand_num;
    }
   else if(var == 8)
    {
    var = 2;
    var += rand_num;
    }
   else if(var == 9)
    {
    var = 1;
    var += rand_num;
    }
   else if(var == 10)
    {
    var = rand_num*2;
    }
   
   //rand_num++;
   
   if(incr == 1 && rand_num < 5)
    rand_num++;
   else if(incr == 1 && rand_num == 5)
    {
    rand_num--;
    incr = 0;
    }
   else if(incr == 0 && rand_num > 1)
    rand_num--;
   else if(incr == 0 && rand_num == 1)
    {
    rand_num++;
    incr = 1;
    }

   return var, incr, rand_num;

}

void kill_enemy()
 {
  for(int a = 0; a < enemy_number; a++)
   {
   if(enemy[a].exists == ENEMY_HIT)
    {
    enemy[a].exists = GONE;
    enemy[a].y = DEAD;
    enemy[a].x = DEAD;
    enemy[a].speed = DEAD;
    enemy[a].width = DEAD;
    enemy[a].height = DEAD;
  //  enemy_creation();
  counter += 10;
    }
   else if(enemy[a].exists == ENEMY_DIE)
    {
    enemy[a].exists = DEAD;
    enemy[a].y = DEAD;
    enemy[a].x = DEAD;
    enemy[a].speed = DEAD;
    enemy[a].width = DEAD;
    enemy[a].height = DEAD;
  //  enemy_creation();
  counter += 10;
    }
   }
 }
 
void kill_bullet()
 {
  for(int a = 0; a < pl_bullet_number; a++)
  {
   if(bullet[a].exists == GONE)
   {
   for(int b = 1; b < pl_bullet_number - a; b++)
   {
    if(bullet[a+b].y < bullet[a].y + 10 && bullet[a+b].x == bullet[a].x)
    {
  //  bullet[a+b].exists = DEAD;
    bullet[a+b].x = GONE;
    bullet[a+b].y = GONE;
    bullet[a+b].exists = GONE;
    }
   }
 //  bullet[a].exists = DEAD;
   bullet[a].x = GONE;
   bullet[a].y = GONE;
   }
  }
 }
