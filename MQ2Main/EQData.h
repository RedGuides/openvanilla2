/*****************************************************************************
    MQ2Main.dll: MacroQuest2's extension DLL for EverQuest
    Copyright (C) 2002-2003 Plazmic, 2003-2005 Lax

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/
namespace EQData
{

// ***************************************************************************
// Defines
// ***************************************************************************

#define AllClassesMASK		0xFFFF
#define WarriorMASK			0x0001
#define ClericMASK			0x0002
#define RogueMASK			0x0100
#define WizardMASK			0x0400

enum PlayerClass
{
    Unknown=                            0,
    Warrior=                            1,
    Cleric=                             2,
    Paladin=                            3,
    Ranger=                             4,
    Shadowknight=                       5,
    Druid=                              6,
    Monk=                               7,
    Bard=                               8,
    Rogue=                              9,
    Shaman=                            10,
    Necromancer=                       11,
    Wizard=                            12,
    Mage=                              13,
    Enchanter=                         14,
    Beastlord=                         15,
    Berserker=                         16,
	Mercenary=                         17,
    TotalClasses=                      17,
};
// class 20 through 35 are the NPC GMs (same class order as above)
// class 41   Merchant
// class 60   LDoN Recruiter
// class 61   LDoN Merchant
// class 63   Tribute Master
// class 67   DoN Merchant (Norrath's Keepers)
// class 68   DoN Merchant (Dark Reign)

typedef struct _ClassInfo
{
    bool CanCast;
    bool PureCaster;
    bool PetClass;
    bool DruidType;
    bool NecroType;
    bool ClericType;
    bool ShamanType;
	bool MercType;
    char RaidColorOrder;
    PCHAR Name;
    PCHAR ShortName;
	PCHAR UCShortName;
} CLASSINFO, *PCLASSINFO;

static _ClassInfo ClassInfo[]=
{
    {0,0,0,0,0,0,0,0,0,"","",""},                         //unk
    {0,0,0,0,0,0,0,0,13,"Warrior","war","WAR"},           //war
    {1,1,0,0,0,1,0,0,2,"Cleric","clr","CLR"},             //clr
    {1,0,0,0,0,1,0,0,8,"Paladin","pal","PAL"},            //pal
    {1,0,0,1,0,0,0,0,9,"Ranger","rng","RNG"},             //rng
    {1,0,0,0,1,0,0,0,11,"Shadowknight","shd","SHD"},      //shd
    {1,1,0,1,0,0,0,0,3,"Druid","dru","DRU"},              //dru
    {0,0,0,0,0,0,0,0,6,"Monk","mnk","MNK"},               //mnk
    {1,0,0,0,0,0,0,0,0,"Bard","brd","BRD"},               //brd
    {0,0,0,0,0,0,0,0,10,"Rogue","rog","ROG"},             //rog
    {1,1,1,0,0,0,1,0,12,"Shaman","shm","SHM"},            //shm
    {1,1,1,0,1,0,0,0,7,"Necromancer","nec","NEC"},        //nec
    {1,1,0,0,0,0,0,0,14,"Wizard","wiz","WIZ"},            //wiz
    {1,1,1,0,0,0,0,0,5,"Mage","mag","MAG"},               //mag
    {1,1,0,0,0,0,0,0,4,"Enchanter","enc","ENC"},          //enc
    {1,0,1,0,0,0,1,0,1,"Beastlord","bst","BST"},          //bst
    {0,0,0,0,0,0,0,0,15,"Berserker","ber","BER"},         //ber
	{1,1,0,0,0,0,0,1,16,"Mercenary","mer","MER"},         //mer
};

#define BI_TARGETABLE                   1
#define BI_TRIGGER                      2 
#define BI_TRAP                         4
#define BI_TIMER                        8

typedef struct _BodyInfo
{
    PCHAR Name;
    DWORD Flags;
} BODYINFO, *PBODYINFO;

#define SPAWN_PLAYER                    0
#define SPAWN_NPC                       1
#define SPAWN_CORPSE                    2
//#define SPAWN_ANY                       3
//#define SPAWN_PET                       4

#define ITEM_NORMAL1                    0x0031
#define ITEM_NORMAL2                    0x0036
#define ITEM_NORMAL3                    0x315f
#define ITEM_NORMAL4                    0x3336
#define ITEM_NORMAL5                    0x0032
#define ITEM_NORMAL6                    0x0033
#define ITEM_NORMAL7                    0x0034
#define ITEM_NORMAL8                    0x0039
#define ITEM_CONTAINER                  0x7900
#define ITEM_CONTAINER_PLAIN            0x7953
#define ITEM_BOOK                       0x7379

#define ITEMITEMTYPE_FOOD               0x0e 
#define ITEMITEMTYPE_WATER              0x0f 
#define ITEMITEMTYPE_SCROLL				0x14
#define ITEMITEMTYPE_ALCOHOL            0x26 
#define ITEMITEMTYPE_POISON             0x2a 
#define ITEMITEMTYPE_AUGUMENT           0x36 

#define ITEMEFFECTTYPE_COMBAT           0x00 
#define ITEMEFFECTTYPE_INVENTORY1       0x01 // Bards need to stop sing to cast 
#define ITEMEFFECTTYPE_WORN             0x02 
#define ITEMEFFECTTYPE_INVENTORY2       0x03 
#define ITEMEFFECTTYPE_MUSTEQUIP        0x04 // Bards need to stop sing to cast 
#define ITEMEFFECTTYPE_INVENTORY3       0x05 

#define SKILLMINDAMAGEMOD_BASH          0x00 
#define SKILLMINDAMAGEMOD_BACKSTAB      0x01 
#define SKILLMINDAMAGEMOD_DRAGONPUNCH   0x02 
#define SKILLMINDAMAGEMOD_EAGLESTRIKE   0x03 
#define SKILLMINDAMAGEMOD_FLYINGKICK    0x04 
#define SKILLMINDAMAGEMOD_KICK          0x05 
#define SKILLMINDAMAGEMOD_ROUNDKICK     0x06 
#define SKILLMINDAMAGEMOD_TIGERCLAW     0x07 
#define SKILLMINDAMAGEMOD_FRENZY        0x08 

//Heroic Mods
#define HEROIC_MOD_SPELL_SHIELDING      0x4
#define HEROIC_MOD_COMBAT_EFFECTS       0x5
#define HEROIC_MOD_MELEE_SHIELDING      0x6
#define HEROIC_MOD_DAMAGE_SHIELDING     0x7
#define HEROIC_MOD_DOT_SHIELDING        0x8
#define HEROIC_MOD_DAMAGE_SHIELD_MITIG  0x9
#define HEROIC_MOD_AVOIDANCE            0xa
#define HEROIC_MOD_ACCURACY             0xb
#define HEROIC_MOD_STUN_RESIST          0xc
#define HEROIC_MOD_STRIKETHROUGH        0xd

#define COLOR_DEFAULT                   0x00
#define COLOR_DARKGREY                  0x01
#define COLOR_DARKGREEN                 0x02
#define COLOR_DARKBLUE                  0x03
#define COLOR_PURPLE                    0x05
#define COLOR_LIGHTGREY                 0x06

#define CONCOLOR_GREY                   0x06
#define CONCOLOR_GREEN                  0x02
#define CONCOLOR_LIGHTBLUE              0x12
#define CONCOLOR_BLUE                   0x04
#define CONCOLOR_BLACK                  0x14
#define CONCOLOR_WHITE                  0x0a
#define CONCOLOR_YELLOW                 0x0f
#define CONCOLOR_RED                    0x0d

#define USERCOLOR_SAY                   0xFF +   1 //  1  - Say
#define USERCOLOR_TELL                  0xFF +   2 //  2  - Tell
#define USERCOLOR_GROUP                 0xFF +   3 //  3  - Group
#define USERCOLOR_GUILD                 0xFF +   4 //  4  - Guild
#define USERCOLOR_OOC                   0xFF +   5 //  5  - OOC
#define USERCOLOR_AUCTION               0xFF +   6 //  6  - Auction
#define USERCOLOR_SHOUT                 0xFF +   7 //  7  - Shout
#define USERCOLOR_EMOTE                 0xFF +   8 //  8  - Emote
#define USERCOLOR_SPELLS                0xFF +   9 //  9  - Spells (meming, scribing, casting, etc.)
#define USERCOLOR_YOU_HIT_OTHER         0xFF +  10 //  10 - You hit other
#define USERCOLOR_OTHER_HIT_YOU         0xFF +  11 //  11 - Other hits you
#define USERCOLOR_YOU_MISS_OTHER        0xFF +  12 //  12 - You miss other
#define USERCOLOR_OTHER_MISS_YOU        0xFF +  13 //  13 - Other misses you
#define USERCOLOR_DUELS                 0xFF +  14 //  14 - Some broadcasts (duels)
#define USERCOLOR_SKILLS                0xFF +  15 //  15 - Skills (ups, non-combat use, etc.)
#define USERCOLOR_DISCIPLINES           0xFF +  16 //  16 - Disciplines or special abilities
#define USERCOLOR_UNUSED001             0xFF +  17 //  17 - Unused at this time
#define USERCOLOR_DEFAULT               0xFF +  18 //  18 - Default text and stuff you type
#define USERCOLOR_UNUSED002             0xFF +  19 //  19 - Unused at this time
#define USERCOLOR_MERCHANT_OFFER        0xFF +  20 //  20 - Merchant Offer Price
#define USERCOLOR_MERCHANT_EXCHANGE     0xFF +  21 //  21 - Merchant Buy/Sell
#define USERCOLOR_YOUR_DEATH            0xFF +  22 //  22 - Your death message
#define USERCOLOR_OTHER_DEATH           0xFF +  23 //  23 - Others death message
#define USERCOLOR_OTHER_HIT_OTHER       0xFF +  24 //  24 - Other damage other
#define USERCOLOR_OTHER_MISS_OTHER      0xFF +  25 //  25 - Other miss other
#define USERCOLOR_WHO                   0xFF +  26 //  26 - /who command
#define USERCOLOR_YELL                  0xFF +  27 //  27 - yell for help
#define USERCOLOR_NON_MELEE             0xFF +  28 //  28 - Hit for non-melee
#define USERCOLOR_SPELL_WORN_OFF        0xFF +  29 //  29 - Spell worn off
#define USERCOLOR_MONEY_SPLIT           0xFF +  30 //  30 - Money splits
#define USERCOLOR_LOOT                  0xFF +  31 //  31 - Loot message
#define USERCOLOR_RANDOM                0xFF +  32 //  32 - Dice Roll (/random)
#define USERCOLOR_OTHERS_SPELLS         0xFF +  33 //  33 - Others spells
#define USERCOLOR_SPELL_FAILURE         0xFF +  34 //  34 - Spell Failures (resists, fizzles, missing component, bad target, etc.)
#define USERCOLOR_CHAT_CHANNEL          0xFF +  35 //  35 - Chat Channel Messages
#define USERCOLOR_CHAT_1                0xFF +  36 //  36 - Chat Channel 1
#define USERCOLOR_CHAT_2                0xFF +  37 //  37 - Chat Channel 2
#define USERCOLOR_CHAT_3                0xFF +  38 //  38 - Chat Channel 3
#define USERCOLOR_CHAT_4                0xFF +  39 //  39 - Chat Channel 4
#define USERCOLOR_CHAT_5                0xFF +  40 //  40 - Chat Channel 5
#define USERCOLOR_CHAT_6                0xFF +  41 //  41 - Chat Channel 6
#define USERCOLOR_CHAT_7                0xFF +  42 //  42 - Chat Channel 7
#define USERCOLOR_CHAT_8                0xFF +  43 //  43 - Chat Channel 8
#define USERCOLOR_CHAT_9                0xFF +  44 //  44 - Chat Channel 9
#define USERCOLOR_CHAT_10               0xFF +  45 //  45 - Chat Channel 10
#define USERCOLOR_MELEE_CRIT            0xFF +  46 //  46 - Melee Crits
#define USERCOLOR_SPELL_CRIT            0xFF +  47 //  47 - Spell Crits
#define USERCOLOR_TOO_FAR_AWAY          0xFF +  48 //  48 - Too far away (melee)
#define USERCOLOR_NPC_RAMPAGE           0xFF +  49 //  49 - NPC Rampage
#define USERCOLOR_NPC_FLURRY            0xFF +  50 //  50 - NPC Furry
#define USERCOLOR_NPC_ENRAGE            0xFF +  51 //  51 - NPC Enrage
#define USERCOLOR_ECHO_SAY              0xFF +  52 //  52 - say echo
#define USERCOLOR_ECHO_TELL             0xFF +  53 //  53 - tell echo
#define USERCOLOR_ECHO_GROUP            0xFF +  54 //  54 - group echo
#define USERCOLOR_ECHO_GUILD            0xFF +  55 //  55 - guild echo
#define USERCOLOR_ECHO_OOC              0xFF +  56 //  56 - group echo
#define USERCOLOR_ECHO_AUCTION          0xFF +  57 //  57 - auction echo
#define USERCOLOR_ECHO_SHOUT            0xFF +  58 //  58 - shout echo
#define USERCOLOR_ECHO_EMOTE            0xFF +  59 //  59 - emote echo
#define USERCOLOR_ECHO_CHAT_1           0xFF +  60 //  60 - chat 1 echo
#define USERCOLOR_ECHO_CHAT_2           0xFF +  61 //  61 - chat 2 echo
#define USERCOLOR_ECHO_CHAT_3           0xFF +  62 //  62 - chat 3 echo
#define USERCOLOR_ECHO_CHAT_4           0xFF +  63 //  63 - chat 4 echo
#define USERCOLOR_ECHO_CHAT_5           0xFF +  64 //  64 - chat 5 echo
#define USERCOLOR_ECHO_CHAT_6           0xFF +  65 //  65 - chat 6 echo
#define USERCOLOR_ECHO_CHAT_7           0xFF +  66 //  66 - chat 7 echo
#define USERCOLOR_ECHO_CHAT_8           0xFF +  67 //  67 - chat 8 echo
#define USERCOLOR_ECHO_CHAT_9           0xFF +  68 //  68 - chat 9 echo
#define USERCOLOR_ECHO_CHAT_10          0xFF +  69 //  69 - chat 10 echo
#define USERCOLOR_RESERVED              0xFF +  70 //  70 - "unused at this time" 
#define USERCOLOR_LINK                  0xFF +  71 //  71 - item links 
#define USERCOLOR_RAID                  0xFF +  72 //  72 - raid 
#define USERCOLOR_PET                   0xFF +  73 //  73 - my pet 
#define USERCOLOR_DAMAGESHIELD          0xFF +  74 //  74 - damage shields 
#define USERCOLOR_LEADER                0xFF +  75 //  75 - LAA-related messages 
#define USERCOLOR_PETRAMPFLURRY         0xFF +  76 //  76 - pet rampage/flurry 
#define USERCOLOR_PETCRITS              0xFF +  77 //  77 - pet's critical hits 
#define USERCOLOR_FOCUS                 0xFF +  78 //  78 - focus item activation 
#define USERCOLOR_XP                    0xFF +  79 //  79 - xp gain/loss 
#define USERCOLOR_SYSTEM                0xFF +  80 //  80 - system broadcasts etc 
#define USERCOLOR_PET_SPELLS            0xFF +  81 //  81 - pet spells
#define USERCOLOR_PET_RESPONSES         0xFF +  82 //  82 - pet responses
#define USERCOLOR_ITEM_SPEECH           0xFF +  83 //  83 - item speech
#define USERCOLOR_STRIKETHROUGH         0xFF +  84 //  84 - strikethrough messages
#define USERCOLOR_STUN                  0XFF +  85 //  85 - stun messages
#define USERCOLOR_RESERVED2             0xFF +  86 //  86 - "unused at this time" (or unknown!?)
#define USERCOLOR_FELLOWSHIP            0xFF +  87 //  87 - fellowship messages
#define USERCOLOR_NPC_SPEECH            0xFF +  88 //  88 - npc dialogue
#define USERCOLOR_NPC_SPEECH_TO_YOU     0xFF +  89 //  89 - npc dialogue to you
#define USERCOLOR_GUILD_MSG             0xFF +  90 //  90 - guild messages

#define DEITY_Bertoxxulous              201
#define DEITY_BrellSerilis              202
#define DEITY_CazicThule                203
#define DEITY_ErollisiMarr              204
#define DEITY_Bristlebane               205
#define DEITY_Innoruuk                  206
#define DEITY_Karana                    207
#define DEITY_MithanielMarr             208
#define DEITY_Prexus                    209
#define DEITY_Quellious                 210
#define DEITY_RallosZek                 211
#define DEITY_RodcetNife                212
#define DEITY_SolusekRo                 213
#define DEITY_TheTribunal               214
#define DEITY_Tunare                    215
#define DEITY_Veeshan                   216

#define ITEMTYPE_NORMAL                 0
#define ITEMTYPE_PACK                   1
#define ITEMTYPE_BOOK                   2

#define COMP_NONE                       0
#define COMP_EQ                         1
#define COMP_NE                         2
#define COMP_GT                         3
#define COMP_LT                         4
#define COMP_GE                         5
#define COMP_LE                         6
#define COMP_CONT                       7
#define COMP_NOTCONT                    8
#define COMP_BITAND                     9
#define COMP_BITOR                      10

#define COMP_TYPE_STRING                0
#define COMP_TYPE_NUMERIC               1
#define COMP_TYPE_BIT                   2

#define CMD_MQ                          1
#define CMD_EQ                          2        

#define LASTFIND_NOTFOUND               96
#define LASTFIND_PRIMARY                97

#define EVENT_CHAT                      0
#define EVENT_TIMER                     1
#define EVENT_CUSTOM                    2
#define EVENT_EVAL                      3
#define EVENT_EXEC                      4
#define EVENT_PULSE                     5
#define EVENT_SHUTDOWN                  6
#define EVENT_BREAK                     7
#define NUM_EVENTS                      8

#define CHAT_SAY                        1
#define CHAT_TELL                       2
#define CHAT_OOC                        4
#define CHAT_SHOUT                      8
#define CHAT_AUC                        16
#define CHAT_GUILD                      32
#define CHAT_GROUP                      64
#define CHAT_CHAT                       128
#define CHATEVENT(x)                    (gEventChat & x)

#define FILTERSKILL_ALL                 0
#define FILTERSKILL_INCREASE            1
#define FILTERSKILL_NONE                2

#define FILTERMACRO_ALL                 0
#define FILTERMACRO_ENHANCED            1
#define FILTERMACRO_NONE                2
#define FILTERMACRO_MACROENDED			3


#define MAX_STRING                      2048
#define MAX_VARNAME                     64

// Defines for CXWnd WindowStyle
#define CWS_VSCROLL                     0x1
#define CWS_HSCROLL                     0x2
#define CWS_TITLE                       0x4
#define CWS_CLOSE                       0x8
#define CWS_TILEBOX                     0x10
#define CWS_MINIMIZE                    0x20
#define CWS_BORDER                      0x40
//#define CWS_UNKNOWN                     0x80
//#define CWS_UNKNOWN                     0x100
#define CWS_RESIZEALL                   0x200
#define CWS_TRANSPARENT                 0x400
//#define CWS_UNKNOWN                     0x800
#define CWS_NOMOVE                      0x8000
#define CWS_QMARK                       0x10000
#define CWS_MAXIMIZE                    0x40000
#define ToggleBit(field,bit)            field^=bit;
#define BitOn(field,bit)                field|=bit;
#define BitOff(field,bit)               field&=~bit;
#define BitSet(field,n)					field|=(1<<n);
#define BitClear(field,n)				field&=~(1<<n);
// End CXWnd WindowStyle Defines

#define ALTCURRENCY_DOUBLOONS           0xa
#define ALTCURRENCY_ORUX                0xb
#define ALTCURRENCY_PHOSPHENES          0xc
#define ALTCURRENCY_PHOSPHITES          0xd
#define ALTCURRENCY_FAYCITES            0xe
#define ALTCURRENCY_CHRONOBINES         0xf
#define ALTCURRENCY_SILVERTOKENS        0x10
#define ALTCURRENCY_GOLDTOKENS          0x11
#define ALTCURRENCY_MCKENZIE            0x12
#define ALTCURRENCY_BAYLE               0x13
#define ALTCURRENCY_RECLAMATION         0x14
#define ALTCURRENCY_BRELLIUM            0x15
#define ALTCURRENCY_MOTES               0x16
#define ALTCURRENCY_REBELLIONCHITS      0x17
#define ALTCURRENCY_DIAMONDCOINS        0x18
#define ALTCURRENCY_BRONZEFIATS         0x19
#define ALTCURRENCY_VOUCHER             0x1a
#define ALTCURRENCY_VELIUMSHARDS        0x1b
#define ALTCURRENCY_CRYSTALLIZEDFEAR    0x1c
#define ALTCURRENCY_SHADOWSTONES        0x1d
#define ALTCURRENCY_DREADSTONES         0x1e
#define ALTCURRENCY_MARKSOFVALOR        0x1f
#define ALTCURRENCY_MEDALSOFHEROISM     0x20
#define ALTCURRENCY_COMMEMORATIVE_COINS 0x21
#define ALTCURRENCY_FISTSOFBAYLE	    0x22
#define ALTCURRENCY_NOBLES			    0x23
#define ALTCURRENCY_ENERGYCRYSTALS	    0x24
#define ALTCURRENCY_PIECESOFEIGHT	    0x25

enum MOUSE_DATA_TYPES {
   MD_Unknown = -1,
   MD_Button0Click=0,
   MD_Button1Click,
   MD_Button0,
   MD_Button1
};

//eqmule Mar 23 2015
//KeypressHandler__HandleKeyUp_x has this one
#define nEQMappableCommands             0x206

#define MAX_PC_LEVEL                    105
#define MAX_NPC_LEVEL                   115
#define MAX_SPELL_LEVEL					255
#define NUM_SPELL_GEMS                  0xc
#define NUM_SPELL_SETS                  30
#define NUM_BUFF_SLOTS					0x61
#define NUM_LONG_BUFFS                  0x2a
#define NUM_SHORT_BUFFS                 0x37

#define EQ_EXPANSION(x)                 (1 << (x - 1))
#define EXPANSION_RoK                   EQ_EXPANSION(1)
#define EXPANSION_SoV                   EQ_EXPANSION(2)
#define EXPANSION_SoL                   EQ_EXPANSION(3)
#define EXPANSION_PoP                   EQ_EXPANSION(4)
#define EXPANSION_LoY                   EQ_EXPANSION(5)
#define EXPANSION_LDoN                  EQ_EXPANSION(6)
#define EXPANSION_GoD                   EQ_EXPANSION(7)
#define EXPANSION_OoW                   EQ_EXPANSION(8)
#define EXPANSION_DoN                   EQ_EXPANSION(9)
#define EXPANSION_DoD                   EQ_EXPANSION(10)
#define EXPANSION_PoR                   EQ_EXPANSION(11)
#define EXPANSION_TSS                   EQ_EXPANSION(12)
#define EXPANSION_TBS                   EQ_EXPANSION(13)
#define EXPANSION_SoF                   EQ_EXPANSION(14)
#define EXPANSION_SoD                   EQ_EXPANSION(15)
#define EXPANSION_UFT                   EQ_EXPANSION(16)
#define EXPANSION_HoT                   EQ_EXPANSION(17)
#define EXPANSION_VoA                   EQ_EXPANSION(18)
#define EXPANSION_RoF                   EQ_EXPANSION(19)
#define EXPANSION_CotF                  EQ_EXPANSION(20)
#define EXPANSION_TDS                   EQ_EXPANSION(21)
#define EXPANSION_TBM                   EQ_EXPANSION(22)
#define NUM_EXPANSIONS                  22

#if _MSC_VER < 1600
#define nullptr                         NULL
#endif

#define SPA_AC                          1
#define SPA_MOVEMENTRATE                3
#define SPA_LURE                        10
#define SPA_HASTE                       11
#define SPA_ILLUSION                    58
#define SPA_MAGNIFICATION               87
#define SPA_PLAYERSIZE                  89
#define SPA_SUMMONCORPSE                91
#define SPA_BARDOVERHASTE               98
#define SPA_SPELLDAMAGE                 124
#define SPA_HEALING                     125
#define SPA_REAGENTCHANCE               131
#define SPA_SPELLMANACOST               132
#define SPA_DOUBLEATTACK                177
#define SPA_STUNRESIST                  195
#define SPA_PROCMOD                     200
#define SPA_DIVINEREZ                   232
#define SPA_METABOLISM                  233
#define SPA_PLACEHOLDER                 254
#define SPA_TRIPLEBACKSTAB              258
#define SPA_DOTCRIT                     273
#define SPA_HEALCRIT                    274
#define SPA_MENDCRIT                    275
#define SPA_FLURRY                      279
#define SPA_PETFLURRY                   280
#define SPA_SPELLCRITCHANCE             294
#define SPA_INCSPELLDMG                 296
#define SPA_DAMAGECRITMOD               302
#define SPA_SHIELDBLOCKCHANCE           320
#define SPA_AC2                         416

#define TT_PBAE                         0x04
#define TT_TARGETED_AE                  0x08
#define TT_AE_PC_V2                     0x28
#define TT_DIRECTIONAL                  0x2a

#define EQHeading(heading) (int)(((heading + 16) % 256) / 32) * 2


// ***************************************************************************
// Structures
// ***************************************************************************

typedef struct _MOUSESPOOF {
   MOUSE_DATA_TYPES     mdType;
   DWORD                dwData;
   struct _MOUSESPOOF   *pNext;
} MOUSESPOOF, *PMOUSESPOOF;

typedef struct _MOUSECLICK {
   BYTE Confirm[8];         // DO NOT WRITE TO THIS BYTE
   BYTE Click[8];         // Left = 0, Right = 1, etc
} MOUSECLICK, *PMOUSECLICK;

typedef struct _UILOCATION {
   DWORD x;
   DWORD y;
   DWORD w;
   DWORD h;
   CHAR error[MAX_STRING];
} UILOCATION, *PUILOCATION;

//5-15-2003   eqmule
typedef struct _CXSTR {
/*0x00*/   DWORD   Font;            // maybe, dont know.  04 = Window 01 = button
/*0x04*/   DWORD   MaxLength;
/*0x08*/   DWORD   Length;
/*0x0c*/   BOOL    Encoding;        // 0: ASCII, 1:Unicode
/*0x10*/   PCRITICAL_SECTION pLock;
/*0x14*/   CHAR    Text[1];         // Stub, can be anywhere from Length to MaxLength (which is how much is malloc'd to this CXStr)
} CXSTR, *PCXSTR;

#define ITEM_NAME_LEN                   0x40
#define LORE_NAME_LEN                   0x70

// size is 0x64 02-16-2007
typedef struct _ITEMSPELLS { 
/*0x00*/ DWORD SpellID; 
/*0x04*/ BYTE  RequiredLevel; 
/*0x05*/ BYTE  EffectType; 
/*0x06*/ BYTE  Unknown[0x2]; 
/*0x08*/ DWORD Unknown0x08;
/*0x0c*/ DWORD MaxCharges;
/*0x10*/ DWORD CastTime;
/*0x14*/ DWORD TimerID;
/*0x18*/ DWORD RecastType;
/*0x1c*/ DWORD ProcRate;
/*0x20*/ BYTE  Unknown0x20[0x44];
/*0x64*/
} ITEMSPELLS, *PITEMSPELLS; 

//CItemInfo__CItemInfo
// actual size: 0x75c Nov 16 2015 (see 6D24F7) - eqmule
typedef struct _ITEMINFO {
/*0x0000*/ CHAR         Name[ITEM_NAME_LEN];
/*0x0040*/ CHAR         LoreName[LORE_NAME_LEN];
/*0x00b0*/ CHAR         IDFile[0x20];
/*0x00d0*/ BYTE         Unknown0x00d0[0x1c];
/*0x00ec*/ DWORD        ItemNumber;
/*0x00f0*/ DWORD        EquipSlots;
/*0x00f4*/ DWORD        Cost;
/*0x00f8*/ DWORD        IconNumber;
/*0x00fc*/ BYTE         Unknown0x00fc[0x4];
/*0x0100*/ DWORD        Weight;
/*0x0104*/ BYTE         NoRent; // 0=temp, 1=default
/*0x0105*/ BYTE         NoDrop; // 0=no drop, 1=can drop same as NoTrade
/*0x0106*/ BYTE         Attuneable;
/*0x0107*/ BYTE         Heirloom;
/*0x0108*/ BYTE         Collectible;
/*0x0109*/ BYTE         NoDestroy;
/*0x010a*/ BYTE         Unknown0x010a;
/*0x010b*/ BYTE         NoZone;
/*0x010c*/ DWORD        MakerID;//0-?? I did up to 12, I think it asks server for the name - eqmule
/*0x0110*/ BYTE         NoGround;
/*0x0111*/ BYTE         Unknown0x0111;
/*0x0112*/ BYTE         MarketPlace;
/*0x0113*/ BYTE         Unknown0x0113[0x2];
/*0x0115*/ BYTE         Size;
/*0x0116*/ BYTE         Type;
/*0x0117*/ BYTE         TradeSkills;
/*0x0118*/ DWORD        Lore;
/*0x011c*/ BYTE         Artifact;
/*0x011d*/ BYTE         Summoned;
/*0x011e*/ CHAR         SvCold;
/*0x011f*/ CHAR         SvFire;
/*0x0120*/ CHAR         SvMagic;
/*0x0121*/ CHAR         SvDisease;
/*0x0122*/ CHAR         SvPoison;
/*0x0123*/ CHAR         SvCorruption;
/*0x0124*/ CHAR         STR;
/*0x0125*/ CHAR         STA;
/*0x0126*/ CHAR         AGI;
/*0x0127*/ CHAR         DEX;
/*0x0128*/ CHAR         CHA;
/*0x0129*/ CHAR         INT;
/*0x012a*/ CHAR         WIS;
/*0x012b*/ BYTE         Unknown0x012b;
/*0x012c*/ DWORD        HP;
/*0x0130*/ DWORD        Mana;
/*0x0134*/ DWORD        AC;
/*0x0138*/ DWORD        RequiredLevel;
/*0x013c*/ DWORD        RecommendedLevel;
/*0x0140*/ BYTE         RecommendedSkill;
/*0x0141*/ BYTE         Unknown0x0141[0x3];
/*0x0144*/ DWORD        SkillModType;
/*0x0148*/ DWORD        SkillModValue;
/*0x014c*/ DWORD        SkillModMax;
/*0x0150*/ BYTE         Unknown0x0150[0x4];
/*0x0154*/ DWORD        BaneDMGRace;
/*0x0158*/ DWORD        BaneDMGBodyType;
/*0x015c*/ BYTE         BaneDMGBodyTypeValue;
/*0x015d*/ BYTE         BaneDMGRaceValue;
/*0x015e*/ BYTE         Unknown0x015e[0x6];
/*0x0164*/ DWORD        InstrumentType;
/*0x0168*/ DWORD        InstrumentMod;
/*0x016c*/ DWORD        Classes;
/*0x0170*/ DWORD        Races;
/*0x0174*/ DWORD        Diety;
/*0x0178*/ BYTE         Unknown0x0178[0x4];
/*0x017c*/ BYTE         Magic;
/*0x017d*/ BYTE         Light;
/*0x017e*/ BYTE         Delay;
/*0x017f*/ BYTE         ElementalFlag;//used to be called DmgBonusType;
/*0x0180*/ BYTE         ElementalDamage;//used to be called DmgBonusVal
/*0x0181*/ BYTE         Range;
/*0x0182*/ BYTE         Unknown0x0182[0x2];
/*0x0184*/ DWORD        Damage;
/*0x0188*/ DWORD        BackstabDamage;
/*0x018c*/ DWORD        DamageShieldMitigation;
/*0x0190*/ DWORD        HeroicSTR;
/*0x0194*/ DWORD        HeroicINT;
/*0x0198*/ DWORD        HeroicWIS;
/*0x019c*/ DWORD        HeroicAGI;
/*0x01a0*/ DWORD        HeroicDEX;
/*0x01a4*/ DWORD        HeroicSTA;
/*0x01a8*/ DWORD        HeroicCHA;
/*0x01ac*/ DWORD        HeroicSvMagic;
/*0x01b0*/ DWORD        HeroicSvFire;
/*0x01b4*/ DWORD        HeroicSvCold;
/*0x01b8*/ DWORD        HeroicSvDisease;
/*0x01bc*/ DWORD        HeroicSvPoison;
/*0x01c0*/ DWORD        HeroicSvCorruption;
/*0x01c4*/ DWORD        HealAmount;
/*0x01c8*/ DWORD        SpellDamage;
/*0x01cc*/ DWORD        Prestige;
/*0x01d0*/ BYTE         ItemType;
/*0x01d1*/ BYTE         Unknown0x01d1[0xb];
/*0x01dc*/ BYTE         Material;
/*0x01dd*/ BYTE         Unknown0x01dd[0xb];
/*0x01e8*/ DWORD        AugSlot1;
/*0x01ec*/ DWORD        AugSlot1_Visible;
/*0x01f0*/ DWORD        AugSlot2;
/*0x01f4*/ DWORD        AugSlot2_Visible;
/*0x01f8*/ DWORD        AugSlot3;
/*0x01fc*/ DWORD        AugSlot3_Visible;
/*0x0200*/ DWORD        AugSlot4;
/*0x0204*/ DWORD        AugSlot4_Visible;
/*0x0208*/ DWORD        AugSlot5;
/*0x020c*/ DWORD        AugSlot5_Visible;
/*0x0210*/ DWORD        AugSlot6;
/*0x0214*/ DWORD        AugSlot6_Visible;
/*0x0218*/ DWORD        AugType;
/*0x021c*/ BYTE         Unknown0x021c[0x4];
/*0x0220*/ DWORD        AugRestrictions;
/*0x0224*/ DWORD        SolventNeeded; //ID# of Solvent (Augs only)
/*0x0228*/ DWORD        LDTheme;
/*0x022c*/ DWORD        LDCost;
/*0x0230*/ DWORD        LDType;
/*0x0234*/ BYTE         Unknown0x0234[0x8];
/*0x023c*/ DWORD        FactionModType[0x4];
/*0x024c*/ DWORD        FactionModValue[0x4];
/*0x025c*/ CHAR         CharmFile[0x20];
/*0x027c*/ BYTE         Unknown0x027c[0x4];
/*0x0280*/ struct _ITEMSPELLS   Clicky;
/*0x02e4*/ struct _ITEMSPELLS   Proc;
/*0x0348*/ struct _ITEMSPELLS   Worn;
/*0x03ac*/ struct _ITEMSPELLS   Focus;
/*0x0410*/ struct _ITEMSPELLS   Scroll;
/*0x0474*/ struct _ITEMSPELLS   Focus2;
/*0x04d8*/ BYTE         Unknown0x04d8[0x140];
/*0x0618*/ DWORD        CombatEffects;
/*0x061c*/ DWORD        Shielding;
/*0x0620*/ DWORD        StunResist;
/*0x0624*/ DWORD        DoTShielding;
/*0x0628*/ DWORD        StrikeThrough;
/*0x062c*/ DWORD        DmgBonusSkill; // SkillMinDamageMod;
/*0x0630*/ DWORD        DmgBonusValue; // MinDamageMod;
/*0x0634*/ DWORD        SpellShield;
/*0x0638*/ DWORD        Avoidance;
/*0x063c*/ DWORD        Accuracy;
/*0x0640*/ DWORD        CharmFileID;
/*0x0644*/ DWORD        FoodDuration;//0-5 snack 6-20 meal 21-30 hearty 31-40 banquet 41-50 feast 51-60 enduring 60- miraculous
/*0x0648*/ BYTE         Combine;
/*0x0649*/ BYTE         Slots;
/*0x064a*/ BYTE         SizeCapacity;
/*0x064b*/ BYTE         WeightReduction;
/*0x064c*/ BYTE         BookType;      // 0=note, !0=book
/*0x064d*/ BYTE         BookLang;
/*0x064e*/ CHAR         BookFile[0x1e];
/*0x066c*/ DWORD        Favor;         // Tribute Value
/*0x0670*/ DWORD        GuildFavor;
/*0x0674*/ BYTE         Unknown0x0674[0x4];
/*0x0678*/ DWORD        Endurance;
/*0x067c*/ DWORD        Attack;
/*0x0680*/ DWORD        HPRegen;
/*0x0684*/ DWORD        ManaRegen;
/*0x0688*/ DWORD        EnduranceRegen;
/*0x068c*/ DWORD        Haste;
/*0x0690*/ DWORD        DamShield;
/*0x0694*/ BYTE         Unknown0x0694[0x8];
/*0x069c*/ BYTE         NoPet;
/*0x069d*/ BYTE         Unknown0x069d[0xb];
/*0x06a8*/ DWORD        StackSize;
/*0x06ac*/ BYTE         Unknown0x06ac[0x4];
/*0x06b0*/ DWORD        MaxPower;
/*0x06b4*/ DWORD        Purity;
/*0x06b8*/ BYTE         Unknown0x06b8[0xc];
/*0x06c4*/ BYTE         QuestItem;
/*0x06c5*/ BYTE         Expendable;
/*0x06c6*/ BYTE         Unknown0x06c6[0x2];
/*0x06c8*/ DWORD        Clairvoyance;
/*0x06cc*/ BYTE         Unknown0x06cc[0x8];
/*0x06d4*/ DWORD        Placeable;
/*0x06d8*/ BYTE			Unknown0x06d8[0x84];
/*0x075c*/
} ITEMINFO, *PITEMINFO;

typedef struct _CONTENTSARRAY {
    struct  _CONTENTS *Contents[0x14]; // 20 bag-slot max - addresses to whats inside the bag if its a bag; augs if an item
} CONTENTSARRAY, *PCONTENTSARRAY;

//Actual Size: 148 (see 591817 in eqgame.exe Live dated Apr 21 2016) - eqmule
typedef struct _CONTENTS {
/*0x0000*/ void*	vtable;
/*0x0004*/ DWORD	ItemType;           // ? 1 = normal, 2 = pack ?
/*0x0008*/ void*	punknown;
/*0x000c*/ DWORD	EvolvingCurrentLevel;
/*0x0010*/ BYTE		Unknown0x0010[0x4];
/*0x0014*/ DWORD	Power;
/*0x0018*/ BYTE		Unknown0x0018[0x4];
/*0x001c*/ DWORD	StackCount;
/*0x0020*/ DWORD	EvolvingMaxLevel;
/*0x0024*/ BYTE		Unknown0x0024[0x34];
/*0x0058*/ DWORD	Open;
/*0x005c*/ BYTE		Unknown0x005c[0x24];
/*0x0080*/ struct _ITEMINFO*	Item1;
/*0x0084*/ BYTE		Unknown0x0084[0x4];
/*0x0088*/ DWORD	OrnamentationIcon;
/*0x008c*/ BYTE		Unknown0x008c[0x10];
/*0x009c*/ BYTE		IsEvolvingItem;
/*0x009d*/ BYTE		EvolvingExpOn;
/*0x009e*/ BYTE		Unknown0x009e[0x2];
/*0x00a0*/ DWORD	GroupID;
/*0x00a4*/ BYTE		Unknown0x00a4[0x14];
/*0x00b8*/ DWORD	NumOfSlots1;//ItemSlot is this address + 0x16 in 20130708
/*0x00bc*/ DWORD	IsMountKeyRing;//0x1b if it is 0 if not
/*0x00c0*/ struct _CONTENTSARRAY*	pContentsArray;
/*0x00c4*/ DWORD	NumOfSlots2;
/*0x00c8*/ BYTE		Unknown0x00c8[0x6];
/*0x00ce*/ WORD		ItemSlot;           // Inventory slot id
/*0x00d0*/ WORD		ItemSlot2;          // Bag slot id, starts at 0 for first slot in bag, or FFFF if item is on cursor
/*0x00d2*/ BYTE		Unknown0x00d2[0xe];
/*0x00e0*/ DWORD	MerchantQuantity;
/*0x00e4*/ BYTE		Unknown0x00e4[0x4];
/*0x00e8*/ DWORD	Charges;
/*0x00ec*/ BYTE		Unknown0x00ec[0x4];
/*0x00f0*/ DWORD	MerchantSlot;       // slot id on a merchant
/*0x00f4*/ BYTE		Unknown0x00f4[0x1c];
/*0x0110*/ DWORD	Price;
/*0x0114*/ BYTE		Unknown0x0114[0x4];
/*0x0118*/ DOUBLE	EvolvingExpPct;
/*0x0120*/ BYTE		Unknown0x0120[0x1c];
/*0x013c*/ struct _ITEMINFO*	Item2;
/*0x0140*/ BYTE		Unknown0x0140[0x08];
/*0x0148*/
} CONTENTS, *PCONTENTS;

// Size 0x58 20110810 - dkaa
// Size 0x58 20150326 - demonstar55
typedef struct _SPELLBUFF {
	/*0x00*/    BYTE      Unknown0x0;
	/*0x01*/    BYTE      Level;
	/*0x02*/    BYTE      Unknown0x2;    // pretty sure is padding
	/*0x03*/    CHAR      DamageShield;  // also probably padding now
	/*0x04*/    FLOAT     Modifier;      // Bard song modifier, 1.0 is default
	/*0x08*/    LONG      SpellID;       // -1 or 0 for no spell..
	/*0x0c*/    DWORD     Duration;
	/*0x10*/    DWORD     Unknown0x10;   // This might be source ID?
	/*0x14*/    DWORD     HitCount;
	/*0x18*/    FLOAT     Y;             // Referenced by SPA 441 (distance removal)
	/*0x1c*/    FLOAT     X;
	/*0x20*/    FLOAT     Z;
	/*0x24*/    DWORD     Unknown0x24;
	/*0x28*/    DWORD     SlotData[0xC]; // used for book keeping of various effects (debuff counter, rune/vie damage remaining)
	/*0x58*/
} SPELLBUFF, *PSPELLBUFF;

// 20101012 - ieatacid
typedef struct _INVENTORY { 
/*0x00*/  struct    _CONTENTS* Charm;
/*0x04*/  struct    _CONTENTS* LeftEar;
/*0x08*/  struct    _CONTENTS* Head;
/*0x0c*/  struct    _CONTENTS* Face;
/*0x10*/  struct    _CONTENTS* RightEar;
/*0x14*/  struct    _CONTENTS* Neck;
/*0x18*/  struct    _CONTENTS* Shoulders;
/*0x1c*/  struct    _CONTENTS* Arms;
/*0x20*/  struct    _CONTENTS* Back;
/*0x24*/  struct    _CONTENTS* LeftWrist;
/*0x28*/  struct    _CONTENTS* RightWrist;
/*0x2c*/  struct    _CONTENTS* Range;
/*0x30*/  struct    _CONTENTS* Hands;
/*0x34*/  struct    _CONTENTS* Primary;
/*0x38*/  struct    _CONTENTS* Secondary;
/*0x3c*/  struct    _CONTENTS* LeftFinger;
/*0x40*/  struct    _CONTENTS* RightFinger;
/*0x44*/  struct    _CONTENTS* Chest;
/*0x48*/  struct    _CONTENTS* Legs;
/*0x4c*/  struct    _CONTENTS* Feet;
/*0x50*/  struct    _CONTENTS* Waist;
/*0x54*/  struct    _CONTENTS* PowerSource;
/*0x58*/  struct    _CONTENTS* Ammo;
/*0x5c*/  struct    _CONTENTS* Pack[0xa];
/*0x84*/  struct    _CONTENTS* Cursor;
} INVENTORY, *PINVENTORY;

//need to find this one
#define NUM_ALT_ABILITIES_ARRAY         0x1F7      
// see 4FBD46 in eqgame.exe dated oct 29 2013 test - eqmule
#define NUM_ALT_ABILITIES               0xC34F

//these two will merge when i get a chance - ieatacid wrote this?
#define AA_CHAR_MAX                     0xF5
//EQ_PC__GetAlternateAbilityId_x
//size is at 7EE7F8 in eqgame dated jun 13 2014 - eqmule
#define AA_CHAR_MAX_REAL                0x12C

typedef struct _AALIST { 
/*0x0*/   DWORD        AAIndex;
/*0x4*/   DWORD        PointsSpent;
/*0x8*/   DWORD        ChargeSpent;        // charges spent in the last 10 min?
} AALIST, *PAALIST;

#define NUM_INV_SLOTS                   0x21
#define NUM_BANK_SLOTS                  0x18
#define NUM_SHAREDBANK_SLOTS            0x04
#define MAX_KEYRINGITEMS			    0x1B //not really sure need to confirm this
//found in CSpellBookWnd__GetBookSlot_x (see 7756CA in Oct 29 2014 Live) -eqmule 
#define NUM_BOOK_SLOTS                  0x320
#define NUM_COMBAT_ABILITIES            0x12c
#define BAG_SLOT_START                  23
#define ExactLocation                   0

typedef struct _LEADERABILITIES {
/*0x00*/ DWORD MarkNPC;
/*0x04*/ DWORD NPCHealth;
/*0x08*/ DWORD Unknown0x8;
/*0x0c*/ DWORD DelegateMA;
/*0x10*/ DWORD DelegateMarkNPC;
/*0x14*/ DWORD Unknown0x14;
/*0x18*/ DWORD InspectBuffs;
/*0x1c*/ DWORD Unknown0x1c;
/*0x20*/ DWORD SpellAwareness;
/*0x24*/ DWORD OffenseEnhancement;
/*0x28*/ DWORD ManaEnhancement;
/*0x2c*/ DWORD HealthEnhancement;
/*0x30*/ DWORD HealthRegen;
/*0x34*/ DWORD FindPathPC;
/*0x38*/ DWORD HoTT;
/*0x3c*/
} LEADERABILITIES, *PLEADERABILITIES;

typedef struct _EQC_INFO {
/* 0x0000 */    DWORD   minus4;
/* 0x0004 */    DWORD   stuff_offset;
} EQC_INFO, *PEQC_INFO;

typedef struct _CI_INFO {
/* 0x0000 */    DWORD   minus8;
/* 0x0004 */    DWORD   stuff_offset;
/* 0x0008 */    DWORD   Unknown0x8;    // 2000
/* 0x000c */    DWORD   Unknown0xc;    // 2500
/* 0x0010 */    DWORD   Unknown0x10;   // 3000
/* 0x0014 */    DWORD   Unknown0x14;   // 4000
/* 0x0018 */    DWORD   Unknown0x18;   // 10000
} CI_INFO, *PCI_INFO;

typedef struct _CI2_INFO {
/* 0x0000 */    DWORD   Unknown0x0;
/* 0x0004 */    struct  _CHARINFO2* pCharInfo2;
/* 0x0008 */    struct  _CHARINFO2* pCharInfo3;
/* 0x000c */    BYTE    Unknown0xc[0x14];
/* 0x0010 */    void    *Unknown0x10[0x10];
/* 0x0060 */
} CI2_INFO, *PCI2_INFO;

//size 34 i think in eqgame dated mar 23 2015 but i have no address for it atm -eqmule
typedef struct _GROUPMEMBER {
/*0x00*/ void   *vftable;
/*0x04*/ struct _CXSTR *pName;
/*0x08*/ BYTE   Mercenary;
/*0x09*/ BYTE   Unknown0x8[0x3];
/*0x0c*/ struct _CXSTR *pOwner; // name of mercenary's owner
/*0x10*/ DWORD  Level;
/*0x14*/ BYTE   Offline;//1 if groupmember is offline
/*0x15*/ BYTE   Unknown0x15[8];
/*0x1d*/ BYTE   MainTank;
/*0x1e*/ BYTE   MainAssist;
/*0x1f*/ BYTE   Puller;
/*0x20*/ BYTE   MarkNpc;
/*0x21*/ BYTE   MasterLooter;
/*0x22*/ BYTE   Unknown0x22[0x2];
/*0x24*/ DWORD  Roles;          // (Roles & 0x1) = MainTank, 0x2 = MainAssist, 0x4 = Puller 0x8 = Mark NPC 0x10 = Master Looter
/*0x28*/ BYTE   Unknown0x28[0x8];
/*0x30*/ struct _SPAWNINFO *pSpawn;
/*0x34*/
} GROUPMEMBER, *PGROUPMEMBER;


typedef struct _GROUPINFO {
/*0x00*/ void   *vftable;
/*0x04*/ struct _GROUPMEMBER *pMember[0x6];
/*0x1c*/ struct _GROUPMEMBER *pLeader;
/*0x20*/
} GROUPINFO, *PGROUPINFO;

typedef struct _BANKARRAY {
/*0x00*/ struct _CONTENTS* Bank[NUM_BANK_SLOTS];
/*0x60*/
} BANKARRAY, *PBANKARRAY;

typedef struct _SHAREDBANKARRAY {
/*0x00*/ struct _CONTENTS* SharedBank[NUM_SHAREDBANK_SLOTS];
/*0x10*/
} SHAREDBANKARRAY, *PSHAREDBANKARRAY;

//added dec 08 2014 -eqmule
typedef struct _KEYRINGARRAY {
	union {
		/*0x00*/ struct _CONTENTS* Mounts[MAX_KEYRINGITEMS];
		/*0x00*/ struct _CONTENTS* Illusions[MAX_KEYRINGITEMS];
	};
	/*0x28*/
} KEYRINGARRAY, *PKEYRINGARRAY;

//aStartingLoad_
// actual size: 0x2770 in Mar 11 2016 Live (see 579C27) - eqmule
typedef struct _CHARINFO {
/*0x0000*/ void*        vtable1;
/*0x0004*/ void*        punknown;
/*0x0008*/ struct _CI_INFO*     charinfo_info;
/*0x000c*/ BYTE         Unknown0x000c[0x10ec];
/*0x10f8*/ struct _BANKARRAY*   pBankArray;
/*0x10fc*/ DWORD        NumBankSlots;//how many bank slots we have
/*0x1100*/ BYTE         Unknown0x1100[0x14];
/*0x1114*/ struct _SHAREDBANKARRAY*     pSharedBankArray;
/*0x1118*/ DWORD        NumSharedSlots;//how many sharedbank slots we have
/*0x111c*/ BYTE         Unknown0x111c[0x44];
/*0x1160*/ DWORD        pMountrelated;//always 0x7d?
/*0x1164*/ DWORD        pMountrelated2;//always 0x1b?
/*0x1168*/ struct _KEYRINGARRAY*        pMountsArray;
/*0x116c*/ BYTE         Unknown0x116c[0x18];
/*0x1184*/ struct _KEYRINGARRAY*        pIllusionsArray;
/*0x1188*/ BYTE         Unknown0x1188[0xdc];
/*0x1264*/ DWORD        GuildID;//GuildID_0
/*0x1268*/ BYTE         Unknown0x1268[0x28];
/*0x1290*/ DWORD        AAExp;
/*0x1294*/ BYTE         Unknown0x1294;
/*0x1295*/ BYTE         PercentEXPtoAA;
/*0x1296*/ BYTE         Unknown0x1296[0x36];
/*0x12cc*/ DWORD        TributeTimer;
/*0x12d0*/ DWORD        BenefitTimer;
/*0x12d4*/ BYTE         Unknown0x12d4[0x4];
/*0x12d8*/ DWORD        CareerFavor;
/*0x12dc*/ BYTE         Unknown0x12dc[0x4];
/*0x12e0*/ DWORD        CurrFavor;
/*0x12e4*/ BYTE         Unknown0x12e4[0x108];
/*0x13ec*/ DWORD        RadiantCrystals;
/*0x13f0*/ BYTE         Unknown0x13f0[0x4];
/*0x13f4*/ DWORD        EbonCrystals;
/*0x13f8*/ BYTE         Unknown0x13f8[0x678];
/*0x1a70*/ DWORD        Exp;
/*0x1a74*/ BYTE         Unknown0x1a74[0x5c];
/*0x1ad0*/ void*        PlayerPointManager;
/*0x1ad4*/ BYTE         Unknown0x1ad4[0x16a];
/*0x1c3e*/ BYTE         UseAdvancedLooting;                     //0=off 1=on
/*0x1c3f*/ BYTE         Unknown0x1c3f[0x2b5];
/*0x1ef4*/ DWORD        Krono;
/*0x1ef8*/ BYTE         Unknown0x1ef8[0x8];
/*0x1f00*/ DWORD        MercAAExp;// divide this with 3.30f and you get the percent - eqmule
/*0x1f04*/ BYTE         Unknown0x1f04[0x4];
/*0x1f08*/ DWORD        MercAAPoints;//number of unspent merc AA points
/*0x1f0c*/ DWORD        MercAAPointsSpent;//number of spent merc AA points
/*0x1f10*/ BYTE         Unknown0x1f10[0xc0];
/*0x1fd0*/ void*        vtable2;//vtable2_0 below aTimeIsDAndCanU
/*0x1fd4*/ struct _EQC_INFO*    eqc_info;
/*0x1fd8*/ struct _SPAWNINFO*   pSpawn;//pSpawn_0
/*0x1fdc*/ BYTE         Unknown0x1fdc[0x4];
/*0x1fe0*/ DWORD        ArmorClassBonus;//vtable2+10
/*0x1fe4*/ DWORD        CurrWeight;//vtable2+14
/*0x1fe8*/ BYTE         Unknown0x1fe8[0xc];
/*0x1ff4*/ DWORD        HPBonus;//vtable2+24
/*0x1ff8*/ DWORD        ManaBonus;//vtable2+28
/*0x1ffc*/ DWORD        EnduranceBonus;//vtable2+2c
/*0x2000*/ DWORD        CombatEffectsCap;//vtable2+30 CombatEffectsBonus
/*0x2004*/ DWORD        ShieldingCap;//vtable2+34 ShieldingBonus
/*0x2008*/ DWORD        SpellShieldCap;//vtable2+38 SpellShieldBonus
/*0x200c*/ DWORD        AvoidanceCap;//vtable2+3c AvoidanceBonus
/*0x2010*/ DWORD        AccuracyCap;//vtable2+40 AccuracyBonus
/*0x2014*/ DWORD        StunResistCap;//vtable2+44 StunResistBonus
/*0x2018*/ DWORD        StrikeThroughCap;//vtable2+48 StrikeThroughBonus
/*0x201c*/ BYTE         Unknown0x201c[0x24];
/*0x2040*/ DWORD        SkillMinDamageModBonus[0x9];//vtable2+70
/*0x2064*/ BYTE         Unknown0x2064[0x4];
/*0x2068*/ DWORD        DoTShieldCap;//DoTShieldBonus //vtable2+98
/*0x206c*/ DWORD        DamageShieldMitigationCap;//DamageShieldMitigationBonus
/*0x2070*/ DWORD        CombatEffectsBonus;
/*0x2074*/ DWORD        SpellShieldBonus;
/*0x2078*/ DWORD        ShieldingBonus;
/*0x207c*/ DWORD        DamageShieldBonus;
/*0x2080*/ DWORD        DoTShieldBonus;
/*0x2084*/ DWORD        DamageShieldMitigationBonus;
/*0x2088*/ DWORD        AvoidanceBonus;
/*0x208c*/ DWORD        AccuracyBonus;
/*0x2090*/ DWORD        StunResistBonus;
/*0x2094*/ DWORD        StrikeThroughBonus;
/*0x2098*/ DWORD        HeroicSTRBonus;
/*0x209c*/ DWORD        HeroicINTBonus;
/*0x20a0*/ DWORD        HeroicWISBonus;
/*0x20a4*/ DWORD        HeroicAGIBonus;
/*0x20a8*/ DWORD        HeroicDEXBonus;
/*0x20ac*/ DWORD        HeroicSTABonus;
/*0x20b0*/ DWORD        HeroicCHABonus;
/*0x20b4*/ DWORD        HeroicSvMagicBonus;
/*0x20b8*/ DWORD        HeroicSvFireBonus;
/*0x20bc*/ DWORD        HeroicSvColdBonus;
/*0x20c0*/ DWORD        HeroicSvDiseaseBonus;
/*0x20c4*/ DWORD        HeroicSvPoisonBonus;
/*0x20c8*/ DWORD        HeroicSvCorruptionBonus;
/*0x20cc*/ DWORD        HealAmountBonus;
/*0x20d0*/ DWORD        SpellDamageBonus;
/*0x20d4*/ BYTE         Unknown0x20d4[0x8];
/*0x20dc*/ DWORD        ClairvoyanceBonus;
/*0x20e0*/ DWORD        AttackBonus;
/*0x20e4*/ DWORD        HPRegenBonus;
/*0x20e8*/ DWORD        ManaRegenBonus;
/*0x20ec*/ DWORD        EnduranceRegenBonus;
/*0x20f0*/ DWORD        DamageShieldCap;
/*0x20f4*/ DWORD        AttackSpeed;
/*0x20f8*/ BYTE         Unknown0x20f8[0x310];
/*0x2408*/ struct _XTARGETMGR*  pXTargetMgr;
/*0x240c*/ DWORD        InCombat;
/*0x2410*/ DWORD        Downtime;
/*0x2414*/ DWORD        DowntimeStamp;
/*0x2418*/ BYTE         Unknown0x2418[0x4];
/*0x241c*/ struct _GROUPINFO*   pGroupInfo;
/*0x2420*/ BYTE         Unknown0x2420[0x1c];
/*0x243c*/ DWORD        CharBaseBegin;//we use this for finding the next members of this struct
/*0x2440*/ BYTE         Unknown0x2440[0x4];
/*0x2444*/ void*        pCharacterBase;
/*0x2448*/ struct _CI2_INFO*    pCI2;//cant find a pointer to this so lets just say its always at pCharacterBase+4
/*0x244c*/ BYTE         Unknown0x244c[0x4];
/*0x2450*/ BYTE         languages[0x20];//CharBaseBegin+14
/*0x2470*/ BYTE         Unknown0x2470[0x10];
/*0x2480*/ CHAR         Name[0x40];//CharBaseBegin+44
/*0x24c0*/ CHAR         Lastname[0x20];//CharBaseBegin+84
/*0x24e0*/ BYTE         Unknown0x24e0[0xc0];
/*0x25a0*/ BYTE         Stunned;//CharBaseBegin+104
/*0x25a1*/ BYTE         Unknown0x25a1[0x3];
/*0x25a4*/ WORD         zoneId;//CharBaseBegin+108 Zone_0
/*0x25a6*/ WORD         instance;
/*0x25a8*/ DWORD        standstate;//CharBaseBegin+10c
/*0x25ac*/ BYTE         Unknown0x25ac[0xdc];
/*0x2688*/ DWORD        ExpansionFlags;//CharBaseBegin+464
/*0x268c*/ BYTE         Unknown0x268c[0x20];
/*0x26ac*/ DWORD        BankSharedPlat;//31e4 CharBaseBegin+488
/*0x26b0*/ DWORD        BankSharedGold;//CharBaseBegin+48c
/*0x26b4*/ DWORD        BankSharedSilver;//CharBaseBegin+490
/*0x26b8*/ DWORD        BankSharedCopper;//CharBaseBegin+494
/*0x26bc*/ DWORD        BankPlat;//CharBaseBegin+498
/*0x26c0*/ DWORD        BankGold;//CharBaseBegin+49c
/*0x26c4*/ DWORD        BankSilver;//CharBaseBegin+4a0
/*0x26c8*/ DWORD        BankCopper;//CharBaseBegin+4a4
/*0x26cc*/ DWORD        STR;//CharBaseBegin+4a8
/*0x26d0*/ DWORD        STA;//CharBaseBegin+4ac
/*0x26d4*/ DWORD        CHA;//CharBaseBegin+4b0
/*0x26d8*/ DWORD        DEX;//CharBaseBegin+4b4
/*0x26dc*/ DWORD        INT;//CharBaseBegin+4b8
/*0x26e0*/ DWORD        AGI;//CharBaseBegin+4bc
/*0x26e4*/ DWORD        WIS;//CharBaseBegin+4c0
/*0x26e8*/ DWORD        SavePoison;//CharBaseBegin+4c4
/*0x26ec*/ DWORD        SaveMagic;//CharBaseBegin+4c8
/*0x26f0*/ DWORD        SaveDisease;//CharBaseBegin+4cc
/*0x26f4*/ DWORD        SaveCorruption;//CharBaseBegin+4d0
/*0x26f8*/ DWORD        SaveFire;//CharBaseBegin+4d4
/*0x26fc*/ DWORD        SaveCold;//CharBaseBegin+4d8
/*0x2700*/ BYTE			Unknown0x2700[0x70];
/*0x2770*/
} CHARINFO, *PCHARINFO;

typedef struct _INVENTORYARRAY {
union {
/*0x00*/ struct _INVENTORY Inventory;
/*0x00*/ struct _CONTENTS* InventoryArray[NUM_INV_SLOTS];
};
} INVENTORYARRAY, *PINVENTORYARRAY;

//aSdeityD CharInfo2__CharInfo2
// actual size: 0x9a28 2016 04 13 test (see 85B22A) - eqmule
typedef struct _CHARINFO2 {
/*0x0000*/ BYTE         Unknown0x0000[0x18];
/*0x0018*/ struct _INVENTORYARRAY*      pInventoryArray;
/*0x001c*/ BYTE         Unknown0x001c[0x48];
/*0x0064*/ struct _SPELLBUFF    Buff[NUM_LONG_BUFFS];
/*0x0ed4*/ struct _SPELLBUFF    ShortBuff[NUM_SHORT_BUFFS];
/*0x21bc*/ DWORD        ZoneBuffs[NUM_BUFF_SLOTS]; // caster IDs for the Effects Window of whoever cast the buff on you in the same zone...
/*0x2340*/ DWORD        ZoneSongs[NUM_BUFF_SLOTS]; // just a guess
/*0x24c4*/ DWORD        SpellBook[NUM_BOOK_SLOTS];
/*0x3144*/ DWORD        MemorizedSpells[0x10];
/*0x3184*/ DWORD        Skill[0x64];
/*0x3314*/ DWORD        InnateSkill[0x19];
/*0x3378*/ BYTE         Unknown0x3378[0xd8];
/*0x3450*/ DWORD        Gender;
/*0x3454*/ DWORD        Race;
/*0x3458*/ DWORD        Class;
/*0x345c*/ BYTE         Unknown0x345c[0x10];
/*0x346c*/ DWORD        Level;
/*0x3470*/ DWORD        Mana;
/*0x3474*/ DWORD        Endurance;
/*0x3478*/ DWORD        BaseHP;
/*0x347c*/ DWORD        BaseSTR;
/*0x3480*/ DWORD        BaseSTA;
/*0x3484*/ DWORD        BaseCHA;
/*0x3488*/ DWORD        BaseDEX;
/*0x348c*/ DWORD        BaseINT;
/*0x3490*/ DWORD        BaseAGI;
/*0x3494*/ DWORD        BaseWIS;
/*0x3498*/ BYTE         Unknown0x3498[0x4];
/*0x349c*/ DWORD        Plat;
/*0x34a0*/ DWORD        Gold;
/*0x34a4*/ DWORD        Silver;
/*0x34a8*/ DWORD        Copper;
/*0x34ac*/ DWORD        CursorPlat;
/*0x34b0*/ DWORD        CursorGold;
/*0x34b4*/ DWORD        CursorSilver;
/*0x34b8*/ DWORD        CursorCopper;
/*0x34bc*/ BYTE         Unknown0x34bc[0x28];
/*0x34e4*/ DWORD        thirstlevel;
/*0x34e8*/ DWORD        hungerlevel;
/*0x34ec*/ BYTE         Unknown0x34ec[0x4];
/*0x34f0*/ DWORD        Shrouded;
/*0x34f4*/ BYTE         Unknown0x34f4[0x74];
/*0x3568*/ DWORD        ZoneBoundID;
/*0x356c*/ FLOAT        ZoneBoundY;
/*0x3570*/ FLOAT        ZoneBoundX;
/*0x3574*/ FLOAT        ZoneBoundZ;
/*0x3578*/ FLOAT        ZoneBoundHeading;
/*0x357c*/ BYTE         Unknown0x357c[0x50];
/*0x35cc*/ DWORD        ArmorType[0x16];
/*0x3624*/ BYTE         Unknown0x3624[0x160];
/*0x3784*/ AALIST       AAList[AA_CHAR_MAX_REAL];
/*0x4594*/ DWORD        BodyColor[0x9];
/*0x45b8*/ BYTE         Unknown0x45b8[0x2000];
/*0x65b8*/ DWORD        CombatAbilities[NUM_COMBAT_ABILITIES];
/*0x6a68*/ DWORD        SpellRecastTimer[0xC];
/*0x6a98*/ BYTE         Unknown0x6a98[0x70];
/*0x6b08*/ DWORD        CombatAbilityTimes[0x14];
/*0x6b58*/ BYTE         Unknown0x6b58[0x1dc4];
/*0x891c*/ DWORD        Deity;
/*0x8920*/ BYTE         Unknown0x8920[0xa0];
/*0x89c0*/ DWORD        Drunkenness;
/*0x89c4*/ BYTE         Unknown0x89c4[0x10];
/*0x89d4*/ DWORD        AAPoints;
/*0x89d8*/ BYTE         Unknown0x89d8[0x100c];
/*0x99e4*/ DWORD        AAPointsSpent;
/*0x99e8*/ DWORD        AAPointsAssigned;
/*0x99ec*/ BYTE         Unknown0x99c4[0x3c];
/*0x9a28*/
} CHARINFO2, *PCHARINFO2;

typedef struct _MODELINFONAME {
/*0x00*/    DWORD Unknown0000;
/*0x04*/    DWORD Unknown0004;
/*0x08*/    PCHAR Name;
/*0x0c*/
} MODELINFONAME, *PMODELINFONAME;

typedef struct _MODELINFO_GENERIC {
/*0x00*/    DWORD Type;
/*0x04*/    DWORD Unknown0x04;
/*0x08*/    DWORD Unknown0x08;
/*0x0c*/    DWORD Unknown0x0c;
/*0x10*/    DWORD Unknown0x10;
/*0x14*/
} MODELINFO_GENERIC, *PMODELINFO_GENERIC;

typedef struct _MODELINFO_48 {
/*0x00*/    struct _MODELINFO_GENERIC Header;
/*0x14*/    FLOAT Float1;
/*0x18*/    FLOAT Float2;
/*0x1c*/    FLOAT Float3;
/*0x20*/    struct _MODELINFONAME *pModelName;
/*0x24*/
} MODELINFO_48, *PMODELINFO_48;

typedef struct _MODELINFO_51 {
/*0x00*/    struct _MODELINFO_GENERIC Header;
/*0x14*/    struct _MODELINFONAME *pFontName;
/*0x18*/    PCHAR LabelText;
/*0x1c*/
} MODELINFO_51, *PMODELINFO_51;

// 10/09/2003 build      plazmic
// 12/24/2003 verified   Amadeus
typedef struct _MODELINFO {
/*0x00*/    DWORD   Unknown;
/*0x04*/    PCHAR NameDAG;
/*0x08*/    struct _MODELINFO_GENERIC *pModelInfo;
/*0x0c*/    struct _MODELINFO *pNextInChain;
/*0x10*/    PVOID pUnknown;
/*0x14*/    struct _MODELINFONAME *pTrack1;
/*0x18*/    struct _MODELINFONAME *pTrack2;
   //moredata
} MODELINFO, *PMODELINFO;

// 4/30/2003 build      eqmule
typedef struct _CAMERAINFO {
/*0x00*/   DWORD Unknown0x00;
/*0x04*/   DWORD Unknown0x04;
/*0x08*/   BYTE Unknown0x08[0x8];
/*0x10*/   FLOAT Y;
/*0x14*/   FLOAT X;
/*0x18*/   FLOAT Z;
/*0x1c*/   FLOAT LightRadius;
/*0x20*/
} CAMERAINFO, *PCAMERAINFO;


#define MODEL_LABEL                     0 
#define MODEL_LABELINFO                 1
#define MODEL_NULL2                     2
#define MODEL_HELD_R                    3
#define MODEL_HELD_L                    4
#define MODEL_SHIELD                    5
#define MODEL_NULL6                     6

/*
//Work in progress...
#define MODEL_HEAD                      0x00
#define MODEL_HEAD_POINT                0x01
#define MODEL_NULL_1                    0x02
#define MODEL_HELD_R                    0x03
#define MODEL_HELD_L                    0x04
#define MODEL_SHIELD                    0x05
#define MODEL_NULL_2                    0x06
#define MODEL_TUNIC                     0x07
#define MODEL_HAIR                      0x08
#define MODEL_BEARD                     0x09
#define MODEL_CHEST                     0x0a
#define MODEL_GLOVES                    0x0b
#define MODEL_GLOVES2                   0b0c
*/

typedef struct _ARGBCOLOR {
    union {
        struct {
            BYTE B;
            BYTE G;
            BYTE R;
            BYTE A;
        };
        DWORD ARGB;
    };
} ARGBCOLOR, *PARGBCOLOR;

// actual size: 0x14 05-14-2013 - eqmule
typedef struct _ARMOR {
/*0x00*/ DWORD  ID; //idfile on Lucy
/*0x04*/ DWORD  Unknown0x04;
/*0x08*/ DWORD  Unknown0x08;
/*0x0c*/ DWORD  Unknown0x0c;
/*0x10*/ DWORD  Unknown0x10;
/*0x14*/
} ARMOR, *PARMOR;

// 10-22-2003 Lax
typedef struct _EQUIPMENT {
   union {
      struct// EQUIPARRAY
      {
         struct _ARMOR Item[9];
      };// Array;
      struct //EQUIPUNIQUE
      {
         struct _ARMOR Head;//0x14
         struct _ARMOR Chest;
         struct _ARMOR Arms;
         struct _ARMOR Wrists;
         struct _ARMOR Hands;
         struct _ARMOR Legs;
         struct _ARMOR Feet;
         struct _ARMOR Primary;
         struct _ARMOR Offhand;
      };// Unique;
   };
} EQUIPMENT, *PEQUIPMENT;

// 10-14-07 - ieatacid
typedef struct _FELLOWSHIPMEMBER {
/*0x00*/  DWORD   Unknown0x0;
/*0x04*/  CHAR    Name[0x40];
/*0x44*/  WORD    ZoneID;
/*0x46*/  WORD    InstanceID;
/*0x48*/  DWORD   Level;
/*0x4c*/  DWORD   Class;
/*0x50*/  DWORD   LastOn;    // FastTime() timestamp
/*0x54*/
} FELLOWSHIPMEMBER, *PFELLOWSHIPMEMBER;

// 20121128 - ieatacid  0x9e4
typedef struct _FELLOWSHIPINFO {
/*0x000*/  DWORD  Unknown0x0;        // always 1?
/*0x004*/  DWORD  FellowshipID;
/*0x008*/  CHAR   Leader[0x40];
/*0x048*/  CHAR   MotD[0x400];
/*0x448*/  DWORD  Members;
/*0x44c*/  struct _FELLOWSHIPMEMBER  FellowshipMember[0xc];
/*0x83c*/  DWORD  Unknown0x83c;      // timestamp for something
/*0x840*/  BYTE   Unknown0x840[0x1a4];
/*0x9e4*/
} FELLOWSHIPINFO, *PFELLOWSHIPINFO;

// offsets are relative to their position in _LAUNCHSPELLDATA
typedef struct _ITEMLOCATION {
/*0x0c*/ DWORD    a;
/*0x10*/ DWORD    InvSlot;
/*0x14*/ DWORD    BagSlot;
/*0x18*/ DWORD    d;
/*0x1c*/
} ITEMLOCATION, *PITEMLOCATION;

typedef struct _LAUNCHSPELLDATA {
/*0x00*/ DWORD    SpellETA;           //Calculated TimeStamp when current spell being cast will land. 0 while not casting.
/*0x04*/ DWORD    SpellID;            // -1 = not casting a spell
/*0x08*/ BYTE     SpellSlot;          // 0xFF if not casting, otherwise it's the spell gem number (0 - 8)
/*0x09*/ BYTE     Padding0x9[0x3];
/*0x0c*/ struct   _ITEMLOCATION ItemLocation;
/*0x1c*/ DWORD    ItemID;
/*0x20*/ FLOAT    CastingY;
/*0x24*/ FLOAT    CastingX;
/*0x28*/ BYTE     Unknown0x28[0x4];
/*0x2c*/ DWORD    TargetID;
/*0x30*/ BYTE     Unknown0x30[0x14];
/*0x44*/ DWORD    Unknown0x44;
/*0x48*/ DWORD    Unknown0x48;
/*0x4c*/ DWORD    Unknown0x4c;
/*0x50*/
} LAUNCHSPELLDATA, *PLAUNCHSPELLDATA;

//this is the size of EQPlayer__EQPlayer_x
// actual size 0x1FE8 in Apr 21 2016 Live (see 0x5D4CDA) - eqmule
typedef struct _SPAWNINFO {
/*0x0000*/ void*	vtable;
/*0x0004*/ struct _SPAWNINFO*	pPrev;
/*0x0008*/ struct _SPAWNINFO*	pNext;
/*0x000c*/ BYTE		Unknown0x000c[0xc];
/*0x0018*/ FLOAT	SpeedMultiplier;
/*0x001c*/ BYTE		Unknown0x001c[0xc];
/*0x0028*/ FLOAT	Feet;//or floor or something, work in progress -eqmule 2015-07-20
/*0x002c*/ BYTE		Unknown0x002c[0x4];
/*0x0030*/ DWORD	PlayerTimeStamp;//doesnt update when on a Vehicle (mounts/boats etc)
/*0x0034*/ BYTE		Unknown0x0034[0x4];
/*0x0038*/ CHAR		Lastname[0x20];
/*0x0058*/ BYTE		Unknown0x0058[0xc];
/*0x0064*/ FLOAT	Y;
/*0x0068*/ FLOAT	X;
/*0x006c*/ FLOAT	Z;
/*0x0070*/ FLOAT	SpeedY;
/*0x0074*/ FLOAT	SpeedX;
/*0x0078*/ FLOAT	SpeedZ;
/*0x007c*/ FLOAT	SpeedRun;
/*0x0080*/ FLOAT	Heading;
/*0x0084*/ BYTE		Unknown0x0084[0x8];
/*0x008c*/ FLOAT	SpeedHeading;
/*0x0090*/ FLOAT	CameraAngle;
/*0x0094*/ BYTE		UnderWater;
/*0x0095*/ BYTE		Unknown0x0095[0xc];
/*0x00a1*/ BYTE		FeetWet;
/*0x00a2*/ BYTE		Unknown0x00a2[0x2];
/*0x00a4*/ CHAR		Name[0x40];             // ie priest_of_discord00
/*0x00e4*/ CHAR		DisplayedName[0x40];    // ie Priest of Discord
/*0x0124*/ BYTE		PossiblyStuck;                  //never seen this be 1 so maybe it was used a a point but not now...
/*0x0125*/ BYTE		Type;
/*0x0126*/ BYTE		Unknown0x0126[0x2];
/*0x0128*/ DWORD**	BodyType;
/*0x012c*/ BYTE		Unknown0x012c[0xc];
/*0x0138*/ FLOAT	AvatarHeight;           // height of avatar from groundwhen standing
/*0x013c*/ FLOAT	UnknownHeight;
/*0x0140*/ FLOAT	AvatarHeight2;          // height of avatar from groundwhen crouched/sitting
/*0x0144*/ BYTE		Unknown0x0144[0x4];
/*0x0148*/ DWORD	SpawnID;
/*0x014c*/ DWORD	PlayerState;                    //0=Idle 1=Open 2=WeaponSheathed 4=Aggressive 8=ForcedAggressive 0x10=InstrumentEquipped 0x20=Stunned 0x40=PrimaryWeaponEquipped 0x80=SecondaryWeaponEquipped
/*0x0150*/ DWORD	IsABoat;                // 1 = a type of boat
/*0x0154*/ struct _SPAWNINFO*	Mount;      // NULL if no mount present
/*0x0158*/ struct _SPAWNINFO*	Rider;      // _SPAWNINFO of mount's rider
/*0x015c*/ BYTE		Unknown0x015c[0x4];
/*0x0160*/ BYTE		Targetable;//1 if mob is targetable
/*0x0161*/ BYTE		Unknown0x0161[0x33];
/*0x0194*/ DWORD	ManaCurrent;
/*0x0198*/ BYTE		Unknown0x0198[0x8];
/*0x01a0*/ DWORD	SpellGemETA[0xc];
/*0x01d0*/ DWORD	InnateETA;              //Calculated TimeStamp when innate skill will be ready (LoH, HT, Bash)
/*0x01d4*/ BYTE		Unknown0x01d4[0x8];
/*0x01dc*/ LONG		HPMax;
/*0x01e0*/ BYTE		Unknown0x01e0[0x4];
/*0x01e4*/ FLOAT	ViewHeight;
/*0x01e8*/ BYTE		Unknown0x01e8[0x4];
/*0x01ec*/ BYTE		Light;
/*0x01ed*/ BYTE		Unknown0x01ed[0x7];
/*0x01f4*/ DWORD	Trader;//found in CEverQuest__RightClickedOnPlayer_x
/*0x01f8*/ DWORD	TimeStamp;//updates all the time including when on a mount
/*0x01fc*/ BYTE		PvPFlag;
/*0x01fd*/ BYTE		Unknown0x01fd[0x3];
/*0x0200*/ FLOAT	RunSpeed;//0.70 on runspeed 5...
/*0x0204*/ DWORD	PetID;//the unknown above this is petwindow target related I think
/*0x0208*/ DWORD	Buyer;
/*0x020c*/ BYTE		Unknown0x020c[0x4];
/*0x0210*/ DWORD	EnduranceCurrent;
/*0x0214*/ DWORD	AFK;
/*0x0218*/ BYTE		Unknown0x0218[0x4];
/*0x021c*/ DWORD	MasterID;
/*0x0220*/ BYTE		Unknown0x0220[0x4];
/*0x0224*/ BYTE		HideMode;
/*0x0225*/ BYTE		Unknown0x0225[0xb];
/*0x0230*/ DWORD	Anon;//found in EQPlayer__SetNameSpriteTint_x
/*0x0234*/ BYTE		Unknown0x0234[0xc];
/*0x0240*/ DWORD	GuildStatus;
/*0x0244*/ DWORD	EnduranceMax;
/*0x0248*/ BYTE		StandState;
/*0x0249*/ BYTE		Unknown0x0249[0x7];
/*0x0250*/ DWORD	RespawnTimer;           // TimeStamp of when RespawnWnd will close - 0 when you're alive
/*0x0254*/ DWORD	LastTick;
/*0x0258*/ BYTE		Unknown0x0258[0x4];
/*0x025c*/ LONG		HPCurrent;
/*0x0260*/ BYTE		Mercenary;
/*0x0261*/ BYTE		Unknown0x0261[0x30];
/*0x0291*/ BYTE		HoldingType; // I dont know the types, i put a 2h in Primary and its a 4 , modrod there and its a 1, nothing its a 5 -eqmule
/*0x0292*/ BYTE		Unknown0x0292[0x6];
/*0x0298*/ DWORD	FishingETA;
/*0x029c*/ BYTE		Unknown0x029c[0xc];
/*0x02a8*/ DWORD	ManaMax;
/*0x02ac*/ BYTE		Unknown0x02ac[0x4c];
/*0x02f8*/ BYTE		Sneak;
/*0x02f9*/ BYTE		Unknown0x02f9[0x8a];
/*0x0383*/ BYTE		Linkdead;
/*0x0384*/ BYTE		Unknown0x0384[0x24];
/*0x03a8*/ DWORD	SpellCooldownETA;
/*0x03ac*/ BYTE		Unknown0x03ac[0x14];
/*0x03c0*/ FLOAT	GetMeleeRangeVar1;      // used by GetMeleeRange
/*0x03c4*/ CHAR		Title[0x80];
/*0x0444*/ DWORD	GuildID;
/*0x0448*/ BYTE		Level;
/*0x0449*/ BYTE		GM;
/*0x044a*/ BYTE		Unknown0x044a[0x8e];
/*0x04d8*/ CHAR		Suffix[0x80];
/*0x0558*/ struct _EQC_INFO*	spawneqc_info;
/*0x055c*/ BYTE		Unknown0x055c[0x8];
/*0x0564*/ WORD		Zone;
/*0x0566*/ WORD		Instance;
/*0x0568*/ BYTE		Unknown0x0568[0x4];
/*0x056c*/ DWORD	Deity;
/*0x0570*/ BYTE		LFG;
/*0x0571*/ BYTE		Unknown0x0571[0x3];
/*0x0574*/ DWORD	AARank;
/*0x0578*/ BYTE		Unknown0x0578[0x14];
/*0x058c*/ struct _LAUNCHSPELLDATA	CastingData; // size: 0x50
/*0x05dc*/ BYTE		FishingEvent;
/*0x05dd*/ BYTE		Unknown0x05dd[0x923];
/*0x0f00*/ struct _SPAWNINFO*	WhoFollowing; // NULL if autofollow off
/*0x0f04*/ DWORD	GroupAssistNPC[0x1];
/*0x0f08*/ DWORD	RaidAssistNPC[0x3];
/*0x0f14*/ DWORD	GroupMarkNPC[0x3];
/*0x0f20*/ DWORD	RaidMarkNPC[0x3];
/*0x0f2c*/ DWORD	TargetOfTarget;
/*0x0f30*/ BYTE		Unknown0x0f30[0x30];
/*0x0f60*/ void*	pActorClient;          // start of ActorClient struct
/*0x0f64*/ BYTE		InNonPCRaceIllusion;
/*0x0f65*/ BYTE		Unknown0x0f65[0x3];
/*0x0f68*/ BYTE		FaceStyle;
/*0x0f69*/ BYTE		HairColor;
/*0x0f6a*/ BYTE		FacialHairColor;
/*0x0f6b*/ BYTE		EyeColor1;
/*0x0f6c*/ BYTE		EyeColor2;
/*0x0f6d*/ BYTE		HairStyle;
/*0x0f6e*/ BYTE		FacialHair;
/*0x0f6f*/ BYTE		Unknown0x0f6f;
/*0x0f70*/ DWORD	Race;
/*0x0f74*/ BYTE		Unknown0x0f74[0x4];
/*0x0f78*/ BYTE		Class;
/*0x0f79*/ BYTE		Unknown0x0f79[0x3];
/*0x0f7c*/ BYTE		Gender;
/*0x0f7d*/ CHAR		ActorDef[0x40];
/*0x0fbd*/ BYTE		Unknown0x0fbd[0x3];
/*0x0fc0*/ ARGBCOLOR	ArmorColor[0x9];
/*0x0fe4*/ BYTE		Unknown0x0fe4[0x4];
/*0x0fe8*/ DWORD	Heritage;               //drakkin only face setting
/*0x0fec*/ DWORD	Tattoo;                 //drakkin only face setting
/*0x0ff0*/ DWORD	Details;                //drakkin only face setting
/*0x0ff4*/ struct _EQUIPMENT	Equipment;   // size 0xb4
/*0x10a8*/ BYTE		Unknown0x10a8[0x38];
/*0x10e0*/ VOID*	pcactorex;             // ActorInterface*
/*0x10e4*/ BYTE		Unknown0x10e4[0x4];
/*0x10e8*/ VOID*	FaceRelatedActorStruct;
/*0x10ec*/ BYTE		Unknown0x10ec[0x34];
/*0x1120*/ FLOAT	GetMeleeRangeVar2;      // used by GetMeleeRange
/*0x1124*/ BYTE		Unknown0x1124[0x64];
/*0x1188*/ DWORD	Animation;
/*0x118c*/ BYTE		Unknown0x118c[0xe0];
/*0x126c*/ DWORD	Holding; //1 holding 0 not holding
/*0x1270*/ BYTE		Unknown0x1270[0x14];
/*0x1284*/ DWORD	MercID;                         //if the spawn is player and has a merc up this is it's spawn ID -eqmule 16 jul 2014
/*0x1288*/ DWORD	ContractorID;           //if the spawn is a merc this is its contractor's spawn ID -eqmule 16 jul 2014
/*0x128c*/ BYTE		Unknown0x128c[0x14];
/*0x12a0*/ FLOAT	WalkSpeed;
/*0x12a4*/ BYTE		Unknown0x12a4;
/*0x12a5*/ DWORD	HideCorpse;
/*0x12a9*/ BYTE		Unknown0x12a9[0x3c];
/*0x12e5*/ BYTE		InvitedToGroup;
/*0x12e6*/ BYTE		Unknown0x12e6[0x2];
/*0x12e8*/ DWORD	GroupMemberTargeted;    // 0xFFFFFFFF if no target, else 1 through 5
/*0x12ec*/ BYTE		Unknown0x12ec[0x184];
/*0x1470*/ struct _FELLOWSHIPINFO	Fellowship; // size 0x9e4
/*0x1e54*/ FLOAT	CampfireY;
/*0x1e58*/ FLOAT	CampfireX;
/*0x1e5c*/ FLOAT	CampfireZ;
/*0x1e60*/ WORD		CampfireZoneID;         // zone ID where campfire is
/*0x1e62*/ WORD		InstanceID;
/*0x1e64*/ DWORD	CampfireTimestamp;      // CampfireTimestamp-FastTime()=time left on campfire
/*0x1e68*/ BYTE		Unknown0x1e68[0x8];
/*0x1e70*/ DWORD	Campfire;               // do we have a campfire up?
/*0x1e74*/ BYTE		Unknown0x1e74[0x11c];
/*0x1f90*/ void*	vtable2;
/*0x1f94*/ BYTE		Unknown0x1f94[0x4];
/*0x1f98*/ struct _SPAWNINFO*	pSpawn;
/*0x1f9c*/ DWORD	Levitate;
/*0x1fa0*/ BYTE		Unknown0x1fa0[0x48];
/*0x1fe8*/
} SPAWNINFO, *PSPAWNINFO;

#define STANDSTATE_STAND                0x64
#define STANDSTATE_CASTING              0x66
#define STANDSTATE_BIND                 0x69
#define STANDSTATE_SIT                  0x6E
#define STANDSTATE_DUCK                 0x6F
#define STANDSTATE_FEIGN                0x73
#define STANDSTATE_DEAD                 0x78

#define MONITOR_SPAWN_X                 1
#define MONITOR_SPAWN_Y                 2
#define MONITOR_SPAWN_Z                 4
#define MONITOR_SPAWN_HEADING           8
#define MONITOR_SPAWN_SPEEDRUN          16
#define MONITOR_SPAWN_HPCURRENT         32

typedef struct _SPAWNMONITORINFO {
    WORD SpawnID;
    FLOAT Y;
    FLOAT X;
    FLOAT Z;
    FLOAT Heading;
    FLOAT SpeedRun;
    DWORD HPCurrent;
    DWORD MonitorMask;
} SPAWNMONITORINFO, *PSPAWNMONITORINFO;

typedef struct _HASHENTRY {
    SPAWNINFO   *spawn;
    DWORD       key;            // same as SpawnID for spawns
    struct      _HASHENTRY *next;
} HASHENTRY, *PHASHENTRY;

typedef struct _HASHTABLE {
    struct _HASHENTRY **table;
    int size;
} HASHTABLE, *PHASHTABLE;

typedef struct _SPAWNMANAGER {
/*0x000*/ void          *vftable;
/*0x004*/ DWORD         random; // rand()%20000
/*0x008*/ struct  _SPAWNINFO        *FirstSpawn;
/*0x00c*/ struct  _SPAWNINFO        *LastSpawn;
/*0x010*/ DWORD         unknown10;
/*0x014*/ struct        _HASHTABLE  *SPHash;
} SPAWNMANAGER, *PSPAWNMANAGER;


#if 0

void *gethashedentry(struct _HASHTABLE  *table, DWORD key)
{
    PHASHENTRY p = NULL;
    p = table->array[key%table->size];

    while(p) {
        if (p->key == key) return p;
        p = p->next;
    }
    return NULL;
}

#endif

// copy of D3DMATRIX by brainiac dec 16 2015
struct Matrix4x4
{
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

//eqmule oct 31 2013
typedef struct _SWITCHCLICK
{
	FLOAT Y;
	FLOAT X;
	FLOAT Z;
	FLOAT Y1;
	FLOAT X1;
	FLOAT Z1;
} SWITCHCLICK,*PSWITCHCLICK;
// this is actually ActorInterface
// actual size: 0x120 3-3-2009
// semi corrected on dec 16 2013 eqmule
// i *think* the size is 0x190
//however i couldnt confirm from 0x38 to 0x114
//more work is needed... anyone feel free to step up...

//updated on dec 16 2015 by brainiac
typedef struct _EQSWITCH {
/*0x00*/    DWORD        Unknown0x0[0x2];
/*0x08*/    float        UnknownData0x08;
/*0x0c*/    float        UnknownData0x0c;
/*0x10*/    float        Unknown0x10[0x2];
/*0x18*/    float        UnknownData0x18;
/*0x1c*/    float        Unknown0x1c;
/*0x20*/    float        UnknownData0x20;
/*0x24*/    float        Unknown0x24[0x2];
/*0x2C*/    FLOAT        Y;
/*0x30*/    FLOAT        X;
/*0x34*/    FLOAT        Z;
/*0x38*/    BYTE         Unknown0x38[0x4c]; //A lot of data here.
/*0x84*/    float        yAdjustment1;//from this point on im not sure -eqmule 2013 dec 16
/*0x88*/    float        xAdjustment1;
/*0x8c*/    float        zAdjustment1;
/*0x90*/    float        headingAdjustment1;
/*0x94*/    float        yAdjustment2;
/*0x98*/    float        xAdjustment2;
/*0x9c*/    float        zAdjustment2;
/*0xa0*/    float        headingAdjustment2;
/*0xa4*/    float        yAdjustment3;
/*0xa8*/    float        xAdjustment3;
/*0xac*/    float        zAdjustment3;
/*0xb0*/    float        headingAdjustment3;
/*0xb4*/    BYTE         Unknown0xb4[0x30];
/*0xe4*/    Matrix4x4    transformMatrix;
/*0x124*/   FLOAT        Heading;
/*0x128*/   BYTE         Unknown0x128[0x18];
/*0x140*/   float        HeightAdjustment;//this is most likely wrong dec 16 2013 eqmule
/*0x144*/   BYTE         Unknown0x144[0x4c];
/*0x190*/
} EQSWITCH, *PEQSWITCH;

// actual size 0xdc 2-9-2009
//updated on dec 16 2015 by brainiac
//not sure about its size - eqmule
typedef struct _DOOR {
/*0x00*/ void  *vtable;
/*0x04*/ BYTE  Unknown0x4;          // always 5
/*0x05*/ BYTE  ID;
/*0x06*/ CHAR  Name[0x20];
/*0x26*/ BYTE  Type;
/*0x27*/ BYTE  State;               // 0 = closed, 1 = open, 2 = opening, 3 = closing
/*0x28*/ FLOAT DefaultY;
/*0x2c*/ FLOAT DefaultX;
/*0x30*/ FLOAT DefaultZ;
/*0x34*/ FLOAT DefaultHeading;
/*0x38*/ FLOAT DefaultDoorAngle;
/*0x3c*/ FLOAT TopSpeed1;
/*0x40*/ FLOAT TopSpeed2;
/*0x44*/ FLOAT Y;
/*0x48*/ FLOAT X;
/*0x4c*/ FLOAT Z;
/*0x50*/ FLOAT Heading;
/*0x54*/ FLOAT DoorAngle;
/*0x58*/ BYTE  Unknown0x58[0x18];
/*0x70*/ int   Unknown0x70;         // always 0xFFFFFFFF
/*0x74*/ SHORT ScaleFactor;         // divide by 100 to get scale multiplier
/*0x76*/ BYTE  Unknown0x76[2];
/*0x78*/ DWORD ZonePoint;
/*0x7c*/ BYTE  Unknown0x7c[0x5];
/*0x81*/ BYTE  Unknown0x81;
/*0x82*/ BYTE  Unknown0x82[0x22];
/*0xa4*/ PEQSWITCH pSwitch;         // (CActorInterface*)
/*0xa8*/ void  *pUnknown0xa8;       // (CParticleCloudInterface*)
/*0xac*/ DWORD TimeStamp;
/*0xb0*/ BYTE  Unknown0xb0[0x2c];
/*0xdc*/
} DOOR, *PDOOR; 

// 7-21-2003    Stargazer
typedef struct _DOORTABLE {
/*0x000*/   DWORD NumEntries;
/*0x004*/   PDOOR pDoor[0x0FF];
/*0x400*/
} DOORTABLE, *PDOORTABLE;

// actual size 0x80 20101012 - ieatacid
typedef struct _GROUNDITEM {
/*0x00*/ struct _GROUNDITEM *pPrev;
/*0x04*/ struct _GROUNDITEM *pNext;
/*0x08*/ DWORD  ID;
/*0x0c*/ DWORD  DropID;
/*0x10*/ DWORD  ZoneID;
/*0x14*/ DWORD  DropSubID;
/*0x18*/ PEQSWITCH pSwitch; // (class EQSwitch *)
/*0x1c*/ CHAR   Name[0x20];
/*0x3c*/ BYTE   Unknown0x3c[0x24];
/*0x60*/ FLOAT  Heading;
/*0x64*/ BYTE   Unknown0x64[0xc];
/*0x70*/ FLOAT  Y;
/*0x74*/ FLOAT  X;
/*0x78*/ FLOAT  Z;
/*0x7c*/ BYTE   Unknown0x7c[0x4];
/*0x80*/
} GROUNDITEM, *PGROUNDITEM;

#define   MAX_ZONES                     0x3e8
extern    PCHAR szZoneExpansionName[];     //defined in LibEQ_Utilities.cpp

//Size 0x1D8 see 867D39 in eqgame.exe live 21 apr 2016 - eqmule
typedef struct _ZONELIST { 
/*0x000*/   DWORD   Header; 
/*0x004*/   DWORD   Unknown0x4;         //pointer to something? 
/*0x008*/   DWORD   EQExpansion;          // szZoneExpansionName[] 
/*0x00c*/   DWORD   Id;  //EQZoneIndex
/*0x010*/   CHAR    ShortName[0x80];
/*0x090*/   BYTE    Unknown0x090;
/*0x091*/   CHAR    LongName[0x100]; 
/*0x191*/   DWORD   Unknown0x191; 
/*0x192*/   DWORD   Unknown0x192[0x6];  
/*0x198*/   DWORD   ZoneFlags;              // 0x800000 = gmzone? 0x8000 water/mountainzone? 0x4 = ? 0x1 = MultiInstanceZone 0x10000000 bazaarzone 0x2000000 = barterzone 0x100000 = HasMinLevel, 0x1000000 = tutorialzone 0x4000 = no air, 0x2 newbie zone, 0x20 no bind, 0x400000 lostestingdisabled, 0x80000000 guildhallzone
/*0x19c*/   DWORD   Unknown0x19c; 
/*0x1a0*/   DWORD   eqstrID;                // can call pStringTable->getString to get this string
/*0x1a4*/   DWORD   PoPValue;           // This has something to do with PoP zones. 
/*0x1a8*/   DWORD   MinLevel;           // Minimum level to access is this used?
/*0x1ac*/   BYTE    Unknown0x1ac[0x8];             
/*0x1b4*/   BYTE    Unknown0x1b4;//something 
/*0x1b5*/   BYTE    Unknown0x1b5[0x3]; 
/*0x1b8*/   BYTE    Unknown0x1b8[0x20];
/*0x1D8      next zone in list*/ 
} ZONELIST, *PZONELIST;

//EQWorldData__EQWorldData_x
//Size 0xFC0 see 5721F1 in eqgame.exe live 21 apr 2016 - eqmule
typedef struct _WORLDDATA {
/*0x000*/ PVOID lpvTable;
/*0x004*/ BYTE Hour;
/*0x005*/ BYTE Minute;
/*0x006*/ BYTE Day;
/*0x007*/ BYTE Month;
/*0x008*/ DWORD Year;
/*0x00C*/ BYTE Unknown0x00C[0x14];
/*0x020*/ PZONELIST ZoneArray[MAX_ZONES];// see 867D1B in eqgame.exe live 21 apr 2016
/*0xFC0*/
} WORLDDATA, *PWORLDDATA;

//Size 0x??? see ?????? corrected this based on eqgame.exe live 21 apr 2016 - eqmule
typedef struct _ZONEINFO {
/*0x000*/   CHAR    CharacterName[0x40];
/*0x040*/   CHAR    ShortName[0x20];
/*0x060*/   CHAR    Unknown0x060[0x60];
/*0x0c0*/   CHAR    LongName[0x80];
/*0x140*/   CHAR    Unknown0x140[0x96];  // <-- this isnt part of zone name, see CEverQuest__CEverQuest
/*0x1d6*/   BYTE    ZoneType; // (usually FF)
/*0x1d7*/   ARGBCOLOR FogRed;
/*0x1db*/   ARGBCOLOR FogGreen;
/*0x1df*/   ARGBCOLOR FogBlue;
/*0x1e3*/   BYTE    Unknown0x1e3;
/*0x1e4*/   FLOAT   Unknown0x1e4[0x4];
/*0x1f4*/   FLOAT   Unknown0x1f4[0x4];
/*0x204*/   FLOAT   ZoneGravity;
/*0x208*/   BYTE    Unknown0x208;
/*0x209*/   BYTE    Unknown0x209[0x11];
/*0x21a*/   BYTE    SkyType;   
/*0x21b*/   BYTE    Unknown0x21b;   
/*0x21c*/   DWORD   Something;   
/*0x220*/   DWORD   Somethingtoo;
/*0x224*/   DWORD   Unknown0x224;
/*0x228*/   FLOAT   ZoneExpModifier;    //This has been nerfed ..now reads 1.0 for all zones
/*0x22c*/   FLOAT   SafeYLoc;
/*0x230*/   FLOAT   SafeXLoc;
/*0x234*/   FLOAT   SafeZLoc;
/*0x238*/   BYTE    Unknown0x238[0x4];
/*0x23c*/   FLOAT   Ceiling;
/*0x240*/   FLOAT   Floor;
/*0x244*/   FLOAT   MinClip;
/*0x248*/   FLOAT   MaxClip;
/*0x24c*/   BYTE    Unknown0x24c[0x54];
/*0x2a0*/   CHAR    ShortNameLwr[0x60];
/*0x300*/ //there is more data here i dont know the size of this struct - eqmule
} ZONEINFO, *PZONEINFO;

typedef struct _SPELLCALCINFO
{
/*0x00*/	LONG Slot;
/*0x04*/	LONG Base;
/*0x08*/	LONG Base2;
/*0x0c*/	LONG Max;
/*0x10*/	LONG Calc;
/*0x14*/	LONG Attrib;
/*0x18*/	CHAR Stuff[4];
/*0x1c*/	DWORD Delimiter;//always ^ ? (0x88)
/*0x20*/
}SPELLCALCINFO,*PSPELLCALCINFO;
#define   TOTAL_SPELL_COUNT             0xC350      // # of spells allocated in memory (06/11/2014) -eqmule
#define   CalcInfoSize                  0x2ab98     // 5FD9EC in eqgame 2016 13 apr test
//this is actually the size of the struct thats populated from aSpells_S_txt
//SpellManager__SpellManager
// size: 0x16F5A8 2016-04-13 test (see 55EE01) - eqmule
typedef struct _SPELLMGR {
/*0x000000*/ PVOID vfTable;//need this for some calls later
/*0x000004*/ BYTE Unknown0x00004[0x31f68];
/*0x031F6C*/ struct _SPELL* Spells[TOTAL_SPELL_COUNT];//50000
/*0x062cac*/ struct _SPELL* PtrToUnknownSpell;//default bailout pointer...
/*0x062CB0*/ struct _SPELLCALCINFO* CalcInfo[CalcInfoSize];//175000
/*0x10DB10*/ DWORD What1[0x6];
/*0x10DB28*/ DWORD What2[0x186a0];//100000
/*0x16F5A8*/ //(1500648) 1.5 mill? hmm large struct in memory for sure...
} SPELLMGR, *PSPELLMGR;

// actual size: 0x4ed 20120316 - ieatacid
// confirmed in Sep 16 2015 test eqgame see 4DB236 - eqmule
// actual size: 0x409 2016 02 10 test se 4E0341 - eqmule
// Filled in missing values see Mar 11 2016 test eqgame / 4DF9C0 - demonstar55
// EQ_Spell__EQ_Spell_x    numeffects  attrib1  base1  base2_1  calc1  max1
typedef struct _SPELL { //      1     |    0   | -30  |   0    | 103  | 125
/*0x000*/   FLOAT   Range;
/*0x004*/   FLOAT   AERange;
/*0x008*/   FLOAT   PushBack;
/*0x00c*/   FLOAT   PushUp;
/*0x010*/   DWORD   CastTime;
/*0x014*/   DWORD   FizzleTime;
/*0x018*/   DWORD   RecastTime;
/*0x01c*/   DWORD   DurationType;       //DurationFormula on Lucy
/*0x020*/   DWORD   DurationValue1;
/*0x024*/   DWORD   AEDuration;
/*0x028*/   DWORD   Mana;
/*0x02c*/   DWORD   ReagentId[0x4];     //ReagentId1-ReagentId4d
/*0x03c*/   DWORD   ReagentCount[0x4];  //ReagentCount1-ReagentCount4
/*0x04c*/   DWORD   NoExpendReagent[0x4];
/*0x05c*/   LONG    CalcIndex;
/*0x060*/   LONG    NumEffects;
/*0x064*/   DWORD   BookIcon;
/*0x068*/   DWORD   GemIcon;
/*0x06C*/   DWORD   DescriptionNumber;
/*0x070*/   DWORD   ResistAdj;
/*0x074*/   DWORD   Diety;
/*0x078*/   DWORD   spaindex;
/*0x07C*/   DWORD   SpellAnim;
/*0x080*/   DWORD   SpellIcon;
/*0x084*/   DWORD   DurationParticleEffect;
/*0x088*/   DWORD   NPCUsefulness;
/*0x08c*/   DWORD   ID;
/*0x090*/   DWORD   Autocast;         //SpellID of spell to instacast on caster when current spell lands on target
/*0x094*/   DWORD   Category;         //Unknown144 from lucy
/*0x098*/   DWORD   Subcategory;      //Subcat to Category. Unknown145 from lucy
/*0x09c*/   DWORD   Subcategory2;
/*0x0a0*/   DWORD   HateMod;          //Additional hate
/*0x0a4*/   DWORD   ResistPerLevel;
/*0x0a8*/   DWORD   ResistCap;
/*0x0ac*/   DWORD   EnduranceCost;      //CA Endurance Cost
/*0x0b0*/   DWORD   CARecastTimerID;    //ID of combat timer, i think.
/*0x0b4*/   DWORD   EndurUpkeep;
/*0x0b8*/   DWORD   HateGenerated;      //Hate override
/*0x0bc*/   DWORD   HitCountType;
/*0x0c0*/   DWORD   HitCount;
/*0x0c4*/   DWORD   ConeStartAngle;
/*0x0c8*/   DWORD   ConeEndAngle;
/*0x0cc*/   DWORD   PvPResistBase;
/*0x0d0*/   DWORD   PvPCalc;
/*0x0d4*/   DWORD   PvPResistCap;
/*0x0d8*/   DWORD   PvPDuration;        //DurationType for PVP
/*0x0dc*/   DWORD   PvPDurationValue1;  //DurationValue1 for PVP
/*0x0e0*/   DWORD   GlobalGroup;
/*0x0e4*/   DWORD   PCNPCOnlyFlag;      // no idea
/*0x0e8*/   DWORD   NPCMemCategory;
/*0x0ec*/   DWORD   SpellGroup;
/*0x0f0*/   DWORD   SubSpellGroup;		//unknown237 on Lucy it is checked at 0x76FE18 in jun 11 2014 and if 0 will ask if we want to replace our spell with a rk. x version
/*0x0f4*/   DWORD   SpellRank;			//Unknown209 on Lucy jun 11 2014 0x76FEE0 Original = 1 , Rk. II = 5 , Rk. III = 10 , I suppose if they add Rk. IV it will be 15 and so on -eqmule
/*0x0f8*/   DWORD   SpellClass;         //Unknown222 from Lucy
/*0x0fc*/   DWORD   SpellSubClass;         //Unknown223 from Lucy
/*0x100*/   DWORD   SpellReqAssociationID;
/*0x104*/   DWORD   CasterRequirementID;
/*0x108*/   DWORD   MaxResist;
/*0x10c*/   DWORD   MinResist;
/*0x110*/   DWORD   MinSpreadTime;
/*0x114*/   DWORD   MaxSpreadTime;
/*0x118*/   DWORD   SpreadRadius;
/*0x11c*/   DWORD   BaseEffectsFocusCap; //song cap, maybe other things?
/*0x120*/   DWORD   CritChanceOverride;
/*0x124*/   DWORD   MaxTargets;     //how many targets a spell will affect
/*0x128*/   DWORD   AIValidTargets;
/*0x12c*/   DWORD   BaseEffectsFocusOffset;
/*0x130*/   FLOAT   BaseEffectsFocusSlope;
/*0x134*/   FLOAT   DistanceModCloseDist;
/*0x138*/   FLOAT   DistanceModCloseMult;
/*0x13c*/   FLOAT   DistanceModFarDist;
/*0x140*/   FLOAT   DistanceModFarMult;
/*0x144*/   FLOAT   MinRange;
/*0x148*/   BYTE    NoNPCLOS; // NPC skips LOS checks
/*0x149*/   BYTE    Feedbackable; // nothing uses this
/*0x14a*/   BYTE    Reflectable;
/*0x14b*/   BYTE    NoPartialSave;
/*0x14c*/   BYTE    NoResist;
/*0x14d*/   BYTE    UsesPersistentParticles;
/*0x14e*/   BYTE    SmallTargetsOnly;
/*0x14f*/   BYTE    DurationWindow;     //0=Long, 1=Short
/*0x150*/   BYTE    Uninterruptable;
/*0x151*/   BYTE    NotStackableDot;
/*0x152*/   BYTE    Deletable;
/*0x153*/   BYTE    BypassRegenCheck;
/*0x154*/   BYTE    CanCastInCombat;
/*0x155*/   BYTE    CanCastOutOfCombat;
/*0x156*/   BYTE    NoHealDamageItemMod; //disable worn focus bonuses
/*0x157*/   BYTE    OnlyDuringFastRegen;
/*0x158*/   BYTE    CastNotStanding;
/*0x159*/   BYTE    CanMGB;
/*0x15a*/   BYTE    NoDisspell;
/*0x15b*/   BYTE    AffectInanimate; //ldon trap spells etc
/*0x15c*/   BYTE    IsSkill;
/*0x15d*/   BYTE    ShowDoTMessage;
/*0x15e*/   BYTE    ClassLevel[0x24];        //per class., yes there are allocations for 0x24 see 4B5776 in eqgame dated 12 mar 2014 -eqmule
/*0x182*/   BYTE    LightType;
/*0x183*/   BYTE    SpellType;          //0=detrimental, 1=Beneficial, 2=Beneficial, Group Only
/*0x184*/   BYTE    Activated;
/*0x185*/   BYTE    Resist;             //0=un 1=mr 2=fr 3=cr 4=pr 5=dr 6=chromatic 7=prismatic 8=physical(skills,etc) 9=corruption
/*0x186*/   BYTE    TargetType;         //03=Group v1, 04=PB AE, 05=Single, 06=Self, 08=Targeted AE, 0e=Pet, 28=AE PC v2, 29=Group v2, 2a=Directional
/*0x187*/   BYTE    FizzleAdj;
/*0x188*/   BYTE    Skill;
/*0x189*/   BYTE    Location;           //01=Outdoors, 02=dungeons, ff=Any
/*0x18a*/   BYTE    Environment;
/*0x18b*/   BYTE    TimeOfDay;          // 0=any, 1=day only, 2=night only
/*0x18c*/   BYTE    CastingAnim;
/*0x18d*/   BYTE    AnimVariation;
/*0x18e*/   BYTE    TargetAnim;
/*0x18f*/   BYTE    TravelType;
/*0x190*/   BYTE    CancelOnSit;
/*0x191*/   BYTE    IsCountdownHeld;
/*0x192*/   CHAR    Name[0x40];
/*0x1d2*/   CHAR    Target[0x20];
/*0x1f2*/   CHAR    Extra[0x20];    //This is 'Extra' from Lucy (portal shortnames etc) official = NPC_FILENAME
/*0x212*/   CHAR    CastByMe[0x60];
/*0x272*/   CHAR    CastByOther[0x60];  //cast by other
/*0x2d2*/   CHAR    CastOnYou[0x60];
/*0x332*/   CHAR    CastOnAnother[0x60];
/*0x392*/   CHAR    WearOff[0x60];
/*0x3f2*/   BYTE    ShowWearOffMessage;
/*0x3f3*/   BYTE    NPCNoCast;
/*0x3f4*/   BYTE    SneakAttack;
/*0x3f5*/   BYTE    NotFocusable; //ignores all(?) focus effects
/*0x3f6*/   BYTE    NoDetrimentalSpellAggro;
/*0x3f7*/   BYTE    StacksWithSelf;
/*0x3f8*/   BYTE    NoBuffBlock;
/*0x3f9*/   BYTE    Scribable;
/*0x3fa*/   BYTE    NoStripOnDeath;
/*0x3fb*/   BYTE    NoRemove; // spell can't be clicked off?
/*0x3fc*/   DWORD   Unknown177; // new spell field valid range (0, 3], will set to 1 if not in that range (0, 1, 2)
/*0x400*/   DWORD   SpellRecourseType;
/*0x404*/   BYTE    Padding; //nothing here? I don't see it setting this at least
/*0x405*/   FLOAT   DistanceMod; // set to (DistanceModFarMult - DistanceModCloseMult) / (DistanceModFarDist - DistanceModCloseDist). Divisor has some bounds checking too
/*0x409*/
} SPELL, *PSPELL;

// actual size: 0x148 10-25-2006  ieatacid
typedef struct _SKILL {
/*0x000*/  PVOID  pUnknown0x0;       //_SKILL *pNext?
/*0x004*/  PVOID  pUnknown0x4;
/*0x008*/  DWORD  nName;
/*0x00c*/  DWORD  ReuseTimer;
/*0x010*/  DWORD  BaseDamage;
/*0x014*/  DWORD  SkillCombatType;   //0 means not a Combat Skill
/*0x018*/  DWORD  Unknown0x18;
/*0x01c*/  FLOAT  Force;
/*0x020*/  bool   Activated;
/*0x021*/  BYTE   LevelCappedSkill;
/*0x022*/  BYTE   Unknown0x22[0x2];
/*0x024*/  DWORD  MinLevel[0x24];
/*0x0b4*/  DWORD  Available[0x24];   //FF=not available for that class
/*0x144*/  DWORD  Unknown0x144;
/*0x148*/  
} SKILL, *PSKILL;

#define NUM_SKILLS 99
typedef struct _SKILLMGR {
/*0x000*/ struct _SKILL *pSkill[NUM_SKILLS];
/*0x004*/ //more data
} SKILLMGR, *PSKILLMGR;

//actual size 0x3a8 11-15-11  ieatacid
//actual size ? last checked by rlane187 may 19 2015
typedef struct _GUILDMEMBER {
/*0x000*/ struct  _GUILDMEMBER *pNext;
/*0x004*/ BYTE    Online;
/*0x005*/ BYTE    Unknown0x5[0x3];
/*0x008*/ WORD    ZoneID;
/*0x00a*/ WORD    Instance;
/*0x00C*/ BYTE	  Unknown0xC[0x6];
/*0x012*/ CHAR	  Name[0x40];
/*0x052*/ BYTE	  Unknown0x52[0x2];
/*0x054*/ DWORD	  Level;
/*0x058*/ DWORD   Flags; //1=banker, 2=alt
/*0x05c*/ DWORD   Class;
/*0x060*/ DWORD   Rank; //0=member 1=officer 2=leader

// not updated
#if 0
/*0x060*/ DWORD   LastSeen; //last seen timestamp
/*0x064*/ CHAR    PublicNote[0x100];//0x1a0
/*0x164*/ CHAR    PersonalNote[0x100];
/*0x264*/ DWORD   TributeStatus;
/*0x268*/ DWORD   TributeDonations;
/*0x26c*/ DWORD   LastDonation;//timestamp
/*0x270*/ DWORD   Unknown0x270;
/*0x274*/
#endif
} GUILDMEMBER, *PGUILDMEMBER;

typedef struct _GUILDDATA
{
/*0x00*/ char   Name[0x40];
/*0x04*/ DWORD  ID;
/*0x08*/
} GUILDDATA, *PGUILDDATA;

typedef struct _GUILD
{
/*0x00*/ struct _GUILDDATA *pGuildData;
/*0x04*/ DWORD  ID;
/*0x08*/ _GUILD *pNext;
/*0x0c*/ BYTE   Unknown0xc[0xc];
/*0x18*/
} GUILD, *PGUILD;

// 11-15-11 - ieatacid
// 2016 Mar 08 Test - eqmule (see 86DFB0) not sure on size needs more investigation
typedef struct _GUILDS {
/*0x0000*/ PVOID    pOneEntryVTable;
/*0x0004*/ BYTE     Unknown0x4[0x4];
/*0x0008*/ DWORD    GuildMemberCount;
/*0x000c*/ struct   _GUILDMEMBER *pMember;
/*0x0010*/ BYTE     Unknown0x10[0x65];
/*0x0075*/ CHAR     GuildMotD[0x200];
/*0x0275*/ CHAR     GuildLeader[0x40];
/*0x02b5*/ BYTE     Unknown0x2b5[0x3];
/*0x02b8*/ DWORD    GuildTribute;
/*0x02bc*/ BYTE     Unknown0x2bc[0x8dc5];
/*0x9081*/ CHAR     GuildUrl[0x200];
/*0x9281*/ CHAR     GuildChannelName[0x80];
/*0x9301*/ BYTE     Unknown0x9301[0x1b];
/*0x931C*/ struct _GUILD **GuildList;
/*0x9320*/ DWORD    HashValue;
/* more data */
} GUILDS, *PGUILDS;

typedef struct _INTERACTGROUNDITEM {
    DWORD DropID;
    DWORD SpawnID;
} INTERACTGROUNDITEM, *PINTERACTGROUNDITEM;

typedef struct _SPELLFAVORITE {
/*0x000*/   DWORD   SpellId[NUM_SPELL_GEMS];
/*0x030*/   CHAR    Name[0x19];
/*0x049*/   BYTE    inuse;
/*0x04a*/   BYTE    Byte_0x4a;
/*0x04b*/   BYTE    Byte_0x4b;
/*0x04c*/
} SPELLFAVORITE, *PSPELLFAVORITE;

typedef struct _CMDLIST {
    DWORD LocalizedStringID;
    PCHAR szName;
    PCHAR szLocalized;
    VOID  (__cdecl *fAddress)(PSPAWNINFO, PCHAR);
    DWORD Restriction;
    DWORD Category;
    DWORD Unknown;
} CMDLIST, *PCMDLIST;

typedef struct _EQSOCIAL {
/*0x0000*/   CHAR   Name[0x10];
/*0x0010*/   CHAR   Line[0x5][0x100];
/*0x0510*/   BYTE   Color; 
} EQSOCIAL, *PEQSOCIAL;

typedef struct _EQFRIENDSLIST {
/*0x0000*/ CHAR Name[0x64][0x40];
/*0x1900*/
} EQFRIENDSLIST, *PEQFRIENDSLIST;

// Size 0xa4    11/15/2011 ieatacid in msg_send_alt_data
// Size 0xa8    06/11/2014 eqmule in msg_send_alt_data
// Size 0xa8    See 4EF12F (msg_send_alt_data) in 2015-09-24 -eqmule
typedef struct _ALTABILITY {
/*0x00*/ DWORD Index;
/*0x04*/ BYTE Flags[4];					//[0] = enabled flag? everything 1, used to be a bool? is a bool in packet?
/*0x08*/ DWORD nShortName;
/*0x0c*/ DWORD nShorterName;
/*0x10*/ DWORD nName;					// now a database number
/*0x14*/ DWORD nDesc;					// now a database number
/*0x18*/ DWORD MinLevel;
/*0x1c*/ DWORD Cost;					//Initial Cost or cost the last time you bought a level of it
/*0x20*/ DWORD ID;						//ID of the AA group (/alt activate id)
/*0x24*/ DWORD CurrentRank;				// the current rank of this AA first rank is 1 etc
/*0x28*/ DWORD RequirementCount;		//how many requirements does it have its always 1 even if its none
/*0x2c*/ DWORD *RequiresAbility;		// array of prereq ID;
/*0x30*/ DWORD Unknown0x30[2];
/*0x38*/ DWORD prereq_count2;			// count of next array, which contains rank required
/*0x3c*/ DWORD *RequiresAbilityPoints;
/*0x40*/ DWORD Unknown0x40;
/*0x44*/ DWORD pointer;
/*0x48*/ DWORD Type;					// 1 General 2 Archetype 3 Class 4 special 5 focus
/*0x4c*/ LONG  SpellID;					// -1 for no Spell
/*0x50*/ DWORD Unknown0x50;
/*0x54*/ DWORD Unknown0x54;				// this uses the same class as prereqs, so count?
/*0x58*/ DWORD *reuse_id; 
/*0x5c*/ BYTE  Unknown0x5c[0x8];
/*0x64*/ DWORD ReuseTimer;				// in seconds
/*0x68*/ DWORD Classes;					// Classes/2 is the actual value we want.
/*0x6c*/ DWORD MaxRank;					//so like x/25, this is the 25
union {									//If you have not spent points in this 
/*0x70*/ DWORD PointsSpent;				//ability, then its PointsToBeSpent (or 
/*0x70*/ DWORD PointsToBeSpent;			//'Cost', in other words).
};
/*0x74*/ DWORD last_id;					// -1 if none, although sometimes it can be -1 when there is ...
/*0x78*/ DWORD next_id;					// ID of the next rank
/*0x7C*/ BYTE grant_only;				// vet AA, quest AA
/*0x7D*/ BYTE  Unknown0x7d[0x3];
/*0x80*/ DWORD max_charges;				// charges on expendable AAs
/*0x84*/ BYTE Unknown0x84[0x4];
/*0x88*/ DWORD Expansion;
/*0x8c*/ DWORD special_category;		// 7 is expendable, -1 none
/*0x90*/ BYTE shroud;
/*0x91*/ BYTE unknown0x91;
/*0x92*/ BYTE loh;						// 1 for lay on hands only. yep.
/*0x93*/ BYTE Autogrant;				// 1 if auto grant is enabled
/*0x94*/ DWORD autogrant_expasnion;		// Usually the same as normal expansion if enabled
/*0x98*/ DWORD effects_count;			// Count of spell effects for AA
/*0x9c*/ DWORD **effects;				// this is repeated a few times some times
/*0xA0*/ BYTE Unknown0xA0[0x8];
/*0xa8*/
} ALTABILITY, *PALTABILITY;

typedef struct _ALTABILITIESLISTMGR {
/*0x00*/ struct _ALTABILITY* Ability;
/*0x04*/ DWORD Index;
} ALTABILITIESLISTMGR, *PALTABILITIESLISTMGR;

//NUM_ALT_ABILITIES is now defined before CHARINFO definition in this same header file.
typedef struct _ALTABILITIESLIST {
/*0x00*/ struct _ALTABILITIESLISTMGR* Abilities[NUM_ALT_ABILITIES_ARRAY];
} ALTABILITIESLIST, *PALTABILITIESLIST;

typedef struct _NEWALTADVMGR {
/*0x00*/ struct _ALTABILITIESLIST* AltAbilityList;
/*0x04*/ DWORD NumAltAbilities;  // NUM_ALT_ABILITIES
/*0x08*/ DWORD Unknown0x08; // data here
/*0x0c*/ DWORD Unknown0x0c; // data here
/*0x10*/ BYTE  Unknown0x10[0x8];
} NEWALTADVMGR, *PNEWALTADVMGR;

typedef struct _ALTADVMGR {
/*0x00*/ struct _NEWALTADVMGR* AltAbilities;
} ALTADVMGR, *PALTADVMGR;

typedef struct _MERCAADATA {
/*0x00*/ DWORD nName;//I would guess we can find aapoints spent on the ability in this struct as well
} MERCAADATA,*PMERCAADATA;//but I dont know yet, I dont have a mercenary with aa yet... -eqmule

typedef struct _MERCAA {
/*0x00*/ DWORD Unknown0x00;
/*0x04*/ DWORD Unknown0x04;
/*0x08*/ struct _MERCAADATA *Ptr;
/*0x0c*/ DWORD Unknown0x00c;
/*0x10*/ DWORD Max;//how many AA can be spent on this ability
} MERCAA, *PMERCAA;

//pinstMercAltAbilities_x
//MercAltAbilities__MercAltAbilities
//Actual Size: 0x478 in eqgame dated oct 04 2013 (see 4A96D4) - eqmule 
typedef struct _EQMERCALTABILITIES {
/*0x000*/ BYTE Unknown0x000[0x408];
/*0x408*/ PMERCAA MercAAInfo[0xc];//12 pointers since there are currently only 12 mercenary aa's
/*0x438*/ BYTE Unknown0x438[0x40];
/*0x478*/
} EQMERCALTABILITIES, *PEQMERCALTABILITIES;

// size 0x98 (3-12-2014) -eqmule
// size 0x9c 3-18-2015 test see (49A077) -eqmule
typedef struct _EQRAIDMEMBER { 
/*0x000*/ CHAR      Name[0x40]; 
/*0x040*/ CHAR      RaidNote[0x40]; 
/*0x080*/ DWORD     nLevel;
/*0x084*/ DWORD     nClass; 
/*0x088*/ BYTE      RaidLeader; 
/*0x089*/ BYTE      GroupLeader; 
/*0x08a*/ BYTE      RaidMainAssist;
/*0x08b*/ BYTE      RaidMarker;
/*0x08c*/ DWORD     MasterLooter;
/*0x090*/ DWORD     GroupNumber;
/*0x094*/ BYTE      Unknown0x94[0x8];//i guess new master looter is in here...
/*0x09c*/ 
} EQRAIDMEMBER, *PEQRAIDMEMBER;

// sizeof(_EQRAID) is 0x3668 (12-09-2009)
//instCRaid_x
// push    13C6h
//mar 18 2015 Test CRaid__ResetRaid eqgame.exe - eqmule
//as for the size... I have no idea...
//maybe 3544h? see 48055F                 mov     [esi+3544h], bl (jun 11 2014) -eqmule
//392C in mar 18 205 test? not sure...
typedef struct _EQRAID {
/*0x0000*/ BYTE     Unknown0x0000[0xe0];
/*0x00e0*/ CHAR     RaidMemberUsed[0x48];
/*0x0128*/ struct   _EQRAIDMEMBER RaidMember[0x48];
/*0x2d08*/ BYTE     Unknown0x2d08[0x4];
/*0x2d0c*/ DWORD    RaidMemberCount;
/*0x2d10*/ CHAR     RaidLeaderName[0x40];
/*0x2d50*/ CHAR     RaidMOTD[0x400];
/*0x3150*/ BYTE     Unknown0x3150[0x40];
/*0x3190*/ BYTE     Invited; // 1 = default?, 2 = invited, 4 = in raid
/*0x3191*/ BYTE     Unknown0x3191[0x8];
/*0x3199*/ BYTE     IsRaidLeader;
/*0x319a*/ BYTE     Unknown0x0x319a[0x2];
/*0x319c*/ DWORD    RaidTarget;
/*0x31a0*/ DWORD    LootType;
/*0x31a4*/ CHAR     RaidLooters[0x13][0x40];
/*0x3664*/ DWORD    TotalRaidMemberLevels; // TotalRaidMemberLevels/RaidMemberCount=RaidAvgLevel
/*0x3668*/ BYTE     Locked;
/*0x3669*/ BYTE     Unknown0x3669[0x7];
/*0x3670*/ // <- im sure this is not right but whatever... we got what we came for...
} EQRAID, *PEQRAID;

// size 0x19C 3-23-2005
typedef struct _EQGROUP {
/*0x000*/ BYTE MemberExists[5];
/*0x005*/ CHAR MemberName[5][0x40];
/*0x145*/ BYTE Unused[3];
/*0x148*/ struct _SPAWNINFO* pMember[5];
/*0x15C*/ CHAR LeaderName[0x40];
/*0x19C*/
} EQGROUP, *PEQGROUP;

// size 0x08
typedef struct _EQSTRING {
/*0x00*/    DWORD ID;
/*0x04*/    PCHAR String;
} EQSTRING, *PEQSTRING;

// size 0x10 4-28-2004 lax
typedef struct _EQSTRINGTABLE {
/*0x00*/ struct _EQSTRING **StringItems;
/*0x04*/ DWORD Size;
/*0x08*/ DWORD Count;
/*0x0c*/ DWORD Unknown0x0c;
/*0x10*/
} EQSTRINGTABLE, *PEQSTRINGTABLE;

//updated by eqmule
//see 7B000C in eqgame.exe dated jul 16 2014
//not sure about size...
typedef struct connection_t {
/*0x000*/ void  *vtable;
/*0x004*/ BYTE  Unknown0x4[0x110];
/*0x114*/ DWORD Master;
/*0x118*/ DWORD Average;
/*0x11c*/ DWORD Low;
/*0x120*/ DWORD High;
/*0x124*/ DWORD Last;
/*0x128*/
} CONNECTION_T, *PCONNECTION_T;

//actual size 0x2dfc 3-19-09 - ieatacid 
typedef struct _CDISPLAY {
/*0x0000*/ BYTE   Unknown0x000[0x12c];
/*0x012c*/ void   *pActorTagManager;
/*0x0130*/ BYTE   Unknown0x130[0x24];
/*0x0154*/ DWORD  TimeStamp;
/*0x0158*/ BYTE   Unknown0x158[0x2c12];
/*0x2d6a*/ BYTE   NpcNames; // show npc names
} CDISPLAY, *PCDISPLAY;

//5-16-06 - ieatacid
typedef struct _DZTIMERINFO {
/*0x000*/ CHAR   ExpeditionName[0x80];
/*0x080*/ CHAR   EventName[0x100];
/*0x180*/ DWORD  TimeStamp;  // TimeStamp - Util__FastTime = time left
/*0x184*/ DWORD  TimerID;
/*0x188*/ struct _DZTIMERINFO *pNext;
/*0x18c*/
} DZTIMERINFO, *PDZTIMERINFO;

typedef struct _DZMEMBER {
/*0x000*/ CHAR   Name[0x40];
/*0x040*/ DWORD  Status;  // 0="unknown", 1="Online", 2="Offline", 3="In Dynamic Zone", 4="Link Dead"
/*0x044*/ struct _DZMEMBER *pNext;
/*0x048*/
} DZMEMBER, *PDZMEMBER;

typedef struct _TASKMEMBER {
/*0x000*/ CHAR   Name[0x40];
/*0x040*/ DWORD  Unknown0x40;
/*0x044*/ DWORD  IsLeader;
/*0x048*/ struct _TASKMEMBER *pNext;
/*0x04c*/
} TASKMEMBER, *PTASKMEMBER;

typedef struct _DYNAMICZONE {
/*0x000*/ void   *vftable;
/*0x004*/ BYTE   Unknown0x04[0x46];
/*0x04a*/ CHAR   Name[0x40]; // Leaders name
/*0x08a*/ CHAR   ExpeditionName[0x80];
/*0x10a*/ BYTE   Unknown0x10a[0x2];
/*0x10c*/ WORD   MaxPlayers;
/*0x10e*/ BYTE   Unknown0x10e[0x2];
/*0x110*/ struct _DZMEMBER *pMemberList;
/*0x114*/ PCHAR  expeditionName;
/*0x118*/ // more?
} DYNAMICZONE, *PDYNAMICZONE;

typedef struct _CHATCHANNELS {
/*0x000*/ PCHAR  ChannelName[0xa];
/*0x004*/
} CHATCHANNELS, *PCHATCHANNELS;

typedef struct _CHATSERVICE {
/*0x000*/ BYTE   Unknown0x0[0xc];
/*0x00c*/ struct _CHATCHANNELS *ChannelList;
/*0x010*/ DWORD  ActiveChannels;   // number of channels joined
/*0x014*/ BYTE   Unknown0x14[0x8];
/*0x01c*/ CHAR   ChatID[0x30];     // "ServerName.CharName" (0x60?)
/*0x04c*/ BYTE   Unknown0x4c[0x30];
/*0x07c*/ CHAR   ServerName[0x30]; // "ServerName."
/*0x0b0*/ // more data
} CHATSERVICE, *PCHATSERVICE;

typedef struct _EVERQUEST {
	/*0x000*/ BYTE   Unknown[0x2a4];
	/*0x2a4*/ struct _CHATSERVICE *ChatService;
	/*0x2a8*/ BYTE   Unknown0x2a8[0x8];
	/*0x2b0*/ bool   bJoinedChannel;
	/*0x2b1*/ CHAR   ChannelPlayerName[0x100];
	/*0x3b1*/ CHAR   ChannelName[0xa][0x30];
	/*0x591*/ BYTE   Unknown0x591[0x3];
	/*0x594*/ DWORD  ChannelNumber[0xa];
	/*0x5bc*/ DWORD  ChannelQty;
	/*0x5c0*/ DWORD  TargetRing;
	/*0x5c4*/ DWORD	 WorldState;//0 everything is fine, 1 we are getting disconnected 2 player not released from zone
	/*0x5c8*/ DWORD  GameState;
	/*0x5cc*/ // more data
} EVERQUEST, *PEVERQUEST;

typedef struct _AURAINFO {
/*0x000*/ CHAR    Name[0x40];
/*0x040*/ BYTE    Unknown0x14[0xc];
/*0x04c*/
} AURAINFO, *PAURAINFO;

typedef struct _AURAS {
/*0x000*/ _AURAINFO Aura[0x2];
} AURAS, *PAURAS;

typedef struct _AURAMGR {
/*0x000*/ DWORD   NumAuras;
/*0x004*/ BYTE    Unknown0x4[0xc];
/*0x010*/ _AURAS  **pAuraInfo;
/*0x014*/ BYTE    Unknown0x14[0x8];
/*0x01c*/
} AURAMGR, *PAURAMGR;

typedef struct _INTERACTSWITCH {
/*0x000*/ DWORD   switchID;
/*0x004*/ DWORD   dwzero;
/*0x008*/ DWORD   dwneg1;
/*0x00c*/ DWORD   spawnID;
} INTERACTSWITCH, *PINTERACTSWITCH;

typedef struct _MERCSTANCEDATA {
DWORD nStance;
DWORD nDbStance;
} MERCSTANCEDATA, *PMERCSTANCEDATA;

typedef struct _MERCSINFO {
/*0x00*/ DWORD Unknown0x00;
/*0x04*/ DWORD nMercCategory;
/*0x08*/ DWORD nMercDesc;
/*0x0c*/ DWORD Purchase; //in copper...
/*0x10*/ DWORD Upkeep; //in copper...
/*0x14*/ BYTE Unknown0x14[0x2c];
/*0x40*/ CHAR Name[0xC];
/*0x4c*/ BYTE Unknown0x4c[0x88];
/*0xD4*/
} MERCSINFO, *PMERCSINFO;
//Size 0xD4 in eqgame.exe dated 01 22 2015 -eqmule
typedef struct _MERCSLIST {
/*0x00*/ MERCSINFO mercinfo[7];//is 7 max, even with slots u can buy for sc?
} MERCSLIST, *PMERCSLIST;

//Actual Size: 0x2fc (See 57117F in eqgame dated dec 10 2013) - eqmule
//CMercenaryInfo__CMercenaryInfo
typedef struct _MERCENARYINFO {
/*0x000*/ BYTE Unknown0x0[0x110];
/*0x110*/ DWORD HaveMerc;
/*0x114*/ DWORD MercState; // 1 = suspended, 5 = active
/*0x118*/ BYTE  Unknown0x118[0x30];
/*0x148*/ DWORD ActiveStance;
/*0x14c*/ BYTE  Unknown0x14c[0x10];
/*0x15c*/ CHAR	MercName[0x18];
/*0x174*/ BYTE  Unknown0x174[0x7c];
/*0x1F0*/ DWORD MercenaryCount;//how many mercenaries we have
/*0x1F4*/ PMERCSLIST pMercsList; 
/*0x1F8*/ BYTE  Unknown0x1f4[0xc];
/*0x204*/ DWORD MaxMercsCount;//max you can have
/*0x208*/ BYTE  Unknown0x208[0x10];
/*0x218*/ DWORD CurrentMercIndex;
/*0x21c*/ BYTE  Unknown0x21c[0x8];
/*0x224*/ DWORD MercSpawnId;//yes its the spawnID of the mercenary
/*0x228*/ BYTE  Unknown0x228[0x30];
/*0x258*/ DWORD NumStances;
/*0x25c*/ _MERCSTANCEDATA **pMercStanceData;
/*0x260*/ BYTE  Unknown0x25c[0x9c];
/*0x2Fc*/
} MERCENARYINFO, *PMERCENARYINFO;

typedef struct _MERCENARYSTATS {
/*0x000*/ DWORD MaxHP; 
/*0x004*/ DWORD CurrHP; 
/*0x008*/ DWORD MaxMana; 
/*0x00c*/ DWORD CurrMana; 
/*0x010*/ DWORD MaxEndurance; 
/*0x014*/ DWORD CurrEndurance; 
/*0x018*/ DWORD AC; 
/*0x01c*/ DWORD Attack; 
/*0x020*/ DWORD Haste; 
/*0x024*/ DWORD STR; 
/*0x028*/ DWORD STA; 
/*0x02c*/ DWORD INT; 
/*0x030*/ DWORD WIS; 
/*0x034*/ DWORD AGI; 
/*0x038*/ DWORD DEX; 
/*0x03c*/ DWORD CHA; 
/*0x040*/ DWORD CombatHPRegen; 
/*0x044*/ DWORD CombatManaRegen; 
/*0x048*/ DWORD CombatEnduranceRegen; 
/*0x04c*/ DWORD HealAmount; 
/*0x050*/ DWORD SpellDamage; 
/*0x054*/ 
} MERCENARYSTATS, *PMERCENARYSTATS;

#define MAX_XTARGETS 20

enum xTargetTypes
{
    XTARGET_EMPTY_TARGET,
    XTARGET_AUTO_HATER,
    XTARGET_SPECIFIC_PC,
    XTARGET_SPECIFIC_NPC,
    XTARGET_TARGETS_TARGET,
    XTARGET_GROUP_TANK,
    XTARGET_GROUP_TANKS_TARGET,
    XTARGET_GROUP_ASSIST,
    XTARGET_GROUP_ASSIST_TARGET,
    XTARGET_GROUP_PULLER,
    XTARGET_GROUP_PULLER_TARGET,
    XTARGET_GROUP_MARK1,
    XTARGET_GROUP_MARK2,
    XTARGET_GROUP_MARK3,
    XTARGET_RAID_ASSIST1,
    XTARGET_RAID_ASSIST2,
    XTARGET_RAID_ASSIST3,
    XTARGET_RAID_ASSIST1_TARGET,
    XTARGET_RAID_ASSIST2_TARGET,
    XTARGET_RAID_ASSIST3_TARGET,
    XTARGET_RAID_MARK1,
    XTARGET_RAID_MARK2,
    XTARGET_RAID_MARK3,
    XTARGET_MY_PET,
    XTARGET_MY_PET_TARGET,
    XTARGET_MY_MERCENARY,
    XTARGET_MY_MERCENTARY_TARGET
};

// size 0x4c 12-25-09 - ieatacid
typedef struct _XTARGETDATA
{
/*0x00*/ DWORD  xTargetType;
/*0x04*/ DWORD  Unknown0x4;
/*0x08*/ DWORD  SpawnID;
/*0x0c*/ char   Name[0x40];
/*0x4c*/
} XTARGETDATA, *PXTARGETDATA;

typedef struct _XTARGETARRAY
{
    XTARGETDATA pXTargetData[MAX_XTARGETS];
} XTARGETARRAY, *PXTARGETARRAY;

// size 0x20 12-25-09 - ieatacid
typedef struct _XTARGETMGR
{
/*0x00*/ void  *vftable;
/*0x04*/ DWORD TargetSlots; // MAX_XTARGETS
/*0x08*/ PXTARGETARRAY pXTargetArray;
/*0x0c*/ DWORD Unknown0xc;  // same as TargetSlots?
/*0x10*/ BYTE  Unknown0x10[0x4];
/*0x14*/ BYTE  AutoAddHaters; // 1 = auto add haters, 0 = do not auto add haters
/*0x15*/ BYTE  Unknown0x15[0x3];
/*0x18*/ BYTE  Unknown0x18[0x4];
/*0x1c*/ BYTE  Unknown0x1c[0x4];
/*0x20*/
} XTARGETMGR, *PXTARGETMGR;

typedef struct _AGGRODATA {
/*0x00*/ DWORD Unknown0x0;
/*0x04*/ BYTE  AggroPct;
/*0x05*/ BYTE  padding[3];
/*0x08*/
} AGGRODATA, *PAGGRODATA;

// size 0xe4 11-28-12 - ieatacid (in GetAggroInfo)
// size 0xfc see 422F94 in 20 Aug 2015 -eqmule
typedef struct _AGGROINFO {
/*0x00*/ struct _AGGRODATA aggroData[0x1e];
/*0xf0*/ DWORD  AggroLockID;//this can be 0, I dont know what it is... -eqmule
/*0xf4*/ DWORD  AggroTargetID;//this is id of whoever we are fighting -eqmule
/*0xf8*/ DWORD  AggroSecondaryID;//this is id of whoever the npc is fighting -eqmule
/*0xfc*/
} AGGROINFO, *PAGGROINFO;

enum AggroDataTypes
{
    AD_Player,
    AD_Secondary,
    AD_Group1,
    AD_Group2,
    AD_Group3,
    AD_Group4,
    AD_Group5,
    AD_xTarget1,
    AD_xTarget2,
    AD_xTarget3,
    AD_xTarget4,
    AD_xTarget5,
    AD_xTarget6,
    AD_xTarget7,
    AD_xTarget8,
    AD_xTarget9,
    AD_xTarget10,
    AD_xTarget11,
    AD_xTarget12,
    AD_xTarget13,
    AD_xTarget14,
    AD_xTarget15,
    AD_xTarget16,
    AD_xTarget17,
    AD_xTarget18,
    AD_xTarget19,
    AD_xTarget20,
};
typedef struct _GROUPAGGRO {
/*0x00*/ DWORD Unknown0x00;
/*0x04*/ DWORD Unknown0x04;
/*0x08*/ DWORD  GroupMemberAggro[6];//player is ALWAYS the 6th member...
} GROUPAGGRO, *PGROUPAGGRO;

#define EQ_ASSIST_CALC                  0x020c0f19
#define EQ_ASSIST_COMPLETE              0x10ef   // aMsg_time_stamp
#define EQ_ASSIST                       0x1B65   // do_assist(PlayerClient *,char const *)+399 20160212 live (see 52C319)
#define EQ_BEGIN_ZONE                   0x668D   // CEverQuest__SavePCForce				
#define EQ_END_ZONE                     0x5CED   // CEverQuest__DoMainLoop+B2F			
#define EQ_LoadingS__ArraySize          0x5a     // EQ_LoadingS__SetProgressBar_x+76 	(4C7396 yes it says 5b there, but we dont want to overwrite the NULL term...	2016 Apr 21
};
using namespace EQData;
