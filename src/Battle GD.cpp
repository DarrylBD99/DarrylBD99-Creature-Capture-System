#include "Battle GD.hpp"
#include "Battle Init.hpp"
#include "Data Manager.hpp"
#include "Battle Manager.hpp"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>

using godot::CCS_Battle;

void CCS_Battle::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_static_method("CCS_Battle", godot::D_METHOD("initialize_battle_singleton"), &initialize_battle_singleton);
    ClassDB::bind_static_method("CCS_Battle", godot::D_METHOD("start_battle", "BattleTeam"), &BattleInit::start_battle);
    ClassDB::bind_static_method("CCS_Battle", godot::D_METHOD("update_project_settings"), &DataManager::update_project_settings);
    ClassDB::bind_static_method("CCS_Battle", godot::D_METHOD("set_player_team","BattleTeam"), &BattleManager::set_player_team);
}

void CCS_Battle::initialize_battle_singleton() {
/**
 * Initializes the Battle Singleton by creating a new Node and adding it to the scene tree.
 * This node is used to store the current battle state and is automatically added to the scene tree.
 * This function should be called before starting a battle.
 */
    DataManager::s_battle_singleton = memnew(godot::Node);
    DataManager::s_battle_singleton->set_name("CCS_Singleton");
    
    godot::SceneTree *tree = godot::Object::cast_to<godot::SceneTree>(godot::Engine::get_singleton()->get_main_loop());
    tree->get_root()->call_deferred("add_child", DataManager::s_battle_singleton);
}

void CCS_Battle::main_battle_loop(){
}
