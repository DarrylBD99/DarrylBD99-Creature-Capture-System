#include "DialogueBox.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

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
    
    ClassDB::bind_method(D_METHOD("set_character_time", "time"),
        &DialogueBox::SetCharacterTime);
    
    ClassDB::bind_method(D_METHOD("get_character_time"),
        &DialogueBox::GetCharacterTime);

    ClassDB::bind_method(D_METHOD("StartDialogue", "text"),
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

void DialogueBox::SetCharacterTime(float time) {
    m_char_time = time;
}

float DialogueBox::GetCharacterTime() const {
    return m_char_time;
}

void DialogueBox::StartDialogue(const String &text) {

    if (!m_dialogue_label)
        return;

    m_dialogue_label->set_text(text);

    text_length = text.length();
    counter = 0.0f;

    // Force reset BEFORE animation
    m_dialogue_label->set_visible_characters(0);
    m_dialogue_label->set_visible_ratio(0.0);

}

void DialogueBox::_process(double delta) {

    if (!m_dialogue_label)
        return;
    if (text_length <= 0)
        return;

    int current = m_dialogue_label->get_visible_characters();

    if (current < 0)
        current = 0;
    
    if (current >= text_length)
        return;

    counter += delta;

    while (counter >= m_char_time && current < text_length) {
        current++;
        m_dialogue_label->set_visible_characters(current);
        counter -= m_char_time;
    }
}