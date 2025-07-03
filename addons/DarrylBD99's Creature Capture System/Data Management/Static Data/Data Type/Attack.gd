@tool
extends CCS_StaticData_DataBase
class_name CCS_StaticData_Attack

@export var power : int = 0
@export var stamina : int = 0
@export var type : StringName
@export var stat_boost : Dictionary[StringName, int]
@export var stat_debuff : Dictionary[StringName, int]

@export var battle_vfx : PackedScene
@export var use_at_self : bool
@export var stat_effect_at_self : bool

func get_data_dictionary() -> Dictionary:
	var type_id = null
	
	var ret : Dictionary = {
		"Power" : power,
		"Stamina" : stamina,
		"Type" : {
			"keys" : "StaticData_Type",
			"data": type
		}
	}
	
	ret.merge(super())
	return ret

func get_data_export() -> Dictionary:
	var type_id = null
	
	var ret : Dictionary = {
		"Power" : power,
		"Stamina" : stamina,
		"Type" : type
	}
	
	ret.merge(super())
	return ret

func set_data_from_dictionary(dic : Dictionary) -> void:
	super(dic)
	for key in dic.keys():
		var data := dic.get(key)
		if (key == "Power"): power = data
		if (key == "Stamina"): stamina = data
		if (key == "Type"): type = data
