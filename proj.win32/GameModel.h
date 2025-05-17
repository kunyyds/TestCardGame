#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include <vector>
#include "CardModel.h"

class GameModel {
private:
    std::vector<CardModel> _playfield;  // ������ģ��
    std::vector<CardModel> _stack;      // �����ƶ�ģ��           
    std::vector<CardModel*> _bottomCard; // ����ģ��
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
    bool matchPlayfieldCard(int index);  // ����ƥ��������ָ����������
    bool matchStackCard();               // ����ƥ�䱸���ƶѵ���
};

#endif // __GAME_MODEL_H__