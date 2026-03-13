#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/label.hpp>

#include <godot_cpp/classes/ref.hpp>

namespace godot {
    class DialogueBox : public Control {
        GDCLASS(DialogueBox, Control);

        private:
            Label *m_dialogue_label = nullptr;
            float m_char_time = 0.04f; //seconds per character
            float m_dialogue_end_delay;

<<<<<<< Updated upstream
            float counter = 0.0f;
            int text_length = 0;
            String full_text;
=======
            float m_char_time = 0.1f; //seconds per character
            float m_counter = 0.0f; //visible characters
            int m_current_dialogue;
            int m_text_length = 0;
            float m_dialogue_delay = 1.0f; //between each texts
            bool m_waiting_to_advance;
            bool m_dialogue_enabled = true;
            Array m_dialogue_queue;
            String m_full_text;
>>>>>>> Stashed changes

            
        protected:
            static void _bind_methods();
        
        public:
            DialogueBox();
            virtual ~DialogueBox();
        

        //node
        void SetDialogueLabelNode(Label *node);
        Label *GetDialogueLabelNode() const;

<<<<<<< Updated upstream
        void SetCharacterTime(float time);
        float GetCharacterTime() const;

        void StartDialogue(const String &text);
=======
        void StartDialogue();
        void AdvanceDialogueStartDelay(float delay = 1.0f);
        void AdvanceDialogue();
        void AddTextToQueue(const String &text);
>>>>>>> Stashed changes
        void _process(double delta) override;

    };
};

#endif // DIALOGUEBOX_H