#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include <godot_cpp/classes/project_settings.hpp>


class DataManager {
    private:
        static const uint16_t MAX_RANDOM = std::numeric_limits<uint16_t>::max();
    
    public:
        DataManager() = delete;
        static void LoadAllData();

        static void initialize_project_settings();
        static void update_project_settings();
        
        static uint8_t* s_max_battle_teams;
        static uint8_t* s_max_team_size;
        static uint16_t* s_rarity_alternate_color_chance;
};

#endif // DATA_MANAGER_HPP