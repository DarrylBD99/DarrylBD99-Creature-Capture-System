#include "CreatureSprite3D.hpp"
#include <godot_cpp/classes/engine.hpp>


#include <Data Manager.hpp>

using godot::CreatureSprite3D;


CreatureSprite3D::CreatureSprite3D() {
    // Constructor code here
    if (Engine::get_singleton()->is_editor_hint())
        return;
    
    // Initialize audio player for creature sounds
    m_audioPlayer = memnew(AudioStreamPlayer);
    add_child(m_audioPlayer);

    // Set sprite frames based on species resource
    //set_sprite_frames(DataManager::s_creature_sprite_frames);
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
    ClassDB::bind_method(D_METHOD("get_species_resource"), &CreatureSprite3D::GetSpeciesResource);
    ClassDB::bind_method(D_METHOD("set_species_resource", "resource"), &CreatureSprite3D::SetSpeciesResource);

    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "species_id"), "set_species_id", "get_species_id");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species_resource", PROPERTY_HINT_RESOURCE_TYPE, "SpeciesResource"), "set_species_resource", "get_species_resource");
}


godot::Ref<godot::SpeciesResource> CreatureSprite3D::GetSpeciesResource() const {
    return m_speciesResource;
}

void CreatureSprite3D::SetSpeciesResource(Ref<SpeciesResource> resource) {
    m_speciesResource = resource;
}

void CreatureSprite3D::SetSprite(bool direction){

    set_sprite_frames(m_speciesResource->GetSpeciesSprites());

    godot::String animation_name;

    if (direction){animation_name = "Front";}
    else {animation_name = "Back";}
    set_autoplay(godot::StringName(animation_name)); // Assuming the animation name corresponds to the animation name
    //godot::UtilityFunctions::print(animation_name," sprite loaded");
} 
