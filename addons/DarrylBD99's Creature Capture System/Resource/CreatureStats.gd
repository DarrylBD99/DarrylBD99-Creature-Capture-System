extends Resource
class_name CCS_CreatureStats

@export_range(1, 20) var power_iv := randi_range(1, 20)
@export_range(1, 20) var defense_iv := randi_range(1, 20)
@export_range(1, 20) var speed_iv := randi_range(1, 20)
@export_range(1, 20) var health_point_iv := randi_range(1, 20)

@export var stamina := 5
@export var other_stats : Dictionary

@export var level : int = 1

signal stat_calculated

var power_offset : int
var defense_offset : int
var speed_offset : int
var health_point_offset : int

var power : int
var defense : int
var speed : int
var health_point : int

var xp_goal : int

func _init() -> void:
	call_deferred("_ready")

func _ready() -> void:
	set_xp_goal()

func calculate_stats(creature_id : StringName) -> void:
	var creature_static_data : CCS_StaticData_Creature = CCS_BattleManager.static_data.creatures.get(creature_id)
	
	power = CCS_BattleManager.calculate_stat(creature_static_data.power, power_iv, level, power_offset)
	defense = CCS_BattleManager.calculate_stat(creature_static_data.defense, defense_iv, level, defense_offset)
	speed = CCS_BattleManager.calculate_stat(creature_static_data.speed, speed_iv, level, speed_offset)
	health_point = CCS_BattleManager.calculate_stat(creature_static_data.health_point, health_point_iv, level, health_point_offset)
	
	stat_calculated.emit()

func refresh(creature_id : StringName) -> void:
	power_offset = 0
	defense_offset = 0
	speed_offset = 0
	health_point_offset = 0
	
	calculate_stats(creature_id)
	

func set_xp_goal() -> void:
	xp_goal = 2 * level

func set_stats(stats : CCS_CreatureStats) -> void:
	power = stats.power
	defense = stats.defense
	speed = stats.speed
	health_point = stats.health_point
	stamina = stats.stamina

static func generate_stats_from_creature_data(creature_id : StringName, level : int = 1) -> CCS_CreatureStats:
	var stats : CCS_CreatureStats = new()
	stats.level = level
	stats.refresh(creature_id)
	
	return stats
