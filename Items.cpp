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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include "pch.h"
#include "Globals.h"
#include "Items.h"

#include "EQClasses.h"

namespace eqlib {

//============================================================================

ItemSpellData::ItemSpellData()
{
	Reset();
}

void ItemSpellData::Reset()
{
	for (SpellData& data : Spells)
		data.Reset();

	memset(SkillMask, 0, sizeof(SkillMask));
}

ItemSpellData::SpellData::SpellData()
{
	Reset();
}

void ItemSpellData::SpellData::Reset()
{
	SpellID = -1;
	RequiredLevel = 0;
	EffectType = ItemEffectProc;
	EffectiveCasterLevel = 0;
	MaxCharges = 0;
	CastTime = 0;
	RecastTime = 0;
	RecastType = 0;
	ProcRate = 0;
	memset(OverrideName, 0, sizeof(OverrideName));
	OverrideDesc = -1;
}

const char* szContainerInstanceNames[] = {
	"Inventory",
	"Bank",
	"Shared Bank",
	"Trade",
	"World Container",
	"Limbo",
	"Tribute",
	"Trophy Tribute",
	"Guild Tribute",
	"Merchant",
	"Deleted Items",
	"Corpse",
	"Bazaar",
	"Inspect",
	"Real Estate",
	"Unknown(15)",
	"Unknown(16)",
	"Unknown(17)",
	"Unknown(18)",
	"Alt Storage",
	"Archived Deleted Items",
	"Mail",
	"Guild Trophy Tribute",
	"Krono",
	"Other",
	"Mercenary",
	"Unknown(26)",
	"Mount Keyring",
	"Unknown(28)",
	"Illusion Keyring",
	"Unknown(30)",
	"Familiar Keyring",
	"Unknown(32)",
	"Hero Forge Keyring",
	"Unknown(34)",
	"Overflow",
	"Dragon Hoard",

	// Some extra in case of expansion in the future
	"Unknown(37)",
	"Unknown(38)",
	"Unknown(39)",
	"Unknown(40)",
};

const char* GetNameForContainerInstance(ItemContainerInstance container)
{
	if (container == eItemContainerInvalid)
		return "Invalid";

	if (container < static_cast<int>(lengthof(szContainerInstanceNames)) && container >= eItemContainerPossessions)
		return szContainerInstanceNames[container];

	return "Unknown";
}

//============================================================================
// ItemDefinition
//============================================================================

ItemDefinition::ItemDefinition()
{
	memset(Name, 0, sizeof(Name));
	memset(LoreName, 0, sizeof(LoreName));
	memset(AdvancedLoreName, 0, sizeof(AdvancedLoreName));
	IDFile = 0;
	IDFile2 = 0;
	ItemNumber = 0;
	EquipSlots = 0;
	Cost = 0;
	IconNumber = 0;
	eGMRequirement = 0;
	bPoofOnDeath = false;
	Weight = 0;
	NoRent = false;
	IsDroppable = false;
	Attuneable = false;
	Heirloom = false;
	Collectible = false;
	NoDestroy = false;
	bNoNPC = false;
	NoZone = false;
	MakerID = 0;
	NoGround = false;
	bNoLoot = false;
	MarketPlace = false;
	bFreeSlot = false;
	bAutoUse = false;
	Unknown0x0e4 = -1;
	Size = 0;
	Type = 0;
	TradeSkills = false;
	Lore = 0;
	LoreEquipped = 0;
	Artifact = false;
	Summoned = false;
	SvCold = 0;
	SvFire = 0;
	SvMagic = 0;
	SvDisease = 0;
	SvPoison = 0;
	SvCorruption = 0;
	STR = 0;
	STA = 0;
	AGI = 0;
	DEX = 0;
	CHA = 0;
	INT = 0;
	WIS = 0;
	HP = 0;
	Mana = 0;
	AC = 0;
	RequiredLevel = 0;
	RecommendedLevel = 0;
	SkillModType = 0;
	SkillModValue = 0;
	SkillModMax = 0;
	SkillModBonus = 0;
	BaneDMGRace = 0;
	BaneDMGBodyType = 0;
	BaneDMGBodyTypeValue = 0;
	BaneDMGRaceValue = 0;
	InstrumentType = 0;
	InstrumentMod = 0;
	Classes = 0;
	Races = 0;
	Deity = 0;
	MaterialTintIndex = 0;
	Magic = false;
	Light = 0;
	Delay = 0;
	ElementalFlag = 0;
	ElementalDamage = 0;
	Range = 0;
	Damage = 0;
	BackstabDamage = 0;
	HeroicSTR = 0;
	HeroicINT = 0;
	HeroicWIS = 0;
	HeroicAGI = 0;
	HeroicDEX = 0;
	HeroicSTA = 0;
	HeroicCHA = 0;
	HealAmount = 0;
	SpellDamage = 0;
	MinLuck = 0;
	MaxLuck = 0;
	Prestige = 0;
	ItemClass = 0;
	ArmorProps.type = 0;
	ArmorProps.variation = 0;
	ArmorProps.material = 0;
	ArmorProps.newArmorID = 0;
	ArmorProps.newArmorType = 0;
	AugData.Reset();
	AugType = 0;
	AugSkinTypeMask = -1;
	AugRestrictions = 0;
	SolventItemID = 0;
	LDTheme = 0;
	LDCost = 0;
	LDType = 0;
	PointBuyBackPercent = 0;
	NeedAdventureCompleted = 0;
	memset(CharmFile, 0, sizeof(CharmFile));
	MerchantGreedMod = 0.0f;

	// TODO: Init ITEMSPELLS

	DmgBonusSkill = 0;
	DmgBonusValue = 0;
	ScriptID = 0;
	FoodDuration = 0;
	ContainerType = 0;
	Slots = 0;
	SizeCapacity = 0;
	WeightReduction = 0;
	BookType = 0;
	BookLang = 0;
	memset(BookFile, 0, sizeof(BookFile));
	Favor = 0;
	GuildFavor = 0;
	bIsFVNoDrop = false;
	Endurance = 0;
	Attack = 0;
	HPRegen = 0;
	ManaRegen = 0;
	EnduranceRegen = 0;
	Haste = 0;
	AnimationOverride = -1;
	PaletteTintIndex = 0;
	bNoPetGive = false;
	bSomeProfile = false;
	StackSize = 1;
	bNoStorage = false;
	MaxPower = 0;
	Purity = 0;
	RightClickScriptID = -1;
	ItemLaunchScriptID = -1;
	QuestItem = false;
	Expendable = false;
	Clairvoyance = 0;
	SubClass = 0;
	bLoginRegReqItem = false;
	Placeable = 0;
	bPlaceableIgnoreCollisions = false;
	PlacementType = 0;
	RealEstateDefID = 0;
	PlaceableScaleRangeMin = .5f;
	PlaceableScaleRangeMax = 2.0;
	RealEstateUpkeepID = 0;
	MaxPerRealEstate = -1;
	memset(HousepetFileName, 0, sizeof(HousepetFileName));
	TrophyBenefitID = -1;
	bDisablePlacementRotation = false;
	bDisableFreePlacement = false;
	NpcRespawnInterval = 0;
	PlaceableDefScale = 1.0f;
	PlaceableDefHeading = 0.0f;
	PlaceableDefPitch = 0.0f;
	PlaceableDefRoll = 0.0f;
	bInteractiveObject = false;
	SocketSubClassCount = 0;
	memset(SocketSubClass, 0, sizeof(SocketSubClass));
}

//============================================================================
// ItemBase / ItemClient
//============================================================================

ItemBase::ItemBase()
	: Contents(0, eItemContainerOther)
{
	ScriptIndex = 0;
	bCollected = false;
	bRankDisabled = false;
	bDisableAugTexture = false;
	Luck = 0;
	ID = 0;
	MerchantSlot = 0;
	ConvertItemID = 0;
	DontKnow = 0;
	NoDropFlag = 0;
	LastCastTime = 0;
	Power = 0;
	ItemHash = 0;
	bRealEstateItemPlaceable = false;
	StackCount = 1;
	OrnamentationIcon = 0;
	MerchantQuantity = 1;
	bItemNeedsUpdate = false;
	Price = 0;
	Open = 0;
	NoteStatus = 0;
	bConvertable = false;
	Tint = 0;
	ArmorType = 0;
	AugFlag = 0;
	NewArmorID = 0;
	RealEstateID = -1;
	Charges = 0;
	Item1 = nullptr;
}

ItemDefinition* ItemBase::GetItemDefinition() const
{
	return const_cast<ItemDefinition*>(Item1);
}

void ItemBase::SetItemDefinition(ItemDefinition* item)
{
	Item1 = item;
	UpdateItemDefinition();
}

void ItemBase::UpdateItemDefinition()
{
	ItemDefinition* pItemDef = GetItemDefinition();
	int containerSlots = pItemDef ? pItemDef->Slots : 0;

	// if no slots, then add slots for augments
	if (containerSlots == 0) containerSlots = MAX_AUG_SOCKETS;
	Contents.SetSize(containerSlots);
}

#ifdef ItemBase__CreateItemTagString_x
FUNCTION_AT_ADDRESS(char*, ItemBase::CreateItemTagString(char*, int, bool), ItemBase__CreateItemTagString);
#endif
#ifdef ItemBase__GetImageNum_x
FUNCTION_AT_ADDRESS(int, ItemBase::GetImageNum() const, ItemBase__GetImageNum);
#endif
#ifdef ItemClient__CanDrop_x
FUNCTION_AT_ADDRESS(bool, ItemBase::CanDrop(bool, bool, bool, bool) const, ItemClient__CanDrop);
#endif
#ifdef ItemBase__GetItemValue_x
FUNCTION_AT_ADDRESS(int, ItemBase::GetItemValue(bool) const, ItemBase__GetItemValue);
#endif
#ifdef ItemBase__IsKeyRingItem_x
FUNCTION_AT_ADDRESS(bool, ItemBase::IsKeyRingItem(KeyRingType) const, ItemBase__IsKeyRingItem);
#endif
#ifdef ItemClient__CanGoInBag_x
FUNCTION_AT_ADDRESS(bool, ItemBase::CanGoInBag(const ItemPtr& pItem, int unused, bool mustbefalse) const, ItemClient__CanGoInBag);
#endif
#ifdef ItemBase__ValueSellMerchant_x
FUNCTION_AT_ADDRESS(int, ItemBase::ValueSellMerchant(float, int) const, ItemBase__ValueSellMerchant);
#endif
#ifdef ItemBase__CanGemFitInSlot_x
FUNCTION_AT_ADDRESS(int, ItemBase::CanGemFitInSlot(const ItemPtr& pItem, int, bool, bool index) const, ItemBase__CanGemFitInSlot);
#endif
#ifdef ItemBase__IsLoreEquipped_x
FUNCTION_AT_ADDRESS(bool, ItemBase::IsLoreEquipped(bool bIncludeSockets) const, ItemBase__IsLoreEquipped);
#endif
#ifdef ItemBase__IsLore_x
FUNCTION_AT_ADDRESS(bool, ItemBase::IsLore(bool bIncludeSockets) const, ItemBase__IsLore);
#endif

void ItemBase::PopulateItemEvolutionData(int maxLevel, int currentLevel, int groupId, int lastEquipped, double expPct)
{
	if (!pEvolutionData)
		pEvolutionData = SoeUtil::MakeShared<ItemEvolutionData>();

	pEvolutionData->EvolvingMaxLevel = maxLevel;
	pEvolutionData->EvolvingCurrentLevel = currentLevel;
	pEvolutionData->GroupID = groupId;
	pEvolutionData->EvolvingExpPct = expPct;
	pEvolutionData->LastEquipped = lastEquipped;
}

void ItemBase::ResetItemEvolutionData()
{
	pEvolutionData.reset();
}

//----------------------------------------------------------------------------

ItemClient::ItemClient()
{
}

DESTRUCTOR_AT_ADDRESS(ItemClient::~ItemClient, ItemClient__dItemClient);

ItemDefinition* ItemClient::GetItemDefinition() const
{
	return const_cast<ItemDefinition*>(Item1 ? Item1 : SharedItemDef.get());
}

//----------------------------------------------------------------------------

char* ItemIndex::FormatItemIndex(char* dest, size_t len) const
{
	if (m_slots[0] == -1)
	{
		strcpy_s(dest, len, "[invalid]");
		return dest;
	}

	strcpy_s(dest, len, "[");

	char szTemp[10];
	for (int i = 0; i < ItemIndex::MAX_INVENTORY_DEPTH; ++i)
	{
		if (m_slots[i] != -1)
		{
			if (i > 0)
				sprintf_s(szTemp, ", %d", m_slots[i]);
			else
				sprintf_s(szTemp, "%d", m_slots[i]);

			strcat_s(dest, len, szTemp);
		}
	}

	strcat_s(dest, len, "]");
	return dest;
}

//----------------------------------------------------------------------------
// ItemContainer

ItemPtr ItemContainer::GetItem(int index) const
{
	if (index >= 0 && index < (int)m_items.size() && index < (int)m_size)
		return m_items[index];

	return ItemPtr();
}

ItemPtr ItemContainer::GetItem(const ItemIndex& index) const
{
	ItemContainer* container = nullptr;
	short slot = -1;

	if (GetIndex(index, container, slot))
	{
		return container->GetItem(slot);
	}

	return ItemPtr();
}

ItemIndex ItemContainer::CreateItemIndex(int slot0, int slot1 /* = -1 */, int slot2 /* = -1 */) const
{
	ItemIndex itemIndex;
	int i = 0;

	// pre-populate with the built-in slots
	for (i = 0; i < m_atDepth; ++i)
		itemIndex[i] = m_slots[i];

	// assign additional slots as available
	int slots[3] = { slot0, slot1, slot2 };

	for (int slot : slots)
	{
		if (slot != -1 && i < ItemIndex::MAX_INVENTORY_DEPTH)
			itemIndex[i++] = slot;
	}

	return itemIndex;
}

bool ItemContainer::IsEmpty() const
{
	for (const auto& item : *this)
	{
		if (item != nullptr)
			return false;
	}

	return true;
}

bool ItemContainer::IsFull() const
{
	for (const auto& item : *this)
	{
		if (item == nullptr)
			return false;
	}

	return true;
}

bool ItemContainer::IsValidIndex(const ItemIndex& index) const
{
	ItemContainer* container = const_cast<ItemContainer*>(this);
	short slot = -1;

	return GetIndex(index, container, slot);
}

void ItemContainer::SetSize(int size)
{
	m_size = size;

	// Only allocate for the container if we already have done so. Otherwise it
	// will happen later when we add items.

	// VeArray hasn't yet implemented resize. As long as we don't call SetSize when
	// it has items, we should be fine...
	//if (!m_items.empty())
	//{
	//	m_items.resize(size);
	//}
}

bool ItemContainer::GetIndex(const ItemIndex& index, ItemContainer*& outContainer, short& outSlot) const
{
	if (!index.IsValid())
		return false;

	const ItemContainer* container = this;
	uint8_t depth = 0;

	// Assumes that -1 was passed in at the start
	outSlot = index.GetSlot(depth++);
	while (outSlot != -1 && container != nullptr)
	{
		short nextSlot = index.GetSlot(depth++);

		if (nextSlot == -1)
		{
			outContainer = const_cast<ItemContainer*>(container);
			return true;
		}

		ItemPtr item = container->GetItem(outSlot);

		container = item ? item->GetChildItemContainer() : nullptr;
		outSlot = nextSlot;
	}

	return false;
}

int ItemContainer::GetRecursiveSize(int depth) const
{
	int size = static_cast<int>(m_size);

	if (depth > 0)
	{
		// recurse over children
		for (const ItemPtr& ptr : *this)
		{
			const ItemContainer* container = ptr ? ptr->GetChildItemContainer() : nullptr;
			if (container)
			{
				size += container->GetSize(depth - 1);
			}
		}
	}

	return size;
}

bool ItemContainer::IsItemInBagOrBase(const ItemIndex& index) const
{
	if (ItemPtr parent = GetItem(index.GetParentIndex()))
	{
		return parent->IsContainer();
	}

	return true;
}

bool ItemContainer::IsItemInSocket(const ItemIndex& index) const
{
	if (ItemPtr parent = GetItem(index.GetParentIndex()))
	{
		return parent->IsSocketValid(index.GetDeepestSlot());
	}

	return false;
}

//----------------------------------------------------------------------------
// EqItemGuid

void EqItemGuid::UnSerialize(CUnSerializeBuffer& buffer)
{
	char temp[GUID_LENGTH - 1];

	buffer.ReadString(temp, lengthof(temp));
	strcpy_s(this->guid, temp);
}

//----------------------------------------------------------------------------
// MultipleItemMoveManager

#ifdef MultipleItemMoveManager__ProcessMove_x
FUNCTION_AT_ADDRESS(MultipleItemMoveManager::ErrorCodes,
	MultipleItemMoveManager::ProcessMove(
		PcZoneClient* pPC,
		const MultipleItemMoveManager::MoveItemArray& moveItemList,
		bool sendMoves, bool clientInitiated), MultipleItemMoveManager__ProcessMove);
#endif

} // namespace eqlib
