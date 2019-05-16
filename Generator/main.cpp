#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

void normalize(float *v) {
    float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (res == 0.0f)
        return;
    
    v[0] = v[0] / res;
    v[1] = v[1] / res;
    v[2] = v[2] / res;
}

void cross(float *a, float *b, float *res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


// Orientacao 1 up, -1 down
string drawPlanoYZ(float x, float y, float z, int divs, int orientacao) {
	ostringstream os;
	float deltaY = y / divs;
	float deltaZ = z / divs;
	int linhas = 0;
	y = y / 2;
	z = z / 2;
	float yi = -y;
	float zi = -z;

	
	for (int i = 1; i <= divs; i++) {
		for (int j = 1; j <= divs; j++) {
			if (orientacao == 1) {
				os << x << " " << yi << " " << zi << '\n';
				os << x << " " << (yi + deltaY) << " " << zi << '\n';
				os << x << " " << (yi + deltaY) << " " << (zi + deltaZ) << '\n';

				os << x << " " << yi << " " << zi << '\n';
				os << x << " " << (yi + deltaY) << " " << (zi + deltaZ) << '\n';
				os << x << " " << yi << " " << (zi + deltaZ) << '\n';
			}
			else {
				os << x << " " << yi << " " << zi << '\n';
				os << x << " " << yi << " " << (zi + deltaZ) << '\n';
				os << x << " " << (yi + deltaY) << " " << (zi + deltaZ) << '\n';

				os << x << " " << yi << " " << zi << '\n';;
				os << x << " " << (yi + deltaY) << " " << (zi + deltaZ) << '\n';
				os << x << " " << (yi + deltaY) << " " << zi << '\n';
			}
			linhas += 6;
			zi = -z + j * deltaZ;
		}
		yi = -y + i * deltaY;
		zi = -z;
	}
	return to_string(linhas) + "\n" + os.str();
}

string plano_YZ_normais (int nDiv, int orient) {
    ostringstream os;
    for (int i = 1; i <= nDiv; i++) {
        for (int j = 1; j <= nDiv; j++) {
            for (int k = 1; k <= 6; k++) {
                os << orient << " 0.0 0.0\n";
            }
        }
    }
    return os.str();
}

// Orientacao 1 up, -1 down
string drawPlanoXY(float x, float y, float z, int divs, int orientacao) {
	ostringstream os;
	float deltaX = x / divs;
	float deltaY = y / divs;
	int linhas = 0;
	y = y / 2;
	x = x / 2;
	float yi = -y;
	float xi = x;

	for (int i = 1; i <= divs; i++) {
		for (int j = 1; j <= divs; j++) {
			if (orientacao == 1) {
				os << xi << " " << yi << " " << z << '\n';
				os << xi << " " << (yi + deltaY) << " " << z << '\n';
				os << (xi - deltaX) << " " << (yi + deltaY) << " " << z << '\n';

				os << xi << " " << yi << " " << z << '\n';
				os << (xi - deltaX) << " " << (yi + deltaY) << " " << z << '\n';
				os << (xi - deltaX) << " " << yi << " " << z << '\n';
			}
			else {
				os << xi << " " << yi << " " << z << '\n';
				os << (xi - deltaX) << " " << yi << " " << z << '\n';
				os << (xi - deltaX) << " " << (yi + deltaY) << " " << z << '\n';

				os << xi << " " << yi << " " << z << '\n';
				os << (xi - deltaX) << " " << (yi + deltaY) << " " << z << '\n';
				os << xi << " " << (yi + deltaY) << " " << z << '\n';
			}
			linhas += 6;
			xi = x - j * deltaX;
		}
		yi = -y + i * deltaY;
		xi = x;
	}
	return to_string(linhas) + "\n" + os.str();
}

string plano_XY_normais (int nDiv, int orient) {
    ostringstream os;
    for (int i = 1; i <= nDiv; i++) {
        for (int j = 1; j <= nDiv; j++) {
            for (int k = 1; k <= 6; k++) {
                os << "0.0 0.0 " << orient << "\n";
            }
        }
    }
    return os.str();
}


// Orientacao 1 up, -1 down
string drawPlanoXZ(float x, float y, float z, int divs, int orientacao) {
	ostringstream os;
	float deltaX = x / divs;
	float deltaZ = z / divs;
	int linhas = 0;
	x = x / 2;
	z = z / 2;
	float xi = x;
	float zi = z;

	
	for (int i = 1; i <= divs; i++) {
		for (int j = 1; j <= divs; j++) {
			if (orientacao == 1) {
				os << xi << " " << y << " " << zi << '\n';
				os << xi << " " << y << " " << (zi - deltaZ) << '\n';
				os << (xi - deltaX) << " " << y << " " << (zi - deltaZ) << '\n';

				os << xi << " " << y << " " << zi << '\n';
				os << (xi - deltaX) << " " << y << " " << (zi - deltaZ) << '\n';
				os << (xi - deltaX) << " " << y << " " << zi << '\n';
			}
			else {
				os << xi << " " << y << " " << zi << '\n';
				os << (xi - deltaX) << " " << y << " " << zi << '\n';
				os << (xi - deltaX) << " " << y << " " << (zi - deltaZ) << '\n';

				os << xi << " " << y << " " << zi << '\n';
				os << (xi - deltaX) << " " << y << " " << (zi - deltaZ) << '\n';
				os << xi << " " << y << " " << (zi - deltaZ) << '\n';
			}
			linhas += 6;
			xi = x - j * deltaX;
		}
		zi = z - i * deltaZ;
		xi = x;
	}
	return to_string(linhas) + "\n" + os.str();
}

string plano_XZ_normais (int nDiv, int orient) {
    ostringstream os;
    for (int i = 1; i <= nDiv; i++) {
        for (int j = 1; j <= nDiv; j++) {
            for (int k = 1; k <= 6; k++) {
                os << "0.0 " << orient << " 0.0\n";
            }
        }
    }
    return os.str();
}




string plano_TexCoords(int nDiv, int orient) {
    ostringstream os;
    float deltaS = 1.0f / nDiv;
    float deltaT = 1.0f / nDiv;

    float s = 1.0f;
    float t = 0.0f;

    for (int i = 1; i <= nDiv; i++) {
        for (int j = 1; j <= nDiv; j++) {
            if (orient == 1) {
                os << s << " " << t << "\n";
                os << s << " " << (t + deltaT) << "\n";
                os << (s - deltaS) << " " << (t + deltaT) << "\n";

                os << s << " " << t << "\n";
                os << (s - deltaS) << " " << (t + deltaT) << "\n";
                os << (s - deltaS) << " " << t << "\n";
            }
            else {
                os << s << " " << t << '\n';
                os << (s - deltaS) << " " << t << '\n';
                os << (s - deltaS) << " " << (t + deltaT) << '\n';

                os << s << " " << t << '\n';
                os << (s - deltaS) << " " << (t + deltaT) << '\n';
                os << s << " " << (t + deltaT) << '\n';
            }
            s = 1.0f - j * deltaS;
        }
        t = i * deltaT;
        s = 1.0f;
    }
    return os.str();
}




string drawBox(float x, float y, float z, int divs) {
	int linhas;
	string plano, linha;
	ostringstream os;
	istringstream in;
	
	plano = drawPlanoXY(x,y,z/2,divs,1);
	istringstream in1(plano);
	getline(in1, linha);
	linhas = stoi(linha, nullptr, 10);
	while (getline(in1, linha)) {
		os << linha << '\n';
	}
	plano = drawPlanoXY(x, y, -z / 2, divs, 0);
	istringstream in2(plano);
	getline(in2, linha);
	linhas += stoi(linha, nullptr, 10);
	while (getline(in2, linha)) {
		os << linha << '\n';
	}
	plano = drawPlanoXZ(x, y/2, z, divs, 1);
	istringstream in3(plano);
	getline(in3, linha);
	linhas += stoi(linha, nullptr, 10);
	while (getline(in3, linha)) {
		os << linha << '\n';
	}
	plano = drawPlanoXZ(x, -y/2, z, divs, 0);
	istringstream in4(plano);
	getline(in4, linha);
	linhas += stoi(linha, nullptr, 10);
	while (getline(in4, linha)) {
		os << linha << '\n';
	}
	plano = drawPlanoYZ(x/2, y, z, divs, 1);
	istringstream in5(plano);
	getline(in5, linha);
	linhas += stoi(linha, nullptr, 10);
	while (getline(in5, linha)) {
		os << linha << '\n';
	}
	plano = drawPlanoYZ(-x/2, y, z, divs, 0);
	istringstream in6(plano);
	getline(in6, linha);
	linhas += stoi(linha, nullptr, 10);
	while (getline(in6, linha)) {
		os << linha << '\n';
	}
	return to_string(linhas) + "\n" + os.str();
}

string box_Normais(int nDiv) {
    string normals, line;
    ostringstream os;
    istringstream iss;

    normals = plano_XY_normais(nDiv, 1);
    istringstream iss1(normals);
    while (getline(iss1, line)) {
        os << line << '\n';
    }
    normals = plano_XY_normais(nDiv, -1);
    istringstream iss2 (normals);
    while (getline(iss2, line)) {
        os << line << '\n';
    }
    normals = plano_XZ_normais(nDiv, 1);
    istringstream iss3 (normals);
    while (getline(iss3, line)) {
        os << line << '\n';
    }
    normals = plano_XZ_normais(nDiv, -1);
    istringstream iss4 (normals);
    while (getline(iss4, line)) {
        os << line << '\n';
    }
    normals = plano_YZ_normais(nDiv, 1);
    istringstream iss5 (normals);
    while (getline(iss5, line)) {
        os << line << '\n';
    }
    normals = plano_YZ_normais(nDiv, -1);
    istringstream iss6 (normals);
    while (getline(iss6, line)) {
        os << line << '\n';
    }
    return os.str();
}


string box_TexCoords(int nDiv) {
    string up = plano_TexCoords(nDiv, 1);
    string down = plano_TexCoords(nDiv, -1);

    return up + down + up +
           down + up + down;
}


string drawCone(float raio, float altura, int fatias, int stacks) {

	float ang = (2 * M_PI) / fatias;
	float descRaio = raio / stacks;
	float distCirc = altura / stacks;
	float totRaio = 0;float totAltura = 0;
	int linhas = 0;
	ostringstream os;

	for (int src = 0; src < stacks; src++) {
		totRaio = raio - (descRaio * src);
		totAltura = -2 + (distCirc * src);

		for (int prc = 0; prc < fatias; prc++) {
			if (totAltura == -2) {
				os << 0.0f << " " << totAltura << " " << 0.0f << '\n';
				os << totRaio * sin(ang * (prc + 1)) << " " << totAltura << " " << totRaio * cos(ang * (prc + 1)) << '\n';
				os << totRaio * sin(ang * prc) << " " << totAltura << " " << totRaio * cos(ang * prc) << '\n';
				linhas += 3;
			}
			
			os << totRaio * sin(ang * prc) << " " << totAltura << " " << totRaio * cos(ang * prc) << '\n';
			os << totRaio * sin(ang * (prc + 1)) << " " << totAltura << " " << totRaio * cos(ang * (prc + 1)) << '\n';
			os << (totRaio - descRaio) * sin(ang * (prc + 1)) << " " << totAltura + distCirc << " " << (totRaio - descRaio) * cos(ang * (prc + 1)) << '\n';
			linhas += 3;
			if (src < stacks - 1) {
				os << totRaio * sin(ang * prc) << " " << totAltura << " " << totRaio * cos(ang * prc) << '\n';
				os << (totRaio - descRaio) * sin(ang * (prc + 1)) << " " << totAltura + distCirc << " " << (totRaio - descRaio) * cos(ang * (prc + 1)) << '\n';
				os << (totRaio - descRaio) * sin(ang * prc) << " " << totAltura + distCirc << " " << (totRaio - descRaio) * cos(ang * prc) << '\n';
				linhas+=3;
			}
		}
	}
	return to_string(linhas) + "\n" + os.str();
}


string cone_Normais(float raio, float altura, int fatias, int stacks){
	
	//if(base) 0 -1 0 

	//if(corpo) PQ x QR 3 pontos

	float ang = (2 * M_PI) / fatias;
	float descRaio = raio / stacks;
	float distCirc = altura / stacks;
	float totRaio = 0;float totAltura = 0;
	ostringstream os;


	for (int i = 0; i < stacks; i++) {
		totRaio = raio - (descRaio * i);
		totAltura = -2 + (distCirc * i);

		for (int j = 0; j < fatias; j++) {
			if (totAltura == -2) { // Base
				os << 0.0f << " " << -1.0f << " " << 0.0f << "\n";
				os << 0.0f << " " << -1.0f << " " << 0.0f << "\n";
				os << 0.0f << " " << -1.0f << " " << 0.0f << "\n";
			}
			
				float p[3] = { totRaio * sin(ang * j), totAltura, totRaio * cos(ang * j)};
				float q[3] = { totRaio * sin(ang * (j + 1)), totAltura, totRaio * cos(ang * (j + 1))};
				float r[3] = { (totRaio - descRaio) * sin(ang * (j + 1)), totAltura + distCirc, (totRaio - descRaio) * cos(ang * (j + 1))};
			
				float pq[3] = {q[0] - p[0], q[1] - p[1], q[2] - p[2]};
				float pr[3] = {r[0] - p[0], r[1] - p[1], r[2] - p[2]};

				float normal[3];
				cross(pq, pr, normal);
				normalize(normal);

				os << normal[0] << " " << normal[1] << " " << normal[2] << "\n";
				os << normal[0] << " " << normal[1] << " " << normal[2] << "\n";
				os << normal[0] << " " << normal[1] << " " << normal[2] << "\n";
			if (i < stacks - 1){
				float p1[3] = {totRaio * sin(ang * j), totAltura, totRaio * cos(ang * j)};
				float q1[3] = {(totRaio - descRaio) * sin(ang * (j + 1)), totAltura + distCirc, (totRaio - descRaio) * cos(ang * (j + 1))};
				float r1[3] = {(totRaio - descRaio) * sin(ang * j), totAltura + distCirc, (totRaio - descRaio) * cos(ang * j)};

				float pq1[3] = {q1[0] - p1[0], q1[1] - p1[1], q1[2] - p1[2]};
				float pr1[3] = {r1[0] - p1[0], r1[1] - p1[1], r1[2] - p1[2]};

				cross(pq1, pr1, normal);
				normalize(normal);

				os << normal[0] << " " << normal[1] << " " << normal[2] << "\n";
				os << normal[0] << " " << normal[1] << " " << normal[2] << "\n";
				os << normal[0] << " " << normal[1] << " " << normal[2] << "\n";
			}
		}
	}	
	return os.str();

}


string cone_TexCoords(float raio, float altura, int fatias, int stacks){
	float vShift = (float)0.625/stacks;
    float uShift = (float)1/fatias;	
    
    float ang = (2 * M_PI) / fatias;
	float descRaio = raio / stacks;
	float distCirc = altura / stacks;
	float totRaio = 0;float totAltura = 0;
	ostringstream os;
	
	float delta = (2.0f * M_PI) / fatias;

    for (int i = 0; i < stacks; i++) {
    	totRaio = raio - (descRaio * i);
		totAltura = -2 + (distCirc * i);

    	for (int j = 0; j < fatias; j++){
    		if (totAltura == -2){ // Base
   				
    			os << 0.8125f << " " << 0.8125f << "\n";
    			os << 0.8125f + 0.1875f*sin(delta*(j+1)) << " " << 0.8125f + 0.1875f*cos(delta*(j+1)) << "\n";
				os <<  0.8125f + 0.1875f *sin(delta*j) << " " << 0.8125f + 0.1875f*cos(delta*j) << "\n";
			}
				os << 1 - (j * uShift) << " " << 0.625f - (i*vShift) << "\n";
    			os << (1-uShift) - (j*uShift) << " " << 0.625f -(i*vShift) << "\n";
				os << (1-uShift) - (j*uShift) << " " << (0.625f-vShift) - (i*vShift)<< "\n";

			if (i < stacks - 1){
                os << 1 - (j * uShift) << " " << 0.625f - (i*vShift) << "\n";
                os << (1-uShift) - (j*uShift) << " " << (0.625f-vShift) - (i*vShift)<< "\n";
                os << 1 - (j * uShift) << " " << (0.625f-vShift) - (i*vShift)<< "\n";
			}
    	}
    }
    return os.str();
}

string drawElipsoide(float a, float b, float c, int fatias, int stacks) {
	float deltaAlpha = (2*M_PI) / fatias;
    float deltaBeta = M_PI / stacks;
    
	int linhas = 0;
	ostringstream os;

    for(int i = 0; i < stacks ; i++) {
		float beta = i * deltaBeta;
		float nextBeta = beta + deltaBeta;
		for(int j = 0; j < fatias; j++) {
			float alpha = j * deltaAlpha;
			float nextAlpha = alpha + deltaAlpha;

			if (i < stacks - 1) {
				os << a * sinf(beta) * sinf(alpha) << " " << b * cosf(beta) << " " << c * sinf(beta) * cosf(alpha) << '\n';
				os << a * sinf(nextBeta) * sinf(alpha) << " " << b * cosf(nextBeta) << " " << c * sinf(nextBeta) * cosf(alpha) << '\n';
				os << a * sinf(nextBeta) * sinf(nextAlpha) << " " << b * cosf(nextBeta) << " " << c * sinf(nextBeta) * cosf(nextAlpha) << '\n';
				linhas += 3;
			}
            
			if (i > 0) {
				os << a * sinf(beta) * sinf(alpha) << " " << b * cosf(beta) << " " << c * sinf(beta) * cosf(alpha) << '\n';
				os << a * sinf(nextBeta) * sinf(nextAlpha) << " " << b * cosf(nextBeta) << " " << c * sinf(nextBeta) * cosf(nextAlpha) << '\n';
				os << a * sinf(beta) * sinf(nextAlpha) << " " << b * cosf(beta) << " " << c * sinf(beta) * cosf(nextAlpha) << '\n';
				linhas += 3;
			}

        }
    }
	return to_string(linhas) + "\n" + os.str();
}

void aux_Normais(float a, float b, float c, float alpha, float beta, ostringstream& os) {
	float n[3] = {
		sinf(beta) * sinf(alpha) / a,
		cosf(beta) / b,
		sinf(beta) * cosf(alpha) / c
	};
	normalize(n);

	os << n[0] << ' ' << n[1] << ' ' << n[2] << '\n';
}

string ellipsoid_Normais(float a, float b, float c, int stacks, int slices) {
    float deltaAlpha = 2.0f * M_PI / slices;
    float deltaBeta = M_PI / stacks;
    ostringstream os;

    for (int i = 0; i < stacks; i++) {
        float beta = i * deltaBeta;
        float nextBeta = beta + deltaBeta;

        for (int j = 0; j < slices; j++) {
            float alpha = j * deltaAlpha;
            float nextAlpha = alpha + deltaAlpha;

            if (i < stacks - 1) {
            	aux_Normais(a, b, c, alpha, beta, os);
            	aux_Normais(a, b, c, alpha, nextBeta, os);
            	aux_Normais(a, b, c, nextAlpha, nextBeta, os);
            }
            if (i > 0) {
                aux_Normais(a, b, c, alpha, beta, os);
                aux_Normais(a, b, c, nextAlpha, nextBeta, os);
                aux_Normais(a, b, c, nextAlpha, beta, os);
            }
        }
    }
    return os.str();
}

string ellipsoid_TexCoords(int stacks, int slices) {
    ostringstream os;
    float deltaS = 1.0f / slices;
    float deltaT = 1.0f / stacks;

    for (int i = 0; i < stacks; ++i) {
        float t = (stacks - i) * deltaT;

        for (int j = 0; j < slices; ++j) {
            float s = j * deltaS;

            if (i < stacks - 1) {
                os << s << ' ' << t << '\n';
                os << s << ' ' << (t - deltaT)  << '\n';
                os << (s + deltaS) << ' ' << (t - deltaT) << '\n';
            }
            if (i > 0) {
                os << s << ' ' << t << '\n';
                os << (s + deltaS) << ' ' << (t - deltaT) << '\n';
                os << (s + deltaS) << ' ' << t << '\n';
            }
        }
    }
    return os.str();
}










string drawAnnulus(float dist, float smj, float smn, int slices) {
	int linhas = 0;
	float deltaAlpha;
	ostringstream os;

	deltaAlpha = (2.0f * M_PI) / slices;
	for (int i = 0; i < slices; ++i) {
		float alpha = i * deltaAlpha;
		float nextAlpha = alpha + deltaAlpha;

		os << smj * cosf(alpha) << " 0.0 " << smn * sinf(alpha) << '\n';
		os << (smj + dist) * cosf(nextAlpha) << " 0.0 " << (smn + dist) * sinf(nextAlpha) << '\n';
		os << (smj + dist) * cosf(alpha) << " 0.0 " << (smn + dist) * sinf(alpha) << '\n';
		os << smj * cosf(alpha) << " 0.0 " << smn * sinf(alpha) << '\n';
		os << smj * cosf(nextAlpha) << " 0.0 " << smn * sinf(nextAlpha) << '\n';
		os << (smj + dist) * cosf(nextAlpha) << " 0.0 " << (smn + dist) * sinf(nextAlpha) << '\n';

        linhas += 6;
	}
	return (to_string(linhas) + "\n" + os.str());
}


string annulus_Normais(int slices) {
    ostringstream os;
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < 6; j++) {
            os << "0.0 1.0 0.0\n";
        }
        
    }
    return os.str();
}

string annulus_TexCoords(int slices) {
    ostringstream os;

    for (int i = 0; i < slices; ++i) {
        os << "1.0 0.0\n";
        os << "0.0 1.0\n";
        os << "0.0 0.0\n";
        os << "1.0 0.0\n";
        os << "1.0 1.0\n";
        os << "0.0 1.0\n";
    }
    return os.str();
}












int annulusGenerate(int argc, char* argv[]) {
	float dist, smj, smn;
	int slices;

	ofstream outfile, outfile2, outfile3;
	dist = atof(argv[0]);
	smj = atof(argv[1]);
	smn = atof(argv[2]);
	slices = atoi(argv[3]);
	if (dist <= 0.0f || smj <= 0.0f || smn <= 0.0f || slices <= 0) {
		fputs("Error: All parameters of the annulus must be positive numbers\n", stderr);
		return 1;
	}

	string s = argv[4];
	string delimiter = ".";
	string token = s.substr(0, s.find(delimiter)); // Ficamos com nome sem a extensão
	string norms = token + ".normals";
	string coords = token + ".coords";

	outfile.open(argv[4]);
	outfile2.open(norms);
	outfile3.open(coords);
	
	if (!outfile.is_open() || !outfile2.is_open() || !outfile3.is_open()) {
		perror("ofstream.open");
		return 1;
	}
	outfile << drawAnnulus(dist, smj, smn, slices);
	outfile2 << annulus_Normais(slices);
	outfile3 << annulus_TexCoords(slices);
	
	outfile.close();
	outfile2.close();
	outfile3.close();
	
	return 0;
}

int boxGenerate(int argc, char *argv[]) {
	float x, y, z;
	int divs;
	ofstream outfile, outfile2, outfile3;

	x = atof(argv[0]);
	y = atof(argv[1]);
	z = atof(argv[2]);
	divs = (argc == 5 ? atoi(argv[3]) : 1);

	if (x <= 0.0f || y <= 0.0f || z <= 0.0f || divs <= 0) {
		fputs("Error: All parameters of the box must be positive numbers\n", stderr);
		return 1;
	}
	string s = (argc == 5) ? argv[4] : argv[3];
	string delimiter = ".";
	string token = s.substr(0, s.find(delimiter)); // Ficamos com nome sem a extensão
	string norms = token + ".normals";
	string coords = token + ".coords";

	outfile.open((argc == 5) ? argv[4] : argv[3]);
	outfile2.open(norms);
	outfile3.open(coords);
	
	if (!outfile.is_open() || !outfile2.is_open() || !outfile3.is_open()) {
		perror("ofstream.open");
		return 1;
	}

	outfile << drawBox(x, y, z, divs);
	outfile2 << box_Normais(divs);
	outfile3 << box_TexCoords(divs);
	
	outfile.close();
	outfile2.close();
	outfile3.close();
	
	return 0;
}

int sphereGenerate(int argc, char *argv[]) {
	float raio;
	int fatias, stacks;
	ofstream outfile, outfile2, outfile3;

	raio = atof(argv[0]);
	fatias = atof(argv[1]);
	stacks = atof(argv[2]);
	
	if (raio <= 0.0f || fatias <= 0.0f || stacks <= 0.0f) {
		fputs("Error: All parameters of the sphere must be positive numbers\n", stderr);
		return 1;
	}

	string s = argv[3];
	string delimiter = ".";
	string token = s.substr(0, s.find(delimiter)); // Ficamos com nome sem a extensão
	string norms = token + ".normals";
	string coords = token + ".coords";

	outfile.open(argv[3]);
	outfile2.open(norms);
	outfile3.open(coords);

	if (!outfile.is_open() || !outfile2.is_open() || !outfile3.is_open()) {
		perror("ofstream.open");
		return 1;
	}
	outfile << drawElipsoide(raio, raio, raio, fatias, stacks);
	outfile2 << ellipsoidNormals(raio, raio, raio, fatias, stacks);
	outfile3 << ellipsoidCoords(fatias, stacks);
	
	outfile.close();
	outfile2.close();
	outfile3.close();
	return 0;
}

int ellipsoideGenerate(int argc, char *argv[]) {
	float x,y,z;
	int fatias, stacks;
	ofstream outfile, outfile2, outfile3;

	x = atof(argv[0]);
	y = atof(argv[1]);
	z = atof(argv[2]);
	fatias = atof(argv[3]);
	stacks = atof(argv[4]);
	
	if (x <= 0.0f || y <= 0.0f || z <= 0.0f || fatias <= 0.0f || stacks <= 0.0f) {
		fputs("Error: All parameters of the ellipsoide must be positive numbers\n", stderr);
		return 1;
	}

	string s = argv[5];
	string delimiter = ".";
	string token = s.substr(0, s.find(delimiter)); // Ficamos com nome sem a extensão
	string norms = token + ".normals";
	string coords = token + ".coords";
	
	outfile.open(argv[5]);
	outfile2.open(norms);
	outfile3.open(coords);
	
	if (!outfile.is_open() || !outfile2.is_open() || !outfile3.is_open()) {
		perror("ofstream.open");
		return 1;
	}
	
	outfile << drawElipsoide(x, y, z, fatias, stacks);
	outfile2 << ellipsoid_Normais(x, y, z, fatias, stacks);
	outfile3 << ellipsoid_TexCoords(fatias, stacks);
	
	outfile.close();
	outfile2.close();
	outfile3.close();
	return 0;
}

int coneGenerate(int argc, char *argv[]) {
	float raio, altura;
	int fatias, stacks;
	ofstream outfile, outfile2, outfile3;

	raio = atof(argv[0]);
	altura = atof(argv[1]);
	fatias = atof(argv[2]);
	stacks = atof(argv[3]);

	if (raio <= 0.0f || altura <= 0 || fatias <= 0.0f || stacks <= 0.0f) {
		fputs("Error: All parameters of the cone must be positive numbers\n", stderr);
		return 1;
	}

	string s = argv[4];
	string delimiter = ".";
	string token = s.substr(0, s.find(delimiter)); // Ficamos com nome sem a extensão
	string norms = token + ".normals";
	string coords = token + ".coords";
	

	outfile.open(argv[4]);
	outfile2.open(norms);
	outfile3.open(coords);
	
	if (!outfile.is_open() || !outfile2.is_open() || !outfile3.is_open()) {
		perror("ofstream.open");
		return 1;
	}

	outfile << drawCone(raio, altura, fatias, stacks);
	outfile2 << cone_Normais(raio, altura, fatias, stacks);
	outfile3 << cone_TexCoords(raio, altura, fatias, stacks);
	
	outfile.close();
	outfile2.close();
	outfile3.close();
	
	return 0;
}

int planeGenerate(int argc, char *argv[]) {
	float x,z;
	int divs;
	ofstream outfile, outfile2, outfile3;

	x = atof(argv[0]);
	z = atof(argv[1]);
	divs = (argc == 4 ? atoi(argv[2]) : 1);

	if (x <= 0.0f || z <= 0.0f || divs <= 0.0f) {
		fputs("Error: All parameters of the plane must be positive numbers\n", stderr);
		return 1;
	}

	string s = (argc == 4) ? argv[3] : argv[2];
	string delimiter = ".";
	string token = s.substr(0, s.find(delimiter)); // Ficamos com nome sem a extensão
	string norms = token + ".normals";
	string coords = token + ".coords";
	

	(argc == 4) ? outfile.open(argv[3]) : outfile.open(argv[2]);
	outfile2.open(norms);
	outfile3.open(coords);
	
	if (!outfile.is_open() || !outfile2.is_open() || !outfile3.is_open()) {
		perror("ofstream.open");
		return 1;
	}

	outfile << drawPlanoXZ(x, 0, z, divs, 1);
	outfile2 << plano_XZ_normais(divs, 1);
	outfile3 << plano_TexCoords(divs, 1);
	
	outfile.close();
	outfile2.close();
	outfile3.close();
	
	return 0;
}


void ajuda() {
    printf("Formas de interagir com o programa:\n\n");
   	printf("+-------------+-------------------------------------------+\n");
    printf("| primitivas  | parametros (sem ficheiro para direcionar) |\n");
    printf("+-------------+-------------------------------------------+\n");
    printf("| annulus     | grossura maior menor fatias               |\n");
    printf("| box         | x y z [divisoes]                          |\n");
    printf("| cone        | raio altura fatias pilhas                 |\n");
    printf("| ellipsoide  | raio_x raio_y raio_z fatias pilhas        |\n");
    printf("| plane       | x z [divisoes]                            |\n");
    printf("| sphere      | raio fatias pilhas                        |\n");
    printf("| bezier      | nivel_tesselation patch                   |\n");
    printf("+-------------+-------------------------------------------+\n");    
}


/* Size (in bytes) of the buffer used to store each line of a .patch file (one at a time) */
#define BUFF_SIZE 1024

typedef struct point {
    float x;
    float y;
    float z;
} point;

point *cpoints;     // control points
int **indexes;      // indexes of the points for each patch
int patches;        // number of patches
int ncpoints;       // number of control points


void multMatrixVector(float *m, float *v, float *res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}

void multVectorMatrix(float *v, float *m, float *res) {
    for (int i = 0; i < 4; ++i) {
        res[i] = 0;
        for (int j = 0; j < 4; ++j) {
            res[i] += v[j] * m[j * 4 + i];
        }
    }
}

void multMatrixMatrix(float *m1, float *m2, float *res) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            res[i * 4 + j] = 0.0f;
            for (int k = 0; k < 4; ++k)
                res[i * 4 + j] += m1[i * 4 + k] * m2[k * 4 + j];
        }
    }
}


void get_ponto_bezier(float u, float v, point *pv, float *res, float *normal, float *coords) {
    float dU[3];
    float dV[3];
    float m[4][4] = {
        { -1.0f,  3.0f, -3.0f, 1.0f },
        {  3.0f, -6.0f,  3.0f, 0.0f },
        { -3.0f,  3.0f,  0.0f, 0.0f },
        {  1.0f,  0.0f,  0.0f, 0.0f }
    };

    float Px[4][4] = {
        { pv[0].x, pv[1].x, pv[2].x, pv[3].x },
        { pv[4].x, pv[5].x, pv[6].x, pv[7].x },
        { pv[8].x, pv[9].x, pv[10].x, pv[11].x },
        { pv[12].x, pv[13].x, pv[14].x, pv[15].x }
    };

    float Py[4][4] = {
        { pv[0].y, pv[1].y, pv[2].y, pv[3].y },
        { pv[4].y, pv[5].y, pv[6].y, pv[7].y },
        { pv[8].y, pv[9].y, pv[10].y, pv[11].y },
        { pv[12].y, pv[13].y, pv[14].y, pv[15].y }
    };

    float Pz[4][4] = {
        { pv[0].z, pv[1].z, pv[2].z, pv[3].z },
        { pv[4].z, pv[5].z, pv[6].z, pv[7].z },
        { pv[8].z, pv[9].z, pv[10].z, pv[11].z },
        { pv[12].z, pv[13].z, pv[14].z, pv[15].z }
    };

    float U[4] = {u * u * u, u * u, u, 1};
    float UD[4] = {3 * u * u, 2 * u, 1, 0};
    float V[4] = {v * v * v, v * v, v, 1};
    float VD[4] = {3 * v * v, 2 * v, 1, 0};

    float MdV[4];
    float MV[4];
    multMatrixVector((float *)m, V, MV);
    multMatrixVector((float *)m, VD, MdV);

    float dUM[4];
    float UM[4];
    multVectorMatrix(U, (float *)m, UM);
    multVectorMatrix(UD, (float *)m, dUM);

    float UMP[3][4];
    multVectorMatrix(UM, (float *)Px, UMP[0]);
    multVectorMatrix(UM, (float *)Py, UMP[1]);
    multVectorMatrix(UM, (float *)Pz, UMP[2]);

    float dUMP[3][4];
    multVectorMatrix(dUM, (float *)Px, dUMP[0]);
    multVectorMatrix(dUM, (float *)Py, dUMP[1]);
    multVectorMatrix(dUM, (float *)Pz, dUMP[2]);

    for (int j = 0; j < 3; j++) {
        res[j] = 0.0f;
        dU[j] = 0.0f;
        dV[j] = 0.0f;

        for (int i = 0; i < 4; i++) {
            res[j] += MV[i] * UMP[j][i];
            dU[j] += MV[i] * dUMP[j][i];
            dV[j] += MdV[i] * UMP[j][i];
        }
    }
    normalize(dU);
    normalize(dV);
    cross(dV, dU, normal);
    normalize(normal);

    coords[0] = u;
    coords[1] = v;
}

int bezierGenerate(char *outfile, int tesselation) {
    int linhas = 0;
    point pv[16];
    int divs = tesselation; // change this to change the tesselation level
    ostringstream pontos, nrms, crds;
    ofstream out, out2, out3;

    string s = outfile;
	string delimiter = ".";
	string token = s.substr(0, s.find(delimiter)); // Ficamos com nome sem a extensão
	string norms = token + ".normals";
	string coords = token + ".coords";
	

    out.open(outfile);
    out2.open(norms);
    out3.open(coords);

    if (!out.is_open() || !out2.is_open() || !out3.is_open()) {
        perror("ofstream.open");
        return 1;
    }

    for (int i = 0; i < patches; i++) {
        for (int j = 0; j < 16; j++) {
            pv[j] = cpoints[indexes[i][j]];
        }
        for (int u = 0; u < divs; u++) {
            float p1[3], nrms1[3], coords1[2];
            float p2[3], nrms2[3], coords2[2];
            float p3[3], nrms3[3], coords3[2];
            float p4[3], nrms4[3], coords4[2];
            for (int v = 0; v < divs; v++) {
                get_ponto_bezier(u / (float)divs, v / (float)divs, pv, p1, nrms1, coords1);
                get_ponto_bezier((u + 1) / (float)divs, v / (float)divs, pv, p2, nrms2, coords2);
                get_ponto_bezier(u / (float)divs, (v + 1) / (float)divs, pv, p3, nrms3, coords3);
                get_ponto_bezier((u + 1) / (float)divs, (v + 1) / (float)divs, pv, p4, nrms4, coords4);

                pontos << p1[0] << ' ' << p1[1] << ' ' << p1[2] << '\n';
                pontos << p3[0] << ' ' << p3[1] << ' ' << p3[2] << '\n';
                pontos << p4[0] << ' ' << p4[1] << ' ' << p4[2] << '\n';

                pontos << p2[0] << ' ' << p2[1] << ' ' << p2[2] << '\n';
                pontos << p1[0] << ' ' << p1[1] << ' ' << p1[2] << '\n';
                pontos << p4[0] << ' ' << p4[1] << ' ' << p4[2] << '\n';

                nrms << nrms1[0] << ' ' << nrms1[1] << ' ' << nrms1[2] << '\n';
                nrms << nrms3[0] << ' ' << nrms3[1] << ' ' << nrms3[2] << '\n';
                nrms << nrms4[0] << ' ' << nrms4[1] << ' ' << nrms4[2] << '\n';

                nrms << nrms2[0] << ' ' << nrms2[1] << ' ' << nrms2[2] << '\n';
                nrms << nrms1[0] << ' ' << nrms1[1] << ' ' << nrms1[2] << '\n';
                nrms << nrms4[0] << ' ' << nrms4[1] << ' ' << nrms4[2] << '\n';

                crds << coords1[0] << ' ' << coords1[1] << '\n';
                crds << coords3[0] << ' ' << coords3[1] << '\n';
                crds << coords4[0] << ' ' << coords4[1] << '\n';

                crds << coords2[0] << ' ' << coords2[1] << '\n';
                crds << coords1[0] << ' ' << coords1[1] << '\n';
                crds << coords4[0] << ' ' << coords4[1] << '\n';

                linhas += 6;
            }
        }
    }
    out << (to_string(linhas) + "\n" + pontos.str());
    out2 << nrms.str();
    out3 << crds.str();

    out.close();
    out2.close();
    out3.close();
    
    return 0;
}

int parser_bezier_patch(char *patch) {
    int lIndex;
    int i, j;
    char line[BUFF_SIZE];
    FILE *f = fopen(patch, "r");

    if (!f)
        return 1;

    fscanf(f, "%d\n", &lIndex);
    patches = lIndex;
    printf("%d\n", patches);
    indexes = (int **) malloc(sizeof(int *) * lIndex);
    if (!indexes)
        return 1;

    for (i = 0; i < lIndex; i++) {
        indexes[i] = (int *) malloc(sizeof(int) * 16);
        if (!indexes[i]) {
            // free previously allocated memory before returning non zero
            for (--i; i >= 0; --i) {
                free(indexes[i]);
            }
            free(indexes);

            return 1;
        }
        memset(line, 0, BUFF_SIZE);
        fgets(line, BUFF_SIZE, f);
        char* ind = NULL;
        for(j = 0, ind = strtok(line,", "); ind && j < 16; ind = strtok(NULL, ", "), j++)
            indexes[i][j] = atoi(ind);
    }
    fscanf(f, "%d\n", &ncpoints);

    cpoints = (point *) malloc(sizeof(point) * ncpoints);
    if (!cpoints) {
        for (i = 0; i < lIndex; i++) {
            free(indexes[i]);
        }
        free(indexes);

        return 1;
    }

    for (i = 0; i < ncpoints; i++) {
        memset(line, 0, BUFF_SIZE);
        fgets(line, BUFF_SIZE, f);
        cpoints[i].x = atof(strtok(line, ", "));
        cpoints[i].y = atof(strtok(NULL, ", "));
        cpoints[i].z = atof(strtok(NULL, ", "));
    }

    fclose(f);
    return 0;
}

int main(int argc, char* argv[]) {
	int res;
	string s(argv[1]);
	if (s == "box" && (argc == 6 || argc == 7)) {// generator box x y z divs box.3d
		res = boxGenerate(argc - 2, &argv[2]);
	}
	else if (s == "cone" && argc == 7) {// generator cone raio altura slices stacks cone.3d
		res = coneGenerate(argc - 2, &argv[2]);
	}
	else if (s == "sphere" && argc == 6) {// generator sphere raio slices stacks sphere.3d 
		res = sphereGenerate(argc - 2, &argv[2]);
	}
	else if (s == "ellipsoide" && argc == 8) {// generator ellipsoide x y z slices stacks ellipsoide.3d 
		res = ellipsoideGenerate(argc - 2, &argv[2]);
	}
	else if (s == "plane" && (argc == 5 || argc == 6)) {// generator plane x z divs plane.3d
		res = planeGenerate(argc - 2, &argv[2]);
	}
	else if (s == "annulus" && argc == 7) {// generator annulus dist x y fatias anel.3d
		res = annulusGenerate(argc - 2, &argv[2]);
	}
	else if (s == "--help") {// generator --help
		ajuda();
		res = 0;
	}
	else if (s == "bezier" && argc == 5) {//generator bezier tesselation patch bezier.3d
        res = parser_bezier_patch(argv[3]);
        if (!res)
            res = bezierGenerate(argv[4], atoi(argv[2]));
    }
	else res = 1; // erro
	
	return res;
}// start esferaTrabalho.exe plane 1 1 4 ..\..\plane.3d
