#pragma once
#include <iostream>
#include <cmath>
#include <string>


enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };

class Square
{

	Piece piece;
	Color color;
	int x, y;
public:
	void setSpace(Square*);
	void setEmpty();
	void setPieceAndColor(Piece, Color);
	Piece getPiece();
	Color getColor();
	void setX(int ex) { x = ex; }
	void setY(int why) { y = why; }
	int getX() { return x; }
	int getY() { return y; }
	Square();
};

class Board
{
	Square square[8][8];
	Color turn = WHITE;
	bool checkKing(int x, int y);
	bool checkQueen(int x, int y);
	bool checkBishop(int x, int y);
	bool checkKnight(int x, int y);
	bool checkRook(int x, int y);
	bool checkPawn(int x, int y);
	bool makeMove(int x1, int y1, int x2, int y2);

public:
	void printBoard();
	Square* getSquare(int x, int y) {
		return &square[x][y];
	}
	void setSquare(Square* s, int x, int y) {
		square[x][y] = *s;
	}
	bool doMove();

	void setBoard();
	bool playGame();

	void setProblem();
	bool checkBoard();
	
};
