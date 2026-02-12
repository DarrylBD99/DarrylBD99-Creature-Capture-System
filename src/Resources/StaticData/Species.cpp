#include "Species.hpp"

using godot::SpeciesResource;

void SpeciesResource::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_method(D_METHOD("get_species_id"), &SpeciesResource::GetSpeciesId);
    ClassDB::bind_method(D_METHOD("set_species_id", "id"), &SpeciesResource::SetSpeciesId);
    ClassDB::bind_method(D_METHOD("get_species_sound"), &SpeciesResource::GetSpeciesSound);
    ClassDB::bind_method(D_METHOD("set_species_sound", "stream"), &SpeciesResource::SetSpeciesSound);
    ClassDB::bind_method(D_METHOD("get_species_sprite"), &SpeciesResource::GetSpeciesSprite);
    ClassDB::bind_method(D_METHOD("set_species_sprite", "sprite"), &SpeciesResource::SetSpeciesSprite);
    //types
    //1
    ClassDB::bind_method(D_METHOD("get_species_type_1"), &SpeciesResource::GetSpeciesType1);
    ClassDB::bind_method(D_METHOD("set_species_type_1", "type"), &SpeciesResource::SetSpeciesType1);
    //2
    ClassDB::bind_method(D_METHOD("get_species_type_2"), &SpeciesResource::GetSpeciesType2);
    ClassDB::bind_method(D_METHOD("set_species_type_2", "type"), &SpeciesResource::SetSpeciesType2);
    /// hp
    ClassDB::bind_method(D_METHOD("get_species_hp"), &SpeciesResource::GetSpeciesHP);
    ClassDB::bind_method(D_METHOD("set_species_hp", "value"), &SpeciesResource::SetSpeciesHP);
    /// atk
    ClassDB::bind_method(D_METHOD("get_species_atk"), &SpeciesResource::GetSpeciesATK);
    ClassDB::bind_method(D_METHOD("set_species_atk", "value"), &SpeciesResource::SetSpeciesATK);
    /// special atk
    ClassDB::bind_method(D_METHOD("get_species_spatk"), &SpeciesResource::GetSpeciesSPATK);
    ClassDB::bind_method(D_METHOD("set_species_spatk", "value"), &SpeciesResource::SetSpeciesSPATK);
    /// speed
    ClassDB::bind_method(D_METHOD("get_species_speed"), &SpeciesResource::GetSpeciesSPEED);
    ClassDB::bind_method(D_METHOD("set_species_speed", "value"), &SpeciesResource::SetSpeciesSPEED);
    /// def
    ClassDB::bind_method(D_METHOD("get_species_def"), &SpeciesResource::GetSpeciesDEF);
    ClassDB::bind_method(D_METHOD("set_species_def", "value"), &SpeciesResource::SetSpeciesDEF);
    /// special def
    ClassDB::bind_method(D_METHOD("get_species_spdef"), &SpeciesResource::GetSpeciesSPDEF);
    ClassDB::bind_method(D_METHOD("set_species_spdef", "value"), &SpeciesResource::SetSpeciesSPDEF);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "species_type_1", PROPERTY_HINT_ENUM, "NORMAL,FIRE,WATER,ICE,DRAGON,FAIRY,ROCK,GROUND,ELECTRIC,STEEL,POSION,FLYING,DARK,PSYCHIC,GRASS,BUG,FIGHTING,GHOST"), "set_species_type_1", "get_species_type_1");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "species_type_2", PROPERTY_HINT_ENUM, "NORMAL,FIRE,WATER,ICE,DRAGON,FAIRY,ROCK,GROUND,ELECTRIC,STEEL,POSION,FLYING,DARK,PSYCHIC,GRASS,BUG,FIGHTING,GHOST,NONE"), "set_species_type_2", "get_species_type_2");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "stats/HP", PROPERTY_HINT_RANGE, "0,255,1"),"set_species_hp","get_species_hp");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "stats/atk", PROPERTY_HINT_RANGE, "0,255,1"),"set_species_atk","get_species_atk");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "stats/spatk", PROPERTY_HINT_RANGE, "0,255,1"),"set_species_spatk","get_species_spatk");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "stats/speed", PROPERTY_HINT_RANGE, "0,255,1"),"set_species_speed","get_species_speed");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "stats/def", PROPERTY_HINT_RANGE, "0,255,1"),"set_species_def","get_species_def");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "stats/spdef", PROPERTY_HINT_RANGE, "0,255,1"),"set_species_spdef","get_species_spdef");
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "species_id"), "set_species_id", "get_species_id");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species_sound", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_species_sound", "get_species_sound");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species_sprite", PROPERTY_HINT_RESOURCE_TYPE, "SpriteFrames"), "set_species_sprite", "get_species_sprite");

}

SpeciesResource::SpeciesResource() {
    // Initialize your variables here
}

SpeciesResource::~SpeciesResource() {
    // add your cleanup here
}

godot::StringName SpeciesResource::GetSpeciesId() const {
    return m_species_id;
}

void SpeciesResource::SetSpeciesId(const StringName& id) {
    m_species_id = id;
}

godot::Ref<godot::AudioStream> SpeciesResource::GetSpeciesSound() const {
    return m_species_sound;
}

void SpeciesResource::SetSpeciesSound(Ref<AudioStream> stream) {
    this->m_species_sound = stream;
}

godot::Ref<godot::SpriteFrames> SpeciesResource::GetSpeciesSprite() const {
    return m_species_sprite;
}

void SpeciesResource::SetSpeciesSprite(const Ref<SpriteFrames>& sprite) {
    m_species_sprite = sprite;
}

//Types
//1
godot::TypeResource::m_type_enum SpeciesResource::GetSpeciesType1() const {
    return m_species_type_1;
}
void SpeciesResource::SetSpeciesType1(TypeResource::m_type_enum type) {
    m_species_type_1 = type;
}
//2
godot::TypeResource::m_type_enum SpeciesResource::GetSpeciesType2() const {
    return m_species_type_2;
}
void SpeciesResource::SetSpeciesType2(TypeResource::m_type_enum type) {
    m_species_type_2 = type;
}

// HP
int SpeciesResource::GetSpeciesHP() const {
    return m_species_HP_iv;
}
void SpeciesResource::SetSpeciesHP(int value) {
    m_species_HP_iv = value;
}

// ATK
int SpeciesResource::GetSpeciesATK() const {
    return m_species_ATK_iv;
}
void SpeciesResource::SetSpeciesATK(int value) {
    m_species_ATK_iv = value;
}

// SPATK
int SpeciesResource::GetSpeciesSPATK() const {
    return m_species_SPATK_iv;
}
void SpeciesResource::SetSpeciesSPATK(int value) {
    m_species_SPATK_iv = value;
}

// SPEED
int SpeciesResource::GetSpeciesSPEED() const {
    return m_species_SPEED_iv;
}
void SpeciesResource::SetSpeciesSPEED(int value) {
    m_species_SPEED_iv = value;
}

// DEF
int SpeciesResource::GetSpeciesDEF() const {
    return m_species_DEF_iv;
}
void SpeciesResource::SetSpeciesDEF(int value) {
    m_species_DEF_iv = value;
}

// SPDEF
int SpeciesResource::GetSpeciesSPDEF() const {
    return m_species_SPDEF_iv;
}
void SpeciesResource::SetSpeciesSPDEF(int value) {
    m_species_SPDEF_iv = value;
}
