#include "Data Manager.hpp"
#include <Battle Manager.hpp>

#include <godot_cpp/variant/string.hpp>
#include <vector>
#include <map>

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

// Static member definitions
uint16_t* DataManager::s_alternate_color_rarity = nullptr;
uint8_t* DataManager::s_max_battle_teams = nullptr;
uint8_t* DataManager::s_max_team_size = nullptr;

godot::ProjectSettings* DataManager::project_setting = nullptr;
godot::String* DataManager::s_default_battlefield_path = nullptr;
godot::String* DataManager::s_default_healthbar_UI = nullptr;
godot::Node* DataManager::s_battle_singleton = nullptr;
godot::Ref<godot::SpriteFrames> DataManager::s_creature_sprite_frames = nullptr;

using godot::Variant, godot::PropertyHint, godot::PropertyUsageFlags, godot::String;

struct SettingProperty {
    Variant::Type type;
    PropertyHint hint;
    String hint_string;
    Variant default_value;
    

    bool is_basic = true;
    bool is_internal = false;
};

// Project Setting Data
void DataManager::initialize_project_settings() {
    project_setting = godot::ProjectSettings::get_singleton();

    const std::map<std::vector<String>, SettingProperty> default_settings = {
        { // Store Sprite Frames to be used for AnimatedSprite Nodes
            {
                "darrylbd99/creature_capture_system/sprite_frames/front",
                "darrylbd99/creature_capture_system/sprite_frames/back",
                "darrylbd99/creature_capture_system/sprite_frames/front_alternate",
                "darrylbd99/creature_capture_system/sprite_frames/back_alternate",
                "darrylbd99/creature_capture_system/main/data_resource",
            }, SettingProperty{
                Variant::STRING,
                PropertyHint::PROPERTY_HINT_FILE,
                "*.tres, *.res",
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
                "res://Template/BattleField.scn"
            }
        },
                { // Default healthbar ui
            {
                "darrylbd99/creature_capture_system/main/default_healthbar_UI"
            }, SettingProperty{
                Variant::STRING,
                PropertyHint::PROPERTY_HINT_FILE,
                "*.tscn, *.scn",
                "res://Template/UI/healthbar ui.tscn"
            }
        },
        { // Rarity Alternate Color Chance
            {
                "darrylbd99/creature_capture_system/rarity/alternate_color)",
            }, SettingProperty{
                Variant::INT,
                PropertyHint::PROPERTY_HINT_RANGE,
                "0," + String::num_int64(MAX_RANDOM) + ",1",
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
    // Update static variables with current project setting values
    godot::Variant s_alternate_color_rarity_variant = project_setting->get_setting("darrylbd99/creature_capture_system/rarity/alternate_color");
    uint16_t s_alternate_color_rarity_value = static_cast<uint16_t>(s_alternate_color_rarity_variant);
    s_alternate_color_rarity = new uint16_t(s_alternate_color_rarity_value);

    // Load SpriteFrames resources and store them in static variables

    if (project_setting->get_setting("darrylbd99/creature_capture_system/sprite_frames/front")) {
        s_creature_sprite_frames = godot::ResourceLoader::get_singleton()->load(project_setting->get_setting("darrylbd99/creature_capture_system/sprite_frames/front"), "SpriteFrames");
    }

    if (project_setting->get_setting("darrylbd99/creature_capture_system/sprite_frames/back")) {
        s_creature_sprite_frames = godot::ResourceLoader::get_singleton()->load(project_setting->get_setting("darrylbd99/creature_capture_system/sprite_frames/back"), "SpriteFrames");
    }
    
    // Load default battlefield as PackedScene and store it in BattleManager
    godot::String battlefield_path = project_setting->get_setting("darrylbd99/creature_capture_system/main/default_battlefield");
    Ref<godot::PackedScene> default_battlefield = godot::ResourceLoader::get_singleton()->load(battlefield_path, "PackedScene");

    //UI
    godot::String UI_path = project_setting->get_setting("darrylbd99/creature_capture_system/main/default_UI");
    Ref<godot::PackedScene> default_UI = godot::ResourceLoader::get_singleton()->load(UI_path, "PackedScene");

    if (default_battlefield.is_null())
        default_battlefield = godot::ResourceLoader::get_singleton()->load("res://Template/BattleField.scn", "PackedScene");

    if (default_battlefield.is_null()) {
        godot::print_error("Failed to load default battlefield");
        return;
    }
    

    if (default_UI.is_null()){
        default_UI = godot::ResourceLoader::get_singleton()->load("res://Template/UI/healthbar ui.tscn", "PackedScene");
    }
    if (default_UI.is_null()) {
        godot::print_error("Failed to load default ui");
        return;
    }

    s_default_battlefield_path = new godot::String(battlefield_path);
    s_default_healthbar_UI = new godot::String(UI_path);
}

void DataManager::free_data() {
    if (s_creature_sprite_frames.is_valid()) {
        memdelete(s_creature_sprite_frames.ptr());
    }
}