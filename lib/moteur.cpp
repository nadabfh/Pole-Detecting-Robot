/*
 * Definition des méthodes de la classe moteur, permettant au robot d'avancer, de reculer, de tourner ou de s'arreter en utilisant le PWM
 * Fichier : moteur.cpp
 * Auteurs : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date : 13 mars 2023
 */

#include "moteur.h"
#include "pwm.h"
#include <avr/io.h>

Moteur::Moteur(volatile uint8_t* const portVoulu, uint8_t pinDroiteVoulu, uint8_t pinGaucheVoulu) : port_(portVoulu)
{
    initialisationPwm();
    pinDroite_ = pinDroiteVoulu;
    pinGauche_ = pinGaucheVoulu;
    vitesseDroite_ = 0;
    vitesseGauche_ = 0;
}

void Moteur::avancer(double vitesse)
{
    vitesseDroite_ = vitesse;
    vitesseGauche_ = vitesse;
    *port_ &= ~(1 << pinDroite_);
    *port_ &= ~(1 << pinGauche_);
    ajusterPwm(vitesseDroite_, vitesseGauche_);
}

void Moteur::reculer(double vitesse)
{
    vitesseDroite_ = vitesse;
    vitesseGauche_ = vitesse;
    *port_ |= (1 << pinDroite_);
    *port_ |= (1 << pinGauche_);
    ajusterPwm(vitesseDroite_, vitesseGauche_);
}

void Moteur::tourner(Direction direction, double vitesse)
{
    switch (direction) {
        case Direction::GAUCHE :
            *port_ |= (1 << pinDroite_);
            *port_ &= ~(1 << pinGauche_);
            break;
        case Direction::DROITE :
            *port_ &= ~(1 << pinDroite_);
            *port_ |= (1 << pinGauche_);
            break;
    }
    vitesseDroite_ = vitesse;
    vitesseGauche_ = vitesse;
    ajusterPwm(vitesseDroite_, vitesseGauche_);
}
void Moteur::ajustementVitesse(double leftSpeed, double rightSpeed) {
    // Ensure the speed values are within the acceptable range (0-255).
    uint8_t leftSpeedValue = (leftSpeed < 0) ? 0 : ((leftSpeed > 255) ? 255 : static_cast<uint8_t>(leftSpeed));
    uint8_t rightSpeedValue = (rightSpeed < 0) ? 0 : ((rightSpeed > 255) ? 255 : static_cast<uint8_t>(rightSpeed));
    
    *port_ &= ~(1 << pinDroite_);
    *port_ &= ~(1 << pinGauche_);
    
    vitesseDroite_ = rightSpeedValue;
    vitesseGauche_ = leftSpeedValue;// Adjust the speed of both motors.
    ajusterPwm(rightSpeedValue,leftSpeedValue);
}
void Moteur::arreter()
{
    ajusterPwm(0, 0);
}
