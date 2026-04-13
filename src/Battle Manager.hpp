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
    private:
        struct BattleSide {
            //vector<BattleTeam*> teams; ? -fevernova
            vector<BattleCreature*> active_creatures;
        };


    public:
        BattleManager() = delete;
        static godot::BattleField* s_current_battlefield;
        static godot::UserInterface* s_current_userinterface;

        static godot::Ref<godot::BattleTeam> m_opponent_team;
        static godot::Ref<godot::BattleTeam> m_player_team;

        static void set_player_team(const godot::Ref<godot::BattleTeam> &team);
        godot::Ref<godot::BattleTeam> get_player_team() const;

        static vector<godot::Ref<godot::BattleCreature>> m_active_creatures;

        static void order_active_creatures_by_speed();

};

#endif // BATTLE_MANAGER_HPP