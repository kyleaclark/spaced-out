#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/* #defined the variables for the boundaries so I can set how big the
  playing screen will be */
#define W_RIGHT 795
#define W_LEFT 5
#define W_UP 5
#define W_DOWN 595

/* transparent pink for drawing images */
#define PINK makecol(255, 0, 255)

/* the maximum number of player bullets allowed onto the screen for memory purposes */
#define SCR_MAX_BULLETS 20

extern short bullets_number;
extern short enemy_number;

short rand_num(bool type);

#endif




