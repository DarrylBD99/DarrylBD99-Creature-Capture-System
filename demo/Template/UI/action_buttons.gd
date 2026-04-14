extends GridContainer


var ui_open : bool
@onready var bag : PanelContainer = %bag
@onready var creatures: PanelContainer = %Creatures
@onready var moves_container: GridContainer = $"../MovesContainer"


func _ready() -> void:
	bag.hide()
	creatures.hide()
	moves_container.hide()
	ui_open = false


func _on_fight_button_pressed() -> void:
	moves_container.show()
	bag.hide()
	creatures.hide()
	hide()
	ui_open = false
func _on_moves_back_button_pressed() -> void:
	moves_container.hide()
	show()


## creatures
func _on_creatures_button_pressed() -> void:
	if !ui_open:
		ui_open = true
		creatures.show()
	elif creatures.visible:
		ui_open = false
		creatures.hide()
func _on_creatures_close_button_pressed() -> void:
	creatures.hide()
	ui_open = false

## bag
func _on_bag_button_pressed() -> void:
	if !ui_open:
		ui_open = true
		bag.show()
	elif bag.visible:
		ui_open = false
		bag.hide()
func _on_bag_close_button_pressed() -> void:
	bag.hide()
	ui_open = false

func _on_flee_button_pressed() -> void:
	## flee logic, eg. CSS_Battle.attempt_flee()
	pass 
