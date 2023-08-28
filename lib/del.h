#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h> 

enum class Couleur {ROUGE, VERT, AMBRE, ETEINT};

const static uint8_t VERT = 1 << PA0;
const static uint8_t ROUGE = 1 << PA1;
const static uint8_t ETEINT = 0;

class Del {
public:
    Del(volatile uint8_t& PORT_VOULU);
    void allumerDel(Couleur couleur);
    void clignoterDel(Couleur couleur_clin);
    ~Del();

private:
    volatile uint8_t& port_;
};