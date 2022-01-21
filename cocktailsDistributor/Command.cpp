#include "Command.h"
#include <WString.h>

//Crée une commande
Command::Command() {
  
}

//Crée une commande avec le nom
Command::Command(String command_) {
  commandName = command_;
}

void Command::setName(String name_) {
  commandName = name_;
}

//Definis un nouveau parametre avec la position et le parametre
void Command::setParameter(String parameter, int id) {
  parametersArray[id] = parameter;
}

//Retire un parametre à la position souhaitée
void Command::deleteParameter(int id) {
  parametersArray[id] = "";
}

//Retire tous les parametres de la commande
void Command::clearParameters() {
  for(int i = 0; i < sizeof(parametersArray)-1; i++){
    parametersArray[i] = "";
  }
}

//Retourne le nom de la commande
String Command::getName(){
  return commandName;
}

//Retourne le parametre de la position souhaitée
String Command::getParameter(int id){
  return parametersArray[id];
}
