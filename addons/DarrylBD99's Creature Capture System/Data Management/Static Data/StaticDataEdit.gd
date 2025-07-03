@tool
extends Node
class_name CCS_StaticDataEdit

signal imported_data
signal exported_data

@onready var static_data : CCS_StaticData = CCS_StaticData.new()

func get_keys(key_type : String) -> Array:
	match key_type:
		"StaticData_Type":
			return static_data.types.keys()
	return []

func import_compiled_data(path : String) -> void:
	var data : CCS_StaticData = _read_file(path)
	if data != null:
		static_data = data

func export_compiled_data(path : String) -> void:
	_write_file(static_data, path)

func add_creature(id : StringName):
	if static_data.creatures.has(id):
		push_error("Error: Creature ID {} is already defined".format([id]))
		return
	
	static_data.creatures[id] = CCS_StaticData_Creature.new()

func add_type(id : StringName):
	if static_data.types.has(id):
		push_error("Error: Type ID {} is already defined".format([id]))
		return
	
	static_data.types[id] = CCS_StaticData_Type.new()

func add_attack(id : StringName):
	if static_data.types.has(id):
		push_error("Error: Attack ID {} is already defined".format([id]))
		return
	
	static_data.attacks[id] = CCS_StaticData_Attack.new()

func remove_creature(id : StringName):
	if !static_data.creatures.has(id):
		push_error("Error: Creature ID {} does not exist".format([id]))
		return
	
	static_data.creatures.erase(id)

func remove_type(id : StringName):
	if !static_data.types.has(id):
		push_error("Error: Type ID {} does not exist".format([id]))
		return
	
	static_data.types.erase(id)

func remove_attack(id : StringName):
	if !static_data.attacks.has(id):
		push_error("Error: Attack ID {} does not exist".format([id]))
		return
	
	static_data.attacks.erase(id)

func get_all_creature_id() -> Array:
	if static_data.creatures.size() > 0:
		var ret : Array = static_data.creatures.keys()
		return ret
	return []

func get_all_type_id() -> Array:
	if static_data.types.size() > 0:
		var ret : Array = static_data.types.keys()
		return ret
	return []

func get_all_attack_id() -> Array:
	if static_data.attacks.size() > 0:
		var ret : Array = static_data.attacks.keys()
		return ret
	return []

func get_creature_data(key : String) -> CCS_StaticData_Creature:
	return static_data.creatures[key]

func get_type_data(key : String) -> CCS_StaticData_Type:
	return static_data.types[key]

func get_attack_data(key : String) -> CCS_StaticData_Attack:
	return static_data.attacks[key]

#region Calculations
func set_calc_variable(data : Dictionary):
	for var_name : String in data:
		static_data.calc_variables[var_name] = data[var_name]

func has_calc_variable(var_name : String):
	return static_data.calc_variables.has(var_name)

func get_all_calc_variables() -> Dictionary:
	return static_data.calc_variables
#endregion

func _write_file(data : CCS_StaticData, path : String) -> void:
	var extension : StringName = path.get_extension() # check file extension
	
	if extension == &"res" || extension == &"tres":
		#region resource
		var error : Error = ResourceSaver.save(data, path, ResourceSaver.FLAG_COMPRESS)
		if error != OK:
			push_warning("Error: Unable to write resource. Code: {}".format([error]))
			return
		
		print("Export successful!")
		exported_data.emit()
		#endregion
	#elif extension == &"dat":
		##region binary serialize
		#var data_dictionary : Dictionary = {
			#"types" : _dictionary_to_array(data.types),
			#"attacks" : _dictionary_to_array(data.attacks),
			#"creatures" : _dictionary_to_array(data.creatures),
			#"extra_resources" : _dictionary_to_array(data.creatures)
		#}
		#
		#var data_file : FileAccess = FileAccess.open(path, FileAccess.WRITE)
		#data_file.store_var(data_dictionary)
		#data_file.close()
		#print("Export successful!")
		#exported_data.emit()
		##endregion
	else:
		push_warning("Error: Unable to write file")

func _read_file(path : String) -> CCS_StaticData:
	var extension : StringName = path.get_extension() # check file extension
	var data : CCS_StaticData = CCS_StaticData.new()
	
	if extension == &"res" || extension == &"tres":
		#region resource
		var new_data : CCS_StaticData = ResourceLoader.load(path)
		
		if new_data:
			print("Import Successful")
			return new_data.duplicate(true)
		imported_data.emit()
		#endregion
	#elif extension == &"dat":
		##region binary serialize
		#var data_file : FileAccess = FileAccess.open(path, FileAccess.READ)
		#var data_dictionary : Dictionary = data_file.get_var()
		#data_file.close()
		#
		##region create static data resources
		#if data_dictionary.has("types"):
			#for type in data_dictionary["types"].keys():
				#data.types[type] = CCS_StaticData_Type.new()
		#
		#if data_dictionary.has("attacks"):
			#for attack in data_dictionary["attacks"].keys():
				#data.attacks[attack] = CCS_StaticData_Attack.new()
			#
		#if data_dictionary.has("creatures"):
			#for creature in data_dictionary["creatures"].keys():
				#data.creatures[creature] = CCS_StaticData_Creature.new()
		##endregion
		#
		##region Multi-Thread
		#var thread_1 : Thread = Thread.new()
		#var thread_2 : Thread = Thread.new()
		#var thread_3 : Thread = Thread.new()
		#var thread_4 : Thread = Thread.new()
		##endregion
		#
		##region add data to static data
		#thread_1.start( func():
			#if data_dictionary.has("types"):
				#for type : String in data.types:
					#data.types[type].set_data_from_dictionary(data_dictionary["types"][type])
		#)
		#thread_2.start( func():
			#if data_dictionary.has("attacks"):
				#for attack : String in data.attacks:
					#data.attacks[attack].set_data_from_dictionary(data_dictionary["attacks"][attack])
		#)
		#thread_4.start( func():
			#if data_dictionary.has("creatures"):
				#for creature : String in data.creatures:
					#data.creatures[creature].set_data_from_dictionary(data_dictionary["creatures"][creature])
		#)
		##endregion
		#
		##region Multi-Thread Wait
		#thread_1.wait_to_finish()
		#thread_2.wait_to_finish()
		##thread_3.wait_to_finish()
		#thread_4.wait_to_finish()
		##endregion
		#
		#imported_data.emit()
		#print("Import Successful")
		#return data
		##endregion
	
	push_warning("Error: Unable to read file")
	return null

func _dictionary_to_array(data_dictionary : Dictionary) -> Dictionary:
	var ret : Dictionary
	
	for id in data_dictionary:
		if data_dictionary[id] is CCS_StaticData_DataBase:
			var data : CCS_StaticData_DataBase = data_dictionary[id]
			ret[id] = data.get_data_export()
	
	return ret

#region addon support
func add_extra_resource(id : StringName, res : CCS_AdditionalResource) -> void:
	static_data.extra_resources[id] = res

func get_extra_resource(id : StringName) -> CCS_AdditionalResource:
	if static_data.extra_resources.has(id):
		return static_data.extra_resources[id]
	
	push_warning("Error: Resource {} not found".format([id]))
	return null
#endregion
