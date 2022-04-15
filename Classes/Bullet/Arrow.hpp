//
//  Arrow.hpp
//  Game
//
//  Created by 吴智超 on 2022/4/14.
//

#ifndef Arrow_hpp
#define Arrow_hpp

#include "cocos2d.h"
#include "Bullet.hpp"
USING_NS_CC;

class Arrow:public Bullet{
public:
    virtual bool init();
    CREATE_FUNC(Arrow);
    void shoot();
    void removeBullet();
};

#endif /* Arrow_hpp */
