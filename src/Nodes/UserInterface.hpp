#ifndef USERINTERFACE_H
#define USERINTERFACE_H

//#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "HealthBar.hpp"

namespace godot {
    class UserInterface : public CanvasLayer { 
        GDCLASS(UserInterface, CanvasLayer);

        private:

            static UserInterface* s_instance;
            


        protected:
            static void _bind_methods();
        
        public:
            UserInterface();
            virtual ~UserInterface();
            void _init();
            void _ready() override;

            static UserInterface* GetInstance();

            static VBoxContainer *m_opponents_container;
            static VBoxContainer *m_allys_container;
        
            //node
            void SetOpponentsContainer(VBoxContainer *node);
            VBoxContainer *GetOpponentsContainer() const;

            void SetAllysContainer(VBoxContainer *node);
            VBoxContainer *GetAllysContainer() const;
            

            //healthbar

            void InitHealthbar(const String &name, int level,int health,bool ally);

    };
};

#endif // USERINTERFACE_H