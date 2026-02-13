extends CanvasLayer

signal attack_pool_updated(creature : CCS_Creature)
signal item_closed
signal creature_closed
signal cancel_action
signal item_creature_selected(creature : CCS_Creature)
signal creature_info_closed
signal target_selected(creature : CCS_Creature)

signal transition_start(anim : String)
signal transition_middle(anim : String)
signal transition_end(anim : String)

signal dialogue_start
signal dialogue_end

@onready var ally_panel_container : Control = %AllyPanelContainer
@onready var opp_panel_container : Control = %OppPanelContainer
@onready var hud_buttons : Control = %HUDButtonList

@onready var attack_buttons : Control = %AttackButtonList
@onready var target_buttons : Control = %TargetButtonList
@onready var creature_list : Control = %CreatureList
@onready var item_list : Control = %ItemList
@onready var item_creature_list : Control = %ItemCreatureList

@onready var creature_options : CCS_BattleUI_OptionSelect = %CreatureOptions
@onready var item_options : CCS_BattleUI_OptionSelect = %ItemOptions
@onready var item_creature_options : CCS_BattleUI_OptionSelect = %CreatureItemOptions

@onready var creature_overlay : Control = %CreatureOverlay
@onready var item_overlay : Control = %ItemOverlay

@onready var creature_info_overlay : Control = %CreatureInfoOverlay
@onready var creature_info_sprite : AnimatedSprite2D = %CreatureInfoSprite

const dialogue_box_scene : PackedScene = preload("uid://cddcwtnbjiit5")

var creature_info_label_texts : Dictionary[Label, String]
var creature_info_viewable_extra_stats : Dictionary[StringName, String]

var hud_enable : bool = false
var attack_enable : bool = false
var targets_enable : bool = false
var creature_enable : bool = false
var creature_info_enable : bool = false
var item_enable : bool = false
var disable_cancel : bool = false
var item_selected : bool = false

var swap_creature : CCS_Creature
var creature_buttons : Array[CCS_BattleUI_CreatureButton]
var item_creature_buttons : Array[CCS_BattleUI_CreatureButton]

#var hud_last_focus : Button
var attack_last_focus : Button
var item_last_focus : Button
var item_creature_last_focus : Button
var creature_last_focus : Button

var info_selected : CCS_Creature

var user : CCS_Creature:
	set(value):
		user = value
	
		if user == null:
			return
		
		CCS_BattleUIManager.enable_battle_ui()
		update_attack_pool()
	
		if CCS_BattleManager.ally_teams.size() > 1:
			_focus_camera(user)

func _ready() -> void:
	CCS_BattleManager.battle_initialized.connect(_initialize_scene)
	CCS_BattleManager.refresh_creature.connect(_refresh_creatures)
	#CCS_BattleManager.creature_summon.connect(_creature_created)
	CCS_BattleManager.creature_retrieve.connect(_creature_remove)
	CCS_BattleManager.creature_dead.connect(_creature_remove)
	
	for extra_stat : StringName in creature_info_viewable_extra_stats:
		var extra_stat_label : Label = %CreatureInfoExtraStatLabel.duplicate()
		extra_stat_label.name = extra_stat
		extra_stat_label.text = extra_stat_label.text.format({
			"stat_name" : creature_info_viewable_extra_stats.get(extra_stat),
			"stat_value" : "{" + extra_stat + "}",
		})
		%CreatureInfoExtraStatContainer.add_child(extra_stat_label)
	
	_get_creature_info_labels()
	
	for attack_idx : int in CCS_BattleManager.max_attack_pool_size:
		var attack_label : Label = %CreatureInfoAttackLabel.duplicate()
		attack_label.name = "attack_" + str(attack_idx)
		%CreatureInfoAttackContainer.add_child(attack_label)
		%CreatureInfoAttackContainer.move_child(attack_label, attack_idx)
	
	%CreatureInfoExtraStatLabel.hide()
	%CreatureInfoAttackLabel.hide()
	%CreatureInfoBackButton.pressed.connect(close_creature_info)
	
	#Creature Info Labels Setup

func add_extra_stat(stat_id : StringName, stat_name : String) -> void:
	if creature_info_viewable_extra_stats.has(stat_id):
		return

	creature_info_viewable_extra_stats[stat_id] = stat_name
	var extra_stat_label : Label = %CreatureInfoExtraStatLabel.duplicate()
	extra_stat_label.show()
	extra_stat_label.name = stat_id
	extra_stat_label.text = extra_stat_label.text.format({
		"stat_name" : stat_name,
	})
	%CreatureInfoExtraStatContainer.add_child(extra_stat_label)
	creature_info_label_texts[extra_stat_label] = extra_stat_label.text

func _get_creature_info_labels(parent : Node = creature_info_overlay) -> void:
	for child : Node in parent.get_children():
		if child == null:
			continue
		
		if child.get_child_count() > 0:
			_get_creature_info_labels(child)
		
		if child is Label:
			var label : Label = child as Label
			creature_info_label_texts[label] = label.text

func _creature_remove(creature : CCS_Creature) -> void:
	if creature in CCS_BattleManager.ally_creatures:
		set_creature_ally(null, CCS_BattleManager.ally_creatures.find(creature))
	elif creature in CCS_BattleManager.opp_creatures:
		set_creature_opp(null, CCS_BattleManager.opp_creatures.find(creature))
		_set_target_buttons(CCS_BattleManager.opp_creatures)

func _refresh_creatures() -> void:
	for idx : int in CCS_BattleManager.ally_creatures.size():
		set_creature_ally(CCS_BattleManager.ally_creatures.get(idx), idx)
	for idx : int in CCS_BattleManager.opp_creatures.size():
		set_creature_opp(CCS_BattleManager.opp_creatures.get(idx), idx)
	
	_set_target_buttons(CCS_BattleManager.opp_creatures)
	
func _initialize_scene() -> void:
	for node : Node in ally_panel_container.get_children():
		node.queue_free()
		
	for node : Node in opp_panel_container.get_children():
		node.queue_free()
	
	for idx : int in CCS_BattleManager.ally_teams.size():
		ally_panel_container.add_child(CCS_HUDPanel.create_new_panel())
	
	for idx : int in CCS_BattleManager.opp_teams.size():
		opp_panel_container.add_child(CCS_HUDPanel.create_new_panel())

func enable_battle_ui():
	enable_hud()

func create_dialogue(texts : Array[String], format : Dictionary = {}, options : Array[String] = []) -> void:
	dialogue_start.emit()
	var dialogue : Array[String] = []
	for text : String in texts:
		dialogue.append(text.format(format))
	
	var dialogue_box : CCS_DialogueBox = dialogue_box_scene.instantiate()
	dialogue_box.dialogue_text = dialogue
	add_child(dialogue_box)
	await dialogue_box.tree_exited
	dialogue_end.emit()

func create_dialogue_options(texts : Array[String], options : Array[String], cancel_option = -1, format : Dictionary = {}) -> int:
	dialogue_start.emit()
	var dialogue : Array[String] = []
	for text : String in texts:
		dialogue.append(text.format(format))
	
	var dialogue_box : CCS_DialogueBox = dialogue_box_scene.instantiate()
	dialogue_box.dialogue_text = dialogue
	dialogue_box.options = options
	
	dialogue_box.cancel_option = cancel_option
	add_child(dialogue_box)
	var option : int = await dialogue_box.option_selected
	await dialogue_box.tree_exited
	dialogue_end.emit()
	return option

func update_creature_list() -> void:
	var idx : int = 0 
	for node : Node in item_creature_list.get_children():
		if node is CCS_BattleUI_CreatureButton:
			var creature : CCS_Creature = null
			if idx < CCS_PlayerData.get_team().creature_list.size():
				creature = CCS_PlayerData.get_team().creature_list.get(idx)
			
			node.creature = creature
			node.focus_mode = Control.FOCUS_NONE
			node.disabled = true
			
			idx += 1
			
			if node in item_creature_buttons:
				continue
			
			node.focus_entered.connect(func(): item_creature_last_focus = node)
			node.creature_selected.connect(_item_creature_select_options)
			item_creature_buttons.append(node)
	
	idx = 0
	
	for node : Node in creature_list.get_children():
		if node is CCS_BattleUI_CreatureButton:
			var creature : CCS_Creature = null
			if idx < CCS_PlayerData.get_team().creature_list.size():
				creature = CCS_PlayerData.get_team().creature_list.get(idx)
			
			node.creature = creature
			
			idx += 1
			
			if node in creature_buttons:
				continue
			
			node.focus_entered.connect(func(): creature_last_focus = node)
			node.creature_selected.connect(_creature_select_options)
			creature_buttons.append(node)

func update_item_list() -> void:
	var current_item_list : Dictionary[StringName, CCS_BattleUI_ItemButton]
	var cancel_btn : Button
	
	for item : Node in item_list.get_children():
		if not item is CCS_BattleUI_ItemButton:
			if item.name == "CancelButton":
				cancel_btn = item
			continue
		
		item = item as CCS_BattleUI_ItemButton
		if not CCS_PlayerData.has_item(item.name):
			item.queue_free()
			continue
		
		current_item_list[item.name] = item
		item.item_quantity = CCS_PlayerData.get_item_quantity(item.name)
		continue
	
	for item_id : StringName in CCS_PlayerData.get_item_list():
		var item_button : CCS_BattleUI_ItemButton
		if current_item_list.has(item_id):
			item_button = current_item_list.get(item_id)
			item_list.move_child(item_button, -1)
		else:
			item_button = CCS_BattleUI_ItemButton.new(item_id, CCS_PlayerData.get_item_quantity(item_id))
			item_button.item_selected.connect(_item_selected)
			item_button.focus_entered.connect(func(): item_last_focus = item_button)
			
			item_list.add_child(item_button)
	
	if cancel_btn:
		item_list.move_child(cancel_btn, -1)

func update_attack_pool():
	if user == null:
		return
	
	var cancel_btn : Button
	var current_attack_list : Dictionary[StringName, CCS_BattleUI_AttackButton]
	
	for child : Button in attack_buttons.get_children():
		if child.name == "CancelButton":
			cancel_btn = child
			continue
		
		if user.attack_pool.has(child.name):
			current_attack_list[child.name] = child
			continue
		
		child.queue_free()
	
	for i : int in CCS_BattleManager.max_attack_pool_size:
		var attack_id : StringName
		
		if i < user.attack_pool.size():
			attack_id = user.attack_pool[i]
		
		var attack_button : CCS_BattleUI_AttackButton
		
		if current_attack_list.has(attack_id):
			attack_button = current_attack_list.get(attack_id)
			attack_buttons.move_child(attack_button, -1)
		else:
			attack_button = CCS_BattleUI_AttackButton.new(attack_id)
			attack_button.pressed.connect(func(): _attack_selected(i))
			attack_button.focus_entered.connect(func(): attack_last_focus = attack_button)
			attack_buttons.add_child(attack_button)
		
	if cancel_btn:
		attack_buttons.move_child(cancel_btn, -1)
	
	attack_pool_updated.emit(user)

func set_creature_ally(creature : CCS_Creature, idx : int):
	var ally_panel : CCS_HUDPanel = ally_panel_container.get_child(idx)
	if ally_panel:
		ally_panel.creature = creature

func set_creature_opp(creature : CCS_Creature, idx : int):
	var opp_panel : CCS_HUDPanel = opp_panel_container.get_child(idx)
	if opp_panel:
		opp_panel.creature = creature

func _set_target_buttons(targets : Array[CCS_Creature]) -> void:
	if targets.is_empty():
		return
	
	var cancel_btn : Button
	var defined_targets : Array[CCS_Creature]
	
	for child : Button in target_buttons.get_children():
		if child.name == "CancelButton":
			cancel_btn = child
			continue
		
		if child is CCS_BattleUI_TargetButton:
			var target : CCS_Creature = child.creature
			
			if not target in targets:
				child.queue_free()
				continue
			
			defined_targets.append(target)
			if target == null or target.is_dead(): child.disable_button()
			else: child.enable_button()
	
	for target : CCS_Creature in targets:
		if target in defined_targets: continue
		var button : CCS_BattleUI_TargetButton = CCS_BattleUI_TargetButton.new(target)
		button.focus_entered.connect(func(): _focus_camera(target))
		target_buttons.add_child(button)
	
	if cancel_btn:
		target_buttons.move_child(cancel_btn, -1)

func _attack_selected(attack_idx : int) -> void:
	if not attack_enable:
		return
	
	await _enable_disable_attack_bar()

	var target : CCS_Creature = await _select_target(attack_idx)
	
	if target == null:
		if CCS_BattleManager.ally_teams.size() > 1:
			_focus_camera(user)
		else:
			_focus_camera(null)
		await _enable_disable_attack_bar()
		return
	
	CCS_BattleManager.attack_selected(user, target, attack_idx)

func _creature_switched(from : CCS_Creature, to : CCS_Creature):
	if creature_enable:
		await _enable_disable_creature_party()
		CCS_BattleManager.switch_creature.emit(CCS_PlayerData.get_team(), from, to)

func _item_selected(item_id : StringName) -> void:
	var item_data : CCS_StaticData_Item = CCS_BattleManager.static_data.items.get(item_id)
	
	disable_cancel = true
	item_options.options.get("Use").visible = item_data.can_use_in_battle if CCS_BattleManager.is_in_battle else item_data.can_use_in_bag
	item_options.options.get("Throw").hide()
	item_options.enable_options()
	var selected_option : StringName = await item_options.option_selected
	item_options.hide()
	disable_cancel = false
	
	match selected_option:
		"Use":
			item_selected = true
			var creature : CCS_Creature = null
			
			if await item_data.use_on_creature():
				if item_data.use_on_party:
					creature = await _item_select_creature(item_data)
				else:
					await CCS_BattleUIManager.close_item_bag()
					creature = await _select_target()
					
					if creature == null:
						_focus_camera(user)
						await CCS_BattleUIManager.open_item_bag()
			
			if await item_data.can_use_item(creature):
				if CCS_BattleManager.is_in_battle:
					CCS_BattleManager.item_used(item_id, creature)
				else:
					await item_data.use_item_in_bag(creature)
			else:
				await CCS_BattleUIManager.open_item_bag()
			
			item_selected = false
	
	if item_last_focus:
		item_last_focus.grab_focus()
	else:
		item_list.grab_focus()
	

func _focus_camera(creature : CCS_Creature) -> void:
	CCS_BattleManager.focus_camera.emit(
			creature,
			0.2,
			Tween.TRANS_CUBIC,
			Tween.EASE_OUT
	)

func _item_creature_select_options(creature : CCS_Creature) -> void:
	disable_cancel = true
	item_creature_options.options.get("Select").visible = true
	
	item_creature_options.enable_options()
	var selected_option : StringName = await item_creature_options.option_selected
	item_creature_options.hide()
	
	match selected_option:
		"Select":
			item_creature_selected.emit(creature)
		_:
			item_creature_last_focus.grab_focus()
	
	disable_cancel = false

func _item_select_creature(item_data : CCS_StaticData_Item) -> CCS_Creature:
	# Disable Item Buttons
	for button : Button in item_list.get_children():
		button.disabled = true
		button.focus_mode = Control.FOCUS_NONE
	
	# Enable Creature Buttons
	var focused : bool = false
	for button : Button in item_creature_list.get_children():
		if button is CCS_BattleUI_CreatureButton:
			if button.creature == null: continue
		
		button.disabled = false
		button.focus_mode = Control.FOCUS_ALL
		
		if focused: continue
		button.grab_focus()
		focused = true
	
	var selected_creature : CCS_Creature = await item_creature_selected
	
	# Disable Creature Buttons
	for button : Button in item_creature_list.get_children():
		button.disabled = true
		button.focus_mode = Control.FOCUS_NONE
	
	# Re-Enable Item Buttons
	for button : Button in item_list.get_children():
		button.disabled = false
		button.focus_mode = Control.FOCUS_ALL
	
	return selected_creature

func enable_hud():
	if not hud_enable:
		await _enable_disable_hud()

func _select_target(attack_idx : int = -1) -> CCS_Creature:
	if attack_idx >= 0:
		var attack : CCS_StaticData_Attack = CCS_BattleManager.static_data.attacks.get(user.attack_pool.get(attack_idx))
		if attack.use_at_self:
			return user
	
	var targets : Array[CCS_Creature] = CCS_BattleManager.opp_creatures
	var target : CCS_Creature = targets.pick_random()
	
	if targets.size() > 1:
		if not targets_enable:
			await _enable_disable_targets()
		
		target = await target_selected
		await _enable_disable_targets()
	
	return target

func _cancel_action() -> void:
	cancel_action.emit()
	if attack_enable:
		var button : Button = attack_buttons.get_child(-1)
		button.grab_focus()
		await _enable_disable_attack_bar()
	
	await close_item_bag()
	await close_creature_party()
	
	if CCS_BattleManager.is_in_battle:
		enable_hud()

func _enable_disable_targets() -> void:
	targets_enable = not targets_enable
	var button_disabled_state : Dictionary[Button, bool]
	
	for button : Button in target_buttons.get_children():
		button_disabled_state[button] = button.disabled
		button.disabled = true
	
	await _animation_player_show_ui("targets", targets_enable)
	#target_buttons.visible = targets_enable
	
	for button : Button in target_buttons.get_children():
		button.disabled = button_disabled_state.get(button)
	
	if targets_enable:
		for button : Button in target_buttons.get_children():
			if button is CCS_BattleUI_TargetButton and not button.disabled:
				button.grab_focus()
				return

func _enable_disable_hud() -> void:
	hud_enable = not hud_enable
	var button_disabled_state : Dictionary[Button, bool]
	
	for button : Button in hud_buttons.get_children():
		button_disabled_state[button] = button.disabled
		button.disabled = true
	
	await _animation_player_show_ui("hud", hud_enable)
	#hud_buttons.visible = hud_enable
	
	for button : Button in hud_buttons.get_children():
		button.disabled = button_disabled_state.get(button)
	
	if hud_enable:
		var button : Button = hud_buttons.get_child(0)
		button.grab_focus()

func _enable_disable_attack_bar() -> void:
	attack_enable = not attack_enable
	var button_disabled_state : Dictionary[Button, bool]
	
	for button : Button in hud_buttons.get_children():
		button_disabled_state[button] = button.disabled
		button.disabled = true
	
	await _animation_player_show_ui("attacks", attack_enable)
	#attack_buttons.visible = attack_enable
	
	for button : Button in hud_buttons.get_children():
		button.disabled = button_disabled_state.get(button)
	
	if attack_enable:
		if attack_last_focus:
			attack_last_focus.grab_focus()
			return
		
		for button : Button in attack_buttons.get_children():
			if button is CCS_BattleUI_AttackButton:
				if not button.has_attack_data:
					continue
				
				button.grab_focus()
				break

func _enable_disable_creature_party() -> void:
	creature_enable = not creature_enable
	await _animation_player_show_ui("creatures", creature_enable)
	#creature_overlay.visible = creature_enable
	
	if not creature_enable:
		creature_closed.emit()
		return
	
	for button : Button in creature_list.get_children():
		var creature_button : CCS_BattleUI_CreatureButton = button as CCS_BattleUI_CreatureButton
		
		if user == null:
			button.grab_focus()
			break
		
		if user in CCS_PlayerData.get_team().creature_list:
			if creature_button.creature == user:
				button.grab_focus()
				break

func _enable_disable_creature_info() -> void:
	creature_info_enable = not creature_info_enable
	
	if creature_info_enable:
		CCS_BattleManager.play_creature_sound(info_selected.id)
		%CreatureInfoBackButton.grab_focus()
	
	await _animation_player_show_ui("creature_info", creature_info_enable)
	#creature_info_overlay.visible = creature_info_enable

func _enable_disable_item_list():
	item_enable = not item_enable
	await _animation_player_show_ui("items", item_enable)
	#item_overlay.visible = item_enable
	
	if not item_enable:
		item_closed.emit()
		return
		
	if item_last_focus:
		item_last_focus.grab_focus()
		return
	
	var button : Button = item_list.get_child(0)
	button.grab_focus()

func _animation_player_show_ui(ui_name : String, enable : bool) -> void:
	if not $AnimationPlayer:
		return
	
	var ui_animation : String = "show_" + ui_name if enable else "hide_" + ui_name
	
	if not $AnimationPlayer.has_animation(ui_animation):
		return
	
	$AnimationPlayer.play(ui_animation)
	await $AnimationPlayer.animation_finished
	return

func _creature_select_options(creature : CCS_Creature) -> void:
	disable_cancel = true
	creature_options.options.get("Switch").visible = CCS_BattleManager.is_in_battle
	creature_options.options.get("ChangeSlot").visible = not CCS_BattleManager.is_in_battle and CCS_PlayerData.get_team().creature_list.size() > 1 and swap_creature == null
	creature_options.options.get("Swap").visible = swap_creature != null
	creature_options.options.get("Info").visible = true
	
	creature_options.enable_options()
	var selected_option : StringName = await creature_options.option_selected
	creature_options.hide()
	
	match selected_option:
		"Switch":
			var can_switched : bool = await CCS_BattleManager.can_switch(CCS_PlayerData.get_team(), creature)
			if can_switched:
				_creature_switched(user, creature)
		"ChangeSlot":
			swap_creature = creature
		"Info":
			open_creature_info(creature)
			disable_cancel = false
			await creature_info_closed
		"Swap":
			if swap_creature != null:
				if swap_creature == creature:
					create_dialogue(CCS_BattleManager.same_swap_error_text, { "creature": creature.get_creature_name() })
				else:
					CCS_PlayerData.swap_creature_order(creature, swap_creature)
				swap_creature = null
			
	creature_last_focus.grab_focus()
	disable_cancel = false

func _attack_pressed() -> void:
	if hud_enable:
		await _enable_disable_hud()
	if not attack_enable:
		await _enable_disable_attack_bar()

func _creature_switch_pressed() -> void:
	if hud_enable:
		await _enable_disable_hud()
	await open_creature_party()

func _open_item_pressed() -> void:
	if hud_enable:
		await _enable_disable_hud()
	await open_item_bag()

func _on_flee_pressed() -> void:
	if hud_enable:
		await _enable_disable_hud()
	
	if not CCS_BattleManager.is_wild:
		await create_dialogue(CCS_BattleManager.trainer_flee_text)
		await _enable_disable_hud()
		return
	
	if CCS_BattleManager.is_boss:
		await create_dialogue(CCS_BattleManager.cant_escape_text)
		await _enable_disable_hud()
		return
	
	CCS_BattleManager.add_command.emit(CCS_BattleCommand_Flee.new())

func is_battle_ui_opened() -> bool:
	return (hud_enable or attack_enable or targets_enable or
			creature_enable or item_enable or disable_cancel or
			item_selected)

func _update_creature_info(creature : CCS_Creature) -> void:
	info_selected = creature
	var format : Dictionary[String, String] = {
		"name" : creature.get_creature_name(),
		"species" : creature.get_creature_species_name() if not creature.nickname.is_empty() else "",
		"level" : str(creature.stats.level),
		"xp" : str(roundi(creature.xp)),
		"xp_goal" : str(creature.stats.xp_goal),
		"health" : str(creature.health),
		"health_max" : str(creature.stats.health_point),
		"power" : str(creature.stats.power),
		"defense" : str(creature.stats.defense),
		"speed" : str(creature.stats.speed),
	}
	
	for label : Label in creature_info_label_texts:
		label.text = creature_info_label_texts.get(label).format(format)
	
	%CreatureInfoXPBar.value = creature.get_xp_percent()
	%CreatureInfoHealthBar.value = creature.get_health_percent()
	
	for extra_stat_label : Label in %CreatureInfoExtraStatContainer.get_children():
		if not extra_stat_label.name in creature.stats.other_stats:
			extra_stat_label.hide()
			continue
		
		extra_stat_label.show()
		extra_stat_label.text = creature_info_label_texts.get(extra_stat_label).format({
			"extra_stat_value" : creature.stats.other_stats.get(extra_stat_label.name)
		})
	
	var idx : int = 0
	for attack_label : Label in %CreatureInfoAttackContainer.get_children():
		var attack_format : Dictionary
		
		if creature.attack_pool.size() > idx:
			attack_format = {
				"attack_name" : CCS_BattleManager.static_data.attacks.get(creature.attack_pool.get(idx)).name
			}
		else:
			attack_format = {
				"attack_name" : "---"
			}
		
		attack_label.text = %CreatureInfoAttackLabel.text.format(attack_format)
		idx += 1
	
	if CCS_BattleManager.loaded_creature_sprite_library():
		creature_info_sprite.sprite_frames = CCS_BattleManager.creature_sprite_library
		
		if CCS_BattleManager.is_creature_sprite_available(creature.id + "_FRONT"):
			creature_info_sprite.play(creature.id + "_FRONT")

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("ui_cancel"):
		if $AnimationPlayer.is_playing():
			get_viewport().set_input_as_handled()
			return
		
		if disable_cancel:
			return
		
		if creature_info_enable:
			close_creature_info()
			get_viewport().set_input_as_handled()
			return
		
		if swap_creature:
			swap_creature = null
			get_viewport().set_input_as_handled()
			return

		if item_selected:
			item_creature_selected.emit(null)
			get_viewport().set_input_as_handled()
			return
		
		if targets_enable:
			target_selected.emit(null)
			get_viewport().set_input_as_handled()
			return
		
		if is_battle_ui_opened():
			_cancel_action()
			get_viewport().set_input_as_handled()
			return
	
	#if creature_info_enable:
		#if event.is_action_pressed("ui_right"):

func transition_playing() -> bool:
	return $AnimationPlayer.is_playing()

func play_transition(anim : String, speed_scale : float = 1) -> bool:
	if not $AnimationPlayer.has_animation(anim):
		return false
	transition_start.emit(anim)
	$AnimationPlayer.play(anim, -1, speed_scale)
	return true

func _signal_middle_transition() -> void:
	transition_middle.emit($AnimationPlayer.get_current_animation())

func _signal_end_transition() -> void:
	transition_end.emit($AnimationPlayer.get_current_animation())

func open_creature_info(creature : CCS_Creature) -> void:
	_update_creature_info(creature)
	
	if not creature_info_enable:
		await _enable_disable_creature_info()

func open_creature_party() -> void:
	if not creature_enable:
		await _enable_disable_creature_party()

func open_item_bag() -> void:
	if not item_enable:
		await _enable_disable_item_list()

func close_creature_info() -> void:
	if creature_info_enable:
		await _enable_disable_creature_info()
	
	creature_info_closed.emit()

func close_creature_party() -> void:
	if creature_enable:
		await _enable_disable_creature_party()

func close_item_bag() -> void:
	if item_enable:
		await _enable_disable_item_list()
