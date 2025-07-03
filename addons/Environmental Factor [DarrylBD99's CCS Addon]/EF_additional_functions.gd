extends CCS_AdditionalBattleFunctions
class_name CCS_EF_AdditionalBattleFunctions

const drop_text : Array[String] = ["The wild {creature} dropped {amount} {shard}s."]

var wild_creatures : Array[CCS_Creature]

func opp_creature_dead(dead_creature : CCS_Creature) -> void:
	if CCS_BattleManager.is_wild:
		wild_creatures.append(dead_creature)

func turn_end() -> void:
	for creature : CCS_Creature in wild_creatures:
		var amount : int = creature.stats.level
		CCS_PlayerData.give_item(CCS_EF_BattleEffects.EF_shard_item, creature.stats.level)
		await CCS_BattleUIManager.create_dialogue(drop_text, {
			"creature" : creature.get_creature_name(),
			"amount" : amount,
			"shard" : CCS_BattleManager.static_data.items.get(CCS_EF_BattleEffects.EF_shard_item).name,
		})
	wild_creatures.clear()
