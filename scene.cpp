#include "scene.h"

//ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *background0 = NULL;
ALLEGRO_BITMAP *background1 = NULL;
ALLEGRO_BITMAP *background2 = NULL;
ALLEGRO_BITMAP *background3 = NULL;
ALLEGRO_BITMAP *background4 = NULL;
ALLEGRO_BITMAP *background5 = NULL;

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

        if (event.keyboard.keycode == ALLEGRO_KEY_T)
            shtp == 1;
            judge_next_window = true;

    if (event.keyboard.keycode == ALLEGRO_KEY_Q)
        close_game = true;
}
void menu_draw()
{
    al_draw_bitmap(background, 0, 0, 0);
    //al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 220 - 50, ALLEGRO_ALIGN_CENTRE, "Press 'q' to quit");
    al_draw_rectangle(WIDTH / 2 - 150, 510 - 50, WIDTH / 2 + 150, 550 - 50, al_map_rgb(255, 255, 255), 0);

    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 220, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH / 2 - 150, 510, WIDTH / 2 + 150, 550, al_map_rgb(255, 255, 255), 0);

    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 220 + 50 , ALLEGRO_ALIGN_CENTRE, "Press 't' to start");
    al_draw_rectangle(WIDTH / 2 - 150, 510, WIDTH / 2 + 150, 550, al_map_rgb(255, 255, 255), 0);
}
void menu_destroy()
{
    al_destroy_font(font);
}

// function of htp
void htp_init()
{
    font = al_load_ttf_font("./font/pirulen.ttf", 12, 0);
    background = al_load_bitmap("./image/howtoplay.png");
}
void htp_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_KEY_UP)
        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            window = 2;
            judge_next_window = true;

}
void htp_draw()
{
    al_draw_bitmap(background, 0, 0, 0);
    //al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 220, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH / 2 - 150, 510, WIDTH / 2 + 150, 550, al_map_rgb(255, 255, 255), 0);
    //al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 220 - 50, ALLEGRO_ALIGN_CENTRE, "Press 'q' to quit");
    //al_draw_rectangle(WIDTH / 2 - 150, 510 - 50, WIDTH / 2 + 150, 550 - 50, al_map_rgb(255, 255, 255), 0);
}
void htp_destroy()
{
    al_destroy_font(font);
    al_destroy_bitmap(background);
}
// function of game_scene
void game_scene_init()
{
    character_init();
    rocks_init();
    stars_init();
    background0 = al_load_bitmap("./image/stage0.jpg");
    background1 = al_load_bitmap("./image/stage1.jpg");
    background2 = al_load_bitmap("./image/stage2.jpg");
    background3 = al_load_bitmap("./image/stage3.jpg");
    background4 = al_load_bitmap("./image/stage4.jpg");
    background5 = al_load_bitmap("./image/stage5.jpg");
}
void game_scene_draw()
{

    //background change by time
    if(){al_draw_bitmap(background0, 0, 0, 0);}
    else if((int)(al_get_time() - play_time)<10) al_draw_bitmap(background1, 0, 0, 0);
    else if(10<=(int)(al_get_time() - play_time)<20) al_draw_bitmap(background2, 0, 0, 0);
    else if(20<=(int)(al_get_time() - play_time)<30) al_draw_bitmap(background3, 0, 0, 0);
    else if(30<=(int)(al_get_time() - play_time)<40) al_draw_bitmap(background4, 0, 0, 0);
    else if((int)(al_get_time() - play_time)>=40)al_draw_bitmap(background5, 0, 0, 0);


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
