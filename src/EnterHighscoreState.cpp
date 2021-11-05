#include "EnterHighscoreState.h"
#include "Highscore/Highscore.h"

EnterHighscoreState *EnterHighscoreState::instance = nullptr;

EnterHighscoreState::EnterHighscoreState(Screen* screen) : screen(screen){
	display = ByteBoi.getDisplay();
	baseSprite = screen->getSprite();
	charCursor = 0;
	cursorTime = 0;
	hiscoreTime = 0;
	cursorBlink = true;
	hiscoreBlink = false;
	name = new char[4];
	strncpy(name, "AAA\0", sizeof(name));
	instance = this;


}

void EnterHighscoreState::start(HighscoreState& highscoreStateEnter){
	highscoreState=&highscoreStateEnter;

	Input::getInstance()->setBtnPressCallback(BTN_UP, [](){
		instance->cursorBlink = true;
		instance->cursorTime = millis();
		instance->name[instance->charCursor]++;
		if(instance->name[instance->charCursor] == '0') instance->name[instance->charCursor] = ' ';
		if(instance->name[instance->charCursor] == '!') instance->name[instance->charCursor] = 'A';
		if(instance->name[instance->charCursor] == '[') instance->name[instance->charCursor] = '0';
		if(instance->name[instance->charCursor] == '@') instance->name[instance->charCursor] = '!';

	});
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_UP, 200, [](uint){
		instance->cursorBlink = true;
		instance->cursorTime = millis();
		instance->name[instance->charCursor]++;
		if(instance->name[instance->charCursor] == '0') instance->name[instance->charCursor] = ' ';
		if(instance->name[instance->charCursor] == '!') instance->name[instance->charCursor] = 'A';
		if(instance->name[instance->charCursor] == '[') instance->name[instance->charCursor] = '0';
		if(instance->name[instance->charCursor] == '@') instance->name[instance->charCursor] = '!';
	});
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_DOWN, 200, [](uint){
		instance->cursorBlink = true;
		instance->cursorTime = millis();
		instance->name[instance->charCursor]--;
		if(instance->name[instance->charCursor] == ' ') instance->name[instance->charCursor] = '?';
		if(instance->name[instance->charCursor] == '/') instance->name[instance->charCursor] = 'Z';
		if(instance->name[instance->charCursor] == 31) instance->name[instance->charCursor] = '/';
		if(instance->name[instance->charCursor] == '@') instance->name[instance->charCursor] = ' ';
	});
	Input::getInstance()->setBtnPressCallback(BTN_DOWN, [](){
		instance->cursorBlink = true;
		instance->cursorTime = millis();
		instance->name[instance->charCursor]--;
		if(instance->name[instance->charCursor] == ' ') instance->name[instance->charCursor] = '?';
		if(instance->name[instance->charCursor] == '/') instance->name[instance->charCursor] = 'Z';
		if(instance->name[instance->charCursor] == 31) instance->name[instance->charCursor] = '/';
		if(instance->name[instance->charCursor] == '@') instance->name[instance->charCursor] = ' ';
	});
	Input::getInstance()->setBtnPressCallback(BTN_A, [](){
		instance->charCursor++;
		instance->cursorBlink = true;
		instance->cursorTime = millis();
	});
	Input::getInstance()->setBtnPressCallback(BTN_LEFT, [](){
		if(instance->charCursor > 0){
			instance->charCursor--;
			instance->cursorBlink = true;
			instance->cursorTime = millis();
		}
	});
	Input::getInstance()->setBtnPressCallback(BTN_RIGHT, [](){
		if(instance->charCursor < 2){
			instance->charCursor++;
			instance->cursorBlink = true;
			instance->cursorTime = millis();
		}
	});

}


void EnterHighscoreState::drawHighscore(){
	baseSprite->setCursor(45, 8);
	baseSprite->setTextFont(2);
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextSize(1);
	baseSprite->print("ENTER NAME");
	baseSprite->setCursor(50, 75);

	if(hiscoreBlink && highscoreState->score > Highscore.get(0).score){
		baseSprite->print("NEW HIGH!");
	}else{
		baseSprite->setCursor(50, 90);
		baseSprite->printf("SCORE: %3d", highscoreState->score);
	}
	baseSprite->setCursor(60, 40);
	baseSprite->print(name[0]);
	baseSprite->setCursor(75, 40);
	baseSprite->print(name[1]);
	baseSprite->setCursor(90, 40);
	baseSprite->print(name[2]);
	if(cursorBlink){
		baseSprite->drawFastHLine(57 + 15 * charCursor, 55, 12, TFT_WHITE);
	}
}

void EnterHighscoreState::stop(){

	Input::getInstance()->removeBtnPressCallback(BTN_A);
	Input::getInstance()->removeBtnReleaseCallback(BTN_A);
	Input::getInstance()->removeBtnPressCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnPressCallback(BTN_LEFT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_LEFT);
	Input::getInstance()->removeBtnPressCallback(BTN_DOWN);
	Input::getInstance()->removeBtnReleaseCallback(BTN_DOWN);
	Input::getInstance()->removeBtnPressCallback(BTN_UP);
	Input::getInstance()->removeBtnReleaseCallback(BTN_UP);
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_UP, 0, nullptr);
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_DOWN, 0, nullptr);
	highscoreState->score=0;
}
void EnterHighscoreState::draw(){
	drawHighscore();
	screen->commit();

}

void EnterHighscoreState::loop(uint time){
	baseSprite->clear(TFT_BLACK);
	hiscoreTime += time;
	if(hiscoreTime >= 1000000){
		hiscoreTime = 0;
		hiscoreBlink = !hiscoreBlink;
	}
	cursorTime += time;
	if(cursorTime >= 350000){
		cursorTime = 0;
		cursorBlink = !cursorBlink;
	}
	if(charCursor >2 || charCursor<0){
		Score newScore{};
		strcpy(newScore.name, name);
		newScore.score = highscoreState->score;
		Highscore.add(newScore);
		highscoreState->openHighscores();
	}

}