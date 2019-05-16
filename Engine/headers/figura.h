//
// Created by thol on 13-03-2019.
//

#ifndef ENGINE_FIGURAS_H
#define ENGINE_FIGURAS_H


#include <vector>

#include "structure.h"
#include "lighting.h"

class figura {
private:
    int filhos;

    int total;

    std::vector<lighting> infoL;

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

    figura();
    figura(const figura &obj);
    figura(int filhos,int tot, float time, std::vector<TPS> control,std::vector<lighting> light, float tx,float ty,float tz,float rt,float a,float x,float y,float z,float sx,float sy,float sz,int to,int ro,int so);

    void setFilhos(int filho);

    int getFilhos();

    int getTotal();

	const int getSizeTrans();
	std::vector<TPS> getTranslates();
    std::vector<lighting> getLight();

    float getTrTime();
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
};


#endif //ENGINE_FIGURAS_H
