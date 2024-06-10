
#include "types.h"
#include "tables.h"
#include "Position.h"
#include "Search.h"
#include <iostream>
void DisplayBoard(int board[]);

int main()
{
	//Make sure to initialise all databases before using the library!
	initialise_all_databases();
	zobrist::initialise_zobrist_keys();

	Position p;
	//print message===============================
	char s[5];
	printf("Dream Chess Engine \n");
	printf("Version 1.1.4, 2024/05/29\n");
	printf("Dream Yeh\n");

	printf("(n)ew:RNBQKBNR\n");
	printf("(d)isplay board\n");

	printf("(m)ove lists\n");
	printf("(1) num Board\n");
	printf("(p)lay This Game\n");
	printf("(q)uit\n");
	printf("\n");

	while (true)
	{
		printf("Enter move or command> ");
		scanf_s("%s", s, 5);

		if (s[0] == 'q')
		{
			printf("Program exiting\n");
			break;
		}
		else if (s[0] == 'n')
		{
			p.set("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -", p);
			std::cout << p;
			
		}
		else if (s[0] == 'd')
		{	//code only 
			int board[64] = { 0 };
			p.get_Piece(board);
			DisplayBoard(board);
		}
		else if (s[0] == '1') {
			Search search1;
			int value;
			search1.Init_Search();
			search1.Init_Piece(BLACK_LEFT_ROOK, a8);
			search1.Init_Piece(WHITE_LEFT_ROOK, b7);
			search1.Init_Piece(WHITE__QUEEN, b6);
			search1.Init_Piece(BLACK__QUEEN, e4);
			search1.Init_Piece(BLACK_RIGHT_ROOK, h2);
			search1.Init_Piece(BLACK__KING, h8);
			search1.Set_Piece(a8, BLACK_ROOK, BLACK);			
			search1.Set_Piece(b7, WHITE_ROOK, WHITE);
			search1.Set_Piece(b6, WHITE_QUEEN, WHITE);
			search1.Set_Piece(e4, BLACK_QUEEN, BLACK);
			search1.Set_Piece(h2, BLACK_ROOK, BLACK);
			search1.Set_Piece(h8, BLACK_KING, BLACK);
			printf("init state\n");
			search1.Draw_Board();// Get_Board(display_board);
			///DisplayBoard(display_board);
			value = search1.Action(0);
			
			printf("Search done. value = %d\n", value);
			//search1.Draw_Board();
		}
	}

	return 0;


	MoveList<WHITE> list(p);

	for (Move m : list) {
		std::cout << m << "\n";
	}

}
