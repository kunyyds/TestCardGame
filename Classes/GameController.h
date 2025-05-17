#ifndef __GAME_CONTROLLER_H__  
#define __GAME_CONTROLLER_H__  
#include "cocos2d.h"  
#include "GameModelGen.h"  // 服务层类  
#include "LevelConfigLoader.h"  
#include "GameView.h"

class GameController {  
private:  
    GameView* _gameView;                     // 游戏视图  
    cocos2d::Scene* _mainScene;              // 游戏scene 
    std::shared_ptr<GameModel> _gameModel;   
     
public:  
    cocos2d::Scene* startGame(int levelId);  // 开始游戏  
    void initControllers();  
    void initViews();  
    void drawViews();  
    void handleCardClick(CardModel*, CardView*);  // 处理牌点击事件  
    void replaceHandCard(CardModel* newCard, CardView*);  // 替换手牌  
    void handleUndoClick();  // 处理回退按钮点击  
};  

extern GameController* mainController;  

#endif // __GAME_CONTROLLER_H__