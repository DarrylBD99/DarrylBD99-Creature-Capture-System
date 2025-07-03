@tool
extends CCS_StaticData_DataBase
class_name CCS_StaticData_Creature

@export var index : int
@export var types : Array[StringName]
@export var creature_icon : Texture2D = CanvasTexture.new()

@export var sound : AudioStream
@export var power : int = randi_range(1, 20)
@export var defense : int = randi_range(1, 20)
@export var speed : int = randi_range(1, 20)
@export var health_point : int = randi_range(1, 20)
@export var attack_pool : Dictionary[StringName, int] #Move ID, Level
@export var catch_rate : float = 0.5

@export var extra_data : Dictionary[String, Variant]

func _init():
	array_keys = ["Types"]

func get_data_dictionary() -> Dictionary:
	var ret : Dictionary = {
		"Index" : index,
		"Types" : {
			"keys" : "StaticData_Type",
			"data": types
		}
	}
	ret.merge(super())
	return ret

func get_data_export() -> Dictionary:
	var ret : Dictionary = {
		"Index" : index,
		"Types" : {
			"method" : "add",
			"data" : types
		}
	}
	ret.merge(super())
	return ret

func set_data_from_dictionary(dic : Dictionary) -> void:
	if (dic.has("Index")):
		index = dic.get("Index")
		dic.erase("Index")
	
	super(dic)

func _append_data_array(key, data) -> void:
	match key:
		"Types":
			data as StringName
			if types.has(data):
				push_warning("Error: Type ID {} exists in resistance".format([data]))
				return
			types.append(data)
			return

func _update_data_array(key, data_old, data_new) -> void:
	match key:
		"Types":
			data_old and data_new as StringName
			if types.has(data_new):
				push_warning("Error: Type ID {} exists in resistance".format([data_new]))
				return
			var idx : int = types.find(data_old)
			types[idx] = data_new
			return

func _remove_data_array(key, data) -> void:
	match key:
		"Types":
			data as StringName
			var idx : int = types.find(data)
			if (idx >= 0): types.remove_at(idx)
			return
