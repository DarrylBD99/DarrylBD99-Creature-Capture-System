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
            TypedArray<Marker3D> m_player_pos;

            //Vector3 m_opponent_pos = Vector3();
            TypedArray<Marker3D> m_opponent_pos;

        protected:
            static void _bind_methods();
        
        public:
            BattleField();
            virtual ~BattleField();
            void _init();

            void set_player_pos(const Array &pos);
            Array get_player_pos() const;
            void add_player_pos(const Marker3D *pos);
            void clear_player_pos();

            void set_opponent_pos(const Array &pos);
            Array get_opponent_pos() const;
            void add_opponent_pos(const Marker3D *pos);
            void clear_opponent_pos();

            void AddSprites(CreatureSprite3D* sprite,bool opponent);
            void AdjustSprite(CreatureSprite3D* sprite);
    };
};

#endif // BATTLEFIELD_H