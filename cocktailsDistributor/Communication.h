#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <WString.h>
#include "Command.h"

#define STATUS_OK "OK"
#define STATUS_ERR "ERR"
#define STATUS_ANOM "ANOM"
#define STATUS_INIT "INIT"
#define STATUS_WCUP "WCUP"
#define STATUS_RCUP "RCUP"
#define STATUS_UKWN "UKWN"
#define STATUS_CAN "CAN"
#define STATUS_END "END"

class Communication {

  private:
    //Pin RX du module
    int pinRx;
    //Pin TX du module
    int pinTx;
    //message récupéré
    String message;
    //parametres récupéré
    String parameters;
    //Commande récupéré
    Command command;

    //Lecture, nettoyage et récuperation des commandes
    void readSerialPort();
    void cleanMessage();
    void identification();
    void parametersTreatment();
    int defineParaDelimiter(int paraDelimiter_);
    String cleanParameter(String parameter_);
    
    //crée la commande
    void createCommand();


  public:
  
  Communication();

  //-----------------------------------------------------------------------
  //                    IHM --> Distributeur
  //-----------------------------------------------------------------------
   
    //Récupere, crée et envoie la commande;
    Command captureCommand();

  //-----------------------------------------------------------------------
  //                    Distributeur --> IHM
  //-----------------------------------------------------------------------

    void sendStatus(String status_);
    void sendNeed(int slots[10]);
    void sendProgress(int step_, int progress_);
    void sendSlotStatus(int available_);
    void sendConfiguration(int quantities[10]);
};

#endif
