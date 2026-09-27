#include "ActionResource.hpp"

using godot::ActionResource;

ActionResource::ActionResource() {
}

ActionResource::~ActionResource() {
}



int ActionResource::GetPriority() const {
    return m_priority;
}

void ActionResource::SetPriority(int value) {
    m_priority = value;
}

godot::ActionType ActionResource::GetEventType() const {
    return m_event_type;
}

void ActionResource::SetEventType(godot::ActionType type) {
    m_event_type = type;
}

godot::Ref<godot::BattleCreature> ActionResource::GetActorId() const {
    return m_actor;
}

void ActionResource::SetActorId(const Ref<BattleCreature> id) {
    m_actor = id;
}

godot::Ref<godot::BattleCreature> ActionResource::GetTargetId() const {
    return m_target;
}

void ActionResource::SetTargetId(const Ref<BattleCreature> id) {
    m_target = id;
}

// for MOVE events
godot::StringName ActionResource::GetMoveId() const {
    return m_move_id;
}

void ActionResource::SetMoveId(const godot::StringName& id) {
    m_move_id = id;
}

// for USE_ITEM events
godot::StringName ActionResource::GetItemId() const {
    return m_item_id;
}

void ActionResource::SetItemId(const godot::StringName& id) {
    m_item_id = id;
}

// for SWITCH events
int ActionResource::GetSlot() const {
    return m_slot;
}

void ActionResource::SetSlot(int value) {
    m_slot = value;
}