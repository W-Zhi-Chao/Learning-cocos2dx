
#include "BaseTower.hpp"
#include "Map.h"
#include "Terrian.hpp"
bool BaseTower::init(){
    if(!Sprite::init()){
        return false;
    }
    return true;
}

void BaseTower::getNearestMonster(){
    MapScene* map = MapScene::getInstance();
    auto ml = map->monsterlist;
    float min = 10000;
    nearestMonster = NULL;
    for(auto i=ml.begin(); i!=ml.end(); i++){
        Vec2 tem = static_cast<Terrian*>(this->getParent())->getPosition(); // Tower的父亲是terrian, 所以其位置
        float t = tem.getDistance((*i)->baseSprite->getPosition()); //对于怪兽而言, 运动的实际是是它的图像
        if(t<getRange() && t<min){
            min=t;
            nearestMonster=*i;
        }
    }
}

Animation* BaseTower::createAnimation(const char* prefixName, int start,int end, float delay,std::string lastFrame)
{
    Vector<SpriteFrame*> animFrames;
    
    for (int i = start; i <= end; i++)
    {
        char tem[64];
        sprintf(tem,prefixName,i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(std::string(tem));
        if(frame!=nullptr)
            animFrames.pushBack(frame);
    }
    animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(lastFrame));
    return Animation::createWithSpriteFrames(animFrames, delay);
}

