#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "Card.h"
class CardModel {
private:
    CardFaceType _face;    // 牌面数字
    CardSuitType _suit;    // 花色
    float _x;    // 牌的位置
    float _y;
	//int _attribute; // 牌的属性:0桌面牌，-1备用牌，1手牌
	CardZone _zoneType;   // 牌的区域
public:
    // 构造函数
    CardModel(CardFaceType f, CardSuitType s,float pos_x,float pos_y);
    CardModel(const CardModel& other);
    CardModel(Card& x);
    CardModel() = default;

    void setZone(CardZone zone) { this->_zoneType = zone; }
	CardZone getZoneType() const { return _zoneType; }
    // 判断是否能与另一张牌匹配（数值差1）
    bool canMatch(const CardModel& other) const;

    // Getter
    CardFaceType getFace() const { return _face; }
    CardSuitType getSuit() const { return _suit; }
    
    int getPosX() const{ return _x; }
    int getPosY() const { return _y; }
    /*void setController(CardController* controller) { _controller = controller; }
    CardController* getController() const { return _controller; }*/
	void updatePosition(float x, float y) { _x = x; _y = y; }
};

#endif // __CARD_MODEL_H__
