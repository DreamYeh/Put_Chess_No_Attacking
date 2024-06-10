#include "types.h"
#include "Tables.h"
#include "Search.h"


#include <omp.h>

#include <ctime>
#include <iostream>
#include "ParaSearch.h"

void SeParaSearch() {
	int i;
	//1.創造五個Search
	Search *search = new Search[15];
	Square awP[15] = {a2, a2, a2, a2, a2,
					 a3, a3, a3, a3,
		             a4, a4, a4, a5, a5, a6};

	Square abP[15] = { a7, a6, a5, a4, a3,
					 a7, a6, a5, a4,
					 a7, a6, a5, a7, a6, a7 };

	//初始化
	for (i = 0; i < 15; i++) {
		search[i].Init_Search();
	}
	//放置棋子
	for (i = 0; i < 15; i++) {
		search[i].Init_Piece(a8, WHITE_LEFT_ROOK);
		search[i].Init_Piece(b6, BLACK__KING);
		search[i].Init_Piece(f5, WHITE__QUEEN);
		/*
		search[i].Init_Piece(a8, BLACK_LEFT_ROOK);
		search[i].Init_Piece(b7, WHITE_LEFT_ROOK);
		search[i].Init_Piece(b6, WHITE__QUEEN);
		search[i].Init_Piece(e4, BLACK__QUEEN);
		search[i].Init_Piece(h2, BLACK_RIGHT_ROOK);
		search[i].Init_Piece(h8, BLACK__KING);
		*/

		search[i].SetParallel(awP[i], abP[i]);
	}
	time_t tt;
	tt = time(NULL);
	printf("Mulit-Analyze your board:");
	search[0].Draw_Board();
#pragma omp parallel for
	for (i = 0; i < 15; i++) {		
		search[i].Action(0);
		printf("Done i=%d PawnA on %s\n", i, SQSTR[awP[i]]);
	}
	printf("Threads Search done. find %d solution\n", 7);

	time_t end_tt = time(NULL);
	printf("Total time = %lld sec.\n", end_tt - tt);

	delete[] search;
}
