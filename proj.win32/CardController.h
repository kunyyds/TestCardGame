#ifndef __CARD_CONTROLLER_H__
#define __CARD_CONTROLLER_H__

class CardModel;
class CardView;

class CardController {
private:
    CardModel* cardModel;  // 牌模型
    CardView* cardView;    // 牌视图

public:
    CardController(CardModel* m, CardView* v);
    void handleCardClick();  // 处理牌点击事件
    void updateCardView();   // 更新牌视图
};

#endif // __CARD_CONTROLLER_H__
