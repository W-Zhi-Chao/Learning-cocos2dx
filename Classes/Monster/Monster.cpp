

#include "Monster.hpp"
#include "Map.h"
USING_NS_CC;

Monster::Monster()
:baseSprite(NULL)
,speed(0)
,maxhp(0)
,force(0)
,hpBar(NULL)
,blood(NULL)
,hpBgSprite(NULL)
,curr_pos(0)
,last_st(stateNone)
,curr_st(stateNone)
{}

Monster::~Monster()
{}

bool Monster::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}

Animation *Monster::createAnimation(const char *prefixName, int start, int end, float delay){
    Vector<SpriteFrame*> animFrames;
        
    for (int i = start; i <= end; i++)
    {
        char a[32];
        sprintf(a, prefixName,i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(std::string(a));
        if(frame!=nullptr)
            animFrames.pushBack(frame);
    }
    return Animation::createWithSpriteFrames(animFrames, delay);
}
Vec2 Monster::currPoint(){
    return path.at(curr_pos);
}

//Vec2 Monster::getNextPoint()
//{
//    auto temp = curr_pos++;
//    auto maxCount = int(path.size());
//    if (temp < maxCount  ){
//        auto node =this->path.at(temp);
//        return node;
//    }
//    return currPoint();
//}

Vec2 Monster::nextPoint(){
    auto maxCount = int(path.size());
    curr_pos++;
    if (curr_pos < maxCount  ){
        auto node =this->path.at(curr_pos);
        return node;
    }
    else{
        curr_pos = maxCount-1 ;
    }
    return currPoint();
}
void Monster::createAndSetHpBar(){
    hpBgSprite = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");
    hpBgSprite->setPosition(Vec2(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height));
    baseSprite->addChild(hpBgSprite);
    hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
    hpBar->setType(ProgressTimer::Type::BAR);
    hpBar->setMidpoint(Point(0, 0.5f));
    hpBar->setBarChangeRate(Point(1, 0));
    hpBar->setPercentage(hp/maxhp);
    hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2 ));
    hpBgSprite->addChild(hpBar);
}

void Monster::stopMonsterAnimation(){
    for(int i = 1 ;i <= 6;i++){
        baseSprite->stopActionByTag(i);
    }
}

void Monster::update(float dt){
    if(last_st!=curr_st){
        switch (curr_st){
        case(stateWalkRight):{
            last_st = stateWalkRight;
            stopMonsterAnimation();
            baseSprite->setFlippedX(false);
            auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"runright")));
            action->setTag(stateWalkRight);
            baseSprite->runAction(action);}
            break;
        case(stateWalkLeft):{
            last_st= stateWalkLeft;
            stopMonsterAnimation();
            baseSprite->setFlippedX(true);
            auto aa = getName();
            auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"runleft")));
            action->setTag(stateWalkLeft);
            baseSprite->runAction(action);}
            break;
        case(stateWalkUp):{
            last_st= stateWalkUp;
            stopMonsterAnimation();
            baseSprite->setFlippedX(false);
            auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"runup")));
            action->setTag(stateWalkUp);
            baseSprite->runAction(action);}
            break;
        case(stateWalkDown):{
            last_st = stateWalkDown;
            stopMonsterAnimation();
            baseSprite->setFlippedX(false);
            auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"rundown")));
            action->setTag(stateWalkDown);
            baseSprite->runAction(action);}
            break;
        case(stateAttackRight):{
            last_st = stateAttackRight;
            stopMonsterAnimation();
            baseSprite->setFlippedX(false);
            auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"attack")));
            action->setTag(stateAttackRight);
            baseSprite->runAction(action);}
            break;
        case(stateAttackLeft):{
            last_st = stateAttackLeft;
            stopMonsterAnimation();
            baseSprite->setFlippedX(true);
            auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"attack")));
            action->setTag(stateAttackLeft);
            baseSprite->runAction(action);}
            break;
        case(stateNone):{
            last_st = stateNone;}
            break;
        case(stateFrozen):{
            last_st = stateFrozen;}
            break;
        case(stateDeath):{
            last_st = stateDeath;}
            break;
        }

    }
}

void Monster::death(){
    MapScene::getInstance()->monsterlist.remove(this);
//    auto i=ml.begin();
//    while(i!=ml.end()){
//        // 这里不注意写的话, 胡乱删除会导致i成为野指针
//        if(*i==this){
//            break;
//        } else{
//            i++;
//        }
//    }
//    if(i!=ml.end()) {
//        ml.
//        if(ml.size()==1)
//            MapScene::getInstance()->monsterlist.clear();
//        else if(i==ml.begin()){
//            MapScene::getInstance()->monsterlist.pop_front();
//        }else{
//            MapScene::getInstance()->monsterlist.erase(i);
//        }
//    }
    if(curr_st!=stateDeath){
        setHp(0);
        curr_st = stateDeath;
        hpBgSprite->setVisible(false);
        baseSprite->stopAllActions();
        unscheduleUpdate();
        MapScene::getInstance()->money += getMoney();
        auto act1 = Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"death"));
        baseSprite->runAction(Sequence::create(act1,FadeOut::create(1.0f),NULL));
    }
}
void Monster::runNextPoint(){
    auto tempCurrPoint = currPoint();

    baseSprite->setPosition(tempCurrPoint);

    auto tempNextPoint = nextPoint();
//    setMonsterZorder(tempNextPoint.y);
    if(fabs(tempNextPoint.y-tempCurrPoint.y)>5 && tempNextPoint.y > tempCurrPoint.y){
        curr_st = stateWalkUp;
    }else if(fabs(tempNextPoint.y-tempCurrPoint.y)>5 &&tempNextPoint.y <= tempCurrPoint.y){
        curr_st = stateWalkDown;
    }else if(tempNextPoint.x >= tempCurrPoint.x){
        curr_st = stateWalkRight;
    }else if(tempNextPoint.x < tempCurrPoint.x){
        curr_st = stateWalkLeft;
    }
    if( tempNextPoint!= tempCurrPoint ){

        auto duration =  tempCurrPoint.getDistance(tempNextPoint) / getSpeed() ;
        baseSprite->runAction(Sequence::create(MoveTo::create(duration, tempNextPoint)
                                           ,CallFuncN::create(CC_CALLBACK_0(Monster::runNextPoint, this))
                                           , NULL));
    }else{
        setHp(0);
        MapScene::getInstance()->health -=1;
        MapScene::getInstance()->monsterlist.remove(this);
        this->baseSprite->removeFromParent();
        unscheduleAllCallbacks();
        this->removeFromParent();
//        this->setVisible(false);
//        this->removeFromParent();
//        auto i=ml.begin();
//        while(i!=ml.end()){
//            // 这里不注意写的话, 胡乱删除会导致i成为野指针
//            if(*i==this){
//                break;
//            } else{
//                i++;
//            }
//        }
//        if(i!=ml.end()) {
//            if(ml.size()==1)
//                MapScene::getInstance()->monsterlist.clear();
//            else if(i==ml.begin()){
//                MapScene::getInstance()->monsterlist.pop_front();
//            }else{
//                MapScene::getInstance()->monsterlist.erase(i);
//            }
//        }
    }
}
