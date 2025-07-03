extends Node

var player_sprites : Array[CCS_CreatureSprite3D]
var opp_sprites : Array[CCS_CreatureSprite3D]

const battle_field_paths := {
	"default" : "uid://csgj4ys4fbply" #res://addons/Creature Capture System/BattleFields/battle_field_1.tscn
}

func _ready() -> void:
	CCS_BattleManager.battle_start.connect(_update_sprites)
	CCS_BattleManager.battle_field_change.connect(_update_battle_field)
	
	CCS_BattleManager.refresh_creature.connect(_update_sprites)
	CCS_BattleManager.creature_summon.connect(_send_out_creature)
	CCS_BattleManager.creature_retrieve.connect(_retrieve_creature)
	CCS_BattleManager.add_shader.connect(_add_shader)
	
	#Camera Signals
	CCS_BattleManager.focus_camera.connect(_focus_camera)
	CCS_BattleManager.focus_camera_no_tween.connect(_focus_camera_no_tween)
	CCS_BattleManager.camera_shake_tween.connect(_tween_camera_trauma)
	CCS_BattleManager.camera_shake.connect(_set_camera_trauma)
	
	CCS_BattleManager.battle_initialized.connect(_initialize_battle)
	CCS_BattleManager.creature_dead.connect(_creature_dead)
	CCS_BattleManager.battle_ending.connect(_end_battle)
	
	if camera.current:
		camera.clear_current(true)

func _update_battle_field(field : CCS_BattleField) -> void:
	if not get_children().has(CCS_BattleManager.battle_field):
		add_child(CCS_BattleManager.battle_field)

func _update_sprites():
	for child in get_children():
		if child is CCS_CreatureSprite3D:
			child.queue_free()

	for i : int in CCS_BattleManager.ally_creatures.size():
		create_player_sprite(i, CCS_BattleManager.ally_creatures[i])
	for i : int in CCS_BattleManager.opp_creatures.size():
		create_opp_sprite(i, CCS_BattleManager.opp_creatures[i])

func _play_sfx(clip_name : StringName) -> void:
	$SFXStreamPlayer.play()
	var sfx_playback : AudioStreamPlaybackInteractive = $SFXStreamPlayer.get_stream_playback()
	sfx_playback.switch_to_clip_by_name(clip_name)

func _send_out_creature(creatures : Array[CCS_Creature]) -> void:
	_play_sfx("Summon")
	
	for creature : CCS_Creature in creatures:
		if creature == null or creature.is_dead():
			continue
		
		if creature in CCS_BattleManager.ally_creatures:
			CCS_BattleUIManager.set_creature_ally(creature, CCS_BattleManager.ally_creatures.find(creature))
			_summon_ally(creature)

		elif creature in CCS_BattleManager.opp_creatures:
			CCS_BattleUIManager.set_creature_opp(creature, CCS_BattleManager.opp_creatures.find(creature))
			_summon_opp(creature)

func _summon_ally(creature : CCS_Creature):
	if creature == null or creature.is_dead():
		return
	
	await player_sprites.get(CCS_BattleManager.ally_creatures.find(creature)).grow_from_ground()

func _summon_opp(creature : CCS_Creature):
	if creature == null or creature.is_dead():
		return
	
	await opp_sprites.get(CCS_BattleManager.opp_creatures.find(creature)).grow_from_ground()

func _retrieve_creature(creature : CCS_Creature) -> void:
	var idx : int
	
	if creature in CCS_BattleManager.ally_creatures:
		idx = CCS_BattleManager.ally_creatures.find(creature)
		CCS_BattleUIManager.set_creature_ally(null, idx)
		await player_sprites.get(idx).shrink_to_ground()
	elif creature in CCS_BattleManager.opp_creatures:
		idx = CCS_BattleManager.opp_creatures.find(creature)
		CCS_BattleUIManager.set_creature_opp(null, idx)
		await opp_sprites.get(idx).shrink_to_ground()
	
func _initialize_battle() -> void:
	if CCS_BattleManager.battle_field != null:
		_update_battle_field(CCS_BattleManager.battle_field)
	else:
		CCS_BattleManager.battle_field = load(battle_field_paths["default"]).instantiate()
	
	camera.make_current()

func _end_battle(_is_lose : bool) -> void:
	if CCS_BattleManager.battle_field:
		CCS_BattleManager.battle_field.queue_free()
	
	camera.clear_current(true)

func create_opp_sprite(team_idx : int, creature : CCS_Creature) -> void:
	if creature == null or creature.is_dead():
		return
	var opp_sprite : CCS_CreatureSprite3D = CCS_CreatureSprite3D.new()
	await opp_sprite.setup(creature)
	
	add_child(opp_sprite)
	
	if CCS_BattleManager.opp_teams.size() == 1: opp_sprite.global_position = opp_sprite.get_position_from_feet(CCS_BattleManager.battle_field.opp_feet_pos[1])
	elif CCS_BattleManager.opp_teams.size() == 2: opp_sprite.global_position = opp_sprite.get_position_from_feet(CCS_BattleManager.battle_field.opp_feet_pos[team_idx * 2])
	else: opp_sprite.global_position = opp_sprite.get_position_from_feet(CCS_BattleManager.battle_field.opp_feet_pos[team_idx])
	
	creature.sprite = opp_sprite
	opp_sprite.set_camera_pos()
	
	if team_idx < opp_sprites.size():
		opp_sprites.set(team_idx, opp_sprite)
	else:
		opp_sprites.append(opp_sprite)

func create_player_sprite(team_idx : int, creature : CCS_Creature):
	if creature == null or creature.is_dead():
		return
	
	var player_sprite : CCS_CreatureSprite3D = CCS_CreatureSprite3D.new()
	await player_sprite.setup(creature, true)
	add_child(player_sprite)
	
	if CCS_BattleManager.ally_teams.size() == 1: player_sprite.global_position = player_sprite.get_position_from_feet(CCS_BattleManager.battle_field.player_feet_pos[1])
	elif CCS_BattleManager.ally_teams.size() == 2: player_sprite.global_position = player_sprite.get_position_from_feet(CCS_BattleManager.battle_field.player_feet_pos[team_idx * 2])
	else: player_sprite.global_position = player_sprite.get_position_from_feet(CCS_BattleManager.battle_field.player_feet_pos[team_idx])
	
	creature.sprite = player_sprite
	player_sprite.set_camera_pos()
	
	if team_idx < player_sprites.size():
		player_sprites.set(team_idx, player_sprite)
	else:
		player_sprites.append(player_sprite)

func _creature_dead(creature : CCS_Creature):
	var sprite : CCS_CreatureSprite3D
	var team_idx : int
	
	if creature in CCS_BattleManager.ally_creatures:
		team_idx = CCS_BattleManager.ally_creatures.find(creature)
		sprite = player_sprites.get(team_idx)
	elif creature in CCS_BattleManager.opp_creatures:
		team_idx = CCS_BattleManager.opp_creatures.find(creature)
		sprite = opp_sprites.get(team_idx)
	
	await sprite.tween_offset(sprite.sprite_offset, -sprite.sprite_offset)
	sprite.queue_free()
	
	if creature in CCS_BattleManager.ally_creatures:
		CCS_BattleUIManager.set_creature_ally(null, team_idx)
	elif creature in CCS_BattleManager.opp_creatures:
		CCS_BattleUIManager.set_creature_opp(null, team_idx)

func _add_shader(creature : CCS_Creature, shader : ShaderMaterial) -> void:
	if creature in CCS_BattleManager.ally_creatures:
		player_sprites.get(CCS_BattleManager.ally_creatures.find(creature)).set_shader_override(shader)
	
	elif creature in CCS_BattleManager.opp_creatures:
		opp_sprites.get(CCS_BattleManager.opp_creatures.find(creature)).set_shader_override(shader)

#region Camera Functionality

@export_category("Camera Proporties")

@onready var camera : Camera3D = $Camera
@onready var initial_camera_rotation : Vector3 = camera.rotation_degrees
@onready var initial_camera_position : Vector3 = camera.global_position

@export var camera_shake_noise : FastNoiseLite
@export var camera_shake_max : Vector3 = Vector3(5, 5, 2)

@export var camera_trauma : Vector3 = Vector3.ZERO
var camera_shake_speed : float = 100.0
var camera_shake_time : float = 0

func _focus_camera_no_tween(creature : CCS_Creature) -> void:
	if creature:
		if creature in CCS_BattleManager.ally_creatures:
			camera.global_position = player_sprites.get(CCS_BattleManager.ally_creatures.find(creature)).focus_camera_position
		elif creature in CCS_BattleManager.opp_creatures:
			camera.global_position = opp_sprites.get(CCS_BattleManager.opp_creatures.find(creature)).focus_camera_position
	else:
		camera.global_position = initial_camera_position

func _focus_camera(creature : CCS_Creature, time : float, trans_type : Tween.TransitionType, ease_type : Tween.EaseType) -> void:
	if creature:
		if creature in CCS_BattleManager.ally_creatures:
			await tween_camera_focus(player_sprites.get(CCS_BattleManager.ally_creatures.find(creature)), time, trans_type, ease_type)
		elif creature in CCS_BattleManager.opp_creatures:
			await tween_camera_focus(opp_sprites.get(CCS_BattleManager.opp_creatures.find(creature)), time, trans_type, ease_type)
	else:
		tween_camera_original(time, trans_type, ease_type)

func tween_camera_focus(sprite : CCS_CreatureSprite3D, time : float, trans_type : Tween.TransitionType, ease_type : Tween.EaseType) -> void:
	var tween : Tween = create_tween()
	tween.set_trans(trans_type)
	tween.set_ease(ease_type)
	await tween.tween_property(camera, "global_position", sprite.focus_camera_position, time)

func tween_camera_original(time : float, trans_type : Tween.TransitionType, ease_type : Tween.EaseType) -> void:
	var tween : Tween = create_tween()
	tween.set_trans(trans_type)
	tween.set_ease(Tween.EASE_OUT)
	await tween.tween_property(camera, "global_position", initial_camera_position, time)

func get_camera_shake_intensity() -> Vector3:
	return camera_trauma * camera_trauma

func get_camera_shake_noise(seed : int) -> float:
	camera_shake_noise.seed = seed
	return camera_shake_noise.get_noise_1d(camera_shake_time * camera_shake_speed)

func _shake_camera(delta : float) -> void:
	camera_shake_time += delta
	camera.rotation_degrees = Vector3(
		initial_camera_rotation.x + camera_shake_max.x * get_camera_shake_intensity().x * get_camera_shake_noise(0),
		initial_camera_rotation.y + camera_shake_max.y * get_camera_shake_intensity().y * get_camera_shake_noise(1),
		initial_camera_rotation.z + camera_shake_max.z * get_camera_shake_intensity().z * get_camera_shake_noise(2)
	)

func _tween_camera_trauma(new_trauma : Vector3, time : float, trans_type : Tween.TransitionType, ease_type : Tween.EaseType) -> void:
	var tween : Tween = create_tween()
	tween.set_trans(trans_type).set_ease(Tween.EASE_OUT)
	tween.tween_property(self, "camera_trauma", new_trauma, time)

func _set_camera_trauma(new_trauma : Vector3) -> void:
	camera_trauma = new_trauma

#endregion

func _process(delta: float) -> void:
	_shake_camera(delta)
