#ifndef BLOCKSBUINO_BYTEBOI_ERASEHIGHSCORESTATE_H
#define BLOCKSBUINO_BYTEBOI_ERASEHIGHSCORESTATE_H

#include "State.h"

class EraseHighscoreState : public State {
public:

	EraseHighscoreState(Screen* screen);

	void loop(uint time) override;

	void start(HighscoreState& highscoreStateEnter) override;

	void stop() override;

	void draw() override;

private:

	void drawWarning();

	static EraseHighscoreState *instance;
	Display *display;
	Screen* screen;
	Sprite *baseSprite;
};

#endif //BLOCKSBUINO_BYTEBOI_ERASEHIGHSCORESTATE_H
