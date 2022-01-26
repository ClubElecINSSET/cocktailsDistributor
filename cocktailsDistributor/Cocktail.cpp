#include "Cocktail.h"
#include "CupSensor.h"
#include "Liquid.h"

Cocktail::Cocktail() {

}

void Cocktail::addInstruction(int instructionID, int pumpID, int amount) {
    _instructions[0][instructionID] = pumpID;
    _instructions[1][instructionID] = amount;
}

int Cocktail::getPumpID(int instructionID) {
    return _instructions[0][instructionID];
}

int Cocktail::getAmount(int instructionID) {
    return _instructions[1][instructionID];
}
