#include "MySprite.h"
bool MySprite::init(const std::string& spritePath, CardFaceType nodeValue) {
    if (!Node::init()) {
        return false;
    }

    // 初始化_sprite
    _sprite = cocos2d::Sprite::create(spritePath);
    if (_sprite == nullptr) {
        // 如果无法加载Sprite，可以选择处理错误或者直接返回false
        return false;
    }
	_spriteBackground = cocos2d::Sprite::create("cards/card_general.png"); // 背景图
    if(_spriteBackground == nullptr) {
        // 如果无法加载Sprite，可以选择处理错误或者直接返回false
        return false;
	}
    // 设置节点值
    _faceValue = nodeValue;

    // 将sprite添加为子节点
    this->addChild(_spriteBackground); // 添加背景图
    this->addChild(_sprite);
	
    // 可选：设置初始位置等属性
    //_sprite->setPosition(this->getContentSize() / 2);

    return true;
}