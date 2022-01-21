#ifndef COMMAND_H
#define COMMAND_H
#include <WString.h>

class Command {
  private:
    //nom de la commande
    String commandName;
    //Parametres des commandes
    String parametersArray[11] = {};

  public:
    Command();
    Command(String CommandName);
    void setName(String name_);
    void setParameter(String parameter, int id);
    void deleteParameter(int id);
    void clearParameters();
    String getName();
    String getParameter(int id);
    //String[11] getParameterArray();
};

#endif
