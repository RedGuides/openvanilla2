/*
 * MacroQuest2: The extension platform for EverQuest
 * Copyright (C) 2002-2019 MacroQuest Authors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#define DBG_SPEW


#include "MQ2Main.h"
DWORD __stdcall BeepOnTellThread(PVOID pData)
{
	Beep(750, 200);
	return 0;
}
DWORD __stdcall FlashOnTellThread(PVOID pData)
{
	DWORD lReturn = GetCurrentProcessId();
	DWORD pid = lReturn;
	AllowSetForegroundWindow(pid);
	BOOL ret = EnumWindows(EnumWindowsProc, (LPARAM)&lReturn);
	if (lReturn != pid) {
		//SetForegroundWindow((HWND)lReturn);
		FLASHWINFO fwi = { sizeof(FLASHWINFO) };
		fwi.dwFlags = FLASHW_ALL;
		fwi.hwnd = (HWND)lReturn;
		fwi.uCount = 3;
		fwi.dwTimeout = 0;
		FlashWindowEx(&fwi);
	}
	return 0;
}

class CChatHook
{
public:
	void Trampoline(const char* szMsg, DWORD dwColor, bool, bool, char *SomeStr);
	void Detour(const char* szMsg, DWORD dwColor, bool EqLog, bool dopercentsubst, char *SomeStr)
	{
		//DebugSpew("CChatHook::Detour(%s)",szMsg);
		gbInChat = TRUE;
		if (dwColor != 269)
		{
			CheckChatForEvent((char*)szMsg);
		}

		BOOL Filtered = FALSE;
		PFILTER Filter = gpFilters;
		while (Filter && !Filtered) {
			if (!Filter->pEnabled || (*Filter->pEnabled)) {
				if (*Filter->FilterText == '*') {
					if (strstr(szMsg, Filter->FilterText + 1))
						Filtered = TRUE;
				}
				else {
					if (!_strnicmp(szMsg, Filter->FilterText, Filter->Length))
						Filtered = TRUE;
				}
			}
			Filter = Filter->pNext;
		}

		if (!Filtered) {
			//if (gTelnetServer && gTelnetConnection && !gPauseTelnetOutput) TelnetServer_Write(szMsg); 
			BOOL SkipTrampoline;
			Benchmark(bmPluginsIncomingChat, SkipTrampoline = PluginsIncomingChat((char*)szMsg, dwColor));
			if (!SkipTrampoline) {
				if (gAnonymize && dwColor!=269 /*System messages don't need anon*/)
				{
					int len = strlen(szMsg);
					char myName[MAX_STRING] = "*";
					int namelen = 0;
					char *szAnonMsg = (char *)LocalAlloc(LPTR, len + 64);
					if (pLocalPlayer) {
						strcpy_s(myName, MAX_STRING, ((PSPAWNINFO)pLocalPlayer)->Name);
						namelen = strlen(myName);
						if (szAnonMsg) {
							strcpy_s(szAnonMsg, len + 64, szMsg);
							while (strstr(szAnonMsg, myName)) {
								if (char *p = strstr(szAnonMsg, myName)) {
									for (int i = 1; i < namelen - 1; i++) {
										p[i] = '*';
									}
								}
							}
						}
					}
					if (szAnonMsg) {
						if (char *pDest = strchr(szAnonMsg, ' ')) {
							int len = strlen(szAnonMsg) - strlen(pDest);
							if (len >= 2) {
								if (szAnonMsg[0] == 0x12) {
									for (int i = 3; i < len - 2; i++) {
										szAnonMsg[i] = '*';
									}
								}
								else {
									if (strstr(szAnonMsg, "You have healed ")) {
										for (int i = 17; i < 17 + namelen - 1; i++) {
											szAnonMsg[i] = '*';
										}
									}
									else if (_strnicmp(szAnonMsg, "you ", 4) && _strnicmp(szAnonMsg, "your ", 5)) {
										for (int i = 1; i < len - 1; i++) {
											szAnonMsg[i] = '*';
										}
									}
								}
							}
						}
						Trampoline(szAnonMsg, dwColor, EqLog, dopercentsubst, SomeStr);
						LocalFree(szAnonMsg);
					}
				}
				else {
					Trampoline(szMsg, dwColor, EqLog, dopercentsubst, SomeStr);
				}
			}
		}
		gbInChat = FALSE;
	}

	void TellWnd_Trampoline(char* message, char*from, char*windowtitle, char*text, int color, bool bLogOk);
	void TellWnd_Detour(char* message, char*from, char*windowtitle, char*text, int color, bool bLogOk)
	{
		int len = strlen(message);
		char *szMsg = (char *)LocalAlloc(LPTR, len + 64);
		BOOL SkipTrampoline = 0;
		gbInChat = true;
		if (szMsg) {
			sprintf_s(szMsg, len + 64, "%s tells you, '%s'", from, message);
			CheckChatForEvent(szMsg);
			Benchmark(bmPluginsIncomingChat, SkipTrampoline = PluginsIncomingChat(szMsg, color));
		}

		if (!SkipTrampoline) {
			if (gAnonymize) {
				CHAR *szName = new CHAR[64];
				strcpy_s(szName, 64, from);
				Anonymize(szName,64);
				TellWnd_Trampoline(message, szName, szName, text, color, bLogOk);
				delete szName;
			}
			else
			{
				TellWnd_Trampoline(message, from, windowtitle, text, color, bLogOk);
			}
		}
		if (szMsg)
			LocalFree(szMsg);
		gbInChat = false;
	}

	void UPCNotificationFlush_Trampoline();
	void UPCNotificationFlush_Detour()
	{
		if (EVERQUEST* eq = (EVERQUEST*)this) {
			CHAR szBuf[MAX_STRING] = { 0 };
			if (eq->ChannelQty > 0) {
				int len = 0;
				sprintf_s(szBuf, "* %s has %s channel ", eq->ChannelPlayerName, eq->bJoinedChannel ? "entered" : "left");
				CHAR szTemp[MAX_STRING] = { 0 };
				int max = eq->ChannelQty;
				if (max > 9)
					max = 9;
				for (int i = 0; i < max; i++) {
					if (i) {
						sprintf_s(szTemp, ", %s:%d", eq->ChannelName[i], eq->ChannelNumber[i] + 1);
					}
					else {
						sprintf_s(szTemp, "%s:%d", eq->ChannelName[i], eq->ChannelNumber[i] + 1);
					}
					strcat_s(szBuf, szTemp);
				}
				CheckChatForEvent(szBuf);
			}
		}
		UPCNotificationFlush_Trampoline();
	}
};

DETOUR_TRAMPOLINE_EMPTY(void CChatHook::Trampoline(const char* szMsg, DWORD dwColor, bool EqLog, bool dopercentsubst, char *SomeStr));
DETOUR_TRAMPOLINE_EMPTY(void CChatHook::TellWnd_Trampoline(char* message, char*from, char*windowtitle, char*text, int color, bool bLogOk));
DETOUR_TRAMPOLINE_EMPTY(void CChatHook::UPCNotificationFlush_Trampoline());

void dsp_chat_no_events(const char *Text, int Color, bool EqLog, bool dopercentsubst, char *SomeStr)
{
	((CChatHook*)pEverQuest)->Trampoline((PCHAR)Text, Color, EqLog, dopercentsubst, SomeStr);
}

unsigned int __stdcall MQ2DataVariableLookup(char * VarName, char * Value, size_t ValueLen)
{
	strcpy_s(Value, ValueLen, VarName);
	if (PCHARINFO pChar = GetCharInfo()) {
		return strlen(ParseMacroParameter(pChar->pSpawn, Value, ValueLen));
	}
	return strlen(Value);
}

void FlashOnTells(PSPAWNINFO pChar, PCHAR szLine)
{
	if (szLine[0] != '\0') {
		if (!_stricmp(szLine, "on")) {
			gbFlashOnTells = 0;
		}
		else if (!_stricmp(szLine, "off")) {
			gbFlashOnTells = 1;
		}
	}
	if (gbFlashOnTells) {
		gbFlashOnTells = 0;
		WriteChatColor("Flash On Tells is OFF", CONCOLOR_LIGHTBLUE);
		WritePrivateProfileString("MacroQuest", "FlashOnTells", "0", gszINIFilename);
	}
	else {
		gbFlashOnTells = 1;
		WriteChatColor("Flash On Tells is ON", CONCOLOR_YELLOW);
		WritePrivateProfileString("MacroQuest", "FlashOnTells", "1", gszINIFilename);
	}
}

void BeepOnTells(PSPAWNINFO pChar, PCHAR szLine)
{
	if (szLine[0] != '\0') {
		if (!_stricmp(szLine, "on")) {
			gbBeepOnTells = 0;
		}
		else if (!_stricmp(szLine, "off")) {
			gbBeepOnTells = 1;
		}
	}
	if (gbBeepOnTells) {
		gbBeepOnTells = 0;
		WriteChatColor("Beep On Tells is OFF", CONCOLOR_LIGHTBLUE);
		WritePrivateProfileString("MacroQuest", "BeepOnTells", "0", gszINIFilename);
	}
	else {
		gbBeepOnTells = 1;
		WriteChatColor("Beep On Tells is ON", CONCOLOR_YELLOW);
		WritePrivateProfileString("MacroQuest", "BeepOnTells", "1", gszINIFilename);
	}
}

void TimeStampChat(PSPAWNINFO pChar, PCHAR szLine)
{
	if (szLine[0] != '\0') {
		if (!_stricmp(szLine, "on")) {
			gbTimeStampChat = 0;
		}
		else if (!_stricmp(szLine, "off")) {
			gbTimeStampChat = 1;
		}
	}
	if (gbTimeStampChat) {
		gbTimeStampChat = 0;
		WriteChatColor("Chat Time Stamping is OFF", CONCOLOR_LIGHTBLUE);
		WritePrivateProfileString("MacroQuest", "TimeStampChat", "0", gszINIFilename);
	}
	else
	{
		gbTimeStampChat = 1;
		WriteChatColor("Chat Time Stamping is ON", CONCOLOR_YELLOW);
		WritePrivateProfileString("MacroQuest", "TimeStampChat", "1", gszINIFilename);
	}
}

void InitializeChatHook()
{
	DebugSpew("Initializing chat hook");

	// initialize Blech
	pEventBlech = new Blech('#', '|', MQ2DataVariableLookup);
	pMQ2Blech = new Blech('#', '|', MQ2DataVariableLookup);
	DebugSpew("%s", pMQ2Blech->Version);
	EzDetourwName(CEverQuest__dsp_chat, &CChatHook::Detour, &CChatHook::Trampoline, "CEverQuest__dsp_chat");
	EzDetourwName(CEverQuest__DoTellWindow, &CChatHook::TellWnd_Detour, &CChatHook::TellWnd_Trampoline, "CEverQuest__DoTellWindow");
	EzDetourwName(CEverQuest__UPCNotificationFlush, &CChatHook::UPCNotificationFlush_Detour, &CChatHook::UPCNotificationFlush_Trampoline, "CEverQuest__UPCNotificationFlush");
	AddCommand("/timestamp", TimeStampChat);
	AddCommand("/beepontells", BeepOnTells);
	AddCommand("/flashontells", FlashOnTells);
}

void ShutdownChatHook()
{
	RemoveCommand("/flashontells");
	RemoveCommand("/beepontells");
	RemoveCommand("/timestamp");
	RemoveDetour(CEverQuest__dsp_chat);
	RemoveDetour(CEverQuest__DoTellWindow);
	RemoveDetour(CEverQuest__UPCNotificationFlush);
	delete pEventBlech;
	delete pMQ2Blech;
	pMQ2Blech = 0;
}
