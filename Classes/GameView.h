#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include <vector>
#include "GameModel.h"
#include "CardView.h"

class GameView : public cocos2d::Layer {
private:
    std::vector<CardView> playfieldViews;  // ��������ͼ
    std::vector<CardView> stackViews;      // �����ƶ���ͼ
    GameModel* _model = nullptr;           // ����GameModelָ��
    std::vector<CardView> _handCards;
public:
    static GameView* create(GameModel* model); // ��̬��������
    virtual bool init() override;
    bool initWithModel(GameModel* model);      // ��GameModel��ʼ��

    void drawPlayfieldView();  // ������������ͼ
    void drawStackView();      // ���±����ƶ���ͼ
    void drawBottomCardView(); // ���µ�����ͼ
    void playMatchAnimation(int index);  // ����ƥ�䶯��
};

#endif // __GAME_VIEW_H__