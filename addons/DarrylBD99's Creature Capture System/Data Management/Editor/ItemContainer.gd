@tool
extends VBoxContainer
class_name CCS_EditorItemContainer

signal item_added(item : String)
signal item_updated(item_old : String, item_new : String)
signal item_removed(item : String)
var items : Array
var keys : Array

func _ready() -> void:
	$OptionButton.item_selected.connect(_add_item_listed)

func set_keys(keys : Array):
	self.keys = keys
	for key in keys:
		$OptionButton.add_item(key)
	
	$OptionButton.select(-1)

func _add_item_listed(id : int):
	if (id < 0): return
	var item : String = $OptionButton.get_item_text(id)
	if (items.has(item)):
		push_warning("Error: Item already exist")
		return
	
	add_item(item)
	item_added.emit(item)
	$OptionButton.select(-1)

func add_item(item : String):
	if (items.has(item)):
		push_warning("Error: Item already exist")
		return
	
	var item_node : CCS_EditorItem = CCS_EditorItem.create_item(item)
	
	item_node.keys = keys
	item_node.item_edit.connect (
		func(val_old : String, val_new : String):
			if (items.has(val_new)):
				push_warning("Error: Item already exist")
				item_node.option_button.select(keys.find(val_old))
				return
			
			var idx : int = items.find(val_old)
			item_updated.emit(val_old, val_new)
			items[idx] = val_new
	)

	item_node.item_remove.connect (
		func(val : String):
			item_removed.emit(val)
			items.remove_at(items.find(val))
	)
	
	add_child(item_node)
	move_child(item_node, items.size())
	items.append(item)

func clear():
	$OptionButton.clear()
	items.clear()
	for child in get_children():
		if child is CCS_EditorItem:
			child.queue_free()
