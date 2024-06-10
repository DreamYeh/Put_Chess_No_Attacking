#include "types.h"
#include "Tables.h"
#include "Search.h"

#include <cstdlib>//system function: pause, exit
#include <ctime>  //time function
unsigned int num_Game = 0;
unsigned long long index_Game = 0;
Bitboard  Possi_Pawn[16];
Bitboard  Possible_Piece[32];


//64��O�_���¤l�B�դl
Bitboard  Piece_All = 0, Piece_W = 0, Piece_B = 0;

//�Ӯ�Q����
Bitboard  Piece_Atack_All = 0, Piece_Attack_W = 0, Piece_Attack_B = 0;
Bitboard  Attacked_by_Piece[32];

//�Ӥl�O�_�}���w�g�Q��m
Square Exist_Piece[32];
//�Ӥl�{�ɦ�m
Square Temp_Position[32];
//�p��X�ժ��{������A���ݥ]�t
Bitboard  Piece_Atack_W_QUEEN;
Bitboard  Piece_Atack_W_ROOK;
Bitboard  Piece_Atack_W_L;

//�L���S��P�_�A�էL��
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

	for (i = 16; i < 32; i++)//�Ҧ��Ѥl�i�H�b�ѽL�W���N��m
		for (j = 0; j < 64; j++)
			Possible_Piece[i] |= SQUARE_BB[j];

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


	//��l�S���Ѥl�i�}����
	for (i = 0; i < MAX_PIECE; i++) Attacked_by_Piece[i] = 0;
	//�U�Ѥl��}�l���O������m
	for (i = 0; i < MAX_PIECE; i++)	Exist_Piece[i] = NO_SQUARE;

	num_Game = 0;
}

//�o��Q�k��²��A�p�G�]�w����l�Ѥl�A�h�N�L�u�i��X�{����m�v�A�]���b�ߤ@��椺
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

//��JBoard ��X�O�_�������o�͡A�p�G���A�O�ֵo��
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
		p == 8 || p == 10 || p==12 || p ==14) {//�ĥ�if�A�H�]�A��h�P�˪��L��	
		possible = Possi_Pawn[p];//Possi_WaP �o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_B;//�Q�����h�h��

		bool NotFindPos = true;
		while(NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			attack_bit = WHITE_PAWN_ATTACKS[getSq];//�o��A���F������檺BitBoard attack
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (attack_bit & Piece_B) {
				continue;
			}
			else {
				posOfWhite[p] = getSq;
				Set_Piece(getSq, WHITE_PAWN, WHITE);//���lA
				//Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);

				Value = Action(p + 1);//�~���U�@��				
				
				Remove_Piece(getSq, WHITE);
				Attacked_by_Piece[p] = 0;
				//Piece_Attack_W &= ~attack_bit;
			}
		}
	}
	else if (p == 1 || p == 3 || p == 5 || p == 7 ||
			 p == 9 || p == 11 || p == 13 || p == 15) {//�§L
		possible = Possi_Pawn[p];
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_W;//�Q�����h�h��

		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			attack_bit = BLACK_PAWN_ATTACKS[getSq];//�o��A���F������檺BitBoard attack
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������A����A��U�@�ӥi���m
			if (attack_bit & Piece_W) {
				continue;
			}
			else {
				if (posOfWhite[p - 1] >= getSq) continue;//�L���S��P�w�A�§L����W�L�էL

				Set_Piece(getSq, BLACK_PAWN, BLACK);//���lA
				//Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(BLACK);
				
				Value = Action(p + 1);//�~���U�@��

				Remove_Piece(getSq, BLACK);
				Attacked_by_Piece[p] = 0;
				//Piece_Attack_B &= ~attack_bit;
			}
		}
	}
	else if (p == 16 || p == 18) {//���M�h
		possible = Possible_Piece[p];//�o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_B;//�Q�����h�h��

		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			attack_bit = KNIGHT_ATTACKS[getSq];//�o��A���F������檺BitBoard attack
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (attack_bit & Piece_B) {
				continue;
			}
			else {	
				Set_Piece(getSq, WHITE_KNIGHT, WHITE);//���lA
				//Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);
				Value = Action(p + 1);//�~���U�@��
				Remove_Piece(getSq, WHITE);
				Attacked_by_Piece[p] = 0;
				//Piece_Attack_W &= ~attack_bit;
			}
		}
	}
	else if (p == 17 || p == 19) {//���M�h
		possible = Possible_Piece[p];//�o��i���m
		possible = possible & ~Piece_All;//���l�h�h��
		possible = possible & ~Piece_Attack_W;//�Q�����h�h��

		bool NotFindPos = true;
		while (NotFindPos) {
			if (possible == 0) {
				return p;
			}
			getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
			attack_bit = KNIGHT_ATTACKS[getSq];//�o��A���F������檺BitBoard attack
			//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
			if (attack_bit & Piece_W) {
				continue;
			}
			else {
				Set_Piece(getSq, BLACK_KNIGHT, BLACK);//���lA
				//Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(BLACK);
				Value = Action(p + 1);//�~���U�@��
				Remove_Piece(getSq, BLACK);
				//Piece_Attack_B &= ~attack_bit;
				Attacked_by_Piece[p] = 0;
			}
		}
	}
	else if (p == 20 || p == 22) {//�դ��B�Z
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			Temp_Position[p] = getSq;
			attack_bit = KING_ATTACKS[getSq];
			if (attack_bit & Piece_B) {//������O�H �����O��誺��XD
				return p;
			}
			else {
				//Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);
				Value = Action(p + 1);//�~���U�@��
			}
		}
		else {
			possible = Possible_Piece[p];//�o��i���m
			possible = possible & ~Piece_All;//���l�h�h��
			possible = possible & ~Piece_Attack_B;//�Q�����h�h��

			bool NotFindPos = true;
			while (NotFindPos) {
				if (possible == 0) {
					return p;
				}
				getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
				attack_bit = KING_ATTACKS[getSq];//�o������F��K��BitBoard attack
				//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
				if (attack_bit & Piece_B) {
					continue;
				}
				else {
					if (p == 20) Set_Piece(getSq, WHITE_KING, WHITE);//���l
					else Set_Piece(getSq, WHITE_QUEEN, WHITE);//���l
					Temp_Position[p] = getSq;
					//Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(WHITE);
					Value = Action(p + 1);//�~���U�@��
					Remove_Piece(getSq, WHITE);
					//Piece_Attack_W &= ~attack_bit;
					Attacked_by_Piece[p] = 0;
				}
			}
		}
	}
	else if (p == 21/* || p == 23*/) {//�¤��B�Z
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = KING_ATTACKS[getSq];
			if (attack_bit & Piece_W) {//������O�H �����O��誺��XD
				return p;
			}
			else {
				//Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(BLACK);
				Value = Action(p + 1);//�~���U�@��
			}
		}
		else {
			possible = Possible_Piece[p];//�o��i���m
			possible = possible & ~Piece_All;//���l�h�h��
			possible = possible & ~Piece_Attack_W;//�Q�����h�h��
			bool NotFindPos = true;
			while (NotFindPos) {
				if (possible == 0) {
					return p;
				}
				getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
				attack_bit = KING_ATTACKS[getSq];//�o������F��K��BitBoard attack
				//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
				if (attack_bit & Piece_W) {
					continue;
				}
				else {
					if (p == 21) Set_Piece(getSq, BLACK_KING, BLACK);//���l
					else Set_Piece(getSq, BLACK_QUEEN, BLACK);//���l
					//Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(BLACK);
					Value = Action(p + 1);//�~���U�@��
					Remove_Piece(getSq, BLACK);
					//Piece_Attack_B &= ~attack_bit;
				}
			}
		}
	}
	//���J�դ�ӦZ�]���{�^�����l�A�ձ��s��J�����B�D�Шϱo��������
	else if (p == WHITE_LEFT_ROOK || p == WHITE_RIGHT_ROOK) {
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = ROOK_NEARS_ATTACK[getSq];
			Temp_Position[p] = getSq;
			if (attack_bit & Piece_B) {//������O�H �����O��誺��XD
				return p;
			}
			else {
				//Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);
				Value = Action(p + 1);//�~���U�@��
			}
		}
		else {
			possible = Possible_Piece[p];//�o��i���m
			possible = possible & ~Piece_All;//���l�h�h��
			possible = possible & ~Piece_Attack_B;//�Q�����h�h��

			bool NotFindPos = true;
			while (NotFindPos) {
				if (possible == 0) {
					return p;
				}
				getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
				attack_bit = ROOK_NEARS_ATTACK[getSq];//�o�쫰���F�����
				//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
				if (attack_bit & Piece_B) {
					continue;
				}
				else {
					Set_Piece(getSq, WHITE_ROOK, WHITE);//���l
					Temp_Position[p] = getSq;
					//Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(WHITE);
					Value = Action(p + 1);//�~���U�@��
					Remove_Piece(getSq, WHITE);
					//Piece_Attack_W &= ~attack_bit;
					Attacked_by_Piece[p] = 0;
				}
			}
		}
	}
	else if (p == WHITE_LIGHT_BISHOP || p == WHITE_DARK_BISHOP) {//�եD��
		//�ժ���ӥD�Ц]�����P���]�������ۤz�Z
		// �]�N�O�G��D�Ч����d�򤣷|�Q��񪺶®�D�мv�T�I
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = BISHOP_NEARS_ATTACK[getSq];
			if (attack_bit & Piece_B) {//������O�H �����O��誺��XD
				return p;
			}
			else {
				//Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(WHITE);
				Value = Action(p + 1);//�~���U�@��
			}
		}
		else {
			possible = Possible_Piece[p];//�o��i���m
			possible = possible & ~Piece_All;//���l�h�h��
			possible = possible & ~Piece_Attack_B;//�Q�����h�h��

			bool NotFindPos = true;
			while (NotFindPos) {
				if (possible == 0) {
					return p;
				}
				getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
				//BISHOP_NEARS_ATTACK[getSq];//�o��D�ЩҦ�������B�o�O�ճ̫��l�]���i�����P�_�I
				attack_bit = get_bishop_attacks(getSq, Piece_All);
				//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
				if (attack_bit & Piece_B) {
					continue;
				}
				else {
					Set_Piece(getSq, WHITE_BISHOP, WHITE);//���l
					//Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(WHITE);
					Value = Action(p + 1);//�~���U�@��
					Remove_Piece(getSq, WHITE);
					//Piece_Attack_W &= ~attack_bit;
					Attacked_by_Piece[p] = 0;
				}
			}
		}
	}
	else if (p == BLACK__QUEEN) {
		/*
		//�ܦ��o�����A�o�ɭԥդl���񧹤F
		// �]���i�H�ھکҦ��դl�P�_�X�u�Ҧ����{�l������v
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
			attack_bit = KING_ATTACKS[getSq];//�¤l�S��,�٬O�ݾF���
			if (attack_bit & Piece_W) {//������O�H �����O��誺��XD
				return p;
			}
			else {
				Attacked_by_Piece[p] = attack_bit;
				Update_Attack(BLACK);
				Value = Action(p + 1);//�~���U�@��
			}
		}
		else {
			possible = Possible_Piece[p];//�o��i���m
			possible = possible & ~Piece_All;//���l�h�h��
			possible = possible & ~Piece_Attack_W;//�Q�����h�h�� �`�N����Piece_Attack_W�]�A�Ҧ����{����
			bool NotFindPos = true;
			while (NotFindPos) {
				if (possible == 0) {
					return p;
				}
				getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
				attack_bit = KING_ATTACKS[getSq];//�o������F��K��BitBoard attack
				//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
				if (attack_bit & Piece_W) {
					continue;
				}
				else {
					Set_Piece(getSq, BLACK_QUEEN, BLACK);//���l
					Attacked_by_Piece[p] = attack_bit;
					Update_Attack(BLACK);
					Value = Action(p + 1);//�~���U�@��
					Remove_Piece(getSq, BLACK);
				}
			}
		}

	}
	/*
	else if (p == 24 || p == 26) {//������
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = ROOK_NEARS_ATTACK[getSq];
			if (attack_bit & Piece_B) {//������O�H �����O��誺��XD
				return p;
			}
			else {
				Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Value = Action(p + 1);//�~���U�@��
			}
		}
		else {
			possible = Possible_Piece[p];//�o��i���m
			possible = possible & ~Piece_All;//���l�h�h��
			possible = possible & ~Piece_Attack_B;//�Q�����h�h��

			bool NotFindPos = true;
			while (NotFindPos) {
				if (possible == 0) {
					return p;
				}
				getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
				attack_bit = ROOK_NEARS_ATTACK[getSq];//�o�쫰���F�����
				//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
				if (attack_bit & Piece_B) {
					continue;
				}
				else {
					Set_Piece(getSq, WHITE_ROOK);//���l
					Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
					Value = Action(p + 1);//�~���U�@��
					Remove_Piece(getSq, WHITE);
					Piece_Attack_W &= ~attack_bit;
				}
			}
		}
	}
	else if (p == 25 || p == 27) {//������
			if (Exist_Piece[p] != NO_SQUARE) {
				getSq = Exist_Piece[p];
				attack_bit = ROOK_NEARS_ATTACK[getSq];
				if (attack_bit & Piece_W) {//������O�H �����O��誺��XD
					return p;
				}
				else {
					Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
					Value = Action(p + 1);//�~���U�@��
				}
			}
			else {
				possible = Possible_Piece[p];//�o��i���m
				possible = possible & ~Piece_All;//���l�h�h��
				possible = possible & ~Piece_Attack_W;//�Q�����h�h��
				bool NotFindPos = true;
				while (NotFindPos) {
					if (possible == 0) {
						return p;
					}
					getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
					attack_bit = ROOK_NEARS_ATTACK[getSq];//�o�쫰���F��|
					//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
					if (attack_bit & Piece_W) {
						continue;
					}
					else {						
						Set_Piece(getSq, BLACK_ROOK);//���l
						Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
						Value = Action(p + 1);//�~���U�@��
						Remove_Piece(getSq, BLACK);
						Piece_Attack_B &= ~attack_bit;
					}
				}
			}
	}
	else if (p == 28 || p == 30) {//�եD��
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = BISHOP_NEARS_ATTACK[getSq];
			if (attack_bit & Piece_B) {//������O�H �����O��誺��XD
				return p;
			}
			else {
				Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Value = Action(p + 1);//�~���U�@��
			}
		}
		else {
			possible = Possible_Piece[p];//�o��i���m
			possible = possible & ~Piece_All;//���l�h�h��
			possible = possible & ~Piece_Attack_B;//�Q�����h�h��

			bool NotFindPos = true;
			while (NotFindPos) {
				if (possible == 0) {
					return p;
				}
				getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
				//BISHOP_NEARS_ATTACK[getSq];//�o��D�оF�����
				attack_bit = get_bishop_attacks(getSq, Piece_All);					
				//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
				if (attack_bit & Piece_B) {
					continue;
				}
				else {
					Set_Piece(getSq, WHITE_BISHOP);//���l
					Piece_Attack_W |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
					//if (p == 30) {//WHITE_LIGHT_BISHOP
					//	Bitboard bb = get_bishop_attacks(getSq, Piece_All);
					//	print_bitboard(bb);						
					//}

					Value = Action(p + 1);//�~���U�@��
					Remove_Piece(getSq, WHITE);
					Piece_Attack_W &= ~attack_bit;
				}
			}
		}
	}
	else if (p == 29 || p == 31) {//�¥D��
		if (Exist_Piece[p] != NO_SQUARE) {
			getSq = Exist_Piece[p];
			attack_bit = BISHOP_NEARS_ATTACK[getSq];
			if (attack_bit & Piece_W) {//������O�H �����O��誺��XD
				return p;
			}
			else {
				Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
				Value = Action(p + 1);//�~���U�@��
			}
		}
		else {
			possible = Possible_Piece[p];//�o��i���m
			possible = possible & ~Piece_All;//���l�h�h��
			possible = possible & ~Piece_Attack_W;//�Q�����h�h��
			bool NotFindPos = true;
			while (NotFindPos) {
				if (possible == 0) {
					return p;
				}
				getSq = pop_lsb(&possible);//���X�Ĥ@�ӥi�ϥΪ���, possible���o�Ӧ��0
				//get_bishop_attacks((Square)sq, Piece_All);
				//BISHOP_NEARS_ATTACK[getSq];
				attack_bit = get_bishop_attacks(getSq, Piece_All);
				//�Y�F������榳�Ĥ�l attack & bit_units[]�A������O�H�A����A��U�@�ӥi���m
				if (attack_bit & Piece_W) {
					continue;
				}
				else {
					Set_Piece(getSq, BLACK_BISHOP);//���l
					Piece_Attack_B |= attack_bit;//�NA�F�������]�w���u�Ĥ褣�i��m����m�v
					Value = Action(p + 1);//�~���U�@��
					Remove_Piece(getSq, BLACK);
					Piece_Attack_B &= ~attack_bit;
				}
			}
		}
	}*/
	else {//�I��̫�@�h�B�~�L�X		
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