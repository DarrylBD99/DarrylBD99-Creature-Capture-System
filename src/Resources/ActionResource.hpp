#ifndef EVENT_RESOURCE_H
#define EVENT_RESOURCE_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <Resources/BattleCreature.hpp>
#include <Type.hpp>


namespace godot {


    // everything that the player could do is turned into an ActionResource with all the ActionType 
    // relavent data eg. m_move_id for MOVE event

    // could add more events and/or more data in the resource 

    enum class ActionType : int { 
        JACKSHIT = 0,
        FLEE     = 1,
        USE_ITEM = 2,
        SWITCH   = 3,
        MOVE     = 4,
    };


    class ActionResource : public Resource {
        GDCLASS(ActionResource, Resource);

        private:
            int m_priority = 0;
            ActionType m_event_type = ActionType::JACKSHIT;

            Ref<BattleCreature> m_actor;
            Ref<BattleCreature> m_target;


            StringName m_move_id;
            StringName m_item_id;
            int m_slot; // for switching


        protected:
            static void _bind_methods();

        public:
            ActionResource();
            virtual ~ActionResource();

            int GetPriority() const;
            void SetPriority(int value);

            ActionType GetEventType() const;
            void SetEventType(ActionType type);

            Ref<BattleCreature> GetActorId() const;
            void SetActorId(const Ref<BattleCreature> id);

            Ref<BattleCreature> GetTargetId() const;
            void SetTargetId(const Ref<BattleCreature> id);

            // for MOVE events
            StringName GetMoveId() const;
            void SetMoveId(const StringName& id);

            // for USE_ITEM
            StringName GetItemId() const;
            void SetItemId(const StringName& id);

            /// for SWITCH events
            int GetSlot() const;
            void SetSlot(int value);

    };
}


#endif