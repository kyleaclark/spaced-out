#ifndef _COLLISION_H_
#define _COLLISION_H_

class Collision
 {
  public:
   Collision::Collision(bool var);

   bool bull(float x, float y, short w, short h, float angle);
 };

extern Collision collision;

#endif
