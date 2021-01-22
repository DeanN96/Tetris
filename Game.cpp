#include "Game.h"
#include "Tetromino.h"
#include "PlayField.h"
#include "Controls.h"
#include <iostream>
#include <thread>
#include <vector>
#include <Windows.h>

using namespace std;

Game::Game()
	: GameOverFlag(true),
	  nSpeedCounter(0),
	  bForceDown(false),
	  nSpeed(20),
	  nScore(0),
	  nPieceCount(0),
	  nScreenWidth(82),
	  nScreenHeight(75)
{
	createScreenBuffer();
	Tetromino tetromino;
	PlayField playfield;
	Controls controls;
}

void Game::createScreenBuffer()
{
	screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	dwBytesWritten = 0;
}

bool Game::tick()
{
	gameTiming();
	controls.enableKeyboardInput();
	controls.handlePlayerMovement(playfield, tetromino);
	controls.handlePlayerRotation(playfield, tetromino);
	if (bForceDown)
		forcePieceDown(playfield, tetromino);
	drawField(playfield);
	drawCurrentPiece(playfield, tetromino);
	drawScore(playfield);
	displayField(playfield);
	if (GameOverFlag == false)
		gameOver();

	return GameOverFlag;
}

void Game::drawScore(PlayField playfield)
{
	swprintf_s(&screen[2 * nScreenWidth + playfield.getnFieldWidth() + 6], 16, L"SCORE: %8d", nScore);
}

void Game::gameTiming()
{
	this_thread::sleep_for(50ms);
	nSpeedCounter++;
	bForceDown = (nSpeedCounter == nSpeed);
}

void Game::increaseGameSpeed()
{
	nPieceCount++;
	if (nPieceCount % 10 == 0 && nSpeed >= 10) nSpeed--;
}

void Game::drawField(PlayField playfield)
{
	for (int x = 0; x < playfield.getnFieldWidth(); x++)
		for (int y = 0; y < playfield.getnFieldHeight(); y++)
			screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[playfield.getpField()[y * playfield.getnFieldWidth() + x]];
}

void Game::drawCurrentPiece(PlayField playfield, Tetromino tetromino)
{
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
			if (tetromino.getTetromino(playfield.getnCurrentPiece())[tetromino.Rotate(px, py, playfield.getnCurrentRotation())] != L'.')
				screen[(playfield.getnCurrentY() + py + 2) * nScreenWidth + (playfield.getnCurrentX() + px + 2)] = playfield.getnCurrentPiece() + 65;
}

void Game::forcePieceDown(PlayField& playfield, Tetromino& tetromino)
{
	if (playfield.doesPieceFit(tetromino, playfield.getnCurrentPiece(), playfield.getnCurrentRotation(), playfield.getnCurrentX(), playfield.getnCurrentY() + 1))
		playfield.incrementnCurrentY();
	else
	{
		playfield.lockPieceIntoField(tetromino);
		increaseGameSpeed();
		playfield.checkForLines();
		nScore += 25;
		playfield.chooseNextPiece();
		GameOverFlag = (playfield.doesPieceFit(tetromino, playfield.getnCurrentPiece(), playfield.getnCurrentRotation(), playfield.getnCurrentX(), playfield.getnCurrentY()));
	}
	nSpeedCounter = 0;
}

void Game::displayField(PlayField& playfield)
{
	if (!playfield.getvLines().empty())
	{
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		this_thread::sleep_for(400ms);
		playfield.deleteLines();
	}
	WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
}

void Game::gameOver()
{
	CloseHandle(hConsole);
	std::cout << "Game Over!! Score:" << nScore << endl;
	std::system("pause");
}


