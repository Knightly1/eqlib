/*
 * MacroQuest: The extension platform for EverQuest
 * Copyright (C) 2002-2022 MacroQuest Authors
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

#include "Common.h"
#include "CXStr.h"
#include "EQData.h"
#include "GraphicsEngine.h"
#include "Items.h"
#include "Spells.h"

// The Profile class hierarchy (PcProfile and BaseProfile) represent the
// "profile" or stats and belongings of a character. Profiles are things that
// can be swapped out at runtime for things like monster missions (shrouds).
//
// This used to be called CHARINFO2.
// CHARINFO2
//   PcProfile -> BaseProfile

namespace eqlib {

class BaseProfile;
class PcProfile;

//============================================================================
// ProfileManager
//============================================================================

enum eProfileListType
{
	eProfileTypeNormal = 0,
	eProfileTypeMonsterMission,
};

enum eProfileType
{
	eProfileTypeMain = 0,
	eProfileTypeAlt,
	eProfileTypeMonster,
	eProfileTypeOther
};

// Two-dimensional doubly-linked-list of profiles. Profiles are
// grouped by type in the ProfileList, and then multiple profiles
// of the same type are linked together.

class [[offsetcomments]] ProfileList
{
public:
/*0x00*/ eProfileListType ListType;
/*0x04*/ BaseProfile* pFirst;
/*0x08*/ BaseProfile* pLast;
/*0x0c*/ ProfileList* pNext;
/*0x10*/ ProfileList* pPrev;
/*0x14*/
};

// Manages the list of profiles. Primarily used for accessing the
// current profile.
class [[offsetcomments]] ProfileManager
{
public:
	const ProfileList* GetCurrentProfileList() const
	{
		ProfileList* pWalk = pFirst;
		while (pWalk != nullptr)
		{
			if (pWalk->ListType == CurProfileList)
			{
				return pWalk;
			}

			pWalk = pWalk->pNext;
		}
		return nullptr;
	}

	BaseProfile* GetCurrentProfile()
	{
		const ProfileList* pList = GetCurrentProfileList();
		if (pList != nullptr)
		{
			return pList->pFirst;
		}
		return nullptr;
	}

	const BaseProfile* GetCurrentProfile() const
	{
		const ProfileList* pList = GetCurrentProfileList();
		if (pList != nullptr)
		{
			return pList->pFirst;
		}
		return nullptr;
	}

private:
/*0x00*/ ProfileList* pFirst;
/*0x04*/ eProfileListType CurProfileList;
/*0x08*/
};

//============================================================================
// BaseProfile
//============================================================================

class [[offsetcomments]] BaseProfile
{
public:
	virtual ~BaseProfile() {}
	// other virtual methods are not mapped out

/*0x0000*/ // vftable
/*0x0008*/ BaseProfile*                          nextProfile;
/*0x000c*/ BaseProfile*                          prevProfile;
/*0x0010*/ eProfileListType                      profileListType;
/*0x0014*/ ItemContainer                         InventoryContainer;
/*0x0030*/ ItemContainer                         TributeBenefitItems;
/*0x004c*/ ItemContainer                         TrophyTributeBenefitItems;
/*0x0068*/ EQ_Affect                             Buffs[NUM_LONG_BUFFS + NUM_SHORT_BUFFS];
/*0x1980*/ int                                   SpellBook[NUM_BOOK_SLOTS];
/*0x2b00*/ int                                   MemorizedSpells[MAX_MEMORIZED_SPELLS];
/*0x2b48*/ int                                   Skill[NUM_SKILLS];
/*0x2cd8*/ int                                   InnateSkill[NUM_INNATE];
/*0x2d3c*/ ArmorProperties                       ArmorProps[9];
/*0x2df0*/ uint32_t                              CharacterTint[9];
/*0x2e14*/ int8_t                                Gender;
/*0x2e18*/ int                                   Race;
/*0x2e1c*/ int                                   Class;
/*0x2e20*/ CharacterPropertyHash                 properties;
/*0x2e30*/ int                                   Level;
/*0x2e34*/ int                                   Mana;
/*0x2e38*/ int                                   Endurance;
/*0x2e40*/ int64_t                               BaseHP;
/*0x2e48*/ int                                   BaseSTR;
/*0x2e4c*/ int                                   BaseSTA;
/*0x2e50*/ int                                   BaseCHA;
/*0x2e54*/ int                                   BaseDEX;
/*0x2e58*/ int                                   BaseINT;
/*0x2e5c*/ int                                   BaseAGI;
/*0x2e60*/ int                                   BaseWIS;
/*0x2e64*/ int8_t                                Face;
/*0x2e68*/ int                                   Plat;
/*0x2e6c*/ int                                   Gold;
/*0x2e70*/ int                                   Silver;
/*0x2e74*/ int                                   Copper;
/*0x2e78*/ int                                   CursorPlat;
/*0x2e7c*/ int                                   CursorGold;
/*0x2e80*/ int                                   CursorSilver;
/*0x2e84*/ int                                   CursorCopper;
/*0x2e88*/ int                                   _max_allowed_spell_slots;
/*0x2e8c*/ int                                   practices;
/*0x2e90*/ int                                   height;
/*0x2e94*/ int                                   width;
/*0x2e98*/ int                                   length;
/*0x2e9c*/ int                                   view_height;
/*0x2ea0*/ char                                  texture_type;
/*0x2ea1*/ char                                  m_armorMat;
/*0x2ea2*/ char                                  m_armorVariation;
/*0x2ea3*/ char                                  headType;
/*0x2ea4*/ int                                   DisciplineTimer;
/*0x2ea8*/ uint32_t                              MendTimer;
/*0x2eac*/ int                                   ForageTimer;
/*0x2eb0*/ int                                   thirstlevel;
/*0x2eb4*/ int                                   hungerlevel;
/*0x2eb8*/ eProfileType                          profileType;
/*0x2ebc*/ int                                   Shrouded;                               // templateId
/*0x2ec0*/ int                                   systemId;
/*0x2ec4*/ int                                   designId;
/*0x2ec8*/ int                                   InventorySlotBitmask;
/*0x2ecc*/ uint32_t                              CurrentProgressionID;
/*0x2ed0*/ uint8_t                               Unknown0x3c28[0x58];
/*0x2f28*/ int                                   ParentId;
/*0x2f2c*/ int                                   TattooIndex;
/*0x2f30*/ int                                   FacialAttachmentIndex;
/*0x2f34*/ //BaseProfile

	// This expects parameter of type eInventorySlot
	inline ItemPtr GetInventorySlot(int invSlot) const { return InventoryContainer.GetItem(invSlot); }
	inline const ItemContainer& GetInventory() const { return InventoryContainer; }
	inline ItemContainer& GetInventory() { return InventoryContainer; }

	inline ItemIndex CreateItemIndex(int slot0, int slot1 = -1, int slot2 = -1) const { return InventoryContainer.CreateItemIndex(slot0, slot1, slot2); }
	inline ItemGlobalIndex CreateItemGlobalIndex(int slot0, int slot1 = -1, int slot2 = -1) const { return InventoryContainer.CreateItemGlobalIndex(eItemContainerPossessions, slot0, slot1, slot2); }
	inline ItemPtr GetItemPossession(const ItemIndex& index) const { return InventoryContainer.GetItem(index); }
	inline ItemContainer& GetItemPosessions() { return InventoryContainer; }

	inline int GetMemorizedSpell(int index) const { return MemorizedSpells[index]; }

	int GetRace() const { return Race; }
	int GetClass() const { return Class; }

	// Can be used to access both short and long buffs
	const EQ_Affect& GetEffect(uint32_t index) const
	{
		if ((int)index >= NUM_LONG_BUFFS + NUM_SHORT_BUFFS)
			return Buffs[0];

		return Buffs[index];
	}
	EQ_Affect& GetEffect(uint32_t index) { return const_cast<EQ_Affect&>(const_cast<const BaseProfile*>(this)->GetEffect(index)); }

	const EQ_Affect& GetTempEffect(uint32_t index) const { return GetEffect(index + NUM_LONG_BUFFS); }
	EQ_Affect& GetTempEffect(uint32_t index) { return GetEffect(index + NUM_LONG_BUFFS); }

	int GetMaxEffects() const { return NUM_LONG_BUFFS + NUM_SHORT_BUFFS; }

	// Buffs array was converted to a dynamic array on 2022-04-14. Instead of relying on the memory layout of the buffs,
	// plugin authors should instead call GetEffect, GetTempEffect, and GetMaxEffects() as necessary.r

	// EQ_Affect Buff[NUM_LONG_BUFFS];
	DEPRECATE("Use GetEffect(index) instead of directly accessing member variable Buff[index]")
		EQ_Affect(&getter_Buff() const)[NUM_LONG_BUFFS] { return (*(EQ_Affect(*)[NUM_LONG_BUFFS])(&Buffs[0])); }
		__declspec(property(get = getter_Buff)) const EQ_Affect(&Buff)[NUM_LONG_BUFFS];

	// EQ_Affect ShortBuff[NUM_SHORT_BUFFS];
	DEPRECATE("Use GetTempEffect(index) instead of directly accessing member variable ShortBuff[index]")
		EQ_Affect(&getter_ShortBuff() const)[NUM_SHORT_BUFFS] { return (*(EQ_Affect(*)[NUM_SHORT_BUFFS])(&Buffs[NUM_LONG_BUFFS])); }
		__declspec(property(get = getter_ShortBuff)) const EQ_Affect(&ShortBuff)[NUM_SHORT_BUFFS];

	// INVENTORYARRAY* pInventoryArray
	DEPRECATE("Use GetInventorySlot(slot) instead directly accessing member variable pInventoryrArray");
	INVENTORYARRAY* getter_pInventoryArray() { return reinterpret_cast<INVENTORYARRAY*>(&InventoryContainer.Items[0]); }
	__declspec(property(get = getter_pInventoryArray)) INVENTORYARRAY* pInventoryArray;
};

//============================================================================
// PcProfile Data
//============================================================================

struct [[offsetcomments]] WorldLocation
{
/*0x00*/ uint32_t     ZoneBoundID;
/*0x04*/ float        ZoneBoundY;
/*0x08*/ float        ZoneBoundX;
/*0x0c*/ float        ZoneBoundZ;
/*0x10*/ float        ZoneBoundHeading;
/*0x14*/
};

struct [[offsetcomments]] AbilityInfo
{
/*0x00*/ int          AAIndex;
/*0x04*/ int          PointsSpent;
/*0x08*/ int          ChargeSpent;            // charges spent in the last 10 min?
/*0x0c*/
};

inline namespace deprecated {
	using PAALIST DEPRECATE("Use AALIST instead of PAALIST") = AbilityInfo*;
	using AALIST DEPRECATE("Use AbilityInfo instead of AALIST") = AbilityInfo;
}

struct [[offsetcomments]] BandolierItemInfo
{
/*0x00*/ int                 ItemID;
/*0x04*/ int                 IconID;
/*0x08*/ char                Name[EQ_MAX_NAME];
/*0x48*/
};

struct [[offsetcomments]] BandolierSet
{
/*0x000*/ char               Name[32];
/*0x020*/ BandolierItemInfo  Items[MAX_BANDOLIER_SLOTS];
/*0x140*/
};

struct [[offsetcomments]] CombatAbilityTimer : public TListNode<CombatAbilityTimer>
{
/*0x0c*/ int32_t  SpellGroup;
/*0x10*/ uint32_t ExpireTimer;
/*0x14*/
};

struct [[offsetcomments]] AssociatedNPCSaveStringNode
{
/*0x0000*/ char              SaveString[0x2000];              // 0x1000 in older clients
/*0x2000*/ AssociatedNPCSaveStringNode* pNext;
/*0x2004*/
};

// Struct not mapped yet
struct PetObjectData;

//============================================================================
// PcProfile
//============================================================================

// @sizeof(PcProfile) == 0x6a28 :: 2022-06-13 (live) @ 0x1405916d4
constexpr size_t PcProfile_size = 0x6a28;

class [[offsetcomments]] PcProfile : public BaseProfile
{
	FORCE_SYMBOLS;

public:
/*0x2f38*/ WorldLocation                         BoundLocations[5];
/*0x2f9c*/ ArmorProperties                       ArmorType[22];
/*0x3154*/ AbilityInfo                           AAList[AA_CHAR_MAX_REAL];                         // AlternateAbilities
/*0x3f64*/ uint32_t                              BodyColor[9];
/*0x3f88*/ int                                   FactionTable[2048];
/*0x5f88*/ int                                   CombatAbilities[NUM_COMBAT_ABILITIES];            // KnownCombatAbilities
/*0x6438*/ uint32_t                              SpellRecastTimer[15];
/*0x6474*/ uint32_t                              CombatAbilityTimers[25];
/*0x64d8*/ TList<CombatAbilityTimer>             CombatAbilityTimersList;
/*0x64e0*/ uint32_t                              LinkedSpellTimers[25];                            // we used to call this CombatAbilityTimes
/*0x6544*/ uint32_t                              ItemRecastTimers[100];
/*0x66d4*/ uint32_t                              AATimers[100];
/*0x6864*/ BandolierSet                          Bandolier[MAX_BANDOLIER_ITEMS];
/*0x8164*/ BenefitSelection                      ActiveTributeBenefits[5];
/*0x818c*/ BenefitSelection                      ActiveTrophyTributeBenefits[10];
/*0x81dc*/ ItemContainer                         GuildTributeBenefitItems;
/*0x81f8*/ ItemContainer                         GuildTrophyTributeBenefitItems;
/*0x8214*/ ArrayClass<CXStr>                     MercenarySaveStrings;
/*0x8224*/ AssociatedNPCSaveStringNode*          PetSaveString;
/*0x8228*/ int                                   Deity;
/*0x822c*/ bool                                  bPVPFlag;
/*0x822d*/ uint8_t                               HighestLevel;
/*0x8230*/ int                                   Drunkenness;                            // inebriation
/*0x8234*/ uint8_t                               HairColor;
/*0x8235*/ uint8_t                               BeardColor;
/*0x8238*/ int                                   NpcTintIndex;
/*0x823c*/ uint8_t                               LeftEye;
/*0x823d*/ uint8_t                               RightEye;
/*0x823e*/ uint8_t                               Hair;
/*0x823f*/ uint8_t                               Beard;
/*0x8240*/ uint8_t                               OldFace;
/*0x8244*/ int                                   AAPoints;
/*0x8248*/ char                                  PocketPetSaveString[0x2000];            // 0x1000 in older clients
/*0xa248*/ CXStr                                 ItemBuffer;
/*0xa24c*/ uint32_t                              LastShield;
/*0xa250*/ bool                                  bSneak;
/*0xa251*/ bool                                  bHide;
/*0xa254*/ int                                   AAPointsSpent;
/*0xa258*/ int                                   AAPointsAssigned[6];                    // none, general, arch, class, special, focus, merc
/*0xa270*/ PetObjectData*                        pPetData;
/*0xa274*/ int                                   PrimaryActor;
/*0xa278*/ int                                   SecondaryActor;
/*0xa27c*/ bool                                  bUseTemplateFaction;
/*0xa280*/ int                                   TitlePrefixID;
/*0xa284*/ int                                   TitleSuffixID;
/*0xa288*/ bool                                  bAreHandsMagic;
/*0xa28c*/ int                                   SoleEnabledZoneID;
/*0xa290*/ int                                   NewBodyTint;
/*0xa294*/ int                                   CurrentMercenaryIndex;
/*0xa298*/
};

inline namespace deprecated {
	using CHARINFO2 DEPRECATE("Use PcProfile instead of CHARINFO2") = PcProfile;
	using PCHARINFO2 DEPRECATE("Use PcProfile* instead of PCHARINFO2") = PcProfile*;
}

SIZE_CHECK(PcProfile, PcProfile_size);

} // namespace eqlib
