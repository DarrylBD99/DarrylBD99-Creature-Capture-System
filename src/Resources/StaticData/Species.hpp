#ifndef SPECIES_RESOURCE_H
#define SPECIES_RESOURCE_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

namespace godot {
    class SpeciesResource : public Resource {
        GDCLASS(SpeciesResource, Resource);
        
        private:
            StringName m_species_id;
            Ref<AudioStream> m_species_sound;

        protected:
            static void _bind_methods();
            
        public:
            SpeciesResource();
            virtual ~SpeciesResource();
            StringName GetSpeciesId() const;
            void SetSpeciesId(const StringName& id);
            Ref<AudioStream> GetSpeciesSound() const;
            void SetSpeciesSound(Ref<AudioStream> stream);
    };
};
#endif