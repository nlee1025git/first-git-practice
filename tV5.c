#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define bingo 2
#define size 3
#define eachNumLines 8

int player;
int numPick;
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
    int index = 1;
    for (int i = 0; i < size; i++) {
        // printf(" ");
        for (int j = 0; j < size; j++) {
            printf("%2d ", index++);
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
    for (int i = 0; i < bingo; i++)
}
