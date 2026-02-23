#ifndef BATTLE_MANAGER_HPP
#define BATTLE_MANAGER_HPP

#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

#include <Resources/BattleTeam.hpp>
#include <Resources/BattleCreature.hpp>

#include <Nodes/BattleField.hpp>

using godot::Ref, godot::BattleTeam, godot::BattleCreature, std::vector;

class BattleManager {
    private:
        struct BattleSide {
            vector<BattleTeam*> teams;
            vector<BattleCreature*> active_creatures;
        };

    public:
        BattleManager() = delete;
        static godot::BattleField* s_current_battlefield;
        static BattleSide s_ally;
        static BattleSide s_opp;

};


#endif // BATTLE_MANAGER_HPP