#include "BattleCreature.hpp"

using namespace godot;


#include <godot_cpp/classes/ref.hpp>
#include <Resources/StaticData/Species.hpp>
#include <Resources/StaticData/Attacks.hpp>


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
    ClassDB::bind_method(D_METHOD("set_attack", "attack"), &BattleCreature::set_attack_stat);
    ClassDB::bind_method(D_METHOD("get_attack"), &BattleCreature::get_attack_stat);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "attack"), "set_attack", "get_attack");

    // Defense
    ClassDB::bind_method(D_METHOD("set_defense", "defense"), &BattleCreature::set_defense_stat);
    ClassDB::bind_method(D_METHOD("get_defense"), &BattleCreature::get_defense_stat);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "defense"), "set_defense", "get_defense");

    // Speed
    ClassDB::bind_method(D_METHOD("set_speed", "speed"), &BattleCreature::set_speed_stat);
    ClassDB::bind_method(D_METHOD("get_speed"), &BattleCreature::get_speed_stat);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "speed"), "set_speed", "get_speed");


    ClassDB::bind_method(D_METHOD("set_attacks", "attacks"), &BattleCreature::set_attacks);
    ClassDB::bind_method(D_METHOD("get_attacks"), &BattleCreature::get_attacks);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attacks", PROPERTY_HINT_ARRAY_TYPE, "AttackResource"),"set_attacks","get_attacks");

    ClassDB::bind_method(D_METHOD("add_attack", "attack"), &BattleCreature::add_attack);
    ClassDB::bind_method(D_METHOD("clear_attacks"), &BattleCreature::clear_attacks);
    ClassDB::bind_method(D_METHOD("get_attack_count"), &BattleCreature::get_attack_count);
    ClassDB::bind_method(D_METHOD("get_attack", "index"), &BattleCreature::get_attack);
}


void BattleCreature::InitBattleCreature(){
    if (m_species_resource.is_null()){
        godot::UtilityFunctions::push_error("Species resource not set");
        return;}

    m_creature_name = m_species_resource->GetSpeciesId(); //temp

    //replace these with the calculations for the stats
    //temp
    m_max_hp = m_species_resource->GetSpeciesHP();
    m_attack_stat = m_species_resource->GetSpeciesATK();
    m_defense_stat = m_species_resource->GetSpeciesDEF();
    m_speed_stat = m_species_resource->GetSpeciesSPEED();

}

//remember the setters/getters for the names
// Setters
void BattleCreature::set_species_resource(const Ref<SpeciesResource> resource) {
    m_species_resource = resource;
}


void BattleCreature::set_creature_name(const StringName &name){
    m_creature_name = name;
}


void BattleCreature::set_active(bool active) {
    m_is_active = active;
}
void BattleCreature::set_player(bool player) {
    m_is_player = player;
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

void BattleCreature::set_attack_stat(int attack) {
    m_attack_stat = attack;
}

void BattleCreature::set_defense_stat(int defense) {
    m_defense_stat = defense;
}

void BattleCreature::set_speed_stat(int speed) {
    m_speed_stat = speed;
}


// Getters
 Ref<SpeciesResource> BattleCreature::get_species_resource() const {
    return m_species_resource;
}


StringName BattleCreature::get_creature_name() const {
    return m_creature_name;
}
TypedArray<AttackResource> BattleCreature::get_creature_attacks() const {
    return m_attacks;
}

bool BattleCreature::get_active() const {
    return m_is_active;
}
bool BattleCreature::get_player() const {
    return m_is_player;
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

int BattleCreature::get_attack_stat() const {
    return m_attack_stat;
}

int BattleCreature::get_defense_stat() const {
    return m_defense_stat;
}

int BattleCreature::get_speed_stat() const {
    return m_speed_stat;
}


void BattleCreature::set_attacks(const Array &attacks) {
    m_attacks = attacks;
}

Array BattleCreature::get_attacks() const {
    return m_attacks;
}

void BattleCreature::add_attack(const Ref<AttackResource> &attack) {
    m_attacks.append(attack);
}

void BattleCreature::clear_attacks() {
    m_attacks.clear();
}

int BattleCreature::get_attack_count() const {
    return m_attacks.size();
}

Ref<AttackResource> BattleCreature::get_attack(int index) const {
    if (index < 0 || index >= m_attacks.size()) {
        return Ref<BattleCreature>();
    }
    return m_attacks[index];
}