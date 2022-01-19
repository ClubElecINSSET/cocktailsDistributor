#ifndef PUMP_H
#define PUMP_H

#include "./Liquid.h"

/// <summary>
/// Classe Pump, organe de pompage des liquides.
/// </summary>
class Pump {
private:

    /// <summary>
    /// Pin de la pompe.
    /// </summary>
    int _pin;

    /// <summary>
    /// Booleen representant l'activation de la pompe.
    /// </summary>
    bool _activated = false;

    /// <summary>
    /// Liquide associé à la pompe.
    /// </summary>
    Liquid _liquid;

public:

    /// <summary>
    /// Constructeur de Pump sans parametres.
    /// </summary>
    Pump();

    /// <summary>
    /// Constructeur de Pump avec la <paramref name="pin"/> de la pompe.
    /// </summary>
    /// <param name="pin">Pin de la pompe.</param>
    Pump(int pin);

    /// <summary>
    /// Initialise la pompe.
    /// </summary>
    void init();

    /// <summary>
    /// Active la pompe.
    /// </summary>
    void activatePump();

    /// <summary>
    /// Desactive la pompe.
    /// </summary>
    void deactivatePump();

    /// <summary>
    /// Retourne si la pompe est activee ou non.
    /// </summary>
    /// <returns>Un booleen correspondant a l'activation de la pompe.</returns>
    bool isActive();

    /// <summary>
    /// Récupère le liquide associé à la pompe.
    /// </summary>
    /// <returns>Une référence au liquide associé à la pompe.</returns>
    Liquid* getLiquid();

    /// <summary>
    /// Paramètre le liquide associé à la pompe.
    /// </summary>
    /// <param name="liquid">Le liquide à associer à la pompe.</param>
    void setLiquid(Liquid liquid);
};

#endif