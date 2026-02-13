extends GPUParticles3D

func _ready():
	emitting = true

func _on_finish() -> void:
	queue_free()
