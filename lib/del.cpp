/*Programme qui permet de contrôler n’importe quelle DEL de notre robot en choisissant notre PORT de sortie
 * 
 * Fichier : del.cpp
 * Auteur  : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date    : 13 mars 2023
 */
#include "del.h"

Del::Del(volatile uint8_t& PORT_VOULU) : port_(PORT_VOULU) {};

void Del::allumerDel(Couleur couleur){
    switch(couleur){
        case Couleur::ROUGE: 
            port_ = ROUGE;
            break;

        case Couleur::VERT: 
            port_ = VERT;
            break;

        case Couleur::AMBRE: 
            port_ = ROUGE;
            _delay_ms(5);
            port_ = VERT;
            _delay_ms(5);
            break;
        
        case Couleur::ETEINT: 
            port_ = ETEINT;
            break;
    }
};

void Del::clignoterDel(Couleur couleur_clin){
    switch(couleur_clin){
        case Couleur::ROUGE: 
            port_ = ROUGE;
            _delay_ms(20);
            port_ = ETEINT;
            _delay_ms(30);
            break;

        case Couleur::VERT: 
            port_ = VERT;
            _delay_ms(20);
            port_ = ETEINT;
            _delay_ms(30);
            break; 

        case Couleur::AMBRE: 
            for (int i=0; i<2; i++){
                port_ = ROUGE;
                _delay_ms(5);
                port_ = VERT;
                _delay_ms(5);    
            }

            port_ = ETEINT;
            _delay_ms(30);
            break;

        case Couleur::ETEINT: 
            port_ = ETEINT;
            break;
    }
};

Del::~Del(){};