#include "Battle Manager.hpp"

#include <iostream>

// Initialize static member
godot::BattleField* BattleManager::s_current_battlefield = nullptr;
godot::HealthBar* BattleManager::s_current_healthbarUI = nullptr;
