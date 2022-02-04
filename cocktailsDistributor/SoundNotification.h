#ifndef SOUNDNOTIFICATION_H
#define SOUNDNOTIFICATION_H

#include <DFRobotDFPlayerMini.h>

#define SOUND_ADD_LIQUID 1
#define SOUND_USER_CALL 2
#define SOUND_WAITING_CUP 3
#define SOUND_START_COCKTAIL 4
#define SOUND_POURING_STEP 5
#define SOUND_COCKTAIL_FINISHED 6
#define SOUND_CUP_REMOVAL 7
#define SOUND_COCKTAIL_CANCELED 8
#define SOUND_COCKTAIL_UNAVAILABLE 9
#define SOUND_ANOMALY 10
#define SOUND_EXPORT_COMPLETE 11

/// <summary>
/// Classe SoundNotification, organe de notification utilisateur.
/// </summary>
class SoundNotification {
private:
    /// <summary>
    /// Pin BUSY du module DFPlayer.
    /// </summary>
    int _busyPin;

    //Liaison s�rie utilis�e pour le module

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
    SoundNotification(int busyPin);

    /// <summary>
    /// Initialise une SoundNotification.
    /// </summary>
    bool init();

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
