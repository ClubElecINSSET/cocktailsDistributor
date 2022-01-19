#include "./Pump.h"
#include "./Liquid.h"
#include "./Arduino.h"

Pump::Pump() {

}

Pump::Pump(int pin) {
    _pin = pin;
}

void Pump::init() {
    pinMode(_pin, OUTPUT);
    _activated = true;
    deactivatePump();
}

void Pump::activatePump() {
    if (!_activated) {
        digitalWrite(_pin, LOW);
        _activated = true;
    }
}

void Pump::deactivatePump() {
    if (_activated) {
        digitalWrite(_pin, HIGH);
        _activated = false;
    }
}

bool Pump::isActive() {
    return _activated;
}

Liquid* Pump::getLiquid() {
    return &_liquid;
}

void Pump::setLiquid(Liquid liquid) {
    _liquid = liquid;
}