extends AnimatedSprite3D
class_name CCS_CreatureSprite3D

var creature_id : String = "INVALID"
var is_back : bool = false
var sprite_offset : Vector2

var focus_camera_position : Vector3

func setup(creature : CCS_Creature, is_back_ : bool = false):
	creature_id = creature.id
	is_back = is_back_
	texture_filter = BaseMaterial3D.TextureFilter.TEXTURE_FILTER_NEAREST
	if CCS_BattleManager.loaded_creature_sprite_library():
		sprite_frames = CCS_BattleManager.creature_sprite_library
	else:
		return
	
	var end_text := "_FRONT"
	if is_back:
		end_text = "_BACK"
	
	if CCS_BattleManager.is_creature_sprite_available(creature_id + end_text):
		play(creature_id + end_text)
	
	var texture : Texture2D = sprite_frames.get_frame_texture(animation, frame)
	offset.y = texture.get_height() / 2
	sprite_offset = offset
	
	scale = Vector3.ONE * 10
	billboard = BaseMaterial3D.BILLBOARD_ENABLED
	alpha_cut = SpriteBase3D.ALPHA_CUT_DISCARD
	shaded = true

func set_shader_override(shader : ShaderMaterial) -> void:
	material_override = shader
	shader.set_shader_parameter("sprite_texture", sprite_frames.get_frame_texture(animation, frame))

func get_position_from_feet(feet_m : Marker3D) -> Vector3:
	#var ret : Vector3 = Vector3.ZERO
	#ret.x = feet_m.global_position.x
	#ret.y = feet_m.global_position.y
	#ret.z = feet_m.global_position.z
	
	return feet_m.global_position

func tween_offset(offset_old : Vector2, offset_new : Vector2, seconds : float = 0.1):
	offset = offset_old
	
	var tween : Tween = create_tween()
	tween.tween_property(self, "offset", offset_new, seconds)
	await tween.finished

func tween_scale(scale_old : Vector3, scale_new : Vector3, seconds : float = 0.1):
	scale = scale_old
	
	var tween : Tween = create_tween()
	tween.tween_property(self, "scale", scale_new, seconds)
	await tween.finished

func shrink_to_ground():
	tween_offset(sprite_offset, -sprite_offset)
	await shrink()

func grow_from_ground():
	tween_offset(-sprite_offset, sprite_offset)
	await grow()

func shrink():
	await tween_scale(Vector3.ONE * 10, Vector3.ZERO)

func grow():
	await tween_scale(Vector3.ZERO, Vector3.ONE * 10)

func set_camera_pos() -> void:
	var sprite_frame : Texture2D = sprite_frames.get_frame_texture(animation, frame)
	var distance : float = sprite_frame.get_height() if sprite_frame.get_height() > sprite_frame.get_width() else sprite_frame.get_width()
	
	focus_camera_position = global_position + CCS_BattleManager.camera_offset * distance
