#pragma once
#include <string>
#include <vector>

const std::string BEGIN_ATTRIBUTE_IDENTIFIER = "BEGIN ATTRIBUTE ";
const std::string END_ATTRIBUTE_IDENTIFIER = "END ATTRIBUTE ";

class SaveAttribute
{
    public:
        //attributes
        int attributeType;
        int attributeId;
        std::string valueString;

        //constructors
        SaveAttribute();
        SaveAttribute(std::string newRawString);

        //destructor
        ~SaveAttribute();

        //methods
    
    private:
        //attributes
        std::string rawString;

        //methods
        int getAttributeType();
        std::string getAttributeHeaderLine();
        std::string getAttributeFooterLine();
        int getAttributeId();
        std::string getAttributeValueString();
};

//utility functions
std::string get2DIntVectorSaveString(std::vector<std::vector<int>> vector);
std::vector<std::vector<int>> get2dIntVectorFromSaveString(std::string saveString);
std::string getIntVectorSaveString(std::vector<int> vector);
std::vector<int> getIntVectorFromSaveString(std::string saveString);
std::string getSubstrBeginEndWithInclusive(std::string string, std::string beginString, std::string endString, int skip = 0, std::string::size_type* endIndex = NULL);
std::string getSubstrBeginEndWithExclusive(std::string string, std::string beginString, std::string endString, int skip = 0, std::string::size_type* endIndex = NULL);
std::string getAttributeString(int id,int type, std::string value);
std::string getAttributeString(int id, int type, int value);
int getUniqueId();

