#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/progress_bar.hpp>

#include <godot_cpp/classes/ref.hpp>

namespace godot {
    class HealthBar : public Control {
        GDCLASS(HealthBar, Control);

        private:
            Label *m_creature_name = nullptr;
            Label *m_creature_level = nullptr;
            ProgressBar *m_creature_healthbar = nullptr; // (should properly rename this)

        protected:
            static void _bind_methods();
        
        public:
            HealthBar();
            virtual ~HealthBar();
            void _init();
        
        void InitHealthbar(String &name,int level,int health);

        //node
        void SetCreatureNameNode(Label *node);
        Label *GetCreatureNameNode() const;

        void SetCreatureLevelNode(Label *node);
        Label *GetCreatureLevelNode() const;

        void SetCreatureHealthbarNode(ProgressBar *node);
        ProgressBar *GetCreatureHealthbarNode() const;

        //values
        void SetCreatureName(const String &name);
        void SetCreatureLevel(int level);
        void SetCreatureHealth(int health);

    };
};

#endif // HEALTHBAR_H