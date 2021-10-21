#include "Rotation.h"
#include "BlocksBuino.h"

Rotation::Rotation(BlocksBuino *blocksBuino) : blocksBuino(blocksBuino){

}

void Rotation::BlocksRotation_Type1(int current_rotation){
	if (current_rotation == 2 || current_rotation == 4) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0])
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 2,blocksBuino->player_blocks1[0])) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1] - 1;

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] - 2;

			SetRotation(current_rotation);
		}
	}
	else {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 2) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1)
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] + 2;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1];

			SetRotation(current_rotation);
		}
	}
}

void Rotation::BlocksRotation_Type3(int current_rotation){
	if (current_rotation == 1) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1)
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] - 1;

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1];

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 2) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0])
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] - 1;

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1];

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 3) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1],blocksBuino->player_blocks1[0] + 1) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] - 1)
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0])) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] + 1;

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 4) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0])
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] - 1;

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1];

			SetRotation(current_rotation);
		}
	}
}

void Rotation::BlocksRotation_Type4(int current_rotation){
	if (current_rotation == 1) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] - 1) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1)
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0] + 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] - 1;

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 2) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0])
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0] + 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] - 1;

			blocksBuino->player_blocks3[0] =blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks3[1] =blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] + 1;

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 3) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] - 1)
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks3[0] =blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks3[1] =blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] + 1;

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 4) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0])
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1] - 1;
			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0];

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] - 1;

			SetRotation(current_rotation);
		}
	}
}

void Rotation::BlocksRotation_Type5(int current_rotation){
	if (current_rotation == 1) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] - 1) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1)
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0] + 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks4[0] =blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks4[1] =blocksBuino->player_blocks1[1] + 1;

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 2) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0])
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1,blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] - 1;
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] + 1;

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 3) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] - 1)
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] - 1;

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 4) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0])
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks3[0] =blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1] - 1;

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] - 1;

			SetRotation(current_rotation);
		}
	}
}

void Rotation::BlocksRotation_Type6(int current_rotation){
	if (current_rotation == 1 || current_rotation == 3) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1,blocksBuino->player_blocks1[0])
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1,blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] + 1;

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 2 || current_rotation == 4) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] - 1)
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks3[0] =blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks4[1] =blocksBuino->player_blocks1[1] - 1;

			SetRotation(current_rotation);
		}
	}
}

void Rotation::BlocksRotation_Type7(int current_rotation){
	if (current_rotation == 1 || current_rotation == 3) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0])
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0] - 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1] - 1;

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] - 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] - 1;

			SetRotation(current_rotation);
		}
	}
	else if (current_rotation == 2 || current_rotation == 4) {
		if (!CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] + 1, blocksBuino->player_blocks1[0]) && !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1], blocksBuino->player_blocks1[0] + 1)
			&& !CheckBlocksRotationCollision(blocksBuino->player_blocks1[1] - 1, blocksBuino->player_blocks1[0] + 1)) {
			blocksBuino->player_blocks2[0] = blocksBuino->player_blocks1[0];
			blocksBuino->player_blocks2[1] = blocksBuino->player_blocks1[1] + 1;

			blocksBuino->player_blocks3[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks3[1] = blocksBuino->player_blocks1[1];

			blocksBuino->player_blocks4[0] = blocksBuino->player_blocks1[0] + 1;
			blocksBuino->player_blocks4[1] = blocksBuino->player_blocks1[1] - 1;

			SetRotation(current_rotation);
		}
	}
}

bool Rotation::CheckBlocksRotationCollision(int x_new_value, int y_new_value){
	if (x_new_value >= BLOCKS_MAX_X) {// || y_new_value >= BLOCKS_MAX_X)) {
		return true;
	}
	if (x_new_value < 0 || y_new_value < 0) {
		return true;
	}

	// down collision
	//if (y_value < 0 && ((player_blocks1[0] + y_value) < 0 || (player_blocks2[0] + y_value) < 0
	//  || (player_blocks3[0] + y_value) < 0  || (player_blocks4[0] + y_value) < 0)) {
	//  return true;
	//}

	return blocksBuino->blocks_activation[y_new_value][x_new_value];
}

void Rotation::SetRotation(int current_rotation){
	//PlaySoundFxRotation();
	blocksBuino->player_blocks_rotation = current_rotation;
}
