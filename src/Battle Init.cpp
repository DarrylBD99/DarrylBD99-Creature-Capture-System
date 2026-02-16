#include "Battle Init.hpp"

#include "Battle Manager.hpp"
#include "Data Manager.hpp"

#include <nodes/CreatureSprite3D.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include <godot_cpp/classes/scene_tree.hpp>

void BattleInit::WildBattle(godot::StringName species, uint8_t level) {
    // Temporary until battle system is implemented
    godot::UtilityFunctions::print("Wild Battle Initialized: " + species + " (Level. " + godot::String::num(level) + ")");

    // Check if Species exist (add later)
    
    // Initialize Battlefield
    if (InitializeBattleField() != godot::Error::OK) {
        godot::UtilityFunctions::push_error("Failed to initialize battle field for wild battle.");
        return;
    }

    InitCreatures(species);

    // Set Wild Battle Species and Level (add in later)
    
}

void BattleInit::SingleBattle() {
    // Temporary until battle system is implemented
    godot::UtilityFunctions::print("Single Battle Initialized");

    if (InitializeBattleField() != godot::Error::OK) {
        godot::UtilityFunctions::push_error("Failed to initialize battle field for single battle.");
        return;
    }

}

godot::Error BattleInit::InitializeBattleField() {
    // Check if Battle Singleton is initialized
    if (DataManager::s_battle_singleton == nullptr) {
        godot::UtilityFunctions::push_error("Battle Singleton not initialized. Please initialize the battle singleton before starting a battle.");
        return godot::Error::ERR_CANT_CREATE;
    }

    // Check if Default Battlefield is initialized
    if (DataManager::s_default_battlefield == nullptr) {
        godot::UtilityFunctions::push_error("Default Battlefield not initialized. Please initialize the default battlefield before starting a battle.");
        return godot::Error::ERR_CANT_CREATE;
    }
    
    // Add Default Battlefield to Battle Singleton
    BattleManager::s_current_battlefield = (godot::BattleField*)DataManager::s_default_battlefield->duplicate();
    DataManager::s_battle_singleton->add_child(BattleManager::s_current_battlefield);
    return godot::Error::OK;
}


void BattleInit::InitCreatures(godot::StringName species){
    //will init all creatures here later i think

    // Create Battle Creature sprite
    godot::CreatureSprite3D* wild_creature_sprite = memnew(godot::CreatureSprite3D());
    wild_creature_sprite->SetSpeciesId(species);
    BattleManager::s_current_battlefield->AddOpponentSprite(wild_creature_sprite);
    
}

