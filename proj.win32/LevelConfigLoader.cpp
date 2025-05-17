#include "LevelConfigLoader.h"
#include "json/json.h"
#include "Enum.h"
#include "cocos2d.h"
#include <fstream>

LevelConfig LevelConfigLoader::loadLevelConfig(int levelId) {
    LevelConfig config;
    std::string s = "D:/Code/cpp/Cards/Test/Resources/res/levels/level1.json";
    std::ifstream file(s);

    if (file.is_open()) {
        Json::Value root;
        file >> root;

        if (!root.isMember("Playfield") || !root.isMember("Stack")) {
            cocos2d::log("Error: Missing required fields in JSON.");
            return config;
        }

        const Json::Value playfieldJson = root["Playfield"];
        for (int i = 0; i < playfieldJson.size(); ++i) {
            Card card;
            card.cardFace = static_cast<CardFaceType>(playfieldJson[i]["CardFace"].asInt());
            card.cardSuit = static_cast<CardSuitType>(playfieldJson[i]["CardSuit"].asInt());
            card.positionX = playfieldJson[i]["Position"]["x"].asInt();
            card.positionY = playfieldJson[i]["Position"]["y"].asInt();
            config.playfield.push_back(card);
        }

        const Json::Value stackJson = root["Stack"];
        for (int i = 0; i < stackJson.size(); ++i) {
            Card card;
            card.cardFace = static_cast<CardFaceType>(stackJson[i]["CardFace"].asInt());
            card.cardSuit = static_cast<CardSuitType>(stackJson[i]["CardSuit"].asInt());
            card.positionX = stackJson[i]["Position"]["x"].asInt();
            card.positionY = stackJson[i]["Position"]["y"].asInt();
            config.stack.push_back(card);
        }
    }
    else {
        cocos2d::log("Failed to open level config file.");
    }

    return config;
}