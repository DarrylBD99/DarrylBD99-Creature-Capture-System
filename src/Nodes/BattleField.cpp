#include "BattleField.hpp"
#include <godot_cpp/classes/texture2d.hpp>

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


void BattleField::AddSprites(CreatureSprite3D* sprite,bool opponent) {
    godot::UtilityFunctions::print("Adding opponent's sprite to battlefield.");
    if (sprite == nullptr) {
        godot::UtilityFunctions::push_error("Cannot add null opponent sprite to battlefield.");
        return;
    }
    add_child(sprite);

    if (opponent){sprite->set_position(m_opponent_pos);}
    else{sprite->set_position(m_player_pos);}

    AdjustSprite(sprite);
}



void BattleField::AdjustSprite(CreatureSprite3D* sprite){
    //should probably have checks
    Ref<SpriteFrames> frames = sprite->get_sprite_frames();
    StringName anim = sprite->get_animation();
    int frame = sprite->get_frame();
    
    Ref<Texture2D> tex = frames->get_frame_texture(anim, frame);
    float h = tex->get_height();
    sprite->set_offset(Vector2(0, h * 0.5f));
    // sprite->set_billboard_mode(BaseMaterial3D::BILLBOARD_ENABLED);
}