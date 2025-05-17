#include "GameModel.h"






bool GameModel::matchPlayfieldCard(int index) {
    // 示例逻辑：检查主牌区是否有可匹配的牌（需根据实际规则实现）
    if (index < 0 || index >= _playfield.size()) return false;
    // ... 具体匹配逻辑 ...
    return true;
}

bool GameModel::matchStackCard() {
    // 示例逻辑：检查备用牌堆是否有可匹配的牌
    // ... 具体匹配逻辑 ...
    return true;
}