#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define bingo 3
#define size 5
#define boarderSize bingo - 1
#define LSIZE(size, borderSize) (size + borderSize + borderSize) // multiplication is not allowed
#define eachNumLines 8

int player;
int numPick;
int initArray[size + boarderSize * 2][size + boarderSize * 2] = {0};
int lineNumbers[size * size][eachNumLines][bingo] = {0};

void initData();
void setBoard();
void printBoard();
int addNums(int numPick);

int main() {
    int count = 0;
    srand(time(0));
    initData();
    // setBoard();
    printBoard();

    while (1) {
        printf("pick a num: ");
        scanf("%d", &numPick);
        
        count++;
        if (count == size * size) {
            printf("draw game\n");
            break;
        }
    }
    return 0;
}

void initData() {
    printf("\n");
    for (int i = 0; i < size + boarderSize * 2; i++) {
        for (int j = 0; j < size + boarderSize * 2; j++) {
            initArray[i][j] = -5;
            printf("%2d ", initArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int Idx = 0;
    int initValue = 0;

    for (int i = 0; i < LSIZE(size, boarderSize); i++) {        
        for (int j = 0; j < LSIZE(size, boarderSize); j++) {
            initValue = -2;
            if (j < boarderSize) {
                initValue = -1 * (boarderSize - j);
                printf("%2d ", -1 * (boarderSize - j));
            } else if (j >= boarderSize && j < size + boarderSize) {
                if (i < boarderSize) {
                    initValue = -1 * (boarderSize - i);
                    printf("%2d ", -1 * (boarderSize - i));
                } else if (i >= size + boarderSize) {
                    // printf("i is %d\n", i);
                    initValue = (-1 * (size + 2 * boarderSize - i - 1) + boarderSize + 1) * -1;
                    printf("%2d ", (-1 * (size + 2 * boarderSize - i - 1) + boarderSize + 1) * -1);
                } else {
                    initValue = ++Idx;
                    printf("%2d ", ++Idx);
                }
            } else {
            // } else if (j >= size + boarderSize && j < size + boarderSize * 2 - j) {
                initValue = size + boarderSize * 2 - j;
                printf("%2d ", size + boarderSize * 2 - j);
            }
            initArray[i][j] = initValue;
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < size + boarderSize * 2; i++) {
        for (int j = 0; j < size + boarderSize * 2; j++) {
            initArray[i][j] = -5;
            printf("%2d ", initArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("1. user    2. computer: ");
    scanf("%d", &player);
}

void setBoard() {
    int seq = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < eachNumLines; k++) {
                lineNumbers[i][j][k] = seq++;
            }
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < size * size; i++) {
        printf("\n   board %d\n", i + 1);
        for (int j = 0; j < eachNumLines; j++) {
            printf("line %d: ", j + 1);
            for (int k = 0; k < bingo; k++) {
                printf("%2d ", lineNumbers[i][j][k]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

int addNums(int numPick) {
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < eachNumLines; j++) {
            for (int k = 0; k < bingo; k++) {
                if (numPick == 1) {
                    lineNumbers[i][j][k] = numPick;
                }
            }
        }
    }
    return 1;
}

void north() {
    for (int i = 0; i < bingo; i++) {
        
    }
}
