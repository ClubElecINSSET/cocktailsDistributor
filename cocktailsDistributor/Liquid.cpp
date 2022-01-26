#include "Liquid.h"

Liquid::Liquid() {

}

Liquid::Liquid(float volumicMass, int available) {
    _volumicMass = volumicMass;
    _available = available;
    resetTest();
}

float Liquid::getVolumicMass() {
    return _volumicMass;
}

void Liquid::decreaseAmount(int amount) {
    _available = _available - amount;
    if (_available < 0) _available = 0;
}

int Liquid::getAvailable() {
    return _available;
}

bool Liquid::testAvailable(int amount) {
    if (_testAvailable >= amount) {
        _testAvailable -= amount;
        return true;
    }
    return false;
}

void Liquid::resetTest() {
    _testAvailable = _available;
}

void Liquid::setAmount(int amount) {
    _available = amount;
    resetTest();
}
