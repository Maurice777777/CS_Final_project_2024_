#include "RedWitch.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"
#include "Witch_bullet.h"

namespace WitchSetting {
	static constexpr char gif_root_path[50] = "./assets/gif/Hero"; 
    static constexpr char gif_postfix[][10] = 
    {
		"left",
		"right",
		"front",
		"back"
	};
}

void Witch::init()
{
    //set gif path
    for(size_t type=0;type<static_cast<size_t>(WitchState::WITCHSTATE_MAX);++type)
    {
        char buffer[50];
        sprintf(buffer,"%s/redwitch_%s.gif",
                WitchSetting::gif_root_path,
                WitchSetting::gif_postfix[static_cast<int>(type)]);
        gifPath[static_cast<WitchState>(type)] = std::string{buffer};
    }

    // set attack gifs for each direction
    gifPath[WitchState::ATTACK_BACK] = "./assets/gif/Hero/redwizard/redwizard_atk_back.gif";
    gifPath[WitchState::ATTACK_FRONT] = "./assets/gif/Hero/redwizard/redwizard_atk_front.gif";
    gifPath[WitchState::ATTACK_LEFT] = "./assets/gif/Hero/redwizard/redwizard_atk_left.gif";
    gifPath[WitchState::ATTACK_RIGHT] = "./assets/gif/Hero/redwizard/redwizard_atk_right.gif";

    //set initial pos and hit box of witch
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
    DataCenter *DC = DataCenter::get_instance();
    shape.reset(new Rectangle(DC->window_width/2,
                                DC->window_height/2,
                                DC->window_width/2+gif->width,
                                DC->window_height/2+gif->height));
}

void Witch::draw()
{
    //load GIF from GIFCenter
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);

    algif_draw_gif(gif,
                    shape->center_x()-gif->width/2,
                    shape->center_y()-gif->width/2,
                    0);
}

void Witch::fire_bullet()
{
    DataCenter *DC = DataCenter::get_instance();
    Direction bullet_direction;

    switch (state)
    {
        case WitchState::BACK:
        case WitchState::ATTACK_BACK:
            bullet_direction = Direction::UP;
            break;
        case WitchState::FRONT:
        case WitchState::ATTACK_FRONT:
            bullet_direction = Direction::DOWN;
            break;
        case WitchState::LEFT:
        case WitchState::ATTACK_LEFT:
            bullet_direction = Direction::LEFT;
            break;
        case WitchState::RIGHT:
        case WitchState::ATTACK_RIGHT:
            bullet_direction = Direction::RIGHT;
            break;
        default:
            return;
    }

    // 創建新的子彈並設置方向
    Witch_bullet *bullet = new Witch_bullet(shape->center_x(), shape->center_y(), bullet_direction);
    bullet->setGifPath("./assets/gif/Hero/redwizard/redwizard_bullet.gif");
    DC->witchBullets.emplace_back(bullet);

}


void Witch::update()
{
    static int bullet_counter = 0; 
    bullet_counter++;

    DataCenter*DC = DataCenter::get_instance();
    is_moving = false;

    if(DC->key_state[ALLEGRO_KEY_W])
    {
        shape->update_center_y(shape->center_y()-speed);
        state = WitchState::BACK;
        is_moving=true;
    }
    else if(DC->key_state[ALLEGRO_KEY_A])
    {
        shape->update_center_x(shape->center_x()-speed);
        state = WitchState::LEFT;
        is_moving=true;
    }
    else if(DC->key_state[ALLEGRO_KEY_S])
    {
        shape->update_center_y(shape->center_y()+speed);
        state = WitchState::FRONT;
        is_moving=true;
    }
    else if(DC->key_state[ALLEGRO_KEY_D])
    {
        shape->update_center_x(shape->center_x()+speed);
        state = WitchState::RIGHT;
        is_moving=true;
    }

    if(!is_moving && bullet_counter>30) //每30fps射射
    {
        switch (state)
        {
        case WitchState::BACK:
            state = WitchState::ATTACK_BACK;
            break;
        case WitchState::FRONT:
            state = WitchState::ATTACK_FRONT;
            break;
        case WitchState::LEFT:
            state = WitchState::ATTACK_LEFT;
            break;
        case WitchState::RIGHT:
            state = WitchState::ATTACK_RIGHT;
            break;
        default:
            break;
        }
        fire_bullet(); // 發射子彈
        bullet_counter = 0;
    }
}

Point Witch::get_position() const 
{
    return Point(shape->center_x(), shape->center_y());
}