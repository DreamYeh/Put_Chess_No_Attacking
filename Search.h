#pragma once
enum DPiece : unsigned int {
	WHITE_A_PAWN, BLACK_A_PAWN, WHITE_B_PAWN, BLACK_B_PAWN,
	WHITE_C_PAWN, BLACK_C_PAWN, WHITE_D_PAWN, BLACK_D_PAWN,
	WHITE_E_PAWN, BLACK_E_PAWN, WHITE_F_PAWN, BLACK_F_PAWN,
	WHITE_G_PAWN, BLACK_G_PAWN, WHITE_H_PAWN, BLACK_H_PAWN,
	WHITE_LEFT_KNIGHT, BLACK_LEFT_KNIGHT, WHITE_RIGHT_KNIGHT, BLACK_RIGHT_KNIGHT,
	WHITE__KING, BLACK__KING, 
	//ªøµ{
	WHITE__QUEEN, 
	WHITE_LEFT_ROOK,	WHITE_RIGHT_ROOK,
	WHITE_LIGHT_BISHOP, WHITE_DARK_BISHOP,
	BLACK__QUEEN,
	BLACK_LEFT_ROOK,  BLACK_RIGHT_ROOK,
	BLACK_LIGHT_BISHOP,  BLACK_DARK_BISHOP,
	MAX_PIECE
};

class Search
{
private:
	Piece board[NSQUARES];
	//int Get_Lowest_1(Bitboard value);
public:
	void Init_Search();
	void Init_Piece(DPiece dp, Square sq);
	void Draw_Board(void);
	
	void Get_Board(int get_board[]);
	void Set_Piece(Square sq, Piece p, Color c);
	void Remove_Piece(Square sq, Color c);	
	int Check();
	int CheckQueen(Square sqWQ, Square sqBQ);
	int Action(unsigned int p);
};

