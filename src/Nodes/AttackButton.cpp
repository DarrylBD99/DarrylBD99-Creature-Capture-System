#include "AttackButton.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

AttackButton::AttackButton() {
}

AttackButton::~AttackButton() {
}


void AttackButton::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_attack_button_move", "attack"),&AttackButton::SetAttackButtonMove);
    ClassDB::bind_method(D_METHOD("get_attack_button_move"),&AttackButton::GetAttackButtonMove);
}


void AttackButton::SetAttackButtonMove(const Ref<AttackResource> attack) {
    m_attack = attack;
}

Ref<AttackResource> AttackButton::GetAttackButtonMove() const {
    return m_attack;
}
