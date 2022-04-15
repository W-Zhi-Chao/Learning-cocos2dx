//
//  LoadingScene.cpp
//  Game
//
//  Created by 吴智超 on 2022/4/12.
//

#include "LoadingScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;


Scene* LoadingScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = LoadingScene::create();

    scene->addChild(layer);

    return scene;
}

bool LoadingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    numberOfLoadedRes = 0;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto back = Sprite::create("Default@2x.png");
    back->setRotation(-90.0f);
    back->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    addChild(back);
    schedule(CC_SCHEDULE_SELECTOR(LoadingScene::logic));
    return true;
}

void LoadingScene::loadSouce()
{

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_2-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_a-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ingame_gui-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_a_2-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_a_3-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_32_2-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_32-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("towers-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_na_2_IPAD2-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_32-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_campaign_32-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_iron_32-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_heroic_32-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_na-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na_2-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cinematics_comic1-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_desert_3-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_desert-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle_2-hd.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level_0_2-hd.plist");


    numberOfLoadedRes=2;
}

void LoadingScene::logic(float dt)
{
    if(numberOfLoadedRes == 0)
    {
        loadSouce();
    }
    if (numberOfLoadedRes == 2)
    {
        auto scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(scene);
        
    }
}
