#include "Communication.h"
#include <WString.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

//Crée une communcation
Communication::Communication() {
  
}

Communication::Communication(int pinRx_, int pinTx_) {
  pinRx = pinRx_;
  pinTx = pinTx_;
}

/*
Communication::Communication(int pinRx_, int pinTx_, *Distributor distributor_) {
  pinRx = pinRx_;
  pinTx = pinTx_;
  distributor = distributor_;
}
*/

//Initialise le module de notification sonore
void Communication::setupCommunicationModule(){
  BTSerial = SoftwareSerial(pinRx, pinTx);
  BTSerial.begin(38400);
}

//--------------------------------------------------------------------
//                          Generisation class
//--------------------------------------------------------------------

//Message
void Communication::setMessage(String message_) {
  message = message_;
}

String Communication::getMessage() {
  return message;
}


//Commande
void Communication::setCommand(Command command_) {
  command = command_;
}

Command Communication::getCommand() {
  return command;
}  

void Communication::createCommand() {
  readSerialPort();
  if(message != "") {
    command = Command();
    cleanMessage();
    identification();
    parametersTreatment();
  }
}


//--------------------------------------------------------------------
//                          Recup Command
//--------------------------------------------------------------------

//lis les données recu par le port serie
void Communication::readSerialPort() {
  message="";
  while (Serial.available()) {
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
      message += c; //makes the string readString
    }
  }
}

//Supprime les caractères de fins du message reçu (\r)
void Communication::cleanMessage() {
  message = message.substring(0, message.length()-2);
}

//identifie le nom de la commande reçu et les paramètres de celle-ci (si elle en a)
void Communication::identification() {
  int wordDelimiter = message.indexOf("(");
  String commandName = message.substring(0, wordDelimiter);
  command.setName(commandName);
  
  //-1 si il y a pas de parenthèse --> pas de parametres 
  if(wordDelimiter != -1) {
    parameters = message.substring(wordDelimiter+1, message.length()-1);    
  } else {
    parameters = "";
  }
}

//sépare et stocke les différents parametres de la commande
void Communication::parametersTreatment() {
  //Delimite les parties a diviser --> chaque parametre (entre 0 et la premiere virgule)
  int paraDelimiter = parameters.indexOf(",");
  int id = 0;
   String parameterN;

  //Continue tant que le message n'est pas vide
  while(parameters.length() != 0) {
    paraDelimiter = this->defineParaDelimiter(paraDelimiter);
    
    //On récupere le parametre et on le place dans un tableau
    parameterN = parameters.substring(0, paraDelimiter);

    //Nettoye le parametre
    parameterN = this->cleanParameter(parameterN);

    //Stocke le parametre
    command.setParameter(parameterN, id);

    //Prepare le message pour la suite (retire le parametre enregistré du message)
    parameters.remove(0, paraDelimiter+1);
    paraDelimiter = parameters.indexOf(",");
    id++;
  }
}

//Definie le delimiter selon le type du parametre
int Communication::defineParaDelimiter(int paraDelimiter) {
  int first = parameters.indexOf("[");
  int second = parameters.indexOf("]");
  if (first < paraDelimiter && second > paraDelimiter) {
    paraDelimiter = parameters.indexOf(",", parameters.indexOf(",")+1);
  }
  if (paraDelimiter > parameters.length()) {
    paraDelimiter = parameters.length();
  }
  return paraDelimiter;
}

//Retire les espaces inutiles au début et à la fin du paramètre
String Communication::cleanParameter(String parameter) {
  if (parameter.indexOf(' ') == 0) {
    parameter.remove(0, 1);
  }
  if (parameter.lastIndexOf(' ') == parameter.length()-1) {
    parameter.remove(parameter.length()-1, parameter.length());
  }
  return parameter;
}