/*

   "Classic" Digital Watch Pebble App

 */

// Standard includes
#include "pebble.h"


// App-specific data
Window *window; // All apps must have at least one window
TextLayer *time_layer; // The clock


static BitmapLayer *xtern_layer;
static BitmapLayer *indyx_layer;


static GBitmap *xtern;
static GBitmap *indyx; 

// Called once per second
static void handle_second_tick(struct tm* tick_time, TimeUnits units_changed) {

  static char time_text[] = "00:00"; // Needs to be static because it's used by the system later.

  if(clock_is_24h_style())
    strftime(time_text, sizeof(time_text), "%R", tick_time);
  else
    strftime(time_text, sizeof(time_text), "%I:%M", tick_time);

  text_layer_set_text(time_layer, time_text);
}


// Handle the start-up of the app
static void do_init(void) {

  // Create our app's base window
  window = window_create();
  window_stack_push(window, true);
  window_set_background_color(window, GColorBlack);

  Layer *window_layer = window_get_root_layer(window);

  // Init the text layer used to show the time
  time_layer = text_layer_create(GRect(0, 100, 144 /* width */, 168-100 /* height */));
  text_layer_set_text_color(time_layer, GColorWhite);
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));

  // Ensures time is displayed immediately (will break if NULL tick event accessed).
  // (This is why it's a good idea to have a separate routine to do the update itself.)
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  handle_second_tick(current_time, SECOND_UNIT);
  tick_timer_service_subscribe(SECOND_UNIT, &handle_second_tick);

  // This needs to be deinited on app exit which is when the event loop ends
  xtern = gbitmap_create_with_resource(RESOURCE_ID_LOGO);
  indyx = gbitmap_create_with_resource(RESOURCE_ID_INDYX);


  // The bitmap layer holds the image for display
  xtern_layer = bitmap_layer_create(GRect(0, 47, 144 /* width */, 168-40 /* height */));
  bitmap_layer_set_bitmap(xtern_layer, xtern);
  bitmap_layer_set_alignment(xtern_layer, GAlignTop);


  // The bitmap layer holds the image for display
  indyx_layer = bitmap_layer_create(GRect(0, 10, 144 /* width */, 168/3 /* height */));
  bitmap_layer_set_bitmap(indyx_layer, indyx);
  bitmap_layer_set_alignment(indyx_layer, GAlignTop);

  layer_add_child(window_layer, bitmap_layer_get_layer(xtern_layer));
  layer_add_child(window_layer, bitmap_layer_get_layer(indyx_layer));

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
}

static void do_deinit(void) {
  text_layer_destroy(time_layer);
  window_destroy(window);
}

// The main event/run loop for our app
int main(void) {
  do_init();
  app_event_loop();
  do_deinit();
}
