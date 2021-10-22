
#include "BlocksBuino.h"
//imports the SPI library (needed to communicate with Gamebuino's screen)
#include <SPI.h>
//importe the Gamebuino library
//#include <Gamebuino.h>
#include <Pins.hpp>

//creates a Gamebuino object named gb
//Gamebuino gb = Gamebuino();
BlocksBuino* BlocksBuino::instance = nullptr;

BlocksBuino::BlocksBuino(Display* display) : Context(*display), baseSprite(screen.getSprite()){
	instance = this;
	rotation = new Rotation(this);
}

BlocksBuino::~BlocksBuino(){
	rotation = nullptr;
	delete rotation;
}
void BlocksBuino::start(){
	Input::getInstance()->addListener(this);
	LoopManager::addListener(this);
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_RIGHT, 25, [](uint){
		Serial.println("Start()");
		if(!instance->game_menu && !instance->game_over){
			if(!instance->CheckBlocksCollision(1, 0)){
				instance->MoveXBlocks(1);
				instance->action = true;
			}
		}
		instance->draw();
		instance->screen.commit();
	});
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_LEFT, 25, [](uint){
		if(!instance->game_menu && !instance->game_over){
			if(!instance->CheckBlocksCollision(-1, 0)){
				instance->MoveXBlocks(-1);
				instance->action = true;
			}
		}
		instance->draw();
		instance->screen.commit();
	});
	Input::getInstance()->setButtonHeldRepeatCallback(BTN_DOWN, 25, [](uint){
		if(!instance->game_menu && !instance->game_over){
			if(instance->player_blocks1[0] > 0 && !instance->CheckBlocksCollision(0, -1)){
				instance->MoveYBlocks(-1);
				instance->action = true;
			}
		}
		instance->draw();
		instance->screen.commit();
	});
	Input::getInstance()->setBtnReleaseCallback(BTN_RIGHT,[](){
		instance->action = false;
	});
	Input::getInstance()->setBtnReleaseCallback(BTN_LEFT,[](){
		instance->action = false;
	});
	Input::getInstance()->setBtnReleaseCallback(BTN_DOWN,[](){
		instance->action = false;
	});
	draw();
	instance->screen.commit();

}

void BlocksBuino::stop(){
	Input::getInstance()->removeBtnPressCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_RIGHT);
	Input::getInstance()->removeBtnPressCallback(BTN_LEFT);
	Input::getInstance()->removeBtnReleaseCallback(BTN_LEFT);
	Input::getInstance()->removeBtnPressCallback(BTN_DOWN);
	Input::getInstance()->removeBtnReleaseCallback(BTN_DOWN);

	Input::getInstance()->removeListener(this);
}

void BlocksBuino::draw(){
	baseSprite->clear(TFT_BLACK);
	if(game_menu){
		GameMenu();
	}else if(game_over){
		GameOver();
	}else{
		PlayDraw();
	}
	screen.commit();

}
void BlocksBuino::loop(uint micros){

	if(!initialize){
		InitGame();
	}
	if(!game_menu && !game_over){
		PlayLogic();
		//Serial.println("loop()");
	}
	draw();
	screen.commit();
}

void BlocksBuino::InitGame(){
	//gb.setFrameRate(game_frame_rate);

	player_new_blocks = true;

	int i = 0;
	int j = 0;
	while(i < BLOCKS_MAX_Y){
		j = 0;
		while(j < BLOCKS_MAX_X){
			blocks_activation[i][j] = false;
			j++;
		}
		i++;
	}

	for(i = 0; i < BLOCKS_MAX_Y; i++){
		lines_completions[i] = false;
	}
	player_nb_lines_completions = 0;

	player_blocks_type = random(1, 8);
	player_blocks_rotation = 1;

	game_lines = 0;
	game_score = 0;
	if(game_force_level > 0){
		game_level = game_force_level;
	}else if(game_menu_level != 1){
		game_level = game_menu_level;
	}else{
		game_level = 1;
	}
	game_menu_level = game_level;
	game_delai = game_levels[game_level - 1];
	game_over = false;

	initialize = true;
}

void BlocksBuino::PlayDraw(){
	if(player_nb_lines_completions > 0){
		unsigned long game_animation_currentTime = millis() - game_animation_delai_prevTime;
		if(game_animation_currentTime >= game_animation_delai){

			DrawScore();
			DrawField();
			DrawBlocks();

			//update animation prevtime
			game_animation_delai_prevTime = millis();
			game_animation_counter = game_animation_default_counter;
		}else{
			//display animation
			DrawScore();
			DrawField();
			DrawAnimationBlocks();
		}
	}else{

		DrawScore();
		DrawField();
		DrawPlayerBlocks();
		DrawBlocks();

		//update animation prevtime
		game_animation_delai_prevTime = millis();
	}
}

void BlocksBuino::PlayLogic(){
	if(player_nb_lines_completions > 0){
		Serial.println("player_nb_lines_completions");
		unsigned long game_animation_currentTime = millis() - game_animation_delai_prevTime;
		if(game_animation_currentTime >= game_animation_delai){
			//END of animation
			UpdateBlocks();//remove completed blocks

			game_animation_delai_prevTime = millis();
			game_animation_counter = game_animation_default_counter;
		}
	}else{
		//GAME
		Serial.println("MovePlayerBlocks()PlayLogic");
		MovePlayerBlocks();
		//update animation prevtime
		game_animation_delai_prevTime = millis();
	}


}

void BlocksBuino::GameMenu(){
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextSize(1);
	baseSprite->setTextFont(1);
	baseSprite->setCursor(15, 1);
	baseSprite->print("-CHOOSE GAME LEVEL-");

	baseSprite->fillTriangle(46, 30, 41, 35, 51, 35, TFT_GREEN);
	baseSprite->fillTriangle(46, 58, 41, 53, 51, 53, TFT_GREEN);

	baseSprite->setCursor(2, 40);
	baseSprite->print("LEVEL: " + String(game_menu_level));

	baseSprite->setCursor(2, 100);
	baseSprite->print("A:accept          B:cancel");


}

void BlocksBuino::GameOver(){
	baseSprite->setTextColor(TFT_RED);
	baseSprite->setTextSize(2);
	baseSprite->setTextFont(1);
	baseSprite->setCursor(22, 3);
	baseSprite->print("!GAME OVER!");

	baseSprite->setTextColor(TFT_BLUE);
	baseSprite->setTextSize(1);
	baseSprite->setTextFont(1);

	baseSprite->setCursor(25, 35);
	baseSprite->print("Level: " + String(game_level));

	baseSprite->setCursor(25, 50);
	baseSprite->print("Lines: " + String(game_lines));

	baseSprite->setCursor(25, 65);
	baseSprite->print("Score: " + String(game_score));

	baseSprite->setCursor(25, 80);
	baseSprite->print("Press A to open menu!");

	baseSprite->setCursor(25, 95);
	baseSprite->print("Press B to continue!");

}

void BlocksBuino::MovePlayerBlocks(){
	unsigned long game_currentTime = millis();
	if((game_currentTime - game_prevTime) >= game_delai){
		if(!player_new_blocks && CheckBlocksCollision(0, -1)){
			if(player_blocks1[0] >= (BLOCKS_MAX_Y - 1)){
				game_over = true;//END of GAME
			}else{

				blocks_activation[player_blocks1[0]][player_blocks1[1]] = true;
				blocks_activation[player_blocks2[0]][player_blocks2[1]] = true;
				blocks_activation[player_blocks3[0]][player_blocks3[1]] = true;
				blocks_activation[player_blocks4[0]][player_blocks4[1]] = true;
				player_new_blocks = true;

				CheckLinesCompletion();
			}
		}else{
			MoveYBlocks(-1);
		}

		game_prevTime = game_currentTime;
	}

	//launch new player block
	if(player_nb_lines_completions == 0 && player_new_blocks){
		NewPlayerBlocks();

		player_new_blocks = false;
	}
}

void BlocksBuino::MoveYBlocks(int value){
	player_blocks1[0] += value;
	player_blocks2[0] += value;
	player_blocks3[0] += value;
	player_blocks4[0] += value;
}

void BlocksBuino::MoveXBlocks(int value){
	player_blocks1[1] += value;
	player_blocks2[1] += value;
	player_blocks3[1] += value;
	player_blocks4[1] += value;
}

void BlocksBuino::RotateBlocks(){
	int current_rotation = ((player_blocks_rotation + 1) > 4) ? 1 : (player_blocks_rotation + 1);

	switch(player_blocks_current_type){
		case BLOCKS_LINE:
			rotation->BlocksRotation_Type1(current_rotation);//line
			break;
		case BLOCKS_T:
			rotation->BlocksRotation_Type3(current_rotation);//T
			break;
		case BLOCKS_L:
			rotation->BlocksRotation_Type4(current_rotation);//L
			break;
		case BLOCKS_L_REVERT:
			rotation->BlocksRotation_Type5(current_rotation);//L(revert)
			break;
		case BLOCKS_S:
			rotation->BlocksRotation_Type6(current_rotation);//S
			break;
		case BLOCKS_S_REVERT:
			rotation->BlocksRotation_Type7(current_rotation);//S(revert)
			break;
	}
}

void BlocksBuino::NewPlayerBlocks(){
	player_blocks_rotation = 1;//reset to initial value

	switch(player_blocks_type){
		case BLOCKS_LINE:
			//line
			player_blocks1[0] = BLOCKS_MAX_Y + 2;//axe
			player_blocks1[1] = BLOCKS_MAX_X / 2;//axe

			player_blocks2[0] = BLOCKS_MAX_Y + 3;
			player_blocks2[1] = BLOCKS_MAX_X / 2;

			player_blocks3[0] = BLOCKS_MAX_Y + 1;
			player_blocks3[1] = BLOCKS_MAX_X / 2;

			player_blocks4[0] = BLOCKS_MAX_Y;
			player_blocks4[1] = BLOCKS_MAX_X / 2;
			break;
		case BLOCKS_CUBE:
			//cube
			player_blocks1[0] = BLOCKS_MAX_Y;//axe
			player_blocks1[1] = (BLOCKS_MAX_X / 2) - 1;//axe
			player_blocks2[0] = BLOCKS_MAX_Y;
			player_blocks2[1] = (BLOCKS_MAX_X / 2);
			player_blocks3[0] = BLOCKS_MAX_Y + 1;
			player_blocks3[1] = (BLOCKS_MAX_X / 2) - 1;
			player_blocks4[0] = BLOCKS_MAX_Y + 1;
			player_blocks4[1] = (BLOCKS_MAX_X / 2);
			break;
		case BLOCKS_T:
			//T
			player_blocks1[0] = BLOCKS_MAX_Y;//axe
			player_blocks1[1] = BLOCKS_MAX_X / 2;//axe
			player_blocks2[0] = BLOCKS_MAX_Y;
			player_blocks2[1] = (BLOCKS_MAX_X / 2) - 1;
			player_blocks3[0] = BLOCKS_MAX_Y + 1;
			player_blocks3[1] = BLOCKS_MAX_X / 2;
			player_blocks4[0] = BLOCKS_MAX_Y - 1;
			player_blocks4[1] = BLOCKS_MAX_X / 2;
			break;
		case BLOCKS_L:
			//L
			player_blocks1[0] = BLOCKS_MAX_Y + 1;//axe
			player_blocks1[1] = (BLOCKS_MAX_X / 2);//axe
			player_blocks2[0] = BLOCKS_MAX_Y;
			player_blocks2[1] = (BLOCKS_MAX_X / 2);
			player_blocks3[0] = BLOCKS_MAX_Y + 2;
			player_blocks3[1] = (BLOCKS_MAX_X / 2);
			player_blocks4[0] = BLOCKS_MAX_Y + 2;
			player_blocks4[1] = (BLOCKS_MAX_X / 2) - 1;
			break;
		case BLOCKS_L_REVERT:
			//L(revert)
			player_blocks1[0] = BLOCKS_MAX_Y + 1;//axe
			player_blocks1[1] = BLOCKS_MAX_X / 2;//axe
			player_blocks2[0] = BLOCKS_MAX_Y;
			player_blocks2[1] = BLOCKS_MAX_X / 2;
			player_blocks3[0] = BLOCKS_MAX_Y + 2;
			player_blocks3[1] = BLOCKS_MAX_X / 2;
			player_blocks4[0] = BLOCKS_MAX_Y + 2;
			player_blocks4[1] = (BLOCKS_MAX_X / 2) + 1;
			break;
		case BLOCKS_S:
			//S
			player_blocks1[0] = BLOCKS_MAX_Y;//axe
			player_blocks1[1] = (BLOCKS_MAX_X / 2) - 1;//axe
			player_blocks2[0] = BLOCKS_MAX_Y + 1;
			player_blocks2[1] = (BLOCKS_MAX_X / 2) - 1;
			player_blocks3[0] = BLOCKS_MAX_Y;
			player_blocks3[1] = (BLOCKS_MAX_X / 2);
			player_blocks4[0] = BLOCKS_MAX_Y - 1;
			player_blocks4[1] = (BLOCKS_MAX_X / 2);
			break;
		case BLOCKS_S_REVERT:
			//S(revert)
			player_blocks1[0] = BLOCKS_MAX_Y;//axe
			player_blocks1[1] = BLOCKS_MAX_X / 2;//axe
			player_blocks2[0] = BLOCKS_MAX_Y + 1;
			player_blocks2[1] = BLOCKS_MAX_X / 2;
			player_blocks3[0] = BLOCKS_MAX_Y;
			player_blocks3[1] = (BLOCKS_MAX_X / 2) - 1;
			player_blocks4[0] = BLOCKS_MAX_Y - 1;
			player_blocks4[1] = (BLOCKS_MAX_X / 2) - 1;
			break;
		default:
			//cube
			player_blocks1[0] = BLOCKS_MAX_Y;//axe
			player_blocks1[1] = BLOCKS_MAX_X / 2;//axe
			player_blocks2[0] = BLOCKS_MAX_Y;
			player_blocks2[1] = (BLOCKS_MAX_X / 2) + 1;
			player_blocks3[0] = BLOCKS_MAX_Y + 1;
			player_blocks3[1] = BLOCKS_MAX_X / 2;
			player_blocks4[0] = BLOCKS_MAX_Y + 1;
			player_blocks4[1] = (BLOCKS_MAX_X / 2) + 1;
			break;
	}

	player_blocks_current_type = player_blocks_type;
	player_blocks_type = random(1, 8);
}

bool BlocksBuino::CheckBlocksCollision(int x_value, int y_value){
	//check move right collision
	if(x_value > 0 && ((player_blocks1[1] + x_value) >= BLOCKS_MAX_X || (player_blocks2[1] + x_value) >= BLOCKS_MAX_X
					   || (player_blocks3[1] + x_value) >= BLOCKS_MAX_X || (player_blocks4[1] + x_value) >= BLOCKS_MAX_X)){
		return true;
	}
	//check move left collision
	if(x_value < 0 && ((player_blocks1[1] + x_value) < 0 || (player_blocks2[1] + x_value) < 0
					   || (player_blocks3[1] + x_value) < 0 || (player_blocks4[1] + x_value) < 0)){
		return true;
	}

	//check move down collision
	if(y_value < 0 && ((player_blocks1[0] + y_value) < 0 || (player_blocks2[0] + y_value) < 0
					   || (player_blocks3[0] + y_value) < 0 || (player_blocks4[0] + y_value) < 0)){
		return true;
	}

	//check collision with other blocks
	return (player_blocks1[0] < BLOCKS_MAX_Y && (blocks_activation[player_blocks1[0] + y_value][player_blocks1[1] + x_value])) || (player_blocks2[0] < BLOCKS_MAX_Y && blocks_activation[player_blocks2[0] + y_value][player_blocks2[1] + x_value])
		   || (player_blocks3[0] < BLOCKS_MAX_Y && blocks_activation[player_blocks3[0] + y_value][player_blocks3[1] + x_value]) || (player_blocks4[0] < BLOCKS_MAX_Y && blocks_activation[player_blocks4[0] + y_value][player_blocks4[1] + x_value]);
}

void BlocksBuino::UpdateBlocks(){
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int new_index = 0;
	boolean increment = false;

	//UPDATE activations blocks
	while(i < BLOCKS_MAX_Y){
		j = 0;

		increment = false;

		while(j < BLOCKS_MAX_X){
			if(!lines_completions[i]){
				blocks_activation[new_index][j] = blocks_activation[i][j];
				increment = true;
			}

			j++;
		}

		if(increment){
			new_index++;
		}

		i++;
	}

	i = new_index;
	while(i < BLOCKS_MAX_Y){
		j = 0;
		while(j < BLOCKS_MAX_X){
			blocks_activation[i][j] = false;
			j++;
		}
		i++;
	}

	//reset
	for(i = 0; i < BLOCKS_MAX_Y; i++){
		lines_completions[i] = false;
	}

	UpdateGameScore();

	player_nb_lines_completions = 0;
}

void BlocksBuino::UpdateGameScore(){
	game_lines += player_nb_lines_completions;
	game_score += (player_nb_lines_completions > 1) ? (player_nb_lines_completions * (game_level + 1)) : 1;

	if(game_lines >= (game_level * 10)){
		//increase game_level
		if((game_level + 1) <= GAME_LEVEL_MAX){
			game_level++;
		}
		game_delai = game_levels[game_level - 1];
	}
}

void BlocksBuino::CheckLinesCompletion(){
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int completion = false;

	while(i < BLOCKS_MAX_Y){
		j = 0;

		completion = true;

		while(j < BLOCKS_MAX_X){
			if(!blocks_activation[i][j]){
				completion = false;
				break;
			}
			j++;
		}

		if(completion){
			player_nb_lines_completions++;
		}

		lines_completions[i] = completion;
		i++;
	}

	if(player_nb_lines_completions > 0){
		//PlaySoundFxLineCompleted();
	}
}

int BlocksBuino::GetXcoordonnee(int x){
	return (field_x + ((block_draw_w * x) + 1));
}

int BlocksBuino::GetYcoordonnee(int y){
	return ((field_y - 1) - (block_draw_h * (y + 1)));
}

void BlocksBuino::DrawPlayerBlocks(){
	if(player_blocks1[0] < BLOCKS_MAX_Y){
		baseSprite->drawRect(GetXcoordonnee(player_blocks1[1]), GetYcoordonnee(player_blocks1[0]), block_draw_w, block_draw_h, TFT_RED);
	}
	if(player_blocks2[0] < BLOCKS_MAX_Y){
		baseSprite->drawRect(GetXcoordonnee(player_blocks2[1]), GetYcoordonnee(player_blocks2[0]), block_draw_w, block_draw_h, TFT_RED);
	}
	if(player_blocks3[0] < BLOCKS_MAX_Y){
		baseSprite->drawRect(GetXcoordonnee(player_blocks3[1]), GetYcoordonnee(player_blocks3[0]), block_draw_w, block_draw_h, TFT_RED);
	}
	if(player_blocks4[0] < BLOCKS_MAX_Y){
		baseSprite->drawRect(GetXcoordonnee(player_blocks4[1]), GetYcoordonnee(player_blocks4[0]), block_draw_w, block_draw_h, TFT_RED);
	}
}

void BlocksBuino::DrawScore(){
	DrawNextBlocks();

	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextSize(1);
	baseSprite->setTextFont(1);
	baseSprite->setCursor(127, 5);
	baseSprite->print(String("Lvl.") + "" + String(game_level));

	baseSprite->setCursor(127, 15);
	baseSprite->print("LINES");

	baseSprite->setCursor(127, 24);
	baseSprite->print(GetScoreString(game_lines, 3));
}

String BlocksBuino::GetScoreString(int score, int sizeBuffer){
	char buf[sizeBuffer];
	if(sizeBuffer == 3){
		sprintf(buf, "%03i", score);
	}else if(sizeBuffer == 5){
		sprintf(buf, "%05i", score);
	}else{
		return String(0);
	}

	int d1, d2, d3, d4, d5;//5 digits MAX score 99999

	d1 = buf[0] - '0';
	d2 = buf[1] - '0';
	d3 = buf[2] - '0';
	d4 = buf[3] - '0';
	d5 = buf[4] - '0';

	if(sizeBuffer == 3){
		return String(d1) + String(d2) + String(d3);
	}else if(sizeBuffer == 5){
		return String(d1) + String(d2) + String(d3) + String(d4) + String(d5);
	}
}

void BlocksBuino::DrawBlocks(){
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;

	while(i < BLOCKS_MAX_Y){
		j = 0;
		y = GetYcoordonnee(i);
		while(j < BLOCKS_MAX_X){
			x = GetXcoordonnee(j);
			if(blocks_activation[i][j]){
				//gb.display.drawRect(x, y, block_draw_w, block_draw_h);
				baseSprite->fillRect(x, y, block_draw_w, block_draw_h,TFT_BLUE);
			}
			j++;
		}
		i++;
	}
}

void BlocksBuino::DrawAnimationBlocks(){
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;

	if((game_animation_counter % 2) == 0){
		game_animation_color = !(boolean) game_animation_color;
	}

	while(i < BLOCKS_MAX_Y){
		j = 0;
		y = GetYcoordonnee(i);

		if(!lines_completions[i]){
			while(j < BLOCKS_MAX_X){
				x = GetXcoordonnee(j);
				if(blocks_activation[i][j]){
					baseSprite->fillRect(x, y, block_draw_w, block_draw_h,TFT_BLUE);
				}
				j++;
			}
		}else{
			while(j < BLOCKS_MAX_X){
				x = GetXcoordonnee(j);

				if(game_animation_color == 0){
					baseSprite->drawRect(x, y, block_draw_w, block_draw_h,TFT_BLUE);
				}else{
					baseSprite->fillRect(x, y, block_draw_w, block_draw_h,TFT_BLUE);
				}
				j++;
			}
		}
		i++;
	}

	game_animation_counter--;
}

void BlocksBuino::DrawNextBlocks(){
	int x = -2;
	int y = 10;
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextSize(1);
	baseSprite->setTextFont(1);
	baseSprite->setCursor(3, 5);
	baseSprite->print("SCORE");

	baseSprite->setCursor(4, (LCDHEIGHT / 2) + y - 15);
	baseSprite->print("NEXT");

	switch(player_blocks_type){
		case BLOCKS_LINE:
			//line
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y - block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y + (block_draw_h * 2), block_draw_w, block_draw_h, TFT_BLUE);
			break;
		case BLOCKS_CUBE:
			//cube
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x + block_draw_w, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x + block_draw_w, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			break;
		case BLOCKS_T:
			//T
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x - block_draw_w, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y - block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			break;
		case BLOCKS_L:
			//L
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y - block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x - block_draw_w, (LCDHEIGHT / 2) + y - block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			break;
		case BLOCKS_L_REVERT:
			//L(revert)
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y - block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x + block_draw_w, (LCDHEIGHT / 2) + y - block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			break;
		case BLOCKS_S:
			//S
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y - block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x + block_draw_w, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x + block_draw_w, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			break;
		case BLOCKS_S_REVERT:
			//S(revert)
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x + block_draw_w, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x + block_draw_w, (LCDHEIGHT / 2) + y - block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			break;
		default:
			//cube
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x + block_draw_w, (LCDHEIGHT / 2) + y, block_draw_w, block_draw_h, TFT_BLUE);
			baseSprite->drawRect((field_x / 2) + x + block_draw_w, (LCDHEIGHT / 2) + y + block_draw_h, block_draw_w, block_draw_h, TFT_BLUE);
			break;
	}
}

void BlocksBuino::DrawField(){
	baseSprite->drawRect(field_x, field_y, field_w, field_h, TFT_BLUE);
	baseSprite->drawRect(field_x - 2, field_y, field_w + 4, field_h, TFT_BLUE);
	//gb.display.drawLine(field_x, 0,field_x, LCDHEIGHT);
	//gb.display.drawLine(field_x2, 0, field_x2, LCDHEIGHT);
}

void BlocksBuino::ShowDebug(String message){
	//print debug line
	baseSprite->setTextColor(TFT_WHITE);
	baseSprite->setTextSize(1);
	baseSprite->setTextFont(1);
	baseSprite->setCursor(1, 1);
	baseSprite->print("[ " + message + " ]");
}


void BlocksBuino::buttonPressed(uint id){
	switch(id){
		case BTN_A :
			if(game_menu){
				game_level = game_menu_level;
				initialize = false;
				game_menu = false;
			}else if(!game_menu && !game_over){
				RotateBlocks();
			}
			break;
		case BTN_B :
			if(game_menu){
				game_menu_level = game_level;
				game_menu = false;
			}else if(game_over){
				initialize = false;
				game_over = false;
			}
			break;
		case BTN_C :
			if(!game_over && !game_menu){
				game_menu = true;
			}else if(game_menu){
				//gb.changeGame();
			}
			break;
		case BTN_UP :
			if(game_menu){
				if((game_menu_level + 1) <= GAME_LEVEL_MAX){
					game_menu_level++;
				}
			}
			break;
		case BTN_DOWN :
			if(game_menu){
				if((game_menu_level - 1) >= 1){
					game_menu_level--;
				}
			}
			break;
		case BTN_LEFT :


			break;
		case BTN_RIGHT :

			break;
	}
}









