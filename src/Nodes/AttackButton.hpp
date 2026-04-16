#ifndef ATTACKBUTTON_H
#define ATTACKBUTTON_H

#include <godot_cpp/classes/button.hpp>
#include <StaticData/Attacks.hpp>

namespace godot {
    class AttackButton : public Button {
        GDCLASS(AttackButton, Button);

        private:
            Ref<AttackResource> m_attack;

        protected:
            static void _bind_methods();
        
        public:
            AttackButton();
            virtual ~AttackButton();
            void _init();

        void SetAttackButtonMove(const Ref<AttackResource> attack);
        Ref<AttackResource> GetAttackButtonMove() const;
        virtual void on_attack_set();

    };
};

#endif // ATTACKBUTTON_H