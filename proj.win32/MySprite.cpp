#include "MySprite.h"
bool MySprite::init(const std::string& spritePath, CardFaceType nodeValue) {
    if (!Node::init()) {
        return false;
    }

    // ��ʼ��_sprite
    _sprite = cocos2d::Sprite::create(spritePath);
    if (_sprite == nullptr) {
        // ����޷�����Sprite������ѡ����������ֱ�ӷ���false
        return false;
    }
	_spriteBackground = cocos2d::Sprite::create("cards/card_general.png"); // ����ͼ
    if(_spriteBackground == nullptr) {
        // ����޷�����Sprite������ѡ����������ֱ�ӷ���false
        return false;
	}
    // ���ýڵ�ֵ
    _faceValue = nodeValue;

    // ��sprite���Ϊ�ӽڵ�
    this->addChild(_spriteBackground); // ��ӱ���ͼ
    this->addChild(_sprite);
	
    // ��ѡ�����ó�ʼλ�õ�����
    //_sprite->setPosition(this->getContentSize() / 2);

    return true;
}