# include "register.hpp"

#include <Nodes/CreatureSprite3D.hpp>
#include <Resources/BattleTeam.hpp>
#include <Resources/StaticData/Species.hpp>
#include <Resources/StaticData/Type.hpp>
#include <Resources/StaticData/Attack.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <map>

#include <Data Manager.hpp>
#include <Battle Init.hpp>

#include "gdextension_interface.h"

void initialize(ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) return;
    
    // Nodes
    GDREGISTER_CLASS(godot::CreatureSprite3D);

    // Static Data Resources
    GDREGISTER_CLASS(godot::SpeciesResource);
    GDREGISTER_CLASS(godot::TypeResource);
    GDREGISTER_CLASS(godot::AttackResource);
    
    // Battle Resources
    GDREGISTER_CLASS(godot::BattleTeam);

    // Initialize project settings
    DataManager::initialize_project_settings();

    // Check if in game
    if (!godot::Engine::get_singleton()->is_editor_hint()) {
        // Update Data
        DataManager::update_project_settings();
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