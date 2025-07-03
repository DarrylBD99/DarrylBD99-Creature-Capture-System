extends Node
class_name CCS_BattleCommandBase

const null_texts : Array[String] = ["Invalid Command", "If this isn't suppose to happen, please check code for any errors."]

var stop_battle : bool = false

var type := "Null"

func execute() -> void:
	#await CCS_BattleUIManager.create_dialogue(null_texts)
	pass

func turn_end_execute() -> void:
	pass

func has_priority_over(command : CCS_BattleCommandBase) -> bool:
	return not command is CCS_BattleCommand_Flee

func combine_command(command : CCS_BattleCommandBase) -> CCS_BattleCommandBase:
	return null
