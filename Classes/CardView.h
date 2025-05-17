#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__

#include "CardModel.h"
#include "CardResConfig.h"
#include "cocos2d.h"

class CardView {
private:
    CardModel* _model;        // 关联的牌模型
    cocos2d::Node* _parentNode; //承载所有卡牌的节点
    cocos2d::Sprite* _sprite;
public:
    CardView(CardModel* m, cocos2d::Node* node) :_model(m), _parentNode(node),_sprite(nullptr) {};
    CardView() = default;
    void drawCard();               // 绘制牌的UI
    void updatePosition();
};

#endif // __CARD_VIEW_H__