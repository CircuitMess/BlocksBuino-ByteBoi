#include "EraseHighscoreState.h"
#include "Highscore/Highscore.h"

EraseHighscoreState *EraseHighscoreState::instance = nullptr;

EraseHighscoreState::EraseHighscoreState(Screen* screen) : screen(screen){
	display = ByteBoi.getDisplay();
	baseSprite = screen->getSprite();
	instance = this;

}

void EraseHighscoreState::start(HighscoreState& highscoreStateEnter){
	highscoreState=&highscoreStateEnter;

	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		Highscore.clear();
		instance->highscoreState->openHighscores();
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->highscoreState->openHighscores();
	});

}

void EraseHighscoreState::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnReleaseCallback(BTN_B);

}

void EraseHighscoreState::drawWarning(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->drawString("Your really want", 30, 17);
	baseSprite->drawString("to erase your", 30, 32);
	baseSprite->drawString("highscore list?", 30, 47);
	baseSprite->setTextFont(2);
	baseSprite->setTextSize(1);
	baseSprite->setCursor(110, 100);
	baseSprite->printCenter("  A: delete     B: back");

}
void EraseHighscoreState::draw(){
	drawWarning();
	screen->commit();

}
void EraseHighscoreState::loop(uint time){

}