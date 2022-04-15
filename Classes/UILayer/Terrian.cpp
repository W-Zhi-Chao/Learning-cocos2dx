
#include "Terrian.hpp"
#include "TowerPanel.hpp"
#include "Map.h"
Terrian* Terrian::createTerrian(int type)
{
    auto terrain = new Terrian();
    if(terrain && terrain->init(type)){
        terrain->autorelease();
        return terrain;
    }
    CC_SAFE_DELETE(terrain);
    return NULL;
}

bool Terrian::init(int type)
{
    if (!Sprite::init())
    {
        return false;
    }
    isUpdateMenuShown = false;
    childIconSelected = false;
    switch (type)
    {
    case(1):{
        terrain = Sprite::createWithSpriteFrameName("build_terrain_0004.png");}
        break;
    case(2):{
        terrain = Sprite::createWithSpriteFrameName("build_terrain_0005.png");}
        break;
    case(3):{
        terrain = Sprite::createWithSpriteFrameName("build_terrain_0006.png");}
        break;
    default:{
        terrain = Sprite::createWithSpriteFrameName("build_terrain_0004.png");}
        break;
    }
    terrain->setPosition(0,0);
    addChild(terrain);
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(Terrian::onTouchBegan, this);
    listener->onMouseUp = CC_CALLBACK_1(Terrian::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,terrain);
    return true;
}

void Terrian::showUpdateMenu()
{
    auto towerPanleLayer = TowerPanel::create();
    towerPanleLayer->setPosition(0,0);
    towerPanleLayer->setTag(this->getTag()+10); // TODO: fix this
    towerPanleLayer->setMyTerrain(this);
    this->addChild(towerPanleLayer);
    towerPanleLayer->inAnimation();
    isUpdateMenuShown = true;
}
   
void Terrian::hideUpdateMenu()
{
    this->removeChildByTag(this->getTag()+10); // TODO: fix this
    isUpdateMenuShown = false;
}

void Terrian::onTouchBegan(Event *event){
    
}

void Terrian::onTouchEnded(Event* event){
    EventMouse *e = (EventMouse*)event;
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    auto mouse_location =e->getLocationInView();
    auto t_origin = this->getPosition();
    auto size = target->getContentSize();
    mouse_location = mouse_location - this->getParent()->getPosition();
    Rect rect = Rect(-size.width/2, -size.height/2, size.width, size.height);
    // 如果目标被隐藏, 就不显示, 这是为了防御塔被建造以后不显示该panel
    if (rect.containsPoint(mouse_location-t_origin)&&target->isVisible()){
        if(isUpdateMenuShown){
            if(!childIconSelected) // 子图标没有被选中, 就把它隐藏
                hideUpdateMenu();
        }else{
            showUpdateMenu();
        }
    }else if(isUpdateMenuShown){
        if(!childIconSelected) // 子图标没有被选中, 就把它隐藏
            hideUpdateMenu();
    }
    childIconSelected = false;
}

//void Terrian::smokeEffect()
//{
//    auto smoke = Sprite::createWithSpriteFrameName("effect_sellSmoke_0001.png");
//    addChild(smoke,99);
//    smoke->runAction(Sequence::create(
//            Animate::create(AnimationCache::getInstance()->getAnimation("sell_smoke")),
//            CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, smoke)),
//            NULL));
//}
