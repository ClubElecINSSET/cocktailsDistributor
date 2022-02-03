#include "SoundNotification.h"
#include "Configuration.h"
#include <DFRobotDFPlayerMini.h>
#include <Arduino.h>

SoundNotification::SoundNotification() {

}

SoundNotification::SoundNotification(int busyPin) {
    _busyPin = busyPin;
}

bool SoundNotification::init() {
    Serial2.begin(9600);
    pinMode(_busyPin, INPUT);
    if (!_player.begin(Serial2)) return false;
    _player.volume(Configuration::SOUND_VOLUME);
    return true;
}

void SoundNotification::notifySync(int notification) {
    _player.play(notification);
    delay(500);
    while ((!digitalRead(_busyPin)));
}

void SoundNotification::notifyASync(int notification) {
    _player.play(notification);
    delay(500);
}
