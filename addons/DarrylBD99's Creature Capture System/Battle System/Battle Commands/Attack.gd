extends CCS_BattleCommandBase
class_name CCS_BattleCommand_Attack

var trainer_name : String
var user : CCS_Creature
var target : CCS_Creature
var attack : CCS_StaticData_Attack
var attack_priority : int = 0
var dialogue_format : Dictionary

const missed_text : Array[String] = ["{ally}'s attack missed."]
const move_use_texts : Array[String] = ["{trainer}{ally} used {attack}!"]
const critical_hit_text : Array[String] = ["A Critial Hit!"]
const resistant_text : Array[String] = ["It's not effective."]
const weakness_text : Array[String] = ["It's really effective."]

const cant_decrease_stat : Array[String] = ["Can't decrease stat any further..."]
const cant_increase_stat : Array[String] = ["Can't increase stat any further..."]

func _init(trainer_name : String, user : CCS_Creature, target : CCS_Creature, attack_idx : int, attack_priority : int = 0) -> void:
	
	self.user = user
	self.target = target
	self.attack_priority = attack_priority
	
	if CCS_PlayerData.get_team().has_creature(user):
		self.trainer_name = trainer_name + "'s "
	elif CCS_BattleManager.is_wild:
		trainer_name = "Wild "
	elif not CCS_BattleManager.is_boss:
		self.trainer_name = trainer_name + "'s "
	
	type = "Attack"
	attack = CCS_BattleManager.static_data.attacks.get(user.attack_pool.get(attack_idx))

func _creature_on_battlefield(creature : CCS_Creature) -> bool:
	return creature in CCS_BattleManager.ally_creatures or creature in CCS_BattleManager.opp_creatures

func execute() -> void:
	if not _creature_on_battlefield(user):
		return
	
	if user == null or user.is_dead():
		return
	
	var dialogue_format : Dictionary = {
		"trainer" : trainer_name,
		"ally" : user.get_creature_name(),
		"target" : "NULL",
		"attack" : attack.name
	}
	
	if target:
		dialogue_format["target"] = target.get_creature_name()
	
	await CCS_BattleUIManager.create_dialogue(move_use_texts, dialogue_format)
	
	if not _creature_on_battlefield(target) or target == null or target.is_dead():
		await CCS_BattleUIManager.create_dialogue(missed_text, dialogue_format)
		return
	
	var stat_affect_creature : CCS_Creature = user if attack.stat_effect_at_self else target
	var can_stat_change : bool = false
	
	if attack.power <= 0:
		if not _can_decrease_stat(stat_affect_creature):
			await CCS_BattleUIManager.create_dialogue(cant_decrease_stat)
			return
		if not _can_increase_stat(stat_affect_creature):
			await CCS_BattleUIManager.create_dialogue(cant_increase_stat)
			return
	
	if attack.battle_vfx != null:
		await CCS_BattleManager.play_battle_vfx_scene(attack.battle_vfx, user, [target], attack)
	elif attack.power > 0:
		await CCS_BattleManager.play_battle_vfx_scene(CCS_BattleManager.hit_vfx_scene, user, [target], attack)
	
	if attack.power > 0:
		var damage : int = CCS_BattleManager.get_damage(attack, user, target)
		user.last_taken_dealt = damage
		
		var dialogue : Array[String]
		
		if CCS_BattleManager.is_critical_hit:
			dialogue.append_array(critical_hit_text)
		
		if CCS_BattleManager.is_resistant:
			dialogue.append_array(resistant_text)
		elif CCS_BattleManager.is_weak:
			dialogue.append_array(weakness_text)
		
		if not dialogue.is_empty():
			await CCS_BattleUIManager.create_dialogue(dialogue)
	
	if not attack.stat_debuff.is_empty():
		if not _can_decrease_stat(stat_affect_creature):
			return
	
		for debuffed_stat : StringName in attack.stat_debuff:
			await CCS_BattleManager.update_stat(stat_affect_creature, debuffed_stat, -attack.stat_debuff.get(debuffed_stat))
	
	if _can_increase_stat(stat_affect_creature):
		for boosted_stat : StringName in attack.stat_boost:
			await CCS_BattleManager.update_stat(stat_affect_creature, boosted_stat, attack.stat_boost.get(boosted_stat))

func _can_decrease_stat(stat_affect_creature : CCS_Creature) -> bool:
	for debuffed_stat : StringName in attack.stat_debuff:
		if CCS_BattleManager.get_stat_offset(stat_affect_creature, debuffed_stat) <= CCS_BattleManager.stat_offset_minimum:
			return false
	
	return true

func _can_increase_stat(stat_affect_creature : CCS_Creature) -> bool:
	for boosted_stat : StringName in attack.stat_boost:
		if CCS_BattleManager.get_stat_offset(stat_affect_creature, boosted_stat) >= CCS_BattleManager.stat_offset_maximum:
			return false
	
	return true

func has_priority_over(command : CCS_BattleCommandBase) -> bool:
	if command is CCS_BattleCommand_Attack:
		if attack_priority != command.attack_priority:
			return attack_priority > command.attack_priority
		
		if user.stats.speed != command.user.stats.speed:
			return user.stats.speed > command.user.stats.speed
	
		return randi() % 1
	
	return false
