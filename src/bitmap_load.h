#include "load.h"
#include "setup.h"

void bitmap_loading();

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

void bitmap_loading()
{
 buffer     = create_bitmap(SCREEN_W, SCREEN_H);
 TEXT_BMP = create_bitmap(100, 20);
 HEALTH_BAR = load_bitmap("health_bar.bmp", NULL);
 CONST_BAR = load_bitmap("health_bar.bmp", NULL);
 
 PLAYER_BMP = load_bitmap("fighter_plane.bmp", NULL);
 BULLET_BMP = load_bitmap("normal_bullets.bmp", NULL);
 FAST_BMP = load_bitmap("plane_bullets.bmp", NULL);
 ENEMY_BMP = load_bitmap("enemy_1.bmp", NULL);
 STAR1 = load_bitmap("star1.bmp", NULL);
 STAR2 = load_bitmap("star2.bmp", NULL);
 STAR3 = load_bitmap("star3.bmp", NULL);
 STAR4 = load_bitmap("star4.bmp", NULL);
 STAR5 = load_bitmap("star5.bmp", NULL);
}
