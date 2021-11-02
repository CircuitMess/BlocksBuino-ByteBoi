#ifndef BLOCKSBUINO_BLOCKSBUINO_H
#define BLOCKSBUINO_BLOCKSBUINO_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include <Support/Context.h>
#include "Rotation.h"
#include <Input/Input.h>

#define GAME_LEVEL_MAX 9
#define BLOCKS_MAX_Y 20
#define BLOCKS_MAX_X 13
#define LCDHEIGHT 120

extern const byte PROGMEM logo[];

enum type_blocks {
	BLOCKS_LINE = 1,
	BLOCKS_CUBE = 2,
	BLOCKS_T = 3,
	BLOCKS_L = 4,
	BLOCKS_L_REVERT = 5,
	BLOCKS_S = 6,
	BLOCKS_S_REVERT = 7
};

class BlocksBuino : public Context, public LoopListener, private InputListener {
public:
	BlocksBuino(Display* display);

	virtual ~BlocksBuino();

	Rotation* rotation;
	void loop(uint micros) override;

	void draw() override;

	void start() override;

	void stop() override;

	short player_blocks_type = BLOCKS_LINE;
	short player_blocks_current_type = BLOCKS_LINE;
	short player_blocks_rotation = 1; //1,2,3,4
	short player_blocks1[2]; //rotation point y,x
	short player_blocks2[2];
	short player_blocks3[2];
	short player_blocks4[2];

	bool blocks_activation[BLOCKS_MAX_Y][BLOCKS_MAX_X];

private:
	void InitGame();
	void PlayLogic();
	void PlayDraw();
	void GameMenu();
	void GameOver();
	void MovePlayerBlocks();
	void MoveYBlocks(int value);
	void MoveXBlocks(int value);
	void RotateBlocks();
	void NewPlayerBlocks();
	bool CheckBlocksCollision(int x_value, int y_value);
	void UpdateBlocks();
	void UpdateGameScore();
	void CheckLinesCompletion();
	int GetXcoordonnee(int x);
	int GetYcoordonnee(int y);
	void DrawPlayerBlocks();
	void DrawScore();
	String GetScoreString(int score, int sizeBuffer);
	void DrawBlocks();
	void DrawAnimationBlocks();
	void DrawNextBlocks();
	void DrawField();
	void ShowDebug(String message);

	//game variables
	bool initialize = false;
	int game_frame_rate = 20;//default 20
	bool game_over = false;
	bool game_menu = true;
	const short game_force_level = 0;
	short game_level = 1; // 1,2,3,4,5,6,7,8,9 Levels
	short game_menu_level = game_level;
	int game_levels[GAME_LEVEL_MAX] = { 300, 275, 250, 225, 200, 175, 150, 125, 100 };
	int game_score = 0;
	int game_lines = 0;
	unsigned long game_delai = game_levels[game_level];
	unsigned long game_prevTime = 0;
	bool action = false;

	//animation variables
	unsigned short game_animation_default_counter = 60;
	short game_animation_counter = game_animation_default_counter;
	short game_animation_color = 0;
	const unsigned int game_animation_delai = 1000;
	unsigned long game_animation_delai_prevTime = millis();

	//blocks variables
	const short block_w = 4;
	const short block_draw_w = block_w + 2;
	const short block_h = 4;
	const short block_draw_h = block_h + 2;

	bool player_new_blocks = true;
	short player_nb_lines_completions = 0;
	bool lines_completions[BLOCKS_MAX_Y];

	//field variables 84x48
	const int field_x = 39; // 16
	const int field_y = LCDHEIGHT + 1;
	const int field_w = 80;// 10 BLOCKS MAX // 42
	const int field_h = -(LCDHEIGHT) - 4;// - 4);// 12 BLOCKS MAX

	Sprite *baseSprite;
	static BlocksBuino* instance;
	Color* menuBuffer = nullptr;

	void buttonPressed(uint id) override;
};
#endif //BLOCKSBUINO_BLOCKSBUINO_H
