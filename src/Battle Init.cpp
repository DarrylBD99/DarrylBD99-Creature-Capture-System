#include "Battle Init.hpp"

#include "Battle Manager.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/object.hpp>

void BattleInit::SingleBattle() {
    // Temporary until battle system is implemented
    godot::UtilityFunctions::print("Single Battle Initialized");

    // Add Default Battlefield to the scene tree
    // if (BattleManager::s_default_battlefield) {
    //     godot::SceneTree *tree = godot::Object::cast_to<godot::SceneTree>(godot::Engine::get_singleton()->get_main_loop());
    //     if (tree) {
    //         godot::Node* root = tree->get_root();
    //         if (root) {
    //             root->add_child(BattleManager::s_default_battlefield);
    //         } else {
    //             godot::print_error("Failed to get root node");
    //         }
    //     } else {
    //         godot::print_error("Failed to get SceneTree");
    //     }
    // } else {
    //     godot::print_error("Default battlefield is not set");
    // }
}