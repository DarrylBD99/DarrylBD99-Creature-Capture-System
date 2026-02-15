#ifndef BATTLE_BASE_HPP
#define BATTLE_BASE_HPP

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


#endif // BATTLE_BASE_HPP