@tool
extends Resource
class_name CCS_StaticData_DataBase

@export var name : String

var id : StringName

var array_keys : Array[String] = []

func get_data_dictionary() -> Dictionary:
	return {
		"Name" : name
	}

func get_data_export() -> Dictionary:
	return get_data_dictionary()

func set_data_from_dictionary(dic : Dictionary) -> void:
	for key in dic.keys():
		if (key == "Name"): 
			name = dic.get(key)
		
		if (array_keys.size() > 0 and array_keys.has(key)):
			var array_data : Dictionary = dic.get(key)
			var data := array_data.get("data")
			if (array_data.get("method") == "add"):
				if data is Array:
					for id in data:
						_append_data_array(key, id)
				else:
					_append_data_array(key, data)
			
			elif (array_data.get("method") == "update"):
				if data is Dictionary:
					for id in data.keys():
						_update_data_array(key, id, data.get(id))
				else:
					push_warning("Error: Array update prompt is invalid")
			
			elif (array_data.get("method") == "remove"):
				if data is Array:
					for id in data:
						_remove_data_array(key, id)
				else:
					_remove_data_array(key, data)

func _append_data_array(key, data) -> void:
	pass

func _update_data_array(key, data_old, data_new) -> void:
	pass

func _remove_data_array(key, data) -> void:
	pass
