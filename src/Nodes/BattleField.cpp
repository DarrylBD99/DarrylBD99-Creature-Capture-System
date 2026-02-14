#include "BattleField.hpp"

using godot::BattleField;

BattleField::BattleField() {
    // Constructor code here
}

BattleField::~BattleField() {
    // add your cleanup here
}

void BattleField::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_method(D_METHOD("get_player_pos"), &BattleField::GetPlayerPos);
    ClassDB::bind_method(D_METHOD("set_player_pos", "pos"), &BattleField::SetPlayerPos);
    ClassDB::bind_method(D_METHOD("get_opponent_pos"), &BattleField::GetOpponentPos);
    ClassDB::bind_method(D_METHOD("set_opponent_pos", "pos"), &BattleField::SetOpponentPos);

    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "player_pos"), "set_player_pos", "get_player_pos");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "opponent_pos"), "set_opponent_pos", "get_opponent_pos");
}

void BattleField::_init() {
    // Initialization code here
}

godot::Vector3 BattleField::GetPlayerPos() const {
    return m_player_pos;
}

void BattleField::SetPlayerPos(const godot::Vector3& pos) {
    m_player_pos = pos;
}

godot::Vector3 BattleField::GetOpponentPos() const {
    return m_opponent_pos;
}

void BattleField::SetOpponentPos(const godot::Vector3& pos) {
    m_opponent_pos = pos;
}