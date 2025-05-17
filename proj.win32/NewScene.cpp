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
		ret->autorelease(); // �����Զ��ͷų�
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
	sprite->retain(); // ������������ü���;
}

void NewScene::popOneUndoOperation()
{
	if (!_undoStack.empty()) {
		UndoOperation operation = _undoStack.top();
		_undoStack.pop(); // ��������
		MySprite* sprite = operation.sprite;
		float previousX = operation.previousX;
		float previousY = operation.previousY;
		sprite->setPosition(previousX, previousY); // �ָ�λ��
		//sprite->release(); // �ͷ����ü���

		//�ָ�����
		if (!_handCards.empty()) {
			MySprite* handCard = _handCards.back();
			_handCards.pop_back(); // ��������
			handCard->setVisible(true); // ��ʾ����
			_handCard = handCard; // ���µ�ǰ����
		}
	}
	else {
		CCLOG("Undo stack is empty.");
	}
}

void NewScene::inithandCard(std::string& spritePath, CardFaceType nodeValue) {
	if (_handCard != nullptr) {
		_handCard->release(); // �ͷžɵ�����
	}
	_handCard = MySprite::create(spritePath, nodeValue);
	if (_handCard != nullptr) {
		//_handCard->retain(); // �������ü���
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
	// ��� _handCard �Ƿ��Ѿ����ͷ�
	if (_handCard->getReferenceCount() == 0) {
		CCLOG("_handCard has already been released.");
		return;
	}
	auto position = _handCard->getPosition();
	auto moveTo = MoveTo::create(1.0,position);
	x->runAction(moveTo);//x->setPosition(position);
	_handCard->setVisible(false);
	_handCards.push_back(_handCard); // ���µ� x ��ӵ������б���
	x->retain(); // ����x�����ü���
	// ������ _handCard ��λ��
	
	_handCard = x;
}

void NewScene::startGame(int levelID)
{
	//��ʼ������
	LevelConfig config = LevelConfigLoader::loadLevelConfig(levelID);
	//��������
	for (int i = 0; i < config.getPlayfieldSize();i++) {
		Card card= config.getPlayfieldCard(i);
		float x = card.positionX, y = card.positionY;
		auto playSprite = MySprite::create(cardRes->getFaceTexture(card.cardFace, card.cardSuit), card.cardFace);
		playSprite->setPosition(x, y);
		playSprite->retain();
		_playCards.push_back(playSprite);
		//������ͼ
		_gameScene->addChild(playSprite);
	}

	//��������
	for (int i = 0; i < config.getStackSize() - 1; i++) {
		Card card = config.getStackCard(i);
		float x = card.positionX, y = card.positionY;
		auto stackSprite = MySprite::create(cardRes->getFaceTexture(card.cardFace, card.cardSuit), card.cardFace);
		stackSprite->setPosition(x, y);
		stackSprite->retain();
		_reserveCards.push_back(stackSprite);
		//������ͼ
		_gameScene->addChild(stackSprite);
	}

	//��ǰ����
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
					//��¼����
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
			// ���������������Ƿ��ھ���ı߽���
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
				//��¼����
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
	// ����һ����ɫ�㣬Ϊ����������
	auto brownLayer = LayerColor::create(Color4B(153, 102, 51, 255));
	brownLayer->setPosition(cornerWidth, cornerWidth);
	brownLayer->setContentSize(Size(gameSizeW, gameSizeH));
	_gameScene->addChild(brownLayer, -1); // ��ӵ����������ڵײ�

	// ����һ����ɫ�㣬Ϊ������
	auto purpleLayer = LayerColor::create(Color4B(153, 51, 153, 255)); // ��ɫ
	purpleLayer->setPosition(cornerWidth, cornerWidth);
	purpleLayer->setContentSize(Size(gameSizeW, topHeight));
	purpleLayer->setAnchorPoint(Vec2(0, 1));
	_gameScene->addChild(purpleLayer, -1);

	Color4B borderColor(200, 200, 200, 255); // ����ɫ
	//// ���������߿�
	auto topBorder = LayerColor::create(borderColor, visibleSize.width, cornerWidth);
	topBorder->setPosition(origin.x, origin.y + visibleSize.height - cornerWidth);
	_gameScene->addChild(topBorder, 1); // �����ϲ���ȷ���ɼ�

	//// �����ײ��߿�
	auto bottomBorder = LayerColor::create(borderColor, visibleSize.width, cornerWidth);
	bottomBorder->setPosition(origin.x, origin.y);
	_gameScene->addChild(bottomBorder, 1);

	//// ������߿�
	auto leftBorder = LayerColor::create(borderColor, cornerWidth, visibleSize.height);
	leftBorder->setPosition(origin.x, origin.y);
	_gameScene->addChild(leftBorder, 1);

	//// �����ұ߿�
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
	_gameScene->addChild(menuNode, 1); // ��ӵ�������
}

Scene* NewScene::createGameScene()
{
	_gameScene = Scene::create();

	auto dirs = Director::getInstance();
	Size visibleSize = dirs->getVisibleSize();
	Vec2 origin = dirs->getVisibleOrigin();
	//��ʼ����Ϸ
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
	
	// ��������������
	auto mouseListener = cocos2d::EventListenerMouse::create();

	return _gameScene;
}

void NewScene::replaceSprite(cocos2d::Sprite* spriteToReplace, cocos2d::Sprite* replacementSprite) {
	if (spriteToReplace == nullptr || replacementSprite == nullptr) {
		CCLOG("One of the sprites is null.");
		return;
	}
	// ��ȡĿ�꾫���λ�ú�Z��
	auto position = spriteToReplace->getPosition();
	int zOrder = spriteToReplace->getLocalZOrder();

	// ���滻������ӵ���ͬ�ĸ��ڵ㣨�������û�б���ӣ�
	auto parentNode = spriteToReplace->getParent();
	if (parentNode != nullptr && replacementSprite->getParent() != parentNode) {
		//parentNode->addChild(replacementSprite, zOrder);
	}

	// �����滻�����λ�ú�Z��
	replacementSprite->setPosition(position);
	replacementSprite->setLocalZOrder(zOrder);

	// ����ԭʼ����
	spriteToReplace->setVisible(false);

	// �����Ҫ�Ļ����㻹���Ե����������ԣ��������š���ת��
	// replacementSprite->setScale(spriteToReplace->getScale());
	// replacementSprite->setRotation(spriteToReplace->getRotation());
}