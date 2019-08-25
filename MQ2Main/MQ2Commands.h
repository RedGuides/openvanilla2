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

#pragma once

#if defined(ISXEQ_LEGACY) || !defined(ISXDK_VERSION)

/* COMMANDS */
EQLIB_API void SetError                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void SuperWho                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void NewIf                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void WhileCmd                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void PluginCommand                       (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Call                                (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DeclareVar                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DumpStack                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void EditMacro                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void EndMacro                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void For                                 (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Goto                                (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void KeepKeys                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Macro                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MacroPause                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Next                                (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Return                              (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Break                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Continue                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void ListMacros                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void SquelchCommand                      (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MacroLog                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MacroBeep                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Echo                                (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void NoParseCmd                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void NoModKeyCmd                         (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Where                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void CaptionColorCmd                     (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void CaptionCmd                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void HudCmd                              (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DropCmd                             (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void CombineCmd                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void ClearErrorsCmd                      (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoTimedCmd                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoShiftCmd                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoCtrlCmd                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoAltCmd                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoCommandCmd                        (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DumpBindsCommand                    (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void LoadCfgCommand                      (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void do_ranged                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoMappable                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MQ2KeyBindCommand                   (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MultilineCommand                    (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Alert                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Alias                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void AltAbility                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void BankList                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Breakin                             (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void BuyItem                             (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void SelectItem                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void CharInfo                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Cast                                (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Cleanup                             (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Click                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DebugSpewFile                       (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Delay                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void EQDestroyHeldItemOrMoney            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DisplayLoginName                    (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoAbility                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoEvents                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoSocial                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Doors                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void DoorTarget                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Exec                                (PSPAWNINFO pChar, PCHAR szLine); 
EQLIB_API void Face                                (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Filter                              (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Help                                (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Hotkey                              (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Identify                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void IniOutput                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Items                               (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void ItemTarget                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void WindowState                         (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void LoadSpells                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Location                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Look                                (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void LootAll                             (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MemSpell                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MouseTo                             (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MQMsgBox                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void SellItem                            (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void SetAutoRun                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Skills                              (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Substitute                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void SuperWhoTarget                      (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void SWhoFilter                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Target                              (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void Unload                              (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void UpdateItemInfo                      (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void ZapVars                             (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void PopupText                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void PopupTextCustom                     (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void PopupTextEcho                       (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void UseItemCmd                          (PSPAWNINFO pChar, PCHAR szLine);

EQLIB_API void SpellSlotInfo                       (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void SetWinTitle                         (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void GetWinTitle                         (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void PetCmd                              (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MercSwitchCmd                       (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void AdvLootCmd                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void PickZoneCmd                         (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void AssistCmd                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void InvokeCmd                           (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void SetProcessPriority                  (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void ScreenModeCmd                       (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void UserCameraCmd                       (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void MapZoomCmd                          (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void ForeGroundCmd                       (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void QuitCmd                             (PSPAWNINFO pChar, PCHAR szLine);
EQLIB_API void PluginCmdSort                       ();
#endif
