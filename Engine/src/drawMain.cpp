//
// Created by thol on 03-03-2019.
//

#ifdef _WIN32
    #include <windows.h>
#endif

#include "structure.h"
#include "parseXML.h"
#include "parse.h"
#include "draw.h"

void printInfo(parseXML toPrint){
    std::vector<std::string> tp = toPrint.getXMLS();
    std::vector<parseXML> filhos = toPrint.getFilhos();

    std::cout << "------------NEW OBJECT------------" << std::endl;
    for(unsigned long k = 0; k < tp.size() ; k++) {
        std::cout << "File:" << tp.at(k) << " Texture:" << toPrint.getLights().at(k).getTexture() << std::endl;
    }

    std::cout << "Translations:" << " Time=" << toPrint.getTrTime() <<" X=" << toPrint.getTrx() << " Y=" << toPrint.getTry() << " Z=" << toPrint.getTrz() << " Order=" << toPrint.getTorder() << std::endl;
    std::cout << "Rotations:" << " Time=" << toPrint.getRtime() << " Angulo=" << toPrint.getRa() << " X=" << toPrint.getRx() << " Y=" << toPrint.getRy() << " Z=" << toPrint.getRz() << " Order=" << toPrint.getRorder() << std::endl;
    std::cout << "Scalings:" << " X=" << toPrint.getSx() << " Y=" << toPrint.getSy() << " Z=" << toPrint.getSz() << " Order=" << toPrint.getSorder() << std::endl;

    std::cout << "Filhos = " << filhos.size() << std::endl;
    for(unsigned long k = 0; k<filhos.size() ;k++){
        printInfo(filhos.at(k));
    }
}
int main(int argc, char *argv[]) {

    if(argc >= 2)
    {
        std::string ficheiro = argv[1];

        std::vector<parseXML> info = getXML(ficheiro);

        std::vector<lightSource> lightInfo = getLight(ficheiro);
        
        std::cout << lightInfo.size() << std::endl;

       // std::cout << "------------LIGHT TYPE------------" << std::endl;
       // std::cout << "Type=" << lightInfo.getType() << std::endl;
       // std::cout << "PointX=" << lightInfo.getPointX() << " PointY=" << lightInfo.getPointY() << " PointZ=" << lightInfo.getPointZ() << std::endl;
       // std::cout << "DirX=" << lightInfo.getDirX() << " DirY=" << lightInfo.getDirY() << " DirZ=" << lightInfo.getDirZ() << std::endl;
       // std::cout << "Phi=" << lightInfo.getPhi() << " Theta=" << lightInfo.getTheta() << std::endl;

        for(unsigned long i = 0; i < info.size() ; i++){
            printInfo(info.at(i));
        }

        std::cout << "---------------END----------------" << std::endl;

        startDrawing(info,lightInfo, argc, argv);
    }
    else
    {
        printf("Insira o nome do ficheiro xml a ler\n");
    }

    return 1;
}
