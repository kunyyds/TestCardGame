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
    Scene* createGameScene();//��ʼ����Ϸ����
private: 
    MySprite* _handCard;//��ǰ������
    Scene* _gameScene;
    std::vector<MySprite*> _playCards;
    std::vector<MySprite*> _reserveCards;
    std::vector<MySprite*> _handCards;
	std::stack<UndoOperation> _undoStack;
	void addToUndoStack(MySprite* sprite, float previousX, float previousY);//����һ����������
	void popOneUndoOperation();//һ�λ���
    void inithandCard(std::string& spritePath, CardFaceType nodeValue);//��ʼ������
    void replaceHandCard(MySprite* x);//�滻����λ��
    void startGame(int levelID);//��ʼ��Ϸ���������п��ƻ��ƺͼ���������
    void initPlayListeners(); //��ʼ�����������Ƶļ�����
	void initHandListeners(); //��ʼ������(���˶����ı����ƶ�)�ļ�����
	void initBackGround(); //��ʼ��������UI���
    //test
	void replaceSprite(Sprite* spriteToReplace, Sprite* replacementSprite);
    Sprite* _mySprite;
	void moveSprite(Ref*sender) { _mySprite->runAction(MoveTo::create(1.0f, Vec2(100, 100))); };
};

#endif // NEW_SCENE_H
