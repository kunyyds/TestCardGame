#ifndef LEVEL_CONFIG_LOADER_H
#define LEVEL_CONFIG_LOADER_H

#include "LevelConfig.h"

class LevelConfigLoader {
public:
    // ����ָ���ؿ������ã���̬������ֱ��ͨ������ã�
    static LevelConfig loadLevelConfig(int levelId);
};

#endif // LEVEL_CONFIG_LOADER_H