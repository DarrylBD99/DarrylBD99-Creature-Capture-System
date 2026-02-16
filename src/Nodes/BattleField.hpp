#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include <godot_cpp/classes/ref.hpp>

#include <nodes/CreatureSprite3D.hpp>

namespace godot {
    class BattleField : public Node {
        GDCLASS(BattleField, Node);

        private:
            Vector3 m_player_pos = Vector3();
            Vector3 m_opponent_pos = Vector3();

        protected:
            static void _bind_methods();
        
        public:
            BattleField();
            virtual ~BattleField();
            void _init();

            Vector3 GetPlayerPos() const;
            void SetPlayerPos(const Vector3& pos);
            Vector3 GetOpponentPos() const;
            void SetOpponentPos(const Vector3& pos);

            void AddOpponentSprite(CreatureSprite3D* sprite);
            void AdjustSprite(CreatureSprite3D* sprite);
    };
};

#endif // BATTLEFIELD_H