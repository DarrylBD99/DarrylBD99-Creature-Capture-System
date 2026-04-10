extends GridContainer


var ui_open : bool
@onready var bag : PanelContainer = %bag
@onready var creatures: PanelContainer = %Creatures

func _ready() -> void:
	bag.hide()
	creatures.hide()
	ui_open = false


func _on_fight_button_pressed() -> void:
	## fight menu logic eg. tween or unhide the menu
	pass

## creatures
func _on_creatures_button_pressed() -> void:
	if !ui_open:
		ui_open = true
		creatures.show()
func _on_creatures_close_button_pressed() -> void:
	creatures.hide()
	ui_open = false

## bag
func _on_bag_button_pressed() -> void:
	if !ui_open:
		ui_open = true
		bag.show()
func _on_bag_close_button_pressed() -> void:
	bag.hide()
	ui_open = false


func _on_flee_button_pressed() -> void:
	## flee logic, eg. CSS_Battle.attempt_flee()
	pass 
