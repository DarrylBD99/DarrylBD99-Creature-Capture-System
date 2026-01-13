#include "CreatureSprite.hpp"

using godot::CreatureSprite;

void CreatureSprite::PlaySpeciesSound() const {
    if (!m_audioPlayer) {
        UtilityFunctions::push_warning("Audio player not initialized.");
        return;
    }
    
    if (m_speciesResource.is_null()) {
        UtilityFunctions::push_warning("No species resource assigned.");
        return;
    }

    Ref<AudioStream> audioStream = m_speciesResource->GetSpeciesSound();
    
    if (audioStream.is_null()) {
        UtilityFunctions::push_warning("No species sound assigned in species resource.");
        return;
    }

    
    m_audioPlayer->set_stream(audioStream);
    m_audioPlayer->play();
}