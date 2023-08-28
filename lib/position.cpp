/*
 * Ce programme définit la classe Position qui permet de calculer la position et l'angle du robot en fonction de son orientation, de la distance parcourue et
    du temps de déplacement.
 * Fichier : position.cpp
 * Auteurs : Nada Benelfellah, Junior Stevy Randy Boussougou, Max-Anthony Schneider, Angel Xi Ting Shih
 * Date : 20 Avril 2023
 */

#include "USART.h"
#include "position.h"
#include <stdio.h>
#include <avr/io.h>

double absolue(double valeur) {
    if (valeur < 0)
        valeur *= -1;
    return valeur;
}


uint16_t Position::calculerAngle(uint8_t time)
{
    uint16_t angles = 0;
    uint8_t tour_complet = 50;
    uint16_t un_tour = 360;
    int differenceAngles;
    int differenceMin = 315;
    uint16_t angleFinal = 0;
    const uint8_t ajout = 45;

    double angle_calcule16 = time * un_tour  / tour_complet; //toujours utiliser un PWM de 100
    uint16_t angle_calcule = static_cast<uint16_t>(angle_calcule16);

    for (int i = 0; i < 8; i++)
    {
        differenceAngles = angle_calcule - angles;
        if (absolue(differenceAngles) < differenceMin)
        {
            differenceMin = absolue(differenceAngles);
            angleFinal = angles;
        }
        angles += ajout;
    }

    return angleFinal;

};




void Position::setPosition(Sens oriente,uint8_t distance, uint16_t angle) 
{
    sens_ =  oriente;
    int8_t offsetY = 0;
    int8_t offsetX = 0;
    switch(oriente){
        case Sens::HAUT:
            switch(angle){
                case angle0 :
                    offsetY = 1;
                    break;
                case angle1 :
                    offsetY = 1;
                    offsetX = 1;
                    break;
                case angle2 :
                    offsetX = 1;
                    break;
                case angle3:
                    offsetY = -1;
                    offsetX = 1;
                    break;
                case angle4:
                    offsetY = -1;
                    break;
                case angle5:
                    offsetY = -1;
                    offsetX = -1;
                    break;
                case angle6:
                    offsetX = -1;
                    break;
                case angle7:
                    offsetY = 1;
                    offsetX = -1;
                    break;
            }
            break;
        case Sens::DROITE:
            switch(angle){
                case angle0:
                    offsetX = 1;
                    break;
                case angle1:
                    offsetY = 1;
                    offsetX = 1;
                    break;
                case angle2:
                    offsetY = 1;
                    break;
                case angle3:
                    offsetY = 0;
                    offsetX = 0;
                    break;
                case angle4:
                    offsetX = 0;
                    break;
                case angle5:
                    offsetY = 0;
                    offsetX = 0;
                    break;
                case angle6:
                    offsetY = 0;
                    break;
                case angle7:
                    offsetY = 0;
                    offsetX = 0;
                    break;
            }
            break;
    }
    if (distance > 40){ 
        y_+=offsetY;
        x_+=offsetX;
    }
    else{
        y_+=2*offsetY;
        x_+=2*offsetX;
    }
}