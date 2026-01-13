#ifndef BATTLE_CREATURE_H
#define BATTLE_CREATURE_H

#include <godot_cpp/classes/resource.hpp>

namespace godot {
    class BattleCreature : public Resource {
        GDCLASS(BattleCreature, Resource);
        
        private:
            // Add member variables here
            StringName m_creature_id;
            int m_level = 1;
            
            // Stats
            int m_max_hp = 10;
            int m_current_hp = 10;
            int m_attack = 5;
            int m_defense = 5;
            int m_speed = 5;

        protected:
            static void _bind_methods();
            
        public:
            BattleCreature();
            virtual ~BattleCreature();
    };
};
#endif