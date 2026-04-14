#ifndef BATTLE_INIT_HPP
#define BATTLE_INIT_HPP

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include "Resources/BattleTeam.hpp"
#include "Resources/BattleCreature.hpp"

class BattleInit {
    private:
        static godot::Error InitializeBattleField();
    public:
        BattleInit() = delete;
        static void start_battle(godot::Ref<godot::BattleTeam> BattleTeam, int player_format,int opponent_format);
        static void InitCreatures(godot::Ref<godot::BattleCreature> BattleCreature, int format,bool opponent);
        static godot::Error InitUserInterface();
};

#endif // BATTLE_INIT_HPP
