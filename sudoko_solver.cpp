#include <iostream>
using namespace std;

class Sudoku {
public:
    static bool isSafe(int sudoku[][9], int row, int col, int digit) {
        // for column
        for (int i = 0; i < 9; i++) {
            if (sudoku[i][col] == digit) {
                return false;
            }
        }
        // for row
        for (int j = 0; j < 9; j++) {
            if (sudoku[row][j] == digit) {
                return false;
            }
        }
        // for grid
        int sr = (row / 3) * 3;
        int sc = (col / 3) * 3;
        for (int i = sr; i < sr + 3; i++) {
            for (int j = sc; j < sc + 3; j++) {
                if (sudoku[i][j] == digit) {
                    return false;
                }
            }
        }
        return true;
    }

    static bool sudokuSolver(int sudoku[][9], int row, int col) {
        // base case
        if (row == 9 && col == 0) {
            return true;
        }

        // recursion
        int nxtrow = row;
        int nxtcol = col + 1;
        if (col + 1 == 9) {
            nxtrow = row + 1;
            nxtcol = 0;
        }

        if (sudoku[row][col] != 0) {
            return sudokuSolver(sudoku, nxtrow, nxtcol);
        }

        for (int digit = 1; digit <= 9; digit++) {
            if (isSafe(sudoku, row, col, digit)) {
                sudoku[row][col] = digit;
                if (sudokuSolver(sudoku, nxtrow, nxtcol)) {
                    return true;
                }
                sudoku[row][col] = 0;
            }
        }

        return false;
    }

    static void printSudoku(int sudoku[][9]) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << sudoku[i][j] << " ";
            }
            cout << endl;
        }
    }

    static void inputSudoku(int sudoku[][9]) {
        cout << "Enter the Sudoku grid (9x9). Use 0 for empty cells. Enter each row, space-separated:\n";
        for (int i = 0; i < 9; i++) {
            cout << "Row " << i + 1 << ": ";
            for (int j = 0; j < 9; j++) {
                int value;
                cin >> value;
                // Input validation
                if (value < 0 || value > 9) {
                    cout << "Invalid input! Values must be between 0 and 9. Try again.\n";
                    j--; // Retry the same cell
                    continue;
                }
                sudoku[i][j] = value;
            }
        }
    }
};

int main() {
    int sudoku[9][9];
    Sudoku::inputSudoku(sudoku);
    cout << "\nInput Sudoku:\n";
    Sudoku::printSudoku(sudoku);
    
    if (Sudoku::sudokuSolver(sudoku, 0, 0)) {
        cout << "\nSolution Exists:\n";
        Sudoku::printSudoku(sudoku);
    } else {
        cout << "\nSolution Does not Exist" << endl;
    }
    return 0;
}
