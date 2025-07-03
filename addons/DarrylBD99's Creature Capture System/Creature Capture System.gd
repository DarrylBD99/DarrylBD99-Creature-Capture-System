@tool
extends EditorPlugin
class_name CCS_EditorPlugin

const battle_manager_uid : String = "uid://ckfh4au320u6x"
const battle_ui_manager_uid : String = "uid://b7w017nyvg5w1"
const editor_singleton_uid : String = "uid://d2u3x2llgwi8d"

const data_management : PackedScene = preload("uid://7k77r5n8hc0x")
const editor_icon : Texture2D = preload("uid://do5vmso070yax")

static var data_management_screen : CCS_EditorUI

func _enter_tree() -> void:
	# Initialization of the plugin goes here.
	add_autoload_singleton("CCS_BattleManager", ResourceUID.get_id_path(ResourceUID.text_to_id(battle_manager_uid)))
	add_autoload_singleton("CCS_BattleUIManager", ResourceUID.get_id_path(ResourceUID.text_to_id(battle_ui_manager_uid)))
	add_autoload_singleton("CCS_EditorSingleton", ResourceUID.get_id_path(ResourceUID.text_to_id(editor_singleton_uid)))
	
	data_management_screen = data_management.instantiate()

	EditorInterface.get_editor_main_screen().add_child(data_management_screen)
	_make_visible(false)

func _exit_tree() -> void:
	# Clean-up of the plugin goes here.
	if data_management_screen:
		data_management_screen.queue_free()
	
	remove_autoload_singleton("CCS_BattleManager")
	remove_autoload_singleton("CCS_BattleUIManager")
	remove_autoload_singleton("CCS_EditorSingleton")

func _has_main_screen():
	return true
	
func _make_visible(visible : bool):
	if data_management_screen:
		data_management_screen.visible = visible

func _get_plugin_name():
	return "Creature Capture System"

func _get_plugin_icon():
	return editor_icon
