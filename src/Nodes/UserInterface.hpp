#ifndef USERINTERFACE_H
#define USERINTERFACE_H

//#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "HealthBar.hpp"
#include "DialogueBox.hpp"

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
            static HBoxContainer *m_dialogue_box_container;
            static Control *m_attacks_buttons_parent;

            static Ref<PackedScene> s_healthbar_scene;
            static Ref<PackedScene> s_dialogue_box_scene;
        
            //node
            void SetOpponentsContainer(VBoxContainer *node);
            VBoxContainer *GetOpponentsContainer() const;

            void SetAllysContainer(VBoxContainer *node);
            VBoxContainer *GetAllysContainer() const;

            void SetDialogueBoxContainer(HBoxContainer *node);
            HBoxContainer *GetDialogueBoxContainer() const;

            void SetAttacksButtonsParent(Control *node);
            Control *GetAttacksButtonsParent() const;

            void SetHealthbarScene(Ref<PackedScene> healthbar);
            Ref<PackedScene> GetHealthbarScene() const;

            void SetDialogueBoxScene(Ref<PackedScene> healthbar);
            Ref<PackedScene> GetDialogueBoxScene() const;


            void InitHealthbar(const String &name, int level,int health,bool ally);
            void InitDialogueBox();
            Array GetAttacksButtons();
            void InitAttacksButtons();

    };
};

#endif // USERINTERFACE_H