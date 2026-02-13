extends Node

const exclaim_particle_scene : PackedScene = preload("uid://lrg0lnca0og3")

func _ready() -> void:
	CCS_BattleManager.additional_functions["Game_Defeated"] = Game_DefeatFunction.new()
	CCS_BattleManager.additional_functions["Game_BoxFunction"] = Game_BoxFunction.new()
