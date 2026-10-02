#include "Battle Init.hpp"

#include "Battle Manager.hpp"
#include "Data Manager.hpp"
#include "Nodes/UserInterface.hpp"
#include "Nodes/DialogueBox.hpp"

#include <Resources/BattleCreature.hpp>
#include <Resources/BattleTeam.hpp>
#include <Battle GD.hpp>
#include <Nodes/CreatureSprite3D.hpp>

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/node.hpp>

void BattleInit::start_battle(godot::Ref<godot::BattleTeam> battle_team, int format,int opponent_format) {
    // Temporary until battle system is implemented
    //godot::UtilityFunctions::print("Wild Battle Initialized: " + battle_team.get) + " (Level. " + godot::String::num(level) + ")");

    // Check if Species exist (add later)
    
    godot::UtilityFunctions::print("didn't crash yet1");
    

    BattleFormat battle_format = static_cast<BattleFormat>(format);
    
    godot::UtilityFunctions::print("didn't crash yet2");

    
    // Initialize Battlefield
    if (InitializeBattleField() != godot::Error::OK) {
        godot::UtilityFunctions::push_error("Failed to initialize battlefield");
        return;}
    if (InitUserInterface() != godot::Error::OK) {
        godot::UtilityFunctions::push_error("Failed to initialize UI");
        return;}
    
    
    if (battle_team->get_member_count() != 1){
        godot::UtilityFunctions::push_error("irenhoirelugewigre");
        return; //TEMPORARY
    }


    BattleManager::s_current_battlefield->initPositions();

    godot::UtilityFunctions::print("didn't crash yet3");

    return;
    
    //init player
    godot::Ref<godot::BattleCreature> player_creature = BattleManager::m_player_team->get_member(0);
    InitCreatures(player_creature,battle_format,false);
    
    
    //init opponent
    godot::Ref<godot::BattleCreature> creature = battle_team->get_member(0);
    InitCreatures(creature,battle_format,true);


    BattleManager::m_opponent_team = battle_team;

    
    godot::UserInterface::GetInstance()->InitAttacksButtons();

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


void BattleInit::InitCreatures(const godot::Ref<godot::BattleTeam>& team, BattleFormat format, bool opponent){
    
    int creature_count = 0;

    switch (format)
    {
        case BattleFormat::Singles:
            creature_count = 1;
            break;

        case BattleFormat::Dobules:
            creature_count = 2;
            break;

        case BattleFormat::Triples:
            creature_count = 3;
            break;

        case BattleFormat::TwoVOne:
            creature_count = opponent ? 1 : 2;
            break;

        case BattleFormat::TwoVTwo:
            creature_count = 2;
            break;
    }

    const auto& creatures = team->get_members();

    int creatures_to_initialize = std::min(creature_count, static_cast<int>(creatures.size()));

    for (int i = 0; i < creatures_to_initialize; ++i)
    {
        godot::Ref<godot::BattleCreature> battle_creature = creatures[i];

        battle_creature->InitBattleCreature();

        godot::CreatureSprite3D* creature_sprite = memnew(godot::CreatureSprite3D());

        creature_sprite->SetSpeciesResource(battle_creature->get_species_resource());

        creature_sprite->SetSprite(opponent);

        godot::UserInterface::GetInstance()->InitHealthbar(battle_creature->get_creature_name(),battle_creature->get_level(),33,opponent);

        BattleManager::s_current_battlefield->AddSprites(creature_sprite,format,opponent);
    }
}



godot::Error BattleInit::InitUserInterface(){

    if (DataManager::s_userinterface == nullptr || DataManager::s_userinterface->is_empty()) {
        godot::UtilityFunctions::push_error("UserInterface path not set");
        return godot::Error::ERR_CANT_CREATE;
    }

    Ref<godot::PackedScene> default_userinterface = godot::ResourceLoader::get_singleton()->load(*DataManager::s_userinterface, "PackedScene");

    if (default_userinterface.is_null()) {
        godot::UtilityFunctions::push_error("Failed to load UI scene");
        return godot::Error::ERR_CANT_CREATE;
    }

    BattleManager::s_current_userinterface = (godot::UserInterface*)default_userinterface->instantiate();

    DataManager::s_battle_singleton->add_child(BattleManager::s_current_userinterface);


    return godot::Error::OK;
}

