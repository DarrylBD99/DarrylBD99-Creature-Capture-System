#include "DialogueBox.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/classes/scene_tree_timer.hpp>

using namespace godot;

DialogueBox::DialogueBox() {
    set_process(true);
}

DialogueBox::~DialogueBox() {
}

void DialogueBox::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_dialouge_label_node", "node"),
        &DialogueBox::SetDialogueLabelNode);

    ClassDB::bind_method(D_METHOD("get_dialouge_label_node"),
        &DialogueBox::GetDialogueLabelNode);
    
<<<<<<< Updated upstream
    ClassDB::bind_method(D_METHOD("set_character_time", "time"),
        &DialogueBox::SetCharacterTime);
    
    ClassDB::bind_method(D_METHOD("get_character_time"),
        &DialogueBox::GetCharacterTime);

    ClassDB::bind_method(D_METHOD("StartDialogue", "text"),
=======
    ClassDB::bind_method(D_METHOD("StartDialogue"),
>>>>>>> Stashed changes
        &DialogueBox::StartDialogue);

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

<<<<<<< Updated upstream
void DialogueBox::SetCharacterTime(float time) {
    m_char_time = time;
}

float DialogueBox::GetCharacterTime() const {
    return m_char_time;
}

void DialogueBox::StartDialogue(const String &text) {
=======
void DialogueBox::AddTextToQueue(const String &text){
    if (!m_dialogue_enabled){return;}
    m_dialogue_queue.append(text);
    UtilityFunctions::print(m_dialogue_queue);

    int current = m_dialogue_label->get_visible_characters();


    current = 0; //TEMP

    if (current == 0){
        StartDialogue();
    }

}

void DialogueBox::StartDialogue(){
    if (!m_dialogue_enabled){return;}
>>>>>>> Stashed changes

    if (!m_dialogue_label)
        return;
    
    if (m_dialogue_queue.size() == 0){
        return;
        //DO SOMETHING HERE TO INDICATE THAT THE QUEUE IS FINISHED AND TO PROGRESS
    }
    
    String text = m_dialogue_queue[0];
    UtilityFunctions::print(text);

    m_dialogue_label->set_text(m_dialogue_queue[0]);

    text_length = text.length();
    counter = 0.0f;

    // reset before animation
    m_dialogue_label->set_visible_characters(0);
    m_dialogue_label->set_visible_ratio(0.0);

}

void DialogueBox::_process(double delta) {
    if (!m_dialogue_enabled){return;}

    if (m_dialogue_queue.size() > 0){
    }

    if (!m_dialogue_label)
        return;
    if (text_length <= 0)
        return;

    int current = m_dialogue_label->get_visible_characters();

<<<<<<< Updated upstream
    if (current < 0)
        current = 0;
    
    if (current >= text_length)
        return;
=======
    if (current < 0){current = 0;}
    if (current >= m_text_length){return;}

    UtilityFunctions::print("delta:", delta);
>>>>>>> Stashed changes

    counter += delta;

    while (counter >= m_char_time && current < text_length) {
        current++;
        m_dialogue_label->set_visible_characters(current);
        counter -= m_char_time;
    }

    if (current >= m_text_length && !m_waiting_to_advance){
        AdvanceDialogueStartDelay(m_dialogue_delay);
        m_waiting_to_advance = true; //so it doesn't get called multiple times, althought TODO make sure this isn't fragile
    }
}

void DialogueBox::AdvanceDialogueStartDelay(float delay){
    auto timer = get_tree()->create_timer(delay);
    timer->connect("timeout", Callable(this, "AdvanceDialogue"));
}
void DialogueBox::AdvanceDialogue(){
    m_waiting_to_advance = false;
    if (m_dialogue_queue.size() > 0){m_dialogue_queue.remove_at(0);}
    StartDialogue();
}

