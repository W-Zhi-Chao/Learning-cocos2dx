
#ifndef BuildTowerIcon_hpp
#define BuildTowerIcon_hpp

#include "cocos2d.h"
USING_NS_CC;

// 这是建造防御塔的图标
class BuildTowerIcon:public Sprite{
public:
    CREATE_FUNC(BuildTowerIcon);
    virtual bool initIcon(int type,int money);
    static BuildTowerIcon* createIcon(int type,int money);
    virtual void setSelected();
    virtual void setNotSelected();
    virtual void setNotEnoughMoney();
    virtual void setEnoughMoney();
    virtual void setUpdateMoney(int money);
    void update(float dt);
    
    CC_SYNTHESIZE(int, money, Money);
    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(bool, isAble, IsAble);
    CC_SYNTHESIZE(bool, isSelected, IsSelected);
    Sprite *baseIcon;
    Sprite *priceIcon;
    Sprite *okIcon;
    Label *priceLabel;
    
};
#endif /* BuildTowerIcon_hpp */
