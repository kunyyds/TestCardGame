#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include <vector>
#include "CardModel.h"

class GameModel {
private:
    std::vector<CardModel> _playfield;  // 主牌区模型
    std::vector<CardModel> _stack;      // 备用牌堆模型           
    std::vector<CardModel*> _bottomCard; // 底牌模型
public:
    void addPlayfieldCard( CardModel& card) {
        _playfield.push_back(card);
    };
    std::vector<CardModel>& getPlayfield() { return _playfield; }
    void addStackCard( CardModel& card) { 
        _stack.push_back(card); 
    };
    std::vector<CardModel>& getStack() { return _stack; }
    void setBottomCard(CardModel& card) { 
        _bottomCard.push_back(&card); 
  
    };
    CardModel* getCurrentHandCard() { 
        if(_bottomCard.empty()) {
            return nullptr; 
		}
        return _bottomCard.back(); 
    }
    bool matchPlayfieldCard(int index);  // 尝试匹配主牌区指定索引的牌
    bool matchStackCard();               // 尝试匹配备用牌堆的牌
};

#endif // __GAME_MODEL_H__