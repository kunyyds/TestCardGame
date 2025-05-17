#include "CardModel.h"

CardModel::CardModel(CardFaceType f, CardSuitType s, float pos_x, float pos_y)
    : _face(f), _suit(s),_x(pos_x),_y(pos_y ) {
	//_attribute = 0;
}

CardModel::CardModel(const CardModel& other)
{
    this->_face = other._face;
    this->_suit = other._suit;
    this->_x = other._x;
    this->_y = other._y;
}

CardModel::CardModel(Card& other)
{
    this->_face = other.cardFace;
    this->_suit = other.cardSuit;
    this->_x = other.positionX;
    this->_y = other.positionY;
}

bool CardModel::canMatch(const CardModel& other) const {
    int temp = static_cast<int>(_face) - static_cast<int>(other._face);
    if (temp <= 1 && temp >= -1) {
        return true;
    }
    return false;
}