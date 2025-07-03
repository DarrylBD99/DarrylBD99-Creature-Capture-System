extends CCS_BattleCommandBase
class_name CCS_EF_BattleCommand_Clash

const clash_texts : Array[String] = ["{users} release their aura."]
const clashing_texts : Array[String] = ["You can feel the intensity from the clashing between auras.", "Deal the most damage to win the clash."]
const clash_success_texts : Array[String] = ["{user}'s aura has overcame the intensity."]

var environments : Array[CCS_EF_BattleCommand_Summon]

func _init(environments : Array[CCS_EF_BattleCommand_Summon]) -> void:
	self.environments = environments
	type = "EF_Clash"

func execute() -> void:
	var format : Dictionary = {
		"users" : ""
	}
	CCS_BattleManager.damage_dealt.connect(_get_damage_taken)
	
	for idx : int in environments.size():
		if idx > 0:
			if idx == environments.size() - 1:
				format["users"] += " and "
			else:
				format["users"] += ", "
		
		environments[idx].user.other_data.set("EF_LastDamageTaken", 0)
		format["users"] += environments[idx].user.get_creature_name()
	
	await CCS_BattleUIManager.create_dialogue(clash_texts, format)
	
	await CCS_EF_BattleEffects.ef_clash(environments)
	
	await CCS_BattleUIManager.create_dialogue(clashing_texts, format)

func turn_end_execute() -> void:
	environments.sort_custom(_sort_by_damage_dealt)
	for environment : CCS_EF_BattleCommand_Summon in environments:
		if environment.user == null or environment.user.is_dead():
			environments.remove_at(environments.find(environment))
	
	var environment : CCS_EF_BattleCommand_Summon = environments.pop_front()

	var format : Dictionary = {
		"user" : environment.user.get_creature_name()
	}

	await CCS_BattleUIManager.create_dialogue(clash_success_texts, format)
	await environment.summon_factor()

func has_priority_over(command : CCS_BattleCommandBase) -> bool:
	if command is CCS_BattleCommand_Creature or command is CCS_BattleCommand_Item or command is CCS_BattleCommand_Flee:
		return false
	
	if command is CCS_BattleCommand_Attack:
		return true

	return randi() % 1 == 0

func combine_command(command : CCS_BattleCommandBase) -> CCS_BattleCommandBase:
	if command is CCS_EF_BattleCommand_Summon:
		environments.append(command)
		return self
	return null

func _sort_by_damage_dealt(a : CCS_EF_BattleCommand_Summon, b : CCS_EF_BattleCommand_Summon) -> bool:
	return a.user.other_data.get("EF_LastDamageTaken") < b.user.other_data.get("EF_LastDamageTaken")

func _get_damage_taken(user : CCS_Creature, _target : CCS_Creature, damage : int) -> void:
	user.other_data.set("EF_LastDamageTaken", damage)
