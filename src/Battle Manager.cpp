#include "Battle Manager.hpp"

#include <iostream>

// Initialize static member
godot::BattleField* BattleManager::s_current_battlefield = nullptr;
godot::UserInterface* BattleManager::s_current_userinterface = nullptr;



godot::Ref<godot::BattleTeam> BattleManager::m_player_team;

void BattleManager::set_player_team(const godot::Ref<godot::BattleTeam> &team) {
    m_player_team = team;
}

godot::Ref<godot::BattleTeam> BattleManager::get_player_team() const {
    return m_player_team;
}
