extends CCS_AdditionalBattleFunctions
class_name Game_TrainerMoney

const defeat_dialogue : Array[String] = ["{player} defeated {opponent}", "{opponent} gave {player} ${money}"]

var money : int

func _init(money_ : int) -> void:
	money = money_

func battle_end_initialized() -> void:
	if CCS_BattleManager.is_lose:
		return
	
	CCS_PlayerData.add_money(money)
	await CCS_BattleUIManager.create_dialogue(defeat_dialogue, {
		"player" : CCS_BattleManager.get_teams_name_string(CCS_BattleManager.ally_teams),
		"opponent" : CCS_BattleManager.get_teams_name_string(CCS_BattleManager.opp_teams),
		"money" : money,
	})
