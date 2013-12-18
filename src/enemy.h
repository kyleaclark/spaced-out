#ifndef _ENEMY_H_
#define _ENEMY_H_

//#define MAX_ENEMIES (set_enemies)

class Enemy
 {
  public:
   short num_enemies;
   //important position and collisiong info
   bool exists;         //to see if the enemy exists or not
   float x, y;     //position vars
   short w, h;     //width and height vars for bitmap
   float angle;    //the current angle the ship is at
   float velx, vely;  //for determing the velocity the player is at

   //enemy attributes
   short state;       //the state of ship (i.e. shooting, still, moving)
   float accel;     //the speed the ship can accel at
   float speed;    //the speed the ship can move at when fully accel
   float turn;     //the speed in which the ship can turn at an angle

   Enemy::Enemy();     //constructor taking in set_enemies
   void create();  //creating the enemies
   void destroy();
 //  bool move();   //determing if the player is pressing a key or not
   void redraw();  //drawing the player on the screen
 };

extern Enemy enemy[20];

#endif
