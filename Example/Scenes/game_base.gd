extends Node
class_name GameBase

@export_category("World")
@export var world_env_scene : PackedScene
@export var healer_location : Marker3D

static var can_pause : bool = true
static var selling : bool = false
static var buying : bool = false
static var luma_box_opened : bool = false
static var player : Node3D
static var playing_cutscene : bool = false

var world_env : WorldEnvironment

func _ready() -> void:
	_instance_world_env()
	
	player = %Player
	if CCS_PlayerData.get_variable("player_pos") != null:
		player.global_position = CCS_PlayerData.get_variable("player_pos")
	
	if CCS_PlayerData.get_variable("player_facing_dir") != null:
		player.facing_dir = CCS_PlayerData.get_variable("player_facing_dir")
	#CCS_PlayerData.give_item("AuraShard", 40)
	
	CCS_BattleManager.battle_initialized.connect(_remove_world_env)
	CCS_BattleManager.battle_ending.connect(_battle_ending)
	CCS_BattleManager.battle_end.connect(_battle_end)
	
	player.disabled = true
	CCS_BattleUIManager.play_transition("black_fade_out")
	await CCS_BattleUIManager.transition_end
	player.disabled = false

func _instance_world_env() -> void:
	if world_env != null:
		_remove_world_env()
	
	world_env = world_env_scene.instantiate()
	add_child(world_env)

func _battle_ending(is_lose : bool = false) -> void:
	if is_lose:
		player.global_position = healer_location.global_position
	
	_instance_world_env()

func _battle_end(is_lose : bool = false) -> void:
	if is_lose:
		await Game_DialogueBox.display_dialogue(["Your part has been fully healed.", "We hope you excel!"])
	
		player.disabled = false

func _remove_world_env() -> void:
	if world_env != null:
		world_env.queue_free()

func _input(_event: InputEvent) -> void:
	if playing_cutscene and not CCS_BattleManager.is_in_battle:
		get_viewport().set_input_as_handled()
