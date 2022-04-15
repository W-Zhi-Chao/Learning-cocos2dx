#ifndef Map_h
#define Map_h

#include "cocos2d.h"
#include "Terrian.hpp"
#include "Monster.hpp"
USING_NS_CC;

#define BLOOD_BAR 0

typedef enum{PLACEABLE, UNPLACEABLE, PATH} GridType;

typedef std::vector<Rect> Grids;
typedef std::vector<Vec2> Path;
typedef std::vector<std::vector<Path>> Paths;
// divide the map 960*640 into 32*24 grid
class MapScene : public Layer
{
public:
    static cocos2d::Scene* createScene();
    static MapScene* getInstance();
    virtual bool init();
    
    void init_health();
    void scheduleBlood(float delta);
    void init_map_bg();
    void init_money_Label();
    void init_gridSprite();
    void init_monsterSprite();
    void update_money();
    
    void logic(); // 场景逻辑函数
    void onEnterTransitionDidFinish();
    
    bool is_clicked;
    Vec2 mouse_last_pos;
    void onMouseMove(Event *event);
    void onMouseUp(Event *event);
    void onMouseDown(Event *event);
    void init_mouse_listener();
    
    void read_map(const std::string& str);
    void init_path();
    void init_grid();
    
    CREATE_FUNC(MapScene);
    
    // 滚动地图
    EventListenerMouse *listener;
    Sprite *map_bg;
    std::vector<Terrian*> buildable;
    // 使用什么容器???
    std::list<Monster*> monsterlist;
    Size visibleSize; // 窗口大小

    Label *money_label;
    ProgressTimer *progress;
    
    int MaxHealth;
    int health; // 生命值
    int money; // 金钱
    Paths paths; // 地图的路线
    Grids tower_grids; // 塔的放置位置
    Grids shield_grids; // 守卫的放置位置
//    void onEnterTransitionDidFinish();
};

#endif /* Map_h */
