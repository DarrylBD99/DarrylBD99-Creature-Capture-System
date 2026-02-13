extends CCS_AdditionalBattleFunctions
class_name Game_DefeatFunction

const defeat_dialogue : Array[String] = ["{player} has ran out of Lumas to battle...", "{player} white out!"]

func battle_end_initialized() -> void:
	if CCS_BattleManager.is_lose:
		await CCS_BattleUIManager.create_dialogue(defeat_dialogue, {"player" : CCS_PlayerData.get_team().get_trainer_name()})
