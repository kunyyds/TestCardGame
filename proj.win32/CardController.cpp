#include "CardController.h"
#include "CardView.h"
#include "CardModel.h"
CardController::CardController(CardModel* m, CardView* v)
    : cardModel(m), cardView(v) {
    // 设置模型和视图相互关联
   /* cardModel->setController(this);*/
}

void CardController::handleCardClick() {
    // 示例：触发牌的匹配逻辑（调用GameController）
    // ... 具体逻辑 ...
}

void CardController::updateCardView() {
    cardView->updatePosition();
}