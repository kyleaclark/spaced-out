#include <allegro.h>
#include <fstream.h>
#include "bitmap_load.h"

bitmaps_ player1_bmp;
bitmaps_ star_field_bmp;
bitmaps_ enemy1_bmp;
bitmaps_ bullets_bmp;
BITMAP *buffer;


void bitmap_loading()
 {
  buffer = create_bitmap(SCREEN_W, SCREEN_H);

  ifstream Fplayer1("art\\player1.txt");
  Fplayer1 >> player1_bmp.width;
  Fplayer1 >> player1_bmp.height;
  Fplayer1.close();
  player1_bmp.sprite = load_bitmap("art\\player1.bmp", NULL);

  star_field_bmp.sprite = load_bitmap("art\\star_field.bmp", NULL);
  star_field_bmp.width = 800;
  star_field_bmp.height = 600;

  ifstream Fenemy1("art\\enemy1.txt");
  Fenemy1 >> enemy1_bmp.width;
  Fenemy1 >> enemy1_bmp.height;
  Fenemy1.close();
  enemy1_bmp.sprite = load_bitmap("art\\enemy1.bmp", NULL);

  bullets_bmp.sprite = load_bitmap("art\\bullet1.bmp", NULL);
  bullets_bmp.width = 6;
  bullets_bmp.height = 15;

 }
