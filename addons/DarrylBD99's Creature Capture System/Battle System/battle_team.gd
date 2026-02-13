extends Resource
class_name CCS_BattleTeam

@export var trainer_name : String
@export var trainer_variant : String = "Trainer"
@export var creature_list : Array[CCS_Creature]

@export var defeat_text : Array[String] = ["Aw man..."]
@export var Money_amount : int = 10

var currently_out_creatures : Array[CCS_Creature]
var sent_out_creatures : Array[CCS_Creature]

func send_out_creature(creature : CCS_Creature, idx : int) -> void:
	if not creature in creature_list:
		push_error("Error: Creature {0} not found".format([creature.get_creature_name()]))
		return

	if is_currently_out(creature):
		push_error("Error: Creature {0} already in battlefield".format([creature.get_creature_name()]))
		return
	
	if currently_out_creatures.size() <= idx:
		currently_out_creatures.resize(idx + 1)
	
	var creature_from : CCS_Creature = currently_out_creatures.get(idx) 
	currently_out_creatures.set(idx, creature)
	
	creature_from.reset_creature()
	
	if not creature_from in sent_out_creatures:
		sent_out_creatures.append(creature_from)
		sent_out_creatures.sort_custom(_sort_by_party_index)

func swap_creature_order(creature_1 : CCS_Creature, creature_2 : CCS_Creature) -> void:
	if not creature_list.has(creature_1):
		push_error("Error: Creature {0} not in team".format([creature_1.get_creature_name()]))
		return
	if not creature_list.has(creature_2):
		push_error("Error: Creature {0} not in team".format([creature_2.get_creature_name()]))
		return
	
	var idx_1 : int = get_creature_idx(creature_1)
	var idx_2 : int = get_creature_idx(creature_2)
	
	creature_list.set(idx_1, creature_2)
	creature_list.set(idx_2, creature_1)

func _sort_by_party_index(a : CCS_Creature, b : CCS_Creature) -> bool:
	if creature_list.find(a) < creature_list.find(b):
		return true
	return false

func get_creature_with_species(species_id : StringName) -> CCS_Creature:
	for creature : CCS_Creature in creature_list:
		if creature.id == species_id:
			return creature
	
	return null

func get_current_creature(idx : int) -> CCS_Creature:
	if idx < 0 or idx >= currently_out_creatures.size():
		push_error("Error: Invalid index {0}".format([idx]))
		return null
	
	if currently_out_creatures.size() >= 0:
		return currently_out_creatures.get(idx)

	return creature_list.get(0)

func get_creature(idx : int) -> CCS_Creature:
	if idx >= 0 and idx < creature_list.size():
		return creature_list.get(idx)

	return null

func has_creature(creature : CCS_Creature) -> bool:
	return creature_list.has(creature)
	
func get_creature_idx(creature : CCS_Creature) -> int:
	return creature_list.find(creature)

func reset_team_to_default() -> void:
	for creature : CCS_Creature in currently_out_creatures:
		if creature != null:
			creature.reset_creature()
	
	currently_out_creatures.clear()
	sent_out_creatures.clear()

func get_trainer_name() -> String:
	return "{0} {1}".format([trainer_variant, trainer_name])

func is_all_dead() -> bool:
	for creature : CCS_Creature in creature_list:
		if not creature.is_dead():
			return false
	
	return true

func heal_team() -> void:
	for creature : CCS_Creature in creature_list:
		creature.reset_health()

func is_currently_out(creature : CCS_Creature) -> bool:
	return creature in currently_out_creatures
