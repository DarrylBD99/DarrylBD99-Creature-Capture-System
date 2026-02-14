#include "Data Manager.hpp"
#include <Battle Manager.hpp>

#include <godot_cpp/variant/string.hpp>
#include <vector>
#include <map>

// Static member definitions
uint16_t* DataManager::s_rarity_alternate_color_chance = nullptr;
uint8_t* DataManager::s_max_battle_teams = nullptr;
uint8_t* DataManager::s_max_team_size = nullptr;

using godot::Variant, godot::PropertyHint, godot::PropertyUsageFlags, godot::String;

struct SettingProperty {
    Variant::Type type;
    PropertyHint hint;
    String hint_string;
    PropertyUsageFlags usage;
    Variant default_value;

    bool is_basic = true;
    bool is_internal = false;
};

// Project Setting Data
void DataManager::initialize_project_settings() {
    godot::ProjectSettings* project_setting = godot::ProjectSettings::get_singleton();

    const std::map<std::vector<String>, SettingProperty> default_settings = {
        { // Store Sprite Frames to be used for AnimatedSprite Nodes
            {
                "darrylbd99/creature_capture_system/sprite_frames/front",
                "darrylbd99/creature_capture_system/sprite_frames/back",
                "darrylbd99/creature_capture_system/sprite_frames/front_alternate",
                "darrylbd99/creature_capture_system/sprite_frames/back_alternate",
                "darrylbd99/creature_capture_system/main/data_resource",
                "darrylbd99/creature_capture_system/main/default_battlefield",
            }, SettingProperty{
                Variant::STRING,
                PropertyHint::PROPERTY_HINT_FILE,
                "*.tres, *.res",
                PropertyUsageFlags::PROPERTY_USAGE_DEFAULT,
                ""
            }
        },
        { // Default Battlefield
            {
                "darrylbd99/creature_capture_system/main/default_battlefield"
            }, SettingProperty{
                Variant::STRING,
                PropertyHint::PROPERTY_HINT_FILE,
                "*.tscn, *.scn",
                PropertyUsageFlags::PROPERTY_USAGE_DEFAULT,
                ""
            }
        },
        { // Rarity Alternate Color Chance
            {
                "darrylbd99/creature_capture_system/rarity/alternate_color)",
            }, SettingProperty{
                Variant::INT,
                PropertyHint::PROPERTY_HINT_RANGE,
                "0," + String::num_int64(MAX_RANDOM) + ",1",
                PropertyUsageFlags::PROPERTY_USAGE_DEFAULT,
                MAX_RANDOM / 8
            }
        },
    };

    for (const auto&[names, setting] : default_settings) {
        for (const String& name : names) {
            // Set up setting property info
            godot::Dictionary properties = godot::Dictionary();
            properties["name"] = name;
            properties["type"] = setting.type;
            properties["hint"] = setting.hint;
            properties["hint_string"] = setting.hint_string;
            properties["usage"] = setting.usage;
            
            // Set setting to default value if it doesn't exist
            project_setting->set_setting(name, project_setting->get_setting(name, setting.default_value));
            
            // Set setting properties in project settings
            project_setting->set_as_basic(name, setting.is_basic);
            project_setting->set_as_internal(name, setting.is_internal);
            project_setting->set_initial_value(name, setting.default_value);
            project_setting->add_property_info(properties);
        }
    }
}

void DataManager::update_project_settings() {
    // Update 
    godot::ProjectSettings* project_setting = godot::ProjectSettings::get_singleton();

    *s_rarity_alternate_color_chance = project_setting->get_setting("darrylbd99/creature_capture_system/rarity/alternate_color");
}