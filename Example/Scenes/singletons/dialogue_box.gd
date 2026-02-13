extends CanvasLayer

@onready var text_box : Label = %Textbox
@onready var controller_icon : Control = %ControllerIcon
@onready var option_container : Control = %OptionContainer

@export var typing_speed : float = 0.02

var line_finished : bool = false
var option_buttons : Array[Button]
var cancel_index : int = 0

const ui_accept_uid : String = "uid://dj5r2ttf2jtnh" # Error with loading ControllerIconTextures on start
const option_scene : PackedScene = preload("uid://htq3wbnt0osl")

signal dialogue_start
signal next_dialogue_line
signal option_selected(idx : int)
signal dialogue_end

func _ready() -> void:
	hide()
	option_container.hide()
	controller_icon.hide()
	%ControllerIcon.texture = load(ui_accept_uid)

func display_dialogue(dialogue : Array[String]) -> void:
	dialogue_start.emit()
	show()
	for text : String in dialogue:
		await set_dialogue_box_text(text)
		controller_icon.show()
		await next_dialogue_line
		controller_icon.hide()
	hide()
	dialogue_end.emit()

func display_dialogue_with_options(dialogue : String, options : Array[String], cancel_idx : int = -1) -> int:
	dialogue_start.emit()
	cancel_index = cancel_idx
	for option_idx : int in options.size():
		option_buttons.append(_create_option(option_idx, options.get(option_idx)))
	show()
	
	await set_dialogue_box_text(dialogue)
	option_container.show()
	option_buttons[0].grab_focus()
	var option_idx : int = await option_selected
	
	hide()
	option_container.hide()
	for option_btn : Button in option_buttons:
		option_btn.queue_free()
	option_buttons.clear()
	dialogue_end.emit()
	return option_idx

func set_dialogue_box_text(text : String) -> void:
	line_finished = false
	text_box.text = ""
	for char_idx : int in text.length():
		text_box.text += text[char_idx]
		await get_tree().create_timer(typing_speed).timeout
	
	line_finished = true

func _input(event: InputEvent) -> void:
	if not visible:
		return
	
	if not line_finished:
		get_viewport().set_input_as_handled()
		return
	
	if option_buttons.is_empty():
		if event.is_action_pressed("ui_accept") or event.is_action_pressed("ui_cancel"):
			next_dialogue_line.emit()
			get_viewport().set_input_as_handled()
	
	if event.is_action_pressed("ui_cancel") and cancel_index >= 0:
		option_selected.emit(cancel_index)
		get_viewport().set_input_as_handled()

func _create_option(idx : int, text : String) -> Button:
	var button : Button = option_scene.instantiate()
	button.pressed.connect(func(): option_selected.emit(idx))
	button.mouse_entered.connect(func(): button.grab_focus())
	button.text = text
	option_container.add_child(button)
	return button
