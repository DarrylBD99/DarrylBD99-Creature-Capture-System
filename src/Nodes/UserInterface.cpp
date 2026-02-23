#include "UserInterface.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

VBoxContainer *UserInterface::m_opponents_container = nullptr;
VBoxContainer *UserInterface::m_allys_container = nullptr;

UserInterface::UserInterface() {
}

UserInterface::~UserInterface() {
}

void UserInterface::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_opponents_container", "node"),
        &UserInterface::SetOpponentsContainer);
    ClassDB::bind_method(D_METHOD("get_opponents_container"),
        &UserInterface::GetOpponentsContainer);

    ClassDB::bind_method(D_METHOD("set_allys_container", "node"),
        &UserInterface::SetAllysContainer);
    ClassDB::bind_method(D_METHOD("get_allys_container"),
        &UserInterface::GetAllysContainer);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "opponents_container",
        PROPERTY_HINT_NODE_TYPE, "VBoxContainer"),
        "set_opponents_container",
        "get_opponents_container");

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "allys_container",
        PROPERTY_HINT_NODE_TYPE, "VBoxContainer"),
        "set_allys_container",
        "get_allys_container");
}

void UserInterface::_init() {
}

void UserInterface::SetOpponentsContainer(VBoxContainer *node) {
    m_opponents_container = node;
}

VBoxContainer *UserInterface::GetOpponentsContainer() const {
    return m_opponents_container;
}

void UserInterface::SetAllysContainer(VBoxContainer *node) {
    m_allys_container = node;
}

VBoxContainer *UserInterface::GetAllysContainer() const {
    return m_allys_container;
}