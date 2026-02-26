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

            float m_char_time = 0.1f; //seconds per character
            float m_counter = 0.0f;
            int m_text_length = 0;
            String m_full_text;

        protected:
            static void _bind_methods();
        
        public:
            DialogueBox();
            virtual ~DialogueBox();
        

        //node
        void SetDialogueLabelNode(Label *node);
        Label *GetDialogueLabelNode() const;

        void StartDialogue(const String &text);
        void _process(double delta) override;

    };
};

#endif // DIALOGUEBOX_H