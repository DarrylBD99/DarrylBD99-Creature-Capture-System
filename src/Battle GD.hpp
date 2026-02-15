#ifndef BATTLE_GD_HPP
#define BATTLE_GD_HPP

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {
    class CCS_Battle : public RefCounted {
        GDCLASS(CCS_Battle, RefCounted);
        
        public:
            static void initialize_battle_singleton();

        protected:
            static void _bind_methods();
    };
};


#endif // BATTLE_GD_HPP