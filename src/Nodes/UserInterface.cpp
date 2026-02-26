#include "UserInterface.hpp"

#include <godot_cpp/core/class_db.hpp>

#include <Battle Manager.hpp>
#include <Data Manager.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

VBoxContainer *UserInterface::m_opponents_container = nullptr;
VBoxContainer *UserInterface::m_allys_container = nullptr;
HBoxContainer *UserInterface::m_dialogue_box_container = nullptr;
Ref<PackedScene> UserInterface::m_healthbar_scene;
Ref<PackedScene> UserInterface::m_dialogue_box_scene;

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
    
    ClassDB::bind_method(D_METHOD("set_dialogue_box_container", "node"),
        &UserInterface::SetDialogueBoxContainer);
    ClassDB::bind_method(D_METHOD("get_dialogue_box_container"),
        &UserInterface::GetDialogueBoxContainer);

    ClassDB::bind_method(D_METHOD("set_healthbar_scene", "scene"),&UserInterface::SetHealthbarScene);
    ClassDB::bind_method(D_METHOD("get_healthbar_scene"),&UserInterface::GetHealthbarScene);

    ClassDB::bind_method(D_METHOD("set_dialogue_box_scene", "scene"),&UserInterface::SetDialogueBoxScene);
    ClassDB::bind_method(D_METHOD("get_dialogue_box_scene"),&UserInterface::GetDialogueBoxScene);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "opponents_container",PROPERTY_HINT_NODE_TYPE, "VBoxContainer"),"set_opponents_container","get_opponents_container");

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "allys_container",PROPERTY_HINT_NODE_TYPE, "VBoxContainer"),"set_allys_container","get_allys_container");
    
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dialogue_box_container",PROPERTY_HINT_NODE_TYPE, "HBoxContainer"),"set_dialogue_box_container","get_dialogue_box_container");

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT,"healthbar_scene",PROPERTY_HINT_RESOURCE_TYPE,"PackedScene"),"set_healthbar_scene","get_healthbar_scene");

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT,"dialogue_box_scene",PROPERTY_HINT_RESOURCE_TYPE,"PackedScene"),"set_dialogue_box_scene","get_dialogue_box_scene");
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
void UserInterface::SetDialogueBoxContainer(HBoxContainer* node) {
    m_dialogue_box_container = node;
}
HBoxContainer* UserInterface::GetDialogueBoxContainer() const {
    return m_dialogue_box_container;
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
void UserInterface::SetDialogueBoxScene(Ref<PackedScene> scene) {
    m_dialogue_box_scene = scene;
}
Ref<PackedScene> UserInterface::GetDialogueBoxScene() const {
    return m_dialogue_box_scene;
}

void UserInterface::InitHealthbar(const String &name,int level,int health,bool opponent){

     //m_dialogue_box_scene->StartDialogue("[weoifbio2rnogin2reio;vniernvoin3rivnpeirniowernionewriogniornvoiewrnviewrnv;oiewrnvklewrnvoiewrnivnewrjvbweruov]");


    
    if (m_healthbar_scene.is_null()) {
        UtilityFunctions::push_error("HealthBar scene not set");
        return;}
    
    Node* instance = m_healthbar_scene->instantiate();
    if (!instance) {
        UtilityFunctions::push_error("Failed to instantiate HealthBar scene");
        return;}


    HealthBar* healthbar = Object::cast_to<HealthBar>(instance);
    if (!healthbar) {
        UtilityFunctions::push_error("HealthBar scene's root does not inherit from HealthBar class");
        return;}

    if (!m_allys_container || !m_opponents_container){
        UtilityFunctions::push_error("containers were not set");
        memdelete(healthbar);
        return;}
    

    if (opponent){godot::UserInterface::m_opponents_container->add_child(healthbar);}
    else{godot::UserInterface::m_allys_container->add_child(healthbar);}

    healthbar->SetCreatureName(name);
    healthbar->SetCreatureLevel(level);
    healthbar->SetCreatureHealth(health);
}

void UserInterface::InitDialogueBox(const String &text){
    //if (!m_dialogue_box_scene)

    Node* diabox_instance = m_dialogue_box_scene->instantiate();
    DialogueBox* dialoguebox = Object::cast_to<DialogueBox>(diabox_instance);

    godot::UserInterface::m_dialogue_box_container->add_child(dialoguebox);

    dialoguebox->StartDialogue(text);
}


