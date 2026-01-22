#include <bits/stdc++.h>
using namespace std;

class SudokuGame {
private:
    static const int N;
    static const int UNASSIGNED;

    vector<vector<int>> board;
    vector<vector<int>> solution;

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    bool isValidInput(int row, int col, int num) {
        return (row >= 1 && row <= 9 &&
                col >= 1 && col <= 9 &&
                num >= 1 && num <= 9);
    }

    bool isModifiableCell(int row, int col) {
        return board[row][col] == UNASSIGNED;
    }

    bool isSafe(const vector<vector<int>>& board, int row, int col, int num) {
        // Check row
        for (int x = 0; x < N; x++) {
            if (board[row][x] == num) return false;
        }

        // Check column
        for (int x = 0; x < N; x++) {
            if (board[x][col] == num) return false;
        }

        // Check 3x3 sub-grid
        int startRow = row - row % 3;
        int startCol = col - col % 3;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[startRow + i][startCol + j] == num) {
                    return false;
                }
            }
        }
        return true;
    }

    void printBoard(const vector<vector<int>>& board) {
        clearScreen();

        cout << "\n     1 2 3   4 5 6   7 8 9\n";
        cout << "   ╔═══════╦═══════╦═══════╗\n";

        for (int row = 0; row < N; row++) {
            cout << " " << row + 1 << " ║ ";
            for (int col = 0; col < N; col++) {
                if (board[row][col] == UNASSIGNED)
                    cout << ". ";
                else
                    cout << board[row][col] << " ";

                if ((col + 1) % 3 == 0 && col < 8)
                    cout << "║ ";
            }
            cout << "║\n";

            if ((row + 1) % 3 == 0 && row < 8) {
                cout << "   ╠═══════╬═══════╬═══════╣\n";
            }
        }
        cout << "   ╚═══════╩═══════╩═══════╝\n\n";
    }

    void printBoardAndCommands() {
        printBoard(board);
        cout << "\nCommands:\n";
        cout << "- Enter move (row col number): e.g., 3 4 5\n";
        cout << "- hint  : Get a hint\n";
        cout << "- solve : Show solution\n";
        cout << "- new   : Start new game\n";
        cout << "- quit  : Exit game\n";
        cout << "\nEnter command: ";
    }

    // -------- BACKTRACKING SOLVER --------
    bool solveSudoku(vector<vector<int>>& board) {
        int row = -1, col = -1;
        bool emptyCell = false;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == UNASSIGNED) {
                    row = i;
                    col = j;
                    emptyCell = true;
                    goto found;
                }
            }
        }
    found:

        if (!emptyCell)
            return true;

        for (int num = 1; num <= N; num++) {
            if (isSafe(board, row, col, num)) {
                board[row][col] = num;

                if (solveSudoku(board))
                    return true;

                // BACKTRACK
                board[row][col] = UNASSIGNED;
            }
        }
        return false;
    }

    void generatePuzzle() {
        board.assign(N, vector<int>(N, UNASSIGNED));

        // Fill diagonal 3x3 boxes
        for (int box = 0; box < N; box += 3) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int num;
                    do {
                        num = rand() % 9 + 1;
                    } while (!isSafe(board, box + i, box + j, num));
                    board[box + i][box + j] = num;
                }
            }
        }

        // Complete board
        solveSudoku(board);
        solution = board;

        // Remove cells
        int cellsToRemove = 40 + (rand() % 21);
        while (cellsToRemove > 0) {
            int row = rand() % N;
            int col = rand() % N;
            if (board[row][col] != UNASSIGNED) {
                board[row][col] = UNASSIGNED;
                cellsToRemove--;
            }
        }
    }

    bool checkSolution() {
        return board == solution;
    }

    int getHint(int row, int col) {
        return solution[row][col];
    }

public:
    SudokuGame() {
        srand(time(0));
    }

    void play() {
        string input;
        generatePuzzle();

        while (true) {
            printBoardAndCommands();
            getline(cin >> ws, input);

            if (input == "quit") {
                break;
            } 
            else if (input == "new") {
                generatePuzzle();
                continue;
            } 
            else if (input == "solve") {
                board = solution;
                printBoard(board);
                cout << "\nPuzzle solved! Press Enter...";
                cin.get();
                generatePuzzle();
                continue;
            } 
            else if (input == "hint") {
                int row, col;
                cout << "Enter position (row col): ";
                cin >> row >> col;

                if (isValidInput(row, col, 1)) {
                    cout << "Hint: " << getHint(row - 1, col - 1) << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
                continue;
            }

            istringstream iss(input);
            int row, col, num;
            if (iss >> row >> col >> num) {
                if (!isValidInput(row, col, num)) {
                    cout << "Invalid input!\n";
                    continue;
                }

                row--; col--;

                if (!isModifiableCell(row, col)) {
                    cout << "Cell cannot be modified!\n";
                    continue;
                }

                if (!isSafe(board, row, col, num)) {
                    cout << "Invalid move!\n";
                    continue;
                }

                board[row][col] = num;

                if (checkSolution()) {
                    printBoard(board);
                    cout << "\nCongratulations! You solved it!\n";
                    cin.get();
                    generatePuzzle();
                }
            } 
            else {
                cout << "Invalid command!\n";
            }
        }
    }
};

const int SudokuGame::N = 9;
const int SudokuGame::UNASSIGNED = 0;

int main() {
    cout << "Welcome to Sudoku!\n\n";
    SudokuGame game;
    game.play();
    return 0;
}
