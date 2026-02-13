extends Button
class_name CCS_BattleUI_ItemButton

signal item_selected(item_id : StringName)

const text_format : String = "{name} x{quantity}"

var item_name : String
		
var item_quantity : int = 1:
	set(val):
		item_quantity = val
		text = text_format.format({"name" : item_name, "quantity" : item_quantity})

func _init(item_id : StringName, item_quantity : int = 1) -> void:
	name = item_id
	icon = CanvasTexture.new()
	alignment = HORIZONTAL_ALIGNMENT_LEFT
	expand_icon = true
	custom_minimum_size.y = 60
	
	var item_data : CCS_StaticData_Item = CCS_BattleManager.static_data.items.get(item_id)
	if item_data:
		item_name = item_data.name
		icon = item_data.item_icon
	else:
		item_name = item_id
		push_error("Error: Item ID {0} not defined".format([item_id]))
		
	self.item_quantity = item_quantity

func _pressed() -> void:
	item_selected.emit(name)
