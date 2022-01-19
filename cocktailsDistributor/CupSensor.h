#ifndef CUPSENSOR_H
#define CUPSENSOR_H

#include "./HX711.h"
#include "./Arduino.h"

/// <summary>
/// Classe CupSensor, organe de verification des dosages.
/// </summary>
class CupSensor {
private:
    /// <summary>
    /// Pin <b>DOUT</b> du capteur.
    /// </summary>
    int _doutPin;

    /// <summary>
    /// Pin <b>SCK</b> du capteur.
    /// </summary>
    int _sckPin;

    /// <summary>
    /// Valeur de calibration du capteur.
    /// </summary>
    int _scale;

    /// <summary>
    /// Jauge de contrainte.
    /// </summary>
    HX711 _sensor;

public:
    /// <summary>
    /// Constructeur de CupSensor.
    /// </summary>
    CupSensor();

    /// <summary>
    /// Constructeur de CupSensor avec son <paramref name="doutPin"/>, son <paramref name="sckPin"/> et son <paramref name="scale"/>.
    /// </summary>
    /// <param name="doutPin">Pin DOUT du capteur.</param>
    /// <param name="sckPin">Pin SCK du capteur.</param>
    /// <param name="scale">Valeur de calibration du capteur.</param>
    CupSensor(int doutPin, int sckPin, int scale);

    /// <summary>
    /// Initialise le CupSensor.
    /// </summary>
    void init();

    /// <summary>
    /// Remet a zero la mesure du capteur.
    /// </summary>
    void tare();

    /// <summary>
    /// Mesure la masse sur la plateforme.
    /// </summary>
    /// <returns>La masse sur la plateforme.</returns>
    int measureLevel();

    /// <summary>
    /// Verifie que le gobelet est pose sur la plateforme.
    /// </summary>
    /// <returns>Un booleen qui vaut <b>true</b> si le gobelet a ete pose, <b>false</b> sinon.</returns>
    bool isCupAvailable();

    /// <summary>
    /// Verifie que le gobelet a ete retire de la plateforme.
    /// </summary>
    /// <returns>Un booleen qui vaut <b>true</b> si le gobelet a ete retire, <b>false</b> sinon.</returns>
    bool isCupRemoved();
};

#endif