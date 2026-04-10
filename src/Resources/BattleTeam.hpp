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
            TypedArray<BattleCreature> m_members;

        protected:
            static void _bind_methods();
            
        public:
            BattleTeam();
            virtual ~BattleTeam();

            void set_team_name(const String &name);
            String get_team_name() const;

            void set_members(const Array &members);
            Array get_members() const;

            void add_member(const Ref<BattleCreature> &member);
            void clear_members();

            int get_member_count() const;
            Ref<BattleCreature> get_member(int index) const;

    };
};
#endif