#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "Card.h"
class CardModel {
private:
    CardFaceType _face;    // ��������
    CardSuitType _suit;    // ��ɫ
    float _x;    // �Ƶ�λ��
    float _y;
	//int _attribute; // �Ƶ�����:0�����ƣ�-1�����ƣ�1����
	CardZone _zoneType;   // �Ƶ�����
public:
    // ���캯��
    CardModel(CardFaceType f, CardSuitType s,float pos_x,float pos_y);
    CardModel(const CardModel& other);
    CardModel(Card& x);
    CardModel() = default;

    void setZone(CardZone zone) { this->_zoneType = zone; }
	CardZone getZoneType() const { return _zoneType; }
    // �ж��Ƿ�������һ����ƥ�䣨��ֵ��1��
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
