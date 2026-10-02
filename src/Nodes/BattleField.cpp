#include "BattleField.hpp"
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/classes/texture2d.hpp>

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
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "player_side_positions", PROPERTY_HINT_ARRAY_TYPE, "Vector3"),"set_player_pos","get_player_pos");
    ClassDB::bind_method(D_METHOD("add_player_pos", "pos"), &BattleField::add_player_pos);
    ClassDB::bind_method(D_METHOD("clear_player_pls"), &BattleField::clear_player_pos);

    ClassDB::bind_method(D_METHOD("set_opponent_pos", "pos"), &BattleField::set_opponent_pos);
    ClassDB::bind_method(D_METHOD("get_opponent_pos"), &BattleField::get_opponent_pos);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "opponent_side_positions", PROPERTY_HINT_ARRAY_TYPE, "Vector3"),"set_opponent_pos","get_opponent_pos");
    ClassDB::bind_method(D_METHOD("add_opponent_pos", "pos"), &BattleField::add_opponent_pos);
    ClassDB::bind_method(D_METHOD("clear_opponent_pls"), &BattleField::clear_opponent_pos);

}

void BattleField::_init() {
    // Initialization code here
}


//plyr
void BattleField::set_player_pos(const TypedArray<Vector3> &pos_array) {
    m_player_pos = pos_array;
}
Array BattleField::get_player_pos() const {
    return m_player_pos;
}
void BattleField::add_player_pos(const Vector3 &pos) {
    m_player_pos.append(pos);
    m_player_side_occupancy[pos] = false;
}
void BattleField::clear_player_pos() {
    m_player_pos.clear();
}

//opp
void BattleField::set_opponent_pos(const TypedArray<Vector3> &pos) {
    m_opponent_pos = pos;
}
Array BattleField::get_opponent_pos() const {
    return m_opponent_pos;
}
void BattleField::add_opponent_pos(const Vector3 &pos) {
    m_opponent_pos.append(pos);
    m_opponent_side_occupancy[pos] = false;
}
void BattleField::clear_opponent_pos() {
    m_opponent_pos.clear();
}


void BattleField::initPositions(){
    for (int i = 0; i < m_player_pos.size(); i++) {
        m_player_side_occupancy[m_player_pos[i]] = false;
    }

    for (int i = 0; i < m_opponent_pos.size(); i++) {
        m_opponent_side_occupancy[m_opponent_pos[i]] = false;
    }
}



void BattleField::AddSprites(CreatureSprite3D* sprite,BattleFormat format,bool opponent) {
    godot::UtilityFunctions::print("Adding sprites to battlefield.");

    if (sprite == nullptr) {
        godot::UtilityFunctions::push_error("Cannot add null sprite to battlefield.");
        return;
    }

    if (m_opponent_side_occupancy.keys().size() == 0){
        godot::UtilityFunctions::push_error("opponent positions not set");
    }

    if (m_player_side_occupancy.keys().size() == 0){
        godot::UtilityFunctions::push_error("player positions not set");
    }

    int position_count = 0;

    switch (format)
    {
        case BattleFormat::Singles:
            position_count = 1;
            break;

        case BattleFormat::Dobules:
            position_count = 2;
            break;

        case BattleFormat::Triples:
            position_count = 3;
            break;

        case BattleFormat::TwoVOne:
            position_count = opponent ? 1 : 2;
            break;

        case BattleFormat::TwoVTwo:
            position_count = 2;
            break;
    }

    add_child(sprite);

    godot::UtilityFunctions::print(m_opponent_side_occupancy);

    if (opponent){ 
        Array keys = m_opponent_side_occupancy.keys();

        for (int i = 0; i < keys.size() && i < position_count; i++) {
            Vector3 key = (Vector3)keys[i];

            if (!m_opponent_side_occupancy[key]) {
                sprite->set_position(key);
                m_opponent_side_occupancy[key] = true;
                break;
            }
        }
    }
    else{
        Array keys = m_player_side_occupancy.keys();

        for (int i = 0; i < keys.size() && i < position_count; i++) {
            Vector3 key = (Vector3)keys[i];

            if (!m_player_side_occupancy[key]) {
                sprite->set_position(key);
                m_player_side_occupancy[key] = true;
                break;
            }
        }
    }

    AdjustSprite(sprite);
}


void BattleField::AdjustSprite(CreatureSprite3D* sprite){
    //should probably have checks
    Ref<SpriteFrames> frames = sprite->get_sprite_frames();
    if (frames.is_null()) {
        godot::UtilityFunctions::push_error("SpriteFrames resource is null. Cannot adjust sprite.");
        return;
    }
    

    StringName anim = sprite->get_animation();
    int frame = sprite->get_frame();
    
    Ref<Texture2D> tex = frames->get_frame_texture(anim, frame);
    float h = tex->get_height();
    sprite->set_offset(Vector2(0, h * 0.5f));
}


