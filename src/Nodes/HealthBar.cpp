#include "HealthBar.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

HealthBar::HealthBar() {
}

HealthBar::~HealthBar() {
}

void HealthBar::InitHealthbar(const String &name,int level,int health,bool ally){
}

void HealthBar::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_creature_name_node", "node"),
        &HealthBar::SetCreatureNameNode);
    ClassDB::bind_method(D_METHOD("get_creature_name_node"),
        &HealthBar::GetCreatureNameNode);

    ClassDB::bind_method(D_METHOD("set_creature_level_node", "node"),
        &HealthBar::SetCreatureLevelNode);
    ClassDB::bind_method(D_METHOD("get_creature_level_node"),
        &HealthBar::GetCreatureLevelNode);

    ClassDB::bind_method(D_METHOD("set_creature_healthbar_node", "node"),
        &HealthBar::SetCreatureHealthbarNode);
    ClassDB::bind_method(D_METHOD("get_creature_healthbar_node"),
        &HealthBar::GetCreatureHealthbarNode);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "creature_name_node",
        PROPERTY_HINT_NODE_TYPE, "Label"),
        "set_creature_name_node",
        "get_creature_name_node");

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "creature_level_node",
        PROPERTY_HINT_NODE_TYPE, "Label"),
        "set_creature_level_node",
        "get_creature_level_node");

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "creature_healthbar_node",
        PROPERTY_HINT_NODE_TYPE, "ProgressBar"),
        "set_creature_healthbar_node",
        "get_creature_healthbar_node");
}

void HealthBar::SetCreatureNameNode(Label *node) {
    m_creature_name = node;
}
Label *HealthBar::GetCreatureNameNode() const {
    return m_creature_name;
}
void HealthBar::SetCreatureLevelNode(Label *node) {
    m_creature_level = node;
}
Label *HealthBar::GetCreatureLevelNode() const {
    return m_creature_level;
}
void HealthBar::SetCreatureHealthbarNode(ProgressBar *node) {
    m_creature_healthbar = node;
}
ProgressBar *HealthBar::GetCreatureHealthbarNode() const {
    return m_creature_healthbar;
}



void HealthBar::SetCreatureName(const String &name) {
    if (m_creature_name)
        m_creature_name->set_text(name);
}

void HealthBar::SetCreatureLevel(int level) {
    if (m_creature_level)
        m_creature_level->set_text("Lv. " + String::num_int64(level));
}

void HealthBar::SetCreatureHealth(int health) {
    if (m_creature_healthbar)
        m_creature_healthbar->set_value(health);
}