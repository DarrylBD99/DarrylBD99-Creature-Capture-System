extends ProgressBar

enum HPColor {
	GREEN,
	ORANGE,
	RED
}

@export var green_col : Color = Color(0.0, 0.71, 0.49)
@export var orange_col : Color = Color(0.831, 0.557, 0.173)
@export var red_col : Color = Color(1.0, 0.278, 0.278)

var health_bar_stylebox : StyleBoxFlat
var health_bar_color : HPColor :
	set(val):
		match val:
			HPColor.GREEN:
				health_bar_stylebox.bg_color = green_col
			HPColor.ORANGE:
				health_bar_stylebox.bg_color = orange_col
			HPColor.RED:
				health_bar_stylebox.bg_color = red_col
		
		health_bar_color = val

func _ready() -> void:
	health_bar_stylebox = StyleBoxFlat.new()
	health_bar_stylebox.set_corner_radius_all(4)
	add_theme_stylebox_override("fill", health_bar_stylebox)
	value_changed.connect(_update_color)

func _update_color(health : int) -> void:
	if health < 25:
		health_bar_color = HPColor.RED
	elif health < 50:
		health_bar_color = HPColor.ORANGE
	else:
		health_bar_color = HPColor.GREEN
	
