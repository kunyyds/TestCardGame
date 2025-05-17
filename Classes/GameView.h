#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include <vector>
#include "GameModel.h"
#include "CardView.h"

class GameView : public cocos2d::Layer {
private:
    std::vector<CardView> playfieldViews;  // 主牌区视图
    std::vector<CardView> stackViews;      // 备用牌堆视图
    GameModel* _model = nullptr;           // 持有GameModel指针
    std::vector<CardView> _handCards;
public:
    static GameView* create(GameModel* model); // 静态工厂方法
    virtual bool init() override;
    bool initWithModel(GameModel* model);      // 用GameModel初始化

    void drawPlayfieldView();  // 更新主牌区视图
    void drawStackView();      // 更新备用牌堆视图
    void drawBottomCardView(); // 更新底牌视图
    void playMatchAnimation(int index);  // 播放匹配动画
};

#endif // __GAME_VIEW_H__