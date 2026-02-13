extends CCS_BattleCommandBase
class_name CCS_BattleCommand_Creature

var team : CCS_BattleTeam

var from : CCS_Creature
var to : CCS_Creature

const item_dialogue : Array[String] = ["Creature."]

func _init(team : CCS_BattleTeam, from : CCS_Creature, to : CCS_Creature) -> void:
	self.team = team
	self.from = from
	self.to = to

func execute() -> void:
	await CCS_BattleManager.switch_creatures(team, from, to)

func has_priority_over(command : CCS_BattleCommandBase) -> bool:
	if command is CCS_BattleCommand_Flee:
		return false
	
	if command is CCS_BattleCommand_Creature:
		return false
	
	return not command.has_priority_over(self)
