#pragma once
#include <string>
#include "ControllerInterface.h"

//constants
const std::string GAME_TITLE = "RPG";
const int SCREEN_WIDTH = 1900;
const int SCREEN_HEIGHT = 1000;
const int MAX_ZONE_WIDTH = 500;
const int MAX_ZONE_HEIGHT = 500;
const int RPG_GAME_TICKS_PER_SECOND = 150;


//enums
enum TEMP_UNIT_EFFECTS {
    TEMP_EFFECT_FOOD,
    NUM_TEMP_UNIT_EFFECTS
};

enum ITEM_TYPES {
    ITEM_TYPE_UNKNOWN,
    WEAPON,
    ARMOUR,
    RESOURCE,
    FOOD,
    NUM_ITEM_TYPES
};

enum EQUIPMENT_SLOTS {
    BARE_HANDS,
    HEAD_SLOT,
    NECK_SLOT,
    SHOULDERS_SLOT,
    BODY_SLOT,
    ARMS_SLOT,
    HANDS_SLOT,
    LEFT_HAND,
    RIGHT_HAND,
    LEFT_RING_SLOT,
    RIGHT_RING_SLOT,
    BELT_SLOT,
    LEGS_SLOT,
    FEET_SLOT,
    NUM_EQUIPMENT_SLOTS
};

enum DOODAD_TYPES {
    HEALING_PAD,
    DOODAD_TOWN_COMMAND,
    DOODAD_TREE,
    DOODAD_APPLE_TREE,
    DOODAD_RASPBERRY_BUSH,
    NUM_DOODAD_TYPES
};

enum UNIT_TEAMS {
    PLAYER_TEAM,
    MONSTER_TEAM,
    UNKNOWN_TEAM
};

enum UNIT_DISPOSITIONS {
    ENEMY,
    ALLY,
    NEUTRAL,
    UNKNOWN_DISPOSITION
};

enum ATTACK_EQUIP_SLOTS {
    MAIN_ATTACK,
    SECONDARY_ATTACK,
    SPECIAL_ATTACK,
    SPECIAL_ATTACK_TWO
};

enum ATTCK_TYPES {
    MELEE,
    RANGED,
    MAGIC
};

enum SAVE_OBJECTS {
    ZONE_MAP,
    ZONE_PORTAL,
    DOODAD,
    LOCATION,
    SAVED_BUILDING,
    SAVED_BULIDING_TILE,
    SAVED_UNIT,
    SAVED_ITEM,
    SAVED_EQUIPMENT,
    SAVED_WEAPON,
    SAVED_ARMOUR,
    SAVED_RPG_UNIT,
    SAVED_AI_UNIT,
    SAVED_TREE,
    SAVED_UNIT_TEMP_EFFECT,
    SAVED_FOOD_EFFECT,
    SAVED_FRUIT_TREE,
    SAVED_BERRY_BUSH
};

enum MENUS {
    BUILD_MENU,
    PORTAL_PROPERTIES_MENU,
    SAVE_ZONE_MENU,
    LOAD_ZONE_MENU,
    MAIN_MENU,
    RPG_OVERWORLD_MENU,
    INVENTORY_MENU,
    EQUIPPED_MENU,
    ITEM_SELL_MENU,
    ITEM_BUY_MENU,
    TOWN_BUILD_MENU
};

enum UNIT_STATES {
    UNIT_IDLE,
    UNIT_MOVING,
    UNIT_ATTACKING
};

enum ANIMATIONS {
    IDLE_UP_LEFT,
    IDLE_UP,
    IDLE_UP_RIGHT,
    IDLE_RIGHT,
    IDLE_DOWN_RIGHT,
    IDLE_DOWN,
    IDLE_DOWN_LEFT,
    IDLE_LEFT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    ATTACK_UP_LEFT,
    ATTACK_UP,
    ATTACK_UP_RIGHT,
    ATTACK_RIGHT,
    ATTACK_DOWN_RIGHT,
    ATTACK_DOWN,
    ATTACK_DOWN_LEFT,
    ATTACK_LEFT
};

enum TEXTURE_NAMES
{
    GRASS,
    TREE,
    WATER,
    MOUNTAIN,
    ENCAMPMENT,
    WOOD_WALL_ONE,
    WOOD_WALL_TWO,
    BLANK_PORTAL,
    BUTTON_BACKGROUND,
    PLAYER_IDLE_UP_LEFT_SHEET,
    PLAYER_IDLE_UP_SHEET,
    PLAYER_IDLE_UP_RIGHT_SHEET,
    PLAYER_IDLE_RIGHT_SHEET,
    PLAYER_IDLE_DOWN_RIGHT_SHEET,
    PLAYER_IDLE_DOWN_SHEET,
    PLAYER_IDLE_DOWN_LEFT_SHEET,
    PLAYER_IDLE_LEFT_SHEET,
    PLAYER_MOVE_UP_SHEET,
    PLAYER_MOVE_DOWN_SHEET,
    PLAYER_MOVE_RIGHT_SHEET,
    PLAYER_MOVE_LEFT_SHEET,
    BASIC_MELEE_ATTACK_SHEET,
    BASIC_MELEE_ATTACK_DOWN_SHEET,
    BASIC_MELEE_ATTACK_LEFT_SHEET,
    BASIC_MELEE_ATTACK_RIGHT_SHEET,
    BASIC_MELEE_ATTACK_UP_SHEET,
    BASIC_MELEE_ATTACK_UP_LEFT_SHEET,
    BASIC_MELEE_ATTACK_UP_RIGHT_SHEET,
    BASIC_MELEE_ATTACK_DOWN_LEFT_SHEET,
    BASIC_MELEE_ATTACK_DOWN_RIGHT_SHEET,
    RAT_IDLE_DOWN,
    MAC_WIZ_IDLE_DOWN,
    ITEM_SHORT_SWORD,
    BLUE_RAT_IDLE_DOWN,
    ITEM_RAG_HAT,
    ITEM_RAG_BODY,
    ITEM_RAG_PANTS,
    ITEM_RAG_GLOVES,
    ITEM_RAG_BOOTS,
    RAT_KING_IDLE_DOWN,
    ITEM_LONG_SWORD,
    ITEM_LINEN_HAT,
    ITEM_LINEN_BODY,
    ITEM_LINEN_PANTS,
    ITEM_LINEN_GLOVES,
    ITEM_LINEN_BOOTS,
    PORTAL_CAVE_HILL,
    CAVE_FILL,
    CAVE_PATH,
    CAVE_WALL_TOP,
    CAVE_STAIRS_UP,
    ITEM_CLUB,
    ITEM_MACE,
    CAVE_WALL_BOTTOM,
    RAT_IDLE_LEFT,
    RAT_IDLE_RIGHT,
    RAT_IDLE_UP,
    BUILDING_ICON_WEAPON_SHOP,
    BUILDING_ICON_ARMOUR_SHOP,
    BUILDING_ICON_HEALTH,
    BUILDING_ICON_TAVERN,
    BUILDING_ICON_BLACKSMITH,
    TEXTURE_TOWN_COMMAND,
    TEXTURE_TREE_STUMP,
    ITEM_LOGS,
    TILE_DIRT_ROAD,
    TREE_2,
    TREE_3,
    ITEM_APPLE,
    TEXTURE_APPLE_TREE_WITH_FRUIT,
    TEXTURE_APPLE_TREE_NO_FRUIT,
    ITEM_RASPBERRY,
    TEXTURE_RASPBERRY_BUSH_WITH_BERRIES,
    TEXTURE_RASPBERRY_BUSH_NO_BERRIES,
    TEXTURE_EQUIPPED_MENU_SILHOUETTE,
    NUM_TEXTURES
};

enum DIRECTIONS {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_RIGHT,
    UP_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT,
    NUM_DIRECTIONS
};

enum SCENES {
    WORLD_BUILDER,
    OVERWORLD,
    MAIN_MENU_SCENE
};

enum RPG_INPUTS {
    BUTTON_1_ON = NUM_BASIC_MESSAGES + 1,
    BUTTON_1_OFF,
    BUTTON_2_ON,
    BUTTON_2_OFF,
    BUTTON_3_ON,
    BUTTON_3_OFF,
    BUTTON_4_ON,
    BUTTON_4_OFF,
    BUTTON_5_ON,
    BUTTON_5_OFF,
    BUTTON_6_ON,
    BUTTON_6_OFF,
    POINTER_MOVEMENT,
    NUM_RPG_INPUTS
};

enum WORLD_BUILDER_INPUT_COMMANDS {
    PLACE_TILE = NUM_RPG_INPUTS + 1,
    PLACE_PORTAL,
    OPEN_PLACED_PORTAL_OPTIONS_MENU,
    PICK_EXIT_COORDS,
    PLACE_BUILDING,
    OPEN_PLACED_BUILDING_OPTIONS_MENU,
    WORLD_BUILDER_PLACE_DOODAD,
    OPEN_PLACED_DOODAD_OPTIONS_MENU
};

enum OVERWORLD_INPUT_COMMANDS {
    PERFORM_MAIN_ATTACK = NUM_RPG_INPUTS + 1,
    START_MOVE_UP,
    START_MOVE_DOWN,
    START_MOVE_RIGHT,
    START_MOVE_LEFT,
    STOP_MOVE_UP,
    STOP_MOVE_DOWN,
    STOP_MOVE_RIGHT,
    STOP_MOVE_LEFT,
    PICK_UP_ITEM,
    USER_ACTION,
    OVERWORLD_PLACE_BUILDING,
    OVERWORLD_USE,
    OVERWORLD_STRIKE
};

enum UNIT_TYPES {
    PLAYER,
    RAT,
    SOLDIER,
    TOWNSPERSON,
    BLUE_RAT,
    RAT_KING
};

enum BUILDING_TYPES {
    BUILDING_ITEM_SHOP,
    BUILDING_CAMP_COMMAND_CENTRE,
    NUM_BUILDING_TYPES
};