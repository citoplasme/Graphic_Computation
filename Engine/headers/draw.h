#ifndef LOADER_DRAW_H
#define LOADER_DRAW_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "tinyxml2.h"
#include "structure.h"
#include "parseXML.h"
#include "figura.h"
#include "lightSource.h"

//void getPontos(std::vector<parseXML> xmls,long size,int pontos[]);

void startDrawing(std::vector<parseXML> xmls,std::vector<lightSource> light,int argc,char **argv);

#endif //LOADER_DRAW_H
