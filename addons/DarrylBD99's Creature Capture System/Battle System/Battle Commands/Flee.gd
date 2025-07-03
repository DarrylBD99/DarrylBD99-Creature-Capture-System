extends CCS_BattleCommandBase
class_name CCS_BattleCommand_Flee

const run_dialogue : Array[String] = ["Ran Away."]

func _init() -> void:
	stop_battle = true
	type = "Flee"

func execute() -> void:
	await CCS_BattleUIManager.create_dialogue(run_dialogue)

func has_priority_over(_command : CCS_BattleCommandBase) -> bool:
	return true
