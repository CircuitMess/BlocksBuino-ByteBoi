#include "ShowHighscoreState.h"
#include "Highscore/Highscore.h"

ShowHighscoreState* ShowHighscoreState::instance = nullptr;


ShowHighscoreState::ShowHighscoreState(Screen* screen) : screen(screen){
	display = ByteBoi.getDisplay();
	baseSprite = screen->getSprite();
	instance = this;
}

void ShowHighscoreState::loop(uint time){

}

void ShowHighscoreState::start(HighscoreState& highscoreStateEnter){
	highscoreState=&highscoreStateEnter;
	Input::getInstance()->setBtnPressCallback(BTN_UP, [](){
		instance->highscoreState->deleteHighscores();
	});
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->highscoreState->returnToTitle();
	});
	Input::getInstance()->setBtnPressCallback(BTN_B, [](){
		instance->highscoreState->returnToTitle();
	});
}

void ShowHighscoreState::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_B);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);

}

void ShowHighscoreState::draw(){
	drawHighscore();
	screen->commit();

}


void ShowHighscoreState::drawHighscore(){
	baseSprite->clear(TFT_BLACK);
	baseSprite->setTextSize(1);
	baseSprite->setTextFont(1);
	baseSprite->setTextColor(TFT_BLUE);
	baseSprite->drawString("HIGHSCORES", screen->getWidth() / 2, 15);
	baseSprite->setCursor(3, 110);
	for(int i = 1; i < 6; i++){
		baseSprite->setCursor(22, 16 + i * 16);
		if(i <= Highscore.count()){
			baseSprite->printf("%d.   %.3s    %04d", i, Highscore.get(i - 1).name, Highscore.get(i - 1).score);
		}else{
			baseSprite->printf("%d.    ---   ----", i);
		}
	}
	baseSprite->drawString("Press UP to erase", screen->getWidth() / 2, 117);
}
