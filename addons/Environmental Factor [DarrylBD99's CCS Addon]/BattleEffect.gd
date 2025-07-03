extends Node

const can_summon_stat_name : String = "CCS_EF_can_summon"

const EF_button_scene : PackedScene = preload("uid://dcixpbvj2whd7")
const EF_summon_effect_scene : PackedScene = preload("uid://de5de0dh51j06")
const EF_subside_effect_scene : PackedScene = preload("uid://dcmn784rv1kcg")
const summon_aura_shader : ShaderMaterial = preload("uid://bguqkgbrcvnh1")

const EF_shard_item : StringName = "AuraShard"
const EF_crystal_item : StringName = "NexusOrb"
const EF_strength_name : String = "Aura Potency"
const EF_duration_name : String = "Aura Pool"

const default_EF_strength : int = 1
const default_EF_duration : int = 2

const max_shards : int = 5

var EF_static_data : CCS_EF_Data
var battle_field_base : CCS_BattleField

var EF_button : Button

var EF_factor : CCS_EF_TypeData
var EF_user : CCS_Creature
var EF_turns : int = 0
var EF_users : Array[CCS_Creature]

func _ready() -> void:
	CCS_BattleManager.additional_functions["EF"] = CCS_EF_AdditionalBattleFunctions.new()
	
	CCS_BattleManager.battle_ending.connect(_battle_end)
	CCS_BattleManager.turn_end.connect(_turn_end)
	CCS_BattleManager.refresh_creature.connect(_refresh_stats)
	#CCS_BattleManager.creature_created.connect(add_ef_factor_to_creature)
	CCS_BattleManager.creature_command_created.connect(_ai_summon_ef)
		
	CCS_BattleUIManager.attack_pool_updated.connect(_add_ef_button)
	
	CCS_BattleUIManager.add_extra_stat("EF_Strength", EF_strength_name)
	CCS_BattleUIManager.add_extra_stat("EF_Duration", EF_duration_name)
	
	if CCS_BattleManager.static_data and CCS_BattleManager.static_data.extra_resources.has("EnvironmentalFactor"):
		EF_static_data = CCS_BattleManager.static_data.extra_resources.get("EnvironmentalFactor")

func add_ef_factor_to_creature(creature : CCS_Creature) -> void:
	creature.other_data.set("CCS_EF_can_summon", true)
	creature.stats.other_stats.set("EF_Strength", default_EF_strength)
	creature.stats.other_stats.set("EF_Duration", default_EF_duration)

func _creature_can_summon(creature : CCS_Creature) -> bool:
	return creature.other_data.get("CCS_EF_can_summon") and not EF_users.has(creature)

func _ai_summon_ef(creature : CCS_Creature):
	if (EF_user == null and _creature_can_summon(creature)):
		CCS_BattleManager.command_list.append(CCS_EF_BattleCommand_Summon.new(creature))

#Adds the Environmental Factor manipulation ability
func _add_ef_button(creature : CCS_Creature) -> void:
	#checks if the creature is capable of EF manipulation
	if _creature_can_summon(creature):
		if EF_button != null:
			EF_button.queue_free()
		
		EF_button = EF_button_scene.instantiate()
		EF_button.user = creature
		EF_button.disabled = (EF_user != null)
		
		CCS_BattleUIManager.attack_buttons.add_child(EF_button)
		CCS_BattleUIManager.attack_buttons.move_child(EF_button, 0)

func _play_stat_vfx(creature : CCS_Creature, _shader : ShaderMaterial = null) -> void:
	if creature.other_data.get("EF_Boost_multiplier") == null:
		return
	
	var multiplier : float = creature.other_data.get("EF_Boost_multiplier")
	if multiplier > 1:
		await CCS_BattleManager.play_battle_vfx_scene(CCS_BattleManager.stat_increase_vfx_scene, creature)
	elif multiplier < 1:
		await CCS_BattleManager.play_battle_vfx_scene(CCS_BattleManager.stat_decrease_vfx_scene, creature)

func add_visual_effect() -> void:
	if EF_user and EF_factor:
		#var shader_array : Array[ShaderMaterial]
		for creature : CCS_Creature in CCS_BattleManager.ally_creatures:
			await _play_stat_vfx(creature)
		
		for creature : CCS_Creature in CCS_BattleManager.opp_creatures:
			await _play_stat_vfx(creature)
		
func remove_visual_effect() -> void:
	pass

func set_ef_type_factor(user : CCS_Creature, type : StringName) -> void:
	if EF_static_data != null:
		EF_user = user
		EF_users.append(user)
		
		EF_factor = EF_static_data.type_factors.get(type)
		EF_factor = EF_factor.duplicate(true)
		
		if not EF_user.stats.other_stats.has("EF_Strength"):
			EF_user.stats.other_stats.set("EF_Strength", default_EF_duration)
		
		EF_factor.base_boost_multiplier *= EF_user.stats.other_stats.get("EF_Strength")
		EF_factor.base_defect_multiplier *= EF_user.stats.other_stats.get("EF_Strength")
		
		battle_field_base = CCS_BattleManager.battle_field.duplicate()
		
		await CCS_BattleManager.play_battle_vfx_scene(EF_summon_effect_scene, EF_user)

		CCS_BattleManager.add_shader.emit(EF_user, summon_aura_shader.duplicate(true))
		
		CCS_BattleManager.battle_field = load(EF_factor.arena_uid.resource_uid).instantiate()
		await CCS_BattleManager.battle_field.battlefield_entered
		
		_refresh_stats()
		
		if not EF_user.stats.other_stats.has("EF_Duration"):
			EF_user.stats.other_stats.set("EF_Duration", default_EF_duration)
		
		EF_turns = EF_user.stats.other_stats.get("EF_Duration")

func remove_ef_type_factor() -> void:
	EF_user = null
	EF_factor = null
	
	if battle_field_base != null:
		var EF_subside_effect : CCS_BattleVFX = EF_subside_effect_scene.instantiate()
		EF_subside_effect.battle_fields.append(battle_field_base)
		add_child(EF_subside_effect)
		await CCS_BattleUIManager.transition_middle
		remove_visual_effect()
		await CCS_BattleUIManager.transition_end
		battle_field_base = null
	
	_refresh_stats()

func ef_clash(environments : Array[CCS_EF_BattleCommand_Summon]) -> void:
	await _refresh_stats_base()
	
	for environment : CCS_EF_BattleCommand_Summon in environments:
		var user : CCS_Creature = environment.user
		
		if not user.stats.other_stats.has("EF_Strength"):
			user.stats.other_stats.set("EF_Strength", default_EF_duration)

		var factor : CCS_EF_TypeData = EF_static_data.type_factors.get(environment.EF_Type)
		var boost_multiplier : float = factor.base_boost_multiplier * user.stats.other_stats.get("EF_Strength")
		
		user.stats.power = round(boost_multiplier * user.stats.power)
		user.stats.speed = round(boost_multiplier * user.stats.speed)

func _refresh_stats_base() -> void:
	for creature : CCS_Creature in CCS_BattleManager.ally_creatures:
		if creature == null:
			continue
		
		creature.stats.calculate_stats(creature.id)
		creature.other_data.set("EF_Boost_multiplier", 1.0)
	
	for creature : CCS_Creature in CCS_BattleManager.opp_creatures:
		if creature == null:
			continue
		
		creature.stats.calculate_stats(creature.id)
		creature.other_data.set("EF_Boost_multiplier", 1.0)

func _refresh_stats() -> void:
	await _refresh_stats_base()
	
	_set_effect()

func _set_effect() -> void:
	if EF_factor:
		for creature : CCS_Creature in CCS_BattleManager.ally_creatures:
			_boost_stats(creature)

		for creature : CCS_Creature in CCS_BattleManager.opp_creatures:
			_boost_stats(creature)

func _boost_stats(creature : CCS_Creature) -> void:
	if creature == null:
		return
		
	if EF_factor:
		var species : CCS_StaticData_Creature = creature.get_species_static_data()
		
		if species:
			var boost_multiplier : float = 1.0
			for type : StringName in species.types:
				if EF_factor.boosted_types.has(type): boost_multiplier *= EF_factor.base_boost_multiplier
				if EF_factor.defective_types.has(type): boost_multiplier *= EF_factor.base_defect_multiplier
			
			creature.other_data.set("EF_Boost_multiplier", boost_multiplier)
			creature.stats.power = round(creature.stats.power * boost_multiplier)
			creature.stats.speed = round(creature.stats.speed * boost_multiplier)

func _battle_end(_islose : bool) -> void:
	EF_factor = null
	EF_user = null
	EF_users.clear()
	
	_refresh_stats()

func _turn_end() -> void:
	if EF_user != null:
		EF_turns -= 1
		
		if EF_turns <= 1:
			CCS_BattleManager.command_list.append(CCS_EF_BattleCommand_Fade.new(EF_user))
