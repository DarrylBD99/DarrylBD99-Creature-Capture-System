#include "Battle Manager.hpp"

#include <iostream>

// Initialize static member
godot::BattleField* BattleManager::s_current_battlefield = nullptr;
godot::Node* BattleManager::s_current_UI = nullptr;