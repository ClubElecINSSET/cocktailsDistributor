#include "./HX711.h"

#include "./CupSensor.h"
#include "./Arduino.h"

CupSensor::CupSensor() {

}

CupSensor::CupSensor(int doutPin, int sckPin, int scale) {
	_doutPin = doutPin;
	_sckPin = sckPin;
	_scale = scale;
}

void CupSensor::init() {
	_sensor.begin(_doutPin, _sckPin);
	_sensor.set_scale(_scale);
	tare();
}

void CupSensor::tare() {
	_sensor.tare();
}

int CupSensor::measureLevel() {
	int measures[5];
	int measure;
	measure = _sensor.get_units(), 10;
	measures[0] = measure;
	delay(10);
	measure = _sensor.get_units(), 10;
	measures[1] = measure;
	delay(10);
	measure = _sensor.get_units(), 10;
	measures[2] = measure;
	delay(10);
	measure = _sensor.get_units(), 10;
	measures[3] = measure;
	delay(10);
	measure = _sensor.get_units(), 10;
	measures[4] = measure;
	return (measures[0] + measures[1] + measures[2] + measures[3] + measures[4]) / 5;
}

bool CupSensor::isCupAvailable() {
	int measure = measureLevel();
	return (measure > 10) ? true : false;
}

bool CupSensor::isCupRemoved() {
	int measure = measureLevel();
	return (measure < -5) ? true : false;
}
