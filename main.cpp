#include <iostream>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <fstream>

using namespace std;

//Function prototypes
void gotoRowCol(int,int);
void BoardInitialization(char [8][8]);
void ChessPiecesPrinting(char [8][8],int,int,int,int);
void SquarePrinting(char,int,int,int,int);
void GridPrinting(char [8][8],char,int,int,int,int);
void TurnChanging(int&);
void SelectPieces(char [8][8],int [2],int [2],int [2],int&,int&,int,int,int);
bool HorizontalMovement(int [2],int [2]);
bool VerticalMovement(int [2],int [2]);
bool DiagnolMovement(int [2],int [2]);
bool Player1(char [8][8],int [2]);
bool Player2(char [8][8],int [2]);
bool PieceIdentifier(char [8][8],int&,int [2]);
bool HorizontalPathClearCheck(char [8][8],int [2],int [2]);
bool VerticalPathClearCheck(char [8][8],int [2],int [2]);
bool DiagnolPathClearCheck(char [8][8],int [2],int [2]);
bool PawnMoves(char [8][8],int [2],int [2],int);
bool RookMoves(char [8][8],int [2],int [2]);
bool KnightMoves(char [8][8],int [2],int [2],int);
bool BishopMoves(char [8][8],int [2],int [2]);
bool QueenMoves(char [8][8],int [2],int [2]);
bool KingMoves(char [8][8],int [2],int [2]);
bool LegalMoves(char [8][8],int [2],int [2],int);
void MovementOnBoard(char [8][8],char&,int [2],int [2]);
bool ValidMovement(char [8][8],int,int [2]);
void PawnPromotion(char [8][8],int [2],int [2],int,char &);
void LegalMoveHighlight(char [8][8],char,int [2],int [2],int,int,int);
void FindOpponentKing(char [8][8],int [2],int [2],int);
bool Check(char [8][8],int [2],int [2],int);
bool SelfCheck(char [8][8],int [2],int [2],int);
void GameSave(char [8][8],int&);
void GameLoad(char [8][8],int&);


int main()
{
    system("mode 1080, 720");
    char ChessBoard[8][8];
    char Symbol=-37,A, Piece, FirstKey,Key;
    int InitialPosition[2], FinalPosition[2], DuplicateInitialPosition[2], DuplicateFinalPosition[2];
    int Row=720, Col=1080, RowDim=Row/140, ColDim=Col/140, CurrentRow=0, CurrentCol=0, Turn=2;

	for(int row=20; row<35; row++)
	{
		gotoRowCol(row,65);
		cout << Symbol;
		gotoRowCol(row,100);
		cout << Symbol;
	}
	for(int col=65; col<101; col++)
	{
		gotoRowCol(20,col);
		cout << Symbol;
		gotoRowCol(35,col);
		cout << Symbol;
	}

    gotoRowCol(25, 75);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << " N == NEW GAME";
    gotoRowCol(27, 75);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << " L == LOAD GAME";
    gotoRowCol(29, 75);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << " E == EXIT GAME";
    gotoRowCol(31, 82);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cin >> FirstKey;
    gotoRowCol(25, 75);
    cout << "                ";
    gotoRowCol(27, 75);
    cout << "                ";
    gotoRowCol(29, 75);
    cout << "                ";
    gotoRowCol(31, 82);
    cout << "               ";
	for(int row=20; row<35; row++)
	{
		gotoRowCol(row,65);
		cout <<"                    ";
		gotoRowCol(row,100);
		cout << "                    ";
	}
	for(int col=65; col<101; col++)
	{
		gotoRowCol(20,col);
		cout << "                        ";
		gotoRowCol(35,col);
		cout << "                        ";
	}

    if(FirstKey == 78 || FirstKey == 110)
    {
        BoardInitialization(ChessBoard);
    }
	else if(FirstKey == 108 || FirstKey == 76)
	{
		GameLoad(ChessBoard,Turn);
		TurnChanging(Turn);
	}
    else if(FirstKey == 69 || FirstKey == 101)
    {
        system("cls");
        return 0;
    }
    GridPrinting(ChessBoard, Symbol, Row, Col, RowDim, ColDim);
    do
    {
        if(Check(ChessBoard, DuplicateInitialPosition, DuplicateFinalPosition, Turn)==true)
        {
            gotoRowCol(4,134);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << "YOUR KING IS IN CHECK!!!";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        }
        if(Check(ChessBoard, DuplicateInitialPosition, DuplicateFinalPosition, Turn)==false)
        {
            gotoRowCol(3,134);
            cout << "                                 ";
        }
        TurnChanging(Turn);
        GridPrinting(ChessBoard, Symbol, Row, Col, RowDim, ColDim);
        do
        {
            SelectPieces(ChessBoard, InitialPosition, FinalPosition, DuplicateInitialPosition, CurrentRow, CurrentCol, RowDim, ColDim, Turn);
        }
        while(!PieceIdentifier(ChessBoard, Turn, InitialPosition));
        LegalMoveHighlight(ChessBoard, Symbol, InitialPosition, FinalPosition, Turn, RowDim, ColDim);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        SelectPieces(ChessBoard, FinalPosition, FinalPosition, DuplicateFinalPosition, CurrentRow, CurrentCol, RowDim, ColDim, Turn);
        if(PieceIdentifier(ChessBoard, Turn, FinalPosition) || !LegalMoves(ChessBoard, InitialPosition, FinalPosition, Turn))
        {
            TurnChanging(Turn);
            continue;
        }
        MovementOnBoard(ChessBoard, A, InitialPosition, FinalPosition);
        TurnChanging(Turn);
        if(Check(ChessBoard, DuplicateInitialPosition, DuplicateFinalPosition, Turn)==true)
        {
            ChessBoard[InitialPosition[0]][InitialPosition[1]]=ChessBoard[FinalPosition[0]][FinalPosition[1]];
            ChessBoard[FinalPosition[0]][FinalPosition[1]]=A;
            gotoRowCol(6,134);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << "YOU CANNOT MAKE THIS MOVE YOUR" << endl;
			gotoRowCol(7,134);
			cout << "YOU ARE IN CHECK!!";
            continue;
        }
        gotoRowCol(30, 90);
        cout << "                                                ";
        TurnChanging(Turn);
        PawnPromotion(ChessBoard, InitialPosition, FinalPosition, Turn, Key);
        gotoRowCol(14, 90);
        cout << "                                                         ";
        gotoRowCol(50, 90);
        cout << "                                                         ";
		//GameSave(ChessBoard,Turn);
    }
    while(true);
    return 0;
}

//This a C++ function which is use to move the cursor to any of your desired coordinates
void gotoRowCol(int rpos, int cpos)
{
    int xpos=cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

//This function is to initialized the ChessBoard i.e. Assign characters to array elements
void BoardInitialization(char ChessBoard[8][8])
{
	//Loop for assigning Pawn piece character to both Players
    for(int i=0; i<8; i++)
    {
        ChessBoard[1][i] = 'P';
        ChessBoard[6][i] = 'p';
    }
	//Loop for assigning Space characters to empty spaces
    for(int row=2; row<6; row++)
    {
        for(int col=0; col<8; col++)
        {
            ChessBoard[row][col] = ' ';
        }
    }
	//Assigning Player 1 elements to an Array
    ChessBoard[0][0] = ChessBoard[0][7] = 'R';
    ChessBoard[0][1] = ChessBoard[0][6] = 'N';
    ChessBoard[0][2] = ChessBoard[0][5] = 'B';
    ChessBoard[0][3] = 'Q';
    ChessBoard[0][4] = 'K';
	//Assigning Player 2 elements to an Array
    ChessBoard[7][0] = ChessBoard[7][7] = 'r';
    ChessBoard[7][1] = ChessBoard[7][6] = 'n';
    ChessBoard[7][2] = ChessBoard[7][5] = 'b';
    ChessBoard[7][3] = 'q';
    ChessBoard[7][4] = 'k';
}

//This function is prinintg Array elements on the console screen
void ChessPiecesPrinting(char ChessBoard[8][8], int Row, int Col, int RowDim, int ColDim)
{
    gotoRowCol(Row*RowDim+RowDim/2, Col*ColDim+ColDim/2);
    if(ChessBoard[Row][Col]>='A' && ChessBoard[Row][Col]<='Z')
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    }
    cout << ChessBoard[Row][Col];
}

//This function prints a simple square box
void SquarePrinting(char Symbol, int Row, int Col, int RowDim, int ColDim)
{
    for(int r=0; r<=RowDim; r++)
    {
        for(int c=0; c<=ColDim; c++)
        {
            if(r == 0 || r == RowDim || c == 0 || c == ColDim)
            {
                gotoRowCol(Row*RowDim+r, Col*ColDim+c);
                cout << Symbol;
            }
        }
    }
}

//This Function prints complete Chess board on the console screen
void GridPrinting(char ChessBoard[8][8], char Symbol, int Row, int Col, int RowDim, int ColDim)
{
    for(int r=0; r<8; r++)
    {
        for(int c=0; c<8; c++)
        {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            SquarePrinting(Symbol, r, c, RowDim, ColDim);
            ChessPiecesPrinting(ChessBoard, r, c, RowDim, ColDim);
        }
    }
	for(int row=0; row<10; row++)
	{
		gotoRowCol(row,130);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << Symbol;
	}
	for(int col=130; col<170; col++)
	{
		gotoRowCol(0,col);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << Symbol;
		gotoRowCol(10,col);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << Symbol;
	}
	gotoRowCol(1,142);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "NOTIFICATION BOX";
	for(int row=30; row<40; row++)
	{
		gotoRowCol(row,130);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << Symbol;
	}
	for(int col=130; col<170; col++)
	{
		gotoRowCol(30,col);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << Symbol;
		gotoRowCol(40,col);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << Symbol;
	}
	gotoRowCol(31,145);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "CONTROLS";
	gotoRowCol(35,141);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "SAVE: 'S' or 's'";
}

//This function is changing Players Turn
void TurnChanging(int &Turn)
{
    if(Turn == 1)
    {
        Turn = 2;
    }
    else
    {
        Turn = 1;
    }
	if(Turn==1)
	{
		gotoRowCol(35, 60);
		cout << "                              ";
		gotoRowCol(5, 60);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "PLAYER " << Turn << " TURN";
	}
	else if(Turn==2)
	{
		gotoRowCol(5, 60);
		cout << "                              ";
		gotoRowCol(35, 60);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout << "PLAYER " << Turn << " TURN";
	}
}

//This is the function in which we are making pieces selection, also moving the cursor on the screen
void SelectPieces(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2], int DuplicateInitialPosition[2], int& CurrentRow, int& CurrentCol, int RowDim, int ColDim, int Turn)
{
   bool PieceSelect = false;

   do
    {
        if(kbhit())
        {
            int PressedKey = getch();

            if(PressedKey == 224)
            {
                PressedKey = getch();

                switch(PressedKey)
                {
                case 72:
                {
                    CurrentRow--;
                    if(CurrentRow<0)
                    {
                        CurrentRow=7;
                    }
                    break;
                }
                case 80:
                {
                    CurrentRow++;
                    if(CurrentRow>7)
                    {
                        CurrentRow=0;
                    }
                    break;
                }
                case 75:
                {
                    CurrentCol--;
                    if(CurrentCol<0)
                    {
                        CurrentCol=7;
                    }
                    break;
                }
                case 77:
                {
                    CurrentCol++;
                    if(CurrentCol>7)
                    {
                        CurrentCol=0;
                    }
                    break;
                }
                }

            }
            else if(PressedKey == 13)
            {
                PieceSelect = true;
            }
			else if(PressedKey == 83 || PressedKey == 115)
			{
				GameSave(ChessBoard,Turn);
			}
        }
        InitialPosition[0] = DuplicateInitialPosition[0] = CurrentRow;
        InitialPosition[1] = DuplicateInitialPosition[1] = CurrentCol;
        gotoRowCol(CurrentRow*RowDim+RowDim/2, CurrentCol*ColDim+ColDim/2);
	}while(PieceSelect==false);
}

//This function will check if a piece can move horizontally or not
bool HorizontalMovement(int InitialPosition[2], int FinalPosition[2])
{
    if(InitialPosition[0] == FinalPosition[0])
	{
		return true;
	}
	else
	{
		return false;
	}
}

//This function will check if a piece can move vertically or not
bool VerticalMovement(int InitialPosition[2], int FinalPosition[2])
{
    if(InitialPosition[1] == FinalPosition[1])
	{
		return true;
	}
	else
	{
		return false;
	}
}

//This function will check if a piece can move diagonally or not
bool DiagnolMovement(int InitialPosition[2], int FinalPosition[2])
{
	if(abs(FinalPosition[0]-InitialPosition[0])==abs(FinalPosition[1]-InitialPosition[1]))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//This function checks if it is a Player 1 piece or not
bool Player1(char ChessBoard[8][8], int InitialPosition[2])
{
    if(ChessBoard[InitialPosition[0]][InitialPosition[1]] >= 'A' && ChessBoard[InitialPosition[0]][InitialPosition[1]] <= 'Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//This function checks if it is a Player 2 piece or not
bool Player2(char ChessBoard[8][8], int InitialPosition[2])
{
    if(ChessBoard[InitialPosition[0]][InitialPosition[1]] >= 'a' && ChessBoard[InitialPosition[0]][InitialPosition[1]] <= 'z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//This function idetifies the Players pieces according to their turn
bool PieceIdentifier(char ChessBoard[8][8], int &Turn, int InitialPosition[2])
{
    if(Turn==1)
    {
        if(Player1(ChessBoard, InitialPosition) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    else if(Turn==2)
    {
        if(Player2(ChessBoard, InitialPosition) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

//This function checks if the horizontal path is clear for piece movement or not
bool HorizontalPathClearCheck(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2])
{
    int MaxC, MinC;

    if(FinalPosition[1] > InitialPosition[1])
    {
        MinC = InitialPosition[1];
        MaxC = FinalPosition[1];
    }
    else
    {
        MinC = FinalPosition[1];
        MaxC = InitialPosition[1];
    }

    int T = abs(MaxC-MinC);

    for(int i=1; i<T; i++)
    {
        if(ChessBoard[InitialPosition[0]][MinC+i] != ' ')
        {
            return false;
        }
    }
    return true;
}

//This function checks if the vertical path is clear for piece movement or not
bool VerticalPathClearCheck(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2])
{
    int MaxR, MinR;

    if(FinalPosition[0] > InitialPosition[0])
    {
        MinR = InitialPosition[0];
        MaxR = FinalPosition[0];
    }
    else
    {
        MinR = FinalPosition[0];
        MaxR = InitialPosition[0];
    }

    int T = abs(MaxR-MinR);

    for(int i=1; i<T; i++)
    {
        if(ChessBoard[MinR+i][InitialPosition[1]] != ' ')
        {
            return false;
        }
    }
    return true;
}

//This function checks if the diagnol path is clear for piece movement or not
bool DiagnolPathClearCheck(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2])
{
    int MaxC, MinC, MaxR, MinR, TR;

    if(InitialPosition[0]<FinalPosition[0] && InitialPosition[1]<FinalPosition[1])
    {
        MinR = InitialPosition[0];
        MaxR = FinalPosition[0];
        MinC = InitialPosition[1];
        MaxC = FinalPosition[1];

        TR = abs(MinR-MaxR);
        for(int r=1; r<TR; r++)
        {
            if(ChessBoard[MinR+r][MinC+r] != ' ')
            {
                return false;
            }
        }
        return true;
    }

    else if(InitialPosition[0]>FinalPosition[0] && InitialPosition[1]>FinalPosition[1])
    {
        MaxR = InitialPosition[0];
        MinR = FinalPosition[0];
        MaxC = InitialPosition[1];
        MinC = FinalPosition[1];

        TR = abs(MaxR-MinR);
        for(int r=1; r<TR; r++)
        {
            if(ChessBoard[MinR+r][MinC+r] != ' ')
            {
                return false;
            }

        }
        return true;
    }

    else if(InitialPosition[0]>FinalPosition[0] && InitialPosition[1]<FinalPosition[1])
    {
        MaxR = InitialPosition[0];
        MinR = FinalPosition[0];
        MinC = InitialPosition[1];
        MaxC = FinalPosition[1];

        TR = abs(MaxR-MinR);
        for(int r=1; r<TR; r++)
        {
            if(ChessBoard[MaxR-r][MinC+r] != ' ')
            {
                return false;
            }

        }
        return true;
    }

    else if(InitialPosition[0]<FinalPosition[0] && InitialPosition[1]>FinalPosition[1])
    {
        MinR = InitialPosition[0];
        MaxR = FinalPosition[0];
        MaxC = InitialPosition[1];
        MinC = FinalPosition[1];

        TR = abs(MaxR-MinR);
        for(int r=1; r<TR; r++)
        {
            if(ChessBoard[MinR+r][MaxC-r] != ' ')
            {
                return false;
            }

        }
        return true;
    }
}

//This function checks Pawn Legal Move.
bool PawnMoves(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2], int Turn)
{
	char Piece = ChessBoard[InitialPosition[0]][InitialPosition[1]];

	if(VerticalMovement(InitialPosition, FinalPosition) == true)
    {
		if(Turn == 1 && ChessBoard[1][InitialPosition[1]]=='P')
        {
            if((InitialPosition[0]-FinalPosition[0])==-1 || (InitialPosition[0]-FinalPosition[0])==-2 && Piece>='A' && Piece<='Z')
            {
                return true;
            }
            return false;
        }
		else if(Turn == 1)
        {
            if((InitialPosition[0]-FinalPosition[0])==-1 && Piece>='A' && Piece<='Z')
            {
                return true;
            }
            return false;
        }
    }
	if(VerticalMovement(InitialPosition,FinalPosition) == true)
    {
		if(Turn == 2 && ChessBoard[6][InitialPosition[1]]=='p')
        {
            if((InitialPosition[0]-FinalPosition[0])==1 || (InitialPosition[0]-FinalPosition[0])==2 && Piece>='a' && Piece<='z')
            {
                return true;
            }
            return false;
        }
        if(Turn == 2)
        {
            if((InitialPosition[0]-FinalPosition[0])==1 && Piece>='a' && Piece<='z')
            {
                return true;
            }
            return false;
        }
    }
}

//This function checks the legal moves of Rook
bool RookMoves(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2])
{
    return ((HorizontalMovement(InitialPosition, FinalPosition)==true && HorizontalPathClearCheck(ChessBoard, InitialPosition, FinalPosition)==true) || (VerticalMovement(InitialPosition, FinalPosition)==true && VerticalPathClearCheck(ChessBoard, InitialPosition, FinalPosition)==true));
}

//This function checks the legal moves of Knight
bool KnightMoves(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2], int Turn)
{
   return ((abs(FinalPosition[0]-InitialPosition[0])==2 && abs(FinalPosition[1]-InitialPosition[1])==1) || (abs(FinalPosition[0]-InitialPosition[0])==1 && abs(FinalPosition[1]-InitialPosition[1])==2));
}

//This function checks the legal moves of Bishop
bool BishopMoves(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2])
{
   return (DiagnolMovement(InitialPosition, FinalPosition) && DiagnolPathClearCheck(ChessBoard, InitialPosition, FinalPosition));
}

//This function checks the legal moves of Queen
bool QueenMoves(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2])
{
    if(BishopMoves(ChessBoard,InitialPosition,FinalPosition)==true || RookMoves(ChessBoard,InitialPosition,FinalPosition)==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//This function checks the legal moves of King
bool KingMoves(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2])
{
    return ((abs(InitialPosition[0]-FinalPosition[0])==1 || abs(InitialPosition[0]-FinalPosition[0])==0) && (abs(InitialPosition[1]-FinalPosition[1])==1 || abs(InitialPosition[1]-FinalPosition[1])==0));
}

//This function returns the legal moves of every single piece
bool LegalMoves(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2], int Turn)
{
    switch(ChessBoard[InitialPosition[0]][InitialPosition[1]])
    {
    case 'P':
    case 'p':
    {
        return PawnMoves(ChessBoard, InitialPosition, FinalPosition, Turn);
        break;
    }
    case 'R':
    case 'r':
    {
        return RookMoves(ChessBoard, InitialPosition, FinalPosition);
        break;
    }
    case 'B':
    case 'b':
    {
        return BishopMoves(ChessBoard, InitialPosition, FinalPosition);
        break;
    }
    case 'Q':
    case 'q':
    {
        return QueenMoves(ChessBoard,InitialPosition,FinalPosition);
        break;
    }
    case 'N':
    case 'n':
    {
        return KnightMoves(ChessBoard, InitialPosition, FinalPosition, Turn);
        break;
    }
    case 'K':
    case 'k':
    {
        return KingMoves(ChessBoard, InitialPosition, FinalPosition);
        break;
    }
	default:
		break;
    }
}

//With the help of this function we are moving on the Chess board.
//When you make a move, it replces your previous position with 'space'
void MovementOnBoard(char ChessBoard[8][8], char& A, int InitialPosition[2], int FinalPosition[2])
{
    A=ChessBoard[FinalPosition[0]][FinalPosition[1]];
    ChessBoard[FinalPosition[0]][FinalPosition[1]] = ChessBoard[InitialPosition[0]][InitialPosition[1]];
    ChessBoard[InitialPosition[0]][InitialPosition[1]] = ' ' ;
}

//This function tells that the destination where you are moving is legal or illegal.
//If you are moving to a place where already one of your piece is placed, it will not allow that move
bool ValidMovement(char ChessBoard[8][8], int Turn, int FinalPosition[2])
{
	if(PieceIdentifier(ChessBoard,Turn,FinalPosition)==false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//This fucntion handles the work related to Pawn Promotion
void PawnPromotion(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2], int Turn, char &Key)
{
	char PressedKey;

	if(Turn==1)
	{
		if(ChessBoard[7][FinalPosition[1]]=='P')
		{
			gotoRowCol(45,0);
			cout << "PLAYER 1 PAWN PROMOTION:";
			gotoRowCol(46,0);
			cout << "PRESS 'Q' FOR QUEEN";
			gotoRowCol(47,0);
			cout << "PRESS 'B' FOR BISHOP";
			gotoRowCol(48,0);
			cout << "PRESS 'N' FOR KNIGHT";
			gotoRowCol(49,0);
			cout << "PRESS 'R' FOR ROOK";
			PressedKey = _getch();
			gotoRowCol(45,0);
			cout << "                        ";
			gotoRowCol(46,0);
			cout << "                        ";
			gotoRowCol(47,0);
			cout << "                        ";
			gotoRowCol(48,0);
			cout << "                        ";
			gotoRowCol(49,0);
			cout << "                        ";
			switch (PressedKey)
				{
					case 'Q':
						ChessBoard[FinalPosition[0]][FinalPosition[1]]= 'Q';
						break;
					case 'B':
						ChessBoard[FinalPosition[0]][FinalPosition[1]]= 'B';
						break;
					case 'N':
						ChessBoard[FinalPosition[0]][FinalPosition[1]]= 'N';
						break;
					case 'R':
						ChessBoard[FinalPosition[0]][FinalPosition[1]]= 'R';
						break;
				}
			}
		}
	if(Turn==2)
	{
		if(ChessBoard[0][FinalPosition[1]]=='p')
		{

			gotoRowCol(45,0);
			cout << "PLAYER 2 PAWN PROMOTION:";
			gotoRowCol(46,0);
			cout << "PRESS 'q' FOR QUEEN";
			gotoRowCol(47,0);
			cout << "PRESS 'b' FOR BISHOP";
			gotoRowCol(48,0);
			cout << "PRESS 'n' FOR KNIGHT";
			gotoRowCol(49,0);
			cout << "PRESS 'r' FOR ROOK";
			PressedKey = _getch();
			gotoRowCol(35,120);
			cout << "                        ";
			gotoRowCol(36,120);
			cout << "                        ";
			gotoRowCol(37,120);
			cout << "                        ";
			gotoRowCol(38,120);
			cout << "                        ";
			gotoRowCol(39,120);
			cout << "                        ";
			switch (PressedKey)
			{
					case 'q':
						ChessBoard[FinalPosition[0]][FinalPosition[1]]= 'q';
						break;
					case 'b':
						ChessBoard[FinalPosition[0]][FinalPosition[1]]= 'b';
						break;
					case 'n':
						ChessBoard[FinalPosition[0]][FinalPosition[1]]= 'n';
						break;
					case 'r':
						ChessBoard[FinalPosition[0]][FinalPosition[1]]= 'r';
						break;
			}
			}
		}
}

//This function highlights the every possible legal move of the piece that you have selected
void LegalMoveHighlight(char ChessBoard[8][8], char Symbol, int InitialPosition[2], int FinalPosition[2], int Turn, int RowDim, int ColDim)
{
    for(int r=0; r<8; r++)
    {
        for(int c=0; c<8; c++)
        {
            FinalPosition[0]=r;
            FinalPosition[1]=c;
			if(LegalMoves(ChessBoard, InitialPosition, FinalPosition, Turn) && PieceIdentifier(ChessBoard,Turn,InitialPosition)==true)
            {
                if(Turn==2 && ChessBoard[r][c]>='A' && ChessBoard[r][c]<='Z')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    SquarePrinting(Symbol, r, c, RowDim, ColDim);
                }
                else if(Turn==1 && ChessBoard[r][c]>='a' && ChessBoard[r][c]<='z')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    SquarePrinting(Symbol, r, c, RowDim, ColDim);
                }
                else if(ChessBoard[r][c]==' ')
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                    SquarePrinting(Symbol, r, c, RowDim, ColDim);
                }
            }
        }
    }
}

//This fucntion finds the opponents King on the Board
void FindOpponentKing(char ChessBoard[8][8], int DuplicateInitialPosition[2], int DuplicateFinalPosition[2], int Turn)
{
    if(Turn==1)
    {
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<8; col++)
            {
                if(ChessBoard[row][col]=='k')
                {
                    DuplicateFinalPosition[0]=row;
                    DuplicateFinalPosition[1]=col;
                    break;
                }
            }
        }
    }
    else if(Turn==2)
    {
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<8; col++)
            {
                if(ChessBoard[row][col]=='K')
                {
                    DuplicateFinalPosition[0]=row;
                    DuplicateFinalPosition[1]=col;
                    break;
                }
            }
        }
    }
}

//This function checks that if players king is in check or not
bool Check(char ChessBoard[8][8], int DuplicateInitialPosition[2], int DuplicateFinalPosition[2], int Turn)
{
    if(Turn==1)
    {
        FindOpponentKing(ChessBoard, DuplicateInitialPosition, DuplicateFinalPosition, Turn);
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<8; col++)
            {
                if(ChessBoard[row][col]>='A' && ChessBoard[row][col]<='Z')
                {
                    DuplicateInitialPosition[0]=row;
                    DuplicateInitialPosition[1]=col;
                    if(LegalMoves(ChessBoard, DuplicateInitialPosition, DuplicateFinalPosition, Turn))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    else if(Turn==2)
    {
        FindOpponentKing(ChessBoard, DuplicateInitialPosition, DuplicateFinalPosition, Turn);
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<8; col++)
            {
                if(ChessBoard[row][col]>='a' && ChessBoard[row][col]<='z')
                {
                    DuplicateInitialPosition[0]=row;
                    DuplicateInitialPosition[1]=col;
                    if(LegalMoves(ChessBoard, DuplicateInitialPosition, DuplicateFinalPosition, Turn))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

//This function is use to check if a king is coming in a check position by his or its teamates moves or not
bool SelfCheck(char ChessBoard[8][8], int InitialPosition[2], int FinalPosition[2], int Turn)
{
    if(Turn==1)
    {
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<8; col++)
            {
                if(ChessBoard[row][col]=='K')
                {
                    FinalPosition[0]=row;
                    FinalPosition[1]=col;
                }
            }
        }
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<8; col++)
            {
                if(ChessBoard[row][col]>='a' && ChessBoard[row][col]<='z')
                {
                    InitialPosition[0]=row;
                    InitialPosition[1]=col;
                    if(LegalMoves(ChessBoard, InitialPosition, FinalPosition, 2))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    if(Turn==2)
    {
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<8; col++)
            {
                if(ChessBoard[row][col]=='k')
                {
                    FinalPosition[0]=row;
                    FinalPosition[1]=col;
                }
            }
        }
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<8; col++)
            {
                if(ChessBoard[row][col]>='A' && ChessBoard[row][col]<='Z')
                {
                    InitialPosition[0]=row;
                    InitialPosition[1]=col;
                    if(LegalMoves(ChessBoard, InitialPosition, FinalPosition, Turn))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

//This function is creating game save file
void GameSave(char ChessBoard[8][8], int &Turn)
{
	char Board;

	ofstream write;
	write.open("D:\\SaveFile.txt");
	write << Turn << endl;

	for(int row=0; row<8; row++)
	{
		for(int col=0; col<8; col++)
		{
			if(ChessBoard[row][col]==' ')
			{
				write << '-';

			}
			else
			{
				write << ChessBoard[row][col];
			}
		}
		write << endl;
	}
	write.close();
}

//This function is loading games save file
void GameLoad(char ChessBoard[8][8], int &Turn)
{
	ifstream read;
	read.open("D:\\SaveFile.txt");
	read>>Turn;
	for(int row=0; row<8; row++)
	{
		for(int col=0; col<8; col++)
		{
			read >> ChessBoard[row][col];
			if(ChessBoard[row][col]=='-')
			{
				ChessBoard[row][col]=' ';
			}
			else
			{
				ChessBoard[row][col];
			}
		}
	}

}
