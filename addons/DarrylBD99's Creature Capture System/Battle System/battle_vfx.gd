extends Node3D
class_name CCS_BattleVFX

signal disposed

@export var battle_field_scenes : Array[PackedScene]
@export var battle_fields : Array[CCS_BattleField]

var user : CCS_Creature
var targets : Array[CCS_Creature]
var attack : CCS_StaticData_Attack

var old_field : CCS_BattleField

func _ready() -> void:
	await $AnimationPlayer.animation_finished
	disposed.emit()
	queue_free()

func setup(user : CCS_Creature, targets : Array[CCS_Creature], attack : CCS_StaticData_Attack) -> void:
	self.user = user
	self.targets = targets
	self.attack = attack

func set_position_user() -> void:
	if user and user.sprite:
		global_position = user.sprite.global_position

func set_position_user_top() -> void:
	if user and user.sprite:
		global_position = user.sprite.global_position
		global_position.y += user.sprite.offset.y / 10 * 2

func set_position_user_center() -> void:
	if user and user.sprite:
		global_position = user.sprite.global_position
		global_position.y += user.sprite.offset.y / 10

func set_position_target(idx : int = 0) -> void:
	if idx < targets.size():
		var target : CCS_Creature = targets.get(idx)
		
		if target and target.sprite:
			global_position = target.sprite.global_position

func set_position_target_top(idx : int = 0) -> void:
	if idx < targets.size():
		var target : CCS_Creature = targets.get(idx)
		
		if target and target.sprite:
			global_position = target.sprite.global_position
			global_position.y += target.sprite.offset.y / 10 * 2

func set_position_target_center(idx : int = 0) -> void:
	if idx < targets.size():
		var target : CCS_Creature = targets.get(idx)
		
		if target and target.sprite:
			global_position = target.sprite.global_position
			global_position.y += target.sprite.offset.y / 10

func focus_camera_to_field(time : float = 0.4, trans_type : Tween.TransitionType = Tween.TRANS_LINEAR, type : Tween.EaseType = Tween.EASE_IN) -> void:
	CCS_BattleManager.focus_camera.emit(null, time, trans_type, type)

func focus_camera_to_user(time : float = 0.4, trans_type : Tween.TransitionType = Tween.TRANS_LINEAR, type : Tween.EaseType = Tween.EASE_IN) -> void:
	CCS_BattleManager.focus_camera.emit(user, time, trans_type, type)

func focus_camera_to_target(time : float = 0.4, trans_type : Tween.TransitionType = Tween.TRANS_LINEAR, type : Tween.EaseType = Tween.EASE_IN, target_idx : int = 0) -> void:
	CCS_BattleManager.focus_camera.emit(targets[target_idx], time, trans_type, type)

func focus_camera_to_field_no_tween() -> void:
	CCS_BattleManager.focus_camera_no_tween.emit(null)

func focus_camera_to_user_no_tween() -> void:
	CCS_BattleManager.focus_camera_no_tween.emit(user)

func focus_camera_to_target_no_tween(target_idx : int = 0) -> void:
	CCS_BattleManager.focus_camera_no_tween.emit(targets[target_idx])

func camera_shake_tween(trauma : Vector3 = Vector3.ZERO, time : float = 0.5, trans_type : Tween.TransitionType = Tween.TRANS_LINEAR, ease_type : Tween.EaseType = Tween.EASE_IN) -> void:
	CCS_BattleManager.camera_shake_tween.emit(trauma, time, trans_type, ease_type)

func camera_shake(trauma : Vector3 = Vector3.ZERO) -> void:
	CCS_BattleManager.camera_shake.emit(trauma)

func turn_off_lights() -> void:
	CCS_BattleManager.turn_off_lights.emit()

func turn_on_lights() -> void:
	CCS_BattleManager.turn_on_lights.emit()

func ui_transition(trans_name : String, speed_scale : float = 1) -> void:
	CCS_BattleUIManager.play_transition(trans_name, speed_scale)

func change_field(idx : int) -> void:
	old_field = CCS_BattleManager.battle_field
	
	if idx < battle_fields.size():
		CCS_BattleManager.battle_field = battle_fields.get(idx)

func set_scale_to_user_sprite_tween(multiplier : float, duration : float = 1) -> void:
	var tween : Tween = create_tween()
	var sprite_scale_multiplier : float = user.sprite.offset.y * 0.05
	tween.tween_property(self, "scale", Vector3.ONE * sprite_scale_multiplier * multiplier, duration)

func change_field_scene(idx : int) -> void:
	old_field = CCS_BattleManager.battle_field
	
	if idx < battle_fields.size():
		CCS_BattleManager.battle_field = battle_field_scenes.get(idx).instantiate()

func reset_field(idx : int) -> void:
	old_field = CCS_BattleManager.battle_field
	
	if idx < battle_fields.size():
		CCS_BattleManager.battle_field = battle_fields.get(idx).instantiate()

func damage_target_with_attack(idx : int = 0) -> void:
	if idx >= targets.size():
		push_warning("No target defined")
		return
	
	if not user:
		push_warning("No user defined")
		return
	
	if not attack:
		push_warning("No attack defined")
		return
		
	var target : CCS_Creature = targets[idx]
	target.damage(CCS_BattleManager.get_damage(attack, user, target))
