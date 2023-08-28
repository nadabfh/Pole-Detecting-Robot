
#pragma once
#include <avr/io.h>
const uint8_t tailleLigne = 120;
const uint16_t xBaseCentre = 191;
const uint16_t yBaseCentre = 453;
const int8_t decalageCarre = -3;
const uint8_t ratioCoordonnees = 110;
const double ratioPouce = 11.0;
const uint32_t polynome = 0xEDB88320;
struct Point {
    uint8_t x = 0;
    uint8_t y = 0;
};
class DessinSvg {
public:
    DessinSvg(); 
    void initialiserSvg(uint8_t numeroSection, uint16_t numeroEquipe, const char* nomRobot);
    void dessinerCarre(uint8_t x, uint8_t y, const char* couleur);
    void dessinerCercleGris(Point point);
    void dessinerPolygoneVert(Point points[], uint8_t taille);
    void transmissionCrc();
    void finirSvg();
private: 
    void transmissionLigne(const char* texte);
    void majCrc(const char* texte);
    uint32_t majCrcOctet(uint32_t caractere);
    uint32_t crc = 0xFFFFFFFF;
};