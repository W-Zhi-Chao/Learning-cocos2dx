//
//  Header.h
//  Game
//
//  Created by 吴智超 on 2022/4/12.
//

#ifndef Header_h
#define Header_h

#include "cocos2d.h"
USING_NS_CC;

class LoadingScene : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScene);
    void loadSouce();
    void logic(float dt);
    int numberOfLoadedRes;
};

#endif /* Header_h */
