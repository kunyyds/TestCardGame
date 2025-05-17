#include "GameView.h"

USING_NS_CC;

GameView* GameView::create(GameModel* model)
{
    GameView* ret = new (std::nothrow) GameView();
    if (ret && ret->initWithModel(model)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool GameView::init()
{
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

    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        //problemLoading("'HelloWorld.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        
        // ��������¼�������
        auto mouseListener = EventListenerMouse::create();
        // ����갴���¼�
        mouseListener->onMouseDown = [sprite](cocos2d::Event* event) {
            cocos2d::EventMouse* mouseEvent = static_cast<cocos2d::EventMouse*>(event);

            // ��ȡ�����λ�ã���ͼ����ϵ��
            cocos2d::Vec2 clickPosInView = mouseEvent->getLocationInView();

            // �����λ��ת��Ϊ����ı�������ϵ
            cocos2d::Vec2 localClickPos = sprite->convertToNodeSpace(clickPosInView);

            // ������Ƿ��ھ���������
            if (sprite->getBoundingBox().containsPoint(localClickPos)) {
                // ������о��飬ִ����ת
                //sprite->runAction(cocos2d::RotateBy::create(0.2f, 30.0f)); // 0.2������ת30��
                auto moveBy = MoveBy::create(2, Vec2(20, 0));
                sprite->runAction(moveBy);
            }
            };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, sprite);
        this->addChild(sprite);
    }
    return true;
}

bool GameView::initWithModel(GameModel* model)
{
    if (!Layer::init()) return false;
    _model = model;

    // ��ʼ���������ͱ����ƶ���ͼ
    playfieldViews.clear();
    stackViews.clear();
    for (auto& card : _model->getPlayfield()) {
        playfieldViews.emplace_back(&card, this);
    }
    for (auto& card : _model->getStack()) {
        stackViews.emplace_back(&card, this);
    }
    if (!stackViews.empty()) {
        auto lastView = stackViews.back();
        stackViews.pop_back();
        _handCards.push_back(lastView);
    }
        

    return true;
}



void GameView::drawPlayfieldView() {
    // ����������������
    for (auto& view : playfieldViews) {
        view.drawCard();
    }
}

void GameView::drawStackView()
{
    for (auto& view : stackViews) {
        view.drawCard();
    }
}

void GameView::drawBottomCardView()
{
    _handCards.back().drawCard();
}



void GameView::playMatchAnimation(int index)
{
}

// ������������ʵ��...