#ifndef BATTLE_INIT_HPP
#define BATTLE_INIT_HPP

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include "Battle Manager.hpp"
#include "Resources/BattleTeam.hpp"
#include "Resources/BattleCreature.hpp"
#include "Resources/StaticData/BattleFormats.hpp"

class BattleInit {
    private:
        static godot::Error InitializeBattleField();
    public:


        BattleInit() = delete;
        static void start_battle(godot::Ref<godot::BattleTeam> BattleTeam, int format,int opponent_format);
        static void InitCreatures(const godot::Ref<godot::BattleTeam>& team,  BattleFormat format,bool opponent);
        static godot::Error InitUserInterface();

};

#endif // BATTLE_INIT_HPP
