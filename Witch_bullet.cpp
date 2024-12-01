#include "Witch_bullet.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include <allegro5/allegro_primitives.h>

Witch_bullet::Witch_bullet(double x, double y, Direction direction)
    : position(x, y), speed(10.0), direction(direction) {}

void Witch_bullet::update()
{
    // 根據方向更新子彈的位置
    switch (direction)
    {
    case Direction::LEFT:
        position.x -= speed;
        break;
    case Direction::RIGHT:
        position.x += speed;
        break;
    case Direction::DOWN:
        position.y += speed;
        break;
    case Direction::UP:
        position.y -= speed;
        break;
    default:
        break;
    }

    
}

void Witch_bullet::setGifPath(const std::string &path)
{
    gifPath = path; // 設置子彈的gif path 
}


void Witch_bullet::draw()
{
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath);

    if (gif)
    {
        algif_draw_gif(gif, position.x, position.y, 0);
    }
    else
    {
        // 繪製一個簡單的圓形作為子彈的占位符
        al_draw_filled_circle(position.x, position.y, 5, al_map_rgb(255, 0, 0));
    }
}
