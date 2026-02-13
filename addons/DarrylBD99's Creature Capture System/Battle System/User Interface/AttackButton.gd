extends Button
class_name CCS_BattleUI_AttackButton

var has_attack_data : bool:
	get():
		return CCS_BattleManager.static_data.attacks.get(name) != null

func _init(attack_id : StringName) -> void:
	if attack_id.is_empty():
		_disable_button()
		return
	
	name = attack_id
	var attack : CCS_StaticData_Attack = CCS_BattleManager.static_data.attacks.get(attack_id)
	has_attack_data = attack != null
	
	if not has_attack_data:
		_disable_button()
		return
	
	text = attack.name

func _disable_button() -> void:
	disabled = true
	text = "---"
	focus_mode = Control.FOCUS_NONE
