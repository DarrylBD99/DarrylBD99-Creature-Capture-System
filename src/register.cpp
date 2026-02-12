# include "register.hpp"

#include <Nodes/CreatureSprite3D.hpp>
#include <Resources/BattleTeam.hpp>
#include <Resources/StaticData/Species.hpp>
#include <Resources/StaticData/Type.hpp>
#include <Resources/StaticData/Moves.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <map>

#include <BattleManager.hpp>

#include "gdextension_interface.h"


using godot::Variant, godot::PropertyHint, godot::PropertyUsageFlags;

struct SettingProperty {
    Variant::Type type;
    PropertyHint hint;
    String hint_string;
    PropertyUsageFlags usage;
    Variant default_value;

    bool is_basic = true;
    bool is_internal = false;
};

void initialize(ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) return;
    
    // Nodes
    GDREGISTER_CLASS(godot::CreatureSprite3D);

    // Static Data Resources
    GDREGISTER_CLASS(godot::SpeciesResource);
    GDREGISTER_CLASS(godot::TypeResource);
    GDREGISTER_CLASS(godot::MoveResource);

    
    // Battle Resources
    GDREGISTER_CLASS(godot::BattleTeam);

    // Add Project Settings
    godot::ProjectSettings* project_setting = godot::ProjectSettings::get_singleton();

    const std::map<vector<String>, SettingProperty> default_settings = {
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
                PropertyUsageFlags::PROPERTY_USAGE_DEFAULT,
                ""
            }
        },
        { // Rarity Alternate Color Chance
            {
                "darrylbd99/creature_capture_system/rarity/alternate_color_(maximum: " + String::num_int64(BattleManager::MAX_RANDOM) + ")",
            }, SettingProperty{
                Variant::INT,
                PropertyHint::PROPERTY_HINT_RANGE,
                "0," + String::num_int64(BattleManager::MAX_RANDOM) + ",1",
                PropertyUsageFlags::PROPERTY_USAGE_DEFAULT,
                BattleManager::MAX_RANDOM / 4
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

void uninitialize(ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) return;
}

extern "C" {
    GDExtensionBool GDE_EXPORT GDExtension_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        const GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization * r_initialization
    ) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize);
        init_obj.register_terminator(uninitialize);
        init_obj.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}