#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

#include "SoundNotification.h"
#include "CupSensor.h"
#include "Pump.h"
#include "Cocktail.h"
#include "Communication.h"
#include <Arduino.h>

/// <summary>
/// Classe principale du distributeur de cocktails.
/// </summary>
class Distributor
{

private:
	/// <summary>
	/// Module de notification sonore.
	/// </summary>
	SoundNotification _soundNotifier;

	/// <summary>
	/// Module de v�rification des dosages.
	/// </summary>
	/// <returns></returns>
	CupSensor _cupSensor;

	/// <summary>
	/// Pompes install�es sur le distributeur.
	/// </summary>
	Pump _pumps[10];

	/// <summary>
	/// Gestion des commandes entrantes/sortantes 
	/// </summary>
	Communication _communication;

	/// <summary>
	 /// Verification des quantites de chaque instruction du cocktail.
	 /// </summary>
	 /// <returns>Un booleen qui vaut <b>true</b> si le cocktail peut etre realise, <b>false</b> sinon.</returns>
	bool checkQuantities(Cocktail* cocktail);

 public:
	 /// <summary>
	 /// Constructeur de Distributor.
	 /// </summary>
	 Distributor();

	 /// <summary>
	 /// Attend qu'une commande soit reçue par bluetooth.
	 /// </summary>
	 void receivingCommand();

	 /// <summary>
	 /// Execute la commande reçue.
	 /// </summary>
	 void executeCommand();

	 /// <summary>
	 /// Ajoute un liquide � l'emplacement sp�cifi�.
	 /// </summary>
	 /// <param name="liquid">Liquide � ajouter.</param>
	 /// <param name="pumpID">Pompe de destination.</param>
	 /// <return>Un bool�en qui vaut <b>true</b> si le liquide a pu �tre ajout�, <b>false</b> sinon.</return>
	 void addLiquid(Liquid liquid, int pumpID);

	 /// <summary>
	 /// Sert le cocktail demand�.
	 /// </summary>
	 /// <param name="cocktail">Cocktail demand�.</param>
	 void serveCocktail(Cocktail cocktail);

	 /// <summary>
	 /// Attend qu'un gobelet soit pose.
	 /// </summary>
	 /// <return>Un bool�en qui vaut <b>true</b> si le gobelet a �t� pos�, <b>false</b> si l'utilisateur n'a pas pose pas son gobelet avant le d�lai imparti.</return>
	 bool waitForCup();

	 /// <summary>
	 /// R�cup�re les informations li�es � la pompe demand�e.
	 /// </summary>
	 /// <param name="pumpID">Num�ro de la pompe.</param>
	 void getPumpInformation(int pumpID);

	 /// <summary>
	 /// R�cup�re la configuration du distributeur.
	 /// </summary>
	 void getConfiguration();

	 /// <summary>
	 /// Stoppe toutes les actions du distributeur.
	 /// </summary>
	 void emergencyStop();
};

#endif
