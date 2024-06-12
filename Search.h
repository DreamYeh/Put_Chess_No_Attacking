#pragma once
enum DPiece : unsigned int {
	WHITE_A_PAWN, WHITE_B_PAWN, WHITE_C_PAWN, WHITE_D_PAWN, 
	WHITE_E_PAWN, WHITE_F_PAWN, WHITE_G_PAWN, WHITE_H_PAWN,
	WHITE_LEFT_KNIGHT,WHITE_RIGHT_KNIGHT,
	WHITE__KING, 
	WHITE_LEFT_ROOK,	WHITE_RIGHT_ROOK,
	WHITE__QUEEN,
	WHITE_LIGHT_BISHOP, WHITE_DARK_BISHOP,
	
	BLACK_A_PAWN, BLACK_B_PAWN,	BLACK_C_PAWN, BLACK_D_PAWN,
	BLACK_E_PAWN, BLACK_F_PAWN,	BLACK_G_PAWN, BLACK_H_PAWN,
	BLACK_LEFT_KNIGHT, BLACK_RIGHT_KNIGHT,
	BLACK__KING, 
	BLACK_LEFT_ROOK,  BLACK_RIGHT_ROOK,
	BLACK__QUEEN,
	BLACK_LIGHT_BISHOP,  BLACK_DARK_BISHOP,
	MAX_PIECE
};

class Search
{
private:
	Piece board[NSQUARES] = { NO_PIECE };
	
	long long time_temp;

	Bitboard  Possible_Piece[32];

	//64格是否有黑子、白子
	Bitboard  Piece_All = 0, Piece_W = 0, Piece_B = 0;

	//該格被攻擊
	Bitboard  Piece_Attack_W = 0, Piece_Attack_B = 0;
	Bitboard  Piece_Attack_W_init = 0, Piece_Attack_B_init = 0;
	Bitboard  Attacked_by_Piece[32];

	//該子是否開局已經被放置
	Square Init_Position[32];

	//b d兵位置 判斷左主教合法用
	Square WPawn_b = NO_SQUARE, WPawn_d = NO_SQUARE, WPawn_e = NO_SQUARE, WPawn_g = NO_SQUARE;
	Square BPawn_b = NO_SQUARE, BPawn_d = NO_SQUARE, BPawn_e = NO_SQUARE, BPawn_g = NO_SQUARE;
	Square WPawn_a = NO_SQUARE, WPawn_h = NO_SQUARE;
	Square BPawn_a = NO_SQUARE, BPawn_h = NO_SQUARE;
	//長程攻擊子位置
	Square Temp_Position_WQ = NO_SQUARE;
	Square Temp_Position_WR1 = NO_SQUARE;
	Square Temp_Position_WR2 = NO_SQUARE;
	Square Temp_Position_BQ = NO_SQUARE;
	Square Temp_Position_BR1 = NO_SQUARE;
	Square Temp_Position_BR2 = NO_SQUARE;

	Bitboard Put_White_Piece_Done();
	Bitboard Put_Black_Piece_Done();

	unsigned long long Num_Piece_Found[NO_SQUARE * NO_PIECE];
	unsigned long long num_Game = 0;
	int  Status_Search;
public:	
	Search();	

	void Init_Piece(Square sq, DPiece dp);
	void Draw_Board(void);
	
	void Set_Piece(Square sq, Piece p, Color c);
	void Remove_Piece(Square sq, Color c);	
	void SetParallel(Square setWPSQ, Square setBPSQ);

	int Active(int cmd);
	int Run(unsigned int p);

	void Print_Stat();
};

