#include "./SoundNotification.h"

#include "./Configuration.h"
#include "./DFRobotDFPlayerMini.h"
#include "./SoftwareSerial.h"
#include "./Arduino.h"

SoundNotification::SoundNotification() {

}

SoundNotification::SoundNotification(int rxPin, int txPin, int busyPin) {
    _rxPin = rxPin;
    _txPin = txPin;
    _busyPin = busyPin;
}

void SoundNotification::init() {
    SoftwareSerial serial(_rxPin, _txPin);
    serial.begin(9600);
    pinMode(_busyPin, INPUT);
    if (!_player.begin(serial)) {
        Serial.println(F("Unable to begin:"));
    }
    _player.volume(Configuration::SOUND_VOLUME);
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
