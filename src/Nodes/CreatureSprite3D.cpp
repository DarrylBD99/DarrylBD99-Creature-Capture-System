#include "CreatureSprite3D.hpp"
#include <godot_cpp/classes/engine.hpp>

using godot::CreatureSprite3D;

CreatureSprite3D::CreatureSprite3D() {
    // Constructor code here

    if (Engine::get_singleton()->is_editor_hint())
        return;
    m_audioPlayer = memnew(AudioStreamPlayer);
    add_child(m_audioPlayer);
}

CreatureSprite3D::~CreatureSprite3D() {
    // add your cleanup here
    if (m_audioPlayer && m_audioPlayer->is_inside_tree()) {
        m_audioPlayer->queue_free();
        m_audioPlayer = nullptr;
    }
}

void CreatureSprite3D::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_method(D_METHOD("get_species_id"), &CreatureSprite3D::GetSpeciesId);
    ClassDB::bind_method(D_METHOD("set_species_id", "id"), &CreatureSprite3D::SetSpeciesId);
    ClassDB::bind_method(D_METHOD("get_species_resource"), &CreatureSprite3D::GetSpeciesResource);
    ClassDB::bind_method(D_METHOD("set_species_resource", "resource"), &CreatureSprite3D::SetSpeciesResource);

    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "species_id"), "set_species_id", "get_species_id");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species_resource", PROPERTY_HINT_RESOURCE_TYPE, "SpeciesResource"), "set_species_resource", "get_species_resource");
}

godot::StringName CreatureSprite3D::GetSpeciesId() const {
    return m_speciesId;
}

void CreatureSprite3D::SetSpeciesId(const StringName& id) {
    m_speciesId = id;
}

godot::Ref<godot::SpeciesResource> CreatureSprite3D::GetSpeciesResource() const {
    return m_speciesResource;
}

void CreatureSprite3D::SetSpeciesResource(Ref<SpeciesResource> resource) {
    m_speciesResource = resource;
}
