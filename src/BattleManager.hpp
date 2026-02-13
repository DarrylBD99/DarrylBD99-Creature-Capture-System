#ifndef BATTLEMANAGER_HPP
#define BATTLEMANAGER_HPP

#include <cstdlib>
#include <ctime>
#include <vector>

#include <Resources/BattleTeam.hpp>
#include <Resources/BattleCreature.hpp>

using godot::Ref, godot::BattleTeam, godot::BattleCreature, std::vector;

class BattleManager {
    public:
        BattleManager(const BattleManager&) = delete;
        static BattleManager& GetInstance() { return s_Instance; }
        static const int MAX_RANDOM = 65534;
        static const int MAX_BATTLE_TEAMS = 3;

    private:
        struct BattleSide {
            vector<Ref<BattleTeam>> teams = {};
            vector<Ref<BattleCreature>> active_creatures = {};
        };

        static BattleManager s_Instance;
        
        BattleSide m_ally;
        BattleSide m_opponent;
        void battle_base();

        const bool is_wild_encounter();
        const bool is_boss_encounter();

        BattleManager(){ srand(time(NULL)); };
};


#endif // BATTLEMANAGER_HPP