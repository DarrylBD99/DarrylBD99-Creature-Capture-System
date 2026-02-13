extends Button
class_name CCS_BattleUI_TargetButton

const base_text : String = "{creature} Lv. {level}"
var creature : CCS_Creature

func _init(creature : CCS_Creature) -> void:
	self.creature = creature
	if creature == null or creature.is_dead():
		disable_button()
	else:
		enable_button()

func _ready() -> void:
	mouse_entered.connect(func(): grab_focus())

func disable_button() -> void:
	disabled = true
	text = "---"
	focus_mode = Control.FOCUS_NONE

func enable_button() -> void:
	disabled = false
	text = base_text.format({
		"creature" : creature.get_creature_name(),
		"level" : creature.stats.level,
	})
	focus_mode = Control.FOCUS_ALL

func _pressed() -> void:
	CCS_BattleUIManager.target_selected.emit(creature)
