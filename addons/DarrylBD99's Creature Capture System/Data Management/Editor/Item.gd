@tool

extends HBoxContainer
class_name CCS_EditorItem

@onready var option_button : OptionButton = $OptionButton
var item
var keys : Array

const item_scene : PackedScene = preload("uid://cacme8iordqi1")

signal item_edit(val_old : String, val_new : String)
signal item_remove(val : String)

func _ready() -> void:
	for key in keys:
		option_button.add_item(key)
	
	option_button.select(keys.find(item))
	
	option_button.item_selected.connect(
		func(index : int):
			item_edit.emit(item, keys.get(index))
			item = keys.get(index)
	)
	
	$RemoveButton.pressed.connect (
		func():
			item_remove.emit(item)
			queue_free()
	)

static func create_item(val) -> CCS_EditorItem:
	if not val.is_empty():
		var item_scene_instance : CCS_EditorItem = item_scene.instantiate()
		item_scene_instance.item = val
		
		return item_scene_instance
	return null
