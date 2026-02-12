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
            Ref<SpriteFrames> m_species_sprite;


            TypeResource::m_type_enum m_species_type_1;
            TypeResource::m_type_enum m_species_type_2;


            int m_species_HP_iv = 0;
            int m_species_ATK_iv = 0;
            int m_species_SPATK_iv = 0;
            int m_species_SPEED_iv = 0;
            int m_species_DEF_iv = 0;
            int m_species_SPDEF_iv = 0;



        protected:
            static void _bind_methods();
            
        public:
            SpeciesResource();
            virtual ~SpeciesResource();
            StringName GetSpeciesId() const;
            void SetSpeciesId(const StringName& id);
            Ref<AudioStream> GetSpeciesSound() const;
            void SetSpeciesSound(Ref<AudioStream> stream);
            Ref<SpriteFrames> GetSpeciesSprite() const;
            void SetSpeciesSprite(const Ref<SpriteFrames>& sprite);

            TypeResource::m_type_enum GetSpeciesType1() const;
            void SetSpeciesType1(TypeResource::m_type_enum type);
            TypeResource::m_type_enum GetSpeciesType2() const;
            void SetSpeciesType2(TypeResource::m_type_enum type);

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
