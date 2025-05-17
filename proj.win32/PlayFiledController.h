#ifndef PLAY_FILED_CONTROLLER_H
#define PLAY_FILED_CONTROLLER_H
#include"CardController.h"
#include <vector>
class PlayFieldController
{
private:
	std::vector<CardController> m_cards; // playfield of cards
public:
	void initController(); // Initialize the play field
};
extern PlayFieldController* g_playFieldController; // Global instance of PlayFieldController

#endif // !PLAY_FILED_CONTROLLER_H

