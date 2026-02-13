extends Button
class_name CCS_BattleUI_CreatureButton

signal creature_selected(creature : CCS_Creature)

@onready var hud_panel : CCS_HUDPanel = %HUDPanel
@onready var creature_icon : TextureRect = %Icon

var creature : CCS_Creature :
	set(val):
		if val == null:
			disabled = true
			focus_mode = Control.FOCUS_NONE
		else:
			disabled = false
			focus_mode = Control.FOCUS_ALL
			
			var species_data : CCS_StaticData_Creature = CCS_BattleManager.static_data.creatures.get(val.id)
			if creature_icon:
				creature_icon.texture = species_data.creature_icon
		
		hud_panel.creature = val
	get():
		return hud_panel.creature

func _pressed() -> void:
	creature_selected.emit(creature)
