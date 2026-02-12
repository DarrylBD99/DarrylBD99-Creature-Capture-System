#include "Moves.hpp"
#include <Type.hpp>

using godot::MoveResource;

void MoveResource::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_method(D_METHOD("get_move_id"), &MoveResource::GetMoveId);
    ClassDB::bind_method(D_METHOD("set_move_id", "id"), &MoveResource::SetMoveId);
    ClassDB::bind_method(D_METHOD("get_move_sound"), &MoveResource::GetMoveSound);
    ClassDB::bind_method(D_METHOD("set_move_sound", "stream"), &MoveResource::SetMoveSound);
    ClassDB::bind_method(D_METHOD("get_move_animation"), &MoveResource::GetMoveAnimation);
    ClassDB::bind_method(D_METHOD("set_move_animation", "sprite"), &MoveResource::SetMoveAnimation);

    /// Type
    ClassDB::bind_method(D_METHOD("get_move_type"), &MoveResource::GetMoveType);
    ClassDB::bind_method(D_METHOD("set_move_type", "type"), &MoveResource::SetMoveType);

    /// Power
    ClassDB::bind_method(D_METHOD("get_move_power"), &MoveResource::GetMovePower);
    ClassDB::bind_method(D_METHOD("set_move_power", "value"), &MoveResource::SetMovePower);
    /// Accuracy
    ClassDB::bind_method(D_METHOD("get_move_accuracy"), &MoveResource::GetMoveAccuracy);
    ClassDB::bind_method(D_METHOD("set_move_accuracy", "value"), &MoveResource::SetMoveAccuracy);
    /// PP
    ClassDB::bind_method(D_METHOD("get_move_pp"), &MoveResource::GetMovePP);
    ClassDB::bind_method(D_METHOD("set_move_pp", "value"), &MoveResource::SetMovePP);
    /// Category
    ClassDB::bind_method(D_METHOD("get_move_category"), &MoveResource::GetMoveCategory);
    ClassDB::bind_method(D_METHOD("set_move_category", "category"), &MoveResource::SetMoveCategory);
    /// Contact
    ClassDB::bind_method(D_METHOD("get_move_contacts"), &MoveResource::GetMoveContacts);
    ClassDB::bind_method(D_METHOD("set_move_contacts", "value"), &MoveResource::SetMoveContacts);



    // Properties
    ADD_PROPERTY(PropertyInfo(Variant::INT, "move_type", PROPERTY_HINT_ENUM, "NORMAL,FIRE,WATER,ICE,DRAGON,FAIRY,ROCK,GROUND,ELECTRIC,STEEL,POSION,FLYING,DARK,PSYCHIC,GRASS,BUG,FIGHTING,GHOST"), "set_move_type", "get_move_type");
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "move_id"), "set_move_id", "get_move_id");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "move_sound", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_move_sound", "get_move_sound");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "move_animation", PROPERTY_HINT_RESOURCE_TYPE, "SpriteFrames"), "set_move_animation", "get_move_animation");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "move_power", PROPERTY_HINT_RANGE, "0,255,1"), "set_move_power", "get_move_power");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "move_accuracy", PROPERTY_HINT_RANGE, "0,100,1"), "set_move_accuracy", "get_move_accuracy");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "move_pp", PROPERTY_HINT_RANGE, "0,100,1"), "set_move_pp", "get_move_pp");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "move_category", PROPERTY_HINT_ENUM, "PHYSICAL,SPECIAL,STATUS"), "set_move_category", "get_move_category");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "move_contacts"), "set_move_contacts", "get_move_contacts");
}

MoveResource::MoveResource() {
    // Initialize your variables here
}

MoveResource::~MoveResource() {
    // add your cleanup here
}

godot::StringName MoveResource::GetMoveId() const {
    return m_move_id;
}

void MoveResource::SetMoveId(const StringName& id) {
    m_move_id = id;
}

godot::Ref<godot::AudioStream> MoveResource::GetMoveSound() const {
    return m_move_sound;
}

void MoveResource::SetMoveSound(Ref<AudioStream> stream) {
    m_move_sound = stream;
}

godot::Ref<godot::SpriteFrames> MoveResource::GetMoveAnimation() const {
    return m_move_animation;
}

void MoveResource::SetMoveAnimation(const Ref<SpriteFrames>& sprite) {
    m_move_animation = sprite;
}

/// type
godot::TypeResource::m_type_enum MoveResource::GetMoveType() const {
    return m_move_type;
}
void MoveResource::SetMoveType(TypeResource::m_type_enum type) {
    m_move_type = type;
}

/// Power
int MoveResource::GetMovePower() const {
    return m_move_power;
}
void MoveResource::SetMovePower(int value) {
    m_move_power = value;
}

/// Accuracy
int MoveResource::GetMoveAccuracy() const {
    return m_move_accuracy;
}
void MoveResource::SetMoveAccuracy(int value) {
    m_move_accuracy = value;
}

/// PP
int MoveResource::GetMovePP() const {
    return m_move_pp;
}
void MoveResource::SetMovePP(int value) {
    m_move_pp = value;
}


/// category
godot::TypeResource::m_category_enum MoveResource::GetMoveCategory() const {
    return m_move_category;
}
void MoveResource::SetMoveCategory(TypeResource::m_category_enum type) {
    m_move_category = type;
}

/// Contact
bool MoveResource::GetMoveContacts() const {
    return m_move_contacts;
}
void MoveResource::SetMoveContacts(bool value) {
    m_move_contacts = value;
}
