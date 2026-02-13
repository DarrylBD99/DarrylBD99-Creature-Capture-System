extends CharacterBody3D
class_name NPC

@onready var sprite : AnimatedSprite3D = $AnimatedSprite3D
@onready var collision : CollisionShape3D = $CollisionShape3D

@export var dialogue : Array[String]

var disabled : bool = false

func _ready() -> void:
	change_visible(visible)

func change_visible(visible_new : bool) -> void:
	visible = visible_new
	
	if collision:
		collision.disabled = not visible_new

func talk(facing : Vector3) -> void:
	if disabled:
		return
	
	_face_direction(facing)
	
	await Game_DialogueBox.display_dialogue(dialogue)
	
func _face_direction(facing : Vector3) -> void:
	if facing == Vector3.FORWARD:
		sprite.play("IDLE_UP")
	elif facing == Vector3.BACK:
		sprite.play("IDLE_DOWN")
	elif facing == Vector3.LEFT:
		sprite.play("IDLE_LEFT")
	elif facing == Vector3.RIGHT:
		sprite.play("IDLE_RIGHT")
