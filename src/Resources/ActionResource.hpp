#ifndef EVENT_RESOURCE_H
#define EVENT_RESOURCE_H

#include <unordered_map>

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <Resources/BattleCreature.hpp>
#include <Resources/StaticData/Attacks.hpp>
#include <Type.hpp>


namespace godot {


    // everything that the player could do is turned into an ActionResource with all the ActionType 
    // relavent data eg. m_move_id for MOVE event

    // could add more events and/or more data in the resource 

    enum class ActionType : int { 
        JACKSHIT  = -1,
        USE_ITEM  = 3,
        SWITCH    = 2,
        FLEE      = 1,
        MOVE      = 0,
    };

    // phases: items first, then switching, then fleeing, then moves.
    // this is simply for ordering the moves, there's nothing preventing eg. a move to go before items
    // if it was given a high enougn priority


    class ActionResource : public Resource {
        GDCLASS(ActionResource, Resource);

        private:
            ActionType m_action_type = ActionType::JACKSHIT;

            Ref<BattleCreature> m_actor;
            Ref<BattleCreature> m_target;


            Ref<AttackResource> m_move_id; 
            //StringName m_item_id;
            int m_target_slot; // for switching, items (sometimes) AND move target (not sure how it'd work with multi target stuff)


        protected:
            static void _bind_methods();

        public:
            ActionResource();
            virtual ~ActionResource();

            ActionType GetActionType() const;
            void SetActionType(ActionType type);

            Ref<BattleCreature> GetActor() const;
            void SetActor(const Ref<BattleCreature> id);

            Ref<BattleCreature> GetTarget() const;
            void SetTarget(const Ref<BattleCreature> id);

            // for MOVE events
            Ref<AttackResource> GetMoveId() const;
            void SetMoveId(const Ref<AttackResource> id);

            

            int GetPriority() const;

            // // for USE_ITEM
            // StringName GetItemId() const;
            // void SetItemId(const StringName& id);

            /// for SWITCH events
            int GetSlot() const;
            void SetSlot(int value);

    };
}


#endif