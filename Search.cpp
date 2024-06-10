#include "types.h"
#include "Tables.h"
#include "Search.h"

#include <cstdlib>//system function: pause, exit
#include <ctime>  //time function

unsigned int num_Game = 0;

Bitboard  Possible_Piece[32];
Bitboard  Possible_BPawn[8];

//64格是否有黑子、白子
Bitboard  Piece_All = 0, Piece_W = 0, Piece_B = 0;

//該格被攻擊
Bitboard  Piece_Attack_W = 0, Piece_Attack_B = 0;
Bitboard  Piece_Attack_W_init = 0, Piece_Attack_B_init = 0;
Bitboard  Attacked_by_Piece[32];
Bitboard  Attacked_by_BPawn[8];
//該子是否開局已經被放置
Square Init_Position[32];

//長程攻擊子位置
Square Temp_Position_WQ = NO_SQUARE;
Square Temp_Position_WR1 = NO_SQUARE;
Square Temp_Position_WR2 = NO_SQUARE;
Square Temp_Position_BQ = NO_SQUARE;
Square Temp_Position_BR1 = NO_SQUARE;
Square Temp_Position_BR2 = NO_SQUARE;


void Search::Init_Search() {
	int i, j;
	for (i=0; i < NSQUARES;i++)	board[i] = NO_PIECE;
	
	for (i = 0; i < 32; i++)//所有棋子可以在棋盤上任意位置
		for (j = 0; j < 64; j++)
			Possible_Piece[i] |= SQUARE_BB[j];

	Possible_Piece[WHITE_A_PAWN] = SQUARE_BB[a2] | SQUARE_BB[a3] | SQUARE_BB[a4] | SQUARE_BB[a5] | SQUARE_BB[a6];
	Possible_Piece[BLACK_A_PAWN] = SQUARE_BB[a7] | SQUARE_BB[a6] | SQUARE_BB[a5] | SQUARE_BB[a4] | SQUARE_BB[a3];
	Possible_Piece[WHITE_B_PAWN] = SQUARE_BB[b2] | SQUARE_BB[b3] | SQUARE_BB[b4] | SQUARE_BB[b5] | SQUARE_BB[b6];
	Possible_Piece[BLACK_B_PAWN] = SQUARE_BB[b7] | SQUARE_BB[b6] | SQUARE_BB[b5] | SQUARE_BB[b4] | SQUARE_BB[b3];
	Possible_Piece[WHITE_C_PAWN] = SQUARE_BB[c2] | SQUARE_BB[c3] | SQUARE_BB[c4] | SQUARE_BB[c5] | SQUARE_BB[c6];
	Possible_Piece[BLACK_C_PAWN] = SQUARE_BB[c7] | SQUARE_BB[c6] | SQUARE_BB[c5] | SQUARE_BB[c4] | SQUARE_BB[c3];
	Possible_Piece[WHITE_D_PAWN] = SQUARE_BB[d2] | SQUARE_BB[d3] | SQUARE_BB[d4] | SQUARE_BB[d5] | SQUARE_BB[d6];
	Possible_Piece[BLACK_D_PAWN] = SQUARE_BB[d7] | SQUARE_BB[d6] | SQUARE_BB[d5] | SQUARE_BB[d4] | SQUARE_BB[d3];
	Possible_Piece[WHITE_E_PAWN] = SQUARE_BB[e2] | SQUARE_BB[e3] | SQUARE_BB[e4] | SQUARE_BB[e5] | SQUARE_BB[e6];
	Possible_Piece[BLACK_E_PAWN] = SQUARE_BB[e7] | SQUARE_BB[e6] | SQUARE_BB[e5] | SQUARE_BB[e4] | SQUARE_BB[e3];
	Possible_Piece[WHITE_F_PAWN] = SQUARE_BB[f2] | SQUARE_BB[f3] | SQUARE_BB[f4] | SQUARE_BB[f5] | SQUARE_BB[f6];
	Possible_Piece[BLACK_F_PAWN] = SQUARE_BB[f7] | SQUARE_BB[f6] | SQUARE_BB[f5] | SQUARE_BB[f4] | SQUARE_BB[f3];
	Possible_Piece[WHITE_G_PAWN] = SQUARE_BB[g2] | SQUARE_BB[g3] | SQUARE_BB[g4] | SQUARE_BB[g5] | SQUARE_BB[g6];
	Possible_Piece[BLACK_G_PAWN] = SQUARE_BB[g7] | SQUARE_BB[g6] | SQUARE_BB[g5] | SQUARE_BB[g4] | SQUARE_BB[g3];
	Possible_Piece[WHITE_H_PAWN] = SQUARE_BB[h2] | SQUARE_BB[h3] | SQUARE_BB[h4] | SQUARE_BB[h5] | SQUARE_BB[h6];
	Possible_Piece[BLACK_H_PAWN] = SQUARE_BB[h7] | SQUARE_BB[h6] | SQUARE_BB[h5] | SQUARE_BB[h4] | SQUARE_BB[h3];

	
	Possible_BPawn[0] = SQUARE_BB[a7] | SQUARE_BB[a6] | SQUARE_BB[a5] | SQUARE_BB[a4] | SQUARE_BB[a3];
	Possible_BPawn[1] = SQUARE_BB[b7] | SQUARE_BB[b6] | SQUARE_BB[b5] | SQUARE_BB[b4] | SQUARE_BB[b3];
	Possible_BPawn[2] = SQUARE_BB[c7] | SQUARE_BB[c6] | SQUARE_BB[c5] | SQUARE_BB[c4] | SQUARE_BB[c3];
	Possible_BPawn[3] = SQUARE_BB[d7] | SQUARE_BB[d6] | SQUARE_BB[d5] | SQUARE_BB[d4] | SQUARE_BB[d3];
	Possible_BPawn[4] = SQUARE_BB[e7] | SQUARE_BB[e6] | SQUARE_BB[e5] | SQUARE_BB[e4] | SQUARE_BB[e3];
	Possible_BPawn[5] = SQUARE_BB[f7] | SQUARE_BB[f6] | SQUARE_BB[f5] | SQUARE_BB[f4] | SQUARE_BB[f3];
	Possible_BPawn[6] = SQUARE_BB[g7] | SQUARE_BB[g6] | SQUARE_BB[g5] | SQUARE_BB[g4] | SQUARE_BB[g3];
	Possible_BPawn[7] = SQUARE_BB[h7] | SQUARE_BB[h6] | SQUARE_BB[h5] | SQUARE_BB[h4] | SQUARE_BB[h3];

	//a1是dark格
	Possible_Piece[WHITE_DARK_BISHOP] =
		SQUARE_BB[a1] | SQUARE_BB[c1] | SQUARE_BB[e1] | SQUARE_BB[g1] |
		SQUARE_BB[b2] | SQUARE_BB[d2] | SQUARE_BB[f2] | SQUARE_BB[h2] |
		SQUARE_BB[a3] | SQUARE_BB[c3] | SQUARE_BB[e3] | SQUARE_BB[g3] |
		SQUARE_BB[b4] | SQUARE_BB[d4] | SQUARE_BB[f4] | SQUARE_BB[h4] |
		SQUARE_BB[a5] | SQUARE_BB[c5] | SQUARE_BB[e5] | SQUARE_BB[g5] |
		SQUARE_BB[b6] | SQUARE_BB[d6] | SQUARE_BB[f6] | SQUARE_BB[h6] |
		SQUARE_BB[a7] | SQUARE_BB[c7] | SQUARE_BB[e7] | SQUARE_BB[g7] |
		SQUARE_BB[b8] | SQUARE_BB[d8] | SQUARE_BB[f8] | SQUARE_BB[h8];

	Possible_Piece[BLACK_DARK_BISHOP] = 
		SQUARE_BB[a1] | SQUARE_BB[c1] | SQUARE_BB[e1] | SQUARE_BB[g1] |
		SQUARE_BB[b2] | SQUARE_BB[d2] | SQUARE_BB[f2] | SQUARE_BB[h2] |
		SQUARE_BB[a3] | SQUARE_BB[c3] | SQUARE_BB[e3] | SQUARE_BB[g3] |
		SQUARE_BB[b4] | SQUARE_BB[d4] | SQUARE_BB[f4] | SQUARE_BB[h4] |
		SQUARE_BB[a5] | SQUARE_BB[c5] | SQUARE_BB[e5] | SQUARE_BB[g5] |
		SQUARE_BB[b6] | SQUARE_BB[d6] | SQUARE_BB[f6] | SQUARE_BB[h6] |
		SQUARE_BB[a7] | SQUARE_BB[c7] | SQUARE_BB[e7] | SQUARE_BB[g7] |
		SQUARE_BB[b8] | SQUARE_BB[d8] | SQUARE_BB[f8] | SQUARE_BB[h8];
		
		//Possible_Piece[WHITE_DARK_BISHOP];

	Possible_Piece[BLACK_LIGHT_BISHOP] =
		SQUARE_BB[b1] | SQUARE_BB[d1] | SQUARE_BB[f1] | SQUARE_BB[h1] |
		SQUARE_BB[a2] | SQUARE_BB[c2] | SQUARE_BB[e2] | SQUARE_BB[g2] |
		SQUARE_BB[b3] | SQUARE_BB[d3] | SQUARE_BB[f3] | SQUARE_BB[h3] |
		SQUARE_BB[a4] | SQUARE_BB[c4] | SQUARE_BB[e4] | SQUARE_BB[g4] |
		SQUARE_BB[b5] | SQUARE_BB[d5] | SQUARE_BB[f5] | SQUARE_BB[h5] |
		SQUARE_BB[a6] | SQUARE_BB[c6] | SQUARE_BB[e6] | SQUARE_BB[g6] |
		SQUARE_BB[b7] | SQUARE_BB[d7] | SQUARE_BB[f7] | SQUARE_BB[h7] |
		SQUARE_BB[a8] | SQUARE_BB[c8] | SQUARE_BB[e8] | SQUARE_BB[g8];

	Possible_Piece[WHITE_LIGHT_BISHOP] = 
		SQUARE_BB[b1] | SQUARE_BB[d1] | SQUARE_BB[f1] | SQUARE_BB[h1] |
		SQUARE_BB[a2] | SQUARE_BB[c2] | SQUARE_BB[e2] | SQUARE_BB[g2] |
		SQUARE_BB[b3] | SQUARE_BB[d3] | SQUARE_BB[f3] | SQUARE_BB[h3] |
		SQUARE_BB[a4] | SQUARE_BB[c4] | SQUARE_BB[e4] | SQUARE_BB[g4] |
		SQUARE_BB[b5] | SQUARE_BB[d5] | SQUARE_BB[f5] | SQUARE_BB[h5] |
		SQUARE_BB[a6] | SQUARE_BB[c6] | SQUARE_BB[e6] | SQUARE_BB[g6] |
		SQUARE_BB[b7] | SQUARE_BB[d7] | SQUARE_BB[f7] | SQUARE_BB[h7] |
		SQUARE_BB[a8] | SQUARE_BB[c8] | SQUARE_BB[e8] | SQUARE_BB[g8];
		
		//Possible_Piece[BLACK_LIGHT_BISHOP];


	//初始沒有棋子展開攻擊
	for (i = 0; i < MAX_PIECE; i++) Attacked_by_Piece[i] = 0;
	//各棋子剛開始都是未知位置
	for (i = 0; i < MAX_PIECE; i++)	Init_Position[i] = NO_SQUARE;

	Piece_All = 0; Piece_W = 0; Piece_B = 0;
	Piece_Attack_W = 0; Piece_Attack_B = 0;
	Piece_Attack_W_init = 0; Piece_Attack_B_init = 0;
	Temp_Position_WQ = NO_SQUARE;
	Temp_Position_WR1 = NO_SQUARE;
	Temp_Position_WR2 = NO_SQUARE;
	Temp_Position_BQ = NO_SQUARE;
	Temp_Position_BR1 = NO_SQUARE;
	Temp_Position_BR2 = NO_SQUARE;

	num_Game = 0;
}


void Search::Init_Piece(Square sq, DPiece dp) {
	Bitboard attack_bit = 0;

	Init_Position[dp] = sq;

	switch (dp) {//update attack
	case WHITE_LEFT_KNIGHT:
	case WHITE_RIGHT_KNIGHT:
		attack_bit = KNIGHT_ATTACKS[sq];
		Piece_Attack_W_init |= attack_bit;
		Set_Piece(sq, WHITE_KNIGHT, WHITE);
		break;
	case BLACK_LEFT_KNIGHT:
	case BLACK_RIGHT_KNIGHT:
		attack_bit = KNIGHT_ATTACKS[sq];
		Piece_Attack_B_init |= attack_bit;
		Set_Piece(sq, BLACK_KNIGHT, BLACK);
		break;
	case WHITE__KING:
		attack_bit = KING_ATTACKS[sq];
		Piece_Attack_W_init |= attack_bit;
		Set_Piece(sq, WHITE_KING, WHITE);
		break;
	case WHITE__QUEEN:
		attack_bit = KING_ATTACKS[sq];
		Piece_Attack_W_init |= attack_bit;
		Temp_Position_WQ = sq;
		Set_Piece(sq, WHITE_QUEEN, WHITE);
		break;
	case BLACK__KING:
		attack_bit = KING_ATTACKS[sq];
		Piece_Attack_B_init |= attack_bit;
		Set_Piece(sq, BLACK_KING, BLACK);
		break;
	case BLACK__QUEEN:
		attack_bit = KING_ATTACKS[sq];
		Piece_Attack_B_init |= attack_bit;
		Temp_Position_BQ = sq;
		Set_Piece(sq, BLACK_QUEEN, BLACK);
		break;
	case WHITE_LEFT_ROOK:
		attack_bit = ROOK_NEARS_ATTACK[sq];
		Piece_Attack_W_init |= attack_bit;
		Temp_Position_WR1 = sq;
		Set_Piece(sq, WHITE_ROOK, WHITE);
		break;
	case WHITE_RIGHT_ROOK:
		attack_bit = ROOK_NEARS_ATTACK[sq];
		Piece_Attack_W_init |= attack_bit;
		Temp_Position_WR2 = sq;
		Set_Piece(sq, WHITE_ROOK, WHITE);
		break;
	case BLACK_LEFT_ROOK:
		attack_bit = ROOK_NEARS_ATTACK[sq];
		Piece_Attack_B_init |= attack_bit;
		Temp_Position_BR1 = sq;
		Set_Piece(sq, BLACK_ROOK, BLACK);
		break;
	case BLACK_RIGHT_ROOK:
		attack_bit = ROOK_NEARS_ATTACK[sq];
		Piece_Attack_B_init |= attack_bit;
		Temp_Position_BR2 = sq;
		Set_Piece(sq, BLACK_ROOK, BLACK);
		break;
	case WHITE_LIGHT_BISHOP:
	case WHITE_DARK_BISHOP:
		attack_bit = BISHOP_NEARS_ATTACK[sq];
		Piece_Attack_W_init |= attack_bit;
		Set_Piece(sq, WHITE_BISHOP, WHITE);
		break;
	case BLACK_LIGHT_BISHOP:
	case BLACK_DARK_BISHOP:
		attack_bit = BISHOP_NEARS_ATTACK[sq];
		Piece_Attack_B_init |= attack_bit;
		Set_Piece(sq, BLACK_BISHOP, BLACK);
		break;
	}
}

void Search::Get_Board(int get_board[]) {
	for (int i = 0; i < 64; i++) {
		get_board[i] = board[i];
	}
}

void DisplayBoard(int board[]);
void board_to_fen(int* board, char* fen);
void Search::Draw_Board() {
	char pFEN[512] = { 0 };
	DisplayBoard((int*)board);
	board_to_fen((int*)board, pFEN);

	printf("FEN=%s\n\n", pFEN);
}
void Search::Set_Piece(Square sq, Piece p, Color c) {
	board[sq] = p;

	if (c == WHITE) {		
		Piece_W = Piece_W | SQUARE_BB[sq];
		Piece_All = Piece_All | SQUARE_BB[sq];
	}
	else
	{
		Piece_B = Piece_B | SQUARE_BB[sq];
		Piece_All = Piece_All | SQUARE_BB[sq];
	}
}
void Search::Remove_Piece(Square sq, Color c) {
	board[sq] = NO_PIECE;
	if (c == WHITE) {
		Piece_W = Piece_W & ~SQUARE_BB[sq];
		Piece_All = Piece_All & ~SQUARE_BB[sq];
	}
	else {
		Piece_B = Piece_B & ~SQUARE_BB[sq];
		Piece_All = Piece_All & ~SQUARE_BB[sq];
	}
}

/*
int Search::Get_Lowest_1(Bitboard value) {
	int V = value;
	return (V & -V);
	printf("%d\n", gpos);
	for (i = 0; i < 65; i++) if (gpos== SQUARE_BB[i]) break;
	printf("position = %s\n", SQSTR[i]);
	
}
*/

//輸入Board 輸出是否有攻擊發生，如果有，是誰發動
int Search::Check()
{
	Bitboard bb;
	for (int sq = 0; sq < NSQUARES; sq++) {
		if (board[sq] == WHITE_BISHOP) {
			 bb = get_bishop_attacks((Square)sq, Piece_All);
			 if (bb & Piece_B) return sq;
		} else if (board[sq] == BLACK_BISHOP) {
			bb = get_bishop_attacks((Square)sq, Piece_All);
			if (bb & Piece_W) return sq;
		} else if (board[sq] == WHITE_ROOK) {
			bb = get_rook_attacks((Square)sq, Piece_All);
			if (bb & Piece_B) return sq;
		} else if (board[sq] == BLACK_ROOK) {
			bb = get_rook_attacks((Square)sq, Piece_All);
			if (bb & Piece_W) return sq;
		} else if (board[sq] == WHITE_QUEEN) {
			bb = get_bishop_attacks((Square)sq, Piece_All);
			if (bb & Piece_B) return sq;
			bb = get_rook_attacks((Square)sq, Piece_All);
			if (bb & Piece_B) return sq;
		} else if (board[sq] == BLACK_QUEEN) {
			bb = get_bishop_attacks((Square)sq, Piece_All);
			if (bb & Piece_W) return sq;
			bb = get_rook_attacks((Square)sq, Piece_All);
			if (bb & Piece_W) return sq;
		}

	}
	return -1;
}

inline void Put_White_Piece_Done()
{
	Bitboard bb1 = get_bishop_attacks(Temp_Position_WQ, Piece_All);
	Bitboard bb2 = get_rook_attacks(Temp_Position_WQ, Piece_All);
	Attacked_by_Piece[WHITE__QUEEN] = bb1 | bb2;
	bb1 = get_rook_attacks(Temp_Position_WR1, Piece_All);
	Attacked_by_Piece[WHITE_LEFT_ROOK] = bb1;
	bb2 = get_rook_attacks(Temp_Position_WR2, Piece_All);
	Attacked_by_Piece[WHITE_RIGHT_ROOK] = bb2;

	Piece_Attack_W =
		Piece_Attack_W_init |
		Attacked_by_Piece[WHITE_A_PAWN] | Attacked_by_Piece[WHITE_B_PAWN] | Attacked_by_Piece[WHITE_C_PAWN] | Attacked_by_Piece[WHITE_D_PAWN] |
		Attacked_by_Piece[WHITE_E_PAWN] | Attacked_by_Piece[WHITE_F_PAWN] | Attacked_by_Piece[WHITE_G_PAWN] | Attacked_by_Piece[WHITE_H_PAWN] |
		Attacked_by_Piece[WHITE_LEFT_KNIGHT] | Attacked_by_Piece[WHITE_RIGHT_KNIGHT] |
		Attacked_by_Piece[WHITE__KING] | Attacked_by_Piece[WHITE__QUEEN] |
		Attacked_by_Piece[WHITE_LEFT_ROOK] | Attacked_by_Piece[WHITE_RIGHT_ROOK] | Attacked_by_Piece[WHITE_LIGHT_BISHOP] | Attacked_by_Piece[WHITE_DARK_BISHOP];

}
inline Bitboard Put_Black_Piece_Done()
{
	Bitboard cc1 = get_bishop_attacks(Temp_Position_BQ, Piece_All);
	Bitboard cc2 =  get_rook_attacks(Temp_Position_BQ, Piece_All);
	//Attacked_by_Piece[BLACK__QUEEN] = bb3 | bb4;

	Bitboard cc3 = get_rook_attacks(Temp_Position_BR1, Piece_All);
	Bitboard cc4 = get_rook_attacks(Temp_Position_BR2, Piece_All);
	//Attacked_by_Piece[BLACK_LEFT_ROOK] = get_rook_attacks(Temp_Position_BR1, Piece_All);
	//Attacked_by_Piece[BLACK_RIGHT_ROOK] = get_rook_attacks(Temp_Position_BR2, Piece_All);

	return (cc1|cc2|cc3|cc4);
}

int Search::Action(unsigned int p) {
	int Value;
	Square getSq;
	Bitboard possible, attack_bit;
	clock_t start_t = 0, end_t = 0;

	if (p == 0) {
		start_t = clock();		
		Piece_Attack_B = Piece_Attack_B_init;//init
		//print_bitboard(Piece_Attack_B);
	}

	if (Init_Position[p] != NO_SQUARE) {
		return Action(p + 1);
	}

	if (p <= WHITE_H_PAWN) {//採用if，以包括更多同樣的兵種	
		possible = Possible_Piece[p];//Possi_WaP 得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_B;//被攻擊則去除

		while(true) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			attack_bit = WHITE_PAWN_ATTACKS[getSq];//得到A的鄰近攻擊格的BitBoard attack
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (!(attack_bit & Piece_B)) {
				Set_Piece(getSq, WHITE_PAWN, WHITE);//落子A		
				Attacked_by_Piece[p] = attack_bit;

				//這步驟暫時不知道怎麼省略，不每次重新計算的話，會在繼續進兵時出錯
				Bitboard  Piece_Attack_W0 = Piece_Attack_W_init;
				for (unsigned int pi = 0; pi <= p; pi++) {
					Piece_Attack_W0 |= Attacked_by_Piece[pi];
				}
				//
				Bitboard poss2 = Possible_BPawn[p];
				poss2 = poss2 & ~Piece_All;//有子則去除
				poss2 = poss2 & ~Piece_Attack_W0;//被攻擊則去除
				//Value = Action(p + 1);//繼續找下一個
				while (true) {
					if (poss2 == 0) {
						break;
					}
					Square getSq2 = pop_lsb(&poss2);//推出第一個可使用的位, possible的這個位取0
					if (getSq2 > getSq) {
						attack_bit = BLACK_PAWN_ATTACKS[getSq2];//得到B的鄰近攻擊格的BitBoard attack
						if (!(attack_bit & Piece_W)) {
							Set_Piece(getSq2, BLACK_PAWN, BLACK);//落子B	
							Attacked_by_BPawn[p] = attack_bit;
							Piece_Attack_B = Piece_Attack_B_init;
							for (unsigned int pi = 0; pi <= p; pi++) {
								Piece_Attack_B |= Attacked_by_BPawn[pi];
							}
							Action(p + 1);
							Remove_Piece(getSq2, BLACK);
						}
					}
				}
				Remove_Piece(getSq, WHITE);
				Attacked_by_Piece[p] = 0;
			}
		}
	}
	else if (p == WHITE_LEFT_KNIGHT || p == WHITE_RIGHT_KNIGHT) {
		Square getSq1, getSq2;

		possible = Possible_Piece[p];//得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_B;//被攻擊則去除

		while (true) {
			if (possible == 0) {
				return p;
			}
			getSq1 = pop_lsb(&possible);
			attack_bit = KNIGHT_ATTACKS[getSq1];
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (!(attack_bit & Piece_B)) {
				Set_Piece(getSq1, WHITE_KNIGHT, WHITE);//落子A
				Attacked_by_Piece[WHITE_LEFT_KNIGHT] = attack_bit;
				//Value = Action(p + 1);//繼續找下一個
				Bitboard possible2 = possible, attack_bit2;//必須複製一個
				while (possible2 > 0) {
					getSq2 = pop_lsb(&possible2);//由於是由possble開始取，只會取新的
					attack_bit2 = KNIGHT_ATTACKS[getSq2];
					if (!(attack_bit2 & Piece_B)) {
						Set_Piece(getSq2, WHITE_KNIGHT, WHITE);//落子B	
						Attacked_by_Piece[WHITE_RIGHT_KNIGHT] = attack_bit2;
						Action(WHITE__KING);
						Remove_Piece(getSq2, WHITE);
					}
				}
				Remove_Piece(getSq1, WHITE);				
			}
		}
	}
	else if (p == WHITE__KING || p == WHITE__QUEEN) {//白王、后
		possible = Possible_Piece[p];//得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_B;//被攻擊則去除

		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			attack_bit = KING_ATTACKS[getSq];//得到王的鄰近八格BitBoard attack
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (attack_bit & Piece_B) {
				continue;
			}
			else {
				if (p == WHITE__KING) Set_Piece(getSq, WHITE_KING, WHITE);//落子
				else if (p == WHITE__QUEEN)
				{
					Set_Piece(getSq, WHITE_QUEEN, WHITE);//落子
					Temp_Position_WQ = getSq;
				}
				//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				Value = Action(p + 1);//繼續找下一個
				Remove_Piece(getSq, WHITE);
				//Piece_Attack_W &= ~attack_bit;
				Attacked_by_Piece[p] = 0;
			}
		}
	}
	else if (p == WHITE_LEFT_ROOK) {
		//這邊僅是為了安全而判斷
		if (Init_Position[WHITE_LEFT_ROOK] != NO_SQUARE) {
			return Action(p + 1);
		}
		//城1未設定、使用雙位元輸出演算法0530夢
		Square getSq1, getSq2;
		possible = Possible_Piece[p];//得到可能位置

		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_B;//被攻擊則去除

		while (true) {
			if (possible == 0) {
				return p;
			}
			getSq1 = pop_lsb(&possible);
			attack_bit = ROOK_NEARS_ATTACK[getSq1];
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (!(attack_bit & Piece_B)) {
				Set_Piece(getSq1, WHITE_ROOK, WHITE);//落子A
				Temp_Position_WR1 = getSq1;
				Attacked_by_Piece[WHITE_LEFT_ROOK] = attack_bit;
				//Value = Action(p + 1);//展開點
				Bitboard possible2 = possible, attack_bit2;//必須複製一個
				while (possible2 > 0) {
					getSq2 = pop_lsb(&possible2);//由於是由possble開始取，只會取新的
					attack_bit2 = KNIGHT_ATTACKS[getSq2];
					if (!(attack_bit2 & Piece_B)) {
						Set_Piece(getSq2, WHITE_ROOK, WHITE);//落子B	
						Temp_Position_WR2 = getSq2;
						Attacked_by_Piece[WHITE_RIGHT_ROOK] = attack_bit2;
						Action(WHITE_LIGHT_BISHOP);
						Remove_Piece(getSq2, WHITE);
					}
				}
				Remove_Piece(getSq1, WHITE);
			}
		}
	}
	else if (p == WHITE_RIGHT_ROOK) {
		possible = Possible_Piece[p];//得到可能位置

		//左下受困
		if (board[b2] == WHITE_PAWN && board[d2] == WHITE_PAWN) {
			if (board[a3] == WHITE_PAWN) {
				possible = SQUARE_BB[a1] | SQUARE_BB[a2] | SQUARE_BB[b1];
			}
		}
		
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_B;//被攻擊則去除

		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			attack_bit = ROOK_NEARS_ATTACK[getSq];//得到城堡鄰近攻擊
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (attack_bit & Piece_B) {
				continue;
			}
			else {
				Set_Piece(getSq, WHITE_ROOK, WHITE);//落子

				if (p == WHITE_LEFT_ROOK)
					Temp_Position_WR1 = getSq;
				else
					Temp_Position_WR2 = getSq;
				//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				//Update_Attack(WHITE);
				Value = Action(p + 1);//繼續找下一個
				Remove_Piece(getSq, WHITE);
				//Piece_Attack_W &= ~attack_bit;
				Attacked_by_Piece[p] = 0;
			}
		}

	} else if (p == WHITE_LIGHT_BISHOP || p == WHITE_DARK_BISHOP) {//白主教
		//白的兩個主教因為不同色格因此不互相干擾
		// 也就是亮格主教攻擊範圍不會被後放的黑格主教影響！
		possible = Possible_Piece[p];//得到可能位置
		
		if (p == WHITE_LIGHT_BISHOP) {//很直覺= =
			if (board[e2] == WHITE_PAWN && board[g2] == WHITE_PAWN)
				possible = SQUARE_BB[f1];
		}
		else {//c1是暗格、別搞錯！
			if (board[b2] == WHITE_PAWN && board[d2] == WHITE_PAWN)
				possible = SQUARE_BB[c1];			
		}


		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_B;//被攻擊則去除

		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			//BISHOP_NEARS_ATTACK[getSq];//得到主教所有攻擊格、這是白最後放子因此可直接判斷！
			attack_bit = get_bishop_attacks(getSq, Piece_All);
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (attack_bit & Piece_B) {
				continue;
			}
			else {
				Set_Piece(getSq, WHITE_BISHOP, WHITE);//落子
				Attacked_by_Piece[p] = attack_bit;
				if (p == WHITE_DARK_BISHOP) {//至此放完
					Put_White_Piece_Done();
					if (!(Piece_Attack_W & Piece_B))
						Value = Action(BLACK_LEFT_KNIGHT);//跳到黑騎士
				} else 			
					Value = Action(p + 1);//繼續找下一個
				Remove_Piece(getSq, WHITE);
				Attacked_by_Piece[p] = 0;
			}
		}
	}/*
	else if (p >= BLACK_A_PAWN && p <= BLACK_H_PAWN) {//黑兵
		possible = Possible_Piece[p];
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_W;//被攻擊則去除

		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			attack_bit = BLACK_PAWN_ATTACKS[getSq];//得到A的鄰近攻擊格的BitBoard attack
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到，移動A到下一個可能位置
			if (attack_bit & Piece_W) {
				continue;
			}
			else {
				if (posOfWhite[p - BLACK_A_PAWN] >= getSq) continue;//兵的特殊判定，黑兵不能超過白兵

				Set_Piece(getSq, BLACK_PAWN, BLACK);//落子A
				//Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」

				Value = Action(p + 1);//繼續找下一個
				Remove_Piece(getSq, BLACK);
				//Piece_Attack_B &= ~attack_bit;
			}
		}
	}*/
	else if (p == BLACK_LEFT_KNIGHT || p == BLACK_RIGHT_KNIGHT) {//黑騎士
		Square getSq1, getSq2;

		possible = Possible_Piece[p];//得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_W;//被攻擊則去除

		while (true) {
			if (possible == 0) {
				return p;
			}
			getSq1 = pop_lsb(&possible);
			attack_bit = KNIGHT_ATTACKS[getSq1];
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (!(attack_bit & Piece_W)) {
				Set_Piece(getSq1, BLACK_KNIGHT, BLACK);//落子A				
				//Value = Action(p + 1);//繼續找下一個
				Bitboard possible2 = possible, attack_bit2;//必須複製一個
				while (possible2 > 0) {
					getSq2 = pop_lsb(&possible2);//由於是由possble開始取，只會取新的
					attack_bit2 = KNIGHT_ATTACKS[getSq2];
					if (!(attack_bit2 & Piece_W)) {
						Set_Piece(getSq2, BLACK_KNIGHT, BLACK);//落子B						
						Action(BLACK__KING);
						Remove_Piece(getSq2, BLACK);
					}
				}
				Remove_Piece(getSq1, BLACK);
			}
		}

	}
	else if (p == BLACK__KING || p == BLACK__QUEEN) {//黑王、后
		possible = Possible_Piece[p];//得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_W;//被攻擊則去除
		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			attack_bit = KING_ATTACKS[getSq];//得到王的鄰近八格BitBoard attack
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (attack_bit & Piece_W) {
				continue;
			}
			else {
				if (p == BLACK__KING)
					Set_Piece(getSq, BLACK_KING, BLACK);//落子
				else {
					Set_Piece(getSq, BLACK_QUEEN, BLACK);//落子
					Temp_Position_BQ = getSq;
				}
				//Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Value = Action(p + 1);//繼續找下一個
				Remove_Piece(getSq, BLACK);
				//Piece_Attack_B &= ~attack_bit;
			}
		}

	}
	else if (p == BLACK_LEFT_ROOK) {//黑雙城, 雙位元演算
		Square getSq1, getSq2;

		possible = Possible_Piece[p];//得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_W;//被攻擊則去除

		while (true) {
			if (possible == 0) {
				return p;
			}
			getSq1 = pop_lsb(&possible);
			attack_bit = ROOK_NEARS_ATTACK[getSq1];
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (!(attack_bit & Piece_W)) {
				Set_Piece(getSq1, BLACK_ROOK, BLACK);//落子A		
				Temp_Position_BR1 = getSq1;
				//Value = Action(p + 1);//繼續找下一個
				Bitboard possible2 = possible, attack_bit2;//必須複製一個
				while (possible2 > 0) {
					getSq2 = pop_lsb(&possible2);//由於是由possble開始取，只會取新的
					attack_bit2 = ROOK_NEARS_ATTACK[getSq2];
					if (!(attack_bit2 & Piece_W)) {
						Set_Piece(getSq2, BLACK_ROOK, BLACK);//落子B	
						Temp_Position_BR2 = getSq2;
						Action(BLACK_LIGHT_BISHOP);
						Remove_Piece(getSq2, BLACK);
					}
				}
				Remove_Piece(getSq1, BLACK);
			}
		}
	}
	else if (p == BLACK_RIGHT_ROOK) {//黑雙城
		possible = Possible_Piece[p];//得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_W;//被攻擊則去除
		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			attack_bit = ROOK_NEARS_ATTACK[getSq];//得到城的鄰近四
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (attack_bit & Piece_W) {
				continue;
			}
			else {
				Set_Piece(getSq, BLACK_ROOK, BLACK);//落子
				
				if (p == BLACK_LEFT_ROOK)
					Temp_Position_BR1 = getSq;
				else
					Temp_Position_BR2 = getSq;

				//Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Value = Action(p + 1);//繼續找下一個
				Remove_Piece(getSq, BLACK);
				//Piece_Attack_B &= ~attack_bit;
			}
		}
	}
	else if (p == BLACK_LIGHT_BISHOP || p == BLACK_DARK_BISHOP) {//黑主教
		possible = Possible_Piece[p];//得到可能位置

		if (p == BLACK_LIGHT_BISHOP) {//很直覺= =
			if (board[b7] == BLACK_PAWN && board[d7] == BLACK_PAWN)
				possible = SQUARE_BB[c8];
		}
		else {
			if (board[e7] == BLACK_PAWN && board[g7] == BLACK_PAWN)
				possible = SQUARE_BB[f8];
		}


		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_W;//被攻擊則去除
		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			//get_bishop_attacks((Square)sq, Piece_All);
			//BISHOP_NEARS_ATTACK[getSq];
			attack_bit = get_bishop_attacks(getSq, Piece_All);
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (attack_bit & Piece_W) {
				continue;
			}
			else {
				Set_Piece(getSq, BLACK_BISHOP, BLACK);//落子
				//Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				
				Value = Action(p + 1);//繼續找下一個
				Remove_Piece(getSq, BLACK);
				//Piece_Attack_B &= ~attack_bit;
			}
		}
	}
	else {//呼到最後一層、才印出
		/* fast test*/
		//放完黑子後請在此判斷，前面都已經判斷過Biece_B沒碰到白子
		Bitboard  Piece_Atack_B_Long = Put_Black_Piece_Done();
		if (Piece_Atack_B_Long & Piece_W) {
			return 0;
		}

		//debug
		//DisplayBoard((int*)board);
		//print_bitboard(Piece_Attack_B);
		//int_bitboard(Piece_W);
		//if (Piece_Attack_B & Piece_W) {//黑長程攻擊力打到白
		//	return 100;
		//}
		//printf("\rdepth %llu", index_Game++);
		//fflush(stdout);
		printf("index=%d=============================\n", num_Game);
		Draw_Board();
		end_t = clock();
		printf("total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		if (++num_Game > 1000) {
			system("pause");
			exit(0);
		}

		return 10000;
	}

	return -1;
}