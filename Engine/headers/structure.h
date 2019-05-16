#ifndef LOADER_STRUCTURE_H
#define LOADER_STRUCTURE_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>


typedef struct triangulo *Triangulo;

Triangulo setTriangulo(Triangulo t, float xx1, float yy1, float zz1, float xx2, float yy2, float zz2, float xx3, float yy3, float zz3);

Triangulo trianguloInit();

float getX1(Triangulo t);
float getX2(Triangulo t);
float getX3(Triangulo t);

float getY1(Triangulo t);
float getY2(Triangulo t);
float getY3(Triangulo t);

float getZ1(Triangulo t);
float getZ2(Triangulo t);
float getZ3(Triangulo t);

typedef struct threePointSet *TPS;

TPS newControlPoint(float x, float y, float z);

float getPX(TPS t);
float getPY(TPS t);
float getPZ(TPS t);

#endif //LOADER_STRUCTURE_H
