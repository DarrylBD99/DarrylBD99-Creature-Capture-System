#include "Battle GD.hpp"
#include "Battle Init.hpp"
#include "Data Manager.hpp"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>

using godot::CCS_Battle;

void CCS_Battle::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_static_method("CCS_Battle", godot::D_METHOD("initialize_battle_singleton"), &initialize_battle_singleton);
    ClassDB::bind_static_method("CCS_Battle", godot::D_METHOD("single_battle"), &BattleInit::SingleBattle);
}

void CCS_Battle::initialize_battle_singleton() {
    DataManager::s_battle_singleton = memnew(godot::Node);
    DataManager::s_battle_singleton->set_name("CCS_Singleton");
    
    godot::SceneTree *tree = godot::Object::cast_to<godot::SceneTree>(godot::Engine::get_singleton()->get_main_loop());
    tree->get_root()->call_deferred("add_child", DataManager::s_battle_singleton);
}