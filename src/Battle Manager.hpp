#ifndef BATTLE_MANAGER_HPP
#define BATTLE_MANAGER_HPP

#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

#include <Resources/BattleTeam.hpp>
#include <Resources/BattleCreature.hpp>
#include <Resources/ActionResource.hpp>

#include <Nodes/BattleField.hpp>
#include <Nodes/UserInterface.hpp>
#include <Nodes/HealthBar.hpp>

using godot::Ref, godot::BattleTeam, godot::BattleCreature, std::vector;

class BattleManager {
    private:

        //removed m_active_creature, active creatures are whatever is currently in a slot
        struct CreatureSlot {
            godot::Ref<godot::BattleCreature> creature;
        };

        struct BattleSide {
            vector<BattleCreature*> active_creatures;
            vector<CreatureSlot*> creature_slots;
        };


        enum class BattleFormat : int { 
        Singles  = 1,
        Dobules  = 2,
        Triples  = 3,
        TwoVOne  = 4, // you + ally vs enemy (eg. route 8 with jake)
        TwoVTwo  = 5, // you + ally vs two enemies. none in PBB but PKMN unbound has a few examples
        };

        struct Battle {
            vector<BattleSide*> battle_sides;
            // for something like 2v1, you and your teammate would be on the same side DUH
            // to distinguish NPC vs player creatures `set_player` on the creature is used

            void occupy_slots(BattleFormat format);
        };

        static void occupy_team_slots(BattleSide* side,const godot::Ref<godot::BattleTeam>& team,int amount);
        
        


    public:
        BattleManager() = delete;
        static godot::BattleField* s_current_battlefield;
        static godot::UserInterface* s_current_userinterface;

        static godot::Ref<godot::BattleTeam> m_opponent_team;
        static godot::Ref<godot::BattleTeam> m_opponent_2_team;

        static godot::Ref<godot::BattleTeam> m_player_team;
        static godot::Ref<godot::BattleTeam> m_ally_team;

        static void set_player_team(const godot::Ref<godot::BattleTeam> &team);
        static godot::Ref<godot::BattleTeam> get_player_team();

        static vector<godot::Ref<godot::BattleCreature>> GetActiveCreatures();

        static vector<godot::Ref<godot::ActionResource>> m_actions; // inshallah cleared after every turn

        static void order_actions();
        static void play_turn();


};

#endif // BATTLE_MANAGER_HPP