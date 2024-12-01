#ifndef REDWITCH_H_INCLUDED
#define REDWITCH_H_INCLUDED

#include <string>
#include <map>
#include "Object.h"

enum class WitchState
{
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    ATTACK_LEFT,
    ATTACK_RIGHT,
    ATTACK_FRONT,
    ATTACK_BACK,
    WITCHSTATE_MAX
};

class Witch : public Object
{
public:
    void init();
    void update();
    void draw();
    void fire_bullet();
    Point get_position() const;
private:
    WitchState state = WitchState::FRONT;
    double speed = 5.0;
    std::map<WitchState, std::string> gifPath; 
    /*--Revise--*/
    bool is_moving = false;
    /*---Revise---*/
};

#endif // REDWITCH_H_INCLUDED
