#ifndef __CARD_RES_CONFIG_H__
#define __CARD_RES_CONFIG_H__


#include <string>
#include "Enum.h"  //ֽ�ƻ�ɫ����ֵ��Ϣ

class CardResConfig {
private:
    //std::map<CardSuitType, std::string> suitTextures;  // ��ɫ-����ӳ��
    //std::map<CardFaceType, std::string> faceTextures;  // ����-����ӳ��
    
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