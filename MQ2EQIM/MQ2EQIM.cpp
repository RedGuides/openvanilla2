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

#include "../MQ2Plugin.h"

PreSetup("MQ2EQIM");
PLUGIN_VERSION(2.0);

#define BUDDY_OFFLINE   1
#define BUDDY_EQIM      2
#define BUDDY_EQIMAFK   3
#define BUDDY_ONLINE    5
#define BUDDY_ONLINEAFK 6

BOOL AnnounceBuddies=true;

PCHAR szBuddyStatus[]=
{
    "\a-wRemoved from list\ax",
    "\a-wOffline\ax",
    "\atEQIM\ax",
    "\a-tEQIM (AFK)\ax",
    "Unknown Status(4)",
    "\agPlaying\ax",
    "\a-gPlaying (AFK)\ax",
};

PCHAR szBuddyStatusNC[]=
{
    "Removed from list",
    "Offline",
    "EQIM",
    "EQIM (AFK)",
    "Unknown Status(4)",
    "Playing",
    "Playing (AFK)",
};

struct EQIMBuddy
{
    CHAR Name[MAX_STRING];
    DWORD Status;
    time_t LastSeen;
};


CIndex<EQIMBuddy*> BuddyList(10);
CHAR Character[MAX_STRING]={0};
BOOL BuddiesLoaded=false;


int FindEQIMBuddy(PCHAR Name)
{
    for (unsigned long N = 0 ; N < BuddyList.Size ; N++)
    {
        if (EQIMBuddy *pBuddy=BuddyList[N])
        {
            if (!_stricmp(pBuddy->Name,Name))
                return N;
        }
    }
    return -1;
}

//extern CHAR DataTypeTemp[MAX_STRING];

class MQ2BuddyType : public MQ2Type
{
public:
    enum BuddyMembers
    {
        Name=1,
        Status=2,
        StatusID=3,
        LastSeen=4,
    };

    MQ2BuddyType():MQ2Type("buddy")
    {
        TypeMember(Name);
        TypeMember(Status);
        TypeMember(StatusID);
        TypeMember(LastSeen);
    }

    ~MQ2BuddyType()
    {
    }

    bool MQ2BuddyType::GetMember(MQ2VARPTR VarPtr, PCHAR Member, PCHAR Index, MQ2TYPEVAR& Dest)
    {
        if (!VarPtr.Ptr)
            return false;
        EQIMBuddy *pBuddy = (EQIMBuddy*)VarPtr.Ptr;
        PMQ2TYPEMEMBER pMember=MQ2BuddyType::FindMember(Member);
        if (!pMember)
            return false;
        switch((BuddyMembers)pMember->ID)
        {
        case Name:
			strcpy_s(DataTypeTemp, pBuddy->Name);
			Dest.Ptr=&DataTypeTemp[0];
            Dest.Type=pStringType;
            return true;
        case Status:
			strcpy_s(DataTypeTemp, szBuddyStatusNC[pBuddy->Status]);
            Dest.Ptr=&DataTypeTemp[0];
            Dest.Type=pStringType;
            return true;
        case StatusID:
            Dest.DWord=pBuddy->Status;
            Dest.Type=pIntType;
            return true;
        case LastSeen:
		{
			struct tm* pTime = (struct tm*)&DataTypeTemp[0];
			ZeroMemory(pTime, sizeof(struct tm));
			localtime_s(pTime, (time_t*)&pBuddy->LastSeen);
			Dest.Ptr = pTime;
			Dest.Type = pTimeType;
			return true;
		}
        }

        return false;
    }

    bool ToString(MQ2VARPTR VarPtr, PCHAR Destination)
    {
        if (!VarPtr.Ptr)
            return false;
        strcpy_s(Destination,MAX_STRING,((EQIMBuddy*)VarPtr.Ptr)->Name);
        return true;
    }

    bool FromData(MQ2VARPTR &VarPtr, MQ2TYPEVAR &Source)
    {
        return false;
    }
    bool FromString(MQ2VARPTR &VarPtr, PCHAR Source)
    {
        return false;
    }
};

class MQ2BuddyType *pBuddyType=0;


BOOL dataBuddies(PCHAR szIndex, MQ2TYPEVAR &Ret)
{
    Ret.DWord=BuddyList.Size;
    Ret.Type=pIntType;
    return true;
}

BOOL dataBuddy(PCHAR szIndex, MQ2TYPEVAR &Ret)
{
    if (szIndex[0]>='0' && szIndex[0]<='9')
    {
        // by number
        unsigned long N=atoi(szIndex)-1;
        if (N<BuddyList.Size && BuddyList[N])
        {
            Ret.Ptr=BuddyList[N];
            Ret.Type=pBuddyType;
            return true;
        }
    }
    else
    {
        // by name
        int N=FindEQIMBuddy(szIndex);
        if (N>=0)
        {
            Ret.Ptr=BuddyList[N];
            Ret.Type=pBuddyType;
            return true;
        }
    }
    return false;
}

void OnBuddyStatusChange(char *Buddy, DWORD Status);
DWORD PreDetour[10]={0};
BOOL Detoured=false;
void SaveBuddyList();
void LoadBuddyList();
void BuddiesCmd(PSPAWNINFO pChar, PCHAR Line);

void SetVTable(DWORD index, DWORD value)
{
    DWORD oldperm=0;
    DWORD Address=(DWORD)&(*((DWORD**)pEverQuest))[index];
    DebugSpewAlways("SetVTable writing at address %X to %X",Address,value);
    VirtualProtectEx(GetCurrentProcess(), (LPVOID)Address, 4,PAGE_EXECUTE_READWRITE, &oldperm);
    WriteProcessMemory(
        GetCurrentProcess(),
        (LPVOID)Address,
        (LPVOID)&value,
        4,
        NULL);
    VirtualProtectEx(GetCurrentProcess(), (LPVOID)Address, 4, oldperm, &oldperm);
}

DWORD GetVTable(DWORD index)
{
    DWORD Ret=(*((DWORD**)pEverQuest))[index];
    DebugSpewAlways("GetVTable(%d)=%X",index,Ret);
    return Ret;
}



PLUGIN_API void InitializePlugin()
{
    DebugSpewAlways("Initializing MQ2EQIM");

    // Add commands, macro parameters, hooks, etc.
    // AddCommand("/mycommand",MyCommand);
    // AddParm("$myparm(x)",MyParm);
    pBuddyType = new MQ2BuddyType;    
    AddMQ2Data("Buddy",dataBuddy);
    AddMQ2Data("Buddies",dataBuddies);
    AddCommand("/buddies",BuddiesCmd);
}

// Called once, when the plugin is to shutdown
PLUGIN_API void ShutdownPlugin()
{
    DebugSpewAlways("Shutting down MQ2EQIM");

    // Remove commands, macro parameters, hooks, etc.
    // RemoveParm("$myparm(x)");
    // RemoveCommand("/mycommand");
    if (Detoured && pEverQuest)
        SetVTable(8,PreDetour[8]);
    RemoveMQ2Data("Buddy");
    RemoveMQ2Data("Buddies");
    if (BuddiesLoaded)
        SaveBuddyList();
    BuddyList.Cleanup();
    delete pBuddyType;
    RemoveCommand("/buddies");
}

// Called once directly after initialization, and then every time the gamestate changes

PLUGIN_API void SetGameState(DWORD GameState)
{
    //DebugSpewAlways("MQ2EQIM::SetGameState()");
    if (GameState==GAMESTATE_INGAME)
    {
        if (!Detoured)
        {
            PreDetour[8]=GetVTable(8);
            SetVTable(8,(DWORD)OnBuddyStatusChange);
            GetVTable(8);
            Detoured=true;
        }
        if (!BuddiesLoaded)
        {
            BuddiesLoaded=true;
            LoadBuddyList();
        }
    }
    else if (GameState==GAMESTATE_CHARSELECT)
    {
        if (BuddiesLoaded)
        {
            BuddiesLoaded=false;
        }
        BuddyList.Cleanup();
    }
}

void OnBuddyStatusChange(char *Buddy, DWORD Status)
{
    int N=FindEQIMBuddy(Buddy);
    if (N==-1)
    {
        EQIMBuddy *pBuddy = new EQIMBuddy;
        strcpy_s(pBuddy->Name,Buddy);
        pBuddy->Status=Status;
        if (Status==BUDDY_OFFLINE)
            pBuddy->LastSeen=0;
        else
            pBuddy->LastSeen=time(0);
        BuddyList+=pBuddy;
    }
    else
    {
        BuddyList[N]->Status=Status;
        if (Status==BUDDY_OFFLINE)
            BuddyList[N]->LastSeen=0;
        else
            BuddyList[N]->LastSeen=time(0);

        if (Status==0) // removed from list
        {
            delete BuddyList[N];
            BuddyList[N]=0;
        }
    }
    SaveBuddyList();

    if (AnnounceBuddies)
    {
        char out[MAX_STRING]={0};
        if (Status<=6)
        {
            sprintf_s(out,"\ar*\ax %s: %s",Buddy,szBuddyStatus[Status]);
        }
        else
            sprintf_s(out,"\ar*\ax Unknown Status(%d)",Status);
        WriteChatColor(out);
    }
}

void LoadBuddyList()
{
    BuddyList.Cleanup();

    sprintf_s(Character,"%s.%s",EQADDR_SERVERNAME,((PCHARINFO)pCharData)->Name);

    // load buddies per char
    CHAR FullList[MAX_STRING*10] = {0};
    CHAR szBuffer[MAX_STRING] = {0};
    CHAR szCommand[MAX_STRING] = {0};
    GetPrivateProfileString(Character,NULL,"",FullList,MAX_STRING*10,INIFileName);
    PCHAR pFullList = FullList;
    while (pFullList[0]!=0) {
        GetPrivateProfileString(Character,FullList,"",szBuffer,MAX_STRING,INIFileName);
        if (szBuffer[0]!=0) {
            //LoadMQ2Plugin(szBuffer);
            if (FindEQIMBuddy(szBuffer)==-1)
            {
                sprintf_s(szCommand,"[buddy %s",szBuffer);
                DoCommand((PSPAWNINFO)pLocalPlayer,szCommand);
                EQIMBuddy *pBuddy = new EQIMBuddy;
                strcpy_s(pBuddy->Name,szBuffer);
                pBuddy->Status=BUDDY_OFFLINE;
                pBuddy->LastSeen=0;
                BuddyList+=pBuddy;
            }
        }
        pFullList+=strlen(pFullList)+1;
    }    

    // import friends list
    unsigned long N;
    unsigned long nfriends=pChatService->GetNumberOfFriends();
    for (N = 0 ; N < nfriends ; N++)
    {
        sprintf_s(szCommand,";buddy %s",pChatService->GetFriendName(N));
        DoCommand((PSPAWNINFO)pLocalPlayer,szCommand);
    }

    // import "last seen" global
    for ( N = 0 ; N < BuddyList.Size ; N++)
    {
        if (EQIMBuddy *pBuddy = BuddyList[N])
        {
            pBuddy->LastSeen=GetPrivateProfileInt("LastSeen",pBuddy->Name,0,INIFileName);
        }
    }
}
template <unsigned int _Size>LPSTR SafeItoa(int _Value,char(&_Buffer)[_Size], int _Radix)
{
	errno_t err = _itoa_s(_Value, _Buffer, _Radix);
	if (!err) {
		return _Buffer;
	}
	return "";
}
void SaveBuddyList()
{
    CHAR Buffer[MAX_STRING]={0};

    // save buddies per char and "last seen" global
    WritePrivateProfileSection(Character,"",INIFileName);

    for (unsigned long N = 0 ; N < BuddyList.Size ; N++)
    {
        if (EQIMBuddy *pBuddy = BuddyList[N])
        {
            WritePrivateProfileString(Character,pBuddy->Name,pBuddy->Name,INIFileName);
            WritePrivateProfileString("LastSeen",pBuddy->Name,SafeItoa((int)pBuddy->LastSeen,Buffer,10),INIFileName);
        }
    }
}

void BuddiesCmd(PSPAWNINFO pChar, PCHAR Line)
{
    BOOL bOnline=true;
    BOOL bOffline=false;
    BOOL bEQIM=true;
    CHAR Buffer[MAX_STRING]={0};
    if (Line[0])
    {
        strcpy_s(Buffer,Line);
        _strlwr_s(Buffer);
        bOnline=(strstr(Buffer,"on")!=0);
        bEQIM=(strstr(Buffer,"eqim")!=0);
        bOffline=(strstr(Buffer,"off")!=0);
    }
    unsigned long Count=0;
    WriteChatColor("List of Buddies");
    WriteChatColor("---------------");
    for (unsigned long N = 0 ; N < BuddyList.Size ; N++)
    {
        if (EQIMBuddy *pBuddy = BuddyList[N])
        {
            switch(pBuddy->Status)
            {
            case BUDDY_OFFLINE:
                if (bOffline)
                {
					struct tm theTime = { 0 };
					localtime_s(&theTime,(time_t*)&pBuddy->LastSeen);
                    Count++;
                    sprintf_s(Buffer,"\ar*\ax %s: %s - Last Seen %02d:%02d:%02d %02d/%02d/%04d",pBuddy->Name,szBuddyStatus[pBuddy->Status],theTime.tm_hour,theTime.tm_min, theTime.tm_sec,theTime.tm_mon+1,theTime.tm_mday, theTime.tm_year+1900);
                    WriteChatColor(Buffer);
                }
                break;
            case BUDDY_EQIM:
            case BUDDY_EQIMAFK:
                if (bEQIM)
                {
                    Count++;
                    sprintf_s(Buffer,"\ar*\ax %s: %s",pBuddy->Name,szBuddyStatus[pBuddy->Status]);
                    WriteChatColor(Buffer);
                }
                break;
            case BUDDY_ONLINE:
            case BUDDY_ONLINEAFK:
                if (bOnline)
                {
                    Count++;
                    sprintf_s(Buffer,"\ar*\ax %s: %s",pBuddy->Name,szBuddyStatus[pBuddy->Status]);
                    WriteChatColor(Buffer);
                }
                break;
            }
        }
    }
    sprintf_s(Buffer,"\ag%d\ax buddies matching\at%s%s%s\ax",Count,bEQIM?" EQIM":"",bOffline?" offline":"",bOnline?" online":"");
    WriteChatColor(Buffer);
}

