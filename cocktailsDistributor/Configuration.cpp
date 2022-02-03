#include "Configuration.h"

bool Configuration::USE_SOUND_NOTIFICATIONS = true; //Permet d'activer/d�sactiver les annonces sonores du distributeur
int Configuration::OVERPOURING_AMOUNT = 5; //Quantit� qui peut �tre encore vers�e apr�s l'arr�t des pompes
int Configuration::MAX_COCKTAIL_INSTRUCTIONS = 10; //Nombre d'instructions maximum par cocktail
int Configuration::TOLERATED_REGRESSION_MARGIN = 10; //Marge de r�gression tol�r�e lors du versement d'un liquide
int Configuration::SOUND_VOLUME = 25; //Volume des annonces sonores (0-30)
int Configuration::CUP_WAITING_TIMEOUT = 10000; //D�lai imparti pour poser le gobelet avant l'annulation du cocktail (en ms)
