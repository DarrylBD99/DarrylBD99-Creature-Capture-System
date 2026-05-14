#include "Battle Init.hpp"

#include "Battle Manager.hpp"
#include "Data Manager.hpp"
#include "Nodes/UserInterface.hpp"
#include "Nodes/DialogueBox.hpp"

#include <nodes/CreatureSprite3D.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/node.hpp>

void BattleInit::WildBattle(godot::StringName species, uint8_t level) {
    // Temporary until battle system is implemented
    godot::UtilityFunctions::print("Wild Battle Initialized: " + species + " (Level. " + godot::String::num(level) + ")");

    // Check if Species exist (add later)
    
    // Initialize Battlefield
    if (InitializeBattleField() != godot::Error::OK) {
        godot::UtilityFunctions::push_error("Failed to initialize battle field for wild battle.");
        return;
    }

    InitUserInterface();

    // Set Wild Battle Species and Level (add in later)   

    InitCreatures(species,level,true);
    InitCreatures(species,10,false); ////temp in place of a player's creature

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
    if (DataManager::s_default_battlefield_path == nullptr || DataManager::s_default_battlefield_path->is_empty()) {
        godot::UtilityFunctions::push_error("Default Battlefield not initialized. Please initialize the default battlefield before starting a battle.");
        return godot::Error::ERR_CANT_CREATE;
    }
    
    // Load Default Battlefield Scene
    Ref<godot::PackedScene> default_battlefield = godot::ResourceLoader::get_singleton()->load(*DataManager::s_default_battlefield_path, "PackedScene");

    if (default_battlefield.is_null()) {
        godot::UtilityFunctions::push_error("Failed to load default battlefield scene.");
        return godot::Error::ERR_CANT_CREATE;
    }
    

    // Add Default Battlefield to Battle Singleton
    BattleManager::s_current_battlefield = (godot::BattleField*)default_battlefield->instantiate();
    DataManager::s_battle_singleton->add_child(BattleManager::s_current_battlefield);

    
    return godot::Error::OK;
}


void BattleInit::InitCreatures(godot::StringName species,int level,bool opponent){
    // will init all creatures here later

    // Create Battle Creature sprite
    godot::CreatureSprite3D* creature_sprite = memnew(godot::CreatureSprite3D());
    creature_sprite->SetSpeciesId(species);
    creature_sprite->SetSprite(opponent);

    godot::UserInterface::GetInstance()->InitHealthbar(species,level,33,opponent);

    BattleManager::s_current_battlefield->AddSprites(creature_sprite,opponent);

}

void BattleInit::InitUserInterface(){


    if (DataManager::s_userinterface == nullptr || DataManager::s_userinterface->is_empty()) {
        godot::UtilityFunctions::push_error("UserInterface path not set");
        return;
    }

    Ref<godot::PackedScene> default_userinterface = godot::ResourceLoader::get_singleton()->load(*DataManager::s_userinterface, "PackedScene");

    if (default_userinterface.is_null()) {
        godot::UtilityFunctions::push_error("Failed to load UI scene");
        return;
    }

    BattleManager::s_current_userinterface = (godot::UserInterface*)default_userinterface->instantiate();

    DataManager::s_battle_singleton->add_child(BattleManager::s_current_userinterface);

    godot::UserInterface::GetInstance()->InitDialogueBox();
}

