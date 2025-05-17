#include "GameController.h"
using namespace cocos2d;
cocos2d::Scene* GameController::startGame(int levelId) {
   
    // 从LevelConfig生成GameModel
    LevelConfig config = LevelConfigLoader::loadLevelConfig(levelId);
    _gameModel = GameModelFromLevelGenerator::generateGameModel(config);

    //初始化 控制器
    //this->initControllers();
    //init views
    this->initViews();
    
    this->drawViews();
    auto scene = cocos2d::Scene::create();
 
    
    scene->addChild(_gameView);
    _mainScene = scene;

    return scene;
}

void GameController::initControllers()
{
    // to do nothing now
}

void GameController::initViews()
{
    if (_gameView) {
        _gameView->removeFromParent(); // 如果需要,移除旧视图
        _gameView = nullptr;
    }

    _gameView = GameView::create(_gameModel.get());
    _gameView->init();
}

void GameController::drawViews()
{
    _gameView->drawPlayfieldView();
    _gameView->drawStackView();
    _gameView->drawBottomCardView();
}

void GameController::handleCardClick(CardModel* clickedCard,CardView* clickedCardView) {
    if (!clickedCard) return;

    // 获取当前手牌（假设GameModel维护手牌数据）
    CardModel* currentHandCard = _gameModel->getCurrentHandCard();

    switch (clickedCard->getZoneType()) {
    case CardZone::DESK_ZONE: {
        // 桌面牌区：检查面值差是否为1
        if (currentHandCard && clickedCard->canMatch(*currentHandCard)) {
            replaceHandCard(clickedCard,clickedCardView);  // 执行替换逻辑
        }
        break;
    }
    case CardZone::RESERVE_ZONE: {
        // 备用牌区：直接替换
        replaceHandCard(clickedCard,clickedCardView);
        break;
    }
    }
}
void GameController::replaceHandCard(CardModel* newCard,CardView* viewToUpdate) {
	auto handNow = _gameModel->getCurrentHandCard();
    // 更新手牌数据
    _gameModel->setBottomCard(*newCard);
    newCard->updatePosition(handNow->getPosX(), handNow->getPosY());
    viewToUpdate->updatePosition();
}

void GameController::handleUndoClick() {
    //auto prevState = undoModel->popUndoState();
    //if (prevState) {
    //    *gameModel = *prevState;  // 恢复历史状态
    //    gameView->updatePlayfieldView();  // 更新视图
    //}
}

static GameController con;
GameController* mainController = &con;