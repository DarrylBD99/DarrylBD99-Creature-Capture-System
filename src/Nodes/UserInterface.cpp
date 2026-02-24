#include "UserInterface.hpp"

#include <godot_cpp/core/class_db.hpp>

#include <Battle Manager.hpp>
#include <Data Manager.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

VBoxContainer *UserInterface::m_opponents_container = nullptr;
VBoxContainer *UserInterface::m_allys_container = nullptr;
UserInterface* UserInterface::s_instance = nullptr;

UserInterface::UserInterface() {
}

UserInterface::~UserInterface() {
}

void UserInterface::_ready() {
    s_instance = this;
}

void UserInterface::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_opponents_container", "node"),
        &UserInterface::SetOpponentsContainer);
    ClassDB::bind_method(D_METHOD("get_opponents_container"),
        &UserInterface::GetOpponentsContainer);

    ClassDB::bind_method(D_METHOD("set_allys_container", "node"),
        &UserInterface::SetAllysContainer);
    ClassDB::bind_method(D_METHOD("get_allys_container"),
        &UserInterface::GetAllysContainer);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "opponents_container",
        PROPERTY_HINT_NODE_TYPE, "VBoxContainer"),
        "set_opponents_container",
        "get_opponents_container");

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "allys_container",
        PROPERTY_HINT_NODE_TYPE, "VBoxContainer"),
        "set_allys_container",
        "get_allys_container");
}

void UserInterface::_init() {
}

void UserInterface::SetOpponentsContainer(VBoxContainer *node) {
    m_opponents_container = node;
}
VBoxContainer *UserInterface::GetOpponentsContainer() const {
    return m_opponents_container;
}
void UserInterface::SetAllysContainer(VBoxContainer *node) {
    m_allys_container = node;
}
VBoxContainer *UserInterface::GetAllysContainer() const {
    return m_allys_container;
}

UserInterface* UserInterface::GetInstance() {
    return s_instance;
}

void UserInterface::InitHealthbar(const String &name,int level,int health,bool opponent){

    //if (default_healthbar_UI.is_null()) {
    //godot::UtilityFunctions::push_error("Failed to load default healthbar UI scene.");
    //return godot::Error::ERR_CANT_CREATE;
    //}

    Ref<godot::PackedScene> default_healthbar_UI = godot::ResourceLoader::get_singleton()->load(*DataManager::s_default_healthbar_UI, "PackedScene");

    BattleManager::s_current_healthbarUI = (godot::HealthBar*)default_healthbar_UI->instantiate();
    if (opponent){godot::UserInterface::m_opponents_container->add_child(BattleManager::s_current_healthbarUI);}
    else{godot::UserInterface::m_allys_container->add_child(BattleManager::s_current_healthbarUI);}

    BattleManager::s_current_healthbarUI->SetCreatureName(name);
    BattleManager::s_current_healthbarUI->SetCreatureLevel(level);
    BattleManager::s_current_healthbarUI->SetCreatureHealth(health);
}


