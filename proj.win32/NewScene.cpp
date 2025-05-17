#include "NewScene.h"

cocos2d::Scene* NewScene::createScene() {	
	auto scene = Scene::create();
	return scene;
}

NewScene::~NewScene()
{
	for (auto card : _handCards) {
		CC_SAFE_RELEASE(card);
	}
	_handCards.clear();
	CC_SAFE_RELEASE(_handCard);
}

MySprite* NewScene::getMySprite() const {
	return _handCard;
}

NewScene* NewScene::create() {
	NewScene* ret = new (std::nothrow) NewScene();
	if (ret ) {
		ret->autorelease(); // 加入自动释放池
		return ret;
	}
	else {
		delete ret;
		return nullptr;
	}
}

void NewScene::addToUndoStack(MySprite* sprite, float previousX, float previousY)
{
	_undoStack.push(UndoOperation(sprite,previousX,previousY));
	sprite->retain(); // 保留精灵的引用计数;
}

void NewScene::popOneUndoOperation()
{
	if (!_undoStack.empty()) {
		UndoOperation operation = _undoStack.top();
		_undoStack.pop(); // 弹出操作
		MySprite* sprite = operation.sprite;
		float previousX = operation.previousX;
		float previousY = operation.previousY;
		sprite->setPosition(previousX, previousY); // 恢复位置
		//sprite->release(); // 释放引用计数

		//恢复手牌
		if (!_handCards.empty()) {
			MySprite* handCard = _handCards.back();
			_handCards.pop_back(); // 弹出手牌
			handCard->setVisible(true); // 显示手牌
			_handCard = handCard; // 更新当前手牌
		}
	}
	else {
		CCLOG("Undo stack is empty.");
	}
}

void NewScene::inithandCard(std::string& spritePath, CardFaceType nodeValue) {
	if (_handCard != nullptr) {
		_handCard->release(); // 释放旧的引用
	}
	_handCard = MySprite::create(spritePath, nodeValue);
	if (_handCard != nullptr) {
		//_handCard->retain(); // 增加引用计数
	}
	else {
		CCLOG("Failed to create MySprite.");
	}
}

void NewScene::replaceHandCard(MySprite* x)
{
	if (x == nullptr) {
		CCLOG("x is null.");
		return;
	}
	if (_handCard == nullptr) {
		CCLOG("_handCard is null.");
		return;
	}
	// 检查 _handCard 是否已经被释放
	if (_handCard->getReferenceCount() == 0) {
		CCLOG("_handCard has already been released.");
		return;
	}
	auto position = _handCard->getPosition();
	auto moveTo = MoveTo::create(1.0,position);
	x->runAction(moveTo);//x->setPosition(position);
	_handCard->setVisible(false);
	_handCards.push_back(_handCard); // 将新的 x 添加到手牌列表中
	x->retain(); // 保留x的引用计数
	// 设置新 _handCard 的位置
	
	_handCard = x;
}

void NewScene::startGame(int levelID)
{
	//初始化手牌
	LevelConfig config = LevelConfigLoader::loadLevelConfig(levelID);
	//桌面牌区
	for (int i = 0; i < config.getPlayfieldSize();i++) {
		Card card= config.getPlayfieldCard(i);
		float x = card.positionX, y = card.positionY;
		auto playSprite = MySprite::create(cardRes->getFaceTexture(card.cardFace, card.cardSuit), card.cardFace);
		playSprite->setPosition(x, y);
		playSprite->retain();
		_playCards.push_back(playSprite);
		//加入视图
		_gameScene->addChild(playSprite);
	}

	//保留牌区
	for (int i = 0; i < config.getStackSize() - 1; i++) {
		Card card = config.getStackCard(i);
		float x = card.positionX, y = card.positionY;
		auto stackSprite = MySprite::create(cardRes->getFaceTexture(card.cardFace, card.cardSuit), card.cardFace);
		stackSprite->setPosition(x, y);
		stackSprite->retain();
		_reserveCards.push_back(stackSprite);
		//加入视图
		_gameScene->addChild(stackSprite);
	}

	//当前手牌
	if (config.getStackSize() >= 1) {
		Card card = config.getStackCard(config.getStackSize() - 1);
		float x = card.positionX, y = card.positionY;
		std::string path = cardRes->getFaceTexture(card.cardFace, card.cardSuit);
		this->inithandCard(path, card.cardFace);
		CCLOG("MySprite reference count: %d", _handCard->getReferenceCount());
		_handCard->setPosition(x, y);
		_gameScene->addChild(_handCard); CCLOG("MySprite reference count: %d", _handCard->getReferenceCount());
	}
}

void NewScene::initPlayListeners()
{
	for (auto& card : _playCards)
	{
		auto listener = EventListenerMouse::create();
		listener->onMouseDown = [&](EventMouse* event) {
			const Vec2 mousePos(event->getCursorX(), event->getCursorY());
			Vec2 localMousePos = card->getParent()->convertToNodeSpace(mousePos);
			int originX = card->getPositionX();
			int originY = card->getPositionY();
			int width = card->getContentSize().x;
			int height = card->getContentSize().y;

			if ((localMousePos.x >= originX && localMousePos.x <= originX + width) &&
				(localMousePos.y <= originY && localMousePos.y >= originY - height)
				//&&card == _playCards.back()
				)
			{
				CardFaceType clickedCardValue = card->getFaceValue();

				if (abs(static_cast<int>(clickedCardValue) - static_cast<int>(_handCard->getFaceValue())) <= 1)
				{
					//记录回退
					addToUndoStack(card, card->getPositionX(), card->getPositionY());
					replaceHandCard(card);
					
				
				}
			}
			};

		_gameScene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, card);
	}
}

void NewScene::initHandListeners()
{
	for (auto& card : _reserveCards)
	{
		auto listener = EventListenerMouse::create();
		listener->onMouseDown = [&](EventMouse* event) {
			// 检查鼠标点击的坐标是否在精灵的边界内
			const Vec2 mousePos(event->getCursorX(), event->getCursorY());
			Vec2 localMousePos = card->getParent()->convertToNodeSpace(mousePos); 
			int width = card->getContentSize().x;
			int height = card->getContentSize().y;
			int originX = card->getPositionX() - width / 2;
			int originY = card->getPositionY() - height / 2;
			
			if (
				(localMousePos.x >= originX && localMousePos.x <= originX + width)&&
				(localMousePos.y>=originY && localMousePos.y<=originY+height)
				) 
			{
				//记录回退
				addToUndoStack(card, card->getPositionX(), card->getPositionY());
				replaceHandCard(card);	
			}
			};

		_gameScene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, card);
	}
}

void NewScene::initBackGround()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int cornerWidth = 50;
	auto gameSizeW = visibleSize.width - 2 * cornerWidth;
	auto gameSizeH = visibleSize.height - 2 * cornerWidth;
	float topHeight = gameSizeH / 4;
	// 创建一个棕色层，为桌面牌区域
	auto brownLayer = LayerColor::create(Color4B(153, 102, 51, 255));
	brownLayer->setPosition(cornerWidth, cornerWidth);
	brownLayer->setContentSize(Size(gameSizeW, gameSizeH));
	_gameScene->addChild(brownLayer, -1); // 添加到场景并置于底层

	// 创建一个紫色层，为手牌区
	auto purpleLayer = LayerColor::create(Color4B(153, 51, 153, 255)); // 紫色
	purpleLayer->setPosition(cornerWidth, cornerWidth);
	purpleLayer->setContentSize(Size(gameSizeW, topHeight));
	purpleLayer->setAnchorPoint(Vec2(0, 1));
	_gameScene->addChild(purpleLayer, -1);

	Color4B borderColor(200, 200, 200, 255); // 淡灰色
	//// 创建顶部边框
	auto topBorder = LayerColor::create(borderColor, visibleSize.width, cornerWidth);
	topBorder->setPosition(origin.x, origin.y + visibleSize.height - cornerWidth);
	_gameScene->addChild(topBorder, 1); // 置于上层以确保可见

	//// 创建底部边框
	auto bottomBorder = LayerColor::create(borderColor, visibleSize.width, cornerWidth);
	bottomBorder->setPosition(origin.x, origin.y);
	_gameScene->addChild(bottomBorder, 1);

	//// 创建左边框
	auto leftBorder = LayerColor::create(borderColor, cornerWidth, visibleSize.height);
	leftBorder->setPosition(origin.x, origin.y);
	_gameScene->addChild(leftBorder, 1);

	//// 创建右边框
	auto rightBorder = LayerColor::create(borderColor, cornerWidth, visibleSize.height);
	rightBorder->setPosition(origin.x + visibleSize.width - cornerWidth, origin.y);
	_gameScene->addChild(rightBorder, 1);

	auto menuNode = Node::create();
	menuNode->setName("menuNode");
	int index = 2;

	auto menuItem1 = MenuItemFont::create("Back OFF");
	menuItem1->setFontNameObj("Marker Felt.ttf");
	menuItem1->setFontSizeObj(64);
	menuItem1->setName("menuItem1");
	menuItem1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2).x,
		(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height).y - (index) * 40));
	menuItem1->setCallback([&](cocos2d::Ref* sender) {
		this->popOneUndoOperation();
		});

	auto menu = Menu::create(menuItem1, NULL);
	menu->setName("menu");
	menuNode->addChild(menu, 1);
	menu->setPosition(Vec2::ZERO);
	_gameScene->addChild(menuNode, 1); // 添加到场景中
}

Scene* NewScene::createGameScene()
{
	_gameScene = Scene::create();

	auto dirs = Director::getInstance();
	Size visibleSize = dirs->getVisibleSize();
	Vec2 origin = dirs->getVisibleOrigin();
	//初始化游戏
	this->startGame(1);
	this->initBackGround();
	this->initPlayListeners();
	this->initHandListeners();
	std::string path1 = "HelloWorld.png";
	_mySprite = Sprite::create(path1);
	_mySprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	//_gameScene->addChild(_mySprite);

	//handcard test
	std::string path2 = "cards/card_general.png";
	
	// 添加鼠标点击监听器
	auto mouseListener = cocos2d::EventListenerMouse::create();

	return _gameScene;
}

void NewScene::replaceSprite(cocos2d::Sprite* spriteToReplace, cocos2d::Sprite* replacementSprite) {
	if (spriteToReplace == nullptr || replacementSprite == nullptr) {
		CCLOG("One of the sprites is null.");
		return;
	}
	// 获取目标精灵的位置和Z序
	auto position = spriteToReplace->getPosition();
	int zOrder = spriteToReplace->getLocalZOrder();

	// 将替换精灵添加到相同的父节点（如果它还没有被添加）
	auto parentNode = spriteToReplace->getParent();
	if (parentNode != nullptr && replacementSprite->getParent() != parentNode) {
		//parentNode->addChild(replacementSprite, zOrder);
	}

	// 设置替换精灵的位置和Z序
	replacementSprite->setPosition(position);
	replacementSprite->setLocalZOrder(zOrder);

	// 隐藏原始精灵
	spriteToReplace->setVisible(false);

	// 如果需要的话，你还可以调整其他属性，例如缩放、旋转等
	// replacementSprite->setScale(spriteToReplace->getScale());
	// replacementSprite->setRotation(spriteToReplace->getRotation());
}