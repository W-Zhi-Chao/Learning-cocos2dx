
#include "Arrow.hpp"
#include "Map.h"
bool Arrow::init(){
    if(!Sprite::init()){
        return false;
    }
    sprite = Sprite::createWithSpriteFrameName("arrow.png");
    addChild(sprite);
    return true;
}

void Arrow::shoot(){
    this->runAction(Sequence::create(bulletAction,
                                     CallFuncN::create(CC_CALLBACK_0(Arrow::removeBullet, this)),
                                     NULL));
}
// 这个是判断是否击中并移除箭头的函数
void Arrow::removeBullet(){
    // 是否击中
    bool missed = true;
    auto ml = MapScene::getInstance()->monsterlist;
    auto tem_vec = this->getPosition()+this->getParent()->getPosition();
    auto tem_size = sprite->getContentSize();
    Monster *death_m = NULL;
    // 这里arrow的anchor居中
    auto bulletRect = Rect(tem_vec.x-tem_size.width/2,tem_vec.y-tem_size.height/2,
                           tem_size.width, tem_size.height);
    for(auto i=ml.begin(); i!=ml.end(); i++){
        auto monsterRect = (*i)->baseSprite->getBoundingBox();
        // 击中
        if(monsterRect.intersectsRect(bulletRect)){
            auto currHp = (*i)->getHp();
            currHp -= this->getBulletForce();
            if(currHp<=0) {
                currHp = 0;
                death_m = *i;
            }
            missed = false;
            (*i)->setHp(currHp);
            (*i)->getHpBar()->setPercentage(100*currHp/(*i)->getMaxhp());
            break;
        }
    }
    // 如果有怪兽死亡, 就调用死亡函数
    if(death_m!=NULL) death_m->death();
    if(missed){
        sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("decal_arrow.png"));
        sprite->runAction(Sequence::create(FadeOut::create(1.0f)
                                        ,CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
                                       , NULL));
    } else{
        this->removeFromParent();
    }
}
