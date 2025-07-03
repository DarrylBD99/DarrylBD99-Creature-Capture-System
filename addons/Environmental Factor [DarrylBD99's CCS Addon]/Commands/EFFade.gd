extends CCS_BattleCommandBase
class_name CCS_EF_BattleCommand_Fade

const summon_fade_texts : Array[String] = ["{user}'s aura has subsided."]

var user : CCS_Creature

func _init(user : CCS_Creature) -> void:
	type = "summon"

	self.user = user

func execute() -> void:
	pass

func turn_end_execute() -> void:
	var format : Dictionary = {
		"user" : user.get_creature_name()
	}
	
	await CCS_EF_BattleEffects.remove_ef_type_factor()
	
	await CCS_BattleUIManager.create_dialogue(summon_fade_texts, format)
