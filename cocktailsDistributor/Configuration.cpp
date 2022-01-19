#include "./Configuration.h"

bool Configuration::USE_SOUND_NOTIFICATIONS = true; //Permet d'activer/désactiver les annonces sonores du distributeur
int Configuration::OVERPOURING_AMOUNT = 5; //Quantité qui peut être encore versée après l'arrêt des pompes
int Configuration::MAX_COCKTAIL_INSTRUCTIONS = 10; //Nombre d'instructions maximum par cocktail
int Configuration::TOLERATED_REGRESSION_MARGIN = 10; //Marge de régression tolérée lors du versement d'un liquide
int Configuration::SOUND_VOLUME = 25; //Volume des annonces sonores (0-30)
int Configuration::CUP_WAITING_TIMEOUT = 10000; //Délai imparti pour poser le gobelet avant l'annulation du cocktail (en ms)