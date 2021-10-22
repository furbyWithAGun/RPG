#pragma once
#include <string>
#include "SaveAttribute.h"
#include <vector>

const std::string BEGIN_OBJECT_IDENTIFIER = "BEGIN OBJECT ";
const std::string END_OBJECT_IDENTIFIER = "END OBJECT ";

class SaveObject
{
    public:
        //attributes
        int objectId;
        int objectType;        
        std::string rawString;
        std::vector<SaveAttribute> attributes;

        //constructors
        SaveObject();
        SaveObject(std::string saveString);

        //destructor
        ~SaveObject();

        //methods
        void reset();
        

    private:
        //attributes
        std::string::size_type index;

        //methods
        void init();
        int getObjectType();
        std::string getObjectHeaderLine();
        std::string getObjectFooterLine();
        int getObjectId();
        std::string getNextSaveAttributeString();
        void populateAllAttributes();
        SaveAttribute getNextSaveAttribute();
};

//utility functions
std::vector<SaveObject> getSaveObjectVectorFromSaveString2(std::string saveString);
std::vector<std::vector<SaveObject>> getSaveObject2dVectorFromSaveString2(std::string saveString);
SaveObject getNextSaveObject2(std::string saveString, std::string::size_type* index);
std::string getNextSaveObjectString2(std::string saveString, std::string::size_type* index);

