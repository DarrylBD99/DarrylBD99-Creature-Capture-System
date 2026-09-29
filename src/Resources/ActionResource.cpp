#include "ActionResource.hpp"

using godot::ActionResource;

ActionResource::ActionResource() {
}

ActionResource::~ActionResource() {
}




godot::ActionType ActionResource::GetActionType() const {
    return m_action_type;
}

void ActionResource::SetActionType(godot::ActionType type) {
    m_action_type = type;
}

godot::Ref<godot::BattleCreature> ActionResource::GetActor() const {
    return m_actor;
}

void ActionResource::SetActor(const Ref<BattleCreature> id) {
    m_actor = id;
}

godot::Ref<godot::BattleCreature> ActionResource::GetTarget() const {
    return m_target;
}

void ActionResource::SetTarget(const Ref<BattleCreature> id) {
    m_target = id;
}

// for MOVE events
godot::Ref<godot::AttackResource> ActionResource::GetMoveId() const {
    return m_move_id;
}

void ActionResource::SetMoveId(const Ref<AttackResource> id) {
    m_move_id = id;
}

/// for USE_ITEM events
// godot::StringName ActionResource::GetItemId() const {
//     return m_item_id;
// }

// void ActionResource::SetItemId(const godot::StringName& id) {
//     m_item_id = id;
// }

// for SWITCH events
int ActionResource::GetSlot() const {
    return m_target_slot;
}

void ActionResource::SetSlot(int value) {
    m_target_slot = value;
} 

int ActionResource::GetPriority() const {
    
    if (m_action_type == ActionType::MOVE && m_move_id.is_valid()) {
        return m_move_id->GetPriority();
    }

    switch (m_action_type) {
        case ActionType::USE_ITEM: return 20;
        case ActionType::SWITCH:   return 15;
        case ActionType::FLEE:     return 10;
        case ActionType::MOVE:     return 0;
        case ActionType::JACKSHIT: return 0;
    }
    return 0;
}