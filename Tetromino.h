#pragma once
#include <iostream>

class Tetromino
{
public:
	Tetromino();
	std::wstring getTetromino(int nCurrentPiece);
	int Rotate(int px, int py, int r);
private: 
	void createTetrominos();
	std::wstring tetromino[7];
};