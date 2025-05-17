#include "cocos2d.h"
#include "Enum.h"
class MySprite : public cocos2d::Node {
public:
    // ������������ѭCocos2d-x���ڴ����ģʽ
    static MySprite* create(const std::string& spritePath, CardFaceType nodeValue) {
        MySprite* ret = new (std::nothrow) MySprite();
        if (ret && ret->init(spritePath, nodeValue)) {
            ret->autorelease();
            CCLOG("MySprite reference count in creat: %d", ret->getReferenceCount());
            return ret;
        }
        else {
            delete ret;
            return nullptr;
        }
    }
    CardFaceType getFaceValue() const
    {
        return _faceValue;
    }
    virtual cocos2d::Vec2 getContentSize() {
        return _spriteBackground->getContentSize();
    }
protected:
    cocos2d::Sprite* _sprite; // ָ��Sprite��ָ��
	cocos2d::Sprite* _spriteBackground; // ָ�򱳾�Sprite��ָ��
    //int _nodeValue;           // �ڵ�ֵ
    CardFaceType _faceValue; //ֽ����ֵ
	int _posAtibute; // ֽ��λ������0�����ƣ�1�����ƣ�2����

    // ���캯��Ĭ����protected��private����ǿ��ʹ��create������������
    MySprite() : _sprite(nullptr),_faceValue(CardFaceType::CFT_NONE),_posAtibute(0) {}
    virtual ~MySprite() {
        CC_SAFE_RELEASE(_sprite); // ȷ�� _sprite ����ȷ�ͷ�
    }
    // ��ʼ������
    bool init(const std::string& spritePath, CardFaceType nodeValue);
    void setNodeValue(int value) { _faceValue = static_cast<CardFaceType>(value); }
};

