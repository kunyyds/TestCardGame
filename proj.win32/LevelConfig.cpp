#include "LevelConfig.h"

Card LevelConfig::getPlayfieldCard(int index) {
    return playfield.at(index);  // 需处理越界异常
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