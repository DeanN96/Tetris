#pragma once
#include "Tetromino.h"
#include <vector>

class PlayField
{
public:
	PlayField(); 
	bool doesPieceFit(Tetromino, int, int, int, int);
	unsigned char* getpField(); 
	int getnFieldWidth(); 
	int getnFieldHeight(); 
	std::vector<int> getvLines();
	int getnCurrentPiece();
	int getnCurrentRotation();
	void setnCurrentRotation(int, int);
	int getnCurrentX();
	void addnCurrentX(int, int);
	void subtractnCurrentX(int, int);
	int getnCurrentY();
	void subtractnCurrentY(int, int);
	void incrementnCurrentY();
	void checkForLines();
	void lockPieceIntoField(Tetromino);
	void deleteLines();
	void chooseNextPiece();
private:
	void createPlayField();
	unsigned char* pField; 
	int nFieldWidth; 
	int nFieldHeight;
	std::vector<int> vLines;
	int nCurrentPiece;  
	int nCurrentRotation;
	int nCurrentX;
	int nCurrentY;
};

