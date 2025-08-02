#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int boardSize = 3;  // Default board size
char** board;       // Dynamic 2D array for board
int playerXScore = 0, playerOScore = 0;

// Function to dynamically create the Tic-Tac-Toe board
void createBoard(int size) {
    board = new char*[size];
    for (int i = 0; i < size; i++) {
        board[i] = new char[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '-';
        }
    }
}

// Function to print the Tic-Tac-Toe board
void printBoard() {
    cout << "\nCurrent Board:\n";
    cout << "  ";
    for (int i = 0; i < boardSize; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < boardSize; i++) {
        cout << i << " ";
        for (int j = 0; j < boardSize; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to reset the board for a new game
void resetBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = '-';
        }
    }
}

// Function to check if the game is won
bool checkWin(char player) {
    // Check rows and columns
    for (int i = 0; i < boardSize; i++) {
        bool rowWin = true, colWin = true;
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] != player) rowWin = false;
            if (board[j][i] != player) colWin = false;
        }
        if (rowWin || colWin) return true;
    }

    // Check diagonals
    bool diag1 = true, diag2 = true;
    for (int i = 0; i < boardSize; i++) {
        if (board[i][i] != player) diag1 = false;
        if (board[i][boardSize - i - 1] != player) diag2 = false;
    }
    return diag1 || diag2;
}

// Function to check if the board is full (draw)
bool checkDraw() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == '-') return false;
        }
    }
    return true;
}

// Function to get valid input from the player
void getPlayerMove(char player) {
    int row, col;
    bool validMove = false;
    while (!validMove) {
        cout << "Player " << player << ", enter your move (row and column): ";
        cin >> row >> col;
        if (row >= 0 && row < boardSize && col >= 0 && col < boardSize && board[row][col] == '-') {
            board[row][col] = player;
            validMove = true;
        } else {
            cout << "Invalid move! Try again.\n";
        }
    }
}

// Simple AI function for the computer to make a move
void getAIMove(char player) {
    srand(time(0)); // Initialize random seed
    int row, col;
    bool validMove = false;
    while (!validMove) {
        row = rand() % boardSize;
        col = rand() % boardSize;
        if (board[row][col] == '-') {
            board[row][col] = player;
            validMove = true;
            cout << "Computer chose: " << row << ", " << col << endl;
        }
    }
}

// Function to display the game menu
void displayMenu() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "1. Play Game (2 Players)\n";
    cout << "2. Play Game (vs Computer)\n";
    cout << "3. Customize Board Size\n";
    cout << "4. View Score\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

// Function to display the score
void displayScore() {
    cout << "\nScore:\n";
    cout << "Player X: " << playerXScore << "\n";
    cout << "Player O: " << playerOScore << "\n";
}

// Main game loop (2 players)
void playGame2Players() {
    resetBoard();
    char currentPlayer = 'X';
    bool gameWon = false, gameDraw = false;

    while (!gameWon && !gameDraw) {
        printBoard();
        getPlayerMove(currentPlayer);

        if (checkWin(currentPlayer)) {
            gameWon = true;
            printBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            if (currentPlayer == 'X') playerXScore++;
            else playerOScore++;
        } else if (checkDraw()) {
            gameDraw = true;
            printBoard();
            cout << "The game is a draw!\n";
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

// Main game loop (vs AI)
void playGameVsAI() {
    resetBoard();
    char currentPlayer = 'X';
    bool gameWon = false, gameDraw = false;

    while (!gameWon && !gameDraw) {
        printBoard();
        if (currentPlayer == 'X') {
            getPlayerMove(currentPlayer);
        } else {
            getAIMove(currentPlayer);
        }

        if (checkWin(currentPlayer)) {
            gameWon = true;
            printBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            if (currentPlayer == 'X') playerXScore++;
            else playerOScore++;
        } else if (checkDraw()) {
            gameDraw = true;
            printBoard();
            cout << "The game is a draw!\n";
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

// Function to customize the board size
void customizeBoardSize() {
    cout << "Enter the board size (3-10): ";
    cin >> boardSize;
    if (boardSize < 3) boardSize = 3;
    if (boardSize > 10) boardSize = 10;
    createBoard(boardSize);
}

// Main function
int main() {
    int choice;
    bool playAgain = true;

    createBoard(boardSize); // Initialize the board with the default size

    while (playAgain) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                playGame2Players();
                break;
            case 2:
                playGameVsAI();
                break;
            case 3:
                customizeBoardSize();
                break;
            case 4:
                displayScore();
                break;
            case 5:
                playAgain = false;
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

        if (choice == 1 || choice == 2) {
            char replay;
            cout << "Do you want to play again? (y/n): ";
            cin >> replay;
            if (replay == 'n' || replay == 'N') {
                playAgain = false;
            }
        }
    }

    // Free dynamically allocated memory for the board
    for (int i = 0; i < boardSize; i++) {
        delete[] board[i];
    }
    delete[] board;

    cout << "Thank you for playing Tic-Tac-Toe!\n";
    return 0;
}
