//
// Created by thol on 12-03-2019.
//

#ifndef ENGINE_PARSEXML_H
#define ENGINE_PARSEXML_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "tinyxml2.h"
#include "structure.h"
#include "lighting.h"

class parseXML {
private:
    std::vector<std::string> xml;
    std::vector<lighting> infoL;
    std::vector<parseXML> filhos;

    float trTime;
    std::vector<TPS> translates;
    float trX;
    float trY;
    float trZ;
    int T_order;

    float rTime;
    float rA;
    float rX;
    float rY;
    float rZ;
    int R_order;

    float sX;
    float sY;
    float sZ;
    int S_order;

public:

    parseXML();
    parseXML(float notEmptyBuilder,float notEmptyBuilder2);
    parseXML(const parseXML &obj);

    std::vector<parseXML> getFilhos();
    std::vector<std::string> getXMLS();
    std::vector<lighting> getLights();

    float getTrTime();
    std::vector<TPS> getTranslates();
    float getTrx();
    float getTry();
    float getTrz();
    int getTorder();

    float getRtime();
    float getRa();
    float getRx();
    float getRy();
    float getRz();
    int getRorder();

    float getSx();
    float getSy();
    float getSz();
    int getSorder();

    void insertFilho(parseXML filho);
    void setXMLS(std::string ins);
    void setLights(lighting ins);

    void setTrTime(float time);
    void inserControlPoint(float x,float y,float z);
    void setTrx(float ins);
    void setTry(float ins);
    void setTrz(float ins);
    void setTorder(int ins);

    void setRtime(float time);
    void setRa(float ins);
    void setRx(float ins);
    void setRy(float ins);
    void setRz(float ins);
    void setRorder(int ins);

    void setSx(float ins);
    void setSy(float ins);
    void setSz(float ins);
    void setSorder(int ins);
};


#endif //ENGINE_PARSEXML_H
