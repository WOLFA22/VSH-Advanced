// vsha_000_RegConsoleCmd.inc

public Action CommandMakeNextSpecial(int client, int args)
{
	char arg[32], name[64];
	if (args < 1)
	{
		ReplyToCommand(client, "[VSH Engine] Usage: vsha_special <boss name>");
		return Plugin_Handled;
	}
	GetCmdArgString(arg, sizeof(arg));

	int count = hArrayBossSubplugins.Length; //GetArraySize(hArrayBossSubplugins);
	for (int i = 0; i < count; i++)
	{
		//GetTrieString(GetArrayCell(hArrayBossSubplugins, i), "BossName", name, sizeof(name));
		GetTrieString(hArrayBossSubplugins.Get(i), "BossName", name, sizeof(name));
		if (StrContains(arg, name, false) != -1)
		{
			iPresetBoss[FindNextBoss(bIsBoss)] = i;
			break;
		}
	}
	ReplyToCommand(client, "[VSH Engine] Set the next Special to %s", name);
	return Plugin_Handled;
}
public Action PickBossMenu(int client, int args)
{
	if (Enabled && IsClientInGame(client))
	{
		Menu pickboss = new Menu(MenuHandler_PickBoss);
		//Handle MainMenu = CreateMenu(MenuHandler_Perks);
		pickboss.SetTitle("[VSH Engine] Choose A Boss");
		int count = hArrayBossSubplugins.Length; //GetArraySize(hArrayBossSubplugins);
		for (int i = 0; i < count; i++)
		{
			//GetTrieString(GetArrayCell(hArrayBossSubplugins, i), "BossName", bossnameholder, sizeof(bossnameholder));
			char bossnameholder[32];
			GetTrieString(hArrayBossSubplugins.Get(i), "BossName", bossnameholder, sizeof(bossnameholder));
			pickboss.AddItem("pickclass", bossnameholder);
		}
		pickboss.Display(client, MENU_TIME_FOREVER);
	}
	return Plugin_Handled;
}
public int MenuHandler_PickBoss(Menu menu, MenuAction action, int client, int selection)
{
	char blahblah[32];
	menu.GetItem(selection, blahblah, sizeof(blahblah));
	if (action == MenuAction_Select)
        {
		char bossnameholder[32];
		GetTrieString(hArrayBossSubplugins.Get(selection), "BossName", bossnameholder, sizeof(bossnameholder));
		ReplyToCommand(client, "[VSH Engine] You selected %s as your boss!", bossnameholder);
		iPresetBoss[client] = selection;
        }
	else if (action == MenuAction_End) delete menu;
}

public Action Command_forceboss(int client, int args)
{
	if (Enabled && IsClientInGame(client))
	{
		Menu pickboss = new Menu(MenuHandler_ForceBoss);
		//Handle MainMenu = CreateMenu(MenuHandler_Perks);
		pickboss.SetTitle("[VSH Engine] Choose A Boss");
		int count = hArrayBossSubplugins.Length; //GetArraySize(hArrayBossSubplugins);
		for (int i = 0; i < count; i++)
		{
			//GetTrieString(GetArrayCell(hArrayBossSubplugins, i), "BossName", bossnameholder, sizeof(bossnameholder));
			char bossnameholder[32];
			GetTrieString(hArrayBossSubplugins.Get(i), "BossName", bossnameholder, sizeof(bossnameholder));
			pickboss.AddItem("pickclass", bossnameholder);
		}
		pickboss.Display(client, MENU_TIME_FOREVER);
	}
	return Plugin_Handled;
}
public int MenuHandler_ForceBoss(Menu menu, MenuAction action, int client, int selection)
{
	char blahblah[32];
	menu.GetItem(selection, blahblah, sizeof(blahblah));
	if (action == MenuAction_Select)
	{
		char bossnameholder[32];
		GetTrieString(hArrayBossSubplugins.Get(selection), "BossName", bossnameholder, sizeof(bossnameholder));
		ReplyToCommand(client, "[VSH Engine] You selected %s as your boss!", bossnameholder);
		iPresetBoss[client] = selection;

		SetClientQueuePoints(client, 99999);
	}
	else if (action == MenuAction_End) delete menu;
}