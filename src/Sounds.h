#ifndef SOUNDS_H
#define SOUNDS_H
#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include <UI/Image.h>

enum soundsFxChannel_t {
	SND_FX_CHANNEL_1 = 0,
	SND_FX_CHANNEL_2 = 1,
	SND_FX_CHANNEL_3 = 2,
	SND_FX_CHANNEL_4 = 3
};

enum soundsFx_t {
	SND_FX_LINE_COMPLETED = 0,
	SND_FX_ROTATE         = 1,
	SND_FX_GAME_OVER      = 2,
	SND_FX_PIECE_DROP     = 3
};

const int soundfx[4][8] = {
		{0,34,75,1,0,1,7,11}, // SND_FX_LINE_COMPLETED
		{0,33,53,1,0,5,7,3},  // SND_FX_ROTATE
		{0,30,34,10,0,1,7,25}, // SND_FX_GAME_OVER
		{1,1,0,0,0,0,7,2} // SND_FX_PIECE_DROP
};
class Sounds : public LoopListener
{
public:
	Sounds();

private:
	void PlaySoundFxGameOver();
	void PlaySoundFxLineCompleted();
	void PlaySoundFxRotation();
	void PlaySoundFxPieceDrop();
	void PlaySoundFx(int fxno, int channel);
};

#endif