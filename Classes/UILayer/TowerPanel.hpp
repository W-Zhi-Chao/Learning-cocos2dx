
#ifndef TowerPanel_hpp
#define TowerPanel_hpp

#include "cocos2d.h"
#include "BuildTowerIcon.hpp"
#include "AttackRange.hpp"
#include "Terrian.hpp"
USING_NS_CC;

// 这是建造防御塔的触控面板控制台
class TowerPanel:public Sprite{
public:
    virtual bool init() override;
    CREATE_FUNC(TowerPanel);
    void onMouseDown(Event *event);
    void onMouseUp(Event* event);
    CC_SYNTHESIZE(Terrian*, terrain, MyTerrain);
    void inAnimation();
    void addIcons();
    void addTempTower(int type);
    void addTower(int type);
    BuildTowerIcon* archerIcon;
    BuildTowerIcon* artilleryIcon;
    BuildTowerIcon* barracksIcon;
    BuildTowerIcon* magicIcon;
    Sprite* planesprite;
    AttackRange* circle;
    Sprite *tempTower;
    bool isBuilt;
};
#endif /* TowerPanel_hpp */
