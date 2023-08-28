/*
 * La fonction detection(Sens orientation) permet de détecter les poteaux situés autour
    du robot et d'enregistrer leur position en coordonnées cartésiennes (x, y).
    Elle prend en paramètre l'orientation du robot.
    La détection des poteaux est basée sur l'intensité lumineuse captée par un capteur.
    Le robot suit un comportement d'états pour détecter, suivre et enregistrer les poteaux.
    La position des poteaux est stockée dans une mémoire EEPROM externe.

 * Fichier : detectionPotos.cpp
 * Auteurs : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date : 20 Avril 2023
 */

#include "detectionPoteau.h"


void DetectionPoteau::premiereEcriture(){

    Memoire24CXXX memoire;

    memoire.ecriture(adresse++, nPoteau);
    _delay_ms(DELAI_ECRITURE);
    memoire.ecriture(adresse++, 0); //x0
    _delay_ms(DELAI_ECRITURE);
    memoire.ecriture(adresse++, 0); //y0
    _delay_ms(DELAI_ECRITURE);
    
};

void DetectionPoteau::detection(Sens orientation) {

    bool tourneDroite = true;
    bool estDectecte = false;
    bool finPoteau = false;
    uint8_t duree = 0;
    uint8_t premiereIntensite ;
    uint16_t angle;
    bool deja_bouge = false;
    
    Direction directionA, directionB;
    if (orientation == Sens::HAUT) {
        directionA = Direction::DROITE;
        directionB = Direction::GAUCHE;
    
    } else {
        directionA = Direction::GAUCHE;
        directionB = Direction::DROITE;
    }
    
    can convertisseur = can();
    Del del = Del(PORTB);
    Moteur moteur = Moteur(&PORTD, PIN_DROITE, PIN_GAUCHE);
    Musique son;
    initialisationUart();
    uint16_t lecture;
    uint8_t intensite;

    EtatRobot etat = EtatRobot::CHERCHER;
    Memoire24CXXX memoire;
    uint16_t adresseNbrePoteaux = 0x0000;
    uint8_t varLu;
  
    const static uint8_t INTENSITE_CHERCHER = 15;
    const static uint8_t INTENSITE_ARRET = 70;
    while(finPoteau == false){
    lecture = convertisseur.lecture(0);
    intensite = lecture >> DECALAGE;

    
    switch (etat) {
        case EtatRobot::CHERCHER:
            lecture = convertisseur.lecture(0);
            intensite = lecture >> DECALAGE;
            
            if (intensite >= INTENSITE_CHERCHER && intensite < INTENSITE_ARRET) {
                etat = EtatRobot::SUIVRE;
                break;
            } 
            else 
            {   
                if (intensite>=INTENSITE_ARRET)
                {
                    if (!estDectecte)
                    {
                        premiereIntensite = intensite;
                        estDectecte= true;
                    }
                    moteur.arreter();
                    for(int i=0; i<3;i++)
                    {
                        son.jouerNote(81);
                        _delay_ms(300);
                        son.arreterJouer();
                        _delay_ms(300);
                    }
                    etat = EtatRobot::FIN;
                    break;
                }
                if (tourneDroite==true && deja_bouge == true){
                    moteur.tourner(directionA, 100.0);
                    _delay_ms(1);
                    duree -= 2;
                    moteur.arreter();
                    _delay_ms(DELAI_ARRET);
                    deja_bouge=false;
                } 
                else 
                {
                    moteur.tourner(directionB, 100.0);
                    _delay_ms(100);
                    duree +=1;
                    moteur.arreter();
                    _delay_ms(DELAI_ARRET);
                    tourneDroite = true;
                }
            }

            if (duree > (tour_complet + 5)){
                aucunPoteau = true;
                etat = EtatRobot::RIEN;
            }
            break;
        case EtatRobot::SUIVRE:
            lecture = convertisseur.lecture(0);
            intensite = lecture >> DECALAGE;
            if (!estDectecte)
            {
                premiereIntensite = intensite;
                estDectecte= true;
            }
            if (intensite >= INTENSITE_CHERCHER && intensite < INTENSITE_ARRET) {
                moteur.avancer(100.0);
                deja_bouge=true;   
            }
            if (intensite>=INTENSITE_ARRET)
            {
                moteur.arreter();
                for(int i=0; i<3;i++)
                {
                    son.jouerNote(81);
                    _delay_ms(300);
                    son.arreterJouer();
                    _delay_ms(300);
                }
                etat = EtatRobot::FIN;
                break;
            }
            if (intensite<INTENSITE_CHERCHER) 
            {
                etat = EtatRobot::CHERCHER;
                break;
            }
            break;

        case EtatRobot::FIN:
            angle = pos.calculerAngle(duree);

            pos.setPosition(orientation, premiereIntensite, angle);

            memoire.lecture(adresseNbrePoteaux, &varLu);
            _delay_ms(DELAI_ECRITURE);
            memoire.lecture(adresseNbrePoteaux, &varLu);

            //Enregistrement du poteau en mémoire
            uint8_t ancien_x, ancien_y;
            memoire.lecture(adresse - 1, &ancien_y);
            memoire.lecture(adresse - 2, &ancien_x);
            
            memoire.ecriture(adresse++, pos.x_);
            _delay_ms(DELAI_ECRITURE);
            memoire.ecriture(adresse++, pos.y_);
            _delay_ms(DELAI_ECRITURE);
            memoire.ecriture(adresseNbrePoteaux, ++nPoteau);
            _delay_ms(DELAI_ECRITURE);
            
            memoire.lecture(adresseNbrePoteaux, &varLu);

            etat = EtatRobot::RIEN;
            break;

        case EtatRobot::RIEN:
            _delay_ms(5000);
            duree = 0;
            estDectecte = false;
            finPoteau = true;
            if (aucunPoteau == true)
            {
                son.jouerNote(45);
                _delay_ms(2000);
                son.arreterJouer();
                for (uint8_t i=0; i<10;i++)
                {
                    del.clignoterDel(Couleur::ROUGE);
                }
                del.allumerDel(Couleur::ETEINT);
            }

            if (aucunPoteau == false)
            {
                for (uint8_t i=0; i<10;i++)
                {
                    del.clignoterDel(Couleur::AMBRE);
                }
                del.allumerDel(Couleur::ETEINT);
            }
    }
    }
}
