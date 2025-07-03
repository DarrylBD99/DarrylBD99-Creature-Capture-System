@tool
extends Control
class_name CCS_DataManagement
 
@export var import_button : Button
@export var export_button : Button

@export var data_add_text : LineEdit
@export var data_add_button : Button
@export var delete_btn : Button

@export var data_type_dropdown : OptionButton
@export var data_list : ItemList
#@onready var data_filter : LineEdit = $Selectable/Filter
@export var info_edit : TabContainer

var data_edit : Array[Dictionary]
var data_selected : CCS_StaticData_DataBase

var selected_data : Dictionary = {
	"id": "",
	"type": data_types.None
}

enum data_types {
	None,
	Creatures,
	Types,
	Attacks,
	Items
}

func _ready() -> void:
	if data_type_dropdown:
		data_type_dropdown.item_selected.connect(func(_val): _update_data())
	
	if import_button:
		import_button.pressed.connect(import_popup_show)
		%Popups/Load.file_selected.connect(load_static_data)
	
	if export_button:
		export_button.pressed.connect(export_popup_show)
		%Popups/Save.file_selected.connect(save_static_data)
	
	if data_list:
		data_list.item_selected.connect(set_data_selected)
		data_list.item_activated.connect(set_data_selected)
	
	if data_add_button:
		data_add_button.pressed.connect(_add_data)
	
	if delete_btn:
		delete_btn.hide()
		delete_btn.pressed.connect(delete_data)
	
	if info_edit:
		info_edit.current_tab = data_types.None
		data_edit.resize(info_edit.get_tab_count())
	
		for tab_idx : int in data_edit.size():
			data_edit[tab_idx] = _get_data_edit_nodes(info_edit.get_tab_control(tab_idx))
		
		info_edit.tab_changed.connect (
			func(tab : int):
				if (tab == data_types.None): delete_btn.hide()
				else: delete_btn.show()
		)

func delete_data():
	%Popups/Delete.set_label(selected_data["id"], data_type_dropdown.get_item_text(selected_data["type"]))
	%Popups/Delete.show()
	
	if await %Popups/Delete.delete_confirm: _delete_data()

func set_data_selected(idx : int):
	selected_data["id"] = data_list.get_item_text(idx)
	selected_data["type"] = data_type_dropdown.get_selected_id()
	
	info_edit.current_tab = data_type_dropdown.get_selected_id()
	
	_update_data_edit_nodes()
	

func _get_data_edit_nodes(parent) -> Dictionary[String, Control]:
	if (parent == null): return {}
	
	var edit_node_dictionary : Dictionary[String, Control] = {}
	
	for child in parent.get_children(true):
		if "_edit" in child.name:
			var key : String = child.name.replace("_edit", "")
			edit_node_dictionary[key] = child
			if child is CCS_EditorItemContainer:
				child as CCS_EditorItemContainer
				child.item_added.connect (
					func(item : String):
						_add_item_array(key, item)
				)
				
				child.item_updated.connect (
					func(item_old : String, item_new : String):
						_update_item_array(key, item_old, item_new)
				)
				
				child.item_removed.connect (
					func(item : String):
						_remove_item_array(key, item)
				)
			
			elif child is OptionButton:
				child as OptionButton
				child.item_selected.connect (
					func(idx : int):
						_edit_data(key, child.get_item_text(idx))
				)
			
			elif child is LineEdit:
				child as LineEdit
				child.text_changed.connect (
					func(text : String):
						_edit_data(key, text)
				)
			
			elif child is SpinBox:
				child as SpinBox
				child.value_changed.connect (
					func(value : float):
						_edit_data(key, value)
				)
			
		elif child.get_child_count() > 0:
			edit_node_dictionary.merge(_get_data_edit_nodes(child))
	
	return edit_node_dictionary

func _update_data_edit_nodes():
	var data : Dictionary = {"id" : selected_data["id"]}
	
	match selected_data["type"]:
		data_types.None:
			return
		data_types.Creatures:
			data_selected = %StaticData.get_creature_data(selected_data["id"])
		data_types.Types:
			data_selected = %StaticData.get_type_data(selected_data["id"])
		data_types.Attacks:
			data_selected = %StaticData.get_attack_data(selected_data["id"])
		
	data.merge(data_selected.get_data_dictionary())
	_update_data_edit_nodes_base(data)

func _update_data_edit_nodes_base(data : Dictionary):
	var data_edit_nodes : Dictionary = data_edit[selected_data["type"]]
	
	for key : String in data_edit_nodes:
		if data.has(key):
			if data_edit_nodes[key] is CCS_EditorItemContainer:
				var item_container : CCS_EditorItemContainer = data_edit_nodes[key]
				item_container.clear()
				item_container.set_keys(%StaticData.get_keys(data[key]["keys"]))
				
				if data[key]["data"] is Array:
					for item : String in data[key]["data"]:
						item_container.add_item(item)
			elif data_edit_nodes[key] is OptionButton:
				var option_box : OptionButton = data_edit_nodes[key]
				option_box.clear()
				
				var ids : Array = %StaticData.get_keys(data[key]["keys"])
				
				for id : String in ids:
					option_box.add_item(id)
				
				option_box.selected = -1
				if data[key]["data"] != null:
					option_box.selected = ids.find(data[key]["data"])
				
			elif data_edit_nodes[key] is LineEdit:
				var line_edit : LineEdit = data_edit_nodes[key]
				line_edit.text = data[key]
			elif data_edit_nodes[key] is SpinBox:
				var spin_box : SpinBox = data_edit_nodes[key]
				spin_box.value = data[key]

#region Import/Export
func import_popup_show() -> void:
	%Popups/Load.popup()

func load_static_data(path : String) -> void:
	await %StaticData.import_compiled_data(path)
	selected_data["id"] = null
	selected_data["type"] = data_types.None
	info_edit.current_tab = data_types.None
	
	_update_data()

func export_popup_show() -> void:
	%Popups/Save.popup()

func save_static_data(path : String) -> void:
	%StaticData.export_compiled_data(path)
#endregion Import/Export

#region Data Manipulation
func _add_data() -> void:
	if data_add_text.text.is_empty():
		return
	
	match data_type_dropdown.get_selected_id():
		data_types.None:
			return
		data_types.Creatures:
			await %StaticData.add_creature(data_add_text.text)
			data_add_text.clear()
		data_types.Types:
			await %StaticData.add_type(data_add_text.text)
			data_add_text.clear()
		data_types.Attacks:
			await %StaticData.add_attack(data_add_text.text)
			data_add_text.clear()
	
	_update_data()
	_update_data_edit_nodes()

func _update_data():
	data_list.deselect_all()
	data_list.clear()
	
	var data_list_str : Array
	match data_type_dropdown.get_selected_id():
		data_types.None:
			return
		data_types.Creatures:
			data_list_str = %StaticData.get_all_creature_id()
		data_types.Types:
			data_list_str = %StaticData.get_all_type_id()
		data_types.Attacks:
			data_list_str = %StaticData.get_all_attack_id()
	
	for data : String in data_list_str:
		data_list.add_item(data)

func _delete_data() -> void:
	match data_type_dropdown.get_selected_id():
		data_types.None:
			return
		data_types.Creatures:
			await %StaticData.remove_creature(selected_data["id"])
		data_types.Types:
			await %StaticData.remove_type(selected_data["id"])
		data_types.Attacks:
			await %StaticData.remove_attack(selected_data["id"])
	
	data_add_text.clear()
	selected_data["id"] = null
	selected_data["type"] = data_types.None
	info_edit.current_tab = data_types.None
	
	_update_data()
	_update_data_edit_nodes()
#endregion

#region Data Inputs

func _edit_data(key : String, data : Variant):
	var data_dictionary : Dictionary[String, Variant] = {key: data}
	
	data_selected.set_data_from_dictionary(data_dictionary)

func _add_item_array(key : String, item : String):
	var data_dictionary : Dictionary = {
		key : {
			"method" : "add",
			"data" : item
		}
	}
	
	data_selected.set_data_from_dictionary(data_dictionary)

func _update_item_array(key : String, item_old : String, item_new : String):
	var data_dictionary : Dictionary = {
		key : {
			"method" : "update",
			"data" : { item_old : item_new }
		}
	}
	
	data_selected.set_data_from_dictionary(data_dictionary)

func _remove_item_array(key : String, item : String):
	var data_dictionary : Dictionary = {
		key : {
			"method" : "remove",
			"data" : item
		}
	}
	
	data_selected.set_data_from_dictionary(data_dictionary)
#endregion
