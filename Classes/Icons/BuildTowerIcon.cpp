
#include "BuildTowerIcon.hpp"
#include "Map.h"
USING_NS_CC;

bool BuildTowerIcon::initIcon(int type, int money){
    if(!Sprite::init()){
        return  false;
    }
    isSelected = false;
    char tem[32];
    sprintf(tem,"main_icons_00%02d.png",type);
    baseIcon = Sprite::createWithSpriteFrameName(std::string(tem));
    addChild(baseIcon);
    priceIcon = Sprite::createWithSpriteFrameName("price_tag.png");
    priceIcon->setPosition(Point(0,-baseIcon->getContentSize().height/2));
    addChild(priceIcon);
    sprintf(tem, "%d", money);
    priceLabel = Label::createWithTTF(std::string(tem),"arial.ttf",20);
    priceLabel->setColor(Color3B(255,153,0));
    priceLabel->setPosition(Point(priceIcon->getContentSize().width/2,priceIcon->getContentSize().height/2-2));
    priceIcon->addChild(priceLabel);
    okIcon = Sprite::createWithSpriteFrameName("main_icons_0019.png");
    okIcon->setPosition(Point(baseIcon->getContentSize().width/2,baseIcon->getContentSize().height/2));
    baseIcon->addChild(okIcon);
    okIcon->setVisible(false);
    
    setMoney(money);
    setType(type);
    this->scheduleUpdate();
    return true;
}
BuildTowerIcon* BuildTowerIcon::createIcon(int type, int money){
    auto buildTowerIcon = new BuildTowerIcon();
    if(buildTowerIcon && buildTowerIcon->initIcon(type, money)){
        buildTowerIcon->autorelease();
        return buildTowerIcon;
    }
    CC_SAFE_DELETE(buildTowerIcon);
    return NULL;
}

void BuildTowerIcon::setUpdateMoney(int money)
{
    setMoney(money);
    char tem[16];
    sprintf(tem,"%d",money);
    priceLabel->setString(std::string(tem));
}

void BuildTowerIcon::setNotEnoughMoney()
{
    isAble = false;
    priceLabel->setColor(Color3B(102,102,102));
    char tem[64];
    sprintf(tem, "main_icons_disabled_00%02d.png", type);
    baseIcon->setSpriteFrame(std::string(tem));
    priceIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("price_tag_disabled.png"));
    okIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("main_icons_disabled_0019.png"));
}

void BuildTowerIcon::setEnoughMoney()
{
    isAble = true;
    priceLabel->setColor(Color3B(255,153,0));
    char tem[64];
    sprintf(tem, "main_icons_00%02d.png", type);
    baseIcon->setSpriteFrame(std::string(tem));
    okIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("main_icons_0019.png"));
    priceIcon->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("price_tag.png"));
}

void BuildTowerIcon::setSelected()
{
    isSelected = true;
    okIcon->setVisible(true);
}

void BuildTowerIcon::setNotSelected()
{
    isSelected = false;
    okIcon->setVisible(false);
}

void BuildTowerIcon::update(float dt)
{
    if(getMoney()<=MapScene::getInstance()->money){
        setEnoughMoney();
    }else{
        setNotEnoughMoney();
    }
}
