#include "Controls.h"
#include <Windows.h>

Controls::Controls()
	: bRotateHold(false)
{
	enableKeyboardInput();
}

void Controls::enableKeyboardInput()
{
	for (int k = 0; k < 4; k++)
		bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
}

void Controls::handlePlayerMovement(PlayField& playfield, Tetromino& tetromino)
{
	if (bKey[0]) {
		int goLeft = bKey[0] && playfield.doesPieceFit(tetromino, playfield.getnCurrentPiece(), playfield.getnCurrentRotation(), playfield.getnCurrentX() + 1, playfield.getnCurrentY()) ? 1 : 0;
		playfield.addnCurrentX(playfield.getnCurrentX(), goLeft);
	}

	if (bKey[1]) {
		int goRight = bKey[1] && playfield.doesPieceFit(tetromino, playfield.getnCurrentPiece(), playfield.getnCurrentRotation(), playfield.getnCurrentX() - 1, playfield.getnCurrentY()) ? 1 : 0;
		playfield.subtractnCurrentX(playfield.getnCurrentX(), goRight);
	}

	if (bKey[2]) {
		int goDown = bKey[2] && playfield.doesPieceFit(tetromino, playfield.getnCurrentPiece(), playfield.getnCurrentRotation(), playfield.getnCurrentX(), playfield.getnCurrentY() + 1) ? 1 : 0;
		playfield.subtractnCurrentY(playfield.getnCurrentY(), goDown);
	}
}

void Controls::handlePlayerRotation(PlayField& playfield, Tetromino& tetromino)
{
	if (bKey[3])
	{
		int newrotation = !bRotateHold && playfield.doesPieceFit(tetromino, playfield.getnCurrentPiece(), playfield.getnCurrentRotation() + 1, playfield.getnCurrentX(), playfield.getnCurrentY()) ? 1 : 0;
		playfield.setnCurrentRotation(playfield.getnCurrentRotation(), newrotation);
		bRotateHold = true;
	}
	else
		bRotateHold = false;
}
