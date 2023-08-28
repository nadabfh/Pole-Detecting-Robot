#ifndef MOTEUR_H
#define MOTEUR_H

#include <stdint.h>

enum class Direction {GAUCHE, DROITE};

class Moteur{
public:
    Moteur(volatile uint8_t* const portVoulu, 
           uint8_t pinDroiteVoulu,
           uint8_t pinGaucheVoulu);
    void avancer(double vitesse);
    void reculer(double vitesse);
    void tourner(Direction direction, double vitesse);
    void arreter();
    void ajustementVitesse(double leftSpeed, double rightSpeed);
private:
    double vitesseGauche_;
    double vitesseDroite_;
    volatile uint8_t* const port_;
    uint8_t pinDroite_;
    uint8_t pinGauche_;
};

#endif