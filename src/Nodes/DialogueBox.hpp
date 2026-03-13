#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/scene_tree_timer.hpp>


#include <godot_cpp/classes/ref.hpp>

namespace godot {
    class DialogueBox : public Control {
        GDCLASS(DialogueBox, Control);

        private:
            Label *m_dialogue_label = nullptr;

            float m_char_time = 0.04f; //seconds per character
            
            float dialogue_end_delay;
            float counter = 0.0f; //visible characters
            int current_dialogue;
            int text_length = 0;
            float dialogue_delay = 1.0f; //between each texts
            bool waiting_to_advance = false;
            bool dialogue_enabled = true;
            Array dialogue_queue;
            String full_text;
            Ref<SceneTreeTimer> timer;
            

            
        protected:
            static void _bind_methods();
        
        public:
            DialogueBox();
            virtual ~DialogueBox();

        void _unhandled_input(const Ref<InputEvent> &event) override;
        
        //node
        void SetDialogueLabelNode(Label *node);
        Label *GetDialogueLabelNode() const;

        void SetCharacterTime(float time);
        float GetCharacterTime() const;

        void StartDialogue();
        void AdvanceDialogueStartDelay(float delay = 1.0f);
        void AdvanceDialogue();
        void AddTextToQueue(const String &text);
        void _process(double delta) override;

    };
};

#endif // DIALOGUEBOX_H