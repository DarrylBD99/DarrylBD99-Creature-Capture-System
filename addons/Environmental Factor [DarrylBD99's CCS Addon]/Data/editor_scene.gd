@tool
extends CCS_DataManagement
class_name CCS_EF_EditorScene

@onready var info_edit_panel : Control = $EditableInfo/Info

var ef_data_selected : CCS_EF_TypeData

enum ef_data_types {
	None,
	Terrain,
	TypeFactor
}

func _ready():
	super()
	info_edit_panel.hide()
	visibility_changed.connect( func(): %StaticData.reset_type_ids() )
	
	var data_edit_nodes : Dictionary[String, Control] = _get_data_edit_nodes(info_edit_panel)
	
	data_edit.resize(ef_data_types.size())
	data_edit[ef_data_types.Terrain] = data_edit_nodes
	data_edit[ef_data_types.TypeFactor] = data_edit_nodes

func set_static_data(static_data : CCS_StaticDataEdit):
	%StaticData.static_data = static_data

func set_data_selected(idx : int):
	selected_data["id"] = data_list.get_item_text(idx)
	selected_data["type"] = data_type_dropdown.get_selected_id()
	
	info_edit_panel.show()
	
	_update_data_edit_nodes()

func _update_data_edit_nodes():
	var data : Dictionary = {"id" : selected_data["id"]}
	
	match selected_data["type"]:
		ef_data_types.None:
			return
		ef_data_types.Terrain:
			data_selected = %StaticData.get_terrain_data(selected_data["id"])
		ef_data_types.TypeFactor:
			data_selected = %StaticData.get_type_factor_data(selected_data["id"])
	
	data.merge(data_selected.get_data_dictionary())
	
	_update_data_edit_nodes_base(data)

#region Import/Export
func load_static_data(path : String) -> void:
	await %StaticData.import_compiled_data(path)
	selected_data["id"] = null
	selected_data["type"] = data_types.None
	info_edit_panel.hide()
	
	_update_data()
#endregion Import/Export

#region Data Manipulation
func _add_data() -> void:
	if data_add_text.text.is_empty():
		return
	
	match data_type_dropdown.get_selected_id():
		ef_data_types.None:
			return
		ef_data_types.Terrain:
			await %StaticData.add_terrain(data_add_text.text)
			data_add_text.clear()
		ef_data_types.TypeFactor:
			return
	
	_update_data()
	_update_data_edit_nodes()

func _update_data():
	data_list.deselect_all()
	data_list.clear()
	
	var data_list_str : Array
	match data_type_dropdown.get_selected_id():
		ef_data_types.None:
			return
		ef_data_types.Terrain:
			data_list_str = %StaticData.get_all_terain_id()
			data_add_text.show()
			data_add_button.show()
		ef_data_types.TypeFactor:
			data_list_str = %StaticData.type_ids
			data_add_text.clear()
			data_add_text.hide()
			data_add_button.hide()
	
	
	for data : String in data_list_str:
		data_list.add_item(data)

func _delete_data() -> void:
	match data_type_dropdown.get_selected_id():
		ef_data_types.None:
			return
		ef_data_types.Terrain:
			await %StaticData.remove_terrain(selected_data["id"])
		ef_data_types.TypeFactor:
			return
	
	data_add_text.clear()
	selected_data["id"] = null
	selected_data["type"] = data_types.None
	info_edit.current_tab = data_types.None
	
	_update_data()
	_update_data_edit_nodes()

func delete_data():
	%Popups/Delete.set_label(selected_data["id"], data_type_dropdown.get_item_text(selected_data["type"]))
	%Popups/Delete.show()
	
	if await %Popups/Delete.delete_confirm: _delete_data()
#endregion
