#ifndef _LOAD_H_
#define _LOAD_H_

#include <allegro.h>

#define PL_MAX_BULLETS 300
#define MAX_ENEMIES 50
#define MAX_BULLETS 10
#define HIT_PLAYER_LEFT (player.x - (PLAYER_WIDTH / 2))
#define HIT_PLAYER_RIGHT (player.x + (PLAYER_WIDTH / 2))
#define HIT_PLAYER_UP (player.y)
#define HIT_PLAYER_DOWN (player.y + PLAYER_HEIGHT)
#define PLAYER_WIDTH 80
#define PLAYER_HEIGHT 80
#define MARGIN 2  //this is the margin on the sides of the screen for when bullets should be deleted

#define DEAD 0x00000000  //binary for 0       
//this means the bullet has not been used yet 
//the enemy is not activated
#define LIVE 0x00000001  //binary for 1  
//this means the bullet is in action
//the enemy is currently activated
#define ENEMY_HIT 0x00000010   //binary for 2
//this means the bullet hit an enemy
//this means the enemy was hit by a player
#define ENEMY_DIE 0x00000011   //binary for 3
//this means the enemy was manually killed
#define GONE 0x00000100     //binary for 4  
//this means the bullet is gone and can't be used until more ammo comes
//this means the enemy was hit by the player and can no longer be activated  

#define LEFT 4 
#define UP 8
#define DOWN 2
#define RIGHT 6

//Bullet/Gun types
#define NORMAL_GUN 0
#define FAST_GUN 1
 
//int behave[3][30]; 

 

#endif


