//
// Created by thol on 23-04-2019.
//

#include "lighting.h"

lighting::lighting(float notEmptyBuilder,float notEmptyBuilder2)
{
    dValue = 0;
    diffR = notEmptyBuilder;
    diffG = notEmptyBuilder2;
    diffB = 0;

    sValue = 0;
    specR = 0;
    specG = 0;
    specB = 0;

    eValue = 0;
    emR = 0;
    emG = 0;
    emB = 0;

    aValue = 0;
    ambR = 0;
    ambG = 0;
    ambB = 0;

    texture = "none";
}

lighting::lighting(const lighting &obj)
{
    dValue = obj.dValue;
    diffR = obj.diffR;
    diffG = obj.diffG;
    diffB = obj.diffB;

    sValue = obj.sValue;
    specR = obj.specR;
    specG = obj.specG;
    specB = obj.specB;

    eValue = obj.eValue;
    emR = obj.emR;
    emG = obj.emG;
    emB = obj.emB;

    aValue = obj.aValue;
    ambR = obj.ambR;
    ambG = obj.ambG;
    ambB = obj.ambB;

    texture = obj.texture;
}

std::string lighting::getTexture(){return texture;}

int lighting::getDV(){return dValue;}
float lighting::getDR(){return diffR;}
float lighting::getDG(){return diffG;}
float lighting::getDB(){return diffB;}

int lighting::getSV(){return sValue;}
float lighting::getSR(){return specR;}
float lighting::getSG(){return specG;}
float lighting::getSB(){return specB;}

int lighting::getEV(){return eValue;}
float lighting::getER(){return emR;}
float lighting::getEG(){return emG;}
float lighting::getEB(){return emB;}

int lighting::getAV(){return aValue;}
float lighting::getAR(){return ambR;}
float lighting::getAG(){return ambG;}
float lighting::getAB(){return ambB;}

void lighting::setTexture(std::string ins){texture = ins;}

void lighting::setDV(int ins){dValue = ins;}
void lighting::setDR(float ins){diffR = ins;}
void lighting::setDG(float ins){diffG = ins;}
void lighting::setDB(float ins){diffB = ins;}

void lighting::setSV(int ins){sValue = ins;}
void lighting::setSR(float ins){specR = ins;}
void lighting::setSG(float ins){specG = ins;}
void lighting::setSB(float ins){specB = ins;}

void lighting::setEV(int ins){eValue = ins;}
void lighting::setER(float ins){emR = ins;}
void lighting::setEG(float ins){emG = ins;}
void lighting::setEB(float ins){emB = ins;}

void lighting::setAV(int ins){aValue = ins;}
void lighting::setAR(float ins){ambR = ins;}
void lighting::setAG(float ins){ambG = ins;}
void lighting::setAB(float ins){ambB = ins;}