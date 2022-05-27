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
int highNum;
int location;
int fillNum[size * size];
int playLineNums[size * size][adjacentLines][bingo + 2];
int defaultLineNums[size * size][adjacentLines][bingo];
int adjacentList[size * size][adjacentLines * (bingo - 1)];

int getBestAdjacentNumber();
void updateNode();
int calculateComputerWeight(int i, int j);
int calculateUserWeight(int i, int j);
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

struct Node {
    int data;
    int key;
    struct Node* next;
};

struct Node* head = NULL;

int main() {
    initData();
    setDefaultLineNums();
    // printDefaultLineNums();

    while (1) {
        setNum();
        // printFillNum();
        printBoard();
        addAdjNums();
        printAllAdjNums();
        // updateNode();
        updatePlay();
        switchPlayer();
        countPlay();
    }
    return 0;
}

int getBestAdjacentNumber() {
    printf("high num is %d\n", highNum);
    printf("location is %d\n", location);
    int num = rand() % 25 + 1;
    while (fillNum[num - 1] != 0) {
        num = rand() % 25 + 1;
    }
    return num;
}

void updateNode() {
    // struct Node* link = (struct Node*) malloc(sizeof(struct Node));

    head->data = 1;
    head->next = NULL;
    
    printf("%d\n", head->data);
    // printf("%s\n", head->next);
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
            playLineNums[i][j][bingo + 1] = calculateUserWeight(i, j);
            if (highNum < playLineNums[i][j][bingo]) {
                highNum = playLineNums[i][j][bingo];
                location = i + 1;
            }
        }
    }
    for (int i = 0; i < size * size; i++) {
        printf("           %d    cpu usr\n", i + 1);
        for (int j = 0; j < adjacentLines; j++) {
            printf("line %d:", j + 1);
            for (int k = 0; k < bingo + 2; k++) {
                if (k == bingo) {
                    printf("%3d ", playLineNums[i][j][k]);
                } else if (k == bingo + 1) {
                    printf("%3d ", playLineNums[i][j][k]);                    
                } else {
                    printf("%2d ", playLineNums[i][j][k]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}

int calculateUserWeight(int i, int j) {
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
    if (player == 1) {
        value = oCount * 2 + xCount * 3 + nCount;
    } else if (player == 2) {
        value = oCount * 3 + xCount * 2 + nCount;
    }
    return value;
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
    if (player == 1) {
        value = oCount * 3 + xCount * 2 + nCount;
    } else if (player == 2) {
        value = oCount * 2 + xCount * 3 + nCount;
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
