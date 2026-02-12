#ifndef TYPE_RESOURCE_H
#define TYPE_RESOURCE_H

#include <godot_cpp/classes/resource.hpp>
//#include <godot_cpp/classes/audio_stream.hpp>

namespace godot {
    class TypeResource : public Resource {
        GDCLASS(TypeResource, Resource);
        
        private:
            StringName m_type_id;
            String m_type_name;

            TypedArray<StringName> m_weaknesses;
            TypedArray<StringName> m_resistances;

        protected:
            static void _bind_methods();
            
        public:

            enum m_type_enum {NORMAL,FIRE,WATER,ICE,DRAGON,FAIRY,ROCK,
            GROUND,ELECTRIC,STEEL,POSION,FLYING,DARK,PSYCHIC,
            GRASS,BUG,FIGHTING,GHOST,NONE};
            m_type_enum m_move_type; 


            enum m_category_enum { PHYSICAL, SPECIAL, STATUS };
            m_category_enum m_move_category; 


            TypeResource();
            virtual ~TypeResource();
            StringName GetTypeId() const;
            void SetTypeId(const StringName& id);
            String GetTypeName() const;
            void SetTypeName(const String& name);
            TypedArray<StringName> GetWeaknesses() const;
            void SetWeaknesses(const TypedArray<StringName>& weaknesses);
            TypedArray<StringName> GetResistances() const;
            void SetResistances(const TypedArray<StringName>& resistances);
    };
};

VARIANT_ENUM_CAST(TypeResource::m_type_enum);
VARIANT_ENUM_CAST(TypeResource::m_category_enum);

#endif