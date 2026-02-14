#include "Battle Init.hpp"

#include "Battle Manager.hpp"
#include "Data Manager.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/object.hpp>

void BattleInit::SingleBattle() {
    // Temporary until battle system is implemented
    godot::UtilityFunctions::print("Single Battle Initialized");

    // Check if Battle Singleton is initialized
    // if (!DataManager::s_battle_singleton) {
    //     godot::UtilityFunctions::print("Battle Singleton not initialized. Initializing now...");
    //     DataManager::initialize_battle_singleton();
    // } else {
    //     godot::UtilityFunctions::print("Battle Singleton already initialized.");
    // }

    // Add Default Battlefield to Battle Singleton
    // DataManager::s_battle_singleton->add_child(DataManager::s_default_battlefield);
}