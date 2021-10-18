#include "ItemFactory.h"

Item* createNewItem(int itemType)
{
	Item* itemToReturn;
	switch (itemType)
	{
	case ITEM_SHORT_SWORD:
		itemToReturn =  new ShortSword();
		break;
	case ITEM_LONG_SWORD:
		itemToReturn = new LongSword();
		break;
	case ITEM_CLUB:
		itemToReturn = new Club();
		break;
	case ITEM_MACE:
		itemToReturn = new Mace();
		break;
	case ITEM_RAG_BODY:
		itemToReturn = new RagBody();
		break;
	case ITEM_RAG_BOOTS:
		itemToReturn = new RagBoots();
		break;
	case ITEM_RAG_GLOVES:
		itemToReturn = new RagGloves();
		break;
	case ITEM_RAG_HAT:
		itemToReturn = new RagHat();
		break;
	case ITEM_RAG_PANTS:
		itemToReturn = new RagPants();
		break;
	case ITEM_LINEN_BODY:
		itemToReturn = new LinenBody();
		break;
	case ITEM_LINEN_BOOTS:
		itemToReturn = new LinenBoots();
		break;
	case ITEM_LINEN_GLOVES:
		itemToReturn = new LinenGloves();
		break;
	case ITEM_LINEN_HAT:
		itemToReturn = new LinenHat();
		break;
	case ITEM_LINEN_PANTS:
		itemToReturn = new LinenPants();
		break;
	default:
		printf("Warning: creating blank Item() from item factory");
		itemToReturn = new Item();
		break;
	}
	return itemToReturn;
}
