#include "ItemFactory.h"
#include "GameScene.h"
#include "MenuText.h"

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
		FOOD,
		ITEM_RASPBERRY,
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
		FOOD,
		ITEM_APPLE,
		-1,
		0,
		0,
		2,
		0,
		false,
		true,
		1
	}},{ITEM_LOGS, ItemTemplate{
		"Logs",
		RESOURCE,
		ITEM_LOGS,
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
		WEAPON,
		ITEM_SHORT_SWORD,
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
		WEAPON,
		ITEM_LONG_SWORD,
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
		WEAPON,
		ITEM_CLUB,
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
		WEAPON,
		ITEM_MACE,
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
		ARMOUR,
		ITEM_RAG_BODY,
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
		ARMOUR,
		ITEM_RAG_BOOTS,
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
		ARMOUR,
		ITEM_RAG_GLOVES,
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
		ARMOUR,
		ITEM_RAG_HAT,
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
		ARMOUR,
		ITEM_RAG_PANTS,
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
		ARMOUR,
		ITEM_LINEN_BODY,
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
		ARMOUR,
		ITEM_LINEN_BOOTS,
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
		ARMOUR,
		ITEM_LINEN_GLOVES,
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
		ARMOUR,
		ITEM_LINEN_HAT,
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
		ARMOUR,
		ITEM_LINEN_PANTS,
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
		ARMOUR,
		ITEM_LEATHER_BODY,
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
		ARMOUR,
		ITEM_LEATHER_BOOTS,
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
		ARMOUR,
		ITEM_LEATHER_GLOVES,
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
		ARMOUR,
		ITEM_LEATHER_HAT,
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
		ARMOUR,
		ITEM_LEATHER_PANTS,
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
	Item* itemToReturn;
	ItemTemplate itemTemplate = itemTemplates[itemType];
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
		return itemToReturn;
		break;
	default:
		printf("Warning: creating blank Item() from item factory");
		return new Item();
		break;
	}
}

HoverToolTip* createItemToolTip(Item* item, GameScene* scene)
{
	HoverToolTip* returnToolTip = new HoverToolTip();
	switch (item->type)
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
