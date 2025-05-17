#ifndef _ENUM_H
#define _ENUM_H
// ��ɫ����
enum class CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // ÷��_Black
    CST_DIAMONDS,   // ����_RED
    CST_HEARTS,     // ����_RED
    CST_SPADES,     // ����_BLACK
    CST_NUM_CARD_SUIT_TYPES
};

// ��������
enum class CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

enum class CardZone {
    DESK_ZONE,    // ��������
    RESERVE_ZONE  // ��������
};

#endif // !_ENUM_H


