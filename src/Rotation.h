#ifndef BLOCKSBUINO_ROTATION_H
#define BLOCKSBUINO_ROTATION_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>

class BlocksBuino;
class Rotation{
public:
	Rotation(BlocksBuino* blocksBuino);

	void BlocksRotation_Type1(int current_rotation);
	void BlocksRotation_Type3(int current_rotation);
	void BlocksRotation_Type4(int current_rotation);
	void BlocksRotation_Type5(int current_rotation);
	void BlocksRotation_Type6(int current_rotation);
	void BlocksRotation_Type7(int current_rotation);
private:
	bool CheckBlocksRotationCollision(int x_new_value, int y_new_value);
	void SetRotation(int current_rotation);
	BlocksBuino* blocksBuino;

};

#endif //BLOCKSBUINO_ROTATION_H
