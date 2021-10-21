#include "ItemFactory.h"

struct ItemTemplate {
	std::string name;
	int itemType;
	int textureKey;
	int slot;
	int minDamage;
	int maxDamage;
	int value;
	int armour;
	bool twoHanded;
};

std::unordered_map<int, ItemTemplate> itemTemplates = {
	{ITEM_SHORT_SWORD, ItemTemplate{
		"Short Sword",
		WEAPON,
		ITEM_SHORT_SWORD,
		LEFT_HAND,
		4,
		10,
		200,
		0,
		false
	}},
	{ITEM_LONG_SWORD, ItemTemplate{
		"Long Sword",
		WEAPON,
		ITEM_LONG_SWORD,
		LEFT_HAND,
		3,
		22,
		800,
		0,
		false
	}},
	{ITEM_CLUB, ItemTemplate{
		"Club",
		WEAPON,
		ITEM_CLUB,
		LEFT_HAND,
		2,
		6,
		75,
		0,
		false
	}},
	{ITEM_MACE, ItemTemplate{
		"Mace",
		WEAPON,
		ITEM_MACE,
		LEFT_HAND,
		4,
		14,
		500,
		0,
		false
	}},
	{ITEM_RAG_BODY, ItemTemplate{
		"Rag Shirt",
		ARMOUR,
		ITEM_RAG_BODY,
		BODY_SLOT,
		0,
		0,
		50,
		1,
		false
	}},
	{ITEM_RAG_BOOTS, ItemTemplate{
		"Rag Boots",
		ARMOUR,
		ITEM_RAG_BOOTS,
		FEET_SLOT,
		0,
		0,
		50,
		1,
		false
	}},
	{ITEM_RAG_GLOVES, ItemTemplate{
		"Rag Gloves",
		ARMOUR,
		ITEM_RAG_GLOVES,
		HANDS_SLOT,
		0,
		0,
		50,
		1,
		false
	}},
	{ITEM_RAG_HAT, ItemTemplate{
		"Rag Hat",
		ARMOUR,
		ITEM_RAG_HAT,
		HEAD_SLOT,
		0,
		0,
		50,
		1,
		false
	}},
	{ITEM_RAG_PANTS, ItemTemplate{
		"Rag Pants",
		ARMOUR,
		ITEM_RAG_PANTS,
		LEGS_SLOT,
		0,
		0,
		50,
		1,
		false
	}},
	{ITEM_LINEN_BODY, ItemTemplate{
		"Linen Shirt",
		ARMOUR,
		ITEM_LINEN_BODY,
		BODY_SLOT,
		0,
		0,
		100,
		2,
		false
	}},
	{ ITEM_LINEN_BOOTS, ItemTemplate{
		"Linen Boots",
		ARMOUR,
		ITEM_LINEN_BOOTS,
		FEET_SLOT,
		0,
		0,
		100,
		2,
		false
	} },
	{ ITEM_LINEN_GLOVES, ItemTemplate{
		"Linen Gloves",
		ARMOUR,
		ITEM_LINEN_GLOVES,
		HANDS_SLOT,
		0,
		0,
		100,
		2,
		false
	} },
	{ ITEM_LINEN_HAT, ItemTemplate{
		"Linen Hat",
		ARMOUR,
		ITEM_LINEN_HAT,
		HEAD_SLOT,
		0,
		0,
		100,
		2,
		false
	} },
	{ ITEM_LINEN_PANTS, ItemTemplate{
		"Linen Pants",
		ARMOUR,
		ITEM_LINEN_PANTS,
		LEGS_SLOT,
		0,
		0,
		100,
		2,
		false
	} }
};

Item* createNewItem(int item)
{
	Item* itemToReturn;
	ItemTemplate itemTemplate = itemTemplates[item];
	switch (itemTemplate.itemType)
	{
	case WEAPON:
		itemToReturn = new Weapon();
		((Weapon*)itemToReturn)->name = itemTemplate.name;
		((Weapon*)itemToReturn)->textureKey = itemTemplate.textureKey;
		((Weapon*)itemToReturn)->minDamage = itemTemplate.minDamage;
		((Weapon*)itemToReturn)->maxDamage = itemTemplate.maxDamage;
		((Weapon*)itemToReturn)->value = itemTemplate.value;
		((Weapon*)itemToReturn)->twoHanded = itemTemplate.twoHanded;
		((Weapon*)itemToReturn)->slot = itemTemplate.slot;
		return itemToReturn;
		break;
	case ARMOUR:
		itemToReturn = new Armour();
		((Armour*)itemToReturn)->name = itemTemplate.name;
		((Armour*)itemToReturn)->textureKey = itemTemplate.textureKey;
		((Armour*)itemToReturn)->value = itemTemplate.value;
		((Armour*)itemToReturn)->armour = itemTemplate.armour;
		((Armour*)itemToReturn)->slot = itemTemplate.slot;
		return itemToReturn;
		break;
	default:
		printf("Warning: creating blank Item() from item factory");
		return new Item();
		break;
	}
}
