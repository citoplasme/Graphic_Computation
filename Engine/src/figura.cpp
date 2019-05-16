//
// Created by thol on 13-03-2019.
//

#include "figura.h"

figura::figura()
{
    filhos = 0;
    total = 0;

    trX = 0;
    trY = 0;
    trZ = 0;
    T_order = 0;

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

figura::figura(const figura &obj)
{
    filhos = obj.filhos;

    total = obj.total;

    infoL = obj.infoL;

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

figura::figura(int fls,int tot, float time, std::vector<TPS> control,std::vector<lighting> light,float tx,float ty,float tz,float tt,float a,float x,float y,float z,float sx,float sy,float sz,int to,int ro,int so)
{
    filhos = fls;
    total = tot;
    infoL = light;

    trTime = time;
    translates = control;
    trX = tx;
    trY = ty;
    trZ = tz;
    T_order = to;

    rTime = tt;
    rA = a;
    rX = x;
    rY = y;
    rZ = z;
    R_order = ro;

    sX = sx;
    sY = sy;
    sZ = sz;
    S_order = so;
}

void figura::setFilhos(int filho){filhos = filho;}

int figura::getFilhos(){return filhos;}

std::vector<lighting> figura::getLight(){return  infoL;}

int figura::getTotal(){return total;}

const int figura::getSizeTrans() {return translates.size();}
std::vector<TPS> figura::getTranslates() {return translates;}

float figura::getTrTime(){return trTime;}
float figura::getTrx(){return trX;}
float figura::getTry(){return trY;}
float figura::getTrz(){return trZ;}
int figura::getTorder(){return  T_order;}

float figura::getRtime() { return rTime; }
float figura::getRa(){return rA;}
float figura::getRx(){return rX;}
float figura::getRy(){return rY;}
float figura::getRz(){return rZ;}
int figura::getRorder(){return  R_order;}

float figura::getSx(){return sX;}
float figura::getSy(){return sY;}
float figura::getSz(){return sZ;}
int figura::getSorder(){return  S_order;}