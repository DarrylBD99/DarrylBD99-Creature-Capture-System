#ifndef ATTACK_RESOURCE_H
#define ATTACK_RESOURCE_H

#include <godot_cpp/classes/resource.hpp>
#include <Type.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>


namespace godot {
    class AttackResource : public Resource {
        GDCLASS(AttackResource, Resource);
        
        private:
            StringName m_attack_id;
            Ref<AudioStream> m_attack_sound;
            Ref<SpriteFrames> m_attack_animation;

            int m_attack_power;
            int m_attack_accuracy;
            int m_attack_pp;
            bool m_attack_contacts;

            StringName m_attack_type;


            /// TODO
            ///insert chance of secondary effect (eg. burn,flinch)
            ///insert other charastaristics (eg. sound move, ball move)
            ///insert who it targets (1 or 2 opponent or ally ect.)
            ///insert move description


        protected:
            static void _bind_methods();
            
        public:
            enum m_category_enum { PHYSICAL, SPECIAL, STATUS };
            m_category_enum m_attack_category; 

            AttackResource();
            virtual ~AttackResource();
            StringName GetAttackId() const;
            void SetAttackId(const StringName& id);
            Ref<AudioStream> GetAttackSound() const;
            void SetAttackSound(Ref<AudioStream> stream);
            Ref<SpriteFrames> GetAttackAnimation() const;
            void SetAttackAnimation(const Ref<SpriteFrames>& sprite);


            StringName GetAttackType() const;
            void SetAttackType(const StringName& type);
            /// Power
            int GetAttackPower() const;
            void SetAttackPower(int value);
            /// Accuracy
            int GetAttackAccuracy() const;
            void SetAttackAccuracy(int value);
            /// PP
            int GetAttackPP() const;
            void SetAttackPP(int value);
            /// Type
            m_category_enum GetAttackCategory() const;
            void SetAttackCategory(m_category_enum type);
            /// Contact
            bool GetAttackContacts() const;
            void SetAttackContacts(bool value);



    };
};

VARIANT_ENUM_CAST(AttackResource::m_category_enum);

#endif