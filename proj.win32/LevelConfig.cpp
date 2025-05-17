#include "LevelConfig.h"

Card LevelConfig::getPlayfieldCard(int index) {
    return playfield.at(index);  // �账��Խ���쳣
}

Card LevelConfig::getStackCard(int index) {
    return stack.at(index);
}

size_t LevelConfig::getPlayfieldSize() const {
    return playfield.size();
}

size_t LevelConfig::getStackSize() const {
    return stack.size();
}