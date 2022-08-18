#include "CraftingRecipe.h"

CraftingRecipe::CraftingRecipe()
{
    init();
}

std::vector<CraftingReagent> CraftingRecipe::getInputs()
{
    return inputs;
}

std::vector<CraftingReagent> CraftingRecipe::getOutputs()
{
    return outputs;
}

std::unordered_map<int, std::vector<CraftingSkillRequirements>> CraftingRecipe::getSkillRequirements()
{
    return skillRequirements;
}

std::vector<int> CraftingRecipe::getCraftingStations()
{
    return craftingStations;
}

void CraftingRecipe::addInput(int item, int qty)
{
    inputs.push_back({ item, qty });
}

void CraftingRecipe::addOutput(int item, int qty)
{
    outputs.push_back({ item, qty });
}

void CraftingRecipe::addCraftingStation(int newCraftingStation)
{
    craftingStations.push_back(newCraftingStation);
}

void CraftingRecipe::addSkillRequirement(int quality, int skill, int level)
{
    skillRequirements[quality].push_back({skill, level});
}

bool CraftingRecipe::canBeCraftedAtStation(int thisCraftingStation)
{
    for (int craftingStation : craftingStations) {
        if (thisCraftingStation == craftingStation)
        {
            return true;
        }
    }
    return false;
}

void CraftingRecipe::init()
{
    recipeName = "";
    inputs = {};
    outputs = {};
    skillRequirements = {};
    craftingStations = {};
    for (size_t i = BARELY_USABLE; i < NUM_ITEM_QUALITY_LEVELS; i++)
    {
        skillRequirements[i] = {};
    }
}
