#ifndef Monster_h
#define Monster_h

#include "cocos2d.h"
USING_NS_CC;
typedef enum{
    stateNone = 0, //空
    stateWalkRight, //向右走
    stateWalkLeft, //向左走
    stateWalkUp, //向上走
    stateWalkDown, //向下走
    stateAttackLeft, // 向左边攻击
    stateAttackRight, //向右边攻击
    stateDeath, //死亡
    stateFrozen //停止行动
}MonsterState;

typedef enum{
    THUG = 0,
    EXECUTIONER,
    FALLEN,
    IMMORTAL,
    MUNRA,
    RADIER,
    SCORPION,
    TREMOR,
    WASPHORNET,
    WASPQUEEN,
    WOLF,
    BOSS_EFREETI,
    EFREETI,
    CANIBAL,
    GORILLA,
    HUNTER,
    PRIEST,
    SHAMAN,
    SHIELD,
    WINGRIDER,
    BOSS_CANIBAL,
    CANIBAL_OFFSPRING,
    BLAZEFANG,
    BROODGUARD,
    ELITE,
    MYRMIDON,
    NIGHTSCALE,
    QUETZAL
}MonsterName;

class Monster:public Sprite{
public:
    Monster();
    ~Monster();
    // should be override by subclass
    virtual bool init() override;
    CREATE_FUNC(Monster);
    Sprite *baseSprite; // 基本图像
    Sprite *hpBgSprite;
    Sprite *blood; // 血条图像
    CC_SYNTHESIZE(float, speed, Speed); // 行走速度
    CC_SYNTHESIZE(float, maxhp, Maxhp); // 最大生命值
    CC_SYNTHESIZE(float, hp, Hp); // 生命值
    CC_SYNTHESIZE(float, force, Force); // 攻击力
    CC_SYNTHESIZE(std::vector<Vec2>, path, Path); // 路径
    CC_SYNTHESIZE(int, money, Money);
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);
    void createAndSetHpBar(); // 血条
    void stopMonsterAnimation();
    void runNextPoint(); // 不断递归调用自己更新状态的函数
    static Animation* createAnimation(const char* prefixName, int start,int end, float delay);
    // call scheduleUpdate() to enable it
    virtual void update(float dt); // 更新函数, 当目前位置等于下一次位置时
    Vec2 currPoint();
    Vec2 nextPoint();
    void death();
    int curr_pos; // path数组的索引
//    CC_SYNTHESIZE(Vector<Point>, <#varName#>, <#funName#>); // 行走路径, 在地图中实现
    std::string monsterName;
    MonsterName name;
    MonsterState curr_st;
    MonsterState last_st;
};

#endif /* Monster_h */

//std::vector<std::string> MonsterNameTable={
//    "THUG",
//    "EXECUTIONER",
//    "FALLEN",
//    "IMMORTAL",
//    "MUNRA",
//    "RADIER",
//    "SCORPION",
//    "TREMOR",
//    "WASPHORNET",
//    "WASPQUEEN",
//    "WOLF",
//    "BOSS_EFREETI",
//    "EFREETI",
//    "CANIBAL",
//    "GORILLA",
//    "HUNTER",
//    "PRIEST",
//    "SHAMAN",
//    "SHIELD",
//    "WINGRIDER",
//    "BOSS_CANIBAL",
//    "CANIBAL_OFFSPRING",
//    "BLAZEFANG",
//    "BROODGUARD",
//    "ELITE",
//    "MYRMIDON",
//    "NIGHTSCALE",
//    "QUETZAL"
//};
