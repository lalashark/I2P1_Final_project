#include "scene.h"

//ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;

// function of menu
void menu_init()
{
    font = al_load_ttf_font("./font/pirulen.ttf", 12, 0);
    background = al_load_bitmap("./image/in.png");
}
void menu_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_KEY_UP)
        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            judge_next_window = true;
    if (event.keyboard.keycode == ALLEGRO_KEY_Q)
        close_game = true;
}
void menu_draw()
{
    al_draw_bitmap(background, 0, 0, 0);
    //al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 220, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH / 2 - 150, 510, WIDTH / 2 + 150, 550, al_map_rgb(255, 255, 255), 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 220 - 50, ALLEGRO_ALIGN_CENTRE, "Press 'q' to quit");
    al_draw_rectangle(WIDTH / 2 - 150, 510 - 50, WIDTH / 2 + 150, 550 - 50, al_map_rgb(255, 255, 255), 0);
}
void menu_destroy()
{
    al_destroy_font(font);
}

// function of game_scene
void game_scene_init()
{
    character_init();
    rocks_init();
    stars_init();
    background = al_load_bitmap("./image/stage.jpg");
}
void game_scene_draw()
{
    al_draw_bitmap(background, 0, 0, 0);
    character_draw();
    stars_draw();
    rocks_draw();
    
}
void game_scene_destroy()
{
    al_destroy_bitmap(background);
    character_destory();
}

void gg_scene_init()
{
    fonts = al_load_ttf_font("./font/pirulen.ttf", 64, 0);
    font = al_load_ttf_font("./font/pirulen.ttf", 12, 0);
    background = al_load_bitmap("./image/ggback.png");
}

void gg_scene_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_KEY_UP)
        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            judge_next_window = true;
    if (event.keyboard.keycode == ALLEGRO_KEY_Q)
        close_game = true;
}

void gg_scene_draw()
{
    al_draw_bitmap(background, 0, 0, 0);
    //fonts = al_load_ttf_font("./font/pirulen.ttf", 14, 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 -50 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to restart");
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Press 'q' to quit");
    al_draw_text(fonts, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE, "GG");
}

void gg_scene_destroy()
{
    al_destroy_font(font);
    al_destroy_font(fonts);
    al_destroy_bitmap(background);
}