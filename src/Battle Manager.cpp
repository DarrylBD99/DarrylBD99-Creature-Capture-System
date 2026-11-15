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
godot::Ref<godot::BattleTeam> BattleManager::m_ally_team;

godot::Ref<godot::BattleTeam> BattleManager::m_opponent_team;
godot::Ref<godot::BattleTeam> BattleManager::m_opponent_2_team;




void BattleManager::set_player_team(const godot::Ref<godot::BattleTeam> &team) {
    m_player_team = team;

    auto members = m_player_team->get_members();

    for (int i = 0; i < members.size(); i++){
        godot::Ref<godot::BattleCreature> creature = members[i];
        creature->set_player(true); // sets the creatures as controllable by the player
    }
}

godot::Ref<godot::BattleTeam> BattleManager::get_player_team() {
    return m_player_team;
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

    // for things like trick room we would basiclly need to have an if statement that goes like 
    // if trickroom: > else <
    std::stable_sort(m_actions.begin(), m_actions.end(),
        [](const godot::Ref<godot::ActionResource>& a,
           const godot::Ref<godot::ActionResource>& b) {

            // sort by priority
            int pa = a->GetPriority();
            int pb = b->GetPriority();
            if (pa != pb) return pa > pb;

            // sort by speed
            int sa = a->GetActor().is_valid() ? a->GetActor()->get_speed_stat() : 0;
            int sb = b->GetActor().is_valid() ? b->GetActor()->get_speed_stat() : 0;
            return sa > sb;
        });

    // 
    
    // i actually don't have any way to test this until its mostly finished lmfao o7
}





// plays one turn AFTER getting all the inputs 

// inputs create actions (what is the input, who used it, who does it target)

void BattleManager::play_turn() {

    // TODO: simply get moves to work


    // for every event in events: do the event eg. attempt switching out or use a move.
    // then wait until its finished (done with a signal, "finished" here probably just means its animation)

    //     -- for every event reorder the events in the same priority 
    //            (in the ideal world this would only happen whenever something that changes priority/speed happens
    //            but we shouldn't bother with that rn)

}








void BattleManager::Battle::occupy_slots(BattleFormat format)
{
    BattleSide* player_side = battle_sides[0];
    BattleSide* opponent_side = battle_sides[1];

    if (opponent_side == nullptr || player_side == nullptr){
        godot::UtilityFunctions::push_error("A battle side is null, go figure out which lmfao");
        return;
    }   
    //ir3ngoiugnr3iugnoiu3lngkjn

    switch (format)
    {
        case BattleFormat::Singles:
        {
            BattleManager::occupy_team_slots(player_side, BattleManager::m_player_team, 1);

            BattleManager::occupy_team_slots(opponent_side, BattleManager::m_opponent_team, 1);

        }

        case BattleFormat::Dobules:
        {
            BattleManager::occupy_team_slots(player_side, BattleManager::m_player_team, 2);

            BattleManager::occupy_team_slots(opponent_side, BattleManager::m_opponent_team, 2);

        }

        case BattleFormat::Triples:
        {
            BattleManager::occupy_team_slots(player_side, BattleManager::m_player_team, 3);

            BattleManager::occupy_team_slots(opponent_side, BattleManager::m_opponent_team, 3);

        }

        case BattleFormat::TwoVOne: //lets ignore OneVTwo for now
        {
            BattleManager::occupy_team_slots(player_side, BattleManager::m_player_team, 1);

            BattleManager::occupy_team_slots(player_side, BattleManager::m_ally_team, 1);

            BattleManager::occupy_team_slots(opponent_side, BattleManager::m_opponent_team, 1);

        }

        case BattleFormat::TwoVTwo:
        {
            BattleManager::occupy_team_slots(player_side, BattleManager::m_player_team, 1);

            BattleManager::occupy_team_slots(player_side, BattleManager::m_ally_team, 1);

            BattleManager::occupy_team_slots(opponent_side, BattleManager::m_opponent_team, 1);

            BattleManager::occupy_team_slots(opponent_side, BattleManager::m_opponent_2_team, 1);

        }
    }
}



void BattleManager::occupy_team_slots(BattleManager::BattleSide* side,const godot::Ref<godot::BattleTeam>& team,int amount){

    if (team.is_null()){
        godot::UtilityFunctions::push_error("Team is null. did you set the correct format?");
        return;
    }

    const auto& members = team->get_members();

    if (members.size() == 0){
        godot::UtilityFunctions::push_error("a team has no members!");
        return;
    }

    for (int i = 0; i < amount && i < members.size(); ++i)
    {
        BattleManager::CreatureSlot* slot = new BattleManager::CreatureSlot;

        slot->creature = members[i];

        side->creature_slots.push_back(slot);
        side->active_creatures.push_back(slot->creature.ptr());
    }
}