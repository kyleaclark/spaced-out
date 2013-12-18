#ifndef _SETUP_H_
#define _SETUP_H_

#include <allegro.h>

void setup();
void bitmap_loading();
void ai_loading();
void sound_loading();
void update_counter();

extern int behave[6][30]; 

extern int counter;

extern BITMAP *buffer;   //used as the backbuffer
extern BITMAP *PLAYER_BMP;   //the player's ship
extern BITMAP *BULLET_BMP;   //the normal bullets
extern BITMAP *FAST_BMP;     //the fast bullets
extern BITMAP *ENEMY_BMP;    //the enemy's ship
extern BITMAP *HEALTH_BAR;   //the health bar for the player
extern BITMAP *CONST_BAR;    //the health bar for the player that doesn't change
extern BITMAP *TEXT_BMP;     //used to display text on the health bar
extern BITMAP *STAR1;        
extern BITMAP *STAR2;
extern BITMAP *STAR3;
extern BITMAP *STAR4;
extern BITMAP *STAR5; 
extern BITMAP *RED_BMP;

extern SAMPLE *SHOT_WAV;


#endif


