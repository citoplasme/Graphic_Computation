//
// Created by thol on 02-03-2019.
//

#include "structure.h"

////////////----------- STRUCT TRIANGULO -----------////////////
////////////----------- STRUCT TRIANGULO -----------////////////
////////////----------- STRUCT TRIANGULO -----------////////////

typedef struct triangulo
{
	float x1;
	float y1;
	float z1;

	float x2;
	float y2;
	float z2;

	float x3;
	float y3;
	float z3;

}triangulo;

Triangulo setTriangulo(Triangulo t, float xx1, float yy1, float zz1, float xx2, float yy2, float zz2, float xx3, float yy3, float zz3)
{
	t->x1 = xx1;
	t->y1 = yy1;
	t->z1 = zz1;

	t->x2 = xx2;
	t->y2 = yy2;
	t->z2 = zz2;

	t->x3 = xx3;
	t->y3 = yy3;
	t->z3 = zz3;

	return t;
}


Triangulo trianguloInit()
{
	auto t = (Triangulo)malloc(sizeof(struct triangulo));

	return t;
}

float getX1(Triangulo t) { return t->x1; }
float getX2(Triangulo t) { return t->x2; }
float getX3(Triangulo t) { return t->x3; }

float getY1(Triangulo t) { return t->y1; }
float getY2(Triangulo t) { return t->y2; }
float getY3(Triangulo t) { return t->y3; }

float getZ1(Triangulo t) { return t->z1; }
float getZ2(Triangulo t) { return t->z2; }
float getZ3(Triangulo t) { return t->z3; }


////////////----------- STRUCT THREE_POINT_SET -----------////////////
////////////----------- STRUCT THREE_POINT_SET -----------////////////
////////////----------- STRUCT THREE_POINT_SET -----------////////////
typedef struct threePointSet
{
	float pointX;
	float pointY;
	float pointZ;

}threePointSet;

TPS newControlPoint(float x, float y, float z) {
	TPS ins = (TPS)malloc(sizeof(struct threePointSet));
	ins->pointX = x;
	ins->pointY = y;
	ins->pointZ = z;

	return ins;
}

float getPX(TPS t) { return t->pointX; }
float getPY(TPS t) { return t->pointY; }
float getPZ(TPS t) { return t->pointZ; }
