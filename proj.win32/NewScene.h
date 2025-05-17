#ifndef NEW_SCENE_H
#define NEW_SCENE_H

#include "cocos2d.h"
#include "MySprite.h"
#include "CardResConfig.h"
#include "LevelConfigLoader.h"
#include <stack>
USING_NS_CC;

struct UndoOperation
{
	UndoOperation() : sprite(nullptr), previousX(0), previousY(0) {}
	UndoOperation(MySprite* sprite, float previousX, float previousY) : sprite(sprite), previousX(previousX), previousY(previousY) {}
    MySprite* sprite;
	float previousX;
	float previousY;
};

class NewScene: public Ref
{
public:
    static NewScene* create();
    static cocos2d::Scene* createScene();

    NewScene() :_handCard(nullptr) {};
    ~NewScene();
    MySprite* getMySprite() const;
    Scene* createGameScene();//初始化游戏界面
private: 
    MySprite* _handCard;//当前的手牌
    Scene* _gameScene;
    std::vector<MySprite*> _playCards;
    std::vector<MySprite*> _reserveCards;
    std::vector<MySprite*> _handCards;
	std::stack<UndoOperation> _undoStack;
	void addToUndoStack(MySprite* sprite, float previousX, float previousY);//增加一个撤销操作
	void popOneUndoOperation();//一次回退
    void inithandCard(std::string& spritePath, CardFaceType nodeValue);//初始化手牌
    void replaceHandCard(MySprite* x);//替换手牌位置
    void startGame(int levelID);//开始游戏，包括所有卡牌绘制和监听器生成
    void initPlayListeners(); //初始化所有桌面牌的监听器
	void initHandListeners(); //初始化手牌(除了顶部的备用牌堆)的监听器
	void initBackGround(); //初始化背景和UI组件
    //test
	void replaceSprite(Sprite* spriteToReplace, Sprite* replacementSprite);
    Sprite* _mySprite;
	void moveSprite(Ref*sender) { _mySprite->runAction(MoveTo::create(1.0f, Vec2(100, 100))); };
};

#endif // NEW_SCENE_H
