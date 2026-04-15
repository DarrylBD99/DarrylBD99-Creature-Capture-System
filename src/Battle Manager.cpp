#include "Battle Manager.hpp"

#include <iostream>
#include <algorithm>
#include <Resources/BattleCreature.hpp>

// Initialize static member
godot::BattleField* BattleManager::s_current_battlefield = nullptr;
godot::UserInterface* BattleManager::s_current_userinterface = nullptr;

godot::Ref<godot::BattleTeam> BattleManager::m_player_team;
godot::Ref<godot::BattleTeam> BattleManager::m_opponent_team;

vector<godot::Ref<godot::BattleCreature>> BattleManager::m_active_creatures;



void BattleManager::set_player_team(const godot::Ref<godot::BattleTeam> &team) {
    m_player_team = team;

    auto members = m_player_team->get_members();

    for (int i = 0; i < members.size(); i++){
        godot::Ref<godot::BattleCreature> creature = members[i];
        creature->set_player(true); //does this
    }
}

godot::Ref<godot::BattleTeam> BattleManager::get_player_team() const {
    return m_player_team;
}


void BattleManager::order_active_creatures_by_speed() {

    m_active_creatures.clear();

    for (int i = 0; i < m_player_team->get_member_count(); i++) {
        if (m_player_team->get_member(i)->get_active()){
        m_active_creatures.push_back(m_player_team->get_member(i));
        }
    }

    for (int i = 0; i < m_opponent_team->get_member_count(); i++) {
        if (m_opponent_team->get_member(i)->get_active()){
        m_active_creatures.push_back(m_opponent_team->get_member(i));
        }
    }

    std::sort(m_active_creatures.begin(), m_active_creatures.end(),
    [](const godot::Ref<godot::BattleCreature> &a,
       const godot::Ref<godot::BattleCreature> &b) {
        return a->get_speed_stat() > b->get_speed_stat();
    });

}

vector<godot::Ref<godot::BattleCreature>> BattleManager::GetActiveCreatures() {
    return m_active_creatures;
}