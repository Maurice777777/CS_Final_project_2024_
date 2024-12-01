#ifndef WITCH_BULLET_H_INCLUDED
#define WITCH_BULLET_H_INCLUDED

#include "Object.h"
#include "shapes/Point.h"
#include "RedWitch.h"

enum class Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Witch_bullet : public Object
{
public:
    Witch_bullet(double x, double y, Direction direction);
    void update();
    void draw();
    void setGifPath(const std::string &path);
private:
    Point position;
    double speed;
    Direction direction;
    std::string gifPath;
};

#endif 
