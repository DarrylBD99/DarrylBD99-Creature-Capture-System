#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/marker3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <godot_cpp/classes/ref.hpp>

#include <nodes/CreatureSprite3D.hpp>

namespace godot {
    class BattleField : public Node {
        GDCLASS(BattleField, Node);

        private:
            //Vector3 m_player_pos = Vector3();
            TypedArray<Vector3> m_player_pos;
            Dictionary m_player_side_occupancy;

            //Vector3 m_opponent_pos = Vector3();
            TypedArray<Vector3> m_opponent_pos;
            Dictionary m_opponent_side_occupancy;

        protected:
            static void _bind_methods();
        
        public:
            BattleField();
            virtual ~BattleField();
            void _init();

            void set_player_pos(const TypedArray<Vector3> &pos_array);
            Array get_player_pos() const;
            void add_player_pos(const Vector3 &pos);
            void clear_player_pos();

            void set_opponent_pos(const TypedArray<Vector3> &pos_array);
            Array get_opponent_pos() const;
            void add_opponent_pos(const Vector3 &pos);
            void clear_opponent_pos();

            void initPositions();

            void AddSprites(CreatureSprite3D* sprite,int format,bool opponent);
            void AdjustSprite(CreatureSprite3D* sprite);

    };
};

#endif // BATTLEFIELD_H