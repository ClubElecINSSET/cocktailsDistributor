/*                                                *
 *            COCKTAILS DISTRIBUTOR               *
 *      A project by ClubElec INSSET - 2022       *
 *                                                *
 *       J.OSEMO - V.BOULANGER - S.DELIENS        *
 *                                                *
 * ---------------------------- Version dev-1.0.0 */

#include "./Configuration.h"
#include "./Arduino.h"
#include "./Distributor.h"

Distributor _distributor;

/// <summary>
/// Initialisation du distributeur.
/// </summary>
void setup() {
	//Inscription de la configuration du distributeur
	Configuration::USE_SOUND_NOTIFICATIONS = true; //Permet d'activer/désactiver les annonces sonores du distributeur
    Configuration::OVERPOURING_AMOUNT = 5; //Quantité qui peut être encore versée après l'arrêt des pompes
	Configuration::MAX_COCKTAIL_INSTRUCTIONS = 10; //Nombre d'instructions maximum par cocktail
    Configuration::TOLERATED_REGRESSION_MARGIN = 10; //Marge de régression tolérée lors du versement d'un liquide
	Configuration::SOUND_VOLUME = 25; //Volume des annonces sonores (0-30)
	Configuration::CUP_WAITING_TIMEOUT = 10000; //Délai imparti pour poser le gobelet avant l'annulation du cocktail (en ms)

	//Initialisation du port série
	Serial.begin(115200);
}

/// <summary>
/// Loops this instance.
/// </summary>
void loop() {
	_distributor.beginService();
}