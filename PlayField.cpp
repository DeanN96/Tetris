#include "PlayField.h"
#include "Tetromino.h"

PlayField::PlayField()
	: nFieldWidth(12),
	  nFieldHeight(18),
	  nCurrentPiece(0),
	  nCurrentRotation(0),
	  nCurrentX(nFieldWidth/2),
	  nCurrentY(0)
{
	createPlayField();
}

unsigned char* PlayField::getpField()
{
	return pField;
}

int PlayField::getnFieldWidth()
{
	return nFieldWidth;
}

int PlayField::getnFieldHeight()
{
	return nFieldHeight;
}

std::vector<int> PlayField::getvLines()
{
	return vLines;
}

int PlayField::getnCurrentPiece()
{
	return nCurrentPiece;
}

int PlayField::getnCurrentRotation()
{
	return nCurrentRotation;
}

void PlayField::setnCurrentRotation(int CurrentRotation, int newRotation)
{
	nCurrentRotation = CurrentRotation + newRotation;
}

int PlayField::getnCurrentX()
{
	return nCurrentX;
}

void PlayField::addnCurrentX(int CurrentX, int addX)
{
	nCurrentX = CurrentX + addX;
}

void PlayField::subtractnCurrentX(int CurrentX, int subtractX)
{
	nCurrentX = CurrentX - subtractX;
}

int PlayField::getnCurrentY()
{
	return nCurrentY;
}

void PlayField::subtractnCurrentY(int CurrentY, int subtractY)
{
	nCurrentY = CurrentY + subtractY;
}

void PlayField::incrementnCurrentY()
{
	nCurrentY = nCurrentY + 1; 
}

void PlayField::createPlayField()
{
	pField = new unsigned char[nFieldWidth * nFieldHeight]; // Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) // Board Boundary
		for (int y = 0; y < nFieldHeight; y++)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
}

bool PlayField::doesPieceFit(Tetromino tetromino, int nTetromino, int nRotation, int nPosX, int nPosY)
{

	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			int pi = tetromino.Rotate(px, py, nRotation);

			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					if (tetromino.getTetromino(nTetromino)[pi] != L'.' && getpField()[fi] != 0)
						return false; 
				}
			}
		}

	return true;
};

void PlayField::checkForLines()
{
	for (int py = 0; py < 4; py++)
		if (nCurrentY + py < nFieldHeight - 1)
		{
			bool bLine = true;
			for (int px = 1; px < nFieldWidth - 1; px++)
				bLine &= (getpField()[(nCurrentY + py) * nFieldWidth + px]) != 0;

			if (bLine)
			{
				for (int px = 1; px < nFieldWidth - 1; px++)
					getpField()[(nCurrentY + py) * nFieldWidth + px] = 8;

				vLines.push_back(nCurrentY + py);
			}
		}
}

void PlayField::lockPieceIntoField(Tetromino tetromino)
{
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
			if (tetromino.getTetromino(nCurrentPiece)[tetromino.Rotate(px, py, nCurrentRotation)] != L'.')
				getpField()[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
}

void PlayField::deleteLines()
{
	for (auto& v : vLines)
		for (int px = 1; px < nFieldWidth - 1; px++)
		{
			for (int py = v; py > 0; py--)
				getpField()[py * nFieldWidth + px] = getpField()[(py - 1) * nFieldWidth + px];
			getpField()[px] = 0;
		}

	vLines.clear();
}

void PlayField::chooseNextPiece()
{
	nCurrentX = nFieldWidth / 2;
	nCurrentY = 0;
	nCurrentRotation = 0;
	nCurrentPiece = rand() % 7;
}