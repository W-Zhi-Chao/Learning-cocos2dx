
#ifndef Executioner_hpp
#define Executioner_hpp

#include "cocos2d.h"
#include "Monster.hpp"
USING_NS_CC;

class Executioner:public Monster{
public:
    virtual bool init() override;
    static Executioner* createMonster(std::vector<Vec2> p);
};

#endif /* Executioner_hpp */
