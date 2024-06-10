//C only code.

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <windows.h>
#include <iostream>
#include <sys/timeb.h>
/*
DisplayBoard() displays the board
The console object is only used to display in colour.
*/
void DisplayBoard(int board[])//int board[64];
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int text = 15;

	int i;
	int x = 0;
	int c;

	printf("\n8 ");

	const int board_color[64] =
	{
		1, 0, 1, 0, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1
	};
	const int Flip[64] =
	{
		 56,  57,  58,  59,  60,  61,  62,  63,
		 48,  49,  50,  51,  52,  53,  54,  55,
		 40,  41,  42,  43,  44,  45,  46,  47,
		 32,  33,  34,  35,  36,  37,  38,  39,
		 24,  25,  26,  27,  28,  29,  30,  31,
		 16,  17,  18,  19,  20,  21,  22,  23,
		  8,   9,  10,  11,  12,  13,  14,  15,
		  0,   1,   2,   3,   4,   5,   6,   7
	};
	enum Color : unsigned int {
		WHITE, BLACK
	};

	char piece_char[6] =
	{
		'P', 'N', 'B', 'R', 'Q', 'K'
	};

	for (int j = 0; j < 64; ++j)
	{
		int i;
		int flip = 0;
		if (flip == 0)
			i = Flip[j];
		else
			i = 63 - Flip[j];

		char showPiece;
		c = 6;
		
		//WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
		//BLACK_PAWN = 8, BLACK_KNIGHT, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING,
		//NO_PIECE
		if (board[i] < 6) {
			showPiece = piece_char[board[i]];
			c = WHITE;
		}
		else if (board[i] < 14) {
			showPiece = piece_char[board[i] - 8];
			c = BLACK;
		}
		else {
			showPiece = 6;//EMPTY
			c = 6;
		}

		switch (c)
		{
		case 6:
			if (board_color[i] == 0)
				text = 127;
			else
				text = 34;
			SetConsoleTextAttribute(hConsole, text);

			printf("  ");
			SetConsoleTextAttribute(hConsole, 15);
			break;
		case 0:
			if (board_color[i] == 0)
				text = 126;
			else
				text = 46;
			SetConsoleTextAttribute(hConsole, text);
			printf(" %c", showPiece);
			SetConsoleTextAttribute(hConsole, 15);
			break;

		case 1:
			if (board_color[i] == 0)
				text = 112;
			else
				text = 32;
			SetConsoleTextAttribute(hConsole, text);
			printf(" %c", showPiece);
			SetConsoleTextAttribute(hConsole, 15);
			break;

		default:
			printf("error\n");
			break;

		}
		if ((j + 1) % 8 == 0 && j != 63)
			printf("\n%d ", 7 - j / 8);
	}

	printf("\n   a b c d e f g h\n\n");

}
