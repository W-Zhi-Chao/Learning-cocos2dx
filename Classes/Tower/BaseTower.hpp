
#ifndef BaseTower_hpp
#define BaseTower_hpp

#include "cocos2d.h"
#include "Monster.hpp"
USING_NS_CC;
typedef enum{
    ARCHER_1 = 0, //1级箭塔
    ARCHER_2, //2级箭塔
    ARCHER_3, //3级箭塔
    COSSBOW, //弩塔
    TOTEMTOWER, //野人
    ARTILLERY_1,//1级炮塔
    ARTILLERY_2,//2级炮塔
    ARTILLERY_3,//3级炮塔
    EARTHQUAKE, //地震
    MECHS, //机器
    BARAACKS_1,//1级兵营
    BARAACKS_2,//2级兵营
    BARAACKS_3,//3级兵营
    ASSASSIN,//盗贼
    TEMPLAR,//战士
    MAGE_1,//1级法师塔
    MAGE_2,//2级法师塔
    MAGE_3,//3级法师塔
    ARCHMAGE,//龙卷风
    NEC,//死灵法
}TowerType;

class BaseTower:public Sprite{
public:
    
    CREATE_FUNC(BaseTower);
    virtual bool init();
    void getNearestMonster();
    Monster *nearestMonster;
//    Sprite *terrain; // 面板
    CC_SYNTHESIZE(TowerType, type, Type); //防御塔类型
    CC_SYNTHESIZE(float, force, Force); //攻击力
    CC_SYNTHESIZE(float, range, Range); //攻击范围
    CC_SYNTHESIZE(float, rate, Rate); //攻击频率
    CC_SYNTHESIZE(bool, isShooting, IsShooting);
    CC_SYNTHESIZE(int, money, Money);
    static Animation* createAnimation(const char* prefixName, int start,int end, float delay,std::string lastFrame);
    
};

#endif /* BaseTower_hpp */
