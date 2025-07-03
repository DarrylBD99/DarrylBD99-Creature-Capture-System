extends CCS_CalculationNode
class_name CCS_CalculationVariableNode
@export var variable_name : String

func _ready() -> void:
	super()
	title += " "
	title += variable_name
