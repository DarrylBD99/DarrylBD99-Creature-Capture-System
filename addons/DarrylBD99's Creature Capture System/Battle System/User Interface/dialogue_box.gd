extends Control
class_name CCS_DialogueBox

@onready var text_label : Label = %TextLabel
@onready var text_scroll_container : ScrollContainer = %TextScrollContainer
@onready var animation_player : AnimationPlayer = %AnimationPlayer
@onready var options_container : Control = %OptionContainer

var options : Array[String]
var cancel_option : int

@export_multiline var dialogue_text : Array[String]
const typing_speed : float = 0.01
const dialogue_buffer : float = 1

signal option_selected(idx : int)

func _ready() -> void:
	if options_container:
		options_container.hide()
	
	for idx : int in options.size():
		var option_button : Button = Button.new()
		option_button.text = options.get(idx)
		option_button.pressed.connect(option_selected.emit.bind(idx))
		options_container.add_child(option_button)
	
	if animation_player and animation_player.is_playing():
		await animation_player.animation_finished
	
	var text : String
	
	for idx : int in dialogue_text.size():
		
		await _display_text(dialogue_text[idx])
		
		if idx == dialogue_text.size() - 1:
			if not options.is_empty():
				options_container.show()
				options_container.get_child(0).grab_focus()
				await option_selected
				options_container.hide()
				break
		
		await get_tree().create_timer(dialogue_buffer).timeout
		
		if animation_player and animation_player.has_animation("hide_text"):
			if idx < (dialogue_text.size() - 1):
				animation_player.play("hide_text")
				await animation_player.animation_finished
				animation_player.play_backwards("hide_text")
				await animation_player.animation_finished
	
	if animation_player:
		animation_player.play_backwards(animation_player.autoplay)
		await animation_player.animation_finished
	
	queue_free()

func _display_text(text : String) -> void:
	text_label.text = ""
	var char_idx : int = 0
	var char_length : int = text.length()
	var time_counter : float = 0
	while true:
		time_counter += get_process_delta_time()
		
		while time_counter > typing_speed:
			text_label.text += text[char_idx]
			char_idx += 1
			
			if char_idx >= char_length:
				break
			
			time_counter -= typing_speed
		
		if text_scroll_container:
			text_scroll_container.scroll_vertical = text_scroll_container.get_v_scroll_bar().max_value
		
		if char_idx >= char_length - 1:
			break
		
		await get_tree().process_frame
	
	text_label.text = text

func _input(event: InputEvent) -> void:
	if cancel_option >= 0 and event.is_action_pressed("ui_cancel"):
		option_selected.emit(cancel_option)
		get_viewport().set_input_as_handled()
