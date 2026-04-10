#ifndef BATTLE_CREATURE_H
#define BATTLE_CREATURE_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <Resources/StaticData/Species.hpp>

namespace godot {
    class BattleCreature : public Resource {
        GDCLASS(BattleCreature, Resource);
        
        private:
            // Add member variables here
            Ref<SpeciesResource> m_species_resource;

            StringName m_creature_name;

            int m_level = 1;
            
            // Stats
            int m_max_hp = 1;
            int m_current_hp = 1;
            int m_attack = 1;
            int m_defense = 1;
            int m_speed = 1;

        protected:
            static void _bind_methods();
            
        public:
            BattleCreature();
            virtual ~BattleCreature();
        
        void InitBattleCreature();
        
        void set_species_resource(const Ref<SpeciesResource> resource);
        void set_creature_id(const StringName &id);
        void set_creature_name(const StringName &name);
        void set_level(int level);
        void set_max_hp(int max_hp);
        void set_current_hp(int current_hp);
        void set_attack(int attack);
        void set_defense(int defense);
        void set_speed(int speed);

        // Getters
        Ref<SpeciesResource> get_species_resource() const;
        StringName get_creature_id() const;
        StringName get_creature_name() const;
        int get_level() const;
        int get_max_hp() const;
        int get_current_hp() const;
        int get_attack() const;
        int get_defense() const;
        int get_speed() const;
    };
};
#endif