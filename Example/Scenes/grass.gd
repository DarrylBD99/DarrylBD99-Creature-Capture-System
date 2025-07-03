extends Area3D
class_name Grass

@export var species_list : Array[StringName]
@export var species_level : Dictionary[StringName, Array]
@export_range(0, 1) var chance : float = 0.01
@export var can_summon_ef : bool = false
@export var gridmap : GridMap
@export var battle_format : int = 2

func _ready() -> void:
	if gridmap != null:
		#var cell_pos : Array[Vector3i] = gridmap.get_used_cells()
		pass
