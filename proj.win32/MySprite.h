#include "cocos2d.h"
#include "Enum.h"
class MySprite : public cocos2d::Node {
public:
    // 创建方法，遵循Cocos2d-x的内存管理模式
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
    cocos2d::Sprite* _sprite; // 指向Sprite的指针
	cocos2d::Sprite* _spriteBackground; // 指向背景Sprite的指针
    //int _nodeValue;           // 节点值
    CardFaceType _faceValue; //纸牌数值
	int _posAtibute; // 纸牌位置属性0桌面牌，1备用牌，2手牌

    // 构造函数默认是protected或private，以强制使用create方法创建对象
    MySprite() : _sprite(nullptr),_faceValue(CardFaceType::CFT_NONE),_posAtibute(0) {}
    virtual ~MySprite() {
        CC_SAFE_RELEASE(_sprite); // 确保 _sprite 被正确释放
    }
    // 初始化方法
    bool init(const std::string& spritePath, CardFaceType nodeValue);
    void setNodeValue(int value) { _faceValue = static_cast<CardFaceType>(value); }
};

