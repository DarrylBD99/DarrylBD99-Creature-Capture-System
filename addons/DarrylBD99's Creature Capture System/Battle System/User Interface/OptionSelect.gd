extends Control
class_name CCS_BattleUI_OptionSelect

signal option_selected(option : StringName)

var options : Dictionary[StringName, Button]

func _ready() -> void:
	hide()
	for button : Button in get_children():
		options[button.name] = button
		button.pressed.connect(func(): option_selected.emit(button.name))

func _unhandled_input(event: InputEvent) -> void:
	if event.is_action_pressed("ui_cancel"):
		option_selected.emit("")

func enable_options() -> void:
	show()
	
	for option : Button in options.values():
		if option.visible:
			option.grab_focus()
			return
