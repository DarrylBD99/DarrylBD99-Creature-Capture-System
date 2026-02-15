#ifndef BATTLE_INIT_HPP
#define BATTLE_INIT_HPP

#include <godot_cpp/variant/string_name.hpp>

class BattleInit {
    private:
        static void InitializeBattleField();
    public:
        BattleInit() = delete;
        static void SingleBattle();
        static void WildBattle(godot::StringName species, uint8_t level);
};

#endif // BATTLE_INIT_HPP