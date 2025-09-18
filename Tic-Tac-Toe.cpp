#include<bits/stdc++.h> 
using namespace std; 

#define COMPUTER 1 
#define HUMAN 2 


#define COMPUTERMOVE 'O' //computer moves with 'O'
#define HUMANMOVE 'X' 	//human moves with 'X'

void showBoard(char board[][3]) 
{ 
	cout << "\t\t\t " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n"; 
	cout << "\t\t\t-----------\n"; 
	cout << "\t\t\t " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n"; 
	cout << "\t\t\t-----------\n"; 
	cout << "\t\t\t " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n\n";  
} 


void showInstructions() 
{ 
	cout << "\nChoose a cell numbered from 1 to 9 as below and play\n\n"; 
	
	cout << "\t\t\t 1 | 2 | 3 \n"; 
	cout << "\t\t\t-----------\n"; 
	cout << "\t\t\t 4 | 5 | 6 \n"; 
	cout << "\t\t\t-----------\n"; 
	cout << "\t\t\t 7 | 8 | 9 \n\n"; 
} 



void initialise(char board[][3]) 
{	
	// Initially the board is empty 
	for (int i=0; i<3; i++) 
	{ 
		for (int j=0; j<3; j++) 
			board[i][j] = ' '; 
	} 
} 


void declareWinner(int whoseTurn) 
{ 
	if (whoseTurn == COMPUTER) 
		cout << "COMPUTER has won\n"; 
	else
		cout << "HUMAN has won\n"; 
} 

bool rowCrossed(char board[][3]) 
{ 
	for (int i=0; i<3; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 


bool columnCrossed(char board[][3]) 
{ 
	for (int i=0; i<3; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 


bool diagonalCrossed(char board[][3]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') 
		return(true); 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		return(true); 

	return(false); 
} 

bool gameOver(char board[][3]) 
{ 
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) ); 
}

int minimax(char board[][3], int depth, bool isAI, int alpha, int beta)
{
    int score = 0;
    if (gameOver(board) == true)
    {
        if (isAI == true)
            return -1;
        else 
            return +1;
    }
    else
    {
        if(depth < 9)
        {
            if(isAI == true)
            {
                int bestScore = -999;
                for(int i=0; i<3; i++)
                {
                    for(int j=0; j<3; j++)
                    {
                        if (board[i][j] == ' ')
                        {
                            board[i][j] = COMPUTERMOVE;
                            score = minimax(board, depth + 1, false, alpha, beta);
                            board[i][j] = ' ';
                            bestScore = max(bestScore, score);
                            alpha = max(alpha, bestScore);
                            if (beta <= alpha)
                                return bestScore;
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                int bestScore = 999;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (board[i][j] == ' ')
                        {
                            board[i][j] = HUMANMOVE;
                            score = minimax(board, depth + 1, true, alpha, beta);
                            board[i][j] = ' ';
                            bestScore = min(bestScore, score);
                            beta = min(beta, bestScore);
                            if (beta <= alpha)
                                return bestScore;
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
}


int bestMove(char board[][3], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex+1, false, -999, 999);
                board[i][j] = ' ';
                if(score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x*3+y;
}



void playTicTacToe(int whoseTurn) 
{ 
	char board[3][3]; 
	int moveIndex = 0, x = 0, y = 0;

	initialise(board);
	showInstructions(); 
	
	while (gameOver(board) == false && moveIndex != 3*3) 
	{ 
		int n;
		if (whoseTurn == COMPUTER) 
		{
			n = bestMove(board, moveIndex);
			x = n / 3;
			y = n % 3;
			board[x][y] = COMPUTERMOVE; 
			cout << "COMPUTER has put a " << COMPUTERMOVE << " in cell " << n+1 << "\n\n";
			showBoard(board);
			moveIndex ++; 
			whoseTurn = HUMAN;
		} 
		
		else if (whoseTurn == HUMAN) 
		{
			cout << "You can insert in the following positions : ";
			for(int i=0; i<3; i++)
				for (int j = 0; j < 3; j++)
					if (board[i][j] == ' ')
						cout << (i * 3 + j) + 1 << " ";
			cout << "\n\nEnter the position = ";
			cin >> n;
			n--;
			x = n / 3;
			y = n % 3; 
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
				board[x][y] = HUMANMOVE; 
				cout << "\nHUMAN has put a " << HUMANMOVE << " in cell " << n+1 << "\n\n"; 
				showBoard(board); 
				moveIndex ++; 
				whoseTurn = COMPUTER;
			}
			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
				cout << "\nPosition is occupied, select any one place from the available places\n\n";
			}
			else if(n<0 || n>8)
			{
				cout << "Invalid position\n";
			}
		} 
	} 

	if (gameOver(board) == false && moveIndex == 3 * 3) 
		cout << "It's a draw\n"; 
	else
	{ 
		if (whoseTurn == COMPUTER) 
			whoseTurn = HUMAN; 
		else if (whoseTurn == HUMAN) 
			whoseTurn = COMPUTER; 
		
		declareWinner(whoseTurn); 
	} 
} 

int main() 
{ 
	cout << "\n-------------------------------------------------------------------\n\n";
	cout << "\t\t\t Tic-Tac-Toe\n"; 
	cout << "\n-------------------------------------------------------------------\n\n";
	char cont='y';
	do {
		char choice;
	 	cout << "Do you want to start first?(y/n) : ";
	 	cin >> choice;

		if(choice=='n')
			playTicTacToe(COMPUTER);
		else if(choice=='y')
			playTicTacToe(HUMAN);
		else
			cout << "Invalid choice\n"; 
        
		cout << "\nDo you want to quit(y/n) : ";
       		cin >> cont;
	} while(cont=='n');
	return (0); 
}
