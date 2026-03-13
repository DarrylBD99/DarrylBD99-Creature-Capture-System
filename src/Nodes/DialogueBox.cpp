#include "DialogueBox.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/classes/scene_tree_timer.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>

using namespace godot;

DialogueBox::DialogueBox() {
    set_process(true);
    set_process_unhandled_input(true);
}

DialogueBox::~DialogueBox() {
}
void DialogueBox::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_dialouge_label_node", "node"),
        &DialogueBox::SetDialogueLabelNode);

    ClassDB::bind_method(D_METHOD("get_dialouge_label_node"),
        &DialogueBox::GetDialogueLabelNode);
    
    ClassDB::bind_method(D_METHOD("set_character_time", "time"),
        &DialogueBox::SetCharacterTime);
    
    ClassDB::bind_method(D_METHOD("get_character_time"),
        &DialogueBox::GetCharacterTime);

    ClassDB::bind_method(D_METHOD("StartDialogue"),
        &DialogueBox::StartDialogue);
    
    ClassDB::bind_method(D_METHOD("AdvanceDialogue"), &DialogueBox::AdvanceDialogue);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT,
        "dialouge_label_node",
        PROPERTY_HINT_NODE_TYPE,
        "Label"),
        "set_dialouge_label_node",
        "get_dialouge_label_node");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT,
        "character_time", PROPERTY_HINT_RANGE, "0.01,2.0,0.01"),
        "set_character_time",
        "get_character_time");
}

void DialogueBox::SetDialogueLabelNode(Label *node) {
    m_dialogue_label = node;
}

Label *DialogueBox::GetDialogueLabelNode() const {
    return m_dialogue_label;
}

void DialogueBox::SetCharacterTime(float time) {
    m_char_time = time;
}

float DialogueBox::GetCharacterTime() const {
    return m_char_time;
}

void DialogueBox::_unhandled_input(const Ref<InputEvent> &event) {

    if (!dialogue_enabled){return;}
    if (!event.is_valid()){return;}
    if (!m_dialogue_label) {return;}

    if (event->is_action_pressed("ui_accept")) {
        
        int current = m_dialogue_label->get_visible_characters();

        if (current < text_length)
            {m_dialogue_label->set_visible_characters(text_length);
            if (!waiting_to_advance) {
                waiting_to_advance = true; 
                AdvanceDialogueStartDelay(dialogue_delay);
            }
        } 
        else {AdvanceDialogue();}
    }
}

void DialogueBox::AddTextToQueue(const String &text){
    if (!dialogue_enabled){return;}

    dialogue_queue.append(text);
    UtilityFunctions::print(dialogue_queue);

    if (dialogue_queue.size() == 1){
        StartDialogue();
    }

}

void DialogueBox::StartDialogue(){
    if (!dialogue_enabled){return;}
    if (!m_dialogue_label){return;}
    
    if (dialogue_queue.size() == 0){
        return;
        //DO SOMETHING HERE TO INDICATE THAT THE QUEUE IS FINISHED AND TO PROGRESS (signal)
    }
    
    String text = dialogue_queue[0];
    UtilityFunctions::print(text);

    m_dialogue_label->set_text(dialogue_queue[0]);

    text_length = text.length();
    counter = 0.0f;

    // reset before animating
    m_dialogue_label->set_visible_characters(0);
    m_dialogue_label->set_visible_ratio(0.0);

}

void DialogueBox::_process(double delta) {
    if (!dialogue_enabled){return;}

    if (dialogue_queue.size() > 0){
    }

    if (!m_dialogue_label)
        return;
    if (text_length <= 0)
        return;

    int current = m_dialogue_label->get_visible_characters();

    if (current < 0){current = 0;}
    if (current >= text_length){return;}

    counter += delta;

    while (counter >= m_char_time && current < text_length) {
        current++;
        m_dialogue_label->set_visible_characters(current);
        counter -= m_char_time;
    }

    if (current >= text_length && !waiting_to_advance){
        waiting_to_advance = true; //so it doesn't get called multiple times, although TODO make sure this isn't fragile
        AdvanceDialogueStartDelay(dialogue_delay);
         
    }
}

void DialogueBox::AdvanceDialogueStartDelay(float delay){
    if (timer.is_valid()){
        timer->disconnect("timeout", Callable(this, "AdvanceDialogue"));
        timer = Ref<SceneTreeTimer>();}
     
    timer = get_tree()->create_timer(delay);
    timer->connect("timeout", Callable(this, "AdvanceDialogue"));
}
void DialogueBox::AdvanceDialogue(){
    waiting_to_advance = false;
    if (dialogue_queue.size() > 0){dialogue_queue.remove_at(0);}
    StartDialogue();
}

