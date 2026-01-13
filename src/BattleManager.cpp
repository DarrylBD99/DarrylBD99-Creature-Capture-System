#include "BattleManager.hpp"

#include <iostream>

BattleManager BattleManager::s_Instance;

void BattleManager::battle_base() {
    std::cout << "Battle started!" << std::endl;
}

const bool BattleManager::is_wild_encounter() {
    return m_opponent.teams.empty();
}