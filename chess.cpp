#if 0
#include "chess.h"


Square::Square()
{
	piece = EMPTY;
	color = NONE;
}

void Square::setSpace(Square* space)
{
	color = space->getColor();
	piece = space->getPiece();
}

void Square::setEmpty()
{
	color = NONE;
	piece = EMPTY;
}

Piece Square::getPiece()
{
	return piece;
}

Color Square::getColor()
{
	return color;
}

void Square::setPieceAndColor(Piece p)
{
	piece = p;
	color = c;

}


void Board::printBoard() {
	using namespace std;
	cout << "   x: 0  1  2  3  4  5  6  7 " << endl << "y:" << endl;
	for (int j = 7; j >= 0; j--)
	{
		cout << " " << j << "   ";
		for (int i = 0; i < 8; i++)
		{
			Piece p = square[i][j].getPiece();
			Color c = square[i][j].getColor();

			switch (p)
			{
			case KING: (c == WHITE) ? cout << " Ｋ" : cout << " ｋ";
				break;
			case QUEEN: (c == WHITE) ? cout << " Ｑ" : cout << " ｑ";
				break;
			case BISHOP:(c == WHITE) ? cout << " Ｂ" : cout << " ｂ";
				break;
			case KNIGHT:(c == WHITE) ? cout << " Ｎ" : cout << " ｎ";
				break;
			case ROOK: (c == WHITE) ? cout << " Ｒ" : cout << " ｒ";
				break;
			case PAWN: (c == WHITE) ? cout << " Ｐ" : cout << " ｐ";
				break;
			case EMPTY: cout << " 口";
				break;
			default: cout << "XXX";
				break;
			}

		}
		cout << endl;
	}
	
}

bool Board::doMove() {
	using namespace std;
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	while (!stop)
	{
		(turn == WHITE) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;
		cout << "Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
		cin >> move;
		x1 = move[0] - 48;
		y1 = move[1] - 48;
		x2 = move[2] - 48;
		y2 = move[3] - 48;
		if (getSquare(x1, y1)->getColor() == turn)
		{


			if (makeMove(x1, y1, x2, y2) == false)
			{
				cout << "Invalid move, try again." << endl;
			}
			else
				stop = true;
		}
		else
			cout << "That's not your piece. Try again." << endl;
	}
	if (getSquare(x2, y2)->getPiece() == KING)
		if (getSquare(x1, y1)->getColor() == WHITE)
		{
			cout << "WHITE WINS" << endl;
			return false;
		}
		else

		{
			cout << "BLACK WINS" << endl;
			return false;
		}


	if (turn == BLACK)
		turn = WHITE;
	else
		turn = BLACK;

	return true;

}

void Board::setBoard()
{
	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[1][0].setPieceAndColor(KNIGHT, WHITE);
	square[2][0].setPieceAndColor(BISHOP, WHITE);
	square[3][0].setPieceAndColor(QUEEN, WHITE);
	square[4][0].setPieceAndColor(KING, WHITE);
	square[5][0].setPieceAndColor(BISHOP, WHITE);
	square[6][0].setPieceAndColor(KNIGHT, WHITE);
	square[7][0].setPieceAndColor(ROOK, WHITE);

	square[0][7].setPieceAndColor(ROOK, BLACK);
	square[1][7].setPieceAndColor(KNIGHT, BLACK);
	square[2][7].setPieceAndColor(BISHOP, BLACK);
	square[3][7].setPieceAndColor(QUEEN, BLACK);
	square[4][7].setPieceAndColor(KING, BLACK);
	square[5][7].setPieceAndColor(BISHOP, BLACK);
	square[6][7].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);

	for (int i = 0; i < 8; i++)
	{
		square[i][1].setPieceAndColor(PAWN, WHITE);
		square[i][6].setPieceAndColor(PAWN, BLACK);

	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].setPieceAndColor(EMPTY, NONE);

	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}

}

void Board::setProblem()
{
	unsigned int sum = 0;
	int x, y;
	int y_WP[8], y_BP[8];//在x列的兵放在那個y
	int y_WP_init[8], y_BP_init[8];//在x的兵初始放在那個y
	int y_WP_offset[8], y_BP_offset[8];//shift
	bool Carry = false;

	int lo;//location x=lo%8  y=lo/8
	
	int l_WR0 = 0, l_WR1 = 0, l_BR0 = 0, l_BR1 = 0; //雙方共四個城堡的位置
	int l_WN0 = 0, l_WN1 = 0, l_BN0 = 0, l_BN1 = 0;	//雙方共四個騎士的位置
	int l_WB0 = 0, l_WB1 = 0, l_BB0 = 0, l_BB1 = 0;	//雙方共四個主教的位置
	int l_WQ = 0, l_BQ;
	int l_WK = 0, l_BK;

	int l_WR0i = 0, l_WR1i = 0, l_BR0i = 0, l_BR1i = 0; //初始位
	int l_WN0i = 0, l_WN1i = 0, l_BN0i = 0, l_BN1i = 0;	//
	int l_WB0i = 0, l_WB1i = 1, l_BB0i = 0, l_BB1i = 1;	//
	int l_WQi = 0, l_BQi = 0;
	int l_WKi = 0, l_BKi = 0;

	for (x = 0; x < 8; x++) {
		y_WP_init[x] = 1; y_BP_init[x] = 6;//下2和上2
		y_WP[x] = 1; y_BP[x] = 6;//下2和上2
		y_WP_offset[x] = 0; y_BP_offset[x] = 0;
	}
	for (unsigned int ii = 0; ; ii++) {	
		//empty Board
		for (x = 0; x < 8; x++)
		{
			for (y = 0; y < 8; y++)
				square[x][y].setPieceAndColor(EMPTY, NONE);
		}
		//put fixed piece
		square[7][1].setPieceAndColor(ROOK, BLACK);
		l_BR1 = 7 + 1*8;
		square[4][3].setPieceAndColor(QUEEN, BLACK);
		l_BQ = 4 + 3*8;
		square[1][5].setPieceAndColor(QUEEN, WHITE);
		l_WQ = 1 + 5*8;
		square[1][6].setPieceAndColor(ROOK, WHITE);
		l_WR1 = 1 + 6*8;
		square[0][7].setPieceAndColor(ROOK, BLACK);
		l_BR0 = 0 + 7*8;
		square[7][7].setPieceAndColor(KING, BLACK);
		l_BK = 7 + 7*8;

		//put pawn  ===========================================
		for (x = 0; x < 8; x++) {
			//empty determine
			for (y_WP[x] = y_WP_init[x]; y_WP[x] < 8; y_WP[x]++) {
				if (square[x][y_WP[x]].getPiece() == EMPTY) {

					//check it does not attack other

					break;
				}
			}
			for (y_BP[x] = y_BP_init[x]; y_BP[x] > 0; y_BP[x]--) {
				if (square[x][y_BP[x]].getPiece() == EMPTY) break;
			}



			//針對特定子、單純找一個空位，放入棋子
			square[x][y_WP[x]].setPieceAndColor(PAWN, WHITE);
			square[x][y_BP[x]].setPieceAndColor(PAWN, BLACK);			
		}
		//put Rook
		for (l_WR0 = 0; l_WR0 < 64; l_WR0++) {
			x = l_WR0 % 8;  y = l_WR0 / 8;
			if (square[x][y].getPiece() == EMPTY) break;
		}
		square[x][y].setPieceAndColor(ROOK, WHITE);

		//Puk King
		for (l_WK = l_WKi; l_WK < 64; l_WK++) {
			x = l_WK % 8;  y = l_WK / 8;
			if (square[x][y].getPiece() == EMPTY) break;
		}
		square[x][y].setPieceAndColor(KING, WHITE);

		//check attck
		if (checkBoard())
		{
		}
		else {
			printBoard();
			printf("sum=%d ii=%d\n", sum++, ii);
			printf("y_WP=%d y_BP=%d y_WPi=%d y_BPi=%d\n",
				y_WP[0], y_BP[0], y_WP_init[0], y_BP_init[0]);
			printf("+===================================\n");
		}
Label_Gobal_Move:
		//move chess 
		//pawn case
		Carry = true;
		for (x = 0; x < 8; x++) {
			if (Carry) {
				Carry = false;
				y_WP_init[x] = y_WP[x] + 1;//變革
				if (y_WP_init[x] >= y_BP[x]) { //如果撞到對方
					y_WP_init[x] = 1;//重新拉回初始位置
					y_BP_init[x] = y_BP[x] - 1;
					if (y_BP_init[x] <= 1) {
						y_BP_init[x] = 6;//重新拉回初始位置
						Carry = true;
					}
				}
			}
		}

		//King case
		if (Carry) {
			do {
				l_WKi++;//往後找一個空位
				if (l_WKi == 63) {
					l_WKi = 0;
					Carry = true;
				}
				x = l_WKi % 8;  y = l_WKi / 8;
				if (square[x][y].getPiece() == EMPTY) break;
			} while (1);
		}

		if (Carry) {
			printf("Carry! x=%d\n", x);
			break;
		}
		if (sum > 10) break;//先這樣假設，因為解太多就沒意義
	}
}
bool Board::checkBoard () {
	//check each piece is not attcked by others
	bool result = false;

	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 7; y++) {
			switch (square[x][y].getPiece())
			{
				case PAWN:
					result = checkPawn(x, y);
					break;

				case KING:
					result = checkKing(x, y);
					break;

			}
			if (result) return true; //check end
		}
	}

	return false;
}



bool Board::playGame()
{
	system("cls");
	printBoard();
	return doMove();

}

bool Board::checkKing(int x, int y)
{
	if (square[x][y].getColor() == WHITE) {
		if (x == 0 && y == 0) {//左下
			if (square[1][0].getColor() == BLACK) return true;
			if (square[0][1].getColor() == BLACK) return true;
			if (square[1][1].getColor() == BLACK) return true;
		}
		else if (x == 0 && y == 7) {
			if (square[1][7].getColor() == BLACK) return true;
			if (square[0][6].getColor() == BLACK) return true;
			if (square[1][6].getColor() == BLACK) return true;
		}
		else if (x == 7 && y == 0) {
			if (square[7][1].getColor() == BLACK) return true;
			if (square[6][0].getColor() == BLACK) return true;
			if (square[6][1].getColor() == BLACK) return true;
		}
		else if (x == 7 && y == 7) {
			if (square[7][6].getColor() == BLACK) return true;
			if (square[6][7].getColor() == BLACK) return true;
			if (square[6][6].getColor() == BLACK) return true;
		}
		else if (x == 0) {
			if (square[0][y-1].getColor() == BLACK) return true;
			if (square[0][y+1].getColor() == BLACK) return true;
			if (square[1][y-1].getColor() == BLACK) return true;
			if (square[1][y+0].getColor() == BLACK) return true;
			if (square[1][y+1].getColor() == BLACK) return true;			
		}
		else if (x == 7) {
			if (square[7][y - 1].getColor() == BLACK) return true;
			if (square[7][y + 1].getColor() == BLACK) return true;
			if (square[6][y - 1].getColor() == BLACK) return true;
			if (square[6][y + 0].getColor() == BLACK) return true;
			if (square[6][y + 1].getColor() == BLACK) return true;
		}
		else if (y == 0) {
			if (square[x-1][0].getColor() == BLACK) return true;
			if (square[x+1][0].getColor() == BLACK) return true;
			if (square[x-1][1].getColor() == BLACK) return true;
			if (square[x+0][1].getColor() == BLACK) return true;
			if (square[x+1][1].getColor() == BLACK) return true;
		}
		else if (y == 7) {
			if (square[x - 1][7].getColor() == BLACK) return true;
			if (square[x + 1][7].getColor() == BLACK) return true;
			if (square[x - 1][6].getColor() == BLACK) return true;
			if (square[x + 0][6].getColor() == BLACK) return true;
			if (square[x + 1][6].getColor() == BLACK) return true;
		}
		else
		{
			if (square[x - 1][y].getColor() == BLACK) return true;
			if (square[x + 0][y].getColor() == BLACK) return true;
			if (square[x + 1][y].getColor() == BLACK) return true;
			if (square[x - 1][y-1].getColor() == BLACK) return true;
			if (square[x + 0][y-1].getColor() == BLACK) return true;
			if (square[x + 1][y-1].getColor() == BLACK) return true;
			if (square[x - 1][y + 1].getColor() == BLACK) return true;
			if (square[x + 0][y + 1].getColor() == BLACK) return true;
			if (square[x + 1][y + 1].getColor() == BLACK) return true;
		}
	} else if (square[x][y].getColor() == BLACK) {
		if (x == 0 && y == 0) {//左下
			if (square[1][0].getColor() == WHITE) return true;
			if (square[0][1].getColor() == WHITE) return true;
			if (square[1][1].getColor() == WHITE) return true;
		}
		else if (x == 0 && y == 7) {
			if (square[1][7].getColor() == WHITE) return true;
			if (square[0][6].getColor() == WHITE) return true;
			if (square[1][6].getColor() == WHITE) return true;
		}
		else if (x == 7 && y == 0) {
			if (square[7][1].getColor() == WHITE) return true;
			if (square[6][0].getColor() == WHITE) return true;
			if (square[6][1].getColor() == WHITE) return true;
		}
		else if (x == 7 && y == 7) {
			if (square[7][6].getColor() == WHITE) return true;
			if (square[6][7].getColor() == WHITE) return true;
			if (square[6][6].getColor() == WHITE) return true;
		}
		else if (x == 0) {
			if (square[0][y - 1].getColor() == WHITE) return true;
			if (square[0][y + 1].getColor() == WHITE) return true;
			if (square[1][y - 1].getColor() == WHITE) return true;
			if (square[1][y + 0].getColor() == WHITE) return true;
			if (square[1][y + 1].getColor() == WHITE) return true;
		}
		else if (x == 7) {
			if (square[7][y - 1].getColor() == WHITE) return true;
			if (square[7][y + 1].getColor() == WHITE) return true;
			if (square[6][y - 1].getColor() == WHITE) return true;
			if (square[6][y + 0].getColor() == WHITE) return true;
			if (square[6][y + 1].getColor() == WHITE) return true;
		}
		else if (y == 0) {
			if (square[x - 1][0].getColor() == WHITE) return true;
			if (square[x + 1][0].getColor() == WHITE) return true;
			if (square[x - 1][1].getColor() == WHITE) return true;
			if (square[x + 0][1].getColor() == WHITE) return true;
			if (square[x + 1][1].getColor() == WHITE) return true;
		}
		else if (y == 7) {
			if (square[x - 1][7].getColor() == WHITE) return true;
			if (square[x + 1][7].getColor() == WHITE) return true;
			if (square[x - 1][6].getColor() == WHITE) return true;
			if (square[x + 0][6].getColor() == WHITE) return true;
			if (square[x + 1][6].getColor() == WHITE) return true;
		}
		else
		{
			if (square[x - 1][y].getColor() == WHITE) return true;
			if (square[x + 0][y].getColor() == WHITE) return true;
			if (square[x + 1][y].getColor() == WHITE) return true;
			if (square[x - 1][y - 1].getColor() == WHITE) return true;
			if (square[x + 0][y - 1].getColor() == WHITE) return true;
			if (square[x + 1][y - 1].getColor() == WHITE) return true;
			if (square[x - 1][y + 1].getColor() == WHITE) return true;
			if (square[x + 0][y + 1].getColor() == WHITE) return true;
			if (square[x + 1][y + 1].getColor() == WHITE) return true;
		}
	}
	return false;
}
bool Board::checkQueen(int x, int y)
{
	return false;
}

bool Board::checkBishop(int x, int y) 
{
	return false;
}
bool Board::checkKnight(int x, int y)
{
	return false;
}

bool Board::checkRook(int x, int y)
{
	int i;
	if (square[x][y].getColor() == WHITE) {
		for (i = 0; i < 7; i++) {
			if ((x + i) > 7) break;
			if (square[x + i][y].getColor() == BLACK) return true;
		}
		for (i = 0; i < 7; i++) {
			if ((x - i) < 0) break;
			if (square[x - i][y].getColor() == BLACK) return true;
		}
		for (i = 0; i < 7; i++) {
			if ((y + i) < 0) break;
			if (square[x][y+i].getColor() == BLACK) return true;
		}
		for (i = 0; i < 7; i++) {
			if ((y - i) < 0) break;
			if (square[x][y-i].getColor() == BLACK) return true;
		}
	}
	if (square[x][y].getColor() == BLACK) {
		for (i = 0; i < 7; i++) {
			if ((x + i) > 7) break;
			if (square[x + i][y].getColor() == WHITE) return true;
		}
		for (i = 0; i < 7; i++) {
			if ((x - i) < 0) break;
			if (square[x - i][y].getColor() == WHITE) return true;
		}
		for (i = 0; i < 7; i++) {
			if ((y + i) < 0) break;
			if (square[x][y + i].getColor() == WHITE) return true;
		}
		for (i = 0; i < 7; i++) {
			if ((y - i) < 0) break;
			if (square[x][y - i].getColor() == WHITE) return true;
		}
	}
}

bool Board::checkPawn(int x, int y)
{
	if (square[x][y].getColor() == WHITE) {
		if (x == 0) {
			if (square[1][y+1].getColor() == BLACK) return true;
		}
		else if (x == 7) {
			if (square[6][y+1].getColor() == BLACK) return true;
		}
		else {
			if (square[x+1][y + 1].getColor() == BLACK) return true;
			if (square[x-1][y + 1].getColor() == BLACK) return true;
		}
	} else if (square[x][y].getColor() == BLACK) {
		if (x == 0) {
			if (square[1][y - 1].getColor() == WHITE) return true;
		}
		else if (x == 7) {
			if (square[6][y - 1].getColor() == WHITE) return true;
		}
		else {
			if (square[x + 1][y - 1].getColor() == WHITE) return true;
			if (square[x - 1][y - 1].getColor() == WHITE) return true;
		}
	}
	return false;
}




bool Board::makeMove(int x1, int y1, int x2, int y2) {

	return false;
}
#endif