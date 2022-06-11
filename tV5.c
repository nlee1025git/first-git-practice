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
int adjacentNums[size * size];

int getBestAdjacentNumber();
int newCalHighVal(int stoneCount, int gapCount, int innerGapCount);
int calculateWeight(int i, int j);
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

int nodeCount = 0;

struct Node {
    int myNum;  // board number
    int sumScore; // lines 1 - 8
    struct Node* next;
};

struct Node* head = NULL;

bool isEmpty() {
    return nodeCount == 0;
}

bool isFull() {
    return nodeCount == size * size;
}

int nodeSize() {
    return nodeCount;
}

void enqueue(struct Node* element) {
    if (isFull()) {
        printf("node is full");
    } else {
        nodeCount++;
        head->myNum = numPick;
        // head->sumScore = sumScores();
        head->next = NULL;
        
    }
}

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
    if (playCount == 0) {
        if (size * size / 2 == 1) {
            return size * size / 2 + 1;
        } else {
            int startNums[4];
            startNums[0] = size * (size / 2 - 1) + size / 2;
            startNums[1] = startNums[0] + 1;
            startNums[2] = startNums[0] + size;
            startNums[3] = startNums[2] + 1;
            int rtn = rand() % 4;
            return startNums[rtn];
        }
    } else {
        int num = rand() % (size * size) + 1;
        while (fillNum[num - 1] != 0) {
            num = rand() % (size * size) + 1;
        }
        return num;
        // int num = -1;
        // int location = 0;
        // printAllAdjNums();
        // for (int i = 0; i < size * size; i++) {
        //     int sum = 0;
        //     for (int j = 0; j < adjacentLines * (bingo - 1); j++) {
        //         if (adjacentList[i][j] > 0) {
        //             printf("%d ", adjacentList[i][j]);
        //             for (int k = 0; k < adjacentLines; k++) {
        //                 // sum += playLineNums[adjacentList[i][j]][k][bingo + 1];
        //                 sum += playLineNums[adjacentList[i][j]][k][bingo];
        //             }
        //         }
        //     }
        //     if (sum >= num) {
        //         num = sum;
        //         location = i + 1;
        //         printf("num: %d, location: %d\n", num, location);
        //     }
        //     printf("\n");
        // }
        // return location;
    }
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
            if (player == 1) {
                playLineNums[i][j][bingo + 1] = calculateWeight(i, j);      // user
                playLineNums[i][j][bingo] = -playLineNums[i][j][bingo + 1]; // cpu
            } else {
                playLineNums[i][j][bingo] = calculateWeight(i, j);           // cpu
                playLineNums[i][j][bingo + 1] = -playLineNums[i][j][bingo]; // user
            }
        }
    }
    // print play board
    for (int i = 0; i < size * size; i++) {
        printf("   %d\n", i + 1);
        for (int j = 0; j < adjacentLines; j++) {
            for (int k = 0; k < bingo + 2; k++) {
                printf("%2d ", playLineNums[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int calculateWeight(int i, int j) {
    int stoneCount = 0;
    int gapCount = 0;
    int innerGapCount = 0;
    int value = 0;

    // to distinguish gap count and innerGap count
    bool isStone = false;

    // killValue is used to find the opponent stone in a line
    int killValue = 1;
    if (player == 1) {
        killValue = -1;
    }
    for (int k = 0; k < bingo; k++) {
        // if killValue is found, return 0
        if (playLineNums[i][j][k] == killValue) {
            return value;
        }
        if (playLineNums[i][j][k] == -killValue) {
            stoneCount++;
            if (isStone == false) {
                isStone == true;
            } else {
                isStone = false;
            }
        } else {
            gapCount++;
            if (isStone == true) {
                innerGapCount++;
            }
        }
    }
    // printf("i: %d, j: %d\n", i, j);
    // printf("stone: %d, gap: %d, innerGap: %d\n", stoneCount, gapCount, innerGapCount);
    value = newCalHighVal(stoneCount, gapCount, innerGapCount);
    return value;
}

int newCalHighVal(int stoneCount, int gapCount, int innerGapCount) {
    int value = 0;
    if (gapCount == size) {
        return value;
    }
    if (stoneCount == bingo && gapCount == 0 && innerGapCount == 0) {
        value = 800;
    } else if (stoneCount == bingo - 1 && gapCount == 1 && innerGapCount == 0) {
        value = 600;
    } else if (stoneCount == bingo - 1 && gapCount == 1 && innerGapCount == 1) {
        value = 500;
    // [' ', 'X', ' ']
    } else if (stoneCount == bingo - 2 && gapCount == 2 && innerGapCount == 0) {
        value = 300;
    // ['X', ' ', ' '] or [' ', ' ', 'X']
    } else if (stoneCount == bingo - 2 && gapCount == 2 && innerGapCount == 0) {
        value = 200;
    }
    // for (int i = size; i > 0; i--) {
    //     if (stoneCount == i) {
    //         value = 100 * i;
    //     }
    // }
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
        // cpu put five stones
        value = 10000;
    } else if (oCount == max && xCount == 0) {
        // user put five stones
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
