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
    ClassDB::bind_method(godot::D_METHOD("on_attack_set"),&AttackButton::on_attack_set);
}


void AttackButton::SetAttackButtonMove(const Ref<AttackResource> attack) {
    m_attack = attack;
    on_attack_set();
}

Ref<AttackResource> AttackButton::GetAttackButtonMove() const {
    return m_attack;
}

void AttackButton::on_attack_set(){
}

