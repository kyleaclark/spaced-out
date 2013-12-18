#ifndef _BULLET_H_
#define _BULLET_H_

//#include "global.h"

class Bullet
 {
  public:
   //important position and collisiong info
   float x, y;
   short w, h;
   float angle;    //the current angle the ship is at
   float turn;     //the speed in which the ship can turn at an angle
   float velx, vely;  //for determing the velocity the player is at
   short exists;

   //bullet attributes
   short gun;
   float speed;

   Bullet::Bullet();     //constructor
   void create(float fx, float fy, short fw, short fh, float fangle);  //creates the bullets when KEY_SPACE is pressed
   bool collision(float x, float y, short w, short h, float angle); //detects collisions
   bool move();   //updates the movement of the bullets
   void destroy();  //for destroying the bullets
   void redraw();  //drawing the player on the screen
 };

extern Bullet bullet[20];

#endif
