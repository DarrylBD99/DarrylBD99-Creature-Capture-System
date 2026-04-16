#ifndef CREATURESPRITE3D_H
#define CREATURESPRITE3D_H

#include <godot_cpp/classes/animated_sprite3d.hpp>

#include "CreatureSprite.hpp"

namespace godot {
    class CreatureSprite3D : public AnimatedSprite3D, public CreatureSprite {
        GDCLASS(CreatureSprite3D, AnimatedSprite3D);

        protected:
            static void _bind_methods();
            StringName m_speciesId; // isn't this redundent since SpeciesId is in SpeciesResource

        public:
            CreatureSprite3D();
            virtual ~CreatureSprite3D();
            void _init();

            Ref<SpeciesResource> GetSpeciesResource() const;
            void SetSpeciesResource(Ref<SpeciesResource> resource);
            void SetSprite(bool direction);

            void SetSpeciesId(const StringName& id);

            StringName GetSpeciesId() const;
    };
};

#endif