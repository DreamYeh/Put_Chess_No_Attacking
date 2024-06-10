#include "types.h"
#include "Tables.h"
#include "Search.h"

#include <cstdlib>//system function: pause, exit
#include <ctime>  //time function

void Search::Init_Search() {
	int i, j;
	for (i = 0; i < NSQUARES; i++)	board[i] = NO_PIECE;

	for (i = 0; i < 32; i++)//�Ҧ��Ѥl�i�H�b�ѽL�W���N��m
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
		
	//a1�Odark��
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


//��l�S���Ѥl�i�}����
	for (i = 0; i < MAX_PIECE; i++) Attacked_by_Piece[i] = 0;
	//�U�Ѥl��}�l���O������m
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
	Force_to_Finish = false;
	time_temp = time(NULL);
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
/*
void Search::Get_Board(int get_board[]) {
	for (int i = 0; i < 64; i++) {
		get_board[i] = board[i];
	}
}*/

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

//��J�ѤlA�C�էL ����p��
void Search::SetParallel(Square setWPSQ, Square setBPSQ)
{
	Possible_Piece[WHITE_A_PAWN] = SQUARE_BB[setWPSQ];
	Possible_Piece[BLACK_A_PAWN] = SQUARE_BB[setBPSQ];
}

void Search::Put_White_Piece_Done()
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
Bitboard Search::Put_Black_Piece_Done()
{
	Bitboard cc1 = get_bishop_attacks(Temp_Position_BQ, Piece_All);
	Bitboard cc2 = get_rook_attacks(Temp_Position_BQ, Piece_All);
	//Attacked_by_Piece[BLACK__QUEEN] = bb3 | bb4;

	Bitboard cc3 = get_rook_attacks(Temp_Position_BR1, Piece_All);
	Bitboard cc4 = get_rook_attacks(Temp_Position_BR2, Piece_All);
	//Attacked_by_Piece[BLACK_LEFT_ROOK] = get_rook_attacks(Temp_Position_BR1, Piece_All);
	//Attacked_by_Piece[BLACK_RIGHT_ROOK] = get_rook_attacks(Temp_Position_BR2, Piece_All);

	return (cc1 | cc2 | cc3 | cc4);
}

int Search::Action(unsigned int p) {
	int Value;
	Square getSq;
	Bitboard possible, attack_bit;
	clock_t start_t = 0, end_t = 0;

	if (Force_to_Finish)	return 0;
	
	if (p <= WHITE_H_PAWN) {//�ĥ�if�A�H�]�A��h�P�˪��L��	
		possible = Possible_Piece[p];//Possi_WaP �o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_B_init;//�Q�����h�h��

		while (true) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			attack_bit = WHITE_PAWN_ATTACKS[getSq];//�o��A���F������檺BitBoard attack
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_B)) {
				
				Set_Piece(getSq, WHITE_PAWN, WHITE);//���lA		
				Attacked_by_Piece[p] = attack_bit;

				//�o�B�J�Ȯɤ����D���ٲ��A���C�����s�p�⪺�ܡA�|�b�~��i�L�ɥX��
				Bitboard  Piece_Attack_W0 = Piece_Attack_W_init;
				for (unsigned int pi = 0; pi <= p; pi++) {
					Piece_Attack_W0 |= Attacked_by_Piece[pi];
				}
				//Black pawn = p + BLACK_A_PAWN()
				Bitboard poss2 = Possible_Piece[p + BLACK_A_PAWN];
				poss2 = poss2 & ~Piece_All;//���l�h�h��
				poss2 = poss2 & ~Piece_Attack_W0;//�Q�����h�h��
				//Value = Action(p + 1);//�~���U�@��
				while (true) {
					if (poss2 == 0) {
						break;
					}
					Square getSq2 = pop_lsb(&poss2);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
					if (getSq2 > getSq) {
						attack_bit = BLACK_PAWN_ATTACKS[getSq2];//�o��B���F������檺BitBoard attack
						if (!(attack_bit & Piece_W)) {
							Set_Piece(getSq2, BLACK_PAWN, BLACK);//���lB	
							//pawn and bishop relate=======================				
							if (p == WHITE_B_PAWN) {
								WPawn_b = getSq;	BPawn_b = getSq2;
							} else if (p == WHITE_D_PAWN) {
								WPawn_d = getSq;	BPawn_d = getSq2;
							} else if (p == WHITE_E_PAWN) {
								WPawn_e = getSq;	BPawn_e = getSq2;
							} else if (p == WHITE_G_PAWN) {
								WPawn_g = getSq;	BPawn_g = getSq2;
							}
							else if (p == WHITE_A_PAWN) {
								WPawn_a = getSq;
							}
							/*��ı�o�U���o�qCode �޿西�T�A���~�M�ɭP�Ĥ@�R�D�L�k�b�b�p�ɤ��]�X���G
							{

								if (getSq == d2)
									if (b_WPawn == b2)
										if (Init_Position[WHITE_DARK_BISHOP] != NO_SQUARE) //�p�G�շt��D�ФS�Q�]�m
											if (Init_Position[WHITE_DARK_BISHOP] != c1) //�B���O�]�w�bc1
												continue;	//�N�h��d2�L�I
							}*/
							//=============================================
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
				//Attacked_by_Piece[p] = 0;
			}
		}
	}
	else if (p == WHITE_LEFT_KNIGHT || p == WHITE_RIGHT_KNIGHT) {
		if (Init_Position[p] != NO_SQUARE) {
			return Action(p + 1);
		}
		Square getSq1, getSq2;

		possible = Possible_Piece[p];//�o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_B;//�Q�����h�h��

		while (possible) {
			if (possible == 0) {
				return p;
			}
			getSq1 = pop_lsb(&possible);
			attack_bit = KNIGHT_ATTACKS[getSq1];
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_B)) {
				Set_Piece(getSq1, WHITE_KNIGHT, WHITE);//���lA
				Attacked_by_Piece[WHITE_LEFT_KNIGHT] = attack_bit;
				//Value = Action(p + 1);//�~���U�@��
				Bitboard possible2 = possible, attack_bit2;//�����ƻs�@��
				while (possible2 > 0) {
					getSq2 = pop_lsb(&possible2);//�ѩ�O��possble�}�l���A�u�|���s��
					attack_bit2 = KNIGHT_ATTACKS[getSq2];
					if (!(attack_bit2 & Piece_B)) {
						Set_Piece(getSq2, WHITE_KNIGHT, WHITE);//���lB	
						Attacked_by_Piece[WHITE_RIGHT_KNIGHT] = attack_bit2;
						Action(WHITE__KING);
						Remove_Piece(getSq2, WHITE);
					}
				}
				Remove_Piece(getSq1, WHITE);
			}
		}
		return 0;
	}
	else if (p == WHITE__KING || p == WHITE__QUEEN) {
		if (Init_Position[p] != NO_SQUARE) {
			return Action(p + 1);
		}
		possible = Possible_Piece[p];//�o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_B;//�Q�����h�h��

		while (possible) {
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			attack_bit = KING_ATTACKS[getSq];//�o������F��K��BitBoard attack
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_B)) {
				if (p == WHITE__KING) Set_Piece(getSq, WHITE_KING, WHITE);//���l
				else if (p == WHITE__QUEEN)
				{
					Set_Piece(getSq, WHITE_QUEEN, WHITE);//���l
					Temp_Position_WQ = getSq;
				}
				Attacked_by_Piece[p] = attack_bit;
				Value = Action(p + 1);//�~���U�@��
				Remove_Piece(getSq, WHITE);
			}
		}
		return 0;
	}
	else if (p == WHITE_LEFT_ROOK) {//double bit
		if (Init_Position[WHITE_LEFT_ROOK] != NO_SQUARE) {
			return Action(p + 1);
		}
		//��1���]�w�B�ϥ����줸��X�t��k0530��
		Square getSq1, getSq2;
		possible = Possible_Piece[p];//�o��i���m

		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_B;//�Q�����h�h��

		while (possible) {
			getSq1 = pop_lsb(&possible);
			attack_bit = ROOK_NEARS_ATTACK[getSq1];
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_B)) {
				Set_Piece(getSq1, WHITE_ROOK, WHITE);//���lA
				Temp_Position_WR1 = getSq1;
				Attacked_by_Piece[WHITE_LEFT_ROOK] = attack_bit;
				//Value = Action(p + 1);//�i�}�I
				Bitboard possible2 = possible, attack_bit2;//�����ƻs�@��
				while (possible2 > 0) {
					getSq2 = pop_lsb(&possible2);//�ѩ�O��possble�}�l���A�u�|���s��
					attack_bit2 = ROOK_NEARS_ATTACK[getSq2];
					if (!(attack_bit2 & Piece_B)) {
						Set_Piece(getSq2, WHITE_ROOK, WHITE);//���lB	
						Temp_Position_WR2 = getSq2;
						Attacked_by_Piece[WHITE_RIGHT_ROOK] = attack_bit2;
						Action(WHITE_LIGHT_BISHOP);
						Remove_Piece(getSq2, WHITE);
					}
				}
				Remove_Piece(getSq1, WHITE);
			}
		}
		return 0;
	}
	else if (p == WHITE_RIGHT_ROOK) {
		if (Init_Position[p] != NO_SQUARE) {
			return Action(p + 1);
		}
		possible = Possible_Piece[p];//�o��i���m
		//���U���x
		if (WPawn_b == b2 && WPawn_d == d2)	{
			if (board[a3] == WHITE_PAWN) {
				possible = SQUARE_BB[a1] | SQUARE_BB[a2] | SQUARE_BB[b1];
			}
		}
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_B;//�Q�����h�h��
		while (possible) {
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			attack_bit = ROOK_NEARS_ATTACK[getSq];//�o�쫰���F�����
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_B)) {
				Set_Piece(getSq, WHITE_ROOK, WHITE);//���l
				Temp_Position_WR2 = getSq;
				//Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Attacked_by_Piece[p] = attack_bit;
				//Update_Attack(WHITE);
				Value = Action(p + 1);//�~���U�@��
				Remove_Piece(getSq, WHITE);
				//Piece_Attack_W &= ~attack_bit;
				Attacked_by_Piece[p] = 0;
			}
		}
		return 0;
	}
	else if (p == WHITE_LIGHT_BISHOP || p == WHITE_DARK_BISHOP) {//�եD��
		if (Init_Position[p] != NO_SQUARE) {
			return Action(p + 1);
		}
		//�ժ���ӥD�Ц]�����P���]�������ۤz�Z
		// �]�N�O�G��D�Ч����d�򤣷|�Q��񪺶®�D�мv�T�I
		possible = Possible_Piece[p];//�o��i���m

		if (p == WHITE_LIGHT_BISHOP) {//�k�U
			if (WPawn_e == e2 && WPawn_g == g2)
				possible = SQUARE_BB[f1];
		}
		else if (p == WHITE_DARK_BISHOP) {//c1�O�t��B�O�d���I ���U
			if (WPawn_b == b2 && WPawn_d == d2)
				possible = SQUARE_BB[c1];
		}
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_B;//�Q�����h�h��
		while (possible) {
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			//BISHOP_NEARS_ATTACK[getSq];//�o��D�ЩҦ�������B�o�O�ճ̫��l�]���i�����P�_�I
			attack_bit = get_bishop_attacks(getSq, Piece_All);
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_B)) {
				Set_Piece(getSq, WHITE_BISHOP, WHITE);//���l
				Attacked_by_Piece[p] = attack_bit;
				if (p == WHITE_DARK_BISHOP) {//�ܦ���
					Put_White_Piece_Done();
					if (!(Piece_Attack_W & Piece_B))
						Value = Action(BLACK_LEFT_KNIGHT);//������M�h
				}
				else
					Value = Action(p + 1);//�~���U�@��
				Remove_Piece(getSq, WHITE);
				Attacked_by_Piece[p] = 0;
			}
		}
		return 0;
	}
	else if (p == BLACK_LEFT_KNIGHT || p == BLACK_RIGHT_KNIGHT) {//���M�h
		if (Init_Position[p] != NO_SQUARE) {
			return Action(p + 1);
		}
		Square getSq1, getSq2;

		possible = Possible_Piece[p];//�o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_W;//�Q�����h�h��
		while (possible) {
			getSq1 = pop_lsb(&possible);
			attack_bit = KNIGHT_ATTACKS[getSq1];
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_W)) {
				Set_Piece(getSq1, BLACK_KNIGHT, BLACK);//���lA				
				//Value = Action(p + 1);//�~���U�@��
				Bitboard possible2 = possible, attack_bit2;//�����ƻs�@��
				while (possible2 > 0) {
					getSq2 = pop_lsb(&possible2);//�ѩ�O��possble�}�l���A�u�|���s��
					attack_bit2 = KNIGHT_ATTACKS[getSq2];
					if (!(attack_bit2 & Piece_W)) {
						Set_Piece(getSq2, BLACK_KNIGHT, BLACK);//���lB						
						Action(BLACK__KING);
						Remove_Piece(getSq2, BLACK);
					}
				}
				Remove_Piece(getSq1, BLACK);
			}
		}
		return 0;
	}
	else if (p == BLACK__KING || p == BLACK__QUEEN) {//�¤��B�Z
		if (Init_Position[p] != NO_SQUARE) {
			return Action(p + 1);
		}
		possible = Possible_Piece[p];//�o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_W;//�Q�����h�h��

		while (possible) {
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			attack_bit = KING_ATTACKS[getSq];//�o������F��K��BitBoard attack
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (attack_bit & Piece_W) {
				continue;
			}
			else {
				if (p == BLACK__KING)
					Set_Piece(getSq, BLACK_KING, BLACK);//���l
				else {
					Set_Piece(getSq, BLACK_QUEEN, BLACK);//���l
					Temp_Position_BQ = getSq;
				}
				//Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Value = Action(p + 1);//�~���U�@��
				Remove_Piece(getSq, BLACK);
				//Piece_Attack_B &= ~attack_bit;
			}
		}
		return 0;
	}
	else if (p == BLACK_LEFT_ROOK) {//������, ���줸�t��
		if (Init_Position[p] != NO_SQUARE) {
			return Action(p + 1);
		}
		Square getSq1, getSq2;
		possible = Possible_Piece[p];//�o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_W;//�Q�����h�h��

		while (possible) {
			getSq1 = pop_lsb(&possible);
			attack_bit = ROOK_NEARS_ATTACK[getSq1];
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_W)) {
				Set_Piece(getSq1, BLACK_ROOK, BLACK);//���lA		
				Temp_Position_BR1 = getSq1;
				//Value = Action(p + 1);//�~���U�@��
				Bitboard possible2 = possible, attack_bit2;//�����ƻs�@��
				while (possible2 > 0) {
					getSq2 = pop_lsb(&possible2);//�ѩ�O��possble�}�l���A�u�|���s��
					attack_bit2 = ROOK_NEARS_ATTACK[getSq2];
					if (!(attack_bit2 & Piece_W)) {
						Set_Piece(getSq2, BLACK_ROOK, BLACK);//���lB	
						Temp_Position_BR2 = getSq2;
						Action(BLACK_LIGHT_BISHOP);
						Remove_Piece(getSq2, BLACK);
					}
				}
				Remove_Piece(getSq1, BLACK);
			}
		}
		return 0;
	}
	else if (p == BLACK_RIGHT_ROOK) {//second
		if (Init_Position[p] != NO_SQUARE) {
			return Action(p + 1);
		}
		possible = Possible_Piece[p];//�o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_W;//�Q�����h�h��

		while (possible) {
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			attack_bit = ROOK_NEARS_ATTACK[getSq];//�o�쫰���F��|
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_W)) {
				Set_Piece(getSq, BLACK_ROOK, BLACK);//���l
				Temp_Position_BR2 = getSq;
				//Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Value = Action(p + 1);//�~���U�@��
				Remove_Piece(getSq, BLACK);
				//Piece_Attack_B &= ~attack_bit;
			}
		}
		return 0;
	}
	else if (p == BLACK_LIGHT_BISHOP || p == BLACK_DARK_BISHOP) {//�¥D��
		if (Init_Position[p] != NO_SQUARE) {
			return Action(p + 1);
		}
		possible = Possible_Piece[p];//�o��i���m

		if (p == BLACK_LIGHT_BISHOP) {//���W
			if (BPawn_b == b7 && BPawn_d == d7)
				possible = SQUARE_BB[c8];
		}
		else if (p == BLACK_DARK_BISHOP) {//�k�W
			if (BPawn_e == e7 && BPawn_g == g7)
				possible = SQUARE_BB[f8];
		}

		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_W;//�Q�����h�h��

		while (possible) {
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			//get_bishop_attacks((Square)sq, Piece_All);
			//BISHOP_NEARS_ATTACK[getSq];
			attack_bit = get_bishop_attacks(getSq, Piece_All);
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (!(attack_bit & Piece_W)) {
				Set_Piece(getSq, BLACK_BISHOP, BLACK);//���l
				//Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v

				Value = Action(p + 1);//�~���U�@��
				Remove_Piece(getSq, BLACK);
				//Piece_Attack_B &= ~attack_bit;
			}
		}
		return 0;
	}
	else {//�I��̫�@�h�B�~�L�X
		//�񧹶¤l��Цb���P�_�A�e�����w�g�P�_�LBiece_B�S�I��դl
		Bitboard  Piece_Atack_B_Long = Put_Black_Piece_Done();
		if (Piece_Atack_B_Long & Piece_W) {
			return 0;
		}

		num_Game++;
		printf("index=%d=============================t=%llds\n", num_Game, time(NULL)- time_temp);
		Draw_Board();
		//end_t = clock();
		//printf("total time = %d sec.\n", (end_t - start_t) / CLOCKS_PER_SEC);
		if (num_Game > 100) {
			Force_to_Finish = true;
			///system("pause");
			//exit(0);
		}

		return 0;
	}
	printf("There are something wrong, please contact DreamYeh for checking.\n");
	system("pause");
	exit(0);
	return -1;
}
