#pragma once
#include <string>
#include "SaveObject.h"
#include <vector>

class SaveFile
{
    public:
        //static methods
        void saveStringToFile(std::string string, std::string filePath);
        std::string loadStringFromFile(std::string filePath);

        //attributes
        std::string filePath;
        std::string rawString;
        std::vector<SaveObject> objects;
        

        //constructors
        SaveFile();
        SaveFile(std::string newFilePath);

        //destructor
        ~SaveFile();

        //methods
        void reset();
        void saveFile();
        void loadFile();
        void addSaveObjectString(std::string saveString);
        void populateAllObjects();

    private:
        //attributes
        std::string::size_type index;
        

        //methods
        void init();
        SaveObject getNextSaveObject();        
        std::string getNextSaveObjectString();
};

