// Algorithm to find positions of 8 bishops on a chess board to cover all of it
// 8x8 chess board [rows][columns]
// Solved case will be saved in file as matrix (1 - occupied square by bishop)
//-------------------------------------------------
// Marking explanation:
// 0 - Not occupied/threathened square
// 1 - Threathened square
// 2 - Occupied square

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Defining board size (N stands for rows and collumns)
#define N 8
#define numberOfRooks 8

int board[N][N] = {0};
FILE *solutions;
int solutionsFound = 0;
long currentPositionInFile = 0;
FILE *results;

bool checkSolution();
void cover(int, int);
bool solve(int, int);
void openFile();
void saveSolution();
void saveFinalSolution();
void getSolution();
void printFinalSolutions();
void invertSolution();

int main(){
    openFile();
    solve(0,0);
    printFinalSolutions();
    fclose(solutions);
    fclose(results);
    return 0;
}

// Function to check wheter solution is correct
bool checkSolution(){
    for (int i = 0; i < N * N / 2; i++) {
        int row = i / (N / 2);
        int col = 2 * (i % (N / 2)) + row % 2;
        if(board[row][col] == 0)
            return false;
    }
    return true;
}

// Function to fill controlled squares by bishop
void cover(int row, int col){
    board[row][col] = 2;
    for(int i = 1; i < N; ++i){
        //Filling diagonal to NW
        if(row - i >= 0 && col - i >= 0 && board[row - i][col - i] != 2)
            board[row - i][col - i] = 1;
        //Filling diagonal to SW
        if(row + i < N && col - i >= 0 && board[row + i][col - i] != 2)
            board[row + i][col - i] = 1;
        //Filling diagonal to SE
        if(row + i < N && col + i < N && board[row + i][col + i] != 2)
            board[row + i][col + i] = 1;
        //Filling diagonal to NE
        if(row - i >= 0 && col + i < N && board[row - i][col + i] != 2)
            board[row - i][col + i] = 1;
    }
}

// Function to generate solutions
bool solve(int current, int placed){
    int tempBoard[N][N] = {0};
    if(placed == numberOfRooks / 2){
        if(checkSolution()){
            saveSolution();
            return true;
        }
        return false;
    }
    for(int i = current; i < N * N / 2; ++i){
        int row = i / (N / 2);
        int col = 2 * (i % (N / 2)) + row % 2;
        for(int rowT = 0; rowT < N; ++rowT)
            for(int colT = 0; colT < N; ++colT)
                tempBoard[rowT][colT] = board[rowT][colT];
        cover(row, col);
        solve(i + 1, placed + 1);
        for(int rowT = 0; rowT < N; ++rowT)
            for(int colT = 0; colT < N; ++colT)
                board[rowT][colT] = tempBoard[rowT][colT];
    }
    return false;
}

// Function to open file
void openFile(){
    solutions = fopen("solutions.txt", "w+");
    results = fopen("results.txt", "w+");
    if(solutions == NULL || results == NULL){
        exit(1);
    }
}

// Function to save produced sollution to file
void saveSolution(){
    solutionsFound++;
    for(int row = 0; row < N; ++row){
        for(int col = 0; col < N; ++col){
            fprintf(solutions, "%d ", board[row][col]);
        }
        fprintf(solutions, "\n");
    }
    fprintf(solutions, "\n");
}

// Function to save produced final sollution to file
void saveFinalSolution(){
    for(int row = 0; row < N; ++row){
        for(int col = 0; col < N; ++col){
            if(board[row][col] == 2 || board[row][col] == 1){
                fprintf(results, "%d ", 1);
            }else{
                fprintf(results, "%d ", board[row][col]);
            }
        }
        fprintf(results, "\n");
    }
    fprintf(results, "\n");
}

// Function to get solution from the file
void getSolution(){
    for(int row = 0; row < N; ++row){
        for(int col = 0; col < N; ++col){
            int value;
            fscanf(solutions, "%1d", &value);
            if(value == 2){
                board[row][col] = 2;
            }
        }
    }
}

//Function to invert the matrix by X axis
void invertSolution(){
    for(int row = 0; row < N; ++row){
        for(int col = 0; col < N; ++col){
            if(board[row][col] == 2){
                board[N - row - 1][col] = 1;
            }
        }
    }
    for(int row = 0; row < N; ++row){
        for(int col = 0; col < N; ++col){
            if(board[row][col] == 2){
                board[row][col] = 0;
            }
        }
    }
}

//Function to print all possible combinations
void printFinalSolutions(){
    for(int i = 0; i < solutionsFound; ++i){
        fseek(solutions, currentPositionInFile, SEEK_SET);
        getSolution();
        invertSolution();
        currentPositionInFile = ftell(solutions);
        rewind(solutions);

        int tempBoard[N][N] = {0};

        for(int row = 0; row < N; ++row)
            for(int col = 0; col < N; ++col)
                tempBoard[row][col] = board[row][col];

        for(int j = 0; j < solutionsFound; j++){
            getSolution();
            saveFinalSolution();

            for(int row = 0; row < N; ++row)
                for(int col = 0; col < N; ++col)
                    board[row][col] = tempBoard[row][col];
        }

        for(int row = 0; row < N; ++row)
            for(int col = 0; col < N; ++col)
                board[row][col] = 0;
    }
}