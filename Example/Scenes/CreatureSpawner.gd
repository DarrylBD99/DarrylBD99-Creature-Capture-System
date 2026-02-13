extends Area3D
class_name CCS_Example_CreatureSpawner

@export var battle_field : CCS_BattleField
@export var species_list : Dictionary[StringName, int]
@export_range(0, 1) var chance : float = 0.01
@export var can_summon_ef : bool = false
