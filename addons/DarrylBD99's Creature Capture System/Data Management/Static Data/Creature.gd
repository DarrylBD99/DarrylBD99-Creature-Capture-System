extends Resource
class_name CCS_Creature

var last_taken_damage : int = 0
var last_taken_dealt : int = 0
var sprite : CCS_CreatureSprite3D

@export var id : StringName
@export var nickname : String
@export var stats : CCS_CreatureStats

@export_range(0, 1, 1, "or_greater") var health : int
@export_range(0, 1, 1, "or_greater") var xp : float = 0

@export var learned_attacks : Array[StringName]
@export var attack_pool : Array[StringName]
@export var other_data : Dictionary

func _init() -> void:
	CCS_BattleManager.battle_end.connect( func(_is_lose): last_taken_damage = 0 )
	CCS_BattleManager.stat_offset.connect( func(creature, stat_key, offset):
		if self != creature:
			return
		
		offset_stat(stat_key, offset)
	)
	
	call_deferred("reset_creature")

func damage(dmg : int) -> void:
	last_taken_damage = dmg
	health -= dmg

func level_up() -> void:
	while xp >= stats.xp_goal:
		stats.level += 1
		xp -= stats.xp_goal
		stats.set_xp_goal()
	
	var health_old : int = stats.health_point
	stats.calculate_stats(id)
	var health_offset : int = stats.health_point - health_old
	
	if health_offset > 0:
		health += health_offset

func get_random_attack_id() -> StringName:
	return attack_pool.pick_random()

func is_dead() -> bool:
	return health <= 0

func get_health_percent() -> int:
	@warning_ignore("integer_division")
	return health * 100 / stats.health_point

func get_xp_percent() -> int:
	return xp * 100 / stats.xp_goal

func get_creature_name() -> String:
	if !nickname.is_empty():
		return nickname
	return get_creature_species_name()

func get_creature_species_name() -> String:
	var creature : CCS_StaticData_Creature = get_species_static_data()
	
	if creature == null:
		push_error("Error: Creature ID {} not found in Static Data".format([id]))
		return id
	
	return creature.name

func get_species_static_data() -> CCS_StaticData_Creature:
	return CCS_BattleManager.static_data.creatures.get(id)

func offset_stat(stat_key : StringName, offset : int) -> void:
	match stat_key:
		"POWER":
			stats.power_offset += offset
		"DEFENSE":
			stats.defense_offset += offset
		"SPEED":
			stats.speed_offset += offset
		"HEALTH_POINT":
			stats.health_point_offset += offset
	
	stats.calculate_stats(id)

func reset_health() -> void:
	health = stats.health_point

func heal(heal_amount : int) -> void:
	health += heal_amount
	
	if health > stats.health_point:
		health = stats.health_point

func reset_creature() -> void:
	stats.refresh(id)

func get_xp_needed() -> int:
	return stats.xp_goal - xp

func can_learn_attacks() -> Array[StringName]:
	var creature_static_data : CCS_StaticData_Creature = get_species_static_data()
	var attack_list : Array[StringName]
	
	for attack : StringName in creature_static_data.attack_pool:
		if creature_static_data.attack_pool[attack] > stats.level:
			continue
		
		if not learned_attacks.has(attack):
			attack_list.append(attack)
	
	return attack_list

static func create_creature(id : StringName, level : int) -> CCS_Creature:
	var creature : CCS_Creature = new()
	
	creature.id = id
	creature.stats = CCS_CreatureStats.generate_stats_from_creature_data(id, level)
	creature.reset_health()
	var attack_list : Array[StringName] = creature.can_learn_attacks()
	
	while attack_list.size() > CCS_BattleManager.max_attack_pool_size:
		var removed_attack : StringName = attack_list.pick_random()
		attack_list.erase(removed_attack)
	
	creature.attack_pool = attack_list
	creature.learned_attacks = attack_list
	
	return creature
