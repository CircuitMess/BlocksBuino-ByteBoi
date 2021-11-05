#ifndef BLOCKSBUINO_BYTEBOI_ENTERHIGHSCORESTATE_H
#define BLOCKSBUINO_BYTEBOI_ENTERHIGHSCORESTATE_H

#include "State.h"

class EnterHighscoreState : public State {
public:

	EnterHighscoreState(Screen* screen);

	void loop(uint time) override;

	void start(HighscoreState& highscoreStateEnter) override;

	void stop() override;

	void draw() override;

private:
	int score{};
	char *name;
	uint8_t charCursor;
	bool cursorBlink;
	bool hiscoreBlink;
	uint cursorTime;
	uint hiscoreTime;

	void drawHighscore();

	static EnterHighscoreState *instance;
	Display *display;
	Screen* screen;
	Sprite* baseSprite;
};

#endif //BLOCKSBUINO_BYTEBOI_ENTERHIGHSCORESTATE_H
