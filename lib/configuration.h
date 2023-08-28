#pragma once
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>

class Configuration{
public:
    Configuration() = default;

    void partirMinuterie (uint16_t duree, uint8_t gMinuterieExpiree, uint8_t numeroMinuterie);
    
    ~Configuration();

};