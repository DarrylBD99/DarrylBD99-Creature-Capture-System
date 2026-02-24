#ifndef BATTLE_MANAGER_HPP
#define BATTLE_MANAGER_HPP

#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

#include <Resources/BattleTeam.hpp>
#include <Resources/BattleCreature.hpp>

#include <Nodes/BattleField.hpp>
#include <Nodes/UserInterface.hpp>
#include <Nodes/HealthBar.hpp>

using godot::Ref, godot::BattleTeam, godot::BattleCreature, std::vector;

class BattleManager {
    public:
        BattleManager() = delete;
        ~BattleManager() = delete;
        static godot::BattleField* s_current_battlefield;
        static godot::UserInterface* s_current_userinterface;

    private:
        struct BattleSide {
            vector<Ref<BattleTeam>> teams = {};
            vector<Ref<BattleCreature>> active_creatures = {};
        };
        
        BattleSide m_ally;
        BattleSide m_opponent;
};


#endif // BATTLE_MANAGER_HPP