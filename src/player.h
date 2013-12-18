#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
 {
  public:
   //important position and collisiong info
   float x, y;
   short w, h;
   float angle;    //the current angle the ship is at
   float turn;     //the speed in which the ship can turn at an angle
   float velx, vely;  //for determing the velocity the player is at

   short gun;

   //player attributes
   float speed;

   Player::Player(float fx, float fy);     //constructor taking in x, y, width, height
   bool collision(float x, float y, short w, short h, float angle);
   bool move();   //determing if the player is pressing a key or not
   void redraw();  //drawing the player on the screen
 };

extern Player player;

#endif
