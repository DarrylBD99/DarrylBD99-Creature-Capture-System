extends CCS_BattleCommandBase
class_name CCS_BattleCommand_Item

var target : CCS_Creature
var item : CCS_StaticData_Item

const item_dialogue : Array[String] = ["Item."]

func _init(item_id : StringName, target : CCS_Creature) -> void:
	self.target = target
	
	item = CCS_BattleManager.static_data.get_item_data(item_id)

func execute() -> void:
	await item.use_item_in_battle(target)

func has_priority_over(command : CCS_BattleCommandBase) -> bool:
	if command is CCS_BattleCommand_Attack:
		return true
	
	if command is CCS_BattleCommand_Item:
		return false
	
	return false
