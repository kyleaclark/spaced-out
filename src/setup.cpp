#include <allegro.h>
#include <fstream.h>
#include "setup.h"
#include "bitmap_load.h"

volatile int counter;
volatile int ani_counter;

void setup()
{
 ofstream filelog("log.txt");
 allegro_init();
 filelog << "allegro_init initialized";
 install_keyboard();
 filelog << "\ninstall_keyboard initialized";
 install_mouse();
 filelog << "\ninstall_mouse initialized";
 install_timer();
 filelog << "\ninstall_timer initialized";
 set_color_depth(32);
 if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 800, 600, 0, 0) == 0)
 {
 filelog << "\nset_color_depth(32) initialized";
 filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) initialized"; 
 }
 else if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) != 0)
 {
 filelog << "\nset_color_depth(32) failed";
 filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) failed";
 
  set_color_depth(24);
  if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) == 0)
  {
  filelog << "\nset_color_depth(24) initialized";
  filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) initialized"; 
  }
  else if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) != 0)
  {
  filelog << "\nset_color_depth(24) failed";
  filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) failed"; 
  
   set_color_depth(16);
   if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) == 0)
   {
   filelog << "\nset_color_depth(16) initialized";
   filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) initialized"; 
   }
   else if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 600, 480, 0, 0) != 0)
   {
   filelog << "\nset_color_depth(16) failed";
   filelog << "\nset_gfx_mode(GFX_AUTODETECT_FULLSCREEN 800x600) failed";
   filelog << "\nProgram bailing out";
   allegro_exit();
   }
  }
 }
 
 install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
 filelog << "\ninstall_sound(DIGI_AUTODETECT, MIDI_AUTODETECT) initialized";
 install_int_ex( update_counter, BPS_TO_TIMER(60));
 filelog << "\ninstall_int_ex(update_counter, BPS_TO_TIMER(60)) initialized";
    
 filelog.close();
  
}

void shutdown()
 {
  destroy_bitmap(player1_bmp.sprite);
  destroy_bitmap(star_field_bmp.sprite);
  destroy_bitmap(enemy1_bmp.sprite);
  destroy_bitmap(buffer);
 }

void update_counter()
 {
  counter++;
  ani_counter++;
 }

