#ifndef BLOCKSBUINO_BYTEBOI_STATE_H
#define BLOCKSBUINO_BYTEBOI_STATE_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/Input.h>
#include <Loop/LoopManager.h>
#include <Display/Sprite.h>
#include <ByteBoi.h>
#include "HighscoreState.h"

class HighscoreState;
class State{
public:
	virtual ~State();

	virtual void start(HighscoreState &highscoreStateEnter) = 0;

	virtual void stop(){};

	virtual void loop(uint time) = 0;

	virtual void draw() = 0;
private:
protected:
	HighscoreState *highscoreState;
};
#endif //BLOCKSBUINO_BYTEBOI_STATE_H
