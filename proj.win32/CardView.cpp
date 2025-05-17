#include "CardView.h"  
#include "GameController.h"  
#include "cocos2d.h"  
using namespace cocos2d;  

void CardView::drawCard() {  
    auto texturePath = cardRes->getFaceTexture(this->_model->getFace(), this->_model->getSuit());  

    _sprite = cocos2d::Sprite::create(texturePath);  
    if (_sprite) {  
        _sprite->setPosition(_model->getPosX(), _model->getPosY());  
        // ... 添加到父节点 ...  
        _parentNode->addChild(_sprite, 1);  
        // 添加触摸监听器  

        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = [this](Event* event) {
            EventMouse* e = (EventMouse*)event;
            // 将鼠标位置转换为相对于_sprite的坐标  
            Vec2 localPos = _sprite->convertToNodeSpace(e->getLocationInView());
            if (_sprite->getBoundingBox().containsPoint(localPos)) {
                // 触发控制器处理点击事件  
                mainController->handleCardClick(_model, this);
            }
            };

        auto eventDispatcher = Director::getInstance()->getEventDispatcher();
        eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, _sprite);

    } else {  
        cocos2d::log("path error");  
    }  
}  

void CardView::updatePosition() {  
    if (_sprite && _model) {  
        _sprite->setPosition(_model->getPosX(), _model->getPosY());  
    }  
}