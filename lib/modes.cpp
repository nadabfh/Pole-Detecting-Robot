/*
 * Ce programme contient deux fonctions principales :
    orientation(Sens oriente) : Indique l'orientation du robot à l'aide de la LED.
    Si le robot est orienté à droite, la LED clignote en rouge.
    Si le robot est orienté vers le haut, la LED clignote en vert.
    menu(Modes mode) : Affiche le mode de fonctionnement du robot à l'aide de la LED.
    Si le robot est en mode détection, la LED s'allume en ambre.
    Si le robot est en mode transmission, la LED s'allume en vert avec un délai.
 * Fichier : modes.cpp
 * Auteurs : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date : 20 Avril 2023
 */

#include "modes.h"

void genererSvg(Point points[], uint8_t nPoints) {

    const char* nomRobot = "Flash";
    DessinSvg createurSvg;

    uint8_t octetDepart = 0x02;
    uint8_t octetFinTexte = 0x03;
    uint8_t octetFin = 0x04;

    transmissionUart(octetDepart);

    _delay_ms(500);

    createurSvg.initialiserSvg(numeroSection, numeroEquipe, nomRobot);

    createurSvg.dessinerPolygoneVert(points, nPoints);

    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 4; j++)
            createurSvg.dessinerCarre(i, j, "black");
    }

    createurSvg.dessinerCarre(0, 0, "red");

    for (uint8_t i = 0; i < nPoints; i++)
        createurSvg.dessinerCercleGris(points[i]);

    createurSvg.finirSvg();

    transmissionUart(octetFinTexte);

    createurSvg.transmissionCrc();

    transmissionUart(octetFin);
}



/*
void orientation(Sens oriente) {
    Del delUse = Del(PORTB);
    initialisationUart();
    switch (oriente) 
    {
        case Sens::DROITE :
            for (int i =0; i<20; i++)
                delUse.clignoterDel(Couleur::ROUGE);
            
            //break;
        
        case Sens::HAUT :
            for (int i =0; i<20; i++)
                delUse.clignoterDel(Couleur::VERT);
            //break;
    }

    char texte[30];
            for (int i = 0; i<10; i++)
{               sprintf(texte, "OUIIII \n");
                transmissionUart(texte);}

    detection(oriente);
}
*/
void menu(Modes mode, bool& ambre)
{
    Del delUse = Del(PORTB);
    Memoire24CXXX memoire24;
    switch (mode)
    {
    case Modes::DETECTION :
        if (ambre == false){
            for (uint8_t i=0; i<250;i++)
                delUse.allumerDel(Couleur::AMBRE);
            ambre = true;
        } 
        else 
        {
            // delUse.allumerDel(Couleur::ETEINT);
            for (uint8_t i=0; i<100;i++)
                {
                    delUse.clignoterDel(Couleur::AMBRE);
                }
                delUse.allumerDel(Couleur::ETEINT);
        }
        
        
        
        break;
    
    case Modes::TRANSMISSION :
        delUse.allumerDel(Couleur::VERT);
        _delay_ms(delai);

        

        uint8_t nPoints;

        memoire24.lecture(0x00, &nPoints);

        Point points[nPoints];
    
        uint8_t x;
        uint8_t y;

        uint8_t adresseTR = 0x03;

        for (uint8_t i = 0; i < nPoints; i++) {
            memoire24.lecture(adresseTR++, &x);
            memoire24.lecture(adresseTR++, &y);
            points[i] = {x, y};
        }

        genererSvg(points, nPoints);      

        break;
    }

}