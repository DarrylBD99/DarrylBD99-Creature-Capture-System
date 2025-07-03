extends CCS_StaticData_Item
class_name CCS_EF_StaticData_Shard

const creature_given_shard_text : Array[String] = ["{creature}'s {stat} increased!"]
const creature_cant_use : Array[String] = ["Can't use on {creature}"]
const creature_max_shards : Array[String] = ["{creature} has already been given {shard_max} {name}"]
const creature_choose_stat : Array[String] = ["Select a stat you would like to buff."]

var stat_id : StringName
var stat_name : String
var used_shards : int = 0

func _init() -> void:
	require_creature = true
	can_use_in_bag = true
	can_use_in_battle = false
	use_on_party = true
	can_use_multiple = false

func _use_item(amount : int = 1) -> void:
	await super(amount)
	
	target_creature.other_data.set("CCS_EF_shards_given", used_shards + 1)
	
	CCS_BattleManager.offset_extra_stats(target_creature, stat_id, 1)
	
	await CCS_BattleUIManager.create_dialogue(creature_given_shard_text, {
		"creature" : target_creature.get_creature_name(),
		"stat" : stat_name,
	})

func can_use_item(creature : CCS_Creature, amount : int = 1) -> bool:
	if not await super(creature):
		return false
	
	if creature.other_data.get("CCS_EF_can_summon") != true:
		await CCS_BattleUIManager.create_dialogue(creature_cant_use, { "creature" : creature.get_creature_name() })
		return false
	
	if creature.other_data.get("CCS_EF_shards_given") == null:
		creature.other_data.set("CCS_EF_shards_given", 0)
	
	if not Engine.get_main_loop().root.has_node("CCS_EF_BattleEffects"):
		return false
	
	if creature.other_data.get("CCS_EF_shards_given") >= Engine.get_main_loop().root.get_node("CCS_EF_BattleEffects").max_shards:
		await CCS_BattleUIManager.create_dialogue(creature_max_shards, {
			"creature" : creature.get_creature_name(),
			"shard_max" : Engine.get_main_loop().root.get_node("CCS_EF_BattleEffects").max_shards,
			"name" : name
		})
		return false
	
	used_shards = creature.other_data.get("CCS_EF_shards_given")
	var options : Array[String] = [
		Engine.get_main_loop().root.get_node("CCS_EF_BattleEffects").EF_strength_name,
		Engine.get_main_loop().root.get_node("CCS_EF_BattleEffects").EF_duration_name,
		"Cancel"
	]
	
	var option : int = await CCS_BattleUIManager.create_dialogue_options(creature_choose_stat, options, 2)
	
	match option:
		0:
			stat_id = "EF_Strength"
			stat_name = Engine.get_main_loop().root.get_node("CCS_EF_BattleEffects").EF_strength_name
		1:
			stat_id = "EF_Duration"
			stat_name = Engine.get_main_loop().root.get_node("CCS_EF_BattleEffects").EF_duration_name
		_:
			return false
	
	return true
