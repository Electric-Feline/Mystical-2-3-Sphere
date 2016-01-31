/*
 * main.c
 * Constructs a Window housing an output TextLayer to show data from 
 * either modes of operation of the accelerometer.
 */

#include <pebble.h>

#define TAP_NOT_DATA true

static Window *s_main_window;
static TextLayer *s_output_layer;


static void tap_handler(AccelAxisType axis, int32_t direction) {
  vibes_short_pulse();static char message[100];
  int r = rand()%30;
  switch(r){
    case 0:{
      strcpy(message, "\n\nIt is certain.... I think.");
      break;   
    }
    case 1:{
      strcpy(message, "\n\nIt is decidedly so.");
      break;
    } 
    case 2:{
      strcpy(message, "I have some doubts. Not many, but it's statistically significant.");
      break;
    }
    case 3:{
      strcpy(message, "\nYes, definitely. Maybe.");
      break;
    } 
    case 4:{
      strcpy(message, "\nYou may rely on it, but I wouldn't.");
      break;
    }
    case 5:{
      strcpy(message, "\n\nAs I see it, maybe.");
      break;   
    }
    case 6:{
      strcpy(message, "\n\n\"Most possibly.\"");
      break;
    } 
    case 7:{
      strcpy(message, "\n\n\"Yes.\"");
      break;
    }
    case 8:{
      strcpy(message, "\n\nSigns point to maybe.");
      break;
    } 
    case 9:{
      strcpy(message, "\n\nReply hazy try again.");
      break;
    }
    case 10:{
      strcpy(message, "\nAsk again later. Waaaayyyy later.");
      break;
    } 
    case 11:{
      strcpy(message, "\nBetter not tell you now.\n Or later.");
      break;
    }
    case 12:{
      strcpy(message, "\nERROR 11: predictions.lib missing");
      break;
    } 
    case 13:{
      strcpy(message, "Concentrate and ask again. Don't hurt yourself, though.");
      break;
    }
    case 14:{
      strcpy(message, "\nDon't count\non it.\n Really.\n Don't.");
      break;   
    }
    case 15:{
      strcpy(message, "Completely ignore whatever Marketing has to say.");
      break;
    } 
    case 16:{
      strcpy(message, "\n\nOutlook not so good.");
      break;
    }
    case 17:{
      strcpy(message, "\n\nOutlook okay, I guess.");
      break;
    } 
    case 18:{
      strcpy(message, "\nMy sources say no, but go ahead anyway.");
      break;
    }
    case 19:{
      strcpy(message, "Go for it, but first bribe your superiors with brunch and tiny wines.");
      break;   
    }
    case 20:{
      strcpy(message, "\n\nPlease stop shaking me.");
      break;   
    }
    case 21:{
      strcpy(message, "I have neither the time nor crayons to explain why it's a bad idea.");
      break;
    } 
    case 22:{
      strcpy(message, "\nBlame it on Quality Control.");
      break;
    }
    case 23:{
      strcpy(message, "\n\nMeh.");
      break;
    } 
    case 24:{
      strcpy(message, "\nSearch your feelings. You know it to be true.");
      break;
    }
    case 25:{
      strcpy(message, "\nI am legally obgliated to tell you \"No\".");
      break;   
    }
    case 26:{
      strcpy(message, "\nI am not liable for your bad decisions.");
      break;
    } 
    case 27:{
      strcpy(message, "\n\nDon't tell HR.\n");
      break;
    }
    case 28:{
      strcpy(message, "\n\nFire the intern.\n");
      break;
    } 
    case 29:{
      strcpy(message, "\n\n...better sleep on it.\n");
      break;
    }
    default: {strcpy(message, "Ass\n");}
  }
  
  text_layer_set_text(s_output_layer, message);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  s_output_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 10, window_bounds.size.h));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  
  
  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_output_layer, GColorClear);
  text_layer_set_text_color(s_output_layer, GColorBlack);
  //text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_output_layer, GTextAlignmentCenter);
  
  text_layer_set_text(s_output_layer, "\nAsk me a question and shake your hand!");
  
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
}

static void main_window_unload(Window *window) {
  // Destroy output TextLayer
  text_layer_destroy(s_output_layer);
}

static void init() {
  srand(time(NULL));
  // Create main Window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);

  // Use tap service? If not, use data service
  if (TAP_NOT_DATA) {
    // Subscribe to the accelerometer tap service
    accel_tap_service_subscribe(tap_handler);
  } else {
    // Subscribe to the accelerometer data service
    int num_samples = 3;
    //accel_data_service_subscribe(num_samples, data_handler);

    // Choose update rate
    accel_service_set_sampling_rate(ACCEL_SAMPLING_10HZ);
  }
}

static void deinit() {
  // Destroy main Window
  window_destroy(s_main_window);

  if (TAP_NOT_DATA) {
    accel_tap_service_unsubscribe();
  } else {
    accel_data_service_unsubscribe();
  }
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}