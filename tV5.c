#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define bingo 3
#define size 5
#define boarderSize (bingo - 1)
#define LongSize size + boarderSize * 2
#define adjacentLines 8

int player;
int numPick;
int playCount = 0;
int numSeq = 0;
int fillNum[size * size];
int initArray[LongSize][LongSize];
int lineNumbers[size * size][adjacentLines][bingo];
int defaultLineNumbers[size * size][adjacentLines][bingo];
int adjacentNumbers[size * size];

void initData();
void printBoard();
void setDefaultLineNumbers();
void updateBoard();
void switchPlayer();
void setNum();
int getBestAdjacentNumber();

int main() {
    srand(time(0));
    initData();
    setDefaultLineNumbers();

    while (1) {
        setNum();
        updateBoard();
        switchPlayer();
        
        playCount++;
        if (playCount == size * size) {
            printf("draw game\n");
            break;
        }
    }
    return 0;
}

void initData() {
    int index = 1;
    for (int i = 0; i < LongSize; i++) {        
        for (int j = 0; j < LongSize; j++) {
            // left boarder line
            if (j < boarderSize) {
                initArray[i][j] = j - boarderSize;
            // middle boarder line
            } else if (j >= boarderSize && j < size + boarderSize) {
                if (i < boarderSize) {
                    initArray[i][j] = i - boarderSize;
                } else if (i >= size + boarderSize) {
                    initArray[i][j] = boarderSize + size - i - 1;
                } else {
                    initArray[i][j] = index++;
                }
            // right borader line
            } else {
                initArray[i][j] = (size - 1) + boarderSize - j;
            }
        }
    }

    for (int i = 0; i < LongSize; i++) {
        for (int j = 0; j < LongSize; j++) {
            printf("%2d ", initArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("1. user    2. computer: ");
    scanf("%d", &player);
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < size * size; i++) {
        printf("\n   board %d\n", i + 1);
        for (int j = 0; j < adjacentLines; j++) {
            printf("line %d: ", j + 1);
            for (int k = 0; k < bingo; k++) {
                printf("%2d ", defaultLineNumbers[i][j][k]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

void setDefaultLineNumbers() {
    int count = 0;
    int x = boarderSize;
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < adjacentLines; j++) {
            int y = boarderSize + i % size;
            for (int k = 0; k < bingo; k++) {
                if (k == 0) {
                    defaultLineNumbers[i][j][k] = i + 1;
                } else {
                    if (j == 0) {
                        defaultLineNumbers[i][j][k] = initArray[x][++y];
                    } else if (j == 1) {
                        defaultLineNumbers[i][j][k] = initArray[++x][++y];                    
                    } else if (j == 2) {
                        defaultLineNumbers[i][j][k] = initArray[++x][y];                    
                    } else if (j == 3) {
                        defaultLineNumbers[i][j][k] = initArray[++x][--y];                    
                    } else if (j == 4) {
                        defaultLineNumbers[i][j][k] = initArray[x][--y];                    
                    } else if (j == 5) {
                        defaultLineNumbers[i][j][k] = initArray[--x][--y];                    
                    } else if (j == 6) {
                        defaultLineNumbers[i][j][k] = initArray[--x][y];                    
                    } else {
                        defaultLineNumbers[i][j][k] = initArray[--x][++y];
                    }
                }
            }
            x = boarderSize + i / size;
        }
        count++;
        if (count % size == 0) {
            x++;
        }
    }
}

void updateBoard() {
    int index = 1;
    for (int i = 0; i < size * size; i++) {
        if (fillNum[i] == 1) {
            if (numPick - 1 == i) {
                printf("%3s ", "'O'");
            } else {
                printf("%3s ", "o");
            }
        } else if (fillNum[i] == -1) {
            if (numPick - 1 == i) {
                printf("%3s ", "'X'");
            } else {
                printf("%3s ", "x");
            }
        } else {
            printf("%3d ", index);
        }
        index++;
        if ((i + 1) % size == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void switchPlayer() {
    if (player == 1) {
        player = 2;
    } else {
        player = 1;
    }
}

void setNum() {
    if (player == 1) {
        printf("enter a num: ");
        scanf("%d", &numPick);
        if (fillNum[numPick - 1] == 0) {
            fillNum[numPick - 1] = 1;
        } else {
            do {
                printf("enter a different num: ");
                scanf("%d", &numPick);
            } while (fillNum[numPick - 1] == 1 || fillNum[numPick - 1] == -1);
            fillNum[numPick - 1] = 1;
        }
        printf("user picks %d\n", numPick);
    } else {
        numPick = getBestAdjacentNumber();
        fillNum[numPick - 1] = -1;
        printf("computer picks %d\n", numPick);
    }
}

int getBestAdjacentNumber() {
    int x;
    int y;
    // find the coordinate of numPick
    for (int i = 0; i < LongSize; i++) {
        for (int j = 0; j < LongSize; j++) {
            if (initArray[i][j] == numPick) {
                x = i;
                y = j;
            }
        }
    }

    // insert adjacent numbers into the adjacentNumbers array
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            bool duplicate = false;
            if (initArray[i][j] != numPick && initArray[i][j] > 0) {
                for (int k = 0; k < numSeq; k++) {
                    if (initArray[i][j] == adjacentNumbers[k]) {
                        duplicate = true;
                    }
                }
                if (duplicate == false) {
                    adjacentNumbers[numSeq++] = initArray[i][j];
                }
            }
        }
    }
    printf("nearest numbers: ");
    for (int i = 0; i < numSeq; i++) {
        printf("%d ", adjacentNumbers[i]);
    }
    printf("\n");

    int nextNumIndex = rand() % numSeq;
    printf("rand is %d\n", nextNumIndex);
    return adjacentNumbers[nextNumIndex];
}
