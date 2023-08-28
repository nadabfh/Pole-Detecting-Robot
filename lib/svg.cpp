/*
 * Ce programme contient les fonctions pour générer un fichier SVG qui représente un ensemble de points et de figures. Les fonctions incluent :
    initialiserSvg : Initialisation du fichier SVG avec les informations de base.
    dessinerCarre : Dessine un carré à partir de coordonnées x, y et d'une couleur donnée.
    dessinerCercleGris : Dessine un cercle gris à partir d'un point donné.
    dessinerPolygoneVert : Dessine un polygone vert à partir d'un tableau de points.
    finirSvg : Termine le fichier SVG.
    majCrcOctet : Met à jour la valeur CRC pour un octet donné.
    majCrc : Met à jour la valeur CRC pour une chaîne de caractères donnée.
    transmissionCrc : Transmet la valeur CRC.
 * Fichier : svg.cpp
 * Auteurs : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date : 20 Avril 2023
 */
#include "svg.h"
#include "USART.h"
#include <string.h>
#include <stdio.h>

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0; // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}
DessinSvg::DessinSvg()
{
    initialisationUart();
}
void DessinSvg::transmissionLigne(const char* texte)
{
    majCrc(texte);
    transmissionUart(texte);
}
void DessinSvg::initialiserSvg(uint8_t numeroSection, uint16_t numeroEquipe, const char* nomRobot)
{
	char base[tailleLigne] = "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1152 576\">\n";
    transmissionLigne(base);
    char cadre[tailleLigne] = "\t<rect x=\"96\" y=\"48\" width=\"960\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/>\n";
    transmissionLigne(cadre);
	char texte[tailleLigne]; 
	sprintf(texte, "\t<text x=\"96\" y=\"36\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">section %0u -- equipe %u -- %s</text>\n", numeroSection, numeroEquipe, nomRobot);
	transmissionLigne(texte);
}
void DessinSvg::dessinerCarre(uint8_t x, uint8_t y, const char* couleur) 
{
    uint16_t xSvg = xBaseCentre + decalageCarre + (ratioCoordonnees * x);
	uint16_t ySvg = yBaseCentre + decalageCarre - (ratioCoordonnees * y);
	char ligne[tailleLigne];
    sprintf(ligne, "\t<rect x=\"%u\" y=\"%u\" width=\"6\" height=\"6\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\"/>\n", xSvg, ySvg, couleur, couleur); 
	transmissionLigne(ligne);
}
void DessinSvg::dessinerCercleGris(Point point) 
{
    uint16_t xSvg = xBaseCentre + (ratioCoordonnees * point.x);
	uint16_t ySvg = yBaseCentre - (ratioCoordonnees * point.y);
	char ligne[tailleLigne];
	sprintf(ligne, "\t<circle cx=\"%u\" cy=\"%u\" r=\"10\" stroke=\"black\" stroke-width=\"2\" fill=\"gray\"/>\n", xSvg, ySvg);
    transmissionLigne(ligne);
}
void DessinSvg::dessinerPolygoneVert(Point points[], uint8_t taille) 
{
    if (taille < 3)
        return;
    int8_t next[taille];
    for (uint8_t i = 0; i < taille; i++)
        next[i] = -1;
    uint8_t l = 0;
    for (uint8_t i = 1; i < taille; i++)
        if (points[i].x < points[l].x)
            l = i;
    uint8_t p = l, q;
    do
    {
        q = (p + 1) % taille;
        for (uint8_t i = 0; i < taille; i++)
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        next[p] = q; 
        p = q; 
    } while (p != l);
    uint8_t j = 0;
    Point enveloppe[taille];
    uint8_t tailleEnveloppe = 0;
    Point centre = {0, 0};
    for (uint8_t i = 0; i < taille; i++)
    {
        if (next[i] != -1) {
            enveloppe[j++] = points[i];
            tailleEnveloppe++;
            centre.x += points[i].x;
            centre.y += points[i].y;
        }
    }
    centre.x /= tailleEnveloppe;
    centre.y /= tailleEnveloppe;
    Point pointTemp = {0, 0};
    for (uint8_t j = 0; j < tailleEnveloppe; j++) {
        for (uint8_t i = 0; i < tailleEnveloppe-1; i++) {
            if (orientation(centre, enveloppe[i], enveloppe[i+1]) == 2) {
                pointTemp = enveloppe[i];
                enveloppe[i] = enveloppe[i+1];
                enveloppe[i+1] = pointTemp;  
            }
        }
        if (orientation(centre, enveloppe[tailleEnveloppe-1], enveloppe[0]) == 2) {
            pointTemp = enveloppe[tailleEnveloppe-1];
            enveloppe[tailleEnveloppe-1] = enveloppe[0];
            enveloppe[0] = pointTemp;  
        }
    }
    double aire = 0.0;
    double hauteur = 0.0;
    double largeur = 0.0;
    for (uint8_t i = 0; i < tailleEnveloppe - 1; i++) {
        hauteur = ratioPouce * (enveloppe[i].x + enveloppe[i + 1].x ) / 2.0; 
        largeur = ratioPouce * (enveloppe[i].y - enveloppe[i + 1].y);
        aire += hauteur * largeur;
    }
    aire += ratioPouce * ((enveloppe[tailleEnveloppe - 1].x + enveloppe[0].x) / 2.0) * (ratioPouce * (enveloppe[tailleEnveloppe - 1].y - enveloppe[0].y));
    char texteAire[tailleLigne];
    sprintf(texteAire, "\t<text x=\"96\" y=\"556\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">AIRE : %i pouces carres</text>\n", (uint16_t)aire);
    transmissionLigne(texteAire);
	char debutLigne[tailleLigne/6] = "\t<polygon points=\"";
	transmissionLigne(debutLigne);
    uint16_t xSvg = 0;
    uint16_t ySvg = 0;
	for (uint8_t i = 0; i < tailleEnveloppe; i++) {
		xSvg = xBaseCentre + ratioCoordonnees * enveloppe[i].x;
		ySvg = yBaseCentre - ratioCoordonnees * enveloppe[i].y;
		char pointsStr[tailleLigne/10];
		sprintf(pointsStr, "%u, %u ", xSvg, ySvg);
		transmissionLigne(pointsStr);
	}
	char finLigne[tailleLigne/2] = "\" style=\"fill:green; stroke:black; stroke-width:2\"/>\n";
	transmissionLigne(finLigne);
}
void DessinSvg::finirSvg()
{
    char finSvg[tailleLigne/12] = "</svg>";
	transmissionLigne(finSvg);
}
// Inspiré de l'article "Understanding CRC32"
// @source https://commandlinefanatic.com/cgi-bin/showarticle.cgi?article=art008 
uint32_t DessinSvg::majCrcOctet(uint32_t caractere)
{
    for (uint8_t k = 8; k; k--)
        caractere = caractere & 1 ? (caractere >> 1) ^ polynome : caractere >> 1;
    return caractere;
}
void DessinSvg::majCrc(const char* texte)
{
	uint8_t longueur = strlen(texte);
	for (uint16_t i = 0; i < longueur; i++) {
		crc = majCrcOctet((crc ^ texte[i]) & 0xFF) ^ (crc >> 8);
    }
}
void DessinSvg::transmissionCrc()
{
	char crcString[10];
    crc ^= 0xFFFFFFFF;
	sprintf(crcString, "%lx", crc);
	transmissionUart(crcString);
}