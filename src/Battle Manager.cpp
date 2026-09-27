#include "Battle Manager.hpp"

#include <iostream>
#include <algorithm>
#include <random>
#include <Resources/BattleCreature.hpp>
#include <godot_cpp/core/math.hpp>

// Initialize static member
godot::BattleField* BattleManager::s_current_battlefield = nullptr;
godot::UserInterface* BattleManager::s_current_userinterface = nullptr;

vector<godot::Ref<godot::ActionResource>> BattleManager::m_actions;

godot::Ref<godot::BattleTeam> BattleManager::m_player_team;
godot::Ref<godot::BattleTeam> BattleManager::m_opponent_team;

vector<godot::Ref<godot::BattleCreature>> BattleManager::m_active_creatures;



void BattleManager::set_player_team(const godot::Ref<godot::BattleTeam> &team) {
    m_player_team = team;

    auto members = m_player_team->get_members();

    for (int i = 0; i < members.size(); i++){
        godot::Ref<godot::BattleCreature> creature = members[i];
        creature->set_player(true); //does this
    }
}

godot::Ref<godot::BattleTeam> BattleManager::get_player_team() {
    return m_player_team;
}

vector<godot::Ref<godot::BattleCreature>> BattleManager::GetActiveCreatures() {
    return m_active_creatures;
}



// this works but i'm not sure how it would work with moves/items/abilities/field conditions

// fvna a day later: pokemon showdown uses event that are created  to signal to whatever the fuck to do
// whatever the fuck they're supposed to do. eg. SwitchIn event that actives whenever a mon enters the battle
// and checks it and uses it to activates abilities like intimidate. that being said the code is 40% spegetti 50% hardcoded
// 10% that are things only mentioned once in the file like the CriticalHit event

// showdown battle code:
// https://github.com/smogon/pokemon-showdown/blob/master/sim/battle.ts


void BattleManager::order_actions() {


    // order the events by priority, if both moves and switching/items are the same ActionResource
    // we should give them 482348834 priority in order for them to NEVER be outsped by regular moves



    // randomizes positions before sorting; making speed ties 50 50

    for (int i = m_actions.size() - 1; i > 0; i--) {
        int j = (int)(godot::UtilityFunctions::randf() * (i + 1));
        std::swap(m_actions[i], m_actions[j]);
    }

    // the actual sorting
    std::stable_sort(m_actions.begin(), m_actions.end(),
        [](const godot::Ref<godot::ActionResource> &a,
           const godot::Ref<godot::ActionResource> &b) {

            // sort by priority
            if (a->GetPriority() != b->GetPriority())
                return a->GetPriority() > b->GetPriority();

            // sort by speed
            int sa = 0, sb = 0;
            if (a->GetActorId().is_valid()) sa = a->GetActorId()->get_speed_stat();
            if (b->GetActorId().is_valid()) sb = b->GetActorId()->get_speed_stat();
            return sa > sb;
        });
    
    // i actually don't have any way to test this until its mostly finished lmfao o7
}





// plays one turn AFTER getting all the inputs 

// inputs create events (what is the input, who used it, who does it target)

void BattleManager::play_turn() {

    // TODO: simply get moves to work


    // for every event in events: do the event eg. attempt switching out or use a move.
    // then wait until its finished (done with a signal, "finished" here probably just means its animation)

    //     -- for every event reorder the events in the same priority 
    //            (in the ideal world this would only happen whenever something that changes priority/speed happens
    //            but we shouldn't bother with that rn)

}
