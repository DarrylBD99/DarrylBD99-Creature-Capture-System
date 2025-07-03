extends Node

@warning_ignore("unused_signal")
signal save_created
signal save_loaded
signal all_saves_found

signal battle_starting
signal battle_initialized
signal battle_start

signal battle_field_change(battle_field : CCS_BattleField)
signal creature_created(creature : CCS_Creature)
signal creature_command_created(creature : CCS_Creature)
signal creature_dead(creature : CCS_Creature)
signal refresh_creature
signal damage_dealt(user : CCS_Creature, target : CCS_Creature, damage : int)
signal creature_summon(creature : Array[CCS_Creature])
signal creature_retrieve(creature : CCS_Creature)
signal add_shader(target : CCS_Creature, shader : ShaderMaterial)
signal leveled_up(creature : CCS_Creature)
signal add_command(command : CCS_BattleCommandBase)
signal captured_creature(creature : CCS_Creature)
signal forget_attack(attack_idx : int)

#Camera Signals
signal focus_camera(creature : CCS_Creature, time : float, trans_type : Tween.TransitionType, type : Tween.EaseType)
signal focus_camera_no_tween(creature : CCS_Creature)
signal camera_shake_tween(trauma : Vector3, time : float, trans_type : Tween.TransitionType, type : Tween.EaseType)
signal camera_shake_instant(trauma : Vector3, time : float)
signal camera_shake(trauma : Vector3)

signal switch_creature(team : CCS_BattleTeam, from : CCS_Creature, to : CCS_Creature)

signal turn_off_lights
signal turn_on_lights

signal turn_end
signal battle_ending(is_lose : bool)
signal battle_end(is_lose : bool)

signal stat_offset(creature : CCS_Creature, stat_key : StringName, offset : int)

@onready var rng : RandomNumberGenerator = RandomNumberGenerator.new()

var ally_teams : Array[CCS_BattleTeam]
var opp_teams : Array[CCS_BattleTeam]

var ally_creatures : Array[CCS_Creature]
var opp_creatures : Array[CCS_Creature]

var ally_dead : Array[bool]
var opp_dead : Array[bool]

var is_wild : bool = false
var is_boss : bool = false
var is_in_battle : bool = false

# for dialogue message
var is_critical_hit : bool
var is_resistant : bool
var is_weak : bool
var is_lose : bool

# for camera position
var camera_offset : Vector3 = Vector3(.15, .04, .12)

# misc
var battle_field : CCS_BattleField:
	set(value):
		if battle_field != null:
			battle_field.queue_free()
		
		battle_field = value
		battle_field_change.emit(value)
	
var command_list : Array[CCS_BattleCommandBase] = []

var additional_functions : Dictionary[StringName, CCS_AdditionalBattleFunctions]

var creature_stream : Array[AudioStreamPlayer]

const max_team_size : int = 6
const max_attack_pool_size : int  = 4
const creature_sprite_library : SpriteFrames = preload("uid://cksut75sirb75")

const hit_vfx_scene : PackedScene = preload("uid://bo4wcpqvk5usg")
const stat_increase_vfx_scene : PackedScene = preload("uid://bcsiwlasr6ueq")
const stat_decrease_vfx_scene : PackedScene = preload("uid://dybowdjvd04yv")
const heal_vfx_scene : PackedScene = preload("uid://d1mnakusrfwio")
const capture_vfx_scene : PackedScene = preload("uid://dmk7bhi2ww5nb")

const boss_battle_text : Array[String] = ["{creatures} challenges you to a battle!"]
const wild_battle_text : Array[String] = ["Wild {creatures} has appeared!"]
const opponent_battle_text : Array[String] = ["{name} has issued a battle!"]
const send_out_text : Array[String] = ["{name} sends out {creature}."]
const retrieve_text : Array[String] = ["{name} retrieves {creature}."]
const same_swap_error_text : Array[String] = ["Cannot swap {creature} into the same position."]

const trainer_flee_text : Array[String] = ["Hey! There is no running from a trainer battle!"]
const cant_escape_text : Array[String] = ["Can't escape!"]
const already_in_battlefield_text : Array[String] = ["{creature} is already in the battlefield."]
const creature_dead_text : Array[String] =["{creature} is unable to battle."]

const dead_text : Array[String] = ["{creature} has fainted."]
const xp_text : Array[String] = ["{creature} gained {xp} xp."]
const level_text : Array[String] = ["{creature} leveled up to level {level}!"]

const stat_increase_text : Array[String] = ["{creature}'s {stat} increased!"]
const stat_decrease_text : Array[String] = ["{creature}'s {stat} decreased."]

const capture_success_dialogue : Array[String] = ["Yay! {creature} was caught!"]
const capture_fail_dialogue : Array[String] = ["{creature} broke free!"]

const attack_pool_full_dialogue : Array[String] = ["{creature} wants to learn {new_attack}, but already knows {max_attack} attacks.", "Please select an attack for {new_attack} to forget"]
const forgot_attack_dialogue : Array[String] = ["{creature} forgotten how to use {old_attack}..."]
const learned_attack_dialogue : Array[String] = ["{creature} learned {new_attack}!"]
const learn_fail_attack_dialogue : Array[String] = ["{creature} did not learned {new_attack}."]

const static_data : CCS_StaticData = preload("res://Example/data.res")

const gain_xp_sound : AudioStream = preload("uid://2ooewtkwep6u")
const level_up_sound : AudioStream = preload("uid://dx3dns8sce5q8")
const level_up_success_sound : AudioStream = preload("uid://xlcub42yi7ht")

const stat_offset_minimum : int = -3
const stat_offset_maximum : int = 3

func _ready() -> void:
	battle_start.connect(_generate_turn)
	turn_end.connect(_generate_turn)
	refresh_creature.connect(_refresh_creatures)
	switch_creature.connect(creature_switched)

func _play_creature_sounds(species_ids : Array[StringName]) -> void:
	for species_id : StringName in species_ids:
		play_creature_sound(species_id)
	
	while not creature_stream.is_empty():
		await get_tree().process_frame

func play_creature_sound(species_id : StringName) -> void:
	var sound : AudioStream = static_data.creatures.get(species_id).sound
	if sound != null:
		await play_sound(sound)

func play_sound(sound : AudioStream) -> void:
	var stream_player : AudioStreamPlayer = AudioStreamPlayer.new()
	creature_stream.append(stream_player)
	stream_player.stream = sound
	add_child(stream_player)
	stream_player.play()
	
	await stream_player.finished
	creature_stream.erase(stream_player)
	stream_player.queue_free()

func battle_boss_wild(boss_creature : CCS_Creature, player_amount : int  = 2):
	is_in_battle = true
	is_wild = true
	is_boss = true
	
	var boss_team : CCS_BattleTeam = CCS_BattleTeam.new()
	var index : int = 0
	
	creature_created.emit(boss_creature)

	boss_team.creature_list.append(boss_creature)
	opp_teams.append(boss_team)
	
	boss_team.send_out_creature(boss_creature, boss_team.creature_list.size() - 1)
	
	for idx : int in opp_teams.size():
		ally_teams.append(CCS_PlayerData.get_team())
	
	opp_teams = _set_side([boss_team], boss_team.creature_list.size())
	ally_teams = _set_side([CCS_PlayerData.get_team()], player_amount)
	
	if CCS_BattleUIManager.play_transition("wild_fade"):
		battle_starting.emit()
		await CCS_BattleUIManager.transition_middle
	
		battle_initialized.emit()
		refresh_creature.emit()
		
		if opp_creatures.size() == 1:
			focus_camera_no_tween.emit(opp_creatures.get(0))
		
		await CCS_BattleUIManager.transition_end
	else:
		battle_starting.emit()
		battle_initialized.emit()
		refresh_creature.emit()
		
		if opp_creatures.size() == 1:
			focus_camera_no_tween.emit(opp_creatures.get(0))
	
	await _opponent_battle_text()
	focus_camera.emit(null, 0.2, Tween.TRANS_CUBIC, Tween.EASE_OUT)
	
	await _send_out_teams(ally_teams)
	
	battle_start.emit()

func battle_wild(creature_datas : Array[Dictionary], ally_count : int = 1):
	is_in_battle = true
	is_wild = true
	is_boss = false
	
	var wild_team : CCS_BattleTeam = CCS_BattleTeam.new()
	var index : int = 0
	
	for creature_data : Dictionary in creature_datas:
		var opp_creature : CCS_Creature = CCS_Creature.create_creature(creature_data.get("species"), creature_data.get("level"))
		
		if creature_data.has("stats") != null and creature_data.get("stats") is CCS_CreatureStats:
			opp_creature.stats = creature_data.get("stats")
		
		creature_created.emit(opp_creature)
	
		wild_team.creature_list.append(opp_creature)
		opp_teams.append(wild_team)
		
		wild_team.send_out_creature(opp_creature, wild_team.creature_list.size() - 1)
	
	for idx : int in opp_teams.size():
		ally_teams.append(CCS_PlayerData.get_team())
	
	opp_teams = _set_side([wild_team], wild_team.creature_list.size())
	ally_teams = _set_side([CCS_PlayerData.get_team()], ally_count)
	
	if CCS_BattleUIManager.play_transition("wild_fade"):
		battle_starting.emit()
		await CCS_BattleUIManager.transition_middle
	
		battle_initialized.emit()
		refresh_creature.emit()
		focus_camera_no_tween.emit(opp_creatures.get(opp_creatures.size() - 1))
		
		await CCS_BattleUIManager.transition_end
	else:
		battle_starting.emit()
		battle_initialized.emit()
		refresh_creature.emit()
		focus_camera_no_tween.emit(opp_creatures.get(opp_creatures.size() - 1))
	
	await _opponent_battle_text()
	focus_camera.emit(null, 0.2, Tween.TRANS_CUBIC, Tween.EASE_OUT)
	
	await _send_out_teams(ally_teams)
	
	battle_start.emit()

func trainer_battle(opponents : Array[CCS_BattleTeam]):
	is_in_battle = true
	is_wild = false
	is_boss = false
	
	var creature_count : int = opponents.size()
	var opponent_list : Array[CCS_BattleTeam]
	
	for team_idx : int in opponents.size():
		var opponent : CCS_BattleTeam = opponents.get(team_idx)

		if opponent in opponent_list:
			var list_idx : int = opponent_list.find(opponent)
			opponents.set(team_idx, opponents.get(list_idx))
		else:
			opponent_list.append(opponent)
			opponents.set(team_idx, opponent.duplicate(true))
	
	opp_teams = _set_side(opponents, creature_count)
	ally_teams = _set_side([CCS_PlayerData.get_team()], creature_count)
	
	if CCS_BattleUIManager.play_transition("black_fade"):
		battle_starting.emit()
		await CCS_BattleUIManager.transition_middle
		battle_initialized.emit()
		await CCS_BattleUIManager.transition_end
	else:
		battle_starting.emit()
		battle_initialized.emit()
	
	await _opponent_battle_text()
	
	await _send_out_teams(opp_teams)
	await _send_out_teams(ally_teams)
	
	battle_start.emit()

func get_stat_offset(creature : CCS_Creature, stat : StringName) -> int:
	match stat:
		"power":
			return creature.stats.power_offset
		"defense":
			return creature.stats.defense_offset
		"speed":
			return creature.stats.speed_offset
		_:
			return 0

func update_stat(creature : CCS_Creature, stat : StringName, counter : int) -> void:
	match stat:
		"power":
			creature.stats.power_offset += counter
			if creature.stats.power_offset < stat_offset_minimum:
				creature.stats.power_offset = stat_offset_minimum
			elif creature.stats.power_offset > stat_offset_maximum:
				creature.stats.power_offset = stat_offset_maximum
		"defense":
			creature.stats.defense_offset += counter
			if creature.stats.defense_offset < stat_offset_minimum:
				creature.stats.defense_offset = stat_offset_minimum
			elif creature.stats.defense_offset > stat_offset_maximum:
				creature.stats.defense_offset = stat_offset_maximum
		"speed":
			creature.stats.speed_offset += counter
			if creature.stats.speed_offset < stat_offset_minimum:
				creature.stats.speed_offset = stat_offset_minimum
			elif creature.stats.speed_offset > stat_offset_maximum:
				creature.stats.speed_offset = stat_offset_maximum
		_:
			pass
	
	var text : Array[String]
	if counter > 0:
		CCS_BattleManager.play_battle_vfx_scene(CCS_BattleManager.stat_increase_vfx_scene, creature)
		text = stat_increase_text
	elif counter < 0:
		CCS_BattleManager.play_battle_vfx_scene(CCS_BattleManager.stat_decrease_vfx_scene, creature)
		text = stat_decrease_text
	
	var format : Dictionary = {
		"creature" : creature.get_creature_name(),
		"stat" : stat,
	}
	await CCS_BattleUIManager.create_dialogue(text, format)

func learn_new_attacks(creature : CCS_Creature) -> void:
	var new_attacks : Array[StringName] = creature.can_learn_attacks()
	if new_attacks.is_empty():
		return
	
	var format : Dictionary = {
		"creature" : creature.get_creature_name(),
		"max_attack" : max_attack_pool_size,
	}
	
	for new_attack : StringName in new_attacks:
		if creature.attack_pool.has(new_attack):
			creature.learned_attacks.append(new_attack)
			continue
		
		format["new_attack"] = static_data.attacks.get(new_attack).name
		
		if creature.attack_pool.size() >= max_attack_pool_size:
			await CCS_BattleUIManager.create_dialogue(attack_pool_full_dialogue, format)
			var attack_idx : int = await forget_attack
			if attack_idx < 0:
				await CCS_BattleUIManager.create_dialogue(learn_fail_attack_dialogue, format)
				return
			
			format["old_attack"] = static_data.attacks.get(creature.attack_pool.get(attack_idx)).name
			creature.attack_pool.set(attack_idx, new_attack)
			await CCS_BattleUIManager.create_dialogue(forgot_attack_dialogue, format)
		else:
			creature.attack_pool.append(new_attack)
		
		await CCS_BattleUIManager.create_dialogue(learned_attack_dialogue, format)

func _refresh_creatures() -> void:
	ally_creatures = _get_current_creatures(ally_teams)
	opp_creatures = _get_current_creatures(opp_teams)

func _send_out_teams(teams : Array[CCS_BattleTeam]) -> void:
	var team_list : Dictionary[CCS_BattleTeam, int] = {}
	var creatures : Array[CCS_Creature]
	
	var team_names : Array[String]
	var creature_names : Array[String]
	var creature_ids : Array[StringName]
	
	for team : CCS_BattleTeam in teams:
		if not team_list.has(team):
			team_list[team] = 0
			team_names.append(team.get_trainer_name())
		
		var creature : CCS_Creature
		
		while creature == null or creature.is_dead():
			if team_list.get(team) >= team.creature_list.size():
				break
			
			creature = team.get_creature(team_list.get(team))
			team_list[team] += 1
		
		if creature == null or creature.is_dead():
			creatures.append(null)
			continue
		
		creature_names.append(creature.get_creature_name())
		creatures.append(creature)
	
	var format : Dictionary = {
		"name" : _get_name_string(team_names),
		"creature" : _get_name_string(creature_names)
	}
	
	await CCS_BattleUIManager.create_dialogue(send_out_text, format)
	
	for idx : int in creatures.size():
		var creature : CCS_Creature = creatures.get(idx)
		if creature == null:
			continue
		creature_ids.append(creature.id)
		teams[idx].send_out_creature(creature, idx)
		
	
	refresh_creature.emit()
	creature_summon.emit(creatures)
	
	await _play_creature_sounds(creature_ids)
	
func _get_name_string(names : Array[String]) -> String:
	var name_string : String
	
	for idx : int in names.size():
		if not name_string.is_empty():
			if idx < (names.size() - 1):
				name_string += ", "
			else:
				name_string += " and "
		name_string += names[idx]
	
	return name_string

func get_teams_name_string(teams : Array[CCS_BattleTeam]) -> String:
	var names : Array[String]
	var iterated_teams : Array[CCS_BattleTeam]
	
	for team : CCS_BattleTeam in teams:
		if team in iterated_teams:
			continue
		
		iterated_teams.append(team)
		names.append(team.get_trainer_name())
	
	return _get_name_string(names)

func _opponent_battle_text() -> void:
	if is_boss or is_wild:
		var creature_names : Array[String]
		for idx : int in opp_creatures.size():
			var creature : CCS_Creature = opp_creatures.get(idx)
			play_creature_sound(creature.id)
			creature_names.append(creature.get_creature_name())
		
		var format := {
			"creatures" : _get_name_string(creature_names)
		}
		
		var battle_text : Array[String] = wild_battle_text
		if is_boss:
			battle_text = boss_battle_text
		
		await CCS_BattleUIManager.create_dialogue(battle_text, format)
		return
	
	await CCS_BattleUIManager.create_dialogue(opponent_battle_text, { "name" : get_teams_name_string(opp_teams) })

func offset_extra_stats(creature : CCS_Creature, stat : StringName, offset : int = 0) -> void:
	creature.stats.other_stats[stat] += offset

func send_out_creature(team : CCS_BattleTeam, creature : CCS_Creature, idx : int) -> void:
	var format : Dictionary = {
		"name" : team.get_trainer_name(),
		"creature" : creature.get_creature_name()
	}
	
	await CCS_BattleUIManager.create_dialogue(send_out_text, format)
	
	team.send_out_creature(creature, idx)
	
	refresh_creature.emit()
	creature_summon.emit([creature] as Array[CCS_Creature])
	await play_creature_sound(creature.id)
	
func retrieve_creature(team : CCS_BattleTeam, creature : CCS_Creature) -> void:
	var format : Dictionary = {
		"name" : team.get_trainer_name(),
		"creature" : creature.get_creature_name()
	}
	
	await CCS_BattleUIManager.create_dialogue(retrieve_text, format)
	
	creature_retrieve.emit(creature)

func switch_creatures(team : CCS_BattleTeam, from : CCS_Creature, to : CCS_Creature) -> void:
	for command : CCS_BattleCommandBase in command_list:
		if command is CCS_BattleCommand_Attack and command.target == from:
			command.target = to
	
	if not from.is_dead():
		await retrieve_creature(team, from)
	await send_out_creature(team, to, team.currently_out_creatures.find(from))

func can_switch(team : CCS_BattleTeam, creature : CCS_Creature) -> bool:
	if creature.is_dead():
		await CCS_BattleUIManager.create_dialogue(creature_dead_text, { "creature" : creature.get_creature_name() })
		return false
	
	if team.is_currently_out(creature):
		await CCS_BattleUIManager.create_dialogue(already_in_battlefield_text, { "creature" : creature.get_creature_name() })
		return false
	
	for command : CCS_BattleCommandBase in command_list:
		if command is CCS_BattleCommand_Creature and command.to == creature:
			await CCS_BattleUIManager.create_dialogue(already_in_battlefield_text, { "creature" : creature.get_creature_name() })
			return false
	
	return true

func heal_creature(creature : CCS_Creature, amount : int = 0) -> void:
	await play_battle_vfx_scene(heal_vfx_scene, creature)
	creature.heal(amount)

func _get_current_creatures(teams : Array[CCS_BattleTeam]) -> Array[CCS_Creature]:
	var checked_teams : Dictionary[CCS_BattleTeam, int]
	var creatures : Array[CCS_Creature]
	
	for team_idx : int in teams.size():
		var team : CCS_BattleTeam = teams.get(team_idx)
		
		if team in checked_teams: checked_teams[team] += 1
		else: checked_teams[team] = 0
		
		var creature_idx : int = checked_teams.get(team)
		
		if creature_idx < team.currently_out_creatures.size():
			var creature : CCS_Creature = team.get_current_creature(creature_idx)
			if not (creature == null or creature.is_dead()):
				creatures.append(team.get_current_creature(creature_idx))
				continue
		
		creatures.append(null)
	return creatures

func _save_creature_dead_state() -> void:
	ally_dead.clear()
	opp_dead.clear()
	
	for creature : CCS_Creature in ally_creatures:
		if creature == null or creature.is_dead(): ally_dead.append(true)
		else: ally_dead.append(false)
	
	for creature : CCS_Creature in opp_creatures:
		if creature == null or creature.is_dead(): opp_dead.append(true)
		else: opp_dead.append(false)

func _try_switching_creature() -> void:
	for team_idx : int in ally_teams.size():
		if not ally_dead[team_idx]: continue
		await _try_switching_creature_base(ally_teams[team_idx], ally_creatures[team_idx])
		
	for team_idx : int in opp_teams.size():
		if not opp_dead[team_idx]: continue
		await _try_switching_creature_base(opp_teams[team_idx], opp_creatures[team_idx])

func _try_switching_creature_base(team : CCS_BattleTeam, switch_from : CCS_Creature) -> void:
	if team.is_all_dead(): return
	
	for creature : CCS_Creature in team.creature_list:
		if team.is_currently_out(creature): continue
		if creature.is_dead(): continue
		
		if team == CCS_PlayerData.get_team():
			CCS_BattleUIManager.disable_cancel = true
			CCS_BattleUIManager.open_creature_party()
			var data : Array = await switch_creature
			await switch_creatures(team, switch_from, data[2])
			CCS_BattleUIManager.disable_cancel = false
		else:
			await switch_creatures(team, switch_from, creature)
		break

func _check_creature_dead() -> void:
	var xp_yield : int = 0
	
	for team_idx : int in ally_creatures.size():
		if ally_dead[team_idx]: continue
		
		var creature : CCS_Creature = ally_creatures[team_idx]

		if creature == null:
			ally_dead[team_idx] = true
			continue
		
		if creature.is_dead():
			await _creature_dead(creature)
			ally_dead[team_idx] = true
	
	for team_idx : int in opp_creatures.size():
		if opp_dead[team_idx]: continue
		
		var creature : CCS_Creature = opp_creatures[team_idx]

		if creature == null:
			opp_dead[team_idx] = true
			continue
		
		if creature == null or creature.is_dead():
			await _creature_dead(creature)
			opp_dead[team_idx] = true
			xp_yield += _get_xp_yield(creature)
	
			for function : CCS_AdditionalBattleFunctions in additional_functions.values():
				await function.opp_creature_dead(creature)
	
	if xp_yield > 0:
		var current_creatures : Array[CCS_Creature] = CCS_PlayerData.get_team().currently_out_creatures
		
		for current_creature : CCS_Creature in current_creatures:
			await gain_xp_gradual(current_creature, xp_yield)
		
		xp_yield /= 2
		
		for creature : CCS_Creature in CCS_PlayerData.get_team().sent_out_creatures:
			if creature in current_creatures:
				continue
			
			await gain_xp(creature, xp_yield)
		
		CCS_PlayerData.get_team().sent_out_creatures.clear()

func gain_xp(creature : CCS_Creature, xp_yield : int) -> void:
	if creature.is_dead():
		return
	
	await CCS_BattleUIManager.create_dialogue(xp_text, {"creature" : creature.get_creature_name(), "xp" : xp_yield})
	
	var level : int = creature.stats.level
	creature.xp += xp_yield
	creature.level_up()
	creature.stats.calculate_stats(creature.id)
	
	if creature.stats.level > level:
		play_sound(level_up_success_sound)
		await CCS_BattleUIManager.create_dialogue(level_text, {"creature" : creature.get_creature_name(), "level" : creature.stats.level})
		await learn_new_attacks(creature)

func gain_xp_gradual(creature : CCS_Creature, xp_yield : int) -> void:
	if creature.is_dead():
		return
	
	await CCS_BattleUIManager.create_dialogue(xp_text, {"creature" : creature.get_creature_name(), "xp" : xp_yield})
	
	var level : int = creature.stats.level
	var target_xp : int = creature.xp + xp_yield
	play_sound(gain_xp_sound)
	while true:
		creature.xp = lerpf(creature.xp, target_xp, get_process_delta_time() * 20)
		if is_equal_approx(creature.xp, target_xp) or creature.xp > target_xp:
			creature.xp = target_xp
		
		if creature.xp >= creature.stats.xp_goal:
			play_sound(level_up_sound)
			target_xp -= creature.stats.xp_goal
			creature.level_up()
			creature.stats.calculate_stats(creature.id)
			leveled_up.emit(creature)
		
		if creature.xp == target_xp:
			break
		
		await get_tree().process_frame
	
	if creature.stats.level > level:
		play_sound(level_up_success_sound)
		await CCS_BattleUIManager.create_dialogue(level_text, {"creature" : creature.get_creature_name(), "level" : creature.stats.level})
		await learn_new_attacks(creature)

func _creature_dead(dead_creature : CCS_Creature) -> void:
	await play_creature_sound(dead_creature.id)
	creature_dead.emit(dead_creature)
	await CCS_BattleUIManager.create_dialogue(dead_text, {"creature" : dead_creature.get_creature_name()})

func _set_side(teams : Array[CCS_BattleTeam], count : int) -> Array[CCS_BattleTeam]:
	if teams.is_empty():
		_battle_over()
		return []
	
	teams.resize(count)
	for idx : int in count:
		if teams[idx] == null:
			teams.set(idx, teams[idx - 1])

	return teams

func _sort_priority(a : CCS_BattleCommandBase, b : CCS_BattleCommandBase) -> bool:
	if a.has_priority_over(b):
		return not b.has_priority_over(a)
	return false

func _get_xp_yield(creature : CCS_Creature) -> int:
	#var species : CCS_StaticData_Creature = static_data.creatures.get(creature.id)
	return creature.stats.level

func _get_type_advantage(attack_type : StringName, target_types : Array[StringName]) -> float:
	var type_advantage : float = 1.0
	
	for target_type : StringName in target_types:
		var type_data : CCS_StaticData_Type = static_data.types.get(target_type)
		
		if type_data.resistance.has(attack_type):
			type_advantage /= 2
		elif type_data.weakness.has(attack_type):
			type_advantage *= 2
	return type_advantage

func calculate_stat(base : int, iv : int, level : int = 1, offset : int = 0) -> int:
	return roundi((float((base + iv) * level) / 8) * (1 + float(offset / 4)))

func get_catch_rate(target : CCS_Creature, capture_device_catch_rate : float) -> float:
	var target_species : CCS_StaticData_Creature = static_data.creatures.get(target.id)
	var hp_max : float = target.stats.health_point
	var hp : float = target.health
	var catch_rate : float = 2*hp_max - hp
	catch_rate /= 2*hp_max
	
	catch_rate *= capture_device_catch_rate
	catch_rate *= target_species.catch_rate
	
	return catch_rate

func get_damage(attack : CCS_StaticData_Attack, user : CCS_Creature, target : CCS_Creature) -> int:
	if !static_data.creatures.has(user.id) || !static_data.creatures.has(target.id):
		push_error("Error: Invalid creature ids detected")
		return 0
	
	var user_species : CCS_StaticData_Creature = static_data.creatures.get(user.id)
	var target_species : CCS_StaticData_Creature = static_data.creatures.get(target.id)
	
	var type_advantage : float = _get_type_advantage(attack.type, target_species.types)
	var power_defense : float = user.stats.power / target.stats.defense
	var stab : float = 3 if user_species.types.has(attack.type) else 1
	var rand : float = rng.randf_range(0.75, 1)
	is_critical_hit = (rng.randf() <= 0.07)
	var critical_hit : float = 2.0 if is_critical_hit else 1.0
	var total_dmg : float = attack.power
	
	total_dmg *= user.stats.level
	total_dmg *= type_advantage
	total_dmg /= 25
	total_dmg *= power_defense
	total_dmg += stab
	total_dmg *= rand
	total_dmg *= critical_hit
	
	is_resistant = (type_advantage < 1)
	is_weak = (type_advantage > 1)
	
	return roundi(total_dmg)

func catch_opponent(target : CCS_Creature, catch_rate : float) -> bool:
	var is_captured : bool = rng.randf() <= catch_rate
	
	var capture_vfx : CCS_BattleVFX = capture_vfx_scene.instantiate()
	capture_vfx.captured = is_captured
	await play_battle_vfx(capture_vfx, target)
	
	if is_captured:
		CCS_PlayerData.give_creature_defined(target)
		
		if target in opp_creatures:
			var idx : int = opp_creatures.find(target)
			var opp_team : CCS_BattleTeam = opp_teams[idx]
			opp_team.currently_out_creatures.set(opp_team.currently_out_creatures.find(target), null)
			opp_team.creature_list.erase(target)
		
		max_team_size
		refresh_creature.emit()
		captured_creature.emit(target)
		
		await CCS_BattleUIManager.create_dialogue(capture_success_dialogue, { "creature" : target.get_creature_name() })
		
		for additional_function : CCS_AdditionalBattleFunctions in additional_functions.values():
			await additional_function.creature_captured(target)
		
		return true
		
	await CCS_BattleUIManager.create_dialogue(capture_fail_dialogue, { "creature" : target.get_creature_name() })
	
	return false

func _combine_commands() -> void:
	for command_a : CCS_BattleCommandBase in command_list:
		for command_b : CCS_BattleCommandBase in command_list:
			if command_a == command_b:
				continue
			
			var command_new := command_a.combine_command(command_b)
			
			if command_new != null:
				command_list.remove_at(command_list.find(command_b))
				command_list[command_list.find(command_a)] = command_new

func _generate_turn() -> void:
	_save_creature_dead_state()
	
	for team_idx : int in ally_teams.size():
		if ally_dead[team_idx]: continue
		
		var command : CCS_BattleCommandBase
		if ally_teams[team_idx] == CCS_PlayerData.get_team():
			CCS_BattleUIManager.user = ally_creatures[team_idx]
			command = await add_command
		else:
			command = _get_commands(
				ally_teams[team_idx],
				ally_creatures[team_idx],
				opp_creatures
			)
		
		command_list.append(command)
		
		if command is CCS_BattleCommand_Flee:
			break
	
	for team_idx : int in opp_teams.size():
		if opp_dead[team_idx]: continue
		
		command_list.append(
			_get_commands(opp_teams[team_idx],
			opp_creatures[team_idx],
			ally_creatures)
		)
	
	CCS_BattleUIManager.user = null
	focus_camera.emit(null, 0.2, Tween.TRANS_CUBIC, Tween.EASE_OUT)
	
	_combine_commands()
	
	command_list.sort_custom(_sort_priority)
	
	for command : CCS_BattleCommandBase in command_list:
		await command.execute()
		
		await _check_creature_dead()
	
		for function : CCS_AdditionalBattleFunctions in additional_functions.values():
			await function.turn_end()
		
		if command.stop_battle:
			is_lose = false
			end_battle()
			return
		
		if _check_battle_over():
			_battle_over()
			return
	
	for command : CCS_BattleCommandBase in command_list:
		await command.turn_end_execute()
		
		if _check_battle_over():
			_battle_over()
			return
	
	await _try_switching_creature()
	
	command_list.clear()
	turn_end.emit()

func _get_commands(team : CCS_BattleTeam, creature : CCS_Creature, targets : Array[CCS_Creature]) -> CCS_BattleCommandBase:
	var selectable_targets : Array[CCS_Creature]
	for target : CCS_Creature in targets:
		if target == null or target.is_dead():
			continue
		
		selectable_targets.append(target)
	
	if creature.attack_pool.size() == 0:
		return CCS_BattleCommandBase.new()
	
	creature_command_created.emit(creature)
	
	var target : CCS_Creature = selectable_targets.pick_random() if selectable_targets.size() > 0 else null
	var attack_idx : int = rng.randi() % creature.attack_pool.size()
	
	var trainer_name : String = team.get_trainer_name()
	
	return CCS_BattleCommand_Attack.new(
		trainer_name,
		creature,
		target,
		attack_idx
	)

func item_used(item_id : StringName, target : CCS_Creature) -> void:
	if not is_in_battle:
		return
	
	await CCS_BattleUIManager.close_item_bag()
	var player_item_command : CCS_BattleCommand_Item = CCS_BattleCommand_Item.new(item_id, target)
	add_command.emit(player_item_command)

func attack_selected(user : CCS_Creature, target : CCS_Creature, attack_idx : int) -> void:
	var trainer_name : String = ""
	if not CCS_PlayerData.get_team().get_trainer_name().is_empty():
		trainer_name = CCS_PlayerData.get_team().get_trainer_name()
		
	var player_attack_command : CCS_BattleCommand_Attack = CCS_BattleCommand_Attack.new(
		trainer_name,
		user,
		target,
		attack_idx
	)
	
	add_command.emit(player_attack_command)

func creature_switched(team : CCS_BattleTeam, from : CCS_Creature, to : CCS_Creature) -> void:
	if command_list.size() >= team.currently_out_creatures.size():
		return
	
	var player_creature_command : CCS_BattleCommand_Creature = CCS_BattleCommand_Creature.new(team, from, to)
	add_command.emit(player_creature_command)

func is_creature_sprite_available(id : String):
	return creature_sprite_library.has_animation(id)

func loaded_creature_sprite_library():
	return creature_sprite_library != null

func _check_battle_over() -> bool:
	for opp_team : CCS_BattleTeam in opp_teams:
		if opp_team.creature_list.is_empty():
			return true
	
	for ally_team : CCS_BattleTeam in ally_teams:
		if ally_team.creature_list.is_empty():
			is_lose = true
			return true
	
	if ally_dead.has(false) and opp_dead.has(false):
		return false
	
	is_lose = true
	for team : CCS_BattleTeam in ally_teams:
		if not team.is_all_dead():
			is_lose = false
			break
	
	if not is_lose:
		for team : CCS_BattleTeam in opp_teams:
			if not team.is_all_dead():
				return false
	
	return true

func _battle_over():
	if is_lose:
		pass
	else:
		pass
	
	end_battle()

func end_battle():
	for function : CCS_AdditionalBattleFunctions in additional_functions.values():
		await function.battle_end_initialized()
	
	var transition_playing : bool = CCS_BattleUIManager.play_transition("black_fade")
	if transition_playing:
		await CCS_BattleUIManager.transition_middle
	
	battle_ending.emit(is_lose)
	is_in_battle = false
	
	for team_idx : int in ally_teams.size():
		ally_teams[team_idx].reset_team_to_default()
		ally_creatures[team_idx] = null
	
	for team_idx : int in opp_teams.size():
		opp_teams[team_idx].reset_team_to_default()
		opp_creatures[team_idx] = null
	
	refresh_creature.emit()
	
	ally_teams.clear()
	ally_creatures.clear()
	opp_teams.clear()
	opp_creatures.clear()
	
	command_list.clear()
	
	if transition_playing:
		await CCS_BattleUIManager.transition_end
	battle_end.emit(is_lose)
	
	for function : CCS_AdditionalBattleFunctions in additional_functions.values():
		await function.battle_end()
	
	if is_lose:
		CCS_PlayerData.get_team().heal_team()

func play_battle_vfx_scene(vfx_scene : PackedScene, user : CCS_Creature, targets : Array[CCS_Creature] = [], attack : CCS_StaticData_Attack = null) -> void:
	var vfx : CCS_BattleVFX = vfx_scene.instantiate()
	await play_battle_vfx(vfx, user, targets, attack)

func play_battle_vfx(vfx : CCS_BattleVFX, user : CCS_Creature, targets : Array[CCS_Creature] = [], attack : CCS_StaticData_Attack = null) -> void:
	vfx.setup(user, targets, attack)
	add_child(vfx)
	
	await vfx.disposed
