#ifndef USERINTERFACE_H
#define USERINTERFACE_H

//#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/container.hpp>
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
            VBoxContainer *m_opponents_container = nullptr;
            VBoxContainer *m_allys_container = nullptr;
            Container *m_dialogue_box_container = nullptr;
            Control *m_attacks_buttons_parent = nullptr;

        protected:
            static void _bind_methods();
        
        public:
            UserInterface();
            virtual ~UserInterface();
            void _init();
            void _ready() override;
            
            static UserInterface* GetInstance();

            static Ref<PackedScene> s_healthbar_scene;
            static Ref<PackedScene> s_dialogue_box_scene;
        
            DialogueBox* dialogue_box = nullptr;

            //node
            void SetOpponentsContainer(VBoxContainer *node);
            VBoxContainer *GetOpponentsContainer() const;

            void SetAllysContainer(VBoxContainer *node);
            VBoxContainer *GetAllysContainer() const;

            void SetDialogueBoxContainer(Container *node);
            Container *GetDialogueBoxContainer() const;

            void SetAttacksButtonsParent(Control *node);
            Control *GetAttacksButtonsParent() const;

            void SetHealthbarScene(Ref<PackedScene> healthbar);
            Ref<PackedScene> GetHealthbarScene() const;

            void SetDialogueBoxScene(Ref<PackedScene> healthbar);
            Ref<PackedScene> GetDialogueBoxScene() const;

            static void FreeStaticResources();

            void InitHealthbar(const String &name, int level,int health,bool ally);
            void InitDialogueBox();
            Array GetAttacksButtons();
            void InitAttacksButtons();

    };
};

#endif // USERINTERFACE_H