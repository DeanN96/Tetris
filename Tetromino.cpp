#include "Tetromino.h"

Tetromino::Tetromino()
{
	createTetrominos();
}

std::wstring Tetromino::getTetromino(int nCurrentPiece)
{
	return tetromino[nCurrentPiece];
}

void Tetromino::createTetrominos()
{
	tetromino[0].append(L"..X...X...X...X.");
	tetromino[1].append(L"..X..XX...X.....");
	tetromino[2].append(L".....XX..XX.....");
	tetromino[3].append(L"..X..XX..X......");
	tetromino[4].append(L".X...XX...X.....");
	tetromino[5].append(L".X...X...XX.....");
	tetromino[6].append(L"..X...X..XX.....");
}

int Tetromino::Rotate(int px, int py, int r)
{
	int pi = 0;
	switch (r % 4)
	{
	case 0: // 0 degrees	
		pi = py * 4 + px;		
		break;											

	case 1: // 90 degrees			
		pi = 12 + py - (px * 4);	
		break;														

	case 2: // 180 degrees			
		pi = 15 - (py * 4) - px;	
		break;											

	case 3: // 270 degrees		
		pi = 3 - py + (px * 4);		
		break;						
	}								
	return pi;
}

