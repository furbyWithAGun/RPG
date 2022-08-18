#pragma once
#include <vector>
#include <unordered_map>
#include "RpgGameConstants.h"

struct CraftingReagent
{
    int item, qty;
};

struct CraftingSkillRequirements {
    int skill, level;
};

struct CraftingSkillExperience {
    int skill, level;
};

class CraftingRecipe
{
public:
    //contructors
    CraftingRecipe();
    CraftingRecipe(std::string newRecipeName);

    //methods
    std::string getName();
    std::vector<CraftingReagent> getInputs();
    std::vector<CraftingReagent> getOutputs();
    std::unordered_map<int, std::vector<CraftingSkillRequirements>> getSkillRequirements();
    std::vector<int> getCraftingStations();
    void addInput(int item, int qty);
    void addOutput(int item, int qty);
    void addCraftingStation(int newCraftingStation);
    void addSkillRequirement(int quality, int skill, int level);
    void addSkillExperience(int skill, int experience);
    bool canBeCraftedAtStation(int thisCraftingStation);

private:
    //attributes
    std::string recipeName;
    std::vector<CraftingReagent> inputs;
    std::vector<CraftingReagent> outputs;
    std::vector<CraftingSkillExperience> skillExperience;
    std::unordered_map<int, std::vector<CraftingSkillRequirements>> skillRequirements;
    std::vector<int> craftingStations;

    //methods
    void init();
};

