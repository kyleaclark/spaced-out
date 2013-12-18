#ifndef _BITMAP_LOAD_H_
#define _BITMAP_LOAD_H_

#include <allegro.h>

struct bitmaps_
 {
  short width;
  short height;
  BITMAP *sprite;
 };

extern bitmaps_ player1_bmp;
extern bitmaps_ star_field_bmp;
extern bitmaps_ enemy1_bmp;
extern bitmaps_ bullets_bmp;

extern BITMAP *buffer;

void bitmap_loading();

#endif
