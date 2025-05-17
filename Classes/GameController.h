#ifndef __GAME_CONTROLLER_H__  
#define __GAME_CONTROLLER_H__  
#include "cocos2d.h"  
#include "GameModelGen.h"  // �������  
#include "LevelConfigLoader.h"  
#include "GameView.h"

class GameController {  
private:  
    GameView* _gameView;                     // ��Ϸ��ͼ  
    cocos2d::Scene* _mainScene;              // ��Ϸscene 
    std::shared_ptr<GameModel> _gameModel;   
     
public:  
    cocos2d::Scene* startGame(int levelId);  // ��ʼ��Ϸ  
    void initControllers();  
    void initViews();  
    void drawViews();  
    void handleCardClick(CardModel*, CardView*);  // �����Ƶ���¼�  
    void replaceHandCard(CardModel* newCard, CardView*);  // �滻����  
    void handleUndoClick();  // ������˰�ť���  
};  

extern GameController* mainController;  

#endif // __GAME_CONTROLLER_H__