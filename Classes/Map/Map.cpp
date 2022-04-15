#include "Map.h"
#include "Executioner.hpp"
#include <stdio.h>
USING_NS_CC;

MapScene* instance = NULL;
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

MapScene* MapScene::getInstance(){
    assert(instance!=NULL);
    return instance;
}
Scene* MapScene::createScene(){
    auto scene = Scene::create();
    auto layer = MapScene::create();
    instance = layer;
    scene->addChild(layer);
    return scene;
}

bool MapScene::init(){
//    if ( !Scene::init() ){
//        return false;
//    }
    // intialize the map member
    visibleSize = Director::getInstance()->getVisibleSize();
    money = 100;
    health = 100;
    MaxHealth = 100;
    is_clicked = false;
    init_path();
    init_grid();
    
    // intialize the map layer
    init_map_bg();
    init_mouse_listener();
    init_money_Label();
    init_health();
    init_gridSprite();
    init_monsterSprite();
    
    return true;
}



void MapScene::init_mouse_listener(){
    listener = EventListenerMouse::create();
    listener->onMouseMove=CC_CALLBACK_1(MapScene::onMouseMove, this);
    listener->onMouseUp=CC_CALLBACK_1(MapScene::onMouseUp, this);
    listener->onMouseDown=CC_CALLBACK_1(MapScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,map_bg);
}
void MapScene::onMouseMove(Event *event){
    EventMouse *e = (EventMouse *)event;
    if(is_clicked){
        listener->setEnabled(false);
        auto location = map_bg->getPosition();
        auto mapsize = map_bg->getContentSize();
        auto curr_pos = Vec2(e->getCursorX(),e->getCursorY());
        auto pos = location + curr_pos-mouse_last_pos;
        mouse_last_pos = Vec2(e->getCursorX(),e->getCursorY());
//        log("prev diff.x:%f, diff.y:%f",diff.x,diff.y);
        pos.x = MIN(pos.x, 0);
        pos.x = MAX(pos.x, -mapsize.width + visibleSize.width);
        pos.y = MIN(pos.y, 0);
        pos.y = MAX(pos.y, -mapsize.height + visibleSize.height);
//        log("afre rpos.x:%f, pos.y:%f",pos.x,pos.y);
        map_bg->setPosition(pos);
        listener->setEnabled(true);
    }
}
void MapScene::onMouseUp(Event *event){
    EventMouse *e = (EventMouse *)event;
//    log("Up");
    is_clicked = false;
}
void MapScene::onMouseDown(Event *event){
    EventMouse *e = (EventMouse *)event;
//    log("Clicked");
    mouse_last_pos = Vec2(e->getCursorX(),e->getCursorY());
    is_clicked = true;
}



void MapScene::init_path(){
    ValueMap plist = FileUtils::getInstance()->getValueMapFromFile("map/map1.plist");
    
    ValueVector path_array = plist["paths"].asValueVector();
    
    for(int i = 0;i<path_array.size();i++)
    {
        std::vector<std::vector<Vec2>> tempPathVector;
        auto path_array2 = path_array.at(i).asValueVector();
        for(int j = 0;j<path_array2.size();j++)
        {
            std::vector<Vec2> tempRandomPathVector;
            auto path_array3 = path_array2.at(j).asValueVector();
            for(int k =0;k<path_array3.size();k++)
            {
                auto tempDic = path_array3.at(k).asValueMap();
                Vec2 tempPath = Vec2();
                // TODO: adjust this to fix some path problem
                tempPath.x = tempDic["x"].asFloat()*1.15;
                tempPath.y = tempDic["y"].asFloat()*1.20 + 50;
                tempRandomPathVector.push_back(tempPath);
            }
            tempPathVector.push_back(tempRandomPathVector);
        }
        paths.push_back(tempPathVector);
    }
}
void MapScene::init_grid(){
    ValueMap plist = FileUtils::getInstance()->getValueMapFromFile("map/map1_grid.plist");
    // Tower
    auto tems = plist["Tower"].asValueVector();
    for(int i=0; i<tems.size(); i++){
        auto tem = tems.at(i).asValueMap();
        Rect tem_rect = Rect(tem["x"].asFloat(),tem["y"].asFloat(),
                             tem["w"].asFloat(),tem["h"].asFloat());
        tower_grids.push_back(tem_rect);
    }
    tems = plist["Shield"].asValueVector();
    for(int i=0; i<tems.size(); i++){
        auto tem = tems.at(i).asValueMap();
        Rect tem_rect = Rect(tem["x"].asFloat(),tem["y"].asFloat(),
                             tem["w"].asFloat(),tem["h"].asFloat());
        tower_grids.push_back(tem_rect);
    }
}



void MapScene::init_map_bg(){
    map_bg = Sprite::createWithSpriteFrameName("Stage_1.png");
    if(map_bg==nullptr) return false;
    map_bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    // set the centre map position
    // should be larger than 0
    auto mapsize = map_bg->getContentSize();
    float x = (mapsize.width-visibleSize.width)/2;
    float y = (mapsize.height-visibleSize.height)/2;
    map_bg->setPosition(-x,-y);
    addChild(map_bg, -1);
}
void MapScene::init_money_Label(){
    std::string str = "Money: ";
    str+=std::to_string(money);
    
    money_label = Label::createWithTTF(str, "Comic_Book.ttf", 36);
    if(money_label==nullptr){
        problemLoading("Comic_Book.ttf");
    } else{
//        log("???");
        money_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        money_label->setPosition(20,620);
        money_label->enableShadow();
        money_label->enableGlow(Color4B::YELLOW);
        money_label->setVisible(true);
        addChild(money_label,0);
    }
}
void MapScene::init_health(){
    auto sprite = Sprite::create("bar.png");   //创建进度框
    sprite->setScale(0.8f);
    sprite->setPosition(Point(visibleSize.width/2,visibleSize.height-30)); //设置框的位置
    this->addChild(sprite);            //加到默认图层里面去
    auto sprBlood = Sprite::create("blood.png");  //创建血条
    sprBlood->setOpacity(170);
    progress = ProgressTimer::create(sprBlood); //创建progress对象
    progress->setType(ProgressTimer::Type::BAR);        //类型：条状
    progress->setPosition(Point(visibleSize.width/2,visibleSize.height-30));
        //从右到左减少血量
    progress->setMidpoint(Point(0,0.5));     //如果是从左到右的话，改成(1,0.5)即可
    progress->setBarChangeRate(Point(1,0));
    progress->setScale(0.8f);
    this->addChild(progress);
    schedule(CC_SCHEDULE_SELECTOR(MapScene::scheduleBlood), 0.1f);  //刷新函数，每隔0.1秒
}
void MapScene::scheduleBlood(float delta){
    progress->setPercentage((((float)health)/MaxHealth)*100);  //这里是百分制显示
    char tem[16];
    sprintf(tem, "Money: %d", money);
    money_label->setString(std::string(tem));
    // 死亡后不再调度
    if (progress->getPercentage() < 0) {
        this->unschedule(CC_SCHEDULE_SELECTOR(MapScene::scheduleBlood));
    }
}
void MapScene::init_gridSprite(){
    for(int i=0; i<tower_grids.size(); i++){
        Vec2 point = tower_grids.at(i).origin;
        auto tem = Terrian::createTerrian(1);
        tem->setPosition(point);
        tem->setTag(i);
        buildable.push_back(tem);
        map_bg->addChild(tem);
    }
}
void MapScene::init_monsterSprite(){
    auto m1 = Executioner::createMonster(paths.at(0).at(0));
    map_bg->addChild(m1);
    auto m2 = Executioner::createMonster(paths.at(0).at(1));
    map_bg->addChild(m2);
    monsterlist.push_back(m1);
    monsterlist.push_back(m2);
}


void MapScene::onEnterTransitionDidFinish(){
    scheduleUpdate();
}
