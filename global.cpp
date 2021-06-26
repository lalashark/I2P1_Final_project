#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 400;
const int HEIGHT = 600;
float play_time;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
ALLEGRO_FONT *font = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
bool close_game = false;
