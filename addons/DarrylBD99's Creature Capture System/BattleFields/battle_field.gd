extends Node3D
class_name CCS_BattleField

@export var player_feet_pos : Array[Marker3D]
@export var opp_feet_pos : Array[Marker3D]
@export var anim_player : AnimationPlayer
@export var extra_proporties : Dictionary = {}

signal battlefield_entered
signal battlefield_exited

func _ready() -> void:
	CCS_BattleManager.turn_on_lights.connect(_turn_on_lights)
	CCS_BattleManager.turn_off_lights.connect(_turn_off_lights)
	
	if anim_player and anim_player.has_animation("Enter"):
		anim_player.play("Enter")
		await anim_player.animation_finished
	battlefield_entered.emit()

func _turn_on_lights() -> void:
	if anim_player and anim_player.has_animation("lights_on"):
		anim_player.play("lights_on")

func _turn_off_lights() -> void:
	if anim_player and anim_player.has_animation("lights_off"):
		anim_player.play("lights_off")
