#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h> 
#include <avr/interrupt.h>
#include <del.h>
#include "memoire_24.h"
#include "position.h"
#include "svg.h"
#include "USART.h"
#include "detectionPoteau.h"

const uint8_t numeroSection = 1;
const uint16_t numeroEquipe = 1722;


const uint8_t anti_rebond = 30;

const uint16_t delai = 2000;

enum class Modes {DETECTION, TRANSMISSION};

void menu(Modes mode, bool& ambre);

void orientation(Sens oriente);



