#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include <ByteBoi.h>
#include <Audio/Piezo.h>
#include <SD.h>
#include "src/BlocksBuino.h"
#include <SleepService.h>

BlocksBuino* blocksBuino;

void setup(){
	Serial.begin(115200);
	ByteBoi.begin();
	Sleep.begin();
	ByteBoi.bindMenu();
	BatteryPopup.enablePopups(true);
	ByteBoi.setGameID("Block");
	blocksBuino=new BlocksBuino(ByteBoi.getDisplay());
	blocksBuino->unpack();
	ByteBoi.splash();
	blocksBuino->start();
}

void loop(){
	LoopManager::loop();
}