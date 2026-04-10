#include "BattleTeam.hpp"

using namespace godot;

// Constructor / Destructor

BattleTeam::BattleTeam() {
    m_team_name = "";
    m_members.clear();
}

BattleTeam::~BattleTeam() {}

void BattleTeam::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_team_name", "name"), &BattleTeam::set_team_name);
    ClassDB::bind_method(D_METHOD("get_team_name"), &BattleTeam::get_team_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "team_name"), "set_team_name", "get_team_name");

    ClassDB::bind_method(D_METHOD("set_members", "members"), &BattleTeam::set_members);
    ClassDB::bind_method(D_METHOD("get_members"), &BattleTeam::get_members);
    //ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "members"), "set_members", "get_members");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "members", PROPERTY_HINT_ARRAY_TYPE, "BattleCreature"),"set_members","get_members");

    ClassDB::bind_method(D_METHOD("add_member", "member"), &BattleTeam::add_member);
    ClassDB::bind_method(D_METHOD("clear_members"), &BattleTeam::clear_members);
    ClassDB::bind_method(D_METHOD("get_member_count"), &BattleTeam::get_member_count);
    ClassDB::bind_method(D_METHOD("get_member", "index"), &BattleTeam::get_member);
}




void BattleTeam::set_team_name(const String &name) {
    m_team_name = name;
}

String BattleTeam::get_team_name() const {
    return m_team_name;
}

void BattleTeam::set_members(const Array &members) {
    m_members = members;
}

Array BattleTeam::get_members() const {
    return m_members;
}

void BattleTeam::add_member(const Ref<BattleCreature> &member) {
    m_members.append(member);
}

void BattleTeam::clear_members() {
    m_members.clear();
}

int BattleTeam::get_member_count() const {
    return m_members.size();
}

Ref<BattleCreature> BattleTeam::get_member(int index) const {
    if (index < 0 || index >= m_members.size()) {
        return Ref<BattleCreature>();
    }
    return m_members[index];
}