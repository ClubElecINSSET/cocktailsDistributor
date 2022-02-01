#include "Distributor.h"
#include "Configuration.h"
#include "SoundNotification.h"
#include "CupSensor.h"
#include "Pump.h"
#include "Cocktail.h"
#include "Liquid.h"
#include "Command.h"
#include <Arduino.h>

Distributor* Distributor::_distributor = NULL;

Distributor::Distributor() {
	//Marquage de l'objet en cours
	Distributor::_distributor = this;
	//Initialisation du port s�rie
	Serial.begin(9600);
	//Definition des pompes
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
	//Creation du service de communication
	_communication = Communication();
	//Parametrage d'une interruption sur le broche de reception des commandes (front montant)
	attachInterrupt(digitalPinToInterrupt(19), Distributor::handleCommand, RISING);
	//Creation du service de notification
	_soundNotifier = SoundNotification(6);
	// TODO : Envoyer un message d'erreur si le module sonore n'est pas initialisé
	//if (!_soundNotifier.init()) _communication.sendStatus(STATUS_ERROR);
	if (!_soundNotifier.init()) Serial.println("ERR");
	//Creation du service de verification des dosages
	_cupSensor = CupSensor(14, 15, -219);
	_cupSensor.init();

	//DEBUG : Création d'un cocktail
	addLiquid(Liquid(1.0, 1500), 0);
	Cocktail cock;
	cock.addInstruction(0, 0, 20);
	serveCocktail(cock);
}

void Distributor::handleCommand() {
	Distributor::_distributor->receivingCommand();
}

void Distributor::addLiquid(Liquid liquid, int pumpID) {
	// TODO: V�rification du num�ro de pompe, si incorrect envoyer ERR
	//if (pumpID < 0 || pumpID > sizeof(_pumps) - 1) _communication.sendStatus(STATUS_ERROR);
	_pumps[pumpID].setLiquid(liquid);
}

void Distributor::receivingCommand() {
	_communication.createCommand();
	executeCommand();
}

void Distributor::executeCommand() {
	Command command = _communication.getCommand();
	String name = command.getName();
	if (name == "LIQU") {
		//Ajout d'un nouveau liquide
		float volumicMass = command.getParameter(0).toFloat();
		int available = command.getParameter(1).toInt();
		int pumpID = command.getParameter(2).toInt();
		addLiquid(Liquid(volumicMass, available), pumpID);
	}
	else if (name == "COCK") {
		//Demande d'un cocktail
		Cocktail cocktail;
		for (int i = 0; i < 10; i++) {
			cocktail.addInstruction(i, 0, 20); // TODO: Modifier pour ajouter les instructions reçues : 10 paramètres, pas 20 ?
		}
		serveCocktail(cocktail);
	}
	else if (name == "SLOT") {
		//Récupération de l'état d'un emplacement
		int pumpID = command.getParameter(0).toInt();
		getPumpInformation(pumpID);
	}
	else if (name == "CONF") {
		//Récupération de la configuration du distributeur
		getConfiguration();
	}
	else if (name = "STOP") {
		//Arrêt du distributeur
		emergencyStop();
	}
	else {
		//Aucune commande reconnue
		//communication.sendStatus(STATUS_UKWN);
	}
}

bool Distributor::waitForCup() {
	int cupTimeout = millis() + Configuration::CUP_WAITING_TIMEOUT;
	//On attend qu'un gobelet soit pose
	Serial.println("Attente gobelet...");
	while (!_cupSensor.isCupAvailable()) {
		if (millis() >= cupTimeout) return false;
		else if (_cupSensor.isCupRemoved()) {
			_cupSensor.tare();
		}
	}
	return true;
}

void Distributor::serveCocktail(Cocktail cocktail) {
	//On v�rifie les quantit�s
	if (checkQuantities(&cocktail)) {
		//On attend qu'un gobelet soit disponible sur la plateforme
		if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(WAITING_FOR_CUP);
		if (waitForCup()) {
			//Stock suffisant - on cr�e le cocktail
			if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(START_POURING);
			//On ex�cute les instructions du cocktail les unes apr�s les autres
			for (int i = 0; i < Configuration::MAX_COCKTAIL_INSTRUCTIONS; i++) {
				int pumpID = cocktail.getPumpID(i);
				int amount = cocktail.getAmount(i);
				if (amount != -1) {
					int amountPoured = 0;
					if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifyASync(STEP_POURING);
					//Remise a zero du capteur de gobelet
					_cupSensor.tare();
					//Versement du liquide
					bool active = true;
					bool anomaly = false;
					float volumicMass = _pumps[pumpID].getLiquid()->getVolumicMass();
					while (active) {
						int measure = _cupSensor.measureLevel();
						//Tant que le niveau exige n'est pas atteint, on verse le liquide
						if (measure < (amount - Configuration::OVERPOURING_AMOUNT) * volumicMass) {
							//Si le gobelet est retire, on engage une anomalie
							if (!_cupSensor.isCupRemoved()) {
								int lastPoured = measure * volumicMass;
								_pumps[pumpID].activatePump();
								//Si la quantite mesuree est inferieure a la quantite mesuree juste avant, on engage une anomalie
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
					//Instruction terminee, desactivation de la pompe
					_pumps[pumpID].deactivatePump();
					//Decrementation de la quantite de liquide versee
					_pumps[pumpID].getLiquid()->decreaseAmount(amountPoured + Configuration::OVERPOURING_AMOUNT);
					//Si une anomalie a ete engagee, on invite l'utilisateur a retirer son gobelet et on met fin au cocktail
					if (anomaly) {
						// TODO: Envoi d'un message ANOM
						//_communication.sendStatus(STATUS_ANOMALY);
						if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(CUP_IS_REMOVED);
						break;
					}
				}
			}
			if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(COCKTAIL_FINISHED);
			// TODO : Envoyer un message informant que le cocktail est terminé
			//_communication.sendStatus(STATUS_ENDED);
		}
		// TODO : Enregistrer un message d'annulation de cocktail et envoyer un message d'annulation à la tablette
		else if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(COCKTAIL_FINISHED);
		//_communication.sendStatus(STATUS_CANCELED);
	}
    else if (Configuration::USE_SOUND_NOTIFICATIONS) _soundNotifier.notifySync(COCKTAIL_UNAVAILABLE);
}

bool Distributor::checkQuantities(Cocktail* cocktail) {
	bool satisfied[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	//Reinitialise le test pour chaque liquide
	for (int i = 0; i < 10; i++) {
		_pumps[i].getLiquid()->resetTest();
	}
	//Realise le test pour chaque instruction du cocktail
	for (int i = 0; i < Configuration::MAX_COCKTAIL_INSTRUCTIONS; i++) {
		int amount = cocktail->getAmount(i);
		if (amount != -1) {
			int pumpId = cocktail->getPumpID(i);
			if (!_pumps[pumpId].getLiquid()->testAvailable(amount)) satisfied[pumpId] = 0;
		}
	}
	//Si au moins une instruction est insatisfaite, on envoie une commande de réapprovisionnement
	for (int i = 0; i < 10; i++) {
		if (!satisfied[i]) {
			// TODO: communication.sendNeed(satisfied);
			return false;
		}
	}
	return true;
}

void Distributor::getPumpInformation(int pumpID) {
	// TODO: Envoyer un message de statut contenant le nom du liquide, sa masse volumique et sa quantit� restante
	//communication.sendSlot(_pumps[pumpID].getLiquid()->getAvailable());
}

void Distributor::getConfiguration() {
	// TODO: Envoyer un message contenant les disponibilit�s pour chaque liquide
	int conf[10];
	for (int i = 0; i < 10; i++) {
		conf[i] = _pumps[i].getLiquid()->getAvailable();
	}
	//communication.sendConfiguration(conf);
}

void Distributor::emergencyStop() {
	// TODO: Stopper toutes les actions du distributeur
	//communication.sendStatus(STATUS_OK);
}
