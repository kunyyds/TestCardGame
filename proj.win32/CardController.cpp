#include "CardController.h"
#include "CardView.h"
#include "CardModel.h"
CardController::CardController(CardModel* m, CardView* v)
    : cardModel(m), cardView(v) {
    // ����ģ�ͺ���ͼ�໥����
   /* cardModel->setController(this);*/
}

void CardController::handleCardClick() {
    // ʾ���������Ƶ�ƥ���߼�������GameController��
    // ... �����߼� ...
}

void CardController::updateCardView() {
    cardView->updatePosition();
}