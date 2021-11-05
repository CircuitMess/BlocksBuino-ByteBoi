#ifndef BLOCKSBUINO_BYTEBOI_SHOWHIGHSCORESTATE_H
#define BLOCKSBUINO_BYTEBOI_SHOWHIGHSCORESTATE_H

#include "State.h"

class ShowHighscoreState : public State{
public:
	ShowHighscoreState(Screen* screen);

	void loop(uint time) override;

	void start(HighscoreState& highscoreStateEnter) override;

	void stop() override;

	void draw() override;

private:
	static ShowHighscoreState* instance;

	Display* display;

	Sprite* baseSprite;
	Screen* screen;

	void drawHighscore();
};

#endif //BLOCKSBUINO_BYTEBOI_SHOWHIGHSCORESTATE_H
