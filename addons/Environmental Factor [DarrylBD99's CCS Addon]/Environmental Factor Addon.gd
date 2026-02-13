@tool
extends EditorPlugin

var editor_scene : PackedScene = preload("uid://7pbjsu34ohyt")
var editor_screen : CCS_EF_EditorScene
var battle_effect_script_uid : String = "uid://drgo0bxuoabxb"

func _enter_tree() -> void:
	var editor_interface = Engine.get_singleton("EditorInterface")
	if not editor_interface.is_plugin_enabled("DarrylBD99's Creature Capture System"):
		push_error("Error: DarrylBD99's Creature Capture System is not installed/enabled")
		return
	
	# Initialization of the plugin goes here.
	add_autoload_singleton("CCS_EF_BattleEffects", ResourceUID.get_id_path(ResourceUID.text_to_id(battle_effect_script_uid)))
	
	editor_screen = editor_scene.instantiate()
	var ccs_singleton = get_node("/root/CCS_EditorSingleton")
	var data_management : CCS_EditorUI = ccs_singleton.data_management
	
	editor_screen.set_static_data(data_management.static_data)
	data_management.tab_container.add_child(editor_screen)

func _exit_tree() -> void:
	# Clean-up of the plugin goes here.
	if editor_screen:
		editor_screen.queue_free()

	remove_autoload_singleton("CCS_EF_BattleEffects")
