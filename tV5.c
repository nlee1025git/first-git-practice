#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define bingo 3
#define size 5
#define adjacentLines 8

int player;
int numPick;
int numSeq;
int playCount;
int fillNum[size * size];
int playLineNums[size * size][adjacentLines][bingo + 2];
int defaultLineNums[size * size][adjacentLines][bingo];
int adjacentList[size * size][adjacentLines * (bingo - 1)];

int getBestAdjacentNumber();
int calculateComputerWeight(int i, int j);
int calculateHighValue(int oCount, int xCount, int nCount, int max);
void updatePlay();
void printAllAdjNums();
void addAdjNums();
void rmvPickNums();
void sort();
void swap();
void printFillNum();
void printDefaultLineNums();
void setDefaultLineNums();
void printBoard();
void setNum();
void initData();
void countPlay();
void switchPlayer();

int main() {
    initData();
    setDefaultLineNums();
    // printDefaultLineNums();

    while (1) {
        setNum();
        // printFillNum();
        printBoard();
        addAdjNums();
        // printAllAdjNums();
        updatePlay();
        switchPlayer();
        countPlay();
    }
    return 0;
}

int getBestAdjacentNumber() {
    int num = -1;
    int location = 0;
    for (int i = 0; i < size * size; i++) {
        int sum = 0;
        if (fillNum[i] == 0) {
            for (int j = 0; j < adjacentLines; j++) {
                sum += playLineNums[i][j][bingo];
            }
            if (sum >= num) {
                num = sum;
                location = i + 1;
                printf("num: %d, location: %d\n", num, location);
            }
        }
    }
    // printf("num: %d, location: %d\n", num, location);
    return location;
}

void updatePlay() {
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < adjacentLines; j++) {
            for (int k = 0; k < bingo; k++) {
                if (numPick == defaultLineNums[i][j][k]) {
                    if (player == 1) {
                        playLineNums[i][j][k] = 1;
                    } else if (player == 2) {
                        playLineNums[i][j][k] = -1;
                    }
                }
            }
            playLineNums[i][j][bingo] = calculateComputerWeight(i, j);
            // playLineNums[i][j][bingo + 1] = ;
        }
    }
    // // play board print
    // for (int i = 0; i < size * size; i++) {
    //     for (int j = 0; j < adjacentLines; j++) {
    //         for (int k = 0; k < bingo + 2; k++) {
    //             printf("%2d ", playLineNums[i][j][k]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }
}

int calculateComputerWeight(int i, int j) {
    int oCount = 0;
    int xCount = 0;
    int nCount = 0;
    int value = 0;
    for (int k = 0; k < bingo; k++) {
        if (playLineNums[i][j][k] == 1) {
            oCount++;
        } else if (playLineNums[i][j][k] == -1) {
            xCount++;
        } else {
            nCount++;
        }
    }
    value = calculateHighValue(oCount, xCount, nCount, bingo);
    return value;
}

int calculateHighValue(int oCount, int xCount, int nCount, int max) {
    int value = 0;
    // o = user, x = cpu
    if (oCount + xCount + nCount == max) {
        // do nothing
    } else {
        if (oCount > max || xCount > max || nCount > max) {
            // any variable is bigger than max
            return value;
        }
        // sum of three counts is less than or greater than max
        return value;
    }
    if (oCount == 0 && xCount == max) {
        // cpu put all five stones
        value = 10000;
    } else if (oCount == max && xCount == 0) {
        // user put all five stones
        value = 5000;
    } else if (oCount == 0 && xCount == max - 1) {
        // cpu put four stones and user has no stones
        value = 1000;
    } else if (oCount == max - 1 && xCount == 0) {
        // user put four stones and cpu has no stones
        value = 800;
    } else if (oCount == 0 && xCount == max - 2) {
        // cpu put three stones and user has no stones
        value = 500;
    } else if (oCount == max - 2 && xCount == 0) {
        // user put three stones and cpu has no stones
        value = 400;
    } else if (oCount == 0 && xCount > 0) {
        // cpu put more than one stone and user has no stones
        value = xCount * 10;
    } else if (oCount > 0 && xCount == 0) {
        // user put more than one stone and cpu has no stones
        value = oCount * 5;
    } else {
        // user and cpus have no stones
        value = 0;
        // printf("oCount: %d, xCount: %d, nCount: %d, value is %d\n", oCount, xCount, nCount, value);
    }
    return value;
}

void printAllAdjNums() {
    printf("o = user, x = cpu\n");
    for (int i = 0; i < size * size; i++) {
        if (fillNum[i] == 1) {
            printf("%2d [o]: ", i + 1);
        } else if (fillNum[i] == -1) {
            printf("%2d [x]: ", i + 1);
        } else {
            printf("%2d [ ]: ", i + 1);
        }
        for (int j = 0; j < adjacentLines * (bingo - 1); j++) {
            if (adjacentList[i][j] > 0) {
                printf("%d ", adjacentList[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

void addAdjNums() {
    for (int i = 0; i < adjacentLines; i++) {
        for (int j = 1; j < bingo; j++) {
            bool duplicate = false;
            if (defaultLineNums[numPick - 1][i][j] > 0) {
                for (int k = 0; k < numSeq; k++) {
                    if (defaultLineNums[numPick - 1][i][j] == adjacentList[numPick - 1][k]) {
                        duplicate = true;
                    }
                }
                if (duplicate == false) {
                    adjacentList[numPick - 1][numSeq++] = defaultLineNums[numPick - 1][i][j];
                }
            }
        }
    }
    numSeq = 0;
    rmvPickNums();
    sort();
}

void rmvPickNums() {
    for (int i = 0; i < size * size; i++) {
        if (fillNum[i] != 0) {
            for (int j = 0; j < size * size; j++) {
                for (int k = 0; k < adjacentLines * bingo; k++) {
                    if (adjacentList[j][k] == i + 1) {
                        adjacentList[j][k] = 0;
                    }
                }
            }
        }
    }
}

void sort() {
    for (int i = 0; i < adjacentLines * (bingo - 1) - 1; i++) {
        for (int j = 0; j < adjacentLines * (bingo - 1) - i - 1; j++) {
                if (adjacentList[numPick - 1][j] > adjacentList[numPick - 1][j + 1]) {
                    swap(&adjacentList[numPick - 1][j], &adjacentList[numPick - 1][j + 1]);
                }
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printFillNum() {
    int index = 1;
    for (int i = 0; i < size * size; i++) {
        printf("%2d ", index++);
    }
    printf("\n");
    for (int i = 0; i < size * size; i++) {
        printf("%2d ", fillNum[i]);
    }
    printf("\n");
}

void printDefaultLineNums() {
    for (int i = 0; i < size * size; i++) {
        printf("     %d\n", i + 1);
        for (int j = 0; j < adjacentLines; j++) {
            printf("%d:", j + 1);
            for (int k = 0; k < bingo; k++) {
                printf("%2d ", defaultLineNums[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void setDefaultLineNums() {
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < adjacentLines; j++) {
            for (int k = 0; k < bingo; k++) {
                if (j == 0) {
                    if ((i + 1 + k) <= size * ((i / size) + 1)) {
                        defaultLineNums[i][j][k] = i + 1 + k;
                    }
                } else if (j == 1) {
                    if ((i + 1 + k * size + k) <= size * size && (i + 1 + k * size + k) <= size * ((i / size) + k + 1)) {
                        defaultLineNums[i][j][k] = i + 1 + k * size + k;
                    }
                } else if (j == 2) {
                    if ((i + 1 + k * size) <= size * size) {
                        defaultLineNums[i][j][k] = i + 1 + k * size;
                    }
                } else if (j == 3) {
                    if ((i + 1 + k * size - k) >= ((i / size) + k) * size + 1 && i + 1 + k * size - k <= size * size) {
                        defaultLineNums[i][j][k] = i + 1 + k * size - k;
                    }
                } else if (j == 4) {
                    if ((i + 1 - k) >= (i / size)  * size + 1) {
                        defaultLineNums[i][j][k] = i + 1 - k;
                    }
                } else if (j == 5) {
                    if ((i + 1 - k - size * k) >= ((i / size) - k) * size + 1 && ((i / size) - k) * size + 1 > 0) {
                        defaultLineNums[i][j][k] = i + 1 - k - size * k;
                    }
                } else if (j == 6) {
                    if ((i + 1 - size * k) >= 0) {
                        defaultLineNums[i][j][k] = i + 1 - size * k;
                    }
                } else if (j == 7) {
                    if (i + 1 + k - size * k > 0 && i + 1 + k - size * k <= ((i / size) + 1 - k) * size) {
                        defaultLineNums[i][j][k] = i + 1 + k - size * k;
                    }
                }
            }
        }
    }
}

void printBoard() {
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
    } else if (player == 2) {
        numPick = getBestAdjacentNumber();
        fillNum[numPick - 1] = -1;
        printf("computer picks %d\n", numPick);
    }
}

void initData() {
    printBoard();
    printf("1. user    2. computer: ");
    scanf("%d", &player);
}

void countPlay() {
    playCount++;
    if (playCount == size * size) {
        printf("draw game\n");
        exit(1);
    }
}

void switchPlayer() {
    if (player == 1) {
        player = 2;
    } else if (player == 2) {
        player = 1;
    }
}
