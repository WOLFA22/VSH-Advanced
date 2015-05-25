// vsha_CreateTimer_WatchGameMode.inc

public Action WatchGameModeTimer(Handle hTimer)
{
	if(!bEnabled.BoolValue) return Plugin_Continue;

	int BossCount = 0;
	LoopActiveBosses(iBossNum)
	{
		BossCount++;
	}
	//DP("BossCount %d",BossCount);
	int TeamBlueCount = 0;
	LoopIsInTeam(TEAM_BLUE,iTarget)
	{
		TeamBlueCount++;
	}
	//DP("TeamBlueCount %d",TeamBlueCount);
	int TeamRedCount = 0;
	LoopIsInTeam(TEAM_RED,iTarget)
	{
		TeamRedCount++;
	}
	//DP("TeamRedCount %d",TeamRedCount);
	if(BossCount <= 0 && TeamBlueCount <= 0 && TeamRedCount > 0)
	{
		// nobody on blue, no bosses!
		int boss = -1;
		boss = FindNextBoss(bIsBoss);

		if(ValidPlayer(boss))
		{
			iBossUserID[boss] = GetClientUserId(boss);
			bIsBoss[boss] = true;
			Storage[boss] = PickBossSpecial(iPresetBoss[boss]);

			ForceTeamChange(boss,TEAM_BLUE);
			return Plugin_Continue;
		}
	}
	else if(BossCount <= 0 && TeamBlueCount > 0 && TeamRedCount > 0)
	{
		// no bosses, enough players

		int boss = -1;
		boss = FindNextBoss(bIsBoss);

		if(ValidPlayer(boss))
		{
			iBossUserID[boss] = GetClientUserId(boss);
			bIsBoss[boss] = true;
			Storage[boss] = PickBossSpecial(iPresetBoss[boss]);

			LoopAlivePlayers(iTarget)
			{
				ForcePlayerSuicide(iTarget);
			}
			ForceTeamChange(boss,TEAM_BLUE);

			CPrintToChatAll("{lightgreen}No Boss??\nRestarting Game...");
			return Plugin_Continue;
		}
	}
	else if(BossCount > 0)
	{
		CPrintToChatAll("{lightgreen}Bosses in the House!\nStarting Round!");
		LoopAlivePlayers(iTarget)
		{
			ForcePlayerSuicide(iTarget);
		}
		return Plugin_Stop;
	}
	return Plugin_Continue;
}