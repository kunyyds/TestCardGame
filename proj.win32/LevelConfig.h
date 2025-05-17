#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include <vector>
#include "Card.h"  

class LevelConfig {
public:
    int levelId;
    std::vector<Card> playfield;  // �洢Playfield����
    std::vector<Card> stack;      // �洢Stack����

    Card getPlayfieldCard(int index);
    Card getStackCard(int index);
    size_t getPlayfieldSize() const;
    size_t getStackSize() const;
};

#endif // __LEVEL_CONFIG_H__
