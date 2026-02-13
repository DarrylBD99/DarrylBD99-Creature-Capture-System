extends CCS_StaticData_Item
class_name CCS_EF_StaticData_Crystal

const creature_given_ef_text : Array[String] = ["A mysterious aura gathers around {creature}", "{creature} can now summon an Aura Field"]
const creature_has_ef_text : Array[String] = ["{creature} can already use Aura Field"]

func _init() -> void:
	require_creature = true
	can_use_in_bag = true
	can_use_in_battle = false
	use_on_party = true
	can_use_multiple = false

func _use_item(amount : int = 1) -> void:
	await super(amount)
	
	if Engine.get_main_loop().root.has_node("CCS_EF_BattleEffects"):
		Engine.get_main_loop().root.get_node("CCS_EF_BattleEffects").add_ef_factor_to_creature(target_creature)
	
	await CCS_BattleUIManager.create_dialogue(creature_given_ef_text, {
		"creature" : target_creature.get_creature_name()
	})

func can_use_item(creature : CCS_Creature, amount : int = 1) -> bool:
	if not await super(creature):
		return false
	
	if creature.other_data.get("CCS_EF_can_summon") == true:
		await CCS_BattleUIManager.create_dialogue(creature_has_ef_text, { "creature" : creature.get_creature_name() })
		return false
	
	return true
