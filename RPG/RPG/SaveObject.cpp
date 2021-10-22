#include "SaveObject.h"

SaveObject::SaveObject() {
    init();
}

SaveObject::SaveObject(std::string saveString) {
    init();
    rawString = saveString;
    objectId = getObjectId();
    objectType = getObjectType();
    populateAllAttributes();
}

void SaveObject::init() {
    rawString = "";
    objectId = -1;
    objectType = -1;
    index = 0;
}

//destructor
SaveObject::~SaveObject() {
    int objectId = 0;
    int objectType = 0;
    std::string rawString = "";
    attributes.clear();
    index = 0;
}

void SaveObject::reset() {
    index = 0;
}

int SaveObject::getObjectId() {
    return std::stoi(getSubstrBeginEndWithExclusive(rawString, BEGIN_OBJECT_IDENTIFIER, "-"));
}

int SaveObject::getObjectType() {
    return std::stoi(getSubstrBeginEndWithExclusive(rawString, BEGIN_OBJECT_IDENTIFIER + std::to_string(objectId) + "-", "\n"));
}

//this method assumes objectType and objectId have already been correctly assigned
std::string SaveObject::getObjectHeaderLine() {
    return BEGIN_OBJECT_IDENTIFIER + std::to_string(objectId) + "-" + std::to_string(objectType);
}

//this method assumes objectType and objectId have already been correctly assigned
std::string SaveObject::getObjectFooterLine() {
    return END_ATTRIBUTE_IDENTIFIER + std::to_string(objectId) + "-" + std::to_string(objectType);
}

SaveAttribute SaveObject::getNextSaveAttribute() {
    std::string attributeString = getNextSaveAttributeString();
    SaveAttribute returnAttribute;

    if (attributeString.compare("") != 0)
    {
        returnAttribute = SaveAttribute(attributeString);
    }
    else {
        reset();
    }

    return returnAttribute;
}

std::string SaveObject::getNextSaveAttributeString() {
    std::string subString = rawString.substr(index);
    std::string nextAttributeId = getSubstrBeginEndWithExclusive(subString, BEGIN_ATTRIBUTE_IDENTIFIER, "\n");
    if (nextAttributeId.compare("") != 0)
    {
        return getSubstrBeginEndWithInclusive(rawString, BEGIN_ATTRIBUTE_IDENTIFIER + nextAttributeId + "\n", END_ATTRIBUTE_IDENTIFIER + nextAttributeId + "\n", 0, &index);
    }
    else {
        return "";
    }  
}

void SaveObject::populateAllAttributes() {
    SaveAttribute saveAttribute;
    bool continueLoop = true;
    while (continueLoop)
    {
        saveAttribute = getNextSaveAttribute();
        if (saveAttribute.valueString.compare("") != 0)
        {
            attributes.push_back(saveAttribute);
        }
        else {
            continueLoop = false;
        }
    }
}

//utility functions
std::vector<SaveObject> getSaveObjectVectorFromSaveString2(std::string saveString) {
    std::vector<SaveObject> returnVector;
    std::string::size_type index = 0;

    SaveObject saveObject;
    bool continueLoop = true;

    while (continueLoop)
    {
        saveObject = getNextSaveObject2(saveString, &index);
        if (saveObject.rawString.compare("") != 0)
        {
            returnVector.push_back(saveObject);
        }
        else {
            continueLoop = false;
        }
    }
    return returnVector;
}

std::vector<std::vector<SaveObject>> getSaveObject2dVectorFromSaveString2(std::string saveString) {
    std::vector<std::vector<SaveObject>> returnVector;
    std::string::size_type index1 = 0, index2 = 0;
    int outerSize, innerSize, innerCount = 0;
    std::string innerSaveString = "";
    bool gotInnerSize = false;
    std::string objectHeader;

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

    for (std::string::size_type i = index1; i < saveString.size(); i++)
    {
        if (saveString[i] == '\n')
        {
            index2 = i;
            break;
        }
    }
    objectHeader = saveString.substr(index1, index2 - index1);

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
                else if (innerCount < innerSize) {
                    innerCount += 1;
                }
                if (innerCount == innerSize) {
                    std::string substring = saveString.substr(index1, index2 - index1);
                    returnVector.push_back(getSaveObjectVectorFromSaveString2(saveString.substr(index1, index2 - index1 + 1)));
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

SaveObject getNextSaveObject2(std::string saveString, std::string::size_type* index) {
    std::string objectString = getNextSaveObjectString2(saveString, index);
    SaveObject returnObject;

    if (objectString.compare("") != 0)
    {
        returnObject = SaveObject(objectString);
    }

    return returnObject;
}

std::string getNextSaveObjectString2(std::string saveString, std::string::size_type * index) {
    std::string subString = saveString.substr(*index);
    std::string nextObjectId = getSubstrBeginEndWithExclusive(subString, BEGIN_OBJECT_IDENTIFIER, "\n");
    return getSubstrBeginEndWithInclusive(saveString, BEGIN_OBJECT_IDENTIFIER + nextObjectId, END_OBJECT_IDENTIFIER + nextObjectId, 0, index);
}