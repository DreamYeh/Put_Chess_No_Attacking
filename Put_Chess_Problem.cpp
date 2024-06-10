
#include "types.h"
#include "tables.h"
#include "Position.h"
#include "Search.h"
#include <ctime>
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
	printf("Dream Chess Engine: \n");
	printf("Version 1.1.4, 2024/05/31\n");
	printf("Dream Yeh\n");

	printf("(n)ew:RNBQKBNR\n");
	printf("(d)isplay board\n");

	printf("(m)ove lists\n");
	printf("(1)Run P1400086 6Pieces\n");
	printf("(2)Run P1416657 5Pieces\n");
	printf("(3)Run P1416658 4Pieces\n");
	printf("(4)Run P1417094 3Pieces\n");
	printf("(5)Run Dream's design\n");
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
		else if (s[0] == '1') {//six chess

			Search search1;
			int value;
			clock_t start_t = 0, end_t = 0;
			
			start_t = clock();
			//search1.Draw_Board();
			search1.Init_Search();
			search1.Init_Piece(a8, BLACK_LEFT_ROOK);
			search1.Init_Piece(b7, WHITE_LEFT_ROOK);
			search1.Init_Piece(b6, WHITE__QUEEN);
			search1.Init_Piece(e4, BLACK__QUEEN);
			search1.Init_Piece(h2, BLACK_RIGHT_ROOK);
			search1.Init_Piece(h8, BLACK__KING);
			printf("Analyze your board:");
			search1.Draw_Board();// Get_Board(display_board);
			///DisplayBoard(display_board);
			value = search1.Action(0);
			
			printf("Search done. value = %d\n", value);
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		}
		else if (s[0] == '2') {

			Search search1;
			int value;
			clock_t start_t = 0, end_t = 0;

			start_t = clock();
			//search1.Draw_Board();
			search1.Init_Search();
			search1.Init_Piece(a5, WHITE_LEFT_ROOK);
			search1.Init_Piece(a6, WHITE__KING);
			search1.Init_Piece(d1, BLACK__QUEEN);
			search1.Init_Piece(e8, WHITE_RIGHT_ROOK);
			search1.Init_Piece(g6, WHITE__QUEEN);
			search1.Set_Piece(a5, WHITE_ROOK, WHITE);
			search1.Set_Piece(a6, WHITE_KING, WHITE);
			search1.Set_Piece(d1, BLACK_QUEEN, BLACK);
			search1.Set_Piece(e8, WHITE_ROOK, WHITE);
			search1.Set_Piece(g6, WHITE_QUEEN, WHITE);

			printf("Analyze your board:");
			search1.Draw_Board();// Get_Board(display_board);
			///DisplayBoard(display_board);
			value = search1.Action(0);

			printf("Search done. value = %d\n", value);
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		}
		else if (s[0] == '4') {

			Search search1;
			int value;
			clock_t start_t = 0, end_t = 0;

			start_t = clock();
			//search1.Draw_Board();
			search1.Init_Search();
			search1.Init_Piece(a8, WHITE_LEFT_ROOK);
			search1.Init_Piece(b6, BLACK__KING);
			search1.Init_Piece(f5, WHITE__QUEEN);


			printf("Analyze your board:");
			search1.Draw_Board();// Get_Board(display_board);
			///DisplayBoard(display_board);
			value = search1.Action(0);

			printf("Search done. value = %d\n", value);
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		}
		else if (s[0] == '5') {

			Search search1;
			int value;
			clock_t start_t = 0, end_t = 0;

			start_t = clock();
			//search1.Draw_Board();
			search1.Init_Search();
			
			search1.Init_Piece(d5, WHITE__QUEEN);
			search1.Init_Piece(g4, BLACK__QUEEN);

			printf("init state\n");
			search1.Draw_Board();// Get_Board(display_board);
			///DisplayBoard(display_board);
			value = search1.Action(0);

			printf("Search done. value = %d\n", value);
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		}
	}

	return 0;


	MoveList<WHITE> list(p);

	for (Move m : list) {
		std::cout << m << "\n";
	}

}
