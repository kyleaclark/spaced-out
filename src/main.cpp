#include <allegro.h>
#include <fstream.h>
#include "global.h"
#include "setup.h" //contains initilizations for program
#include "bitmap_load.h"  //contains data of all bitmaps
#include "player.h"
#include "enemy.h"
#include "bullet.h"

void bullet_init();
void bullet_update();
void redraw();

Player player(200, 200);
Enemy enemy[20];
Bullet bullet[SCR_MAX_BULLETS];

int main() 
{ 
 short frames;

 //loading initilizers
 setup();
 bitmap_loading();
 bullet_init();

 enemy[0].create();

 redraw();


 counter = 0;

 // Looping until the ESCape key is pressed.
 while(!key[KEY_ESC])
  {
   if(keypressed())
    {
     player.move();
    }

   bullet_update();
   redraw();

   frames++;
  }

 //textprintf_centre(screen, font, 50, 5, makecol(0, 0, 235), "FPS %d", (frames/((int)counter/60));
 ofstream fpslog("fps.txt");
 fpslog << "time " << ((int)counter/60);
 fpslog << "\nframes " << frames;
 fpslog << "\nfps " << frames/((int)counter/60);
 fpslog.close();
 // rest(1500);
 //  poll_keyboard(); // This shouldn't be necessary in Windows.

 // Exit program.
 save_bitmap("screenshot.bmp", buffer, NULL);
 shutdown();
 return 0;     
}     

// Some Allegro magic to deal with WinMain().
END_OF_MAIN();

void redraw()
 {
  //clear(buffer);
  blit(star_field_bmp.sprite, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

  player.redraw();

  for(short i = 0; i < enemy_number; i++)
   {
    if(enemy[i].exists == 1)
     enemy[i].redraw();
   }

  for(short i = 0; i < bullets_number; i++)
   {
    if(bullet[i].exists == 1)
     bullet[i].redraw();
   }

 // draw_sprite(buffer, player1_bmp.sprite, player.x, player.y);
  masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
 }

void bullet_init()
 {
  for(short i = 0; i < SCR_MAX_BULLETS; i++)
   bullet[i].exists = 0;
 }

void bullet_update()
 {
  for(short i = 0; i < SCR_MAX_BULLETS; i++)
   {
    if(bullet[i].exists == 1)
     {
      bullet[i].move();
     }
   }
 }
