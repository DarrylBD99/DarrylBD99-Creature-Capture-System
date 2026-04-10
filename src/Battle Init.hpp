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
        static void SingleBattle();
        static void WildBattle(godot::Ref<godot::BattleTeam> BattleTeam, uint8_t level);
        static void InitCreatures(godot::Ref<godot::BattleCreature> BattleCreature, int level,bool opponent);
        static void InitUserInterface();
};

#endif // BATTLE_INIT_HPP
