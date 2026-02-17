#ifndef CREATURESPRITE3D_H
#define CREATURESPRITE3D_H

#include <godot_cpp/classes/animated_sprite3d.hpp>

#include "CreatureSprite.hpp"

namespace godot {
    class CreatureSprite3D : public AnimatedSprite3D, public CreatureSprite {
        GDCLASS(CreatureSprite3D, AnimatedSprite3D);

        protected:
            static void _bind_methods();
        public:
            CreatureSprite3D();
            virtual ~CreatureSprite3D();
            void _init();

            StringName GetSpeciesId() const;
            void SetSpeciesId(const StringName& id);
            Ref<SpeciesResource> GetSpeciesResource() const;
            void SetSpeciesResource(Ref<SpeciesResource> resource);
            void SetSprite(bool direction);
    };
};

#endif