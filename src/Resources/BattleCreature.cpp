#include "BattleCreature.hpp"

using namespace godot;


#include <godot_cpp/classes/ref.hpp>
#include <Resources/StaticData/Species.hpp>


BattleCreature::BattleCreature() {
}

BattleCreature::~BattleCreature() {
}

// No Godot bindings
void BattleCreature::_bind_methods() {


    // Species resource
    ClassDB::bind_method(D_METHOD("set_species_resource", "resource"), &BattleCreature::set_species_resource);
    ClassDB::bind_method(D_METHOD("get_species_resource"), &BattleCreature::get_species_resource);
    ADD_PROPERTY(
        PropertyInfo(Variant::OBJECT, "species_resource", PROPERTY_HINT_RESOURCE_TYPE, "SpeciesResource"),
        "set_species_resource",
        "get_species_resource"
    );

    ClassDB::bind_method(D_METHOD("get_creature_name"), &BattleCreature::get_creature_name);
    ClassDB::bind_method(D_METHOD("set_creature_name", "name"), &BattleCreature::set_creature_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "creature_name"),"set_creature_name", "get_creature_name");

    // Level
    ClassDB::bind_method(D_METHOD("set_level", "level"), &BattleCreature::set_level);
    ClassDB::bind_method(D_METHOD("get_level"), &BattleCreature::get_level);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "level"), "set_level", "get_level");

    // Max HP
    ClassDB::bind_method(D_METHOD("set_max_hp", "max_hp"), &BattleCreature::set_max_hp);
    ClassDB::bind_method(D_METHOD("get_max_hp"), &BattleCreature::get_max_hp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_hp"), "set_max_hp", "get_max_hp");

    // Current HP
    ClassDB::bind_method(D_METHOD("set_current_hp", "current_hp"), &BattleCreature::set_current_hp);
    ClassDB::bind_method(D_METHOD("get_current_hp"), &BattleCreature::get_current_hp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_hp"), "set_current_hp", "get_current_hp");

    // Attack
    ClassDB::bind_method(D_METHOD("set_attack", "attack"), &BattleCreature::set_attack);
    ClassDB::bind_method(D_METHOD("get_attack"), &BattleCreature::get_attack);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "attack"), "set_attack", "get_attack");

    // Defense
    ClassDB::bind_method(D_METHOD("set_defense", "defense"), &BattleCreature::set_defense);
    ClassDB::bind_method(D_METHOD("get_defense"), &BattleCreature::get_defense);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "defense"), "set_defense", "get_defense");

    // Speed
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &BattleCreature::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &BattleCreature::get_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "speed"), "set_speed", "get_speed");
}


void BattleCreature::InitBattleCreature(){
    if (m_species_resource.is_null()){
        godot::UtilityFunctions::push_error("Species resource not set");
        return;}

    m_creature_name = m_species_resource->GetSpeciesId(); //temp

    //replace these with the calculations for the stats
    //temp
    m_max_hp = m_species_resource->GetSpeciesHP();
    m_attack = m_species_resource->GetSpeciesATK();
    m_defense = m_species_resource->GetSpeciesDEF();
    m_speed = m_species_resource->GetSpeciesSPEED();

}

//remember the setters/getters for the names
// Setters
void BattleCreature::set_species_resource(const  Ref<SpeciesResource> resource) {
    m_species_resource = resource;
}


void BattleCreature::set_creature_name(const StringName &name){
    m_creature_name = name;
}


void BattleCreature::set_level(int level) {
    m_level = level;
}

void BattleCreature::set_max_hp(int max_hp) {
    m_max_hp = max_hp;
}

void BattleCreature::set_current_hp(int current_hp) {
    m_current_hp = current_hp;
}

void BattleCreature::set_attack(int attack) {
    m_attack = attack;
}

void BattleCreature::set_defense(int defense) {
    m_defense = defense;
}

void BattleCreature::set_speed(int speed) {
    m_speed = speed;
}


// Getters
 Ref<SpeciesResource> BattleCreature::get_species_resource() const {
    return m_species_resource;
}


StringName BattleCreature::get_creature_name() const {
    return m_creature_name;
}

int BattleCreature::get_level() const {
    return m_level;
}

int BattleCreature::get_max_hp() const {
    return m_max_hp;
}

int BattleCreature::get_current_hp() const {
    return m_current_hp;
}

int BattleCreature::get_attack() const {
    return m_attack;
}

int BattleCreature::get_defense() const {
    return m_defense;
}

int BattleCreature::get_speed() const {
    return m_speed;
}