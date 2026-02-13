@tool
extends CCS_StaticData_DataBase
class_name CCS_EF_TypeData

@export var base_boost_multiplier : float = 1.5
@export var boosted_types : Array[StringName]

@export var base_defect_multiplier : float = 0.7
@export var defective_types : Array[StringName]

@export var arena_uid : CCS_UID

func _init():
	array_keys = ["BoostTypes", "DefectTypes"]

func get_data_dictionary() -> Dictionary:
	var ret : Dictionary = {
		"BoostMult" : base_boost_multiplier,
		"BoostTypes" : {
			"keys" : "StaticData_Type",
			"data": boosted_types
		},
		"DefectMult" : base_defect_multiplier,
		"DefectTypes" : {
			"keys" : "StaticData_Type",
			"data": defective_types
		}
	}
	ret.merge(super())
	return ret


func get_data_export() -> Dictionary:
	var ret : Dictionary = {
		"BoostMult" : base_boost_multiplier,
		"BoostTypes" : {
			"method" : "add",
			"data": boosted_types
		},
		"DefectMult" : base_defect_multiplier,
		"DefectTypes" : {
			"method" : "add",
			"data": defective_types
		}
	}
	ret.merge(super())
	return ret

func set_data_from_dictionary(dic : Dictionary) -> void:
	if (dic.has("BoostMult")):
		base_boost_multiplier = dic.get("BoostMult")
		dic.erase("BoostMult")
	
	if (dic.has("DefectMult")):
		base_defect_multiplier = dic.get("DefectMult")
		dic.erase("DefectMult")
	
	super(dic)

func _append_data_array(key, data) -> void:
	data as StringName
	match key:
		"BoostTypes":
			if boosted_types.has(data):
				push_warning("Error: Type ID {} exists in boosted types".format([data]))
				return
			boosted_types.append(data)
			return
		"DefectTypes":
			if defective_types.has(data):
				push_warning("Error: Type ID {} exists in defective types".format([data]))
				return
			defective_types.append(data)
			return

func _update_data_array(key, data_old, data_new) -> void:
	data_old and data_new as StringName
	match key:
		"BoostTypes":
			if boosted_types.has(data_new):
				push_warning("Error: Type ID {} exists in boosted types".format([data_new]))
				return
			var idx : int = boosted_types.find(data_old)
			boosted_types[idx] = data_new
			return
		"DefectTypes":
			if defective_types.has(data_new):
				push_warning("Error: Type ID {} exists in defective types".format([data_new]))
				return
			var idx : int = defective_types.find(data_old)
			defective_types[idx] = data_new
			return

func _remove_data_array(key, data) -> void:
	data as StringName
	match key:
		"BoostTypes":
			var idx : int = boosted_types.find(data)
			if (idx >= 0): boosted_types.remove_at(idx)
			return
		"DefectTypes":
			var idx : int = defective_types.find(data)
			if (idx >= 0): defective_types.remove_at(idx)
			return
