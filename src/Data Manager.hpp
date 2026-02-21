#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

#include <nodes/BattleField.hpp>


class DataManager {
    private:
        static const uint16_t MAX_RANDOM = std::numeric_limits<uint16_t>::max();
    
    public:
        DataManager() = delete;
        ~DataManager() = delete;

        static void initialize_project_settings();
        static void update_project_settings();
        static void free_data();

        static godot::ProjectSettings* project_setting;
        static godot::Node* s_battle_singleton;

        static godot::Ref<godot::SpriteFrames> s_creature_sprite_frames;
        
        static uint8_t* s_max_battle_teams;
        static uint8_t* s_max_team_size;
        static uint16_t* s_alternate_color_rarity;

        static godot::String* s_default_battlefield_path;
};

#endif // DATA_MANAGER_HPP