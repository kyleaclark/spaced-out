#include <allegro.h>
#include <fstream.h>
#include "setup.h"

int behave[6][30]; 

int counter;

BITMAP *buffer;   //used as the backbuffer
BITMAP *PLAYER_BMP;   //the player's ship
BITMAP *BULLET_BMP;   //the normal bullets
BITMAP *FAST_BMP;     //the fast bullets
BITMAP *ENEMY_BMP;    //the enemy's ship
BITMAP *HEALTH_BAR;   //the health bar for the player
BITMAP *CONST_BAR;    //the health bar for the player that doesn't change
BITMAP *TEXT_BMP;     //used to display text on the health bar
BITMAP *STAR1;        
BITMAP *STAR2;
BITMAP *STAR3;
BITMAP *STAR4;
BITMAP *STAR5; 
BITMAP *RED_BMP;

SAMPLE *SHOT_WAV;

void setup()
{
 ofstream filelog("log.txt");
 allegro_init();
 filelog << "allegro_init initialized";
 install_keyboard();
 filelog << "\ninstall_keyboard initialized";
 install_mouse();
 filelog << "\ninstall_mouse initialized";
 install_timer();
 filelog << "\ninstall_timer initialized";
 set_color_depth(32);
 if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 800, 600, 0, 0) == 0)
 {
 filelog << "\nset_color_depth(32) initialized";
 filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) initialized"; 
 }
 else if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) != 0)
 {
 filelog << "\nset_color_depth(32) failed";
 filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) failed";
 
  set_color_depth(24);
  if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) == 0)
  {
  filelog << "\nset_color_depth(24) initialized";
  filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) initialized"; 
  }
  else if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) != 0)
  {
  filelog << "\nset_color_depth(24) failed";
  filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) failed"; 
  
   set_color_depth(16);
   if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) == 0)
   {
   filelog << "\nset_color_depth(16) initialized";
   filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) initialized"; 
   }
   else if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 600, 480, 0, 0) != 0)
   {
   filelog << "\nset_color_depth(16) failed";
   filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) failed";
   filelog << "\nProgram bailing out";
   allegro_exit();
   }
  }
 }
 
 install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
 filelog << "\ninstall_sound(DIGI_AUTODETECT, MIDI_AUTODETECT) initialized";
 install_int_ex( update_counter, BPS_TO_TIMER(60));
 filelog << "\ninstall_int_ex(update_counter, BPS_TO_TIMER(60)) initialized";  
    
 filelog.close();
  
}
 
void bitmap_loading()
{
 buffer     = create_bitmap(SCREEN_W, SCREEN_H);
 TEXT_BMP = create_bitmap(100, 20);
 RED_BMP = create_bitmap(50, 50);
 HEALTH_BAR = load_bitmap("Art\\health_bar.bmp", NULL);
 CONST_BAR = load_bitmap("Art\\health_bar.bmp", NULL);
 
 PLAYER_BMP = load_bitmap("Art\\fighter_plane.bmp", NULL);
 BULLET_BMP = load_bitmap("Art\\normal_bullets.bmp", NULL);
 FAST_BMP = load_bitmap("Art\\plane_bullets.bmp", NULL);
 ENEMY_BMP = load_bitmap("Art\\enemy_1.bmp", NULL);
 STAR1 = load_bitmap("Art\\star1.bmp", NULL);
 STAR2 = load_bitmap("Art\\star2.bmp", NULL);
 STAR3 = load_bitmap("Art\\star3.bmp", NULL);
 STAR4 = load_bitmap("Art\\star4.bmp", NULL);
 STAR5 = load_bitmap("Art\\star5.bmp", NULL);
 
}

void sound_loading()
 {
  SHOT_WAV = load_sample("Sounds\\dissolve.wav");
 }

void ai_loading()
{
  ifstream file_behav1("AI_behaviors\\AI_behavior1.txt");
  for(int a = 0; a < 30; a++)
  {
  file_behav1 >> behave[0][a];
  behave[0][a] = int(.711111111111 * behave[0][a]);
  }
  file_behav1.close(); 
  
  ifstream file_behav2("AI_behaviors\\AI_behavior2.txt");
  for(int a = 0; a < 30; a++)
  {
  file_behav2 >> behave[1][a];
  behave[1][a] = int(.711111111111 * behave[1][a]);
  }
  file_behav2.close(); 
  
  ifstream file_behav3("AI_behaviors\\AI_behavior3.txt");
  for(int a = 0; a < 30; a++)
  {
  file_behav3 >> behave[2][a];
  behave[2][a] = int(.711111111111 * behave[2][a]);
  }
  file_behav3.close();
  
  ifstream file_behav4("AI_behaviors\\AI_behavior4.txt");
  for(int a = 0; a < 30; a++)
  {
  file_behav4 >> behave[3][a];
  behave[3][a] = int(.711111111111 * behave[3][a]);
  }
  file_behav4.close();
  
  ifstream file_behav5("AI_behaviors\\AI_behavior5.txt");
  for(int a = 0; a < 30; a++)
  {
  file_behav5 >> behave[4][a];
  behave[4][a] = int(.711111111111 * behave[4][a]);
  }
  file_behav5.close();
  
  ifstream file_behav6("AI_behaviors\\AI_behavior6.txt");
  for(int a = 0; a < 30; a++)
  {
  file_behav6 >> behave[5][a];
  behave[5][a] = int(.711111111111 * behave[5][a]);
  }
  file_behav6.close();
}
 
void update_counter()
{
     counter++;
}
