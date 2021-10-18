#include "SaveAttribute.h"
#include <stdio.h>
#include <vector>

int uniqueId = 0;


SaveAttribute::SaveAttribute() {
    attributeType = -1;
    attributeId = -1;
    rawString = "";
    valueString = "";
}

SaveAttribute::SaveAttribute(std::string newRawString) {
    rawString = newRawString;
    attributeId = getAttributeId();
    attributeType = getAttributeType();
    valueString = getAttributeValueString();
}

SaveAttribute::~SaveAttribute() {
    attributeType = 0;
    attributeId = 0;
    rawString = "";
    valueString = "";
}

int SaveAttribute::getAttributeId() {
    return std::stoi(getSubstrBeginEndWithExclusive(rawString, BEGIN_ATTRIBUTE_IDENTIFIER, "-"));
}


int SaveAttribute::getAttributeType() {
    return std::stoi(getSubstrBeginEndWithExclusive(rawString, BEGIN_ATTRIBUTE_IDENTIFIER + std::to_string(attributeId) + "-", "\n"));
}

//this method assumes attributeType and attributeId have already been correctly assigned
std::string SaveAttribute::getAttributeHeaderLine() {
    return BEGIN_ATTRIBUTE_IDENTIFIER + std::to_string(attributeId) + "-" + std::to_string(attributeType);
}

//this method assumes attributeType and attributeId have already been correctly assigned
std::string SaveAttribute::getAttributeFooterLine() {
    return END_ATTRIBUTE_IDENTIFIER + std::to_string(attributeId) + "-" + std::to_string(attributeType);
}

//this method assumes attributeType and attributeID have already been correctly assigned
std::string SaveAttribute::getAttributeValueString() {
    std::string tempValueString = getSubstrBeginEndWithExclusive(rawString, getAttributeHeaderLine() + "\n", getAttributeFooterLine() + "\n");
    int size = tempValueString.size();
    return tempValueString.substr(0, size - 1);
}

//utility functions
std::string get2DIntVectorSaveString(std::vector<std::vector<int>> vector) {
    std::string returnString;
    returnString += std::to_string(vector.size())+ "\n";
    for (int i = 0; i < vector.size(); i++)
    {
        returnString += std::to_string(vector[i].size()) + "\n";
        for (int j = 0; j < vector[i].size(); j++)
        {
            returnString += std::to_string(vector[i][j]) + "\n";
        }
    }

    return returnString;
}

std::string getIntVectorSaveString(std::vector<int> vector) {
    std::string returnString;
    returnString += std::to_string(vector.size()) + "\n";
    for (int i = 0; i < vector.size(); i++)
    {
        returnString += std::to_string(vector[i]) + "\n";
    }

    return returnString;
}


std::vector<std::vector<int>> get2dIntVectorFromSaveString(std::string saveString) {
    std::vector<std::vector<int>> returnVector;
    std::string::size_type index1 = 0, index2 = 0;
    int outerSize, innerSize, innerCount = 0;
    std::string innerSaveString = "";
    bool gotInnerSize = false;

    for (std::string::size_type i = 0; i < saveString.size(); i++)
    {
        if (saveString[i] == '\n')
        {
            index2 = i;
            break;
        }
    }
    outerSize = stoi(saveString.substr(index1, index2 - index1));
    index1 = index2 + 1;

    for (int i = 0; i < outerSize; i++)
    {
        for (int j = index1; j < saveString.size(); j++)
        {
            if (saveString[j] == '\n')
            {
                index2 = j;
                if (!gotInnerSize)
                {
                    innerSize = stoi(saveString.substr(index1, index2 - index1));
                    gotInnerSize = true;
                }
                else if (innerCount < innerSize){
                    innerCount += 1;
                }
                if (innerCount == innerSize) {
                    std::string substring = saveString.substr(index1, index2 - index1);
                    returnVector.push_back(getIntVectorFromSaveString(saveString.substr(index1, index2 - index1 + 1)));
                    innerCount = 0;
                    gotInnerSize = false;
                    index1 = index2 + 1;
                    break;
                }
            }
        }
    }
    

    return returnVector;
}

std::vector<int> getIntVectorFromSaveString(std::string saveString) {
    std::vector<int> returnVector;
    std::string::size_type index1 = 0, index2 = 0;
    int size;
    bool gotSize = false;

    for (std::string::size_type i = 0; i < saveString.size(); i++)
    {
        if (saveString[i] == '\n')
        {
            index2 = i;
            break;
        }
    }

    size = stoi(saveString.substr(index1, index2 - index1));
    index1 = index2 + 1;

    for (int i = 0; i < size; i++)
    {
        for (int j = index1; j < saveString.size(); j++)
        {
            if (saveString[j] == '\n')
            {
                index2 = j;
                returnVector.push_back(stoi(saveString.substr(index1, index2 - index1)));
                index1 = index2 + 1;
                break;
            }
        }
    }


    return returnVector;
}

std::string getSubstrBeginEndWithInclusive(std::string string, std::string beginString, std::string endString, int skip, std::string::size_type * endIndex) {
    std::string::size_type index1 = 0, index2 = 0;
    if (endIndex != NULL) {
        index1 = *endIndex;
        index2 = *endIndex;
    }
    std::string returnString = "";
    int skipped = 0;
    bool index1Found = false, index2Found = false;
    for (std::string::size_type i = index1; i < string.size(); i++) {
        if (string.substr(i, beginString.size()).compare(beginString) == 0)
        {
            index1 = i;
            index1Found = true;
        }
        else if (string.substr(i, endString.size()).compare(endString) == 0 && index1Found) {
            index2 = i + endString.size();
            index2Found = true;
        }
        if (index1Found == true && index2Found == true) {
            if (skipped >= skip)
            {
                break;
            }
            else {
                skipped += 1;
                index1Found = false;
                index2Found = false;
            }
        }
    }
    if (index1Found == true && index2Found == true)
    {
        returnString = string.substr(index1, index2 - index1);
    }
    else {
        returnString = "";
    }
    if (endIndex != NULL)
    {
        *endIndex = index2;
    }
    return returnString;
}

std::string getSubstrBeginEndWithExclusive(std::string string, std::string beginString, std::string endString, int skip, std::string::size_type* endIndex) {
    std::string::size_type index1 = 0, index2 = 0;
    if (endIndex != NULL) {
        index1 = *endIndex;
        index2 = *endIndex;
    }
    std::string returnString = "";
    int skipped = 0;
    bool index1Found = false, index2Found = false;
    for (std::string::size_type i = index1; i < string.size(); i++) {
        if (string.substr(i, beginString.size()).compare(beginString) == 0)
        {
            index1 = i + beginString.size();
            index1Found = true;
        }
        else if (string.substr(i, endString.size()).compare(endString) == 0 && index1Found) {
            index2 = i;
            index2Found = true;
        }
        if (index1Found == true && index2Found == true) {
            if (skipped >= skip)
            {
                break;
            }
            else {
                skipped += 1;
                index1Found = false;
                index2Found = false;
            }
        }
    }
    if (index1Found == true && index2Found == true)
    {
        returnString = string.substr(index1, index2 - index1);
    }
    else {
        returnString = "";
    }

    if (endIndex != NULL)
    {
        *endIndex = index2;
    }
    return returnString;
}

std::string getAttributeString(int id, int type, std::string value) {
    return BEGIN_ATTRIBUTE_IDENTIFIER + std::to_string(id) + "-" + std::to_string(type) + "\n" + value + "\n" + END_ATTRIBUTE_IDENTIFIER + std::to_string(id) + "-" + std::to_string(type) + "\n";
}

std::string getAttributeString(int id,int type,int value) {
    return BEGIN_ATTRIBUTE_IDENTIFIER + std::to_string(id) + "-" + std::to_string(type) + "\n" + std::to_string(value) + "\n" + END_ATTRIBUTE_IDENTIFIER + std::to_string(id) + "-" + std::to_string(type) + "\n";
}

int getUniqueId() {
    uniqueId += 1;
    return uniqueId;
}