#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__

#include "CardModel.h"
#include "CardResConfig.h"
#include "cocos2d.h"

class CardView {
private:
    CardModel* _model;        // ��������ģ��
    cocos2d::Node* _parentNode; //�������п��ƵĽڵ�
    cocos2d::Sprite* _sprite;
public:
    CardView(CardModel* m, cocos2d::Node* node) :_model(m), _parentNode(node),_sprite(nullptr) {};
    CardView() = default;
    void drawCard();               // �����Ƶ�UI
    void updatePosition();
};

#endif // __CARD_VIEW_H__