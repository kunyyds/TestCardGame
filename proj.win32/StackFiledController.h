#ifndef STACK_FIELD_CONTROLLER_H
#define STACK_FIELD_CONTROLLER_H

#include "CardController.h"
#include <vector>
class StackFieldController
{
private:
	std::vector<CardController> m_cards; // Stack of cards
public:
	void initController(); // Initialize the stack field
};
extern StackFieldController* g_stackFieldController; // Global instance of StackFieldController

#endif // !STACK_FIELD_CONTROLLER_H

