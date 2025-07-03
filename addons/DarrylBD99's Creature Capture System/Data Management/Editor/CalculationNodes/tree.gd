@tool
extends Window

@onready var tree : Tree = $ScrollContainer/Tree

var variable_root : TreeItem
var setter_root : TreeItem
var getter_root : TreeItem

func _ready() -> void:
	close_requested.connect(_on_close_requested)
	_create_variable_nodes(%StaticData.get_all_calc_variables())

func _create_variable_nodes(variables : Dictionary) -> void:
	variable_root = tree.create_item()
	setter_root = tree.create_item(variable_root)
	getter_root = tree.create_item(variable_root)
	
	variable_root.set_text(0, "Variables")
	setter_root.set_text(0, "Set")
	getter_root.set_text(0, "Get")
	
	for variable : String in variables:
		variables[variable]

func _on_close_requested() -> void:
	hide()
