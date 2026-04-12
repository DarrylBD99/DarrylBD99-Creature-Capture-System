#include "BattleField.hpp"
#include <godot_cpp/variant/array.hpp>

using godot::BattleField;

using namespace godot;

BattleField::BattleField() {
    // Constructor code here
}

BattleField::~BattleField() {
    // add your cleanup here
}

void BattleField::_bind_methods() {
    // Binding methods to Godot
    ClassDB::bind_method(D_METHOD("set_player_pos", "pos"), &BattleField::set_player_pos);
    ClassDB::bind_method(D_METHOD("get_player_pos"), &BattleField::get_player_pos);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "members", PROPERTY_HINT_ARRAY_TYPE, "Marker3d"),"set_player_pos","get_player_pos");
    ClassDB::bind_method(D_METHOD("add_player_pos", "pos"), &BattleField::add_player_pos);
    ClassDB::bind_method(D_METHOD("clear_player_pls"), &BattleField::clear_player_pos);

    ClassDB::bind_method(D_METHOD("set_opponent_pos", "pos"), &BattleField::set_player_pos);
    ClassDB::bind_method(D_METHOD("get_opponent_pos"), &BattleField::get_player_pos);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "members", PROPERTY_HINT_ARRAY_TYPE, "Marker3d"),"set_opponent_pos","get_opponent_pos");
    ClassDB::bind_method(D_METHOD("add_opponent_pos", "pos"), &BattleField::add_player_pos);
    ClassDB::bind_method(D_METHOD("clear_opponent_pls"), &BattleField::clear_player_pos);


    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "player_pos"), "set_player_pos", "get_player_pos");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "opponent_pos"), "set_opponent_pos", "get_opponent_pos");
}

void BattleField::_init() {
    // Initialization code here
}


//plyr
void BattleField::set_player_pos(const Array &pos) {
    m_player_pos = pos;
}
Array BattleField::get_player_pos() const {
    return m_player_pos;
}
void BattleField::add_player_pos(const Marker3D *pos) {
    m_player_pos.append(pos);
}
void BattleField::clear_player_pos() {
    m_player_pos.clear();
}

//opp
void BattleField::set_opponent_pos(const Array &pos) {
    m_opponent_pos = pos;
}
Array BattleField::get_opponent_pos() const {
    return m_opponent_pos;
}
void BattleField::add_opponent_pos(const Marker3D *pos) {
    m_opponent_pos.append(pos);
}
void BattleField::clear_opponent_pos() {
    m_opponent_pos.clear();
}


