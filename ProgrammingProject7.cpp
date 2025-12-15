#include <iostream>
using namespace std;

const int SIZE = 3;

// Board state constants
enum BoardState { PLAY, TIE, X_WIN, O_WIN };

// Check result constants
enum CheckResult { SPACE_LEFT, NO_SPACE, WINNER };

// Function prototypes
void initializeBoard(char board[][SIZE], int rows, int cols);
void displayBoard(const char board[][SIZE], int rows, int cols);
void placeToken(char token, char board[][SIZE], int rows, int cols);
void getLocation(int& row, int& col, const char board[][SIZE], int rows, int cols);
BoardState getBoardState(char token, const char board[][SIZE], int rows, int cols);
CheckResult checkForWinner(char token, const char board[][SIZE], int rows, int cols);

int main()
{
    char board[SIZE][SIZE];
    const char player1_token = 'X';
    const char player2_token = 'O';

    BoardState boardState = PLAY;

    // Initialize and display the empty board
    initializeBoard(board, SIZE, SIZE);
    displayBoard(board, SIZE, SIZE);

    // Main game loop
    while (boardState == PLAY)
    {
        // Player 1 turn
        cout << "Player 1 (" << player1_token << ") turn.\n";
        placeToken(player1_token, board, SIZE, SIZE);
        displayBoard(board, SIZE, SIZE);
        boardState = getBoardState(player1_token, board, SIZE, SIZE);

        if (boardState != PLAY)
        {
            break; // X either wins or the game is a tie
        }

        // Player 2 turn
        cout << "Player 2 (" << player2_token << ") turn.\n";
        placeToken(player2_token, board, SIZE, SIZE);
        displayBoard(board, SIZE, SIZE);
        boardState = getBoardState(player2_token, board, SIZE, SIZE);
    }

    // Final result
    if (boardState == X_WIN)
    {
        cout << "Player 1 (X) wins!\n";
    }
    else if (boardState == O_WIN)
    {
        cout << "Player 2 (O) wins!\n";
    }
    else if (boardState == TIE)
    {
        cout << "The game is a tie. No more spaces left and no winner.\n";
    }

    return 0;
}

// initializeBoard()
// Input: empty 3x3 array
// Output: all locations set to '*'
void initializeBoard(char board[][SIZE], int rows, int cols)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            board[r][c] = '*';
        }
    }
}

// displayBoard()
// Input: 3x3 board
// Postcondition: row/column numbers and cell contents displayed
void displayBoard(const char board[][SIZE], int rows, int cols)
{
    cout << "\n    1   2   3\n";
    cout << "  -------------\n";

    for (int r = 0; r < rows; r++)
    {
        cout << " " << (r + 1) << " | ";
        for (int c = 0; c < cols; c++)
        {
            cout << board[r][c];
            if (c < cols - 1)
                cout << " | ";
        }
        cout << " |\n";
        cout << "  -------------\n";
    }
    cout << endl;
}

// placeToken()
// Input: token (X or O) and board
// Uses getLocation() to get a valid row/col and places token there
void placeToken(char token, char board[][SIZE], int rows, int cols)
{
    int row, col;
    getLocation(row, col, board, rows, cols);  // row, col will be 0-based
    board[row][col] = token;
}

// getLocation()
// Input: references to row & col and board
// Gets, validates row/col (1–3), ensures cell has '*', then returns 0-based row/col
void getLocation(int& row, int& col, const char board[][SIZE], int rows, int cols)
{
    while (true)
    {
        int userRow, userCol;

        // Get row with validation
        do
        {
            cout << "Enter row (1-3): ";
            cin >> userRow;

            if (userRow < 1 || userRow > 3)
            {
                cout << "Invalid row. Please enter a value between 1 and 3.\n";
            }
        } while (userRow < 1 || userRow > 3);

        // Get column with validation
        do
        {
            cout << "Enter column (1-3): ";
            cin >> userCol;

            if (userCol < 1 || userCol > 3)
            {
                cout << "Invalid column. Please enter a value between 1 and 3.\n";
            }
        } while (userCol < 1 || userCol > 3);

        // Convert to 0-based indices
        int rIndex = userRow - 1;
        int cIndex = userCol - 1;

        // Verify the location is available
        if (board[rIndex][cIndex] == '*')
        {
            row = rIndex;
            col = cIndex;
            break;  // valid and available location found
        }
        else
        {
            cout << "That location is already taken. Please choose another.\n";
        }
    }
}

// getBoardState()
// Input: token to check and the board
// Output: PLAY, TIE, X_WIN, or O_WIN
BoardState getBoardState(char token, const char board[][SIZE], int rows, int cols)
{
    CheckResult result = checkForWinner(token, board, rows, cols);

    if (result == WINNER)
    {
        if (token == 'X')
            return X_WIN;
        else
            return O_WIN;
    }
    else if (result == SPACE_LEFT)
    {
        return PLAY;
    }
    else // NO_SPACE
    {
        return TIE;
    }
}

// checkForWinner()
// Input: token (X or O) and board
// Checks rows, columns, diagonals for a winner
// Then checks if any spaces ('*') are left
// Output: WINNER, SPACE_LEFT, or NO_SPACE
CheckResult checkForWinner(char token, const char board[][SIZE], int rows, int cols)
{
    // Check rows
    for (int r = 0; r < rows; r++)
    {
        if (board[r][0] == token &&
            board[r][1] == token &&
            board[r][2] == token)
        {
            return WINNER;
        }
    }

    // Check columns
    for (int c = 0; c < cols; c++)
    {
        if (board[0][c] == token &&
            board[1][c] == token &&
            board[2][c] == token)
        {
            return WINNER;
        }
    }

    // Check diagonals
    if (board[0][0] == token &&
        board[1][1] == token &&
        board[2][2] == token)
    {
        return WINNER;
    }

    if (board[0][2] == token &&
        board[1][1] == token &&
        board[2][0] == token)
    {
        return WINNER;
    }

    // No winner; check for any remaining spaces
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (board[r][c] == '*')
            {
                return SPACE_LEFT;  // no winner, moves still available
            }
        }
    }

    // No winner and no spaces left
    return NO_SPACE;
}
