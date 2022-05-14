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
int fillNum[size * size] = {0};
int initArray[LongSize][LongSize] = {0};
int lineNumbers[size * size][adjacentLines][bingo] = {0};
int defaultLineNumbers[size * size][adjacentLines][bingo] = {0};
int adjacentNumbers[size * size] = {0};

void initData();
void printLineNumberBoard(int arr[size * size][adjacentLines][bingo]);
void setDefaultLineNumbers();
void printUpdatedBoard();
void switchPlayer();
void setNum();
int getBestAdjacentNumber();
void printAdjacentNumbers();
void updateAdjacentNumbers();
void swap(int *a, int *b);
void updateLineNumbers();
void countPlay();
int calculateComputerWeight(int player, int boardNum, int rowNum, int lineNumbers[size * size][adjacentLines][bingo]);

int main() {
    srand(time(0));
    initData();
    setDefaultLineNumbers();
    // printLineNumberBoard(defaultLineNumbers);

    while (1) {
        setNum();
        updateAdjacentNumbers(); // add or remove adjacent numbers
        printAdjacentNumbers();  // print all adjacent numbers
        updateLineNumbers();     // update line numbers with numPick
        // printLineNumberBoard(lineNumbers); // print line numbers
        printUpdatedBoard();     // update 'o' or 'x' drawing
        switchPlayer();
        countPlay();
    }
    return 0;
}

int calculateComputerWeight(int player, int boardNum, int rowNum, int arr[size * size][adjacentLines][bingo]) {
    // player1 = user, player2 = cpu
    // o = user, x = cpu
    int oCount = 0;
    int xCount = 0;
    int nCount = 0;
    int rtnValue = 0;
    for (int i = 0; i < bingo; i++) {
        if (arr[boardNum][rowNum][i] == 1) {
            oCount++;
        } else if (arr[boardNum][rowNum][i] == -1) {
            xCount++;
        } else {
            nCount++;
        }
    }
    
    printf("i: %d, j: %d, o: %d, x: %d, n: %d\n", boardNum + 1, rowNum + 1, oCount, xCount, nCount);
    if (rowNum + 1 == adjacentLines) {
        printf("\n");
    }

    if (player == 1) {
        if (oCount > xCount) {
            rtnValue += oCount * 10;
        } else if (oCount < xCount) {
            rtnValue += xCount * 5;
        } else {
            rtnValue += 1;
        }
    } else {
        if (oCount > xCount) {
            rtnValue += oCount * 5;
        } else if (oCount < xCount) {
            rtnValue += xCount * 10;
        } else {
            rtnValue += 1;
        }
    }
    printf("rtnValue is %d\n", rtnValue);
    return rtnValue;
}

int getBestAdjacentNumber() {
    if (numSeq == 0) {
        if (size % 2 == 1) {
            return (size * size) / 2 + 1;
        } else {
            return (size * size) / 2 + (size / 2);
        }
    }
    int nextNumIndex = rand() % numSeq;
    return adjacentNumbers[nextNumIndex];
}

void updateLineNumbers() {
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < adjacentLines; j++) {
            for (int k = 0; k < bingo; k++) {
                if (defaultLineNumbers[i][j][k] == numPick) {
                    if (player == 1) {
                        lineNumbers[i][j][k] = 1;
                    } else if (player == 2) {
                        lineNumbers[i][j][k] = -1;
                    }
                }
            }
            calculateComputerWeight(player, i, j, lineNumbers);
        }
    }
}

void updateAdjacentNumbers() {
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

    // delete the selected number
    int index = 0;
    int tempArray[size * size] = {0};
    for (int i = 0; i < numSeq; i++) {
        if (fillNum[adjacentNumbers[i] - 1] == 0) {
            tempArray[index] = adjacentNumbers[i];
            index++;
        }
    }
    if (numSeq > 0) {
        numSeq--;
    }
    memcpy(adjacentNumbers, tempArray, sizeof(adjacentNumbers));

    // insert adjacent numbers into the adjacentNumbers array
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            bool duplicate = false;
            if (fillNum[initArray[i][j] - 1] == 0 && initArray[i][j] > 0) {
                bool duplicate = false;
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
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// print all adjacent numbers
void printAdjacentNumbers() {
    for (int i = 0; i < numSeq - 1; i++) {
        for (int j = 0; j < numSeq - i - 1; j++) {
            if (adjacentNumbers[j] > adjacentNumbers[j + 1]) {
                swap(&adjacentNumbers[j], &adjacentNumbers[j + 1]);
            }
        }
    }

    printf("adjacent numbers: ");
    for (int i = 0; i < numSeq; i++) {
        printf("%d ", adjacentNumbers[i]);
    }
    printf("\n\n");
}

void initData() {
    int index = 1;
    for (int i = 0; i < LongSize; i++) {        
        for (int j = 0; j < LongSize; j++) {
            if (i < boarderSize && j < boarderSize) {
                if (i < j) {
                    initArray[i][j] = i - boarderSize;
                } else {
                    initArray[i][j] = j - boarderSize;
                }
            } else if (i < boarderSize && (j >= boarderSize && j < size + boarderSize)) {
                initArray[i][j] = i - boarderSize;
            } else if (i < boarderSize && j >= size + boarderSize) {
                if (i > 0 && i < j - size - boarderSize) {
                    initArray[i][j] = size + boarderSize - j - 1;
                } else if (i > 0 && j > size + boarderSize && i > j - size - boarderSize) {
                    initArray[i][j] = size + boarderSize - j - 1;
                } else if (i == (j - size - boarderSize) && i >= boarderSize / 2) {
                    initArray[i][j] = -i - 1;
                } else {
                    initArray[i][j] = i - boarderSize;
                }
            } else if ((i >= boarderSize && i < size + boarderSize) && j < boarderSize) {
                initArray[i][j] = j - boarderSize;
            } else if ((i >= boarderSize && i < size + boarderSize) && j >= size + boarderSize) {
                initArray[i][j] = boarderSize + size - j - 1;
            } else if (i >= size + boarderSize && j < boarderSize) {
                if (j > 0 && j < i - size - boarderSize) {
                    initArray[i][j] = size + boarderSize - i - 1;
                } else if (j > 0 && i > size + boarderSize && j > i - size - boarderSize) {
                    initArray[i][j] = size + boarderSize - i - 1;
                } else if (j == (i - size - boarderSize) && j >= boarderSize / 2) {
                    initArray[i][j] = -j - 1;
                } else {
                    initArray[i][j] = j - boarderSize;
                }
            } else if (i >= size + boarderSize && (j >= boarderSize && j < size + boarderSize)) {
                initArray[i][j] = boarderSize + size - i - 1;
            } else if (i >= size + boarderSize && j >= size + boarderSize) {
                if (j < i) {
                    initArray[i][j] = size + boarderSize - i - 1;
                } else {
                    initArray[i][j] = size + boarderSize - j - 1;
                }
            } else {
                initArray[i][j] = index++;
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

void printLineNumberBoard(int arr[size * size][adjacentLines][bingo]) {
    printf("\n");
    for (int i = 0; i < size * size; i++) {
        printf("\n   board %d\n", i + 1);
        for (int j = 0; j < adjacentLines; j++) {
            printf("line %d: ", j + 1);
            for (int k = 0; k < bingo; k++) {
                printf("%2d ", arr[i][j][k]);
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

void printUpdatedBoard() {
    int index = 1;
    for (int i = 0; i < size * size; i++) {
        if (fillNum[i] == 1) {
            if (numPick - 1 == i) {
                printf(" %3s", "'o'");
            } else {
                printf("%3s ", "o");
            }
        } else if (fillNum[i] == -1) {
            if (numPick - 1 == i) {
                printf(" %3s", "'x'");
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

void countPlay() {
    playCount++;
    if (playCount == size * size) {
        printf("draw game\n");
        exit(1);
    }
}
