@tool
extends CCS_StaticData_DataBase
class_name CCS_StaticData_Type

@export var resistance : Array[StringName]
@export var weakness : Array[StringName]
@export var immunity : Array[StringName]

func _init():
	array_keys = ["Resistance", "Weakness", "Immunity"]

func get_data_dictionary() -> Dictionary:
	var ret : Dictionary = {
		"Resistance" : {
			"keys" : "StaticData_Type",
			"data": resistance
		},
		"Weakness" : {
			"keys" : "StaticData_Type",
			"data": weakness
		},
		"Immunity" : {
			"keys" : "StaticData_Type",
			"data": immunity
		}
	}
	
	ret.merge(super())
	return ret

func get_data_export() -> Dictionary:
	var ret : Dictionary = {
		"Resistance" : {
			"method" : "add",
			"data" : resistance
		},
		"Weakness" : {
			"method" : "add",
			"data" : weakness
		},
		"Immunity" : {
			"method" : "add",
			"data" : immunity
		}
	}
	
	ret.merge(super())
	return ret

func _append_data_array(key, data) -> void:
	match key:
		"Resistance":
			if resistance.has(data):
				push_warning("Error: Type ID {} exists in resistance".format([data]))
				return
			resistance.append(data)
			return
		"Weakness":
			if weakness.has(data):
				push_warning("Error: Type ID {} exists in weakness".format([data]))
				return
			weakness.append(data)
			return
		"Immunity":
			if immunity.has(data):
				push_warning("Error: Type ID {} exists in immunity".format([data]))
				return
			immunity.append(data)
			return

func _update_data_array(key, data_old, data_new) -> void:
	match key:
		"Resistance":
			if resistance.has(data_new):
				push_warning("Error: Type ID {} exists in resistance".format([data_new]))
				return
			var idx : int = resistance.find(data_old)
			resistance[idx] = data_new
			return
		"Weakness":
			if weakness.has(data_new):
				push_warning("Error: Type ID {} exists in weakness".format([data_new]))
				return
			var idx : int = weakness.find(data_old)
			weakness[idx] = data_new
			return
		"Immunity":
			if immunity.has(data_new):
				push_warning("Error: Type ID {} exists in immunity".format([data_new]))
				return
			var idx : int = immunity.find(data_old)
			immunity[idx] = data_new
			return

func _remove_data_array(key, data) -> void:
	match key:
		"Resistance":
			var idx : int = resistance.find(data)
			if (idx >= 0): resistance.remove_at(idx)
			return
		"Weakness":
			var idx : int = weakness.find(data)
			if (idx >= 0): weakness.remove_at(idx)
			return
		"Immunity":
			var idx : int = immunity.find(data)
			if (idx >= 0): immunity.remove_at(idx)
			return
