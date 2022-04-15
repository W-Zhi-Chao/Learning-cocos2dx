
#ifndef ArrowTower_hpp
#define ArrowTower_hpp

#include "cocos2d.h"
#include "BaseTower.hpp"
#include "Arrow.hpp"
USING_NS_CC;

typedef std::string String;

class ArrowTower:public BaseTower{
public:
    CREATE_FUNC(ArrowTower);
    bool init();
    Sprite *towerBase;
    Sprite *shooter_1;
    Sprite *shooter_2;
//    virtual Bullet* ArrowTowerBullet();
    int shootTag;
    int level; //塔的等级
    virtual Bullet* ArrowTowerBullet(); // 创建子弹
    virtual void shoot(float dt); // 射击
    
};

#endif /* ArrowTower_hpp */
