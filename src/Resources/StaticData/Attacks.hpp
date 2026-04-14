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
            Ref<SpriteFrames> m_attack_animation;

            int m_attack_power = 0;
            int m_attack_accuracy = 100;
            int m_attack_pp = 10;

            /// TODO everything

        protected:
            static void _bind_methods();
            
        public:

            AttackResource();
            virtual ~AttackResource();
            StringName GetAttackId() const;
            void SetAttackId(const StringName& id);
            Ref<SpriteFrames> GetAttackAnimation() const;
            void SetAttackAnimation(const Ref<SpriteFrames>& sprite);

            /// Power
            int GetAttackPower() const;
            void SetAttackPower(int value);
            /// Accuracy
            int GetAttackAccuracy() const;
            void SetAttackAccuracy(int value);
            /// PP
            int GetAttackPP() const;
            void SetAttackPP(int value);

    };
};

#endif