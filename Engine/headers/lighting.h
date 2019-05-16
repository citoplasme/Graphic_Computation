//
// Created by thol on 23-04-2019.
//

#ifndef ENGINE_LIGHTING_H
#define ENGINE_LIGHTING_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "tinyxml2.h"
#include "structure.h"

class lighting {
private:

    std::string texture;

    int dValue;
    float diffR;
    float diffG;
    float diffB;

    int sValue;
    float specR;
    float specG;
    float specB;

    int eValue;
    float emR;
    float emG;
    float emB;

    int aValue;
    float ambR;
    float ambG;
    float ambB;

public:

    lighting(float notEmptyBuilder,float notEmptyBuilder2);
    lighting(const lighting &obj);

    std::string getTexture();

    int getDV();
    float getDR();
    float getDG();
    float getDB();

    int getSV();
    float getSR();
    float getSG();
    float getSB();

    int getEV();
    float getER();
    float getEG();
    float getEB();

    int getAV();
    float getAR();
    float getAG();
    float getAB();

    void setTexture(std::string ins);

    void setDV(int ins);
    void setDR(float ins);
    void setDG(float ins);
    void setDB(float ins);

    void setSV(int ins);
    void setSR(float ins);
    void setSG(float ins);
    void setSB(float ins);

    void setEV(int ins);
    void setER(float ins);
    void setEG(float ins);
    void setEB(float ins);

    void setAV(int ins);
    void setAR(float ins);
    void setAG(float ins);
    void setAB(float ins);
};


#endif //ENGINE_LIGHTING_H
