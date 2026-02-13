@tool
@icon("./editor_icon.svg")

extends MarginContainer
class_name CCS_EditorUI

@export var data_management_container : CCS_DataManagement
@export var tab_container : TabContainer
@onready var static_data : CCS_StaticDataEdit = %StaticData
