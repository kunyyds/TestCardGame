#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include <vector>
#include "Card.h"  

class LevelConfig {
public:
    int levelId;
    std::vector<Card> playfield;  // 存储Playfield数组
    std::vector<Card> stack;      // 存储Stack数组

    Card getPlayfieldCard(int index);
    Card getStackCard(int index);
    size_t getPlayfieldSize() const;
    size_t getStackSize() const;
};

#endif // __LEVEL_CONFIG_H__
