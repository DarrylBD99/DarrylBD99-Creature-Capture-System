extends CCS_StaticData_Item
class_name CCS_StaticData_CaptureItem

@export var device_catch_rate : float = 1.0

const capturing_dialogue : Array[String] = ["{player} threw a {item}."]
const too_many_opponents : Array[String] = ["There's too many Lumas on the opposing side, making it hard to aim.", "Defeat one of them to catch the other."]
const thief_dialogue : Array[String] = ["Please don't be a thief..."]

func _init() -> void:
	require_creature = true
	can_use_in_bag = false
	can_use_in_battle = true
	use_on_party = false
	can_use_multiple = false

func _use_item(amount : int = 1) -> void:
	if not CCS_BattleManager.is_in_battle:
		return
	
	var catch_rate : float = CCS_BattleManager.get_catch_rate(target_creature, device_catch_rate)
	
	await CCS_BattleUIManager.create_dialogue(capturing_dialogue, {
		"player" : CCS_PlayerData.get_team().get_trainer_name(),
		"item" : name
	})
	
	CCS_PlayerData.throw_item(id, amount)
	await CCS_BattleManager.catch_opponent(target_creature, catch_rate)

func use_on_creature() -> bool:
	if not CCS_BattleManager.is_wild:
		await CCS_BattleUIManager.create_dialogue(thief_dialogue)
		return false
	
	if CCS_BattleManager.is_boss:
		await CCS_BattleUIManager.create_dialogue(cant_use_dialogue)
		return false
	
	var opp_count : int = 0
	
	for opp_creature : CCS_Creature in CCS_BattleManager.opp_creatures:
		if opp_creature == null or opp_creature.is_dead():
			continue
		
		opp_count += 1
	
	if opp_count > 1:
		await CCS_BattleUIManager.create_dialogue(too_many_opponents)
		return false
	
	return super()
