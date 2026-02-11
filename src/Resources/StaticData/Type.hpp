#ifndef TYPE_RESOURCE_H
#define TYPE_RESOURCE_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

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
#endif