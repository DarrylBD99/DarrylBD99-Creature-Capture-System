#include "Attack.hpp"
#include <Type.hpp>

using godot::AttackResource;

void AttackResource::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_method(D_METHOD("get_attack_id"), &AttackResource::GetAttackId);
    ClassDB::bind_method(D_METHOD("set_attack_id", "id"), &AttackResource::SetAttackId);
    ClassDB::bind_method(D_METHOD("get_attack_sound"), &AttackResource::GetAttackSound);
    ClassDB::bind_method(D_METHOD("set_attack_sound", "stream"), &AttackResource::SetAttackSound);
    ClassDB::bind_method(D_METHOD("get_attack_animation"), &AttackResource::GetAttackAnimation);
    ClassDB::bind_method(D_METHOD("set_attack_animation", "sprite"), &AttackResource::SetAttackAnimation);

    /// Type
    ClassDB::bind_method(D_METHOD("get_attack_type"), &AttackResource::GetAttackType);
    ClassDB::bind_method(D_METHOD("set_attack_type", "type"), &AttackResource::SetAttackType);

    /// Power
    ClassDB::bind_method(D_METHOD("get_attack_power"), &AttackResource::GetAttackPower);
    ClassDB::bind_method(D_METHOD("set_attack_power", "value"), &AttackResource::SetAttackPower);
    /// Accuracy
    ClassDB::bind_method(D_METHOD("get_attack_accuracy"), &AttackResource::GetAttackAccuracy);
    ClassDB::bind_method(D_METHOD("set_attack_accuracy", "value"), &AttackResource::SetAttackAccuracy);
    /// PP
    ClassDB::bind_method(D_METHOD("get_attack_pp"), &AttackResource::GetAttackPP);
    ClassDB::bind_method(D_METHOD("set_attack_pp", "value"), &AttackResource::SetAttackPP);
    /// Category
    ClassDB::bind_method(D_METHOD("get_attack_category"), &AttackResource::GetAttackCategory);
    ClassDB::bind_method(D_METHOD("set_attack_category", "category"), &AttackResource::SetAttackCategory);
    /// Contact
    ClassDB::bind_method(D_METHOD("get_attack_contacts"), &AttackResource::GetAttackContacts);
    ClassDB::bind_method(D_METHOD("set_attack_contacts", "value"), &AttackResource::SetAttackContacts);
    // Enums
    BIND_ENUM_CONSTANT(PHYSICAL);
    BIND_ENUM_CONSTANT(SPECIAL);
    BIND_ENUM_CONSTANT(STATUS);

    // Properties
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "attack_type"), "set_attack_type", "get_attack_type");
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "attack_id"), "set_attack_id", "get_attack_id");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attack_sound", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_attack_sound", "get_attack_sound");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attack_animation", PROPERTY_HINT_RESOURCE_TYPE, "SpriteFrames"), "set_attack_animation", "get_attack_animation");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "attack_power", PROPERTY_HINT_RANGE, "0,255,1"), "set_attack_power", "get_attack_power");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "attack_accuracy", PROPERTY_HINT_RANGE, "0,100,1"), "set_attack_accuracy", "get_attack_accuracy");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "attack_pp", PROPERTY_HINT_RANGE, "0,100,1"), "set_attack_pp", "get_attack_pp");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "attack_category", PROPERTY_HINT_ENUM, "PHYSICAL,SPECIAL,STATUS"), "set_attack_category", "get_attack_category");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "attack_contacts"), "set_attack_contacts", "get_attack_contacts");
}

AttackResource::AttackResource() {
    // Initialize your variables here
}

AttackResource::~AttackResource() {
    // add your cleanup here
}

godot::StringName AttackResource::GetAttackId() const {
    return m_attack_id;
}

void AttackResource::SetAttackId(const StringName& id) {
    m_attack_id = id;
}

godot::Ref<godot::AudioStream> AttackResource::GetAttackSound() const {
    return m_attack_sound;
}

void AttackResource::SetAttackSound(Ref<AudioStream> stream) {
    m_attack_sound = stream;
}

godot::Ref<godot::SpriteFrames> AttackResource::GetAttackAnimation() const {
    return m_attack_animation;
}

void AttackResource::SetAttackAnimation(const Ref<SpriteFrames>& sprite) {
    m_attack_animation = sprite;
}

/// type
godot::StringName AttackResource::GetAttackType() const {
    return m_attack_type;
}
void AttackResource::SetAttackType(const StringName& type) {
    m_attack_type = type;
}

/// Power
int AttackResource::GetAttackPower() const {
    return m_attack_power;
}
void AttackResource::SetAttackPower(int value) {
    m_attack_power = value;
}

/// Accuracy
int AttackResource::GetAttackAccuracy() const {
    return m_attack_accuracy;
}
void AttackResource::SetAttackAccuracy(int value) {
    m_attack_accuracy = value;
}

/// PP
int AttackResource::GetAttackPP() const {
    return m_attack_pp;
}
void AttackResource::SetAttackPP(int value) {
    m_attack_pp = value;
}


/// category
godot::AttackResource::m_category_enum AttackResource::GetAttackCategory() const {
    return m_attack_category;
}
void AttackResource::SetAttackCategory(m_category_enum type) {
    m_attack_category = type;
}

/// Contact
bool AttackResource::GetAttackContacts() const {
    return m_attack_contacts;
}
void AttackResource::SetAttackContacts(bool value) {
    m_attack_contacts = value;
}
