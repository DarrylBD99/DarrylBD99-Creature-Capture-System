#include "Data Manager.hpp"
#include <Battle Manager.hpp>

#include <godot_cpp/variant/string.hpp>
#include <vector>
#include <map>

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

// Static member definitions
uint16_t* DataManager::s_alternate_color_rarity = nullptr;
uint8_t* DataManager::s_max_battle_teams = nullptr;
uint8_t* DataManager::s_max_team_size = nullptr;

godot::ProjectSettings* DataManager::project_setting = nullptr;
godot::BattleField* DataManager::s_default_battlefield = nullptr;
godot::Node* DataManager::s_battle_singleton = nullptr;

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

    // Load default battlefield as PackedScene and store it in BattleManager
    godot::String battlefield_path = project_setting->get_setting("darrylbd99/creature_capture_system/main/default_battlefield");
    Ref<godot::PackedScene> default_battlefield = godot::ResourceLoader::get_singleton()->load(battlefield_path, "PackedScene");

    if (default_battlefield.is_null())
        default_battlefield = godot::ResourceLoader::get_singleton()->load("res://Template/BattleField.scn", "PackedScene");
    

    if (default_battlefield.is_null()) {
        godot::print_error("Failed to load default battlefield");
        return;
    }

    // Check if the instanced loaded resource is BattleField, if not print error and return
    godot::Object* instanced_battlefield = default_battlefield->instantiate();
    godot::BattleField* battlefield = godot::Object::cast_to<godot::BattleField>(instanced_battlefield);
    if (battlefield == nullptr) {
        if (instanced_battlefield) {
            godot::Node* node = godot::Object::cast_to<godot::Node>(instanced_battlefield);
            if (node) node->queue_free();
            else memdelete(instanced_battlefield);
        
        }
        godot::print_error("Default battlefield is not a valid BattleField scene");
        return;
    }
    s_default_battlefield = battlefield;
}

void DataManager::initialize_battle_singleton() {
    s_battle_singleton = memnew(godot::Node);
    godot::SceneTree *tree = godot::Object::cast_to<godot::SceneTree>(godot::Engine::get_singleton()->get_main_loop());
    tree->get_root()->add_child(s_battle_singleton);
}

void DataManager::free_data() {
    godot::print_line("Freeing DataManager resources...");
    
    // Free any allocated resources or perform any necessary cleanup here
    if (s_default_battlefield)
        memdelete(s_default_battlefield);
        
    if (s_battle_singleton)
        memdelete(s_battle_singleton);
}