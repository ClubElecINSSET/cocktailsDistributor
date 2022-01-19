#ifndef LIQUID_H
#define LIQUID_H

#include "./Arduino.h"

/// <summary>
/// Classe Liquid, element qui compose un cocktail.
/// </summary>
class Liquid {
private:
    /// <summary>
    /// Masse volumique du liquide.
    /// </summary>
    float _volumicMass;

    /// <summary>
    /// Quantite de liquide restante dans la bouteille.
    /// </summary>
    int _available;

    /// <summary>
    /// Quantite restante apres un test de quantite.
    /// </summary>
    int _testAvailable;

public:
    /// <summary>
    /// Constructeur de Liquid, element qui compose un cocktail.
    /// </summary>
    Liquid();

    /// <summary>
    /// Constructeur de Liquid, avec son <paramref name="liquidName"/>, sa <paramref name="volumicMass"/> et son <paramref name="amount"/>.
    /// </summary>
    /// <param name="volumicMass">La masse volumique du liquide.</param>
    /// <param name="amount">La quantite chargee dans la bouteille.</param>
    Liquid(float volumicMass, int available);

    /// <summary>
    /// Recupere la masse volumique du liquide.
    /// </summary>
    /// <returns>La masse volumique du liquide.</returns>
    float getVolumicMass();

    /// <summary>
    /// Decremente la quantite de liquide disponible dans la bouteille.
    /// </summary>
    /// <param name="amount">La quantite a retirer de la bouteille.</param>
    void decreaseAmount(int amount);

    /// <summary>
    /// Recuperer la quantite de liquide disponible dans la bouteille.
    /// </summary>
    /// <returns>La quantite disponible dans la bouteille.</returns>
    int getAvailable();

    /// <summary>
    /// Verifie qu'une certaine quantite de liquide est disponible dans la bouteille.
    /// </summary>
    /// <param name="amount">La quantite de liquide a verifier.</param>
    /// <returns>Un booleen qui vaut <b>true</b> si la quantité est disponible, <b>false</b> sinon.</returns>
    bool testAvailable(int amount);

    /// <summary>
    /// Reinitialise le test de quantite.
    /// </summary>
    void resetTest();

    /// <summary>
    /// Parametre la quantite restante de liquide dans la bouteille.
    /// </summary>
    /// <param name="amount">La nouvelle quantite de liquide.</param>
    void setAmount(int amount);
};

#endif

