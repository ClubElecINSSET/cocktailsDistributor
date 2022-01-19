#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration
{
public:
	static bool USE_SOUND_NOTIFICATIONS; //Permet d'activer/désactiver les annonces sonores du distributeur
	static int OVERPOURING_AMOUNT; //Quantité qui peut être encore versée après l'arrêt des pompes
	static int MAX_COCKTAIL_INSTRUCTIONS; //Nombre d'instructions maximum par cocktail
	static int TOLERATED_REGRESSION_MARGIN; //Marge de régression tolérée lors du versement d'un liquide
	static int SOUND_VOLUME; //Volume des annonces sonores (0-30)
	static int CUP_WAITING_TIMEOUT; //Délai imparti pour poser le gobelet avant l'annulation du cocktail (en ms)
};
#endif