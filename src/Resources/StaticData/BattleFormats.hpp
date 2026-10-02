// BattleFormat.hpp
#pragma once

enum class BattleFormat : int { 
    Singles  = 1,
    Dobules  = 2,
    Triples  = 3,
    TwoVOne  = 4, // you + ally vs enemy (eg. route 8 with jake)
    TwoVTwo  = 5, // you + ally vs two enemies. none in PBB but PKMN unbound has a few examples
};