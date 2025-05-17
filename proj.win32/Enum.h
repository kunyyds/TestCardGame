#ifndef _ENUM_H
#define _ENUM_H
// 花色类型
enum class CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // 梅花_Black
    CST_DIAMONDS,   // 方块_RED
    CST_HEARTS,     // 红桃_RED
    CST_SPADES,     // 黑桃_BLACK
    CST_NUM_CARD_SUIT_TYPES
};

// 正面类型
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
    DESK_ZONE,    // 桌面牌区
    RESERVE_ZONE  // 备用牌区
};

#endif // !_ENUM_H


