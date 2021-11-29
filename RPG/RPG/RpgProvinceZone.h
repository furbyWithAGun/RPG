#pragma once
#include "RpgZone.h"

class RpgProvinceZone : public RpgZone
{
public:
    //constructors
    RpgProvinceZone();
    RpgProvinceZone(int newId, std::vector< std::vector<int> > tiles, RpgTileGridScene* gameScene);
    RpgProvinceZone(int newId, RpgTileGridScene* gameScene);
    RpgProvinceZone(SaveObject saveObject, RpgTileGridScene* gameScene);
    RpgProvinceZone(const RpgProvinceZone& oldZone);

    //methods
    void addTownToZone(RpgTown* townToAdd);

    virtual std::string toSaveString(bool withHeaderAndFooter = true) override;

private:
    //attributes
    std::vector<RpgTown*> towns;

    //methods
    void init();
};

