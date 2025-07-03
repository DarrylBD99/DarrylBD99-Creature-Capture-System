extends Resource
class_name CCS_PlayerData

static var player_data : CCS_PlayerData = new()
static var current_slot : int = -1

@export var items : Dictionary[StringName, int]
@export var team : CCS_BattleTeam = CCS_BattleTeam.new()
@export var variables : Dictionary[StringName, Variant]
@export var player_pos : Vector3
@export var money : int = 100

const save_folder : String = "user://saves/"
const save_path : String = "player_data_{0}.res"

func _init() -> void:
	pass

static func save_game() -> bool:
	if not DirAccess.dir_exists_absolute(save_folder):
		DirAccess.make_dir_absolute(save_folder)
	
	var path : String = save_folder + save_path.format([current_slot])
	var save_status : Error = ResourceSaver.save(player_data.duplicate(true), path)
	return (save_status == Error.OK)

static func load_game(slot : int) -> void:
	var path : String = save_folder + save_path.format([slot])
	if not ResourceLoader.exists(path):
		return
	current_slot = slot
	player_data = ResourceLoader.load(path).duplicate(true)
	CCS_BattleUIManager.update_creature_list()
	CCS_BattleUIManager.update_item_list()
	CCS_BattleManager.save_loaded.emit()

static func get_all_saves() -> Array[CCS_PlayerData]:
	var path : String
	var save_files : Array[CCS_PlayerData]
	
	while true:
		path = save_folder + save_path.format([save_files.size()])
		if not ResourceLoader.exists(path):
			break
			
		save_files.append(ResourceLoader.load(path))
		continue
	
	CCS_BattleManager.all_saves_found.emit()
	return save_files

static func new_game() -> void:
	var counter : int = 0
	var path : String
	
	while true:
		path = save_folder + save_path.format([counter])
		if ResourceLoader.exists(path):
			counter += 1
			continue
		current_slot = counter
		player_data = new()
		CCS_BattleManager.save_created.emit()
		return

static func get_team() -> CCS_BattleTeam:
	return player_data.team

static func set_trainer_name(trainer_name : String) -> void:
	get_team().trainer_name = trainer_name

static func get_variable(variable_name : StringName) -> Variant:
	if player_data.variables.has(variable_name):
		return player_data.variables.get(variable_name)
	
	return null

static func set_variable(variable_name : StringName, data : Variant) -> void:
	if data == null:
		player_data.variables.erase(variable_name)
		return
	
	player_data.variables[variable_name] = data

static func give_item(id : StringName, amount : int = 1) -> void:
	if player_data.items.has(id):
		player_data.items[id] += amount
	else:
		player_data.items[id] = amount
	
	CCS_BattleUIManager.update_item_list()

static func has_item(id : StringName) -> bool:
	return player_data.items.has(id)

static func get_item_quantity(id : StringName) -> int:
	if has_item(id):
		return player_data.items.get(id)
	
	return 0

static func get_item_list() -> Dictionary[StringName, int]:
	return player_data.items

static func throw_item(id : StringName, amount : int = 1) -> void:
	if can_use_item(id, amount):
		player_data.items[id] -= amount
		if player_data.items.get(id) <= 0: player_data.items.erase(id)
		
		CCS_BattleUIManager.update_item_list()

static func can_use_item(id : StringName, amount : int = 1) -> bool:
	if not player_data.items.has(id):
		return false
	
	if player_data.items.get(id) < amount:
		return false
	
	return true

static func give_creature(species_id : String, level : int = 1) -> void:
	give_creature_defined(CCS_Creature.create_creature(species_id, level))
	CCS_BattleUIManager.update_creature_list()

static func remove_creature(creature : CCS_Creature) -> void:
	get_team().creature_list.erase(creature)
	CCS_BattleUIManager.update_creature_list()

static func give_creature_defined(creature : CCS_Creature) -> void:
	get_team().creature_list.append(creature)
	CCS_BattleUIManager.update_creature_list()

static func swap_creature_order(creature_1 : CCS_Creature, creature_2 : CCS_Creature) -> void:
	get_team().swap_creature_order(creature_1, creature_2)
	CCS_BattleUIManager.update_creature_list()

static func get_money() -> int:
	return player_data.money

static func add_money(money_in : int) -> void:
	player_data.money += money_in

static func subtract_money(money_out : int) -> void:
	player_data.money -= money_out
