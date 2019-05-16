//
// Created by thol on 30-04-2019.
//

#ifndef ENGINE_LIGHTSOURCE_H
#define ENGINE_LIGHTSOURCE_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

class lightSource {
private:

    std::string tipoLuz;

    float pointX;
    float pointY;
    float pointZ;

    float dirX;
    float dirY;
    float dirZ;

    float phi;
    float theta;

public:

    lightSource();
    lightSource(float notEmptyBuilder,float notEmptyBuilder2);
    lightSource(const lightSource &obj);

    std::string getType();

    float getPointX();
    float getPointY();
    float getPointZ();

    float getDirX();
    float getDirY();
    float getDirZ();

    float getPhi();
    float getTheta();

    void setType(std::string ins);

    void setPointX(float ins);
    void setPointY(float ins);
    void setPointZ(float ins);

    void setDirX(float ins);
    void setDirY(float ins);
    void setDirZ(float ins);

    void setPhi(float ins);
    void setTheta(float ins);

};


#endif //ENGINE_LIGHTSOURCE_H
