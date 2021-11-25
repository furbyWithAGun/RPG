#include "ItemFactory.h"
#include "GameScene.h"
#include "MenuText.h"

struct ItemTemplate {
	std::string name;
	int specificType;
	int generalType;
	int textureKey;
	int slot;
	int minDamage;
	int maxDamage;
	int value;
	int armour;
	bool twoHanded;
	bool stackable;
	int stackSize;
};

struct FoodTemplate {
	int hungerGain;
	int healthRegen;
	int healthRegenDurationInSeconds;
};

std::unordered_map<int, FoodTemplate> foodTemplates = {
	{ITEM_RASPBERRY, FoodTemplate{
		10,
		2,
		50
}},{ITEM_APPLE, FoodTemplate{
		10,
		1,
		120
}}
};

std::unordered_map<int, ItemTemplate> itemTemplates = {
	{ITEM_RASPBERRY, ItemTemplate{
		"Raspberry",
		ITEM_RASPBERRY,
		FOOD,
		TEXTURE_RASPBERRY,
		-1,
		0,
		0,
		2,
		0,
		false,
		true,
		1
	}},{ITEM_APPLE, ItemTemplate{
		"Apple",
		ITEM_APPLE,
		FOOD,
		TEXTURE_APPLE,
		-1,
		0,
		0,
		2,
		0,
		false,
		true,
		1
	}},{ITEM_WOOD, ItemTemplate{
		"Wood",
		ITEM_WOOD,
		RESOURCE,
		TEXTURE_LOGS,
		-1,
		0,
		0,
		2,
		0,
		false,
		true,
		1
	}},
	{ITEM_SHORT_SWORD, ItemTemplate{
		"Short Sword",
		ITEM_SHORT_SWORD,
		WEAPON,
		TEXTURE_SHORT_SWORD,
		LEFT_HAND,
		4,
		10,
		200,
		0,
		false,
		false,
		1
	}},
	{ITEM_LONG_SWORD, ItemTemplate{
		"Long Sword",
		ITEM_LONG_SWORD,
		WEAPON,
		TEXTURE_LONG_SWORD,
		LEFT_HAND,
		3,
		22,
		800,
		0,
		false,
		false,
		1
	}},
	{ITEM_CLUB, ItemTemplate{
		"Club",
		ITEM_CLUB,
		WEAPON,
		TEXTURE_CLUB,
		LEFT_HAND,
		2,
		6,
		75,
		0,
		false,
		false,
		1
	}},
	{ITEM_MACE, ItemTemplate{
		"Mace",
		ITEM_MACE,
		WEAPON,
		TEXTURE_MACE,
		LEFT_HAND,
		4,
		14,
		500,
		0,
		false,
		false,
		1
	}},
	{ITEM_RAG_BODY, ItemTemplate{
		"Rag Shirt",
		ITEM_RAG_BODY,
		ARMOUR,
		TEXTURE_RAG_BODY,
		BODY_SLOT,
		0,
		0,
		50,
		1,
		false,
		false,
		1
	}},
	{ITEM_RAG_BOOTS, ItemTemplate{
		"Rag Boots",
		ITEM_RAG_BOOTS,
		ARMOUR,
		TEXTURE_RAG_BOOTS,
		FEET_SLOT,
		0,
		0,
		50,
		1,
		false,
		false,
		1
	}},
	{ITEM_RAG_GLOVES, ItemTemplate{
		"Rag Gloves",
		ITEM_RAG_GLOVES,
		ARMOUR,
		TEXTURE_RAG_GLOVES,
		HANDS_SLOT,
		0,
		0,
		50,
		1,
		false,
		false,
		1
	}},
	{ITEM_RAG_HAT, ItemTemplate{
		"Rag Hat",
		ITEM_RAG_HAT,
		ARMOUR,
		TEXTURE_RAG_HAT,
		HEAD_SLOT,
		0,
		0,
		50,
		1,
		false,
		false,
		1
	}},
	{ITEM_RAG_PANTS, ItemTemplate{
		"Rag Pants",
		ITEM_RAG_PANTS,
		ARMOUR,
		TEXTURE_RAG_PANTS,
		LEGS_SLOT,
		0,
		0,
		50,
		1,
		false,
		false,
		1
	}},
	{ITEM_LINEN_BODY, ItemTemplate{
		"Linen Shirt",
		ITEM_LINEN_BODY,
		ARMOUR,
		TEXTURE_LINEN_BODY,
		BODY_SLOT,
		0,
		0,
		100,
		2,
		false,
		false,
		1
	}},
	{ ITEM_LINEN_BOOTS, ItemTemplate{
		"Linen Boots",
		ITEM_LINEN_BOOTS,
		ARMOUR,
		TEXTURE_LINEN_BOOTS,
		FEET_SLOT,
		0,
		0,
		100,
		2,
		false,
		false,
		1
	} },
	{ ITEM_LINEN_GLOVES, ItemTemplate{
		"Linen Gloves",
		ITEM_LINEN_GLOVES,
		ARMOUR,
		TEXTURE_LINEN_GLOVES,
		HANDS_SLOT,
		0,
		0,
		100,
		2,
		false,
		false,
		1
	} },
	{ ITEM_LINEN_HAT, ItemTemplate{
		"Linen Hat",
		ITEM_LINEN_HAT,
		ARMOUR,
		TEXTURE_LINEN_HAT,
		HEAD_SLOT,
		0,
		0,
		100,
		2,
		false,
		false,
		1
	} },
	{ ITEM_LINEN_PANTS, ItemTemplate{
		"Linen Pants",
		ITEM_LINEN_PANTS,
		ARMOUR,
		TEXTURE_LINEN_PANTS,
		LEGS_SLOT,
		0,
		0,
		100,
		2,
		false,
		false,
		1
	} },
	{ITEM_LEATHER_BODY, ItemTemplate{
		"Leather Armour",
		ITEM_LEATHER_BODY,
		ARMOUR,
		TEXTURE_LEATHER_BODY,
		BODY_SLOT,
		0,
		0,
		250,
		3,
		false,
		false,
		1
	}},
	{ ITEM_LEATHER_BOOTS, ItemTemplate{
		"Leather Boots",
		ITEM_LEATHER_BOOTS,
		ARMOUR,
		TEXTURE_LEATHER_BOOTS,
		FEET_SLOT,
		0,
		0,
		250,
		3,
		false,
		false,
		1
	} },
	{ ITEM_LEATHER_GLOVES, ItemTemplate{
		"leather Gloves",
		ITEM_LEATHER_GLOVES,
		ARMOUR,
		TEXTURE_LEATHER_GLOVES,
		HANDS_SLOT,
		0,
		0,
		250,
		3,
		false,
		false,
		1
	} },
	{ ITEM_LEATHER_HAT, ItemTemplate{
		"Leather Helm",
		ITEM_LEATHER_HAT,
		ARMOUR,
		TEXTURE_LEATHER_HAT,
		HEAD_SLOT,
		0,
		0,
		250,
		3,
		false,
		false,
		1
	} },
	{ ITEM_LEATHER_PANTS, ItemTemplate{
		"Leather Leggings",
		ITEM_LEATHER_PANTS,
		ARMOUR,
		TEXTURE_LEATHER_PANTS,
		LEGS_SLOT,
		0,
		0,
		250,
		3,
		false,
		false,
		1
	} }
};

Item* createNewItem(int itemType)
{
	Item* itemToReturn;
	/*ItemTemplate itemTemplate = itemTemplates[itemType];
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
		break;
	case ARMOUR:
		itemToReturn = new Armour();
		((Armour*)itemToReturn)->name = itemTemplate.name;
		((Armour*)itemToReturn)->textureKey = itemTemplate.textureKey;
		((Armour*)itemToReturn)->value = itemTemplate.value;
		((Armour*)itemToReturn)->armour = itemTemplate.armour;
		((Armour*)itemToReturn)->slot = itemTemplate.slot;
		break;
	case RESOURCE:
		itemToReturn = new Item();
		itemToReturn->name = itemTemplate.name;
		itemToReturn->textureKey = itemTemplate.textureKey;
		itemToReturn->value = itemTemplate.value;
		itemToReturn->stackable= itemTemplate.stackable;
		itemToReturn->stackSize= itemTemplate.stackSize;
		break;
	case FOOD:
		itemToReturn = new Food();
		itemToReturn->name = itemTemplate.name;
		itemToReturn->textureKey = itemTemplate.textureKey;
		itemToReturn->value = itemTemplate.value;
		itemToReturn->stackable = itemTemplate.stackable;
		itemToReturn->stackSize = itemTemplate.stackSize;
		((Food*)itemToReturn)->hungerGain = foodTemplates[itemType].hungerGain;
		((Food*)itemToReturn)->healthRegen = foodTemplates[itemType].healthRegen;
		((Food*)itemToReturn)->healthRegenDurationInSeconds = foodTemplates[itemType].healthRegenDurationInSeconds;
		break;
	default:
		printf("Warning: creating blank Item() from item factory");
		itemToReturn = new Item();
		break;
	}
	itemToReturn->id = getUniqueItemId();*/
	itemToReturn = createNewItemBlankId(itemType);
	itemToReturn->id = getUniqueItemId();
	return itemToReturn;
}

Item* createNewItemBlankId(int itemType)
{
	Item* itemToReturn = nullptr;
	ItemTemplate itemTemplate = itemTemplates[itemType];
	switch (itemTemplate.generalType)
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
		break;
	case ARMOUR:
		itemToReturn = new Armour();
		((Armour*)itemToReturn)->name = itemTemplate.name;
		((Armour*)itemToReturn)->textureKey = itemTemplate.textureKey;
		((Armour*)itemToReturn)->value = itemTemplate.value;
		((Armour*)itemToReturn)->armour = itemTemplate.armour;
		((Armour*)itemToReturn)->slot = itemTemplate.slot;
		break;
	case RESOURCE:
		itemToReturn = new Item();
		itemToReturn->name = itemTemplate.name;
		itemToReturn->textureKey = itemTemplate.textureKey;
		itemToReturn->value = itemTemplate.value;
		itemToReturn->stackable = itemTemplate.stackable;
		itemToReturn->stackSize = itemTemplate.stackSize;
		break;
	case FOOD:
		itemToReturn = new Food();
		itemToReturn->name = itemTemplate.name;
		itemToReturn->textureKey = itemTemplate.textureKey;
		itemToReturn->value = itemTemplate.value;
		itemToReturn->stackable = itemTemplate.stackable;
		itemToReturn->stackSize = itemTemplate.stackSize;
		((Food*)itemToReturn)->hungerGain = foodTemplates[itemType].hungerGain;
		((Food*)itemToReturn)->healthRegen = foodTemplates[itemType].healthRegen;
		((Food*)itemToReturn)->healthRegenDurationInSeconds = foodTemplates[itemType].healthRegenDurationInSeconds;
		break;
	default:
		printf("Warning: creating blank Item() from item factory");
		break;
	}
	itemToReturn->specificType = itemTemplate.specificType;
	return itemToReturn;
}

HoverToolTip* createItemToolTip(Item* item, GameScene* scene)
{
	HoverToolTip* returnToolTip = new HoverToolTip();
	switch (item->generalType)
	{
	case WEAPON:
		returnToolTip->setdimensions(scene->engine->screenWidth * 0.15, scene->engine->screenHeight * 0.15);
		returnToolTip->subElements.push_back(new MenuText(scene, "Damage: " + std::to_string(((Weapon*)item)->minDamage) + "-" + std::to_string(((Weapon*)item)->maxDamage), COLOR_WHITE, 10, 10));
		returnToolTip->subElements.push_back(new MenuText(scene, "Value: " + std::to_string(((Weapon*)item)->value), COLOR_WHITE, 10, 40));
		break;
	case ARMOUR:
		returnToolTip->setdimensions(scene->engine->screenWidth * 0.15, scene->engine->screenHeight * 0.15);
		returnToolTip->subElements.push_back(new MenuText(scene, "Armour: " + std::to_string(((Armour*)item)->armour), COLOR_WHITE, 10, 10));
		returnToolTip->subElements.push_back(new MenuText(scene, "Value: " + std::to_string(((Armour*)item)->value), COLOR_WHITE, 10, 40));
		break;
	case FOOD:
		returnToolTip->setdimensions(scene->engine->screenWidth * 0.21, scene->engine->screenHeight * 0.15);
		returnToolTip->subElements.push_back(new MenuText(scene, "Heals " + std::to_string(((Food*)item)->healthRegen * ((Food*)item)->healthRegenDurationInSeconds) + " over " + std::to_string(((Food*)item)->healthRegenDurationInSeconds) + " seconds", COLOR_WHITE, 10, 10));
		returnToolTip->subElements.push_back(new MenuText(scene, "Value: " + std::to_string(((Food*)item)->value), COLOR_WHITE, 10, 40));
		break;
	default:
		returnToolTip->setdimensions(scene->engine->screenWidth * 0.15, scene->engine->screenHeight * 0.15);
		returnToolTip->subElements.push_back(new MenuText(scene, "Value: " + std::to_string(((Food*)item)->value), COLOR_WHITE, 10, 10));
		break;
	}

	returnToolTip->setScene(scene);
	return returnToolTip;
}
