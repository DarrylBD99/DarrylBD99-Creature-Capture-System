#include "Species.hpp"

using godot::SpeciesResource;

void SpeciesResource::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_method(D_METHOD("get_species_id"), &SpeciesResource::GetSpeciesId);
    ClassDB::bind_method(D_METHOD("set_species_id", "id"), &SpeciesResource::SetSpeciesId);
    ClassDB::bind_method(D_METHOD("get_species_sound"), &SpeciesResource::GetSpeciesSound);
    ClassDB::bind_method(D_METHOD("set_species_sound", "stream"), &SpeciesResource::SetSpeciesSound);
    

    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "species_id"), "set_species_id", "get_species_id");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species_sound", PROPERTY_HINT_RESOURCE_TYPE, "AudioStream"), "set_species_sound", "get_species_sound");
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