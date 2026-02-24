#include "UserInterface.hpp"

#include <godot_cpp/core/class_db.hpp>

#include <Battle Manager.hpp>
#include <Data Manager.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

VBoxContainer *UserInterface::m_opponents_container = nullptr;
VBoxContainer *UserInterface::m_allys_container = nullptr;
Ref<PackedScene> UserInterface::m_healthbar_scene;
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

    ClassDB::bind_method(D_METHOD("set_healthbar_scene", "scene"),
                     &UserInterface::SetHealthbarScene);

    ClassDB::bind_method(D_METHOD("get_healthbar_scene"),
                     &UserInterface::GetHealthbarScene);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "opponents_container",
        PROPERTY_HINT_NODE_TYPE, "VBoxContainer"),
        "set_opponents_container",
        "get_opponents_container");

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "allys_container",
        PROPERTY_HINT_NODE_TYPE, "VBoxContainer"),
        "set_allys_container",
        "get_allys_container");

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT,
                          "healthbar_scene",
                          PROPERTY_HINT_RESOURCE_TYPE,
                          "PackedScene"),
             "set_healthbar_scene",
             "get_healthbar_scene");
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
void UserInterface::SetHealthbarScene(Ref<PackedScene> healthbar) {
    m_healthbar_scene = healthbar;
}

Ref<PackedScene> UserInterface::GetHealthbarScene() const {
    return m_healthbar_scene;
}

void UserInterface::InitHealthbar(const String &name,int level,int health,bool opponent){

    //if (default_healthbar_UI.is_null()) {
    //godot::UtilityFunctions::push_error("Failed to load default healthbar UI scene.");
    //return godot::Error::ERR_CANT_CREATE;
    //}


    HealthBar* healthbar = Object::cast_to<HealthBar>(m_healthbar_scene->instantiate());

    if (opponent){godot::UserInterface::m_opponents_container->add_child(healthbar);}
    else{godot::UserInterface::m_allys_container->add_child(healthbar);}

    healthbar->SetCreatureName(name);
    healthbar->SetCreatureLevel(level);
    healthbar->SetCreatureHealth(health);
}


