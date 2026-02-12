#ifndef MOVES_RESOURCE_H
#define MOVES_RESOURCE_H

#include <godot_cpp/classes/resource.hpp>
#include <Type.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>


namespace godot {
    class MoveResource : public Resource {
        GDCLASS(MoveResource, Resource);
        
        private:
            StringName m_move_id;
            Ref<AudioStream> m_move_sound;
            Ref<SpriteFrames> m_move_animation;

            int m_move_power;
            int m_move_accuracy;
            int m_move_pp;
            bool m_move_contacts;

            TypeResource::m_type_enum m_move_type;
            TypeResource::m_category_enum m_move_category;

            /// TODO
            ///insert chance of secondary effect (eg. burn,flinch)
            ///insert other charastaristics (eg. sound move, ball move)
            ///insert who it targets (1 or 2 opponent or ally ect.)
            ///insert move description


        protected:
            static void _bind_methods();
            
        public:
            


            MoveResource();
            virtual ~MoveResource();
            StringName GetMoveId() const;
            void SetMoveId(const StringName& id);
            Ref<AudioStream> GetMoveSound() const;
            void SetMoveSound(Ref<AudioStream> stream);
            Ref<SpriteFrames> GetMoveAnimation() const;
            void SetMoveAnimation(const Ref<SpriteFrames>& sprite);


            TypeResource::m_type_enum GetMoveType() const;
            void SetMoveType(TypeResource::m_type_enum type);
            /// Power
            int GetMovePower() const;
            void SetMovePower(int value);
            /// Accuracy
            int GetMoveAccuracy() const;
            void SetMoveAccuracy(int value);
            /// PP
            int GetMovePP() const;
            void SetMovePP(int value);
            /// Type
            TypeResource::m_category_enum GetMoveCategory() const;
            void SetMoveCategory(TypeResource::m_category_enum type);
            /// Contact
            bool GetMoveContacts() const;
            void SetMoveContacts(bool value);



    };
};


#endif