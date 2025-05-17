#include "GameView.h"
USING_NS_CC;
cocos2d::Scene* GameView::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = GameView::create();
    scene->addChild(layer);
    return scene;
}

bool GameView::init()
{
    //mainController->setGameView(this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    int cornerWidth = 50;
    auto gameSizeW = visibleSize.width - 2 * cornerWidth;
    auto gameSizeH = visibleSize.height - 2 * cornerWidth;
    float topHeight = gameSizeH / 4;
    
    //����������
    auto brownLayer = LayerColor::create(Color4B(153, 102, 51, 255));
    brownLayer->setPosition(cornerWidth, cornerWidth);
    brownLayer->setContentSize(Size(gameSizeW,gameSizeH));
    this->addChild(brownLayer, -1); // ��ӵ����������ڵײ�

    // ����һ����ɫ�㣬Ϊ������
    auto purpleLayer = LayerColor::create(Color4B(153, 51, 153, 255)); // ��ɫ
    purpleLayer->setPosition(cornerWidth, cornerWidth);
    purpleLayer->setContentSize(Size(gameSizeW, topHeight));
    purpleLayer->setAnchorPoint(Vec2(0, 1));
    this->addChild(purpleLayer, -1);

    Color4B borderColor(200, 200, 200, 255); // ����ɫ
    //// ���������߿�
    auto topBorder = LayerColor::create(borderColor, visibleSize.width, cornerWidth);
    topBorder->setPosition(origin.x, origin.y + visibleSize.height - cornerWidth);
    this->addChild(topBorder, 1); // �����ϲ���ȷ���ɼ�

    //// �����ײ��߿�
    auto bottomBorder = LayerColor::create(borderColor, visibleSize.width, cornerWidth);
    bottomBorder->setPosition(origin.x, origin.y);
    this->addChild(bottomBorder, 1);

    //// ������߿�
    auto leftBorder = LayerColor::create(borderColor, cornerWidth, visibleSize.height);
    leftBorder->setPosition(origin.x, origin.y);
    this->addChild(leftBorder, 1);

    //// �����ұ߿�
    auto rightBorder = LayerColor::create(borderColor, cornerWidth, visibleSize.height);
    rightBorder->setPosition(origin.x + visibleSize.width - cornerWidth, origin.y);
    this->addChild(rightBorder, 1);

    //test cardview 
    //auto spriteNode = Node::create();
    ////auto model = std::make_shared<CardModel>(CardFaceType::CFT_EIGHT, CardSuitType::CST_CLUBS, 300.0, 400.0);
    //auto model = new CardModel(CardFaceType::CFT_EIGHT, CardSuitType::CST_CLUBS, 300.0, 400.0);
    //auto view = std::make_shared<CardView>(model, spriteNode);
    //view->drawCard();
    //this->addChild(spriteNode);
    mainController->startGame(1);

    return true;
}


GameView::GameView( GameModel& model)
{
    // ��ʼ���������ͱ����ƶ���ͼ
    for ( auto& card : model.getPlayfield()) {
        playfieldViews.emplace_back(&card, this);
    }
    for ( auto& card : model.getStack()) {
        stackViews.emplace_back(&card, this);
    }
    _bottomCardView = stackViews.back();
}

void GameView::updatePlayfieldView() {
    // ����������������
    for (auto& view : playfieldViews) {
        view.drawCard();
    }
}

void GameView::updateStackView()
{
    for (auto& view : stackViews) {
        view.drawCard();
    }
}

void GameView::updateBottomCardView()
{
    _bottomCardView.drawCard();
}

void GameView::playMatchAnimation(int index)
{
}

// ������������ʵ��...