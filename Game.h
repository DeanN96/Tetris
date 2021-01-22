#pragma once
#include "Tetromino.h"
#include "PlayField.h"
#include "Controls.h"
#include <Windows.h>

class Game
{
public:
	Game();
	bool tick();
private: 
	void createScreenBuffer();
	void drawScore(PlayField);
	void gameTiming();
	void increaseGameSpeed();
	void drawField(PlayField);
	void drawCurrentPiece(PlayField, Tetromino);
	void forcePieceDown(PlayField&, Tetromino&);
	void displayField(PlayField&);
	void gameOver();
	Tetromino tetromino;
	PlayField playfield;
	Controls controls;
	bool GameOverFlag;
	wchar_t* screen;
	HANDLE hConsole;
	DWORD dwBytesWritten;
	int nSpeedCounter;
	bool bForceDown;
	int nSpeed;
	int nPieceCount;
	int nScore;
	int nScreenWidth;
	int nScreenHeight;
};

