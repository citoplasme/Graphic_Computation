//
// Created by thol on 12-03-2019.
//

#include "parseXML.h"

parseXML::parseXML()
{
    trTime = 0;
    trX = 0;
    trY = 0;
    trZ = 0;
    T_order = 0;

    rTime = 0;
    rA = 0;
    rX = 0;
    rY = 0;
    rZ = 0;
    R_order = 0;

    sX = 1;
    sY = 1;
    sZ = 1;
    S_order = 0;

}

parseXML::parseXML(const parseXML &obj)
{
    xml = obj.xml;
    infoL = obj.infoL;
    filhos = obj.filhos;

    trTime = obj.trTime;
    translates = obj.translates;
    trX = obj.trX;
    trY = obj.trY;
    trZ = obj.trZ;
    T_order = obj.T_order;

    rTime = obj.rTime;
    rA = obj.rA;
    rX = obj.rX;
    rY = obj.rY;
    rZ = obj.rZ;
    R_order = obj.R_order;

    sX = obj.sX;
    sY = obj.sY;
    sZ = obj.sZ;
    S_order = obj.S_order;

}

parseXML::parseXML(float notEmptyBuilder,float notEmptyBuilder2)
{
    trTime = 0;
    trX = notEmptyBuilder;
    trY = notEmptyBuilder2;
    trZ = 0;
    T_order = 0;

    rTime = 0;
    rA = 0;
    rX = 0;
    rY = 0;
    rZ = 0;
    R_order = 0;

    sX = 1;
    sY = 1;
    sZ = 1;
    S_order = 0;

}

std::vector<parseXML> parseXML::getFilhos(){return filhos;}
std::vector<std::string> parseXML::getXMLS(){return xml;}
std::vector<lighting> parseXML::getLights(){return infoL;}

float parseXML::getTrTime(){return  trTime;}
std::vector<TPS> parseXML::getTranslates(){return translates;}
float parseXML::getTrx(){return trX;}
float parseXML::getTry(){return trY;}
float parseXML::getTrz(){return trZ;}
int parseXML::getTorder(){return T_order;}

float parseXML::getRtime(){return rTime;}
float parseXML::getRa(){return rA;}
float parseXML::getRx(){return rX;}
float parseXML::getRy(){return rY;}
float parseXML::getRz(){return rZ;}
int parseXML::getRorder(){return R_order;}

float parseXML::getSx(){return sX;}
float parseXML::getSy(){return sY;}
float parseXML::getSz(){return sZ;}
int parseXML::getSorder(){return S_order;}

void parseXML::insertFilho(parseXML filho){filhos.push_back(filho);}
void parseXML::setXMLS(std::string ins){xml.push_back(ins);}
void parseXML::setLights(lighting ins){infoL.push_back(ins);}

void parseXML::setTrTime(float time){trTime = time;}
void parseXML::setTrx(float ins){trX = ins;}
void parseXML::setTry(float ins){trY = ins;}
void parseXML::setTrz(float ins){trZ = ins;}
void parseXML::setTorder(int ins){T_order = ins;}

void parseXML::setRtime(float time){rTime = time;}
void parseXML::setRa(float ins){rA = ins;}
void parseXML::setRx(float ins){rX = ins;}
void parseXML::setRy(float ins){rY = ins;}
void parseXML::setRz(float ins){rZ = ins;}
void parseXML::setRorder(int ins){R_order = ins;}

void parseXML::setSx(float ins){sX = ins;}
void parseXML::setSy(float ins){sY = ins;}
void parseXML::setSz(float ins){sZ = ins;}
void parseXML::setSorder(int ins){S_order = ins;}

void parseXML::inserControlPoint(float x,float y,float z){
    TPS ins = newControlPoint(x,y,z);
    translates.push_back(ins);
}