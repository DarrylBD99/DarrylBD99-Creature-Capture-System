#ifndef CREATURESPRITE_H
#define CREATURESPRITE_H

#include <Resources/StaticData/Species.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>

namespace godot {
    class CreatureSprite{
        protected:
            StringName m_speciesId;
            Ref<SpeciesResource> m_speciesResource = nullptr;
            AudioStreamPlayer* m_audioPlayer = nullptr;
        public:
            void PlaySpeciesSound() const;
    };
};
#endif