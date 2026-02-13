#include "Type.hpp"

using godot::TypeResource;

void TypeResource::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_method(D_METHOD("get_type_id"), &TypeResource::GetTypeId);
    ClassDB::bind_method(D_METHOD("set_type_id", "id"), &TypeResource::SetTypeId);
    ClassDB::bind_method(D_METHOD("get_type_name"), &TypeResource::GetTypeName);
    ClassDB::bind_method(D_METHOD("set_type_name", "name"), &TypeResource::SetTypeName);
    ClassDB::bind_method(D_METHOD("get_weaknesses"), &TypeResource::GetWeaknesses);
    ClassDB::bind_method(D_METHOD("set_weaknesses", "weaknesses"), &TypeResource::SetWeaknesses);
    ClassDB::bind_method(D_METHOD("get_resistances"), &TypeResource::GetResistances);
    ClassDB::bind_method(D_METHOD("set_resistances", "resistances"), &TypeResource::SetResistances);
    
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "type_id"), "set_type_id", "get_type_id");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "type_name"), "set_type_name", "get_type_name");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "weaknesses", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_weaknesses", "get_weaknesses");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "resistances", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_resistances", "get_resistances");
}

TypeResource::TypeResource() {
    // Initialize your variables here
}

TypeResource::~TypeResource() {
    // add your cleanup here
}

godot::StringName TypeResource::GetTypeId() const {
    return m_type_id;
}

void TypeResource::SetTypeId(const StringName& id) {
    m_type_id = id;
}

godot::String TypeResource::GetTypeName() const {
    return m_type_name;
}

void TypeResource::SetTypeName(const String& name) {
    m_type_name = name;
}

godot::TypedArray<godot::StringName> TypeResource::GetWeaknesses() const {
    return m_weaknesses;
}

void TypeResource::SetWeaknesses(const TypedArray<StringName>& weaknesses) {
    this->m_weaknesses = weaknesses;
}

godot::TypedArray<godot::StringName> TypeResource::GetResistances() const {
    return m_resistances;
}

void TypeResource::SetResistances(const TypedArray<StringName>& resistances) {
    this->m_resistances = resistances;
}