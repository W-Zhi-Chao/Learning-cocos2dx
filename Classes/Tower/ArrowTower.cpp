
#include "ArrowTower.hpp"
#include "Monster.hpp"
#include "Terrian.hpp"
#include "Arrow.hpp"
// Tower建立在 Terrian之上
bool ArrowTower::init(){
    if(!Sprite::init()){
        return false;
    }
    
    nearestMonster = NULL;
    level = 1;
    shootTag = 1; // right archer
    setType(ARCHER_1);
    setRange(500.0f);
    setMoney(70);
    setForce(100);
    setRate(1.0f);
    
    char tem[64];
    sprintf(tem,"archer_tower_000%d.png",level);
    towerBase = Sprite::createWithSpriteFrameName(String(tem));
    sprintf(tem,"tower_archer_lvl%d_shooter_0001.png",level);
    shooter_1 = Sprite::createWithSpriteFrameName(String(tem));
    sprintf(tem,"tower_archer_lvl%d_shooter_0001.png",level);
    shooter_2 = Sprite::createWithSpriteFrameName(String(tem));
    shooter_1->setPosition(Vec2(towerBase->getContentSize().width/2-10,towerBase->getContentSize().height/2+18));
    shooter_2->setPosition(Vec2(towerBase->getContentSize().width/2+10,towerBase->getContentSize().height/2+18));
    // initialize shooter_1 and shooter_2 Animation
    AnimationCache::getInstance()->addAnimation(BaseTower::createAnimation("tower_archer_lvl1_shooter_00%02d.png",3,10, 0.04f,"tower_archer_lvl1_shooter_0001.png"), "level1_shoot_down");
    AnimationCache::getInstance()->addAnimation(BaseTower::createAnimation("tower_archer_lvl1_shooter_00%02d.png",11,18, 0.04f,"tower_archer_lvl1_shooter_0002.png"), "level1_shoot_top");
    towerBase->addChild(shooter_1);
    towerBase->addChild(shooter_2);

    addChild(towerBase);
    schedule(CC_SCHEDULE_SELECTOR(ArrowTower::shoot),rate); // 回调函数, 不断更新射击
    return true;
}

// 由子弹类考虑击中与否, 这里只负责射击
void ArrowTower::shoot(float dt){
    getNearestMonster();
    if(nearestMonster!=NULL && nearestMonster->getHp()>0){
        Vec2 m_pos = nearestMonster->baseSprite->getPosition();
        Vec2 shoot_vec = m_pos-static_cast<Terrian*>(this->getParent())->getPosition();
        auto bullet = ArrowTowerBullet();
        float startangle = bullet->getRotation();
        float endangle = 0;
        auto p_vec = bullet->getPosition()-shoot_vec;
        float angleRadians = atan(p_vec.y/p_vec.x);
        float angleChange = CC_RADIANS_TO_DEGREES(angleRadians);
        // left
        if(shoot_vec.x - bullet->getPosition().x<=0){
            startangle += abs(angleChange);
            endangle = -90;
            if(shootTag==1){
                bullet->setPosition(Vec2(0,30));
                shooter_1->setFlippedX(true);
                if(shoot_vec.y-bullet->getPosition().y<=0)
                    shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("level1_shoot_down")));
                else
                    shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("level1_shoot_top")));
                shootTag = 2;
            } else{
                bullet->setPosition(Vec2(10,30));
                shooter_2->setFlippedX(true);
                if(shoot_vec.y-bullet->getPosition().y<=0)
                    shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("level1_shoot_down")));
                else
                    shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("level1_shoot_top")));
                shootTag = 1;
            }
        } else{
            startangle -= abs(angleChange);
            endangle = 270;
            if(shootTag==1){
                bullet->setPosition(Vec2(0,30));
                shooter_1->setFlippedX(false);
                if(shoot_vec.y-bullet->getPosition().y<=0)
                    shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("level1_shoot_down")));
                else
                    shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("level1_shoot_top")));
                shootTag = 2;
            } else{
                bullet->setPosition(Vec2(10,30));
                shooter_2->setFlippedX(false);
                if(shoot_vec.y-bullet->getPosition().y<=0)
                    shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("level1_shoot_down")));
                else
                    shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("level1_shoot_top")));
                shootTag = 1;
            }
        }
        ccBezierConfig bezier;
        //两个控制点
        bezier.controlPoint_1 = Point(bullet->getPosition().x,bullet->getPosition().y+200);
        bezier.controlPoint_2 = Point(shoot_vec.x,shoot_vec.y+200);;
        bezier.endPosition = shoot_vec;

        auto action = Spawn::create(BezierTo::create(0.5f, bezier),RotateTo::create(0.5f,endangle),NULL);
        //攻击属性给弓箭
        bullet->setBulletAction(action);
        bullet->shoot();
        // TODO
        bullet = NULL;
    }
}
Bullet* ArrowTower::ArrowTowerBullet(){
    auto bullet = Arrow::create();
    bullet->setRotation(90.0f);
    bullet->setBulletForce(getForce());
    this->getParent()->addChild(bullet);
    return bullet;
}
