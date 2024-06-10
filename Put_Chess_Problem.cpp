
#include "types.h"
#include "tables.h"
#include "Position.h"
#include "Search.h"
#include <ctime>
#include <iostream>

void DisplayBoard(int board[]);
void SeParaSearch();
int main()
{
	//Make sure to initialise all databases before using the library!
	initialise_all_databases();
	zobrist::initialise_zobrist_keys();

	Position p;
	unsigned int pos;	
	Piece myBoard[NSQUARES] = { NO_PIECE };
	for (pos = 0; pos < NSQUARES; pos++) myBoard[pos] = NO_PIECE;
	//print message===============================
	char s[5];
	printf("Dream Chess Engine: \n");
	printf("Version 1.2.0, 2024/06/04\n");
	printf("Dream Yeh@gmail.com\n");

	printf("(N)ew a Board\n");
	printf("(A)dd Piece\n");
	printf("(R)emove Piece\n");
	printf("(G)et board for a legal position with no unit attacking an enemy unit\n");
	printf("==========Example==========\n");
	printf("(1)Run P1400086 6Pieces\n");
	printf("(2)Run P1416657 5Pieces\n");
	printf("(3)Run P1416658 4Pieces\n");
	printf("(4)Run P1417094 3Pieces\n");
	printf("(5)Run P1417xxx 5Pieces by Dream 0604\n");
	printf("(6)Run P1417xxx 4Pieces by Dream 0605\n");
	printf("(7)Run design by Dream\n");
	printf("(S)tatistics\n");
	printf("(Q)uit\n");
	printf("\n");

	//SeParaSearch();



	while (true)
	{
		printf("Enter command> ");
		scanf_s("%s", s, 5);

		if (s[0] == 'n' || s[0] == 'N')
		{
			for (pos = 0; pos < NSQUARES; pos++) myBoard[pos] = NO_PIECE;
			DisplayBoard((int *)myBoard);
		}
		else if (s[0] == 'a' || s[0] == 'A')
		{				
			DisplayBoard((int*)myBoard);
			
			printf("Piece+Postion(ex: Ka1 rg4). (Piece:KQBRN kqbrn)\n");
			
			
			while (1) {
				char m[5];
				int x, y;
				Piece p;

				printf("Please input Move(x=exit) >");
				scanf_s("%s", m, 5);

				if (m[0] == 'x') break;
				else if (m[0] == 'K') p = WHITE_KING;
				else if (m[0] == 'Q') p = WHITE_QUEEN;
				else if (m[0] == 'B') p = WHITE_BISHOP;
				else if (m[0] == 'N') p = WHITE_KNIGHT;
				else if (m[0] == 'R') p = WHITE_ROOK;
				else if (m[0] == 'k') p = BLACK_KING;
				else if (m[0] == 'q') p = BLACK_QUEEN;
				else if (m[0] == 'b') p = BLACK_BISHOP;
				else if (m[0] == 'n') p = BLACK_KNIGHT;
				else if (m[0] == 'r') p = BLACK_ROOK;
				else { printf("illegal move: KQBNR on m[0]\n"); continue; }

				if (m[1] == 'a') x = 0;
				else if (m[1] == 'b') x = 1;
				else if (m[1] == 'c') x = 2;
				else if (m[1] == 'd') x = 3;
				else if (m[1] == 'e') x = 4;
				else if (m[1] == 'f') x = 5;
				else if (m[1] == 'g') x = 6;
				else if (m[1] == 'h') x = 7;
				else { printf("illegal move: a-h on m[1]\n"); continue; }

				if (m[2] == '1') y = 0;
				else if (m[2] == '2') y = 1;
				else if (m[2] == '3') y = 2;
				else if (m[2] == '4') y = 3;
				else if (m[2] == '5') y = 4;
				else if (m[2] == '6') y = 5;
				else if (m[2] == '7') y = 6;
				else if (m[2] == '8') y = 7;
				else { printf("illegal move: 1-8 on m[2]\n"); continue; }


				//if king or queen, clear original.
				if (m[0] == 'K') {
					for (pos = 0; pos < NSQUARES; pos++)
						if (myBoard[pos] == WHITE_KING) myBoard[pos] = NO_PIECE;
				}
				if (m[0] == 'Q') {
					for (pos = 0; pos < NSQUARES; pos++)
						if (myBoard[pos] == WHITE_QUEEN) myBoard[pos] = NO_PIECE;
				}
				if (m[0] == 'k') {
					for (pos = 0; pos < NSQUARES; pos++)
						if (myBoard[pos] == BLACK_KING) myBoard[pos] = NO_PIECE;
				}
				if (m[0] == 'q') {
					for (pos = 0; pos < NSQUARES; pos++)
						if (myBoard[pos] == BLACK_QUEEN) myBoard[pos] = NO_PIECE;
				}
				pos = 8 * y + x;
				myBoard[pos] = p;
				DisplayBoard((int*)myBoard);
			}
		}
		else if (s[0] == 'r' || s[0] == 'R') {
			char m[5];
			int x, y;

			DisplayBoard((int*)myBoard);
			printf("input position (ex:a1) to remove > ");
			scanf_s("%s", m, 5);
			if (m[1] == 'a') x = 0;
			else if (m[1] == 'b') x = 1;
			else if (m[1] == 'c') x = 2;
			else if (m[1] == 'd') x = 3;
			else if (m[1] == 'e') x = 4;
			else if (m[1] == 'f') x = 5;
			else if (m[1] == 'g') x = 6;
			else if (m[1] == 'h') x = 7;
			else { printf("illegal move: a-h on m[1]\n"); continue; }

			if (m[2] == '1') y = 0;
			else if (m[2] == '2') y = 1;
			else if (m[2] == '3') y = 2;
			else if (m[2] == '4') y = 3;
			else if (m[2] == '5') y = 4;
			else if (m[2] == '6') y = 5;
			else if (m[2] == '7') y = 6;
			else if (m[2] == '8') y = 7;
			else { printf("illegal move: 1-8 on m[2]\n"); continue; }
			pos = 8 * y + x;
			myBoard[pos] = NO_PIECE;
			DisplayBoard((int*)myBoard);
		}
		else if (s[0] == 'g' || s[0] == 'G') {
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

			Search search0;
			int value;
			clock_t start_t0 = 0, end_t0 = 0;
			int num_W_N = 0, num_W_R = 0;
			int num_B_N = 0, num_B_R = 0;

			start_t0 = clock();
			search0.Init_Search();
			for (pos = a1; pos < NO_SQUARE; pos++) {
				Piece p = myBoard[pos];
				if (p == WHITE_KING) {
					search0.Init_Piece((Square)pos, WHITE__KING);
				} else if (p == WHITE_QUEEN) {
					search0.Init_Piece((Square)pos, WHITE__QUEEN);
				} else if (p == WHITE_BISHOP) {
					if (board_color[pos] == 1)
						search0.Init_Piece((Square)pos, WHITE_DARK_BISHOP);
					else 
						search0.Init_Piece((Square)pos, WHITE_LIGHT_BISHOP);
				} else if (p == WHITE_KNIGHT) {
					if (num_W_N == 0)
						search0.Init_Piece((Square)pos, WHITE_LEFT_KNIGHT);
					else if (num_W_N == 1)
						search0.Init_Piece((Square)pos, WHITE_RIGHT_KNIGHT);
					num_W_N++;
				} else if (p == WHITE_ROOK) {
					if (num_W_R == 0)
						search0.Init_Piece((Square)pos, WHITE_LEFT_ROOK);
					else if (num_W_R == 1)
						search0.Init_Piece((Square)pos, WHITE_RIGHT_ROOK);
					num_W_R++;
				}
				else if (p == BLACK_KING) {
					search0.Init_Piece((Square)pos, BLACK__KING);
				}
				else if (p == BLACK_QUEEN) {
					search0.Init_Piece((Square)pos, BLACK__QUEEN);
				}
				else if (p == BLACK_BISHOP) {
					if (board_color[pos] == 1)
						search0.Init_Piece((Square)pos, BLACK_DARK_BISHOP);
					else
						search0.Init_Piece((Square)pos, BLACK_LIGHT_BISHOP);
				}
				else if (p == BLACK_KNIGHT) {
					if (num_B_N == 0)
						search0.Init_Piece((Square)pos, BLACK_LEFT_KNIGHT);
					else if (num_B_N == 1)
						search0.Init_Piece((Square)pos, BLACK_RIGHT_KNIGHT);
					num_B_N++;
				}
				else if (p == WHITE_ROOK) {
					if (num_B_R == 0)
						search0.Init_Piece((Square)pos, BLACK_LEFT_ROOK);
					else if (num_B_R == 1)
						search0.Init_Piece((Square)pos, BLACK_RIGHT_ROOK);
					num_B_R++;
				}				
			}
			printf("Analyze your board:");
			search0.Draw_Board();// Get_Board(display_board);
			///DisplayBoard(display_board);
			value = search0.Action(0);

			printf("Search done. value = %d\n", value);
			end_t0 = clock();
			printf("Total time = %d sec.\n", (end_t0 - start_t0) / CLOCKS_PER_SEC);
		}
		else if (s[0] == '1') {//six chess

			Search *s1 = new Search();
			time_t tt;
			tt = time(NULL);
			
			//search1.Draw_Board();
			s1->Init_Search();
			s1->Init_Piece(a8, BLACK_LEFT_ROOK);
			s1->Init_Piece(b7, WHITE_LEFT_ROOK);
			s1->Init_Piece(b6, WHITE__QUEEN);
			s1->Init_Piece(e4, BLACK__QUEEN);
			s1->Init_Piece(h2, BLACK_RIGHT_ROOK);
			s1->Init_Piece(h8, BLACK__KING);
			printf("Analyze your board:");
			s1->Draw_Board();// Get_Board(display_board);
			///DisplayBoard(display_board);
			s1->Action(0);
			printf("Search done. find %llu solution\n", s1->num_Game);
			
			time_t end_tt = time(NULL);
			printf("Total time = %lld sec.\n", end_tt -tt);
			delete s1;
		}
		else if (s[0] == 't') {//test action2
			SeParaSearch();		

		}
		else if (s[0] == '2') {

			Search *s2 = new Search();
			int value;
			clock_t start_t = 0, end_t = 0;

			start_t = clock();
			//search1.Draw_Board();
			s2->Init_Search();
			s2->Init_Piece(a5, WHITE_LEFT_ROOK);
			s2->Init_Piece(a6, WHITE__KING);
			s2->Init_Piece(d1, BLACK__QUEEN);
			s2->Init_Piece(e8, WHITE_RIGHT_ROOK);
			s2->Init_Piece(g6, WHITE__QUEEN);

			printf("Analyze your board:");
			s2->Draw_Board();// Get_Board(display_board);
			///DisplayBoard(display_board);
			value = s2->Action(0);

			printf("Search done. find %llu solution\n", s2->num_Game);
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
			delete s2;
		}
		else if (s[0] == '3') {

			Search* s3 = new Search();
			clock_t start_t = 0, end_t = 0;

			start_t = clock();
			//search1.Draw_Board();
			s3->Init_Search();
			s3->Init_Piece(b4, WHITE_LEFT_ROOK);
			s3->Init_Piece(c4, WHITE_LIGHT_BISHOP);
			s3->Init_Piece(e5, BLACK_LEFT_ROOK);
			s3->Init_Piece(g8, BLACK_LEFT_KNIGHT);
			printf("Analyze your boards:");
			s3->Draw_Board();// Get_Board(display_board);			
			s3->Action(0);
			printf("Search done. find %llu solution\n", s3->num_Game);
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
			delete s3;
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

			printf("Search done. find %llu solution\n", search1.num_Game);
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
			search1.Init_Piece(b6, WHITE__QUEEN);
			search1.Init_Piece(e5, WHITE_LEFT_ROOK);
			search1.Init_Piece(g7, WHITE_RIGHT_ROOK);
			printf("init state\n");
			search1.Draw_Board();// Get_Board(display_board);

			value = search1.Action(0);			
			printf("Search done. find %llu solution\n", search1.num_Game);
			//search1.Get_Stat_Num();
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		}
		else if (s[0] == '6') {

			Search search1;
			int value;
			clock_t start_t = 0, end_t = 0;

			start_t = clock();
			//search1.Draw_Board();
			search1.Init_Search();
			search1.Init_Piece(d5, WHITE__QUEEN);
			search1.Init_Piece(g6, WHITE__KING);
			search1.Init_Piece(a8, WHITE_LEFT_ROOK);
			search1.Init_Piece(a2, WHITE_RIGHT_ROOK);
			printf("init state\n");
			search1.Draw_Board();// Get_Board(display_board);

			value = search1.Action(0);
			printf("Search done. find %llu solution\n", search1.num_Game);
			//search1.Get_Stat_Num();
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		}
		else if (s[0] == '7') {

			Search search1;
			int value;
			clock_t start_t = 0, end_t = 0;

			start_t = clock();
			//search1.Draw_Board();
			search1.Init_Search();
			search1.Init_Piece(d5, WHITE__QUEEN);
			search1.Init_Piece(g4, WHITE_LIGHT_BISHOP);
			search1.Init_Piece(e8, WHITE_LEFT_ROOK);
			search1.Init_Piece(a1, BLACK_DARK_BISHOP);
			printf("init state\n");
			search1.Draw_Board();// Get_Board(display_board);

			value = search1.Action(0);
			printf("Search done. find %llu solution\n", search1.num_Game);
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		}
		else if (s[0] == 's' || s[0] == 'S') {

			Search search1;
			int value;
			clock_t start_t = 0, end_t = 0;

			start_t = clock();
			//search1.Draw_Board();
			search1.Init_Search();
			search1.Init_Piece(d5, WHITE__QUEEN);
			search1.Init_Piece(g4, WHITE_LIGHT_BISHOP);
			search1.Init_Piece(e8, WHITE_LEFT_ROOK);
			//search1.Init_Piece(g6, WHITE__KING);
			//search1.Init_Piece(a8, WHITE_LEFT_ROOK);
			//search1.Init_Piece(a2, WHITE_RIGHT_ROOK);

			printf("init Statistics\n");
			search1.Draw_Board();// Get_Board(display_board);
			value = search1.Statistics(0);
			printf("Statistics done.\n");
			search1.Print_Stat();
			end_t = clock();
			printf("Total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		}
		else if (s[0] == 'q' || s[0] == 'Q')
		{
			printf("Program exiting\n");
			break;
		}
	}

	return 0;


	MoveList<WHITE> list(p);

	for (Move m : list) {
		std::cout << m << "\n";
	}

}
