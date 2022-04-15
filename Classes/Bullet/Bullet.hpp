
#ifndef Bullet_hpp
#define Bullet_hpp

#include "cocos2d.h"
USING_NS_CC;

class Bullet:public Sprite{
public:
    Bullet();
    ~Bullet();
    CREATE_FUNC(Bullet);
    virtual bool init();
    
    CC_SYNTHESIZE(float, bulletScope, BulletScope); // 攻击范围
    CC_SYNTHESIZE(float, bulletForce, BulletForce); // 攻击力
    CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction); // 在飞行过程的动作
    Sprite *sprite; //子弹图像
    virtual void shoot(){};
    virtual void removeBullet(){};
};
#endif /* Bullet_hpp */
