#include "./Distributor.h"
#include "./Configuration.h"
#include "./SoundNotification.h"
#include "./CupSensor.h"
#include "./Pump.h"
#include "./Cocktail.h"
#include "./Liquid.h"
#include "./Arduino.h"
#include "./SoftwareSerial.h"

Distributor::Distributor() {
	//Définition des pompes
	_pumps[0] = Pump(53);
	_pumps[1] = Pump(52);
	_pumps[2] = Pump(51);
	_pumps[3] = Pump(50);
	_pumps[4] = Pump(49);
	_pumps[5] = Pump(48);
	_pumps[6] = Pump(47);
	_pumps[7] = Pump(46);
	_pumps[8] = Pump(45);
	_pumps[9] = Pump(44);
	//Initialisation des pompes
	_pumps[0].init();
	_pumps[1].init();
	_pumps[2].init();
	_pumps[3].init();
	_pumps[4].init();
	_pumps[5].init();
	_pumps[6].init();
	_pumps[7].init();
	_pumps[8].init();
	_pumps[9].init();
	//Création du service de communication
	// TODO: Construire un objet Communication et l'initialiser avec une instance de distributeur
	//Création du service de notification
	_soundNotifier = SoundNotification(17, 16, 6);
	_soundNotifier.init();
	//Création du service de vérification des dosages
	_cupSensor = CupSensor(14, 15, -219);
	_cupSensor.init();
}

void Distributor::addLiquid(Liquid liquid, int pumpID) {
	// TODO: Vérification du numéro de pompe, si incorrect envoyer ERR
	//if (pumpID < 0 || pumpID > sizeof(_pumps) - 1)
	_pumps[pumpID].setLiquid(liquid);
}

void Distributor::beginService() {
	// TODO: Démarrer l'écoute de la communication bluetooth en parallèle

	//DEBUG - Création d'un cocktail sans communication
	while (true) {
		Liquid water = Liquid(1, 1500);
		_pumps[0].setLiquid(water);
		Cocktail cocktail;
		cocktail.addInstruction(0, 0, 20);
		cocktail.addInstruction(1, 0, 20);
		Serial.println("I'm here (1) !");
		serveCocktail(cocktail);
	}
}

bool Distributor::waitForCup() {
	int cupTimeout = millis() + Configuration::CUP_WAITING_TIMEOUT;
	//On attend qu'un gobelet soit posé
	while (!_cupSensor.isCupAvailable()) {
		if (millis() >= cupTimeout) return false;
		else if (_cupSensor.isCupRemoved()) {
			_cupSensor.tare();
		}
	}
	return true;
}

void Distributor::serveCocktail(Cocktail cocktail) {
	//On vérifie les quantités
	Serial.println("I'm here (2) !");
	if (checkQuantities(&cocktail)) {
		//On attend qu'un gobelet soit disponible sur la plateforme
		if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(WAITING_FOR_CUP);
		if (waitForCup()) {
			//Stock suffisant - on crée le cocktail
			if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(START_POURING);
			//On exécute les instructions du cocktail les unes après les autres
			for (int i = 0; i < Configuration::MAX_COCKTAIL_INSTRUCTIONS; i++) {
				int pumpID = cocktail.getPumpID(i);
				int amount = cocktail.getAmount(i);
				if (amount != -1) {
					int amountPoured = 0;
					if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifyASync(STEP_POURING);
					//Remise à zéro du capteur de gobelet
					_cupSensor.tare();
					//Versement du liquide
					bool active = true;
					bool anomaly = false;
					float volumicMass = _pumps[pumpID].getLiquid()->getVolumicMass();
					while (active) {
						int measure = _cupSensor.measureLevel();
						//Tant que le niveau exigé n'est pas atteint, on verse le liquide
						if (measure < (amount - Configuration::OVERPOURING_AMOUNT) * volumicMass) {
							//Si le gobelet est retiré, on engage une anomalie
							if (!_cupSensor.isCupRemoved()) {
								int lastPoured = measure * volumicMass;
								_pumps[pumpID].activatePump();
								//Si la quantité mesurée est inférieure à la quantité mesurée juste avant, on engage une anomalie
								if (lastPoured < amountPoured - Configuration::TOLERATED_REGRESSION_MARGIN) {
									amountPoured += lastPoured;
									active = false;
									anomaly = true;
								}
								else {
									amountPoured = lastPoured;
									int percentageCompleted = ((float)measure / (amount * volumicMass)) * 100;
									// TODO: Envoi du statut de versement POUR(i, percentageCompleted)
								}
							}
							else {
								active = false;
								anomaly = true;
							}
						}
						else active = false;
					}
					//Instruction terminée, désactivation de la pompe
					_pumps[pumpID].deactivatePump();
					//Décrémentation de la quantité de liquide versée
					_pumps[pumpID].getLiquid()->decreaseAmount(amountPoured + Configuration::OVERPOURING_AMOUNT);
					//Si une anomalie a été engagée, on invite l'utilisateur à retirer son gobelet et on met fin au cocktail
					if (anomaly) {
						// TODO: Envoi d'un message ANOM
						if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(CUP_IS_REMOVED);
						break;
					}
				}
			}
			if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(COCKTAIL_FINISHED);
		}
	}
    else if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(COCKTAIL_UNAVAILABLE);
}

bool Distributor::checkQuantities(Cocktail* cocktail) {
	bool satisfied[10] = { true, true, true, true, true, true, true, true, true, true };
	//Réinitialise le test pour chaque liquide
	for (int i = 0; i < 10; i++) {
		_pumps[i].getLiquid()->resetTest();
	}
	//Réalise le test pour chaque instruction du cocktail
	for (int i = 0; i < Configuration::MAX_COCKTAIL_INSTRUCTIONS; i++) {
		int amount = cocktail->getAmount(i);
		if (amount != -1) {
			int pumpId = cocktail->getPumpID(i);
			if (!_pumps[pumpId].getLiquid()->testAvailable(amount)) satisfied[pumpId] = false;
		}
	}
	//Vérification des instructions non-satisfaites
	for (int i = 0; i < 10; i++) {
		if (!satisfied[i]) {
			// TODO: Envoi d'un message NEED(satisfied)
			return false;
		}
	}
	return true;
}

void Distributor::getPump(int pumpID) {
	// TODO: Envoyer un message de statut contenant le nom du liquide, sa masse volumique et sa quantité restante
}

void Distributor::getConfiguration() {
	// TODO: Envoyer un message contenant les disponibilités pour chaque liquide
}

void Distributor::emergencyStop() {
	// TODO: Stopper toutes les actions du distributeur
}