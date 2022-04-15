
#ifndef Terrian_hpp
#define Terrian_hpp

#include "cocos2d.h"

USING_NS_CC;

// 这是建造防御塔的触控面板控制台
class Terrian : public Sprite{
public:
    virtual bool init(int type);
    static Terrian* createTerrian(int type);
    void showUpdateMenu();
    void hideUpdateMenu();
    Sprite* terrain;
    void onTouchBegan(Event *event);
    void onTouchEnded(Event* event);
    bool isUpdateMenuShown;
    bool childIconSelected;
//    void smokeEffect();
};

#endif /* Terrian_hpp */
