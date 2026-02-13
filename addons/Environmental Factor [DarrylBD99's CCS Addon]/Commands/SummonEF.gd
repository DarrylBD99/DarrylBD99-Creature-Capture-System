extends CCS_BattleCommandBase
class_name CCS_EF_BattleCommand_Summon

const summon_texts : Array[String] = ["{user} releases a powerful wave of aura."]
const summon_success_texts : Array[String] = ["{user}'s aura engulfes the battlefield."]
const environment_aura_texts : Array[String] = ["The environment has shifted to benefit {user} and certain Lumas."]

var user : CCS_Creature
var EF_Type : StringName

var format : Dictionary

func _init(user : CCS_Creature) -> void:
	type = "summon"

	self.user = user
	var user_species : CCS_StaticData_Creature = user.get_species_static_data()
	EF_Type = user_species.types.get(0)
	
	format = {
		"user" : user.get_creature_name()
	}

func execute() -> void:
	if user == null or user.is_dead():
		return
	
	await CCS_BattleUIManager.create_dialogue(summon_texts, format)
	
	await summon_factor()

func summon_factor() -> void:
	await CCS_EF_BattleEffects.set_ef_type_factor(user, EF_Type)
	
	await CCS_BattleUIManager.create_dialogue(summon_success_texts, format)
	await CCS_EF_BattleEffects.add_visual_effect()
	
	await CCS_BattleUIManager.create_dialogue(environment_aura_texts, format)

func has_priority_over(command : CCS_BattleCommandBase) -> bool:
	if command is CCS_BattleCommand_Creature or command is CCS_BattleCommand_Item or command is CCS_BattleCommand_Flee:
		return false
	
	if command is CCS_BattleCommand_Attack:
		return true

	return randi() % 1 == 0

func combine_command(command : CCS_BattleCommandBase) -> CCS_BattleCommandBase:
	if command is CCS_EF_BattleCommand_Summon:
		return CCS_EF_BattleCommand_Clash.new([self, command])
	
	if command is CCS_EF_BattleCommand_Clash:
		command.append(self)
		return command
	
	return null
