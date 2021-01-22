#pragma once
#include "Playfield.h"
#include "Tetromino.h"

class Controls
{
public:
	Controls();
	void enableKeyboardInput();
	void handlePlayerMovement(PlayField&, Tetromino&); 
	void handlePlayerRotation(PlayField&, Tetromino&);
private:
	bool bKey[4];
	bool bRotateHold;
};

