#include "charater.h"

// the state of character
enum
{
    STOP = 0,
    MOVE,
    ATK
};
float base_speed = 1;
const int seal_floor = 500;
const int rocks_count = 15;
const int stars_count = 2;
typedef struct character
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    bool dir;          // left: false, right: true
    int state;         // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    int hp;
    int atk_count;
    int wait_for_heal;
    float speedX;
} Character;

typedef struct item
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    bool live;         // live this rock ?
    int state;         // the state of character
    float speedX = 1;
    ALLEGRO_BITMAP *img_move[3];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    int hp = 1;
} Item;

Character chara;
Item rocks[rocks_count];
Item stars[stars_count];
ALLEGRO_SAMPLE *sample = NULL;

void stars_init()
{
    // load star images
    for (int star = 0; star < stars_count; star++)
    {
        for (int i = 1; i <= 3; i++)
        {
            char temp[50];
            sprintf(temp, "./image/star_move%d.png", i);
            stars[star].img_move[i - 1] = al_load_bitmap(temp);
        }
    }
    // initial the geometric information of character rock
    for (int star = 0; star < stars_count; star++)
    {
        stars[star].width = al_get_bitmap_width(stars[star].img_move[0]);
        stars[star].height = al_get_bitmap_height(stars[star].img_move[0]);
        stars[star].x = 0;
        stars[star].y = 0;
        stars[star].live = false;
        stars[star].speedX = 3;
    }
    for (int star = 0; star < stars_count; star++)
    {
        stars[star].state = MOVE;
        stars[star].anime = 0;
        stars[star].anime_time = 20;
    }
}

void rocks_init()
{
    // load rock images
    for (int rock = 0; rock < rocks_count; rock++)
    {
        for (int i = 1; i <= 3; i++)
        {
            char temp[50];
            sprintf(temp, "./image/rock_move%d.png", i);
            rocks[rock].img_move[i - 1] = al_load_bitmap(temp);
        }
    }
    // initial the geometric information of character rock
    for (int rock = 0; rock < rocks_count; rock++)
    {
        rocks[rock].width = al_get_bitmap_width(rocks[rock].img_move[0]);
        rocks[rock].height = al_get_bitmap_height(rocks[rock].img_move[0]);
        rocks[rock].x = WIDTH / 2;
        rocks[rock].y = 0;
        rocks[rock].live = false;
    }

    // initial the animation component rock
    for (int rock = 0; rock < rocks_count; rock++)
    {
        rocks[rock].state = MOVE;
        rocks[rock].anime = ( rock * 3 )% 30;
        rocks[rock].anime_time = (((rock * 3) %30 )+ 20)%30;
    }
}

void character_init()
{
    //printf("charater_init\n");

    // load seal images
    for (int i = 1; i <= 2; i++)
    {
        char temp[50];
        sprintf(temp, "./image/char_atk%d.png", i);
        chara.img_atk[i - 1] = al_load_bitmap(temp);
    }
    for (int i = 1; i <= 2; i++)
    {
        char temp[50];
        sprintf(temp, "./image/char_move%d.png", i);
        chara.img_move[i - 1] = al_load_bitmap(temp);
    }

    // load effective sound
    sample = al_load_sample("./sound/atk_sound.wav");
    chara.atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = WIDTH / 2 + 50;
    chara.y = seal_floor;
    chara.dir = false;
    chara.hp = 5;
    chara.atk_count = 3;
    chara.wait_for_heal = true;
    chara.speedX = 1;
    chara.atk_count = 3;
    // initial the animation component
    chara.state = MOVE;
    chara.anime = 0;
    chara.anime_time = 30;

    font = al_load_ttf_font("./font/pirulen.ttf", 12, 0);
}
void charater_process(ALLEGRO_EVENT event)
{
    //printf("charater_process\n");
    // process the animation
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        if (event.timer.source == fps)
        {
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
        // process the animation of rock
        for (int rock = 0; rock < rocks_count; rock++)
        {
            rocks[rock].anime++;
            rocks[rock].anime %= rocks[rock].anime_time;
        }
        // process the animation of star
        for (int star = 0; star < stars_count; star++)
        {
            stars[star].anime++;
            stars[star].anime %= stars[star].anime_time;
        }
    }
    // process the keyboard event

    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        if (event.timer.source == fps)
        {
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
        // process the keyboard event
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            printf("%d\n", chara.atk_count);
            chara.atk_count -= 1;
        }
        key_state[event.keyboard.keycode] = false;
    }
}

void stars_update()
{
    // generate a rock at top
    //printf("charater_update\n");
    for (int star = stars_count - 1; star >= 0; star--)
    {
        // if rock is not live
        if (!stars[star].live)
        {

            if (rand() % 300 == 0)
            {
                stars[star].live = true;
                stars[star].y = (rand() % (HEIGHT)-150);
                stars[star].x = 0;
                printf("star generate: %d %d\n", stars[star].x, stars[star].y);
                break;
            }
        }
    }
    for (int star = 0; star < stars_count; star++)
    {
        if (stars[star].live)
        {
            stars[star].y += stars[star].speedX * base_speed;
            stars[star].x += stars[star].speedX * base_speed;
            if (stars[star].y > HEIGHT || stars[star].x > WIDTH)
                stars[star].live = false;
        }
    }
    // colider
    for (unsigned int star = 0; star < stars_count; star++)
    {
        if (stars[star].live)
        {
            if (
                (
                    (stars[star].x + stars[star].width > chara.x &&
                     stars[star].x < chara.x) ||
                    (stars[star].x < chara.x + chara.width &&
                     stars[star].x + stars[star].width > chara.x)) &&
                ((stars[star].y + stars[star].height > chara.y &&
                  stars[star].y < chara.y) ||
                 (stars[star].y < chara.y + chara.height &&
                  stars[star].y + stars[star].height > chara.y)))
            {
                if (chara.state == ATK)
                {
                    // miss attack
                    stars[star].live = false;
                    //printf("ATK\n");
                }
                else
                {
                    stars[star].live = false;
                    chara.speedX+=0.2;
                }
            }
        }
    }
}

void rocks_update()
{
    // generate a rock at top
    //printf("charater_update\n");
    for (int rock = rocks_count - 1; rock >= 0; rock--)
    {
        // if rock is not live
        if (!rocks[rock].live)
        {
            if (rand() % 300 == 0)
            {
                rocks[rock].live = true;
                rocks[rock].y = 30;
                rocks[rock].x = 30 + rand() % (WIDTH - 20);
                break;
            }
        }
    }

    // move the rock who live.
    for (int rock = 0; rock < rocks_count; rock++)
    {
        if (rocks[rock].live)
        {
            rocks[rock].y += rocks[rock].speedX * base_speed;
            if (rocks[rock].y > HEIGHT)
                rocks[rock].live = false;
        }
    }

    // colider
    for (unsigned int rock = 0; rock < rocks_count; rock++)
    {
        if (rocks[rock].live)
        {
            if (
                (
                    (rocks[rock].x + rocks[rock].width > chara.x &&
                     rocks[rock].x < chara.x) ||
                    (rocks[rock].x < chara.x + chara.width &&
                     rocks[rock].x + rocks[rock].width > chara.x)) &&
                ((rocks[rock].y + rocks[rock].height > chara.y &&
                  rocks[rock].y < chara.y) ||
                 (rocks[rock].y < chara.y + chara.height &&
                  rocks[rock].y + rocks[rock].height > chara.y)))
            {
                if (chara.state == ATK)
                {
                    // miss attack
                    rocks[rock].live = false;
                    //printf("ATK\n");
                }
                else
                {
                    rocks[rock].live = false;
                    chara.hp--;
                }
            }
        }
    }
    if (!chara.hp)
    {
        judge_next_window = true;
    }
}

void charater_update()
{
    // use the idea of finite state machine to deal with different state
    /*
    if (key_state[ALLEGRO_KEY_W])
    {
        chara.y -= base_speed;
        chara.state = MOVE;
    }
    else*/

    if (key_state[ALLEGRO_KEY_A])
    {
        chara.dir = false;
        chara.x -= base_speed;
        chara.state = MOVE;
    }
    /*else if (key_state[ALLEGRO_KEY_S])
    {
        chara.y += base_speed;
        chara.state = MOVE;
    }*/
    else if (key_state[ALLEGRO_KEY_D])
    {
        chara.dir = true;
        chara.x += base_speed;
        chara.state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_SPACE])
    {
        if (chara.atk_count >= 1)
        {
            chara.state = ATK;
        }
    }
    else if (chara.anime == chara.anime_time - 1)
    {
        chara.anime = 0;
        chara.state = STOP;
    }
    else if (chara.anime == 0)
    {
        chara.state = STOP;
    }
    
    if ((int)(al_get_time() - play_time) % 20 == 1 && chara.wait_for_heal)
    {
        chara.hp += 1;
        chara.wait_for_heal = false;
        if(chara.hp >= 5)
        {
            chara.hp = 5;
        }
    }
    else
    {
        chara.wait_for_heal = true;
    }
}

void stars_draw()
{
    // draw star
    for (int star = 0; star < stars_count; star++)
    {
        
        if (stars[star].live)
        {
            printf("%d %d\n", stars[star].anime, stars[star].anime_time);
            if (stars[star].anime < stars[star].anime_time / 3)
            {
                al_draw_bitmap(stars[star].img_move[0], stars[star].x, stars[star].y, 0);
            }
            else if (stars[star].anime < stars[star].anime_time / 3 * 2)
            {
                al_draw_bitmap(stars[star].img_move[1], stars[star].x, stars[star].y, 0);
            }
            else
            {
                al_draw_bitmap(stars[star].img_move[2], stars[star].x, stars[star].y, 0);
            }
        }
    }
}

void rocks_draw()
{
    // draw rock
    for (int rock = 0; rock < rocks_count; rock++)
    {
        if (rocks[rock].live)
        {
            if (rocks[rock].anime < rocks[rock].anime_time / 3)
            {
                al_draw_bitmap(rocks[rock].img_move[0], rocks[rock].x, rocks[rock].y, 0);
            }
            else if (rocks[rock].anime < rocks[rock].anime_time / 3 * 2)
            {
                al_draw_bitmap(rocks[rock].img_move[1], rocks[rock].x, rocks[rock].y, 0);
            }
            else
            {
                al_draw_bitmap(rocks[rock].img_move[2], rocks[rock].x, rocks[rock].y, 0);
            }
        }
    }
}
void character_draw()
{
    //rintf("character_draw\n");
    // with the state, draw corresponding image
    // draw slot of hp
    al_draw_rectangle(WIDTH / 2 - 100, seal_floor + 45, WIDTH / 2 + 180, seal_floor + 70, al_map_rgb(200, 200, 200), 5);
    // draw blocks in hp
    al_draw_filled_rectangle(WIDTH / 2 - 100, seal_floor + 45, WIDTH / 2 - 100 + (280) / 5 * chara.hp, seal_floor + 70, al_map_rgb(255, 0, 0));
    al_draw_rectangle(WIDTH / 2 - 100, seal_floor + 45, WIDTH / 2 - 100 + (280) / 5 * chara.hp, seal_floor + 70, al_map_rgb(200, 200, 200), 5);
    // print time from game start. printf("%f\n", al_get_time() - play_time);
    char c[50];
    sprintf(c, ">> %d <<", (int)(al_get_time() - play_time));
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2 - 150, seal_floor + 40, ALLEGRO_ALIGN_CENTRE, "Live Time");
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2 - 150, seal_floor + 55, ALLEGRO_ALIGN_CENTRE, c);

    if (chara.state == STOP)
    {
        if (chara.dir)
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
    }
    else if (chara.state == MOVE)
    {
        if (chara.dir)
        {
            if (chara.anime < chara.anime_time / 2)
            {
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else
            {
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
        else
        {
            if (chara.anime < chara.anime_time / 2)
            {
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }
            else
            {
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }
        }
    }
    else if (chara.state == ATK)
    {
        if (chara.dir)
        {
            if (chara.anime < chara.anime_time / 2)
            {
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else
            {
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara.atk_Sound);
            }
        }
        else
        {
            if (chara.anime < chara.anime_time / 2)
            {
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, 0);
            }
            else
            {
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, 0);
                al_play_sample_instance(chara.atk_Sound);
            }
        }
    }
}
void character_destory()
{
    al_destroy_bitmap(chara.img_atk[0]);
    al_destroy_bitmap(chara.img_atk[1]);
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
    al_destroy_sample_instance(chara.atk_Sound);
}
