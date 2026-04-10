#ifndef SPECIES_RESOURCE_H
#define SPECIES_RESOURCE_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <Type.hpp>


namespace godot {
    class SpeciesResource : public Resource {
        GDCLASS(SpeciesResource, Resource);
        
        private:
            StringName m_species_id;
            Ref<AudioStream> m_species_sound;
            Ref<SpriteFrames> m_species_sprites;


            StringName m_species_type_1;
            StringName m_species_type_2;


            int m_species_base_HP = 100;
            int m_species_base_ATK = 1;
            int m_species_base_SPATK = 1;
            int m_species_base_SPEED = 1;
            int m_species_base_DEF = 1;
            int m_species_base_SPDEF = 1;



        protected:
            static void _bind_methods();
            
        public:
            SpeciesResource();
            virtual ~SpeciesResource();
            StringName GetSpeciesId() const;
            void SetSpeciesId(const StringName& id);
            Ref<AudioStream> GetSpeciesSound() const;
            void SetSpeciesSound(Ref<AudioStream> stream);
            Ref<SpriteFrames> GetSpeciesSprites() const;
            void SetSpeciesSprites(const Ref<SpriteFrames> sprites);

            StringName GetSpeciesType1() const;
            void SetSpeciesType1(const StringName& type);
            StringName GetSpeciesType2() const;
            void SetSpeciesType2(const StringName& type);

            /// HP
            int GetSpeciesHP() const;
            void SetSpeciesHP(int value);
            /// ATK
            int GetSpeciesATK() const;
            void SetSpeciesATK(int value);
            /// SPATK
            int GetSpeciesSPATK() const;
            void SetSpeciesSPATK(int value);
            /// SPEED
            int GetSpeciesSPEED() const;
            void SetSpeciesSPEED(int value);
            /// DEF
            int GetSpeciesDEF() const;
            void SetSpeciesDEF(int value);
            /// SPDEF
            int GetSpeciesSPDEF() const;
            void SetSpeciesSPDEF(int value);


    };
};
#endif
