#ifndef LOADER_PARSE_H
#define LOADER_PARSE_H

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
#include "parseXML.h"
#include "lightSource.h"


std::vector<parseXML> getXML(std::string ficheiro);
std::vector<lightSource> getLight(std::string ficheiro);

#endif //LOADER_PARSE_H
