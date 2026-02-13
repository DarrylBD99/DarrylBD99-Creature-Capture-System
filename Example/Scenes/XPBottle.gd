extends CCS_StaticData_Item
class_name Game_XP_Bottle

func _init() -> void:
	require_creature = true
	can_use_in_bag = true
	can_use_in_battle = false
	use_on_party = true
	can_use_multiple = false

func _use_item(amount : int = 1) -> void:
	var xp_yield : int = target_creature.get_xp_needed()
	await CCS_BattleManager.gain_xp_gradual(target_creature, xp_yield)
	
	await super(amount)

#func can_use_item(creature : CCS_Creature, amount : int = 1) -> bool:
	#if not await super(creature):
		#return false
	#
	#return true
