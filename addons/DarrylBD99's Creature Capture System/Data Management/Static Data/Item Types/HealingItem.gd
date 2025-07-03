extends CCS_StaticData_Item
class_name CCS_StaticData_HealingItem

@export var health : int = 10

const health_full_dialogue : Array[String] = ["{creature}'s health is full!"]
const health_restore_dialogue : Array[String] = ["{creature} restored health"]
const battle_health_restore_dialogue : Array[String] = ["{player}'s {creature} restored health"]

func _init() -> void:
	require_creature = true
	can_use_in_bag = true
	can_use_in_battle = true
	use_on_party = true
	can_use_multiple = true

func _use_item(amount : int = 1) -> void:
	await super(amount)
	
	target_creature.heal(health)
	
	if CCS_BattleManager.is_in_battle:
		await CCS_BattleUIManager.create_dialogue(battle_health_restore_dialogue, {
			"player" : CCS_PlayerData.get_team().get_trainer_name(),
			"creature" : target_creature.get_creature_name()
		})
	else:
		await CCS_BattleUIManager.create_dialogue(health_restore_dialogue, {
			"creature" : target_creature.get_creature_name()
		})

func can_use_item(creature : CCS_Creature, amount : int = 1) -> bool:
	if not await super(creature):
		return false
	
	if creature.get_health_percent() == 100:
		await CCS_BattleUIManager.create_dialogue(health_full_dialogue, { "creature" : creature.get_creature_name() })
		return false
	
	return true
