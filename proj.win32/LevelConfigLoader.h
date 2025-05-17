#ifndef LEVEL_CONFIG_LOADER_H
#define LEVEL_CONFIG_LOADER_H

#include "LevelConfig.h"

class LevelConfigLoader {
public:
    // 加载指定关卡的配置（静态方法，直接通过类调用）
    static LevelConfig loadLevelConfig(int levelId);
};

#endif // LEVEL_CONFIG_LOADER_H