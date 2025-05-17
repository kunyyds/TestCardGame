#include "GameController.h"
using namespace cocos2d;
cocos2d::Scene* GameController::startGame(int levelId) {
   
    // ��LevelConfig����GameModel
    LevelConfig config = LevelConfigLoader::loadLevelConfig(levelId);
    _gameModel = GameModelFromLevelGenerator::generateGameModel(config);

    //��ʼ�� ������
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
        _gameView->removeFromParent(); // �����Ҫ,�Ƴ�����ͼ
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

    // ��ȡ��ǰ���ƣ�����GameModelά���������ݣ�
    CardModel* currentHandCard = _gameModel->getCurrentHandCard();

    switch (clickedCard->getZoneType()) {
    case CardZone::DESK_ZONE: {
        // ���������������ֵ���Ƿ�Ϊ1
        if (currentHandCard && clickedCard->canMatch(*currentHandCard)) {
            replaceHandCard(clickedCard,clickedCardView);  // ִ���滻�߼�
        }
        break;
    }
    case CardZone::RESERVE_ZONE: {
        // ����������ֱ���滻
        replaceHandCard(clickedCard,clickedCardView);
        break;
    }
    }
}
void GameController::replaceHandCard(CardModel* newCard,CardView* viewToUpdate) {
	auto handNow = _gameModel->getCurrentHandCard();
    // ������������
    _gameModel->setBottomCard(*newCard);
    newCard->updatePosition(handNow->getPosX(), handNow->getPosY());
    viewToUpdate->updatePosition();
}

void GameController::handleUndoClick() {
    //auto prevState = undoModel->popUndoState();
    //if (prevState) {
    //    *gameModel = *prevState;  // �ָ���ʷ״̬
    //    gameView->updatePlayfieldView();  // ������ͼ
    //}
}

static GameController con;
GameController* mainController = &con;