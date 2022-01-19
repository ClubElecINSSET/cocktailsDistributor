#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

#include "./SoundNotification.h"
#include "./CupSensor.h"
#include "./Pump.h"
#include "./Cocktail.h"
#include "./Arduino.h"

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
	/// Module de vérification des dosages.
	/// </summary>
	/// <returns></returns>
	CupSensor _cupSensor;

	/// <summary>
	/// Pompes installées sur le distributeur.
	/// </summary>
	Pump _pumps[10];

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
	 /// Démarre le service du distributeur.
	 /// </summary>
	 void beginService();

	 /// <summary>
	 /// Ajoute un liquide à l'emplacement spécifié.
	 /// </summary>
	 /// <param name="liquid">Liquide à ajouter.</param>
	 /// <param name="pumpID">Pompe de destination.</param>
	 /// <return>Un booléen qui vaut <b>true</b> si le liquide a pu être ajouté, <b>false</b> sinon.</return>
	 void addLiquid(Liquid liquid, int pumpID);

	 /// <summary>
	 /// Sert le cocktail demandé.
	 /// </summary>
	 /// <param name="cocktail">Cocktail demandé.</param>
	 void serveCocktail(Cocktail cocktail);

	 /// <summary>
	 /// Attend qu'un gobelet soit pose.
	 /// </summary>
	 /// <return>Un booléen qui vaut <b>true</b> si le gobelet a été posé, <b>false</b> si l'utilisateur n'a pas pose pas son gobelet avant le délai imparti.</return>
	 bool waitForCup();

	 /// <summary>
	 /// Récupère les informations liées à la pompe demandée.
	 /// </summary>
	 /// <param name="pumpID">Numéro de la pompe.</param>
	 void getPump(int pumpID);

	 /// <summary>
	 /// Récupère la configuration du distributeur.
	 /// </summary>
	 void getConfiguration();

	 /// <summary>
	 /// Stoppe toutes les actions du distributeur.
	 /// </summary>
	 void emergencyStop();
};

#endif

