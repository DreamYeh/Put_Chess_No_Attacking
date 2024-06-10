#include "types.h"
#include "Tables.h"
#include "Search.h"

#include <cstdlib>//system function: pause, exit
#include <ctime>  //time function
unsigned int num_Game = 0;
unsigned long long index_Game = 0;
Bitboard  Possi_Pawn[16];
Bitboard  Possible_Piece[32];


//64格是否有黑子、白子
Bitboard  Piece_All = 0, Piece_W = 0, Piece_B = 0;

//該格被攻擊
Bitboard  Piece_Atack_All = 0, Piece_Attack_W = 0, Piece_Attack_B = 0;
Bitboard  Attacked_by_Piece[32];

//該子是否開局已經被放置
Square Exist_Piece[32];
//該子臨時位置
Square Temp_Position[32];
//計算出白長程攻擊格，不需包含
Bitboard  Piece_Atack_W_QUEEN;
Bitboard  Piece_Atack_W_ROOK;
Bitboard  Piece_Atack_W_L;

//兵的特殊判斷，白兵位
Square posOfWhite[32];

void Search::Init_Search() {
	int i, j;
	int x, y;
	for (i=0; i < NSQUARES;i++)	board[i] = NO_PIECE;

	Possi_Pawn[0] = SQUARE_BB[a2] | SQUARE_BB[a3] | SQUARE_BB[a4] | SQUARE_BB[a5] | SQUARE_BB[a6];
	Possi_Pawn[1] = SQUARE_BB[a7] | SQUARE_BB[a6] | SQUARE_BB[a5] | SQUARE_BB[a4] | SQUARE_BB[a3];
	Possi_Pawn[2] = SQUARE_BB[b2] | SQUARE_BB[b3] | SQUARE_BB[b4] | SQUARE_BB[b5] | SQUARE_BB[b6];
	Possi_Pawn[3] = SQUARE_BB[b7] | SQUARE_BB[b6] | SQUARE_BB[b5] | SQUARE_BB[b4] | SQUARE_BB[b3];
	Possi_Pawn[4] = SQUARE_BB[c2] | SQUARE_BB[c3] | SQUARE_BB[c4] | SQUARE_BB[c5] | SQUARE_BB[c6];
	Possi_Pawn[5] = SQUARE_BB[c7] | SQUARE_BB[c6] | SQUARE_BB[c5] | SQUARE_BB[c4] | SQUARE_BB[c3];
	Possi_Pawn[6] = SQUARE_BB[d2] | SQUARE_BB[d3] | SQUARE_BB[d4] | SQUARE_BB[d5] | SQUARE_BB[d6];
	Possi_Pawn[7] = SQUARE_BB[d7] | SQUARE_BB[d6] | SQUARE_BB[d5] | SQUARE_BB[d4] | SQUARE_BB[d3];
	Possi_Pawn[8] = SQUARE_BB[e2] | SQUARE_BB[e3] | SQUARE_BB[e4] | SQUARE_BB[e5] | SQUARE_BB[e6];
	Possi_Pawn[9] = SQUARE_BB[e7] | SQUARE_BB[e6] | SQUARE_BB[e5] | SQUARE_BB[e4] | SQUARE_BB[e3];
	Possi_Pawn[10] = SQUARE_BB[f2] | SQUARE_BB[f3] | SQUARE_BB[f4] | SQUARE_BB[f5] | SQUARE_BB[f6];
	Possi_Pawn[11] = SQUARE_BB[f7] | SQUARE_BB[f6] | SQUARE_BB[f5] | SQUARE_BB[f4] | SQUARE_BB[f3];
	Possi_Pawn[12] = SQUARE_BB[g2] | SQUARE_BB[g3] | SQUARE_BB[g4] | SQUARE_BB[g5] | SQUARE_BB[g6];
	Possi_Pawn[13] = SQUARE_BB[g7] | SQUARE_BB[g6] | SQUARE_BB[g5] | SQUARE_BB[g4] | SQUARE_BB[g3];
	Possi_Pawn[14] = SQUARE_BB[h2] | SQUARE_BB[h3] | SQUARE_BB[h4] | SQUARE_BB[h5] | SQUARE_BB[h6];
	Possi_Pawn[15] = SQUARE_BB[h7] | SQUARE_BB[h6] | SQUARE_BB[h5] | SQUARE_BB[h4] | SQUARE_BB[h3];

	for (i = 16; i < 32; i++)//所有棋子可以在棋盤上任意位置
		for (j = 0; j < 64; j++)
			Possible_Piece[i] |= SQUARE_BB[j];

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

	Possible_Piece[BLACK_DARK_BISHOP] = Possible_Piece[WHITE_DARK_BISHOP];

	Possible_Piece[BLACK_LIGHT_BISHOP] =
		SQUARE_BB[b1] | SQUARE_BB[d1] | SQUARE_BB[f1] | SQUARE_BB[h1] |
		SQUARE_BB[a2] | SQUARE_BB[c2] | SQUARE_BB[e2] | SQUARE_BB[g2] |
		SQUARE_BB[b3] | SQUARE_BB[d3] | SQUARE_BB[f3] | SQUARE_BB[h3] |
		SQUARE_BB[a4] | SQUARE_BB[c4] | SQUARE_BB[e4] | SQUARE_BB[g4] |
		SQUARE_BB[b5] | SQUARE_BB[d5] | SQUARE_BB[f5] | SQUARE_BB[h5] |
		SQUARE_BB[a6] | SQUARE_BB[c6] | SQUARE_BB[e6] | SQUARE_BB[g6] |
		SQUARE_BB[b7] | SQUARE_BB[d7] | SQUARE_BB[f7] | SQUARE_BB[h7] |
		SQUARE_BB[a8] | SQUARE_BB[c8] | SQUARE_BB[e8] | SQUARE_BB[g8];

	Possible_Piece[WHITE_LIGHT_BISHOP] = Possible_Piece[BLACK_LIGHT_BISHOP];


	//初始沒有棋子展開攻擊
	for (i = 0; i < MAX_PIECE; i++) Attacked_by_Piece[i] = 0;
	//各棋子剛開始都是未知位置
	for (i = 0; i < MAX_PIECE; i++)	Exist_Piece[i] = NO_SQUARE;

	num_Game = 0;
}

//這邊想法很簡單，如果設定的初始棋子，則將他「可能出現的位置」，侷限在唯一方格內
void Search::Init_Piece(DPiece dp, Square sq) {
	Exist_Piece[dp] = sq;
	Possible_Piece[dp] = SQUARE_BB[sq];
}

void Search::Get_Board(int get_board[]) {
	for (int i = 0; i < 64; i++) {
		get_board[i] = board[i];
	}
}

void DisplayBoard(int board[]);
void Search::Draw_Board() {
	DisplayBoard((int*)board);
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
	}
	else {
		Piece_B = Piece_B & ~SQUARE_BB[sq];
	}	
	
	Piece_All = Piece_W | Piece_B;
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

int Search::CheckQueen(Square sqWQ, Square sqBQ)
{
	Bitboard bb;
	bb = get_bishop_attacks((Square)sqWQ, Piece_All);
	if (bb & Piece_B) return 1;
	bb = get_rook_attacks((Square)sqWQ, Piece_All);
	if (bb & Piece_B) return 2;

	bb = get_bishop_attacks((Square)sqBQ, Piece_All);
	if (bb & Piece_W) return 3;
	bb = get_rook_attacks((Square)sqBQ, Piece_All);
	if (bb & Piece_W) return 4;

	return 0;
}

inline void Update_Attack(Color c) {
	if (c == WHITE) {
		Piece_Attack_W =
			Attacked_by_Piece[WHITE_A_PAWN] | Attacked_by_Piece[WHITE_B_PAWN] | Attacked_by_Piece[WHITE_C_PAWN] | Attacked_by_Piece[WHITE_D_PAWN] |
			Attacked_by_Piece[WHITE_E_PAWN] | Attacked_by_Piece[WHITE_F_PAWN] | Attacked_by_Piece[WHITE_G_PAWN] | Attacked_by_Piece[WHITE_H_PAWN] |
			Attacked_by_Piece[WHITE_LEFT_KNIGHT] | Attacked_by_Piece[WHITE_RIGHT_KNIGHT] |
			Attacked_by_Piece[WHITE__KING] | Attacked_by_Piece[WHITE__QUEEN] |
			Attacked_by_Piece[WHITE_LEFT_ROOK] | Attacked_by_Piece[WHITE_RIGHT_ROOK] | Attacked_by_Piece[WHITE_LIGHT_BISHOP] | Attacked_by_Piece[WHITE_DARK_BISHOP];
	}
	else {
		Piece_Attack_B =
			Attacked_by_Piece[BLACK_A_PAWN] | Attacked_by_Piece[BLACK_B_PAWN] | Attacked_by_Piece[BLACK_C_PAWN] | Attacked_by_Piece[BLACK_D_PAWN] |
			Attacked_by_Piece[BLACK_E_PAWN] | Attacked_by_Piece[BLACK_F_PAWN] | Attacked_by_Piece[BLACK_G_PAWN] | Attacked_by_Piece[BLACK_H_PAWN] |
			Attacked_by_Piece[BLACK_LEFT_KNIGHT] | Attacked_by_Piece[BLACK_RIGHT_KNIGHT] |
			Attacked_by_Piece[BLACK__KING] | Attacked_by_Piece[BLACK__QUEEN] |
			Attacked_by_Piece[BLACK_LEFT_ROOK] | Attacked_by_Piece[BLACK_RIGHT_ROOK] | Attacked_by_Piece[BLACK_LIGHT_BISHOP] | Attacked_by_Piece[BLACK_DARK_BISHOP];
	}
}

int Search::Action(unsigned int p) {
	int Value;
	Square getSq;
	Bitboard possible, attack_bit;
	clock_t start_t = 0, end_t = 0;
	if (p == 0) start_t = clock();

	if (p == 0 || p == 2 || p == 4 || p == 6 ||
		p == 8 || p == 10 || p==12 || p ==14) {//採用if，以包括更多同樣的兵種	
		possible = Possi_Pawn[p];//Possi_WaP 得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_B;//被攻擊則去除

		bool NotFindPos = true;
		while(NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			attack_bit = WHITE_PAWN_ATTACKS[getSq];//得到A的鄰近攻擊格的BitBoard attack
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (attack_bit & Piece_B) {
				continue;
			}
			else {
				posOfWhite[p] = getSq;
				Set_Piece(getSq, WHITE_PAWN, WHITE);//落子A
				//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);

				Value = Action(p + 1);//繼續找下一個				
				
				Remove_Piece(getSq, WHITE);
				Attacked_by_Piece[p] = 0;
				//Piece_Attack_W &= ~attack_bit;
			}
		}
	}
	else if (p == 1 || p == 3 || p == 5 || p == 7 ||
			 p == 9 || p == 11 || p == 13 || p == 15) {//黑兵
		possible = Possi_Pawn[p];
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
				if (posOfWhite[p - 1] >= getSq) continue;//兵的特殊判定，黑兵不能超過白兵

				Set_Piece(getSq, BLACK_PAWN, BLACK);//落子A
				//Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(BLACK);
				
				Value = Action(p + 1);//繼續找下一個

				Remove_Piece(getSq, BLACK);
				Attacked_by_Piece[p] = 0;
				//Piece_Attack_B &= ~attack_bit;
			}
		}
	}
	else if (p == 16 || p == 18) {//白騎士
		possible = Possible_Piece[p];//得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_B;//被攻擊則去除

		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			attack_bit = KNIGHT_ATTACKS[getSq];//得到A的鄰近攻擊格的BitBoard attack
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (attack_bit & Piece_B) {
				continue;
			}
			else {	
				Set_Piece(getSq, WHITE_KNIGHT, WHITE);//落子A
				//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);
				Value = Action(p + 1);//繼續找下一個
				Remove_Piece(getSq, WHITE);
				Attacked_by_Piece[p] = 0;
				//Piece_Attack_W &= ~attack_bit;
			}
		}
	}
	else if (p == 17 || p == 19) {//黑騎士
		possible = Possible_Piece[p];//得到可能位置
		possible = possible & ~Piece_All;//有子則去除
		possible = possible & ~Piece_Attack_W;//被攻擊則去除

		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
			attack_bit = KNIGHT_ATTACKS[getSq];//得到A的鄰近攻擊格的BitBoard attack
			//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
			if (attack_bit & Piece_W) {
				continue;
			}
			else {
				Set_Piece(getSq, BLACK_KNIGHT, BLACK);//落子A
				//Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(BLACK);
				Value = Action(p + 1);//繼續找下一個
				Remove_Piece(getSq, BLACK);
				//Piece_Attack_B &= ~attack_bit;
				Attacked_by_Piece[p] = 0;
			}
		}
	}
	else if (p == 20 || p == 22) {//白王、后
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			Temp_Position[p] = getSq;
			attack_bit = KING_ATTACKS[getSq];
			if (attack_bit & Piece_B) {//攻擊到別人 那必是對方的錯XD
				return p;
			}
			else {
				//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);
				Value = Action(p + 1);//繼續找下一個
			}
		}
		else {
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
					if (p == 20) Set_Piece(getSq, WHITE_KING, WHITE);//落子
					else Set_Piece(getSq, WHITE_QUEEN, WHITE);//落子
					Temp_Position[p] = getSq;
					//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(WHITE);
					Value = Action(p + 1);//繼續找下一個
					Remove_Piece(getSq, WHITE);
					//Piece_Attack_W &= ~attack_bit;
					Attacked_by_Piece[p] = 0;
				}
			}
		}
	}
	else if (p == 21/* || p == 23*/) {//黑王、后
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = KING_ATTACKS[getSq];
			if (attack_bit & Piece_W) {//攻擊到別人 那必是對方的錯XD
				return p;
			}
			else {
				//Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(BLACK);
				Value = Action(p + 1);//繼續找下一個
			}
		}
		else {
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
					if (p == 21) Set_Piece(getSq, BLACK_KING, BLACK);//落子
					else Set_Piece(getSq, BLACK_QUEEN, BLACK);//落子
					//Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(BLACK);
					Value = Action(p + 1);//繼續找下一個
					Remove_Piece(getSq, BLACK);
					//Piece_Attack_B &= ~attack_bit;
				}
			}
		}
	}
	//到放入白方皇后（長程）攻擊子，白接連放入城堡、主教使得局面完成
	else if (p == WHITE_LEFT_ROOK || p == WHITE_RIGHT_ROOK) {
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = ROOK_NEARS_ATTACK[getSq];
			Temp_Position[p] = getSq;
			if (attack_bit & Piece_B) {//攻擊到別人 那必是對方的錯XD
				return p;
			}
			else {
				//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);
				Value = Action(p + 1);//繼續找下一個
			}
		}
		else {
			possible = Possible_Piece[p];//得到可能位置
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
					Temp_Position[p] = getSq;
					//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(WHITE);
					Value = Action(p + 1);//繼續找下一個
					Remove_Piece(getSq, WHITE);
					//Piece_Attack_W &= ~attack_bit;
					Attacked_by_Piece[p] = 0;
				}
			}
		}
	}
	else if (p == WHITE_LIGHT_BISHOP || p == WHITE_DARK_BISHOP) {//白主教
		//白的兩個主教因為不同色格因此不互相干擾
		// 也就是亮格主教攻擊範圍不會被後放的黑格主教影響！
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = BISHOP_NEARS_ATTACK[getSq];
			if (attack_bit & Piece_B) {//攻擊到別人 那必是對方的錯XD
				return p;
			}
			else {
				//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);
				Value = Action(p + 1);//繼續找下一個
			}
		}
		else {
			possible = Possible_Piece[p];//得到可能位置
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
					//Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(WHITE);
					Value = Action(p + 1);//繼續找下一個
					Remove_Piece(getSq, WHITE);
					//Piece_Attack_W &= ~attack_bit;
					Attacked_by_Piece[p] = 0;
				}
			}
		}
	}
	else if (p == BLACK__QUEEN) {
		/*
		//至此發生轉折，這時候白子都放完了
		// 因此可以根據所有白子判斷出「所有長程子攻擊格」
		Bitboard b1 = get_bishop_attacks(Temp_Position[WHITE__QUEEN], Piece_All);
		Bitboard b2 = get_rook_attacks(Temp_Position[WHITE__QUEEN], Piece_All);
		Attacked_by_Piece[WHITE__QUEEN] = b1 | b2;
		b1 = get_rook_attacks(Temp_Position[WHITE_LEFT_ROOK], Piece_All);
		Attacked_by_Piece[WHITE_LEFT_ROOK] = b1;
		b2 = get_rook_attacks(Temp_Position[WHITE_RIGHT_ROOK], Piece_All);
		Attacked_by_Piece[WHITE_RIGHT_ROOK] = b2;
		
		Update_Attack(WHITE);	
		//print_bitboard(Attacked_by_Piece[WHITE__QUEEN]);
		*/
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = KING_ATTACKS[getSq];//黑子沒放完,還是看鄰近格
			if (attack_bit & Piece_W) {//攻擊到別人 那必是對方的錯XD
				return p;
			}
			else {
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(BLACK);
				Value = Action(p + 1);//繼續找下一個
			}
		}
		else {
			possible = Possible_Piece[p];//得到可能位置
			possible = possible & ~Piece_All;//有子則去除
			possible = possible & ~Piece_Attack_W;//被攻擊則去除 注意此時Piece_Attack_W包括所有遠程攻擊
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
					Set_Piece(getSq, BLACK_QUEEN, BLACK);//落子
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(BLACK);
					Value = Action(p + 1);//繼續找下一個
					Remove_Piece(getSq, BLACK);
				}
			}
		}

	}
	/*
	else if (p == 24 || p == 26) {//白雙堡
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = ROOK_NEARS_ATTACK[getSq];
			if (attack_bit & Piece_B) {//攻擊到別人 那必是對方的錯XD
				return p;
			}
			else {
				Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Value = Action(p + 1);//繼續找下一個
			}
		}
		else {
			possible = Possible_Piece[p];//得到可能位置
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
					Set_Piece(getSq, WHITE_ROOK);//落子
					Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
					Value = Action(p + 1);//繼續找下一個
					Remove_Piece(getSq, WHITE);
					Piece_Attack_W &= ~attack_bit;
				}
			}
		}
	}
	else if (p == 25 || p == 27) {//黑雙城
			if (Exist_Piece[p] != NO_SQUARE) {
				getSq = Exist_Piece[p];
				attack_bit = ROOK_NEARS_ATTACK[getSq];
				if (attack_bit & Piece_W) {//攻擊到別人 那必是對方的錯XD
					return p;
				}
				else {
					Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
					Value = Action(p + 1);//繼續找下一個
				}
			}
			else {
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
						Set_Piece(getSq, BLACK_ROOK);//落子
						Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
						Value = Action(p + 1);//繼續找下一個
						Remove_Piece(getSq, BLACK);
						Piece_Attack_B &= ~attack_bit;
					}
				}
			}
	}
	else if (p == 28 || p == 30) {//白主教
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = BISHOP_NEARS_ATTACK[getSq];
			if (attack_bit & Piece_B) {//攻擊到別人 那必是對方的錯XD
				return p;
			}
			else {
				Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Value = Action(p + 1);//繼續找下一個
			}
		}
		else {
			possible = Possible_Piece[p];//得到可能位置
			possible = possible & ~Piece_All;//有子則去除
			possible = possible & ~Piece_Attack_B;//被攻擊則去除

			bool NotFindPos = true;
			while (NotFindPos) {
				if (possible == 0) {
					return p;
				}
				getSq = pop_lsb(&possible);//推出第一個可使用的位, possible的這個位取0
				//BISHOP_NEARS_ATTACK[getSq];//得到主教鄰近攻擊
				attack_bit = get_bishop_attacks(getSq, Piece_All);					
				//若鄰近攻擊格有敵方子 attack & bit_units[]，攻擊到別人，移動A到下一個可能位置
				if (attack_bit & Piece_B) {
					continue;
				}
				else {
					Set_Piece(getSq, WHITE_BISHOP);//落子
					Piece_Attack_W |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
					//if (p == 30) {//WHITE_LIGHT_BISHOP
					//	Bitboard bb = get_bishop_attacks(getSq, Piece_All);
					//	print_bitboard(bb);						
					//}

					Value = Action(p + 1);//繼續找下一個
					Remove_Piece(getSq, WHITE);
					Piece_Attack_W &= ~attack_bit;
				}
			}
		}
	}
	else if (p == 29 || p == 31) {//黑主教
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = BISHOP_NEARS_ATTACK[getSq];
			if (attack_bit & Piece_W) {//攻擊到別人 那必是對方的錯XD
				return p;
			}
			else {
				Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
				Value = Action(p + 1);//繼續找下一個
			}
		}
		else {
			possible = Possible_Piece[p];//得到可能位置
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
					Set_Piece(getSq, BLACK_BISHOP);//落子
					Piece_Attack_B |= attack_bit;//將A鄰近攻擊格設定為「敵方不可放置的位置」
					Value = Action(p + 1);//繼續找下一個
					Remove_Piece(getSq, BLACK);
					Piece_Attack_B &= ~attack_bit;
				}
			}
		}
	}*/
	else {//呼到最後一層、才印出		
		//printf("\rdepth %llu", index_Game++);
		//fflush(stdout);
		//if (Check() != -1) return 32;
		//if(CheckQueen(b6, e4)) return 32;		
		printf("index=%d=============================\n", num_Game++);
		DisplayBoard((int*)board);
		end_t = clock();
		printf("total time = %f sec.\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

		if (num_Game++ > 10) {
			system("pause");
			exit(0);
		}

		return 10000;
	}

	return -1;
}