#include "GameModelGen.h"


std::shared_ptr<GameModel> GameModelFromLevelGenerator::generateGameModel(LevelConfig& levelConfig) {
    // Create a new GameModel instance
    auto gameModel = std::make_shared<GameModel>();
      
    // Add playfield cards from LevelConfig
    for (size_t i = 0; i < levelConfig.getPlayfieldSize(); ++i) {
        Card playfieldCard = levelConfig.getPlayfieldCard(i);
        CardModel cardModel(playfieldCard); // Convert Card to CardModel
        cardModel.setZone(CardZone::DESK_ZONE);
        gameModel->addPlayfieldCard(cardModel);  
    }

    // Add stack cards from LevelConfig
    for (size_t i = 0; i < levelConfig.getStackSize(); ++i) {
        Card stackCard = levelConfig.getStackCard(i);
        CardModel cardModel(stackCard); // Convert Card to CardModel
        cardModel.setZone(CardZone::RESERVE_ZONE);
        gameModel->addStackCard(cardModel);  
    }

    // Set bottom card
    if(levelConfig.getStackSize() > 0) {
        //Card bottomCard = levelConfig.getStackCard(levelConfig.getStackSize() - 1);
        //CardModel cardModel(bottomCard); // Convert Card to CardModel
        //cardModel.setZone(CardZone::RESERVE_ZONE);
        gameModel->setBottomCard(gameModel->getStack().back());  
	}
   

    return gameModel;
}