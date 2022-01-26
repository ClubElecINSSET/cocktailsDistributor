#ifndef COCKTAIL_H
#define COCKTAIL_H

#include "Liquid.h"
#include "CupSensor.h"
#include "SoundNotification.h"

/// <summary>
/// Classe Cocktail, element que demande l'utilisateur.
/// </summary>
class Cocktail {
private:
    /// <summary>
    /// Instructions de dosage (pompeID et quantit�) du cocktail.
    /// </summary>
    int _instructions[10][2] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
public:
    /// <summary>
    /// Constructeur de Cocktail.
    /// </summary>
    Cocktail();

    /// <summary>
    /// Ajoute une instruction de dosage a une certaine position du cocktail.
    /// </summary>
    /// <param name="instructionID">La position de l'instruction</param>
    /// <param name="pumpID">Le numero de pompe qui doit etre activee</param>
    /// <param name="amount">La quantite de ce liquide qui doit etre versee dans le gobelet.</param>
    void addInstruction(int instructionID, int pumpID, int amount);

    /// <summary>
    /// Recupere le numero de pompe de <paramref name="instructionID"/>.
    /// </summary>
    /// <param name="instructionID">La position de l'instruction.</param>
    /// <returns>Le numero de pompe de l'instruction souhaitee.</returns>
    int getPumpID(int instructionID);

    /// <summary>
    /// Recupere la quantite a verser du liquide en position <paramref name="pos"/>.
    /// </summary>
    /// <param name="instructionID">La position de l'instruction.</param>
    /// <returns>La quantite a verser.</returns>
    int getAmount(int instructionID);
};

#endif
