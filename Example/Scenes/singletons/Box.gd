extends CCS_AdditionalBattleFunctions
class_name Game_BoxFunction

const party_full_dialogue : Array[String] = ["Your party is full, {creature} is sent to the Box."]

func creature_captured(creature : CCS_Creature) -> void:
	if CCS_PlayerData.get_team().creature_list.size() > CCS_BattleManager.max_team_size:
		await CCS_BattleUIManager.create_dialogue(party_full_dialogue, { "creature" : creature.get_creature_name() })
		
		var team : CCS_BattleTeam = CCS_PlayerData.get_team()
		team.creature_list.remove_at(team.creature_list.find(creature))
		
		if CCS_PlayerData.get_variable("Game_Box") == null:
			CCS_PlayerData.set_variable("Game_Box", [])
		
		CCS_PlayerData.player_data.variables["Game_Box"].append(creature)
