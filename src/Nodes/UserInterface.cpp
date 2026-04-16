#include "UserInterface.hpp"

#include <godot_cpp/core/class_db.hpp>

#include <Battle Manager.hpp>
#include <Data Manager.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <Nodes/AttackButton.hpp>

using namespace godot;

VBoxContainer *UserInterface::m_opponents_container = nullptr;
VBoxContainer *UserInterface::m_allys_container = nullptr;
HBoxContainer *UserInterface::m_dialogue_box_container = nullptr;
Control* UserInterface::m_attacks_buttons_parent = nullptr;
Ref<PackedScene> UserInterface::s_healthbar_scene;
Ref<PackedScene> UserInterface::s_dialogue_box_scene;

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

    ClassDB::bind_method(D_METHOD("set_attacks_buttons_parent", "node"),
        &UserInterface::SetAttacksButtonsParent);
    ClassDB::bind_method(D_METHOD("get_attacks_buttons_parent"),
        &UserInterface::GetAttacksButtonsParent);
    
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

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attacks_buttons_parent",PROPERTY_HINT_NODE_TYPE, "Control"),"set_attacks_buttons_parent","get_attacks_buttons_parent");

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
void UserInterface::SetAttacksButtonsParent(Control *node) {
    m_attacks_buttons_parent = node;
}
Control *UserInterface::GetAttacksButtonsParent() const {
    return m_attacks_buttons_parent;
}
UserInterface* UserInterface::GetInstance() {
    return s_instance;
}
void UserInterface::SetHealthbarScene(Ref<PackedScene> healthbar) {
    s_healthbar_scene = healthbar;
}
Ref<PackedScene> UserInterface::GetHealthbarScene() const {
    return s_healthbar_scene;
}
void UserInterface::SetDialogueBoxScene(Ref<PackedScene> scene) {
    s_dialogue_box_scene = scene;
}
Ref<PackedScene> UserInterface::GetDialogueBoxScene() const {
    return s_dialogue_box_scene;
}

void UserInterface::InitHealthbar(const String &name,int level,int health,bool opponent){
    
    if (s_healthbar_scene.is_null()) {
        UtilityFunctions::push_error("HealthBar scene not set");
        return;}
    
    Node* instance = s_healthbar_scene->instantiate();
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

void UserInterface::InitDialogueBox(){
    if (!m_dialogue_box_container){return;}
    if (!s_dialogue_box_scene.is_valid()){return;}

    Node* diabox_instance = s_dialogue_box_scene->instantiate();
    DialogueBox* dialoguebox = Object::cast_to<DialogueBox>(diabox_instance);

    godot::UserInterface::m_dialogue_box_container->add_child(dialoguebox);

    //temp test
    dialoguebox->AddTextToQueue("Hello? Hello, hello?");
    dialoguebox->AddTextToQueue("Uh, I wanted to record a message for you to help you get settled in on your first night.");
    dialoguebox->AddTextToQueue("Um, I actually worked in that office before you. I'm finishing up my last week now, as a matter of fact.");
    dialoguebox->AddTextToQueue("So, I know it can be a bit overwhelming, but I'm here to tell you there's nothing to worry about.");
    dialoguebox->AddTextToQueue("The animatronic characters here do get a bit quirky at night, but do I blame them? No.");
    dialoguebox->AddTextToQueue("If I were forced to sing those same stupid songs for twenty years and I never got a bath...");
    dialoguebox->AddTextToQueue("I'd probably get a little angry at night too.");
    dialoguebox->AddTextToQueue("Heh, hey, what are you, uh, still here? I should probably tell you about your first night.");
    dialoguebox->AddTextToQueue("Uh, the main thing to remember is to keep an eye on the cameras.");
    dialoguebox->AddTextToQueue("Uh, the animatronics do tend to wander a bit...");
    dialoguebox->AddTextToQueue("Uh, I should also mention that, uh, the parts and service rooms are off-limits, okay?");
    dialoguebox->AddTextToQueue("Well, good luck, and I'll talk to you tomorrow.");
}

Array UserInterface::GetAttacksButtons(){
    Array buttons;

    if (!m_attacks_buttons_parent) {
		UtilityFunctions::push_error("attacks parent not found or not set");
	}

	int count = m_attacks_buttons_parent->get_child_count();

	for (int i = 0; i < count; i++) {
		Node *child = m_attacks_buttons_parent->get_child(i);

		if (Object::cast_to<AttackButton>(child)) {
			buttons.append(child);
		}
	}

    godot::UtilityFunctions::print(buttons);
    return buttons;
}

void UserInterface::InitAttacksButtons(){
    Array buttons = GetAttacksButtons();

    if (buttons.is_empty()){
        UtilityFunctions::push_error("attack buttons not found");
        return;
    }

    auto active_creatures = BattleManager::GetActiveCreatures();
    godot::Ref<godot::BattleCreature> the_creature_in_question;

    UtilityFunctions::print(active_creatures.size());

    for (int i = 0; i < active_creatures.size(); i++){
        godot::Ref<godot::BattleCreature> creature = active_creatures[i];
        UtilityFunctions::print(creature);
        if (creature->get_player()){
            the_creature_in_question = creature;
        }
    }
    if (the_creature_in_question.is_null()){
        UtilityFunctions::push_error("the_creature_in_question is null");
        return;
     }

    auto attacks = the_creature_in_question->get_creature_attacks();

    for (int i = 0; i < attacks.size(); i++){
        auto bazinga = Object::cast_to<AttackButton>(buttons[i]);
        bazinga->SetAttackButtonMove(attacks[i]);

    }
}

 