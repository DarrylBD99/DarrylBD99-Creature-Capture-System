#include "Battle Init.hpp"

#include "Battle Manager.hpp"
#include "Data Manager.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include <godot_cpp/classes/scene_tree.hpp>

void BattleInit::WildBattle(godot::StringName species, uint8_t level) {
    // Temporary until battle system is implemented
    godot::UtilityFunctions::print("Wild Battle Initialized: " + species + " (Level. " + godot::String::num(level) + ")");
    
    InitializeBattleField();
}

void BattleInit::SingleBattle() {
    // Temporary until battle system is implemented
    godot::UtilityFunctions::print("Single Battle Initialized");

    InitializeBattleField();

}

void BattleInit::InitializeBattleField() {
    // Check if Battle Singleton is initialized
    if (DataManager::s_battle_singleton == nullptr) {
        godot::UtilityFunctions::push_error("Battle Singleton not initialized. Please initialize the battle singleton before starting a battle.");
        return;
    }

    // Add Default Battlefield to Battle Singleton
    BattleManager::s_current_battlefield = (godot::BattleField*)DataManager::s_default_battlefield->duplicate();
    DataManager::s_battle_singleton->add_child(BattleManager::s_current_battlefield);
}