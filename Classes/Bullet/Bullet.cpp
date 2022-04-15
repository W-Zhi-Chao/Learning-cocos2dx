
#include "Bullet.hpp"

Bullet::Bullet()
:sprite(NULL),bulletForce(0),bulletScope(0)
{
}

Bullet::~Bullet(){}

bool Bullet::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}
