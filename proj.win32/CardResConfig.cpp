#include "CardResConfig.h"



std::string CardResConfig::getSuitTexture(CardSuitType suit) {
    std::string pngPath;
    switch (suit) {
    case CardSuitType:: CST_CLUBS:
        pngPath = "club.png";
        break;
    case CardSuitType::CST_DIAMONDS:
        pngPath = "diamond.png";
        break;
    case  CardSuitType::CST_HEARTS:
        pngPath = "heart.png";
        break;
    case CardSuitType::CST_SPADES:
        pngPath = "spade.png";
        break;
    default:
        pngPath = "";
        break;
    }
    //
    return this->suitResPath + pngPath;
}

std::string CardResConfig::getFaceTexture(CardFaceType face, CardSuitType suit) {
    std::string color;
    std::string num;
    if (suit ==CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES) {
        color = "_black_";
    }
    else if (suit == CardSuitType::CST_DIAMONDS || suit == CardSuitType::CST_HEARTS) {

        color = "_red_";
    }
    else {
        //不合法的花色数据
    }
    switch (face) {
    case CardFaceType::CFT_ACE:
        num = "A";
        break;
    case  CardFaceType::CFT_TWO:
        num = "2";
        break;
    case  CardFaceType::CFT_THREE:
        num = "3";
        break;
    case CardFaceType::CFT_FOUR:
        num = "4";
        break;
    case  CardFaceType::CFT_FIVE:
        num = "5";
        break;
    case CardFaceType::CFT_SIX:
        num = "6";
        break;
    case CardFaceType::CFT_SEVEN:
        num = "7";
        break;
    case CardFaceType::CFT_EIGHT:
        num = "8";
        break;
    case CardFaceType::CFT_NINE:
        num = "9";
        break;
    case CardFaceType::CFT_TEN:
        num = "10";
        break;
    case CardFaceType::CFT_JACK:
        num = "J";
        break;
    case CardFaceType::CFT_QUEEN:
        num = "Q";
        break;
    case CardFaceType::CFT_KING:
        num = "K";
        break;
    default:
        //不合法的数字
        num = "0";
        break;
    }
    return this->faceResPath+"big"+color + num + ".png";
}

static CardResConfig source("cards/suits","cards/number/");
CardResConfig* cardRes = &source;

