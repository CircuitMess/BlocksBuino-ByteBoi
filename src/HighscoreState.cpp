#include "HighscoreState.h"
#include "EnterHighscoreState.h"
#include "EraseHighscoreState.h"
#include "ShowHighscoreState.h"

HighscoreState::HighscoreState(Display* display,HState hState,uint score) : Context(*display){
	state = new HighscoreState(display,hState);
}
void HighscoreState::loop(uint micros){

}

void HighscoreState::draw(){

}

void HighscoreState::start(){
	state->start(*this);
}

void HighscoreState::stop(){

}

void HighscoreState::enterHighscore(){
	state->stop();
	delete state;
	state = new EnterHighscoreState(&screen);

}

void HighscoreState::openHighscores(){
	state->stop();
	delete state;
	state = new ShowHighscoreState(&screen);
}

void HighscoreState::deleteHighscores(){
	state->stop();
	delete state;
	state = new EraseHighscoreState(&screen);
}

