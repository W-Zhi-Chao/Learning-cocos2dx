
#include "TowerPanel.hpp"
#include "Map.h"
#include "AttackRange.hpp"
#include "Terrian.hpp"
#include "ArrowTower.hpp"
bool TowerPanel::init(){
    if ( !Sprite::init() ){
        return false;
    }
    circle = AttackRange::create();
    addChild(circle);
    circle->setVisible(false);
    circle->setVisible(false);
    planesprite = Sprite::createWithSpriteFrameName("gui_ring.png");
    planesprite->setPosition(0,0);
    planesprite->setScale(0.5f);
    addChild(planesprite);
    
    isBuilt = false;
    return true;
}

void TowerPanel::inAnimation(){
    planesprite->runAction(Sequence::create(ScaleTo::create(0.1f,1.0f,1.0f),
        CallFuncN::create(CC_CALLBACK_0(TowerPanel::addIcons,this)),
        NULL));
}

void TowerPanel::addIcons()
{
    archerIcon = BuildTowerIcon::createIcon(1,70);
    archerIcon->setPosition(Vec2(-(planesprite->getContentSize().width/4+20),planesprite->getContentSize().height/4+30));
    addChild(archerIcon);

    artilleryIcon = BuildTowerIcon::createIcon(4,120);
    artilleryIcon->setPosition(Vec2(planesprite->getContentSize().width/4+20,-(planesprite->getContentSize().height/4+30)));
    addChild(artilleryIcon);

    barracksIcon = BuildTowerIcon::createIcon(2,100);
    barracksIcon->setPosition(Vec2(planesprite->getContentSize().width/4+20,planesprite->getContentSize().height/4+30));
    addChild(barracksIcon);

    magicIcon = BuildTowerIcon::createIcon(3,100);
    magicIcon->setPosition(Vec2(-(planesprite->getContentSize().width/4+20),-(planesprite->getContentSize().height/4+30)));
    addChild(magicIcon);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseUp = CC_CALLBACK_1(TowerPanel::onMouseUp, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(TowerPanel::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, archerIcon);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener->clone(), artilleryIcon);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener->clone(), barracksIcon);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener->clone(), magicIcon);
}
void TowerPanel::addTower(int type)
{
//    static_cast<BaseMap*>(this->getParent()->getParent())->playerState->removeTowerInfo();
    switch (type){
        case(2):{
            log("2");
//        auto barracksTower = BaseBarracksTower::create();
//        barracksTower->setPosition(Point(0,20));
//        barracksTower->setTag(terrain->getTag());
//        barracksTower->setMyTerrain(terrain);
//        terrain->addChild(barracksTower);
//        barracksTower->buildingAnimation();
//        GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - barracksTower->getBuildMoney();
//        }
            break;
        }
        case(1):{
            auto arrowTower = ArrowTower::create();
            arrowTower->setPosition(Point(0,20));
            arrowTower->setTag(terrain->getTag());
            
            terrain->addChild(arrowTower); // TowerPanel的父亲
            MapScene::getInstance()->money -= arrowTower->getMoney();
            break;
        }
        case(4):{
            log("4");
//        auto artilleryTower = SimpleArtilleryTowerlvl1::create();
//        artilleryTower->setPosition(Point(0,20));
//        artilleryTower->setTag(terrain->getTag());
//        artilleryTower->setMyTerrain(terrain);
//        terrain->addChild(artilleryTower);
//        MapScene::getInstance()->money -=
//        }
            break;
        }
        case(3):{
            log("3");
//        auto mageTower = SimpleMageTowerlvl1::create();
//        mageTower->setPosition(Point(0,20));
//        mageTower->setTag(terrain->getTag());
//        mageTower->setMyTerrain(terrain);
//        terrain->addChild(mageTower);
//        GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - mageTower->getBuildMoney();
            break;
        }
    }
//    SoundManager::playTowerBuilding();
    isBuilt = true;
    terrain->terrain->setVisible(false); // 把terrain设置为不可见, 方便后续拆除
    this->setVisible(false);
}

void TowerPanel::addTempTower(int type){
    if(tempTower!=NULL){
        removeChild(tempTower,true);
    }
    circle->setVisible(true);
    switch (type){
        case(1):
            tempTower = Sprite::createWithSpriteFrameName("tower_preview_archer.png");
            tempTower->setPosition(Vec2(0,25));
    //        static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARCHER_1);}
            break;
        case(2):
            tempTower = Sprite::createWithSpriteFrameName("tower_preview_barrack.png");
            tempTower->setPosition(Vec2(0,25));
    //        static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(BARAACKS_1);}
            break;
        case(3):
            tempTower = Sprite::createWithSpriteFrameName("tower_preview_mage.png");
            tempTower->setPosition(Vec2(0,10));
    //        static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(MAGE_1);}
            break;
        case(4):
            tempTower = Sprite::createWithSpriteFrameName("tower_preview_artillery.png");
            tempTower->setPosition(Vec2(0,25));
    //        static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARTILLERY_1);}
            break;
    }
    addChild(tempTower);
}
        

void TowerPanel::onMouseDown(Event *event){
    EventMouse *e = (EventMouse*)event;
    auto target = static_cast<BuildTowerIcon*>(e->getCurrentTarget());
    auto mouse_location =e->getLocationInView();
    auto t_origin = target->getPosition()+static_cast<Terrian*>(this->getParent())->getPosition();
    mouse_location -= MapScene::getInstance()->map_bg->getPosition();
    Size size = target->baseIcon->getContentSize();
    Rect rect = Rect(0-size.width/2, 0-size.height/2, size.width, size.height);
    if(rect.containsPoint(mouse_location-t_origin)){
        static_cast<Terrian*>(this->getParent())->childIconSelected=true;
        if(target->getIsSelected()){
            if(target->getIsAble()){
                int type = target->getType();
                addTower(type);
            }
        } else{
            // 取消其余选中的
            archerIcon->setNotSelected();
            artilleryIcon->setNotSelected();
            barracksIcon->setNotSelected();
            magicIcon->setNotSelected();
            // 设置选中的
            target->setSelected();
            addTempTower(target->getType());
        }
    }
    
}
void TowerPanel::onMouseUp(Event *event){
    EventMouse *e = (EventMouse*)event;
    if(isBuilt){
        removeFromParent();
    }
}
