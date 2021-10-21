
#include "Sounds.h"

Sounds::Sounds(){

}

void Sounds::PlaySoundFxGameOver() {
	PlaySoundFx(SND_FX_GAME_OVER, SND_FX_CHANNEL_1);
}

void Sounds::PlaySoundFxLineCompleted() {
	PlaySoundFx(SND_FX_LINE_COMPLETED, SND_FX_CHANNEL_1);
}

void Sounds::PlaySoundFxRotation() {
	PlaySoundFx(SND_FX_ROTATE, SND_FX_CHANNEL_1);
}

void Sounds::PlaySoundFxPieceDrop() {
	PlaySoundFx(SND_FX_PIECE_DROP, SND_FX_CHANNEL_1);
}
void Sounds::PlaySoundFx(int fxno, int channel){
	/*gb.sound.command(0,soundfx[fxno][6],0,channel); // set volume
	gb.sound.command(1,soundfx[fxno][0],0,channel); // set waveform
	gb.sound.command(2,soundfx[fxno][5],-soundfx[fxno][4],channel); // set volume slide
	gb.sound.command(3,soundfx[fxno][3],soundfx[fxno][2]-58,channel); // set pitch slide
	gb.sound.playNote(soundfx[fxno][1],soundfx[fxno][7],channel); // play note*/
}