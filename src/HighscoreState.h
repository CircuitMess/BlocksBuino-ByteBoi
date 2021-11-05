#ifndef BLOCKSBUINO_BYTEBOI_HIGHSCORESTATE_H
#define BLOCKSBUINO_BYTEBOI_HIGHSCORESTATE_H

#include <Arduino.h>
#include <ByteBoi.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include <Support/Context.h>

class State;
enum HState{
	showHS,enterHS,eraseHS
};
class HighscoreState : public Context, public LoopListener {
public:
	HighscoreState(Display* display,HState hState ,uint score = 0);

	void loop(uint micros) override;

	void draw() override;

	void start() override;

	void stop() override;

	uint score = 0;

private:
	void enterHighscore();

	void openHighscores();

	void deleteHighscores();

	State* state;
	static HighscoreState* instance;
	Display* display;
	Sprite* baseSprite;
};


#endif //BLOCKSBUINO_BYTEBOI_HIGHSCORESTATE_H
