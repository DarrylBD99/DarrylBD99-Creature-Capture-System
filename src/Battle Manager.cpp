#include "Battle Manager.hpp"

#include <iostream>

// Initialize static member
godot::BattleField* BattleManager::s_current_battlefield = nullptr;
godot::UserInterface* BattleManager::s_current_userinterface = nullptr;
