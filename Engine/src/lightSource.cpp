//
// Created by thol on 30-04-2019.
//

#include "lightSource.h"

lightSource::lightSource()
{
    tipoLuz = "nada";

    pointX = 0;
    pointY = 0;
    pointZ = 0;

    dirX = 0;
    dirY = 0;
    dirZ = 0;

    phi = 0;
    theta = 0;
}

lightSource::lightSource(float notEmptyBuilder, float notEmptyBuilder2)
{
    tipoLuz = "nada";

    pointX = notEmptyBuilder;
    pointY = notEmptyBuilder2;
    pointZ = 0;

    dirX = 0;
    dirY = 0;
    dirZ = 0;

    phi = 0;
    theta = 0;
}

lightSource::lightSource(const lightSource &obj)
{
    tipoLuz = obj.tipoLuz;

    pointX = obj.pointX;
    pointY = obj.pointY;
    pointZ = obj.pointZ;

    dirX = obj.dirX;
    dirY = obj.dirY;
    dirZ = obj.dirZ;

    phi = obj.phi;
    theta = obj.theta;
}

std::string lightSource::getType(){return tipoLuz;}

float lightSource::getPointX(){return pointX;}
float lightSource::getPointY(){return pointY;}
float lightSource::getPointZ(){return pointZ;}

float lightSource::getDirX(){return dirX;}
float lightSource::getDirY(){return dirY;}
float lightSource::getDirZ(){return dirZ;}

float lightSource::getPhi(){return phi;}
float lightSource::getTheta(){return theta;}

void lightSource::setType(std::string ins){tipoLuz = ins;}

void lightSource::setPointX(float ins){pointX = ins;}
void lightSource::setPointY(float ins){pointY = ins;}
void lightSource::setPointZ(float ins){pointZ = ins;}

void lightSource::setDirX(float ins){dirX = ins;}
void lightSource::setDirY(float ins){dirY = ins;}
void lightSource::setDirZ(float ins){dirZ = ins;}

void lightSource::setPhi(float ins){phi = ins;}
void lightSource::setTheta(float ins){theta = ins;}