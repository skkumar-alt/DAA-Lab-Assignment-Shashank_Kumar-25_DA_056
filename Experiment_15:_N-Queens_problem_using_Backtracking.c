//Shashank Kumar
//25/DA/056

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isSafe(int **board, int row, int col, int n) {
    int i, j;
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
    for (i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j])
            return false;
    return true;
}

bool solveNQUtil(int **board, int col, int n) {
    if (col >= n)
        return true;
    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            board[i][col] = 1;
            if (solveNQUtil(board, col + 1, n))
                return true;
            board[i][col] = 0;
        }
    }
    return false;
}

void printSolution(int **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j])
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the number of queens (N): ");
    scanf("%d", &n);

    int **board = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        board[i] = (int *)calloc(n, sizeof(int));
    }

    if (solveNQUtil(board, 0, n) == false) {
        printf("Solution does not exist\n");
    } else {
        printf("\nSolution:\n");
        printSolution(board, n);
    }

    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    return 0;
}
