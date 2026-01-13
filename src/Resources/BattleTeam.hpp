#ifndef BATTLE_TEAM_H
#define BATTLE_TEAM_H

#include <godot_cpp/classes/resource.hpp>
#include <Resources/BattleCreature.hpp>

namespace godot {
    class BattleTeam : public Resource {
        GDCLASS(BattleTeam, Resource);
        
        private:
            // Add member variables here
            String m_team_name;
            vector<Ref<BattleCreature>> m_members;

        protected:
            static void _bind_methods();
            
        public:
            BattleTeam();
            virtual ~BattleTeam();
    };
};
#endif