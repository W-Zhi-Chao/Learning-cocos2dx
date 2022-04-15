/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Map.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add background
    auto sprite_bg = Sprite::createWithSpriteFrameName("mainmenu_bg.png");
    sprite_bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    addChild(sprite_bg,-1);
    
    // 3. add Logo
    sprite_logo = Sprite::createWithSpriteFrameName("logo.png");
    sprite_logo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprite_logo->setScale(0.2f);
    logo_pos=Vec2(visibleSize.width/2, visibleSize.height-sprite_logo->getContentSize().height/2);
    sprite_logo->setPosition(logo_pos);
    addChild(sprite_logo,0);
    
    // 4. add startbutton
    button_start = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
    button_start->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    button_start->setPosition(logo_pos.x,logo_pos.y);
    button_start->setVisible(false);
    addChild(button_start, 1);
    auto button_start_listener = EventListenerMouse::create();
    //鼠标移动反应
    button_start_listener->onMouseMove = [&](Event *event){
        EventMouse* e = (EventMouse*)event;
//        Size size = button_start->getContentSize();
        float x = e->getCursorX();
        float y = e->getCursorY();
        Rect bt = Rect(360, 170, 240 , 110);
        
        // 如果按钮已经可见, 并且鼠标在其中, 则更换图片.
        if(bt.containsPoint(Point(x,y))&&button_start->isVisible()){
            button_start->setSpriteFrame("menu_startchain_0002.png");
        } else{
            button_start->setSpriteFrame("menu_startchain_0001.png");
        }
        
    };
    // 鼠标Down反应
    button_start_listener->onMouseDown = [&](Event *event){
        
    };
    // 鼠标Up反应
    button_start_listener->onMouseUp = [&](Event *event){
        EventMouse* e = (EventMouse*)event;
        Rect bt = Rect(360, 170, 240 , 110);
        float x = e->getCursorX();
        float y = e->getCursorY();
        if(bt.containsPoint(Point(x,y))&&button_start->isVisible()){
            auto seq = Sequence::create(DelayTime::create(0.2f),
                                        MoveTo::create(0.3f, logo_pos),
                                        CallFuncN::create(CC_CALLBACK_0(HelloWorld::button_invisible, this)),
                                        NULL);
            button_start->runAction(seq);
        }
        auto scene = MapScene::createScene();
        Director::getInstance()->replaceScene(scene);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(button_start_listener,button_start);
    return true;
}

void HelloWorld::logo_animation(){
    auto sprite = Sprite::createWithSpriteFrameName("logo_brillo_0001.png");
    sprite->setPosition(logo_pos);
    //生成帧动画
    SpriteFrame* frame = NULL;
    Vector<SpriteFrame*> aFrames(20);

    for (int len = 1;len <= 21; len++)
    {
        char a[32];
        sprintf(a, "logo_brillo_00%02d.png",len);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(std::string(a));
        if(frame!=nullptr)
            aFrames.pushBack(frame);
    }
    addChild(sprite,10);
    auto animation = Animation::createWithSpriteFrames(aFrames,0.1f);
    //播放动画
    sprite->runAction(RepeatForever::create(Animate::create(animation)));
}

void HelloWorld::button_start_animation(){
    button_start->setVisible(true);
    //执行平移动画
    button_start->runAction(MoveTo::create(0.3f, Point(logo_pos.x,logo_pos.y-180)));
}

void HelloWorld::button_invisible(){
    button_start->setVisible(false);
}

void HelloWorld::onEnterTransitionDidFinish(){
    auto seq = Sequence::create(ScaleTo::create(0.5f, 1.5f, 1.5f),
            ScaleTo::create(0.2f, 1.0f,1.0f),
            CallFuncN::create(CC_CALLBACK_0(HelloWorld::logo_animation,this)),
            CallFuncN::create(CC_CALLBACK_0(HelloWorld::button_start_animation,this)),
            NULL
    );
    sprite_logo->runAction(seq);
}
