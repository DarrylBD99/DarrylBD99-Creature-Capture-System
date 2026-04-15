#ifndef BATTLE_CREATURE_H
#define BATTLE_CREATURE_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <Resources/StaticData/Species.hpp>
#include <Resources/StaticData/Attacks.hpp>


namespace godot {
    class BattleCreature : public Resource {
        GDCLASS(BattleCreature, Resource);
        
        private:
            // Add member variables here
            Ref<SpeciesResource> m_species_resource;
            StringName m_creature_name;

            bool m_is_active = false;
            bool m_is_player = false;

            int m_level = 1;
            
            // Stats
            int m_max_hp = 1;
            int m_current_hp = 1;
            int m_attack_stat = 1;
            int m_defense_stat = 1;
            int m_speed_stat = 1;

            TypedArray<AttackResource> m_attacks;

        protected:
            static void _bind_methods();
            
        public:
            BattleCreature();
            virtual ~BattleCreature();
        
        void InitBattleCreature();
        
        void set_species_resource(const Ref<SpeciesResource> resource);
        void set_creature_id(const StringName &id);
        void set_creature_name(const StringName &name);
        void set_active(bool active);
        void set_player(bool player);
        void set_level(int level);
        void set_max_hp(int max_hp);
        void set_current_hp(int current_hp);
        void set_attack_stat(int attack);
        void set_defense_stat(int defense);
        void set_speed_stat(int speed);

        // Getters
        Ref<SpeciesResource> get_species_resource() const;
        StringName get_creature_id() const;
        StringName get_creature_name() const;
        TypedArray<AttackResource> get_creature_attacks() const;
        bool get_active() const;
        bool get_player() const;
        int get_level() const;
        int get_max_hp() const;
        int get_current_hp() const;
        int get_attack_stat() const;
        int get_defense_stat() const;
        int get_speed_stat() const;

        void set_attacks(const Array &attacks);
        Array get_attacks() const;

        void add_attack(const Ref<AttackResource> &attack);
        void clear_attacks();

        int get_attack_count() const;
        Ref<AttackResource> get_attack(int index) const;
    };
};
#endif