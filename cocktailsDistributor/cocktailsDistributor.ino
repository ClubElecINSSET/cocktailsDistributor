/*                                                *
 *            COCKTAILS DISTRIBUTOR               *
 *      A project by ClubElec INSSET - 2022       *
 *                                                *
 *       J.OSEMO - V.BOULANGER - S.DELIENS        *
 *                                                *
 * ---------------------------- Version dev-1.0.0 */

#include "Configuration.h"
#include <Arduino.h>
#include "Distributor.h"

Distributor _distributor;

/// <summary>
/// Initialisation du distributeur.
/// </summary>
void setup() {
	//Inscription de la configuration du distributeur
	Configuration::USE_SOUND_NOTIFICATIONS = true; //Permet d'activer/d�sactiver les annonces sonores du distributeur
    Configuration::OVERPOURING_AMOUNT = 5; //Quantit� qui peut �tre encore vers�e apr�s l'arr�t des pompes
	Configuration::MAX_COCKTAIL_INSTRUCTIONS = 10; //Nombre d'instructions maximum par cocktail
    Configuration::TOLERATED_REGRESSION_MARGIN = 10; //Marge de r�gression tol�r�e lors du versement d'un liquide
	Configuration::SOUND_VOLUME = 25; //Volume des annonces sonores (0-30)
	Configuration::CUP_WAITING_TIMEOUT = 10000; //D�lai imparti pour poser le gobelet avant l'annulation du cocktail (en ms)

	//Initialisation du port s�rie
	Serial.begin(115200);
}

/// <summary>
/// Loops this instance.
/// </summary>
void loop() {

}
