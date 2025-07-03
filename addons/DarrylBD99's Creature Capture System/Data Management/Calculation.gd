@tool
extends Control

@export_category("Variables")
@onready var var_list : ItemList = $Variables/VariableScroll/VariableList
@onready var add_var_button : Button = $Variables/VarDataHBox/Add
@onready var var_name : LineEdit = $Variables/VarNameHBox/LineEdit
@onready var var_type : OptionButton = $Variables/VarNameHBox/OptionButton

@onready var data_str_line : LineEdit = $Variables/VarDataHBox/StrLineEdit
@onready var data_int_spin : SpinBox = $Variables/VarDataHBox/IntSpinBox
@onready var data_bool_option : OptionButton = $Variables/VarDataHBox/BoolOption

@export_category("Graph")
@onready var graph_edit : GraphEdit = $GraphEdit

var mouse_over_graph : bool = false

enum VariableType {
	STR = 0,
	INT = 1,
	BOOL = 2
}

func _ready():
	add_var_button.pressed.connect(add_variable)
	var_type.item_selected.connect(update_variable_type)
	var_type.select(0)
	
	graph_edit.mouse_entered.connect(func(): mouse_over_graph = true)
	graph_edit.mouse_exited.connect(func(): mouse_over_graph = false)

func _input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		if event.get_button_index() == 2 and event.pressed and mouse_over_graph:
			show_popup(event.position)

func show_popup(mouse_position : Vector2) -> void:
	%Popups/GraphRightClick.show()
	%Popups/GraphRightClick.position = mouse_position

func update_variable_list() -> void:
	var_list.clear()
	var calc_variables : Dictionary = %StaticData.get_all_calc_variables()
	
	for var_name : String in calc_variables:
		var item_name : String = var_name
		print(calc_variables[var_name])
		if calc_variables[var_name].has("value"):
			print("has value")
			var_name += " {default: " + str(calc_variables[var_name]["value"]) + "}"
		
		var_list.add_item(var_name)

func update_variable_type(idx : int) -> void:
	match idx:
		VariableType.STR:
			data_str_line.show()
			data_int_spin.hide()
			data_bool_option.hide()
		VariableType.INT:
			data_str_line.hide()
			data_int_spin.show()
			data_bool_option.hide()
		VariableType.BOOL:
			data_str_line.hide()
			data_int_spin.hide()
			data_bool_option.show()

func add_variable() -> void:
	if %StaticData.has_calc_variable(var_name.text):
		push_error("Error: Variable already exist")
		return
	
	var variable : Dictionary = {
		var_name.text : {
			"type": VariableType.STR
		}
	}
	match var_type.selected:
		VariableType.STR:
			if not data_str_line.text.is_empty():
				variable[var_name.text]["value"] = data_str_line.text
				data_str_line.clear()
			
		VariableType.INT:
			variable[var_name.text]["value"] = data_int_spin.value
			data_int_spin.value = 0
			
		VariableType.BOOL:
			variable[var_name.text]["value"] = data_bool_option.selected
			data_bool_option.select(0)
	
	var_name.clear()
	
	%StaticData.set_calc_variable(variable)
	update_variable_list()
