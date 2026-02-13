extends NPC

const battled_variable_name : StringName = "battled_{0}"

@export var data : CCS_BattleTeam
@export var battle_dialogue : Array[String]
@export var is_double : bool = false
@export var money : int = 200

@onready var raycast : RayCast3D = $RayCast3D
@onready var trainer_money_functions : Game_TrainerMoney = Game_TrainerMoney.new(money)

signal battle_initiated

var var_name : StringName
var battled : bool = false

func _ready() -> void:
	var_name = battled_variable_name.format([data.get_trainer_name()])
	if CCS_PlayerData.get_variable(var_name) == null:
		CCS_PlayerData.set_variable(var_name, false)
	
	battled = CCS_PlayerData.get_variable(var_name)
	
	super()

func _physics_process(delta: float) -> void:
	if not (disabled or battled):
		if (raycast.is_colliding()):
			var obj := raycast.get_collider()
			if obj == GameBase.player:
				GameBase.player.disabled = true
				await _spotted_player()

func _spotted_player() -> void:
	battle_initiated.emit()
	disabled = true
	var particle : GPUParticles3D = Game_Manager.exclaim_particle_scene.instantiate()
	
	add_child(particle)
	particle.position = Vector3.ZERO
	
	await particle.finished
	await Game_DialogueBox.display_dialogue(battle_dialogue)
	
	await _initialize_battle()
	

func _initialize_battle():
	for creature : CCS_Creature in data.creature_list:
		creature.reset_health()
	
	var teams : Array[CCS_BattleTeam] = [data]
	
	if is_double:
		teams.append(data)
	
	CCS_BattleManager.trainer_battle(teams)
	CCS_BattleManager.additional_functions["trainer_money"] = trainer_money_functions
	battled = not await CCS_BattleManager.battle_end
	CCS_BattleManager.additional_functions.erase("trainer_money")
	CCS_PlayerData.set_variable(var_name, battled)
	
	if battled:
		await Game_DialogueBox.display_dialogue(data.defeat_text)
		GameBase.player.disabled = false
	
	disabled = false

func talk(facing : Vector3) -> void:
	if disabled:
		return
	
	if battled:
		await super(facing)
		
		if CCS_PlayerData.get_variable("boss_defeated"):
			var option : int = await Game_DialogueBox.display_dialogue_with_options("[Would you like to initiate a rematch?]", ["Yes", "No"], 1)
			if option == 0:
				await _initialize_battle()
		return
	
	_face_direction(facing)
	await _spotted_player()
