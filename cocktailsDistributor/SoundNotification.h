#ifndef SOUNDNOTIFICATION_H
#define SOUNDNOTIFICATION_H

#include "./DFRobotDFPlayerMini.h"
#include "./SoftwareSerial.h"

#define WAITING_FOR_CUP 1
#define START_POURING 2
#define COCKTAIL_UNAVAILABLE 3
#define STEP_POURING 4
#define CUP_IS_REMOVED 5
#define COCKTAIL_FINISHED 6
#define RETIRE_CUP 7

/// <summary>
/// Classe SoundNotification, organe de notification utilisateur.
/// </summary>
class SoundNotification {
private:
    /// <summary>
    /// Pin RX du module DFPlayer.
    /// </summary>
    int _rxPin;

    /// <summary>
    /// Pin TX du module DFPlayer.
    /// </summary>
    int _txPin;

    /// <summary>
    /// Pin BUSY du module DFPlayer.
    /// </summary>
    int _busyPin;

    //Liaison série utilisée pour le module

    /// <summary>
    /// Module DFPlayer.
    /// </summary>
    DFRobotDFPlayerMini _player;

public:
    /// <summary>
    /// Constructeur de SoundNotification.
    /// </summary>
    SoundNotification();

    /// <summary>
    /// Constructeur de SoundNotification, avec son <paramref name="rxModulePin"/>, son <paramref name="txModulePin"/> et son <paramref name="busyModulePin"/>.
    /// </summary>
    /// <param name="rxModulePin">Le pin RX du module DFPlayer.</param>
    /// <param name="txModulePin">Le pin TX du module DFPlayer.</param>
    /// <param name="busyModulePin">Le pin BUSY du module DFPlayer.</param>
    SoundNotification(int rxPin, int txPin, int busyPin);

    /// <summary>
    /// Initialise une SoundNotification.
    /// </summary>
    void init();

    /// <summary>
    /// Notifie l'utilisateur, attend la fin de la notification pour continuer.
    /// </summary>
    /// <param name="notification">Le <b>notificationID</b> a jouer.</param>
    void notifySync(int notification);

    /// <summary>
    /// Notifie l'utilisateur et continue directement.
    /// </summary>
    /// <param name="notification">Le <b>notificationID</b> a jouer.</param>
    void notifyASync(int notification);
};

#endif
