
#include "Executioner.hpp"
USING_NS_CC;

Executioner* Executioner::createMonster(std::vector<Vec2> points)
{
    auto monster = new Executioner();
    if (monster && monster->init())
    {
        monster->setPath(points);
        monster->setForce(100);
        monster->setMaxhp(300);
        monster->setHp(300);
        monster->setSpeed(200);
        monster->setMoney(100);
        monster->runNextPoint();
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Executioner::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    // initialize animation
    AnimationCache::getInstance()->addAnimation(createAnimation("desertExecutioner_0%003d.png",73,98, 0.04f), "Executioner_attack");
    AnimationCache::getInstance()->addAnimation(createAnimation("desertExecutioner_0%003d.png",99,118, 0.04f), "Executioner_death");
    AnimationCache::getInstance()->addAnimation(createAnimation("desertExecutioner_0%003d.png",49,72, 0.05f), "Executioner_runup");
    AnimationCache::getInstance()->addAnimation(createAnimation("desertExecutioner_0%003d.png",25,48, 0.05f), "Executioner_rundown");
    AnimationCache::getInstance()->addAnimation(createAnimation("desertExecutioner_0%003d.png",1,24, 0.05f), "Executioner_runleft");
    AnimationCache::getInstance()->addAnimation(createAnimation("desertExecutioner_0%003d.png",1,24, 0.05f), "Executioner_runright");
    name=EXECUTIONER;
    setName("Executioner_");
    baseSprite = Sprite::createWithSpriteFrameName("desertExecutioner_0001.png");
    addChild(baseSprite);
    createAndSetHpBar();
    last_st = stateNone;
    curr_st=stateNone;
    this->blood = Sprite::createWithSpriteFrameName("fx_blood_splat_red_0001.png");
    blood->setPosition(Vec2(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/2));
    baseSprite->addChild(blood);
    blood->setVisible(false);
    scheduleUpdate();
//    setListener();
    return true;
}
