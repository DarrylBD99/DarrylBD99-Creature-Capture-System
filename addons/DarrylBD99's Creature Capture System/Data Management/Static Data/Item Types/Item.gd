extends CCS_StaticData_DataBase
class_name CCS_StaticData_Item

@export var item_icon : Texture2D = CanvasTexture.new()
@export var sell : int
@export var buy : int

var target_creature : CCS_Creature = null

var require_creature : bool = true
var can_use_in_bag : bool = false
var can_use_in_battle : bool = false
var use_on_party : bool = false
var can_use_multiple : bool = false

const item_cant_use_dialogue : Array[String] = ["{item} cannot be used!"]
const item_use_dialogue : Array[String] = ["{player} used a {item}"]
const cant_use_dialogue : Array[String] = ["Can't use that here."]

func _use_item(amount : int  = 1) -> void:
	if CCS_BattleManager.is_in_battle:
		await CCS_BattleUIManager.create_dialogue(item_use_dialogue, {
			"player" : CCS_PlayerData.get_team().get_trainer_name(),
			"item" : name,
			"creature" : target_creature.get_creature_name()
		})
	
	CCS_PlayerData.throw_item(id, amount)

func use_item_in_battle(creature : CCS_Creature) -> void:
	if not can_use_in_battle:
		push_error("Error: Item cannot be used in battle")
		return
	
	target_creature = creature
	
	if require_creature and target_creature == null:
		push_error("Error: Creature undefined")
		return
	
	await _use_item()

func use_item_in_bag(creature : CCS_Creature, amount : int = 1) -> void:
	if not can_use_in_bag:
		push_error("Error: Item cannot be used in bag")
		return
	
	target_creature = creature
	
	if require_creature and target_creature == null:
		push_error("Error: Creature undefined")
		return

	await _use_item(amount)

func use_on_creature() -> bool:
	return require_creature

func can_use_item(creature : CCS_Creature, amount : int = 1) -> bool:
	if not CCS_PlayerData.can_use_item(id, amount):
		return false
	
	if creature == null and require_creature:
		return false
	
	if not CCS_PlayerData.get_team().creature_list.has(creature) and use_on_party:
		push_error("Error: Creature {0} not found in player's party!".format([creature.get_creature_name()]))
		await CCS_BattleUIManager.create_dialogue(item_cant_use_dialogue, { "item" : name })
		return false
	
	return true
