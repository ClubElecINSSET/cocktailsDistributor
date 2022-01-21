#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <WString.h>
#include <SoftwareSerial.h>
#include "Command.h"

class Communication {
  private:
    //Pin RX du module
    int pinRx;
    //Pin TX du module
    int pinTx;
    //Pin BUSY du module
    int busyPin;
    //message récupéré
    String message;
    //parametres récupéré
    String parameters;
    //Commande récupéré
    Command command;
    //BTSerial
    SoftwareSerial BTSerial = SoftwareSerial(8, 9);
    //Reference Distributor
    //*Distributor distributor

    //Lecture, nettoyage et récuperation des commandes
    void readSerialPort();
    void cleanMessage();
    void identification();
    void parametersTreatment();
    int defineParaDelimiter(int paraDelimiter);
    String cleanParameter(String parameter);

  public:

    Communication();
    Communication(int pinRx_, int pinTx_);
    //Communication(int pinRx_, int pinTx_, *Distributor distributor_);
    void setupCommunicationModule();

  //-----------------------------------------------------------------------
  //                    IHM --> Distributeur
  //-----------------------------------------------------------------------
    
    void setMessage(String message_);
    String getMessage();
    
    void setCommand(Command command_);
    Command getCommand();
    
    //crée la commande complète
    void createCommand();

  //-----------------------------------------------------------------------
  //                    Distributeur --> IHM
  //-----------------------------------------------------------------------

    void sendSuccess();
    void sendError();
    void sendNeed(int slots[10]);
    void sendProgress(int step, int progress);
    void sendAnomaly();
    void sendSlotStatus(int available);
    void sendConfiguration(int quantities[10]);
    void sendInitialized();
    void sendWaitForCup();
    void sendRetireCup();
    void sendUnknown();

};

#endif
