#include "SaveFile.h"
#include "SaveObject.h"
#include <fstream>

//static methods
void SaveFile::saveStringToFile(std::string string, std::string filePath) {
    std::ofstream file(filePath.c_str());
    if (file.is_open()) {
        file << string;
        file.close();
    }
    else {
        printf("could not save file %s", filePath.c_str());
    }
}

std::string SaveFile::loadStringFromFile(std::string filePath) {
    std::string returnString;
    std::string line;
    std::ifstream file(filePath.c_str());
    if (file.is_open()) {
        while (std::getline(file, line)) {
            returnString += line + "\n";
        }
        file.close();
    }
    return returnString;
}


//contstructos
SaveFile::SaveFile() {
    init();
}

SaveFile::SaveFile(std::string newFilePath) {
    init();
    filePath = newFilePath;
}

void SaveFile::init() {
    rawString = "";
    filePath = "";
    index = 0;
}

//destructor
SaveFile::~SaveFile() {
    filePath = "";
    rawString = "";
    objects.clear();
    index = 0;
}

//public methods
void SaveFile::reset() {
    index = 0;
}


void SaveFile::saveFile() {
    SaveFile::saveStringToFile(rawString, filePath);
}

void SaveFile::loadFile() {
    rawString = SaveFile::loadStringFromFile(filePath);
    objects = getSaveObjectVectorFromSaveString2(rawString);
    //populateAllObjects();
}

void SaveFile::addSaveObjectString(std::string saveString) {
    rawString += saveString;
}