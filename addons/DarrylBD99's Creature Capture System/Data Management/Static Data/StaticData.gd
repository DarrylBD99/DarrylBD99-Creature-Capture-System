extends Resource
class_name CCS_StaticData

@export var calc_variables : Dictionary
#@export var item_types : Dictionary[StringName, CCS_ItemType]

@export var creatures : Dictionary[StringName, CCS_StaticData_Creature]
@export var types : Dictionary[StringName, CCS_StaticData_Type]
@export var attacks : Dictionary[StringName, CCS_StaticData_Attack]
@export var items : Dictionary[StringName, CCS_StaticData_Item]

@export var extra_resources : Dictionary[StringName, CCS_AdditionalResource]

func _init() -> void:
	call_deferred("_ready")

func _ready() -> void:
	for creature_id : StringName in creatures:
		creatures[creature_id].id = creature_id
	
	for types_id : StringName in types:
		types[types_id].id = types_id
	
	for attacks_id : StringName in attacks:
		attacks[attacks_id].id = attacks_id
	
	for items_id : StringName in items:
		items[items_id].id = items_id

func get_item_data(item_id : StringName) -> CCS_StaticData_Item:
	return items.get(item_id)
