#ifndef __GAME_MODEL_FROM_LEVEL_GENERATOR_H__
#define __GAME_MODEL_FROM_LEVEL_GENERATOR_H__

#include <memory>
#include "LevelConfig.h"
#include "GameModel.h"
#include "CardModel.h" 

class GameModel;
class GameModelFromLevelGenerator {
public:
    static std::shared_ptr<GameModel> generateGameModel( LevelConfig& levelConfig);
};

#endif // __GAME_MODEL_FROM_LEVEL_GENERATOR_H__