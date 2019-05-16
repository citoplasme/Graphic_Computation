#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>

#endif

#ifdef _WIN32
#define line1 ""
#else
#define line1 "../../SistemaSolar/"
#include <zconf.h>
#endif

#define _USE_MATH_DEFINES

#include "draw.h"
using namespace std;

float alfa = 0.0f, beta = 0.5f, radius = 700.0f;
float camX, camY, camZ;
float refX=0,refY=0,refZ=0;
int timebase = 0, frame = 0;

struct globalInfo
{
    std::vector<parseXML> xmlInfo;
    long size = 0; //numero de ficheiros xml a ler

    std::vector<figura> figuras;

    std::vector<lighting> luzes;

    int loadValue = 0; // se for igual a 0, ainda nao se leu os ficheiros, se for 1, ja se leu os ficheiros

    std::vector<lightSource> lightInfo;

};

GLuint* buff;
GLuint* normBuff;
GLuint* textBuff;
GLuint* vertexcount;
GLuint* texture;

int imageWidth;
unsigned char *imageData;

int totFig = 0;

std::vector<std::vector<int>> filhos;

globalInfo glinf;

float defD[4] = {0.8, 0.8, 0.8, 1.0};
float defS[4] = {0.0, 0.0, 0.0, 1.0};
float defE[4] = {0.0, 0.0, 0.0, 1.0};
float defA[4] = {0.2, 0.2, 0.2, 1.0};

// ------------------------------------------------------------------------------------------------------

void buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float *a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}


float length(float *v) {

	float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return res;

}

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}


void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };

	float a[3][4];
	// Compute A = M * P
  //float *v[4] = {p0, p1, p2, p3 };
	float x[4] = { p0[0],p1[0],p2[0],p3[0] };
	float y[4] = { p0[1],p1[1],p2[1],p3[1] };
	float z[4] = { p0[2],p1[2],p2[2],p3[2] };
	multMatrixVector(m[0], x, a[0]);
	multMatrixVector(m[0], y, a[1]);
	multMatrixVector(m[0], z, a[2]);

	// Compute pos = T * A
	float T[4] = { (float)pow((double)t,3), (float)pow((double)t,2), t, 1 };
	pos[0] = { T[0] * a[0][0] + T[1] * a[0][1] + T[2] * a[0][2] + T[3] * a[0][3] };
	pos[1] = { T[0] * a[1][0] + T[1] * a[1][1] + T[2] * a[1][2] + T[3] * a[1][3] };
	pos[2] = { T[0] * a[2][0] + T[1] * a[2][1] + T[2] * a[2][2] + T[3] * a[2][3] };

	float d[4] = { (float)pow((double)3 * t,2), 2 * t, 1, 1 };
	deriv[0] = { d[0] * a[0][0] + d[1] * a[1][0] + d[2] * a[2][0] + d[3] * a[3][0] };
	deriv[1] = { d[0] * a[0][1] + d[1] * a[1][1] + d[2] * a[2][1] + d[3] * a[3][1] };
	deriv[2] = { d[0] * a[0][2] + d[1] * a[1][2] + d[2] * a[2][2] + d[3] * a[3][2] };


}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, float p[][3], int size) {

	float t = gt * size; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + size - 1) % size;
	indices[1] = (indices[0] + 1) % size;
	indices[2] = (indices[1] + 1) % size;
	indices[3] = (indices[2] + 1) % size;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

// ------------------------------------------------------------------------------------------------------

int coordsToArray(vector<TPS> points, float curvePoints[][3])
{
	int i = 0;
	vector<TPS>::iterator it;

	for (it = points.begin(); it != points.end(); it++) {
		TPS aux = *it;

		curvePoints[i][0] = getPX(aux);
		curvePoints[i][1] = getPY(aux);
		curvePoints[i][2] = getPZ(aux);

		i++;
	}

	return i;
}

typedef float float_arr[3];

void translateTime(figura f, int i){
	static float tt[20];
	static float time = 0;
	static float elapsedTime[20];
	int size;
	float tf = f.getTrTime();
	float_arr* curvePoints = new float_arr[f.getTranslates().size()];

	size = coordsToArray(f.getTranslates(), curvePoints);

	float pos[4];
	float deriv[4];

	//glBegin(GL_LINE_LOOP);
	int npoints = 100;
	for (int i = 0; i < npoints; i++) {
		getGlobalCatmullRomPoint((double)i / npoints, pos, deriv, curvePoints, size);
		glVertex3d(pos[0], pos[1], pos[2]);
	}
	glEnd();

	getGlobalCatmullRomPoint(tt[i], pos, deriv, curvePoints, size);

	// Ver o tempo
	if (time < totFig) {
		double ttt = glutGet(GLUT_ELAPSED_TIME);
		elapsedTime[i] = 1 / (f.getTrTime() * 1000);
		time++;
	}
	tt[i] += elapsedTime[i];

	glTranslatef(pos[0], pos[1], pos[2]);

}

void rotateTime(figura f, int i){

	float time = f.getRtime();

	float static angle[20];

	angle[i] += 360 / (time * 1000);
	//float x = glutGet(GLUT_ELAPSED_TIME) % (int) (time * 1000);
	//angle[i] = (x*360) / (time * 1000);

	glRotatef(angle[i], f.getRx(), f.getRy(), f.getRz());
}

// ------------------------------------------------------------------------------------------------------


int num_de_fig_filhos(parseXML pai)
{
    int tut = 0;
    std::vector<parseXML> filhos = pai.getFilhos();
    for(unsigned i = 0; i < filhos.size() ;i++){
        parseXML filho = filhos.at(i);
        tut+=num_de_fig_filhos(filho);
        tut+=1;
    }
    return tut;
}
int numero_de_figuras()
{
    int tot = 0;

    for(unsigned i = 0; i < glinf.xmlInfo.size() ;i++)
    {
        parseXML info = glinf.xmlInfo.at(i);

        tot += num_de_fig_filhos(info);
        tot += 1;
    }

    return tot;
}

void loadTexture(std::string tex,int figWeOn) {

    unsigned int t, tw, th;
    unsigned char *texData;
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring) tex.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texture[figWeOn]);

    glBindTexture(GL_TEXTURE_2D, texture[figWeOn]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

    glGenerateMipmap(GL_TEXTURE_2D);

}

void initTexture(lighting ll,int figWeOn) {

    unsigned int ima[1];

    std::string tex = line1 + ll.getTexture();

    ilInit();
    ilGenImages(1, ima);
    ilBindImage(ima[0]);
    ilLoadImage((ILstring) tex.c_str());
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);

    imageWidth = ilGetInteger(IL_IMAGE_HEIGHT);
    imageData = ilGetData();
    printf("\nImage: %s\n", ll.getTexture().c_str());

    loadTexture(tex,figWeOn);

    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

}

void loadFilhos(parseXML pai,int* figWeOn2)
{
    FILE *fp,*nfp,*tfp;
    int read;
    int tot = 0;
    float x,y,z;
    std::vector<float> fVec;
    std::vector<float> nVec;
    std::vector<float> tVec;

    std::vector<parseXML> filhos = pai.getFilhos();

    for (unsigned i = 0; i < filhos.size(); i++) {
        parseXML filho = filhos.at(i);
        std::vector<std::string> xmls = filho.getXMLS();

        for (unsigned k = 0; k < xmls.size(); k++) {
            std::string line2 = xmls.at(k);
            std::string final = line1 + line2;
            std::string name = line2.substr(0,line2.size()-3);
            std::string norm = line1 + (name + ".normals");
            std::string text = line1 + (name + ".coords");

            fp = fopen(final.c_str(),"r");
            nfp = fopen(norm.c_str(),"r");
            tfp = fopen(text.c_str(),"r");

            if (!fp || !nfp || !tfp){
                printf("can't open file %s\n", name.c_str());
                _exit(1);
            }else {
                fscanf(fp,"%d",&tot);

                while(!(feof(fp))){
                    read = fscanf(fp,"%f %f %f",&x,&y,&z);

                    if(read == 3){
                        fVec.push_back(x);
                        fVec.push_back(y);
                        fVec.push_back(z);
                    }
                }
                while(!(feof(nfp))){
                    read = fscanf(nfp,"%f %f %f",&x,&y,&z);

                    if(read == 3){
                        nVec.push_back(x);
                        nVec.push_back(y);
                        nVec.push_back(z);
                    }
                }
                while(!(feof(tfp))){
                    read = fscanf(tfp,"%f %f",&x,&y);

                    if(read == 2){
                        tVec.push_back(x);
                        tVec.push_back(y);
                    }
                }
                vertexcount[*figWeOn2] = (GLuint) fVec.size();
                glGenBuffers(1, &buff[*figWeOn2]);
                glBindBuffer(GL_ARRAY_BUFFER, buff[*figWeOn2]);
                glBufferData(GL_ARRAY_BUFFER,sizeof(float) * fVec.size(),&fVec[0],GL_STATIC_DRAW);

                glGenBuffers(1, &normBuff[*figWeOn2]);
                glBindBuffer(GL_ARRAY_BUFFER, normBuff[*figWeOn2]);
                glBufferData(GL_ARRAY_BUFFER,sizeof(float) * nVec.size(),&nVec[0],GL_STATIC_DRAW);

                glGenBuffers(1, &textBuff[*figWeOn2]);
                glBindBuffer(GL_ARRAY_BUFFER, textBuff[*figWeOn2]);
                glBufferData(GL_ARRAY_BUFFER,sizeof(float) * tVec.size(),&tVec[0],GL_STATIC_DRAW);

                initTexture(filho.getLights().at(k),*figWeOn2);

                glinf.luzes.push_back(filho.getLights().at(k));

                *figWeOn2+=1;
                fVec.clear();
                nVec.clear();
                tVec.clear();;
            }
        }
        figura putIn(filho.getFilhos().size(),tot,filho.getTrTime(),filho.getTranslates(),filho.getLights(),filho.getTrx(),filho.getTry(),filho.getTrz(),filho.getRtime(),filho.getRa(),filho.getRx(),filho.getRy(),filho.getRz(),filho.getSx(),filho.getSy(),filho.getSz(),filho.getTorder(),filho.getRorder(),filho.getSorder());
        glinf.figuras.push_back(putIn);
        loadFilhos(filho,figWeOn2);
    }
}

void loadObj()
{
    FILE *fp,*nfp,*tfp;
    int read;
    int tot = 0;
    int figWeOn = 0;
    float x,y,z;

    int nFig =  numero_de_figuras();
    buff = {};
    vertexcount = {};
    normBuff = {};
    textBuff = {};
    texture = {};
    buff = new GLuint [nFig];
    vertexcount = new GLuint [nFig];
    normBuff = new GLuint [nFig];
    textBuff = new GLuint [nFig];
    texture = new GLuint [nFig];
    totFig = nFig;
    std::vector<float> fVec;
    std::vector<float> nVec;
    std::vector<float> tVec;


    for (unsigned i = 0 ;i < glinf.size; i++){
        parseXML info = glinf.xmlInfo.at(i);
        std::vector<std::string> xmls = info.getXMLS();

        for (unsigned k = 0 ;k < xmls.size(); k++){
            std::string line2 = xmls.at(k);
            std::string final = line1 + line2;
            std::string name = line2.substr(0,line2.size()-3);
            std::string norm = line1 + (name + ".normals");
            std::string text = line1 + (name + ".coords");

            fp = fopen(final.c_str(),"r");
            nfp = fopen(norm.c_str(),"r");
            tfp = fopen(text.c_str(),"r");

            if (!fp || !nfp || !tfp){
                printf("can't open file %s\n", name.c_str());
                _exit(1);
            }
            else{
                fscanf(fp,"%d",&tot);

                while(!(feof(fp))){
                    read = fscanf(fp,"%f %f %f",&x,&y,&z);

                    if(read == 3){
                        fVec.push_back(x);
                        fVec.push_back(y);
                        fVec.push_back(z);
                    }
                }
                while(!(feof(nfp))){
                    read = fscanf(nfp,"%f %f %f",&x,&y,&z);

                    if(read == 3){
                        nVec.push_back(x);
                        nVec.push_back(y);
                        nVec.push_back(z);
                    }
                }
                while(!(feof(tfp))){
                    read = fscanf(tfp,"%f %f",&x,&y);

                    if(read == 2){
                        tVec.push_back(x);
                        tVec.push_back(y);
                    }
                }

                vertexcount[figWeOn] = (GLuint) fVec.size();
                glGenBuffers(1, &buff[figWeOn]);
                glBindBuffer(GL_ARRAY_BUFFER, buff[figWeOn]);
                glBufferData(GL_ARRAY_BUFFER,sizeof(float) * fVec.size(),&fVec[0],GL_STATIC_DRAW);

                glGenBuffers(1, &normBuff[figWeOn]);
                glBindBuffer(GL_ARRAY_BUFFER, normBuff[figWeOn]);
                glBufferData(GL_ARRAY_BUFFER,sizeof(float) * nVec.size(),&nVec[0],GL_STATIC_DRAW);

                glGenBuffers(1, &textBuff[figWeOn]);
                glBindBuffer(GL_ARRAY_BUFFER, textBuff[figWeOn]);
                glBufferData(GL_ARRAY_BUFFER,sizeof(float) * tVec.size(),&tVec[0],GL_STATIC_DRAW);

                initTexture(info.getLights().at(k),figWeOn);

                glinf.luzes.push_back(info.getLights().at(k));

                figWeOn+=1;
                fVec.clear();
                nVec.clear();
                tVec.clear();
            }
        }
        figura putIn(info.getFilhos().size(),tot,info.getTrTime(),info.getTranslates(),info.getLights(),info.getTrx(),info.getTry(),info.getTrz(),info.getRtime(),info.getRa(),info.getRx(),info.getRy(),info.getRz(), info.getSx(), info.getSy(), info.getSz(), info.getTorder(), info.getRorder(), info.getSorder());
        glinf.figuras.push_back(putIn);
        loadFilhos(info,&figWeOn);
    }
}

void spherical2Cartesian() {

    camX = radius * cos(beta) * sin(alfa);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alfa);
}

void drawFilhos(figura pai,int* drawnFigures){
    glColor3f(0,1,0);
    int filhos = pai.getFilhos();
    for(unsigned i = 0 ;i<filhos; i++){
        figura info = glinf.figuras.at((unsigned long) *drawnFigures);

        lighting ls = glinf.luzes.at((unsigned long) *drawnFigures);

        if(ls.getDV() == 1) {
            float put[4] = {ls.getDR(), ls.getDG(), ls.getDB(), 1.0};
            glMaterialfv(GL_FRONT, GL_DIFFUSE, put);
        }
        if(ls.getSV() == 1) {
            float put[4] = {ls.getSR(), ls.getSG(), ls.getSB(), 1.0};
            glMaterialfv(GL_FRONT, GL_SPECULAR, put);
        }
        if(ls.getEV() == 1) {
            float put[4] = {ls.getER(), ls.getEG(), ls.getEB(), 1.0};
            glMaterialfv(GL_FRONT, GL_EMISSION, put);
        }
        if(ls.getAV() == 1) {
            float put[4] = {ls.getAR(), ls.getAG(), ls.getAB(), 1.0};
            glMaterialfv(GL_FRONT, GL_AMBIENT, put);
        }

        glPushMatrix();
        for(int i = 1 ; i<=3 ;i++) {
			if (info.getTorder() == i) {
				if (info.getTranslates().size() == 0) {
					glTranslatef(info.getTrx(), info.getTry(), info.getTrz());
				}
				else {
					translateTime(info, *drawnFigures);
				}
			}
       
			if (info.getRorder() == i) {
				if (info.getRtime() == 0) {
					glRotatef(info.getRa(), info.getRx(), info.getRy(), info.getRz());
				}
				else {
					rotateTime(info, *drawnFigures);
				}
			}
                
            if(info.getSorder() == i)
                glScalef(info.getSx(), info.getSy(), info.getSz());
        }

        glBindTexture(GL_TEXTURE_2D, texture[*drawnFigures]);
        glBindBuffer(GL_ARRAY_BUFFER,buff[*drawnFigures]);
        glVertexPointer(3,GL_FLOAT,0,0);

        glBindBuffer(GL_ARRAY_BUFFER, normBuff[*drawnFigures]);
        glNormalPointer(GL_FLOAT, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, textBuff[*drawnFigures]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);

        glDrawArrays(GL_TRIANGLES,0,vertexcount[*drawnFigures]);

        glBindTexture(GL_TEXTURE_2D,0);

        *drawnFigures+=1;

        drawFilhos(info,drawnFigures);

        glPopMatrix();

        if(ls.getDV() == 1)
            glMaterialfv(GL_FRONT, GL_DIFFUSE, defD);
        if(ls.getEV() == 1)
            glMaterialfv(GL_FRONT, GL_EMISSION, defE);
        if(ls.getSV() == 1)
            glMaterialfv(GL_FRONT, GL_SPECULAR, defS);
        if(ls.getAV() == 1)
            glMaterialfv(GL_FRONT, GL_AMBIENT, defA);
    }
}

void draw(){
    int drawnFigures = 0;
    while(drawnFigures < totFig){
        figura info = glinf.figuras.at((unsigned long) drawnFigures);

        lighting ls = glinf.luzes.at((unsigned long) drawnFigures);

        if(ls.getDV() == 1) {
            float put[4] = {ls.getDR(), ls.getDG(), ls.getDB(), 1.0};
            glMaterialfv(GL_FRONT, GL_DIFFUSE, put);
        }
        if(ls.getSV() == 1) {
            float put[4] = {ls.getSR(), ls.getSG(), ls.getSB(), 1.0};
            glMaterialfv(GL_FRONT, GL_SPECULAR, put);
        }
        if(ls.getEV() == 1) {
            float put[4] = {ls.getER(), ls.getEG(), ls.getEB(), 1.0};
            glMaterialfv(GL_FRONT, GL_EMISSION, put);
        }
        if(ls.getAV() == 1) {
            float put[4] = {ls.getAR(), ls.getAG(), ls.getAB(), 1.0};
            glMaterialfv(GL_FRONT, GL_AMBIENT, put);
        }

        glPushMatrix();
        for(int i = 1 ; i<=3 ;i++) {
			if (info.getTorder() == i) {
				if (info.getTranslates().size() == 0) {
					glTranslatef(info.getTrx(), info.getTry(), info.getTrz());
				}
				else {
					translateTime(info,drawnFigures);
				}
			}

			if (info.getRorder() == i) {
				if (info.getRtime() == 0) {
					glRotatef(info.getRa(), info.getRx(), info.getRy(), info.getRz());
				}
				else {
					rotateTime(info, drawnFigures);
				}
			}
                

            if(info.getSorder() == i)
                glScalef(info.getSx(), info.getSy(), info.getSz());
        }

        glBindTexture(GL_TEXTURE_2D, texture[drawnFigures]);
		glBindBuffer(GL_ARRAY_BUFFER,buff[drawnFigures]);
        glVertexPointer(3,GL_FLOAT,0,0);

        glBindBuffer(GL_ARRAY_BUFFER, normBuff[drawnFigures]);
        glNormalPointer(GL_FLOAT, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, textBuff[drawnFigures]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);

        glDrawArrays(GL_TRIANGLES,0,vertexcount[drawnFigures]);

        glBindTexture(GL_TEXTURE_2D,0);

        drawnFigures++;

        drawFilhos(info,&drawnFigures);

        glPopMatrix();

        if(ls.getDV() == 1)
            glMaterialfv(GL_FRONT, GL_DIFFUSE, defD);
        if(ls.getEV() == 1)
            glMaterialfv(GL_FRONT, GL_EMISSION, defE);
        if(ls.getSV() == 1)
            glMaterialfv(GL_FRONT, GL_SPECULAR, defS);
        if(ls.getAV() == 1)
            glMaterialfv(GL_FRONT, GL_AMBIENT, defA);
    }
}

void initLightSource()
{
    for(int i = 0; i < glinf.lightInfo.size() ;i++) {
        glEnable(GL_LIGHT0 + i);
        lightSource ls = glinf.lightInfo.at(i);
        std::string lType = ls.getType();

        if (lType.compare("POINT") == 0) {

            GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
            GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};
            float light[4] = {ls.getPointX(), ls.getPointY(), ls.getPointZ(), 1.0};

            glLightfv(GL_LIGHT0 + i, GL_POSITION, light);
            glLightfv(GL_LIGHT0 + i, GL_AMBIENT, amb);
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diff);
        }

        if (lType.compare("DIRECTIONAL") == 0) {

            GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
            GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};
            float light[4] = {ls.getDirX(), ls.getDirY(), ls.getDirZ(), 0.0};

            glLightfv(GL_LIGHT0 + i, GL_POSITION, light);
            glLightfv(GL_LIGHT0 + i, GL_AMBIENT, amb);
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diff);
        }

        if (lType.compare("SPOT") == 0) {

            GLfloat amb[4] = {0.2, 0.2, 0.2, 1.0};
            GLfloat diff[4] = {1.0, 1.0, 1.0, 1.0};
            float spotPos[4] = {ls.getPointX(), ls.getPointY(), ls.getPointZ(),1.0};
            float spotDir[3] = {ls.getDirX(), ls.getDirY(), ls.getDirZ()};

            glLightfv(GL_LIGHT0 + i,GL_POSITION,spotPos);
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diff);
            glLightfv(GL_LIGHT0 + i, GL_AMBIENT, amb);
            glLightfv(GL_LIGHT0 + i,GL_SPOT_DIRECTION,spotDir);
            glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, ls.getPhi()); // [0,90] ou 180
            glLightf(GL_LIGHT0 + i,GL_SPOT_EXPONENT, ls.getTheta()); // [0,128]
        }
    }
}

void renderScene(void) {

    static float gTime = 0;

    float fps;
    int time;
    char s[64];

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMaterialf(GL_FRONT,GL_SHININESS,180);

    if(glinf.loadValue == 0)
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        loadObj();
        glinf.loadValue = 1;
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        spherical2Cartesian();
    }

    // set the camera
    glLoadIdentity();
    gluLookAt(camX+refX, camY+refY, camZ+refZ,
              refX, refY, refZ,
              0.0f, 1.0f, 0.0f);

    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000) {
        fps = frame*1000.0/(time-timebase);
        timebase = time;
        frame = 0;
        sprintf(s, "FPS: %f6.2", fps);
        glutSetWindowTitle(s);
    }

    //glColor3f(0.976, 0.384, 0.160);

    glColor3f(1,1,1);

    draw();

    initLightSource();

	// End of frame
	glutSwapBuffers();

	gTime += 0.001;

}

void processKeys(unsigned char c, int xx, int yy){
    switch (c) {
        case 'w': {
            refZ -= 5 * cos(alfa);
            refX -= 5 * sin(alfa);
        } break;
        case 's': {
            refZ += 5 * cos(alfa);
            refX += 5 * sin(alfa);
        } break;

        case 'd': {
            refX += 5 * cos(alfa);
            refZ += 5 * (-sin(alfa));
        } break;
        case 'a': {
            refX -= 5 * cos(alfa);
            refZ -= 5 * (-sin(alfa));
        } break;
        case 'q': {
            refY +=3;
        } break;
        case 'e': {
            refY -=3;
        } break;
        case '-': {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } break;
        case '.': {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        } break;
        case ',': {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } break;
    }

    glutPostRedisplay();
}
void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {

        case GLUT_KEY_RIGHT:
            alfa -= 0.01; break;

        case GLUT_KEY_LEFT:
            alfa += 0.01; break;

        case GLUT_KEY_UP:
            beta += 0.1f;
            if (beta > 1.5f)
                beta = 1.5f;
            break;

        case GLUT_KEY_DOWN:
            beta -= 0.1f;
            if (beta < -1.5f)
                beta = -1.5f;
            break;

        case GLUT_KEY_PAGE_DOWN: radius -= 5.0f;
            if (radius < 1.0f)
                radius = 1.0f;
            break;

        case GLUT_KEY_PAGE_UP: radius += 5.0f; break;
    }
    spherical2Cartesian();
    glutPostRedisplay();

}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,10000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void startDrawing(std::vector<parseXML> xmls,std::vector<lightSource> light ,int argc,char **argv) {

    glinf.xmlInfo = xmls;
    glinf.size = xmls.size();
    glinf.loadValue = 0;
    glinf.lightInfo = light;

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
	
// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

}

