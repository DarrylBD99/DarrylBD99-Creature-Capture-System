extends Control
class_name CCS_HUDPanel

enum HPColor {
	GREEN,
	ORANGE,
	RED
}

@export var panel_selected : StyleBox
@export var panel_unselected : StyleBox

@export var green_col : Color = Color(0.0, 0.71, 0.49)
@export var orange_col : Color = Color(0.831, 0.557, 0.173)
@export var red_col : Color = Color(1.0, 0.278, 0.278)

@onready var name_label : Label = %Name
@onready var level_label : Label = %Level
@onready var health_bar : ProgressBar = %HealthBar
@onready var xp_bar : ProgressBar = %XPBar

var is_tweening : bool = false
var new_health : int
var is_selected : bool = false

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

var creature : CCS_Creature :
	set(val):
		if val:
			new_health = val.get_health_percent()
			
			name_label.text = val.get_creature_name()
			level_label.text = "Lvl. " + str(val.stats.level)
			show()
		else:
			new_health = 100
			hide()
		
		health_bar.value = new_health
		creature = val

const panel_scene : PackedScene = preload("uid://b8345ptc3gg3x")

func _ready() -> void:
	CCS_BattleManager.leveled_up.connect(_update_level)
	
	if has_theme_stylebox_override("panel"):
		add_theme_stylebox_override("panel", panel_unselected)
	
	health_bar_stylebox = StyleBoxFlat.new()
	health_bar_stylebox.set_corner_radius_all(4)
	
	health_bar.value_changed.connect(_update_health_bar_color)
	health_bar.add_theme_stylebox_override("fill", health_bar_stylebox)
	new_health = health_bar.value
	hide()

func _process(_delta: float) -> void:
	if not creature:
		return
	
	if has_theme_stylebox_override("panel"):
		if CCS_BattleUIManager.user == creature and not is_selected:
			add_theme_stylebox_override("panel", panel_selected)
			is_selected = true
		elif is_selected:
			add_theme_stylebox_override("panel", panel_unselected)
			is_selected = false
	
	new_health = creature.get_health_percent()
	
	xp_bar.value = creature.get_xp_percent()
	
	if new_health != health_bar.value and not is_tweening:
		_update_health()

func _update_health_bar_color(new_val : float) -> void:
	if new_val < 25:
		health_bar_color = HPColor.RED
	elif new_val < 50:
		health_bar_color = HPColor.ORANGE
	else:
		health_bar_color = HPColor.GREEN

func _update_level(leveled_up_creature : CCS_Creature) -> void:
	if creature == leveled_up_creature:
		level_label.text = "Lvl. " + str(creature.stats.level)

func _update_health() -> void:
	is_tweening = true
	var tween : Tween = create_tween()
	tween.set_ease(Tween.EASE_OUT).set_trans(Tween.TRANS_QUART)
	
	tween.tween_property(health_bar, "value", new_health, 0.3)
	await tween.finished
	is_tweening = false

static func create_new_panel() -> CCS_HUDPanel:
	return panel_scene.instantiate() as CCS_HUDPanel
