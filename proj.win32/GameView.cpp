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
    
    //桌面牌区域
    auto brownLayer = LayerColor::create(Color4B(153, 102, 51, 255));
    brownLayer->setPosition(cornerWidth, cornerWidth);
    brownLayer->setContentSize(Size(gameSizeW,gameSizeH));
    this->addChild(brownLayer, -1); // 添加到场景并置于底层

    // 创建一个紫色层，为手牌区
    auto purpleLayer = LayerColor::create(Color4B(153, 51, 153, 255)); // 紫色
    purpleLayer->setPosition(cornerWidth, cornerWidth);
    purpleLayer->setContentSize(Size(gameSizeW, topHeight));
    purpleLayer->setAnchorPoint(Vec2(0, 1));
    this->addChild(purpleLayer, -1);

    Color4B borderColor(200, 200, 200, 255); // 淡灰色
    //// 创建顶部边框
    auto topBorder = LayerColor::create(borderColor, visibleSize.width, cornerWidth);
    topBorder->setPosition(origin.x, origin.y + visibleSize.height - cornerWidth);
    this->addChild(topBorder, 1); // 置于上层以确保可见

    //// 创建底部边框
    auto bottomBorder = LayerColor::create(borderColor, visibleSize.width, cornerWidth);
    bottomBorder->setPosition(origin.x, origin.y);
    this->addChild(bottomBorder, 1);

    //// 创建左边框
    auto leftBorder = LayerColor::create(borderColor, cornerWidth, visibleSize.height);
    leftBorder->setPosition(origin.x, origin.y);
    this->addChild(leftBorder, 1);

    //// 创建右边框
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
        
        // 创建鼠标事件监听器
        auto mouseListener = EventListenerMouse::create();
        // 绑定鼠标按下事件
        mouseListener->onMouseDown = [sprite](cocos2d::Event* event) {
            cocos2d::EventMouse* mouseEvent = static_cast<cocos2d::EventMouse*>(event);

            // 获取鼠标点击位置（视图坐标系）
            cocos2d::Vec2 clickPosInView = mouseEvent->getLocationInView();

            // 将点击位置转换为精灵的本地坐标系
            cocos2d::Vec2 localClickPos = sprite->convertToNodeSpace(clickPosInView);

            // 检查点击是否在精灵区域内
            if (sprite->getBoundingBox().containsPoint(localClickPos)) {
                // 点击命中精灵，执行旋转
                //sprite->runAction(cocos2d::RotateBy::create(0.2f, 30.0f)); // 0.2秒内旋转30度
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

    // 初始化主牌区和备用牌堆视图
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
    // 绘制主牌区所有牌
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

// 其他方法类似实现...