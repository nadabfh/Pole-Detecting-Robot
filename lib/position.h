#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <assert.h>

const uint8_t tour_complet = 50;

enum class Sens {HAUT, DROITE};

class Position
{
public:
    Position() = default;
    void setX(int x) {
        assert((x<4)&&(x>=0)&& "X_ IS OUT OF RANGE");
        x_ = x;
    };
    void setY(int y) {
        assert((y<8)&&(y>=0)&& "Y_ IS OUT OF RANGE");
        y_ = y;
    };
    uint16_t calculerAngle(uint8_t time);
    void setPosition(Sens direction,uint8_t distance, uint16_t angle);


    static constexpr uint16_t angle0 = 0;
    static constexpr uint16_t angle1 = 45;
    static constexpr uint16_t angle2 = 90;
    static constexpr uint16_t angle3 = 135;
    static constexpr uint16_t angle4 = 180;
    static constexpr uint16_t angle5 = 225;
    static constexpr uint16_t angle6 = 270;
    static constexpr uint16_t angle7 = 315;


    int8_t x_ = 0;
    int8_t y_ = 0;
    Sens sens_;
    
};
