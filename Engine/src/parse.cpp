//
// Created by thol on 02-03-2019.
//

#ifdef _WIN32
#define line1 ""
#else
#define line1 "../../SistemaSolar/"
#endif

#include "parse.h"

std::vector<parseXML> globalInfo;

/// Função que vai tirar a informação necessaria de um elemento xml
parseXML getInfo(tinyxml2::XMLElement *group, parseXML insert)///VALUE == 0 >> PAI..... VALUE == 1 >> FILHO
{
	int pos = 1;
	tinyxml2::XMLNode *fC;
	fC = group->FirstChild();
	while (fC != nullptr && pos <= 3)
	{
		const char * value = fC->Value();
		std::string trans(value);

		if (trans == "translate")
		{
			tinyxml2::XMLElement *translate;
			translate = group->FirstChildElement("translate");
			if (translate) {
				const char* tm = translate->Attribute("time");
				if (tm != nullptr) {
					float time = atof(tm);
					insert.setTrTime(time);

					tinyxml2::XMLElement *controlPoints;
					controlPoints = translate->FirstChildElement("point");
					while (controlPoints) {
						const char* x = controlPoints->Attribute("X");
						const char* y = controlPoints->Attribute("Y");
						const char* z = controlPoints->Attribute("Z");
						float iX = 0;float iY = 0;float iZ = 0;

						if (x != nullptr) {
							iX = atof(x);
						}
						if (y != nullptr) {
							iY = atof(y);
						}
						if (z != nullptr) {
							iZ = atof(z);
						}

						insert.inserControlPoint(iX, iY, iZ);

						controlPoints = controlPoints->NextSiblingElement("point");
					}
				}
				else {
					const char* trx = translate->Attribute("X");
					const char* tryy = translate->Attribute("Y");
					const char* trz = translate->Attribute("Z");

					if (trx != nullptr) {
						float trX = atof(trx);
						insert.setTrx(trX);
					}
					if (tryy != nullptr) {
						float trY = atof(tryy);
						insert.setTry(trY);
					}
					if (trz != nullptr) {
						float trZ = atof(trz);
						insert.setTrz(trZ);
					}
				}
				insert.setTorder(pos);
				pos++;
			}
		}

		if (trans == "rotate")
		{
			tinyxml2::XMLElement *rotate;
			rotate = group->FirstChildElement("rotate");
			if (rotate) {
				const char* tm = rotate->Attribute("time");
				const char* ag = rotate->Attribute("angle");
				const char* rx = rotate->Attribute("axisX");
				const char* ry = rotate->Attribute("axisY");
				const char* rz = rotate->Attribute("axisZ");

				if (tm != nullptr)
				{
					float time = atof(tm);
					insert.setRtime(time);
				}
				if (ag != nullptr)
				{
					float angulo = atof(ag);
					insert.setRa(angulo);
				}
				if (rx != nullptr)
				{
					float rX = atof(rx);
					insert.setRx(rX);
				}
				if (ry != nullptr)
				{
					float rY = atof(ry);
					insert.setRy(rY);
				}
				if (rz != nullptr)
				{
					float rZ = atof(rz);
					insert.setRz(rZ);
				}
				insert.setRorder(pos);
				pos++;
			}
		}

		if (trans == "scale")
		{
			tinyxml2::XMLElement *scale;
			scale = group->FirstChildElement("scale");
			if (scale) {
				const char* sx = scale->Attribute("X");
				const char* sy = scale->Attribute("Y");
				const char* sz = scale->Attribute("Z");

				if (sx != nullptr) {
					float sX = atof(sx);
					insert.setSx(sX);
				}
				if (sy != nullptr) {
					float sY = atof(sy);
					insert.setSy(sY);
				}
				if (sz != nullptr) {
					float sZ = atof(sz);
					insert.setSz(sZ);
				}
				insert.setSorder(pos);
				pos++;
			}
		}

		fC = fC->NextSibling();
	}

	tinyxml2::XMLElement *models;
	models = group->FirstChildElement("models");
	if (models) {
        lighting light(0,0);
		tinyxml2::XMLElement *model;
		model = models->FirstChildElement("model");
		while (model) {
			const char* xml = model->Attribute("file");
			const char* tex = model->Attribute("texture");
			const char* dr = model->Attribute("diffR");
			const char* dg = model->Attribute("diffG");
			const char* db = model->Attribute("diffB");
            const char* sr = model->Attribute("specR");
            const char* sg = model->Attribute("specG");
            const char* sb = model->Attribute("specB");
            const char* er = model->Attribute("emR");
            const char* eg = model->Attribute("emG");
            const char* eb = model->Attribute("emB");
            const char* ar = model->Attribute("ambR");
            const char* ag = model->Attribute("ambG");
            const char* ab = model->Attribute("ambB");
			if (xml != nullptr)
				insert.setXMLS(xml);
			if(tex != nullptr)
			    light.setTexture(tex);
            if(dr != nullptr) {
                float ins = atof(dr);
                light.setDR(ins);
                light.setDV(1);
            }
            if(dg != nullptr) {
                float ins = atof(dg);
                light.setDG(ins);
                light.setDV(1);
            }
            if(db != nullptr) {
                float ins = atof(db);
                light.setDB(ins);
                light.setDV(1);
            }
            if(sr != nullptr) {
                float ins = atof(sr);
                light.setSR(ins);
                light.setSV(1);
            }
            if(sg != nullptr) {
                float ins = atof(sg);
                light.setSG(ins);
                light.setSV(1);
            }
            if(sb != nullptr) {
                float ins = atof(sb);
                light.setSB(ins);
                light.setSV(1);
            }
            if(er != nullptr) {
                float ins = atof(er);
                light.setER(ins);
                light.setEV(1);
            }
            if(eg != nullptr) {
                float ins = atof(eg);
                light.setEG(ins);
                light.setEV(1);
            }
            if(eb != nullptr) {
                float ins = atof(eb);
                light.setEB(ins);
                light.setEV(1);
            }
            if(ar != nullptr) {
                float ins = atof(ar);
                light.setAR(ins);
                light.setAV(1);
            }
            if(ag != nullptr) {
                float ins = atof(ag);
                light.setAG(ins);
                light.setAV(1);
            }
            if(ab != nullptr) {
                float ins = atof(ab);
                light.setAB(ins);
                light.setAV(1);
            }

            insert.setLights(light);

            model = model->NextSiblingElement("model");
		}
	}
	return insert;
}

/// Função que vai obter a informação xml dos filhos das roots principais e manter as suas transformações
parseXML getFilhos(parseXML parsePai, tinyxml2::XMLElement *nodoPai)
{
	tinyxml2::XMLElement *filho = nodoPai->FirstChildElement("group");
	while (filho)
	{
		parseXML insert(0, 0);
		insert = getInfo(filho, insert);
		insert = getFilhos(insert, filho);
		parsePai.insertFilho(insert);
		filho = filho->NextSiblingElement("group");
	}
	return parsePai;
}

/// Função principal que vai obter a informação xml das roots originais antes de chamar nos seus filhos
std::vector<parseXML> getXML(std::string ficheiro)
{
	tinyxml2::XMLDocument doc;

	std::string final = line1 + ficheiro;

	doc.LoadFile(final.c_str());
	if (doc.ErrorID() == 0)
	{
		tinyxml2::XMLElement *scene;
		scene = doc.FirstChildElement("scene");
		if (scene)
		{
			tinyxml2::XMLElement *group;
			group = scene->FirstChildElement("group");
			while (group)
			{
				parseXML insert(0, 0);
				insert = getInfo(group, insert);
				insert = getFilhos(insert, group);
				globalInfo.push_back(insert);
				group = group->NextSiblingElement("group");
			}
		}
	}

	return globalInfo;
}

std::vector<lightSource> getLight(std::string ficheiro)
{
    tinyxml2::XMLDocument doc;

    std::string final = line1 + ficheiro;

    std::vector<lightSource> reto;

    doc.LoadFile(final.c_str());
    if (doc.ErrorID() == 0)
    {
        tinyxml2::XMLElement *scene;
        scene = doc.FirstChildElement("scene");
        if (scene)
        {
            tinyxml2::XMLElement *light;
            light = scene->FirstChildElement("lights");
            if (light)
            {
                tinyxml2::XMLElement *l;
                l = light->FirstChildElement("light");
                while(l)
                {
                    lightSource ret(0,0);

                    const char* type = l->Attribute("type");
                    const char* px = l->Attribute("posX");
                    const char* py = l->Attribute("posY");
                    const char* pz = l->Attribute("posZ");
                    const char* dx = l->Attribute("dirX");
                    const char* dy = l->Attribute("dirY");
                    const char* dz = l->Attribute("dirZ");
                    const char* phi = l->Attribute("phi");
                    const char* theta = l->Attribute("theta");

                    if(type != nullptr)
                        ret.setType(type);
                    if(px != nullptr)
                        ret.setPointX(atof(px));
                    if(py != nullptr)
                        ret.setPointY(atof(py));
                    if(pz != nullptr)
                        ret.setPointZ(atof(pz));
                    if(dx != nullptr)
                        ret.setDirX(atof(dx));
                    if(dy != nullptr)
                        ret.setDirY(atof(dy));
                    if(dz != nullptr)
                        ret.setDirZ(atof(dz));
                    if(phi != nullptr)
                        ret.setPhi(atof(phi));
                    if(theta != nullptr)
                        ret.setTheta(atof(theta));

                    reto.push_back(ret);

                    l = l->NextSiblingElement("light");
                }
            }
        }
    }
    return reto;
}

