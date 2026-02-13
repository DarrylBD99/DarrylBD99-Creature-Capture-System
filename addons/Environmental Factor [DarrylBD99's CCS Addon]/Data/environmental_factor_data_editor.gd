@tool
extends Node
class_name CCS_EF_DataEdit

var ef_data : CCS_EF_Data:
	set(val):
		if static_data:
			static_data.add_extra_resource("EnvironmentalFactor", val)
	get():
		if static_data:
			return static_data.get_extra_resource("EnvironmentalFactor")
		return null

var static_data : CCS_StaticDataEdit
var type_ids : Array[StringName]

func _ready() -> void:
	ef_data = CCS_EF_Data.new()

func get_keys(key_type : String) -> Array:
	match key_type:
		"StaticData_Type":
			return type_ids
	return []

func import_compiled_data(path : String) -> void:
	static_data.import_compiled_data(path)

func export_compiled_data(path : String) -> void:
	static_data.export_compiled_data(path)

func add_terrain(id : StringName):
	if ef_data.terrains.has(id):
		push_error("Error: Terrain ID {} is already defined".format([id]))
		return
	
	ef_data.terrains[id] = CCS_EF_TypeData.new()

func add_type_factor(id : StringName):
	if ef_data.type_factors.has(id):
		push_error("Error: Type ID {} is already defined".format([id]))
		return
	
	ef_data.type_factors[id] = CCS_EF_TypeData.new()
	ef_data.type_factors[id].name = "{0} Type Field".format([id])

func remove_terrain(id : StringName):
	if !ef_data.terrains.has(id):
		push_error("Error: Terrain ID {} does not exist".format([id]))
		return
	
	ef_data.terrains.erase(id)

func remove_type_factor(id : StringName):
	if !ef_data.type_factors.has(id):
		push_error("Error: Type ID {} does not exist".format([id]))
		return
	
	ef_data.type_factors.erase(id)

func get_all_terain_id() -> Array:
	if ef_data.terrains.size() > 0:
		var ret : Array = ef_data.terrains.keys()
		return ret
	return []

func get_terrain_data(key : String) -> CCS_EF_TypeData:
	return ef_data.terrains[key]

func get_type_factor_data(key : String) -> CCS_EF_TypeData:
	return ef_data.type_factors[key]

func reset_type_ids():
	if static_data:
		var type_ids_new  : Array[StringName] = static_data.get_keys("StaticData_Type")
		for type_id : StringName in type_ids:
			var idx : int = type_ids_new.find(type_id)
			if idx >= 0: type_ids_new.remove_at(idx)
			else: remove_type_factor(type_id)
		
		for type_id_new : StringName in type_ids_new:
			if !type_ids.has(type_id_new): add_type_factor(type_id_new)
		
		type_ids = static_data.get_keys("StaticData_Type")
