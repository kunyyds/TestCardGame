#ifndef __CARD_RES_CONFIG_H__
#define __CARD_RES_CONFIG_H__


#include <string>
#include "Enum.h"  //纸牌花色和数值信息

class CardResConfig {
private:
    //std::map<CardSuitType, std::string> suitTextures;  // 花色-纹理映射
    //std::map<CardFaceType, std::string> faceTextures;  // 牌面-纹理映射
    
public:
    CardResConfig(std::string s1, std::string s2) :suitResPath(s1), faceResPath(s2) {};
    CardResConfig() = default;
    std::string suitResPath;
    std::string faceResPath;
    std::string getSuitTexture(CardSuitType suit);
    std::string getFaceTexture(CardFaceType face, CardSuitType suit);
    
};
extern CardResConfig* cardRes;

#endif // __CARD_RES_CONFIG_H__