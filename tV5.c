#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define bingo 5
#define size 12
#define adjacentLines 8

int player;
int numPick;
int playCount;
int fillNum[size * size];
int playLineNums[size * size][adjacentLines][bingo + 2];
int defaultLineNums[size * size][adjacentLines][bingo];
int adjacentList[size * size][adjacentLines * (bingo - 1)];
int bestPossibleNums[adjacentLines * (bingo - 1)];
int totalScore[size * size][2];
int adjFillList[size * size] = {};

int receiveANum();
void calculateTotalScore();
void printTotalScore();
void printNumScore();
void resetNextNums();
void setNextNums();
int getBestAdjacentNumber();
int calculateHighValue(int stoneCount, int gapCount, int innerGapCount);
int calculateUserWeight(int i, int j);
int calculateCpuWeight(int i, int j);
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
void printAdjNums();
void printSpot();
void printAdjBoard();
void printNumBoard();

int main() {
    srand(time(0));
    initData();
    setDefaultLineNums();

    while (1) {
        // numPick = receiveANum();
        // if (numPick > 10000) {
        //     printSpot();
        // } else {
            setNum();
            printBoard();
            addAdjNums();
            updatePlay();
            calculateTotalScore();
            // printTotalScore();
            // printNumScore();
            switchPlayer();
            countPlay();
        // }
    }
    return 0;
}

void printSpot() {
    printf("test line\n");
}

int getBestAdjacentNumber() {
    if (playCount == 0) {
        if (size * size % 2 == 1) {
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
        printAdjNums();
        int count = 0;
        printf("adjacent numbers: ");
        for (int i = 0; i < size * size; i++) {
            int temp = adjFillList[i + 1];
            if (temp > 0) {
                count++;
            }
        }

        int adjNums[count];
        int index = 0;
        for (int i = 0; i < size * size; i++) {
            int temp = adjFillList[i + 1];
            if (temp > 0) {
                adjNums[index++] = temp;
            }
        }
        int max = 0;
        int location = 0;
        printf("\n");
        for (int i = 0; i < count; i++) {
            // printf("%d \n", adjNums[i]);
            printf("%2d(i)- %2d: %4d,%4d\n", i + 1, adjNums[i], totalScore[adjNums[i] - 1][0], totalScore[adjNums[i] - 1][1]);
            if (totalScore[adjNums[i] - 1][1] > max) {
                max = totalScore[adjNums[i] - 1][1];
                location = i;
            }
        }
        printf("\n");
        printf("max:%d %d\n", max, adjNums[location]);
        return adjNums[location];
    }
}

void printAdjNums() {
    printf("o = user, x = cpu\n");
    for (int i = 0; i < size * size; i++) {
        bool check = false;
        if (fillNum[i] == 1) {
            if (adjacentList[i][adjacentLines * (bingo - 1) - 1] != 0) {
                printf("%2d [o]: ", i + 1);
                check = true;
            }
        } else if (fillNum[i] == -1) {
            if (adjacentList[i][adjacentLines * (bingo - 1) - 1] != 0) {
                printf("%2d [x]: ", i + 1);
                check = true;
            }
        }
        if (check == true) {
            for (int j = 0; j < adjacentLines * (bingo - 1); j++) {
                if (adjacentList[i][j] > 0) {
                    printf("%d ", adjacentList[i][j]);
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}

void setNextNums() {
    int max = 0;
    for (int i = 0; i < size * size; i++) {
        if (max < totalScore[i][1]) {
            max = totalScore[i][1];
        }
    }
    int index = 0;
    for (int i = 0; i < size * size; i++) {
        if (max == totalScore[i][1]) {
            bestPossibleNums[index++] = i + 1;
        }
    }
}

// update recently selected number in the array of playLineNums
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
                if (defaultLineNums[i][j][k] == 0) {
                    playLineNums[i][j][bingo] = -1;        // cpu
                    playLineNums[i][j][bingo + 1] = -1;    // user
                } else {
                    if (player == 1) {
                        playLineNums[i][j][bingo] = calculateCpuWeight(i, j);
                        playLineNums[i][j][bingo + 1] = calculateUserWeight(i, j);
                    } else if (player == 2) {
                        playLineNums[i][j][bingo] = calculateCpuWeight(i, j);
                        playLineNums[i][j][bingo + 1] = calculateUserWeight(i, j);
                    }
                }
            }
        }
    }
}

void calculateTotalScore() {
    for (int i = 0; i < size * size; i++) {
        if (fillNum[i] == 0) {
            int cpuSum = 0;
            int userSum = 0;
            if (i + 1 == numPick) {
            }
            for (int j = 0; j < adjacentLines; j++) {
                cpuSum += playLineNums[i][j][bingo];
                userSum += playLineNums[i][j][bingo + 1];
            }
            totalScore[i][0] = cpuSum;
            totalScore[i][1] = userSum;
            // printf("%d - %d(%d,%d)\n", i + 1, fillNum[i + 1], totalScore[i + 1][0], totalScore[i][1]);
        } else {
            totalScore[i][0] = 0;
            totalScore[i][1] = 0;
        }
        // printf("%d - %d(%d,%d)\n", i + 1, fillNum[i + 1], totalScore[i + 1][0], totalScore[i][1]);
    }
}

void printTotalScore() {
    printf("     cpu user diff\n");
    for (int i = 0; i < size * size; i++) {
        printf("%2d: ", i + 1);
        for (int j = 0; j < 2; j++) {
            printf("%4d ", totalScore[i][j]);
        }
        int diff = totalScore[i][1] - totalScore[i][0];
        printf("%4d", diff);
        printf("\n");
    }
    printf("\n");
}

void printNumScore() {
    printf("\nuser = 1, cpu = -1\n");
    // numPick = 13;
    printf("      %2d %9s cpu user\n", numPick, " ");
    for (int j = 0; j < adjacentLines; j++) {
        printf("%d: ", j + 1);
        for (int k = 0; k < bingo + 2; k++) {
            if (k >= bingo) {
                printf("%4d ", playLineNums[numPick - 1][j][k]);
            } else {
                printf("%2d ", playLineNums[numPick - 1][j][k]);
            }
        }
        printf("\n");
    }
    printf("\n");

    // printf("\nuser = 1, cpu = -1\n");
    // for (int i = 0; i < 2; i++) {
    //     printf("     %2d     cpu user\n", i + 1);
    //     for (int j = 0; j < adjacentLines; j++) {
    //         printf("%d: ", j + 1);
    //         for (int k = 0; k < bingo + 2; k++) {
    //             if (k >= bingo) {
    //                 printf("%4d ", playLineNums[i][j][k]);
    //             } else {
    //                 printf("%2d ", playLineNums[i][j][k]);
    //             }
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }
    // printf("\n");
}

void resetNextNums() {
    for (int i = 0; i < adjacentLines * (bingo - 1); i++) {
        bestPossibleNums[i] = 0;
    }
}

int calculateCpuWeight(int i, int j) {
    int stoneCount = 0;
    int gapCount = 0;
    int innerGapCount = 0;
    int tempInnerCount = 0;
    int value = 0;

    // to distinguish gap count and innerGap count
    bool isStone = false;

    // killValue is used to find the opponent stone in a line
    int killValue = 1;

    for (int k = 0; k < bingo; k++) {
        // if killValue is found, it is impossible to make five in a row
        if (playLineNums[i][j][k] == killValue) {   //opponent
            value = -1;
            return value;
        } else if (playLineNums[i][j][k] == -killValue) { //same player
            stoneCount++;
            innerGapCount += tempInnerCount;
            tempInnerCount = 0;
            if (isStone == false) {
                isStone = true;
            }
        } else if (playLineNums[i][j][k] == 0) {
            // no 'x' = -1 or 'o' = 1   gap = 0   // empty
            gapCount++;
            if (isStone == true) {
                tempInnerCount++;
            }
        }
    }
    value = calculateHighValue(stoneCount, gapCount, innerGapCount);
    return value;
}

int calculateUserWeight(int i, int j) {
    int stoneCount = 0;
    int gapCount = 0;
    int innerGapCount = 0;
    int tempInnerCount = 0;
    int value = 0;

    // to distinguish gap count and innerGap count
    bool isStone = false;

    // killValue is used to find the opponent stone in a line
    int killValue = -1;

    for (int k = 0; k < bingo; k++) {
        // if killValue is found, it is impossible to make five in a row
        if (playLineNums[i][j][k] == killValue) {   //opponent
            value = -1;
            return value;
        } else if (playLineNums[i][j][k] == -killValue) { //same player
            stoneCount++;
            innerGapCount += tempInnerCount;
            tempInnerCount = 0;
            if (isStone == false) {
                isStone = true;
            }
        } else if (playLineNums[i][j][k] == 0) {
            // no 'x' = -1 or 'o' = 1   gap = 0   // empty
            gapCount++;
            if (isStone == true) {
                tempInnerCount++;
            }
        }
    }
    value = calculateHighValue(stoneCount, gapCount, innerGapCount);
    return value;
}

int calculateHighValue(int stoneCount, int gapCount, int innerGapCount) {
    int value = 0;
    if (gapCount == bingo) {
        return value;
    }
    // stone = 1000, no gap = 500, innerGap = 20
    if (gapCount == 0) {
        value = stoneCount * 5000 + 500;
    } else {
        value = stoneCount * 3000 + 500 - innerGapCount * 20;
    }
    // printf("stoneCount:%d %d gapCount: %d\n", stoneCount, value, gapCount);
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
    int numSeq = 0;
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

// int receiveANum() {
//     printf("\n[user] enter a num\n");
//     printf("or to print enter number + 10000: ");
//     scanf("%d", &numPick);
//     return numPick;
// }

void printNumBoard() {
    printf("num: %d\n", numPick);
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < adjacentLines; j++) {
            for (int k = 0; k < bingo + 2; k++) {
                printf("%d ", playLineNums[i][j][k]);
            }
        }
        printf("\n");
    }
    printf("\n");
    // for (int i = 0; i < 8; i++) {
    //     printf("%d-%d: (%d,%d)\n", numPick, i, playLineNums[numPick - 1][0], totalScore[numPick - 1][1]);
    // }
}

void setNum() {
    int temp = 0;
    int foundSlot = 0;
    char* name = "user";
    if (player == 1) {
        printf("\n[%s turn] enter a number\n", name);
        printf("or add 10000 to the number to print: ");
        scanf("%d", &temp);
        do {
            if (temp > 0 && temp <= size * size) {
                if (fillNum[temp - 1] == 0) {
                    foundSlot = 1;
                }
            }
            if (temp > 10000 && temp <= 10000 + size * size) {
                numPick = temp - 10000;
                printNumBoard();
            }
            if (foundSlot == 0) {
                printf("\n[%s turn] enter a different number\n", name);
                printf("or add 10000 to the number to print: ");
                scanf("%d", &temp);
            }
        } while (foundSlot != 1);
        fillNum[temp - 1] = 1;
        printf("\nuser picks %d\n", temp);
    } else if (player == 2) {
        name = "cpu";
        printf("\n[%s turn] enter negative number to continue\n", name);
        printf("or add 10000 to the number to print: ");
        scanf("%d", &temp);
        do {
            if (temp < 0) {
                foundSlot = 1;
            } else {
                if (temp > 10000 && temp <= 10000 + size * size) {
                    numPick = temp - 10000;
                    printNumBoard();
                }
                printf("\n[%s turn] enter negative number to continue\n", name);
                printf("or add 10000 to the number to print: ");
                scanf("%d", &temp);
            }
        } while (foundSlot != 1);
        numPick = getBestAdjacentNumber();
        fillNum[numPick - 1] = -1;
        printf("\ncomputer picks %d\n", numPick);
    }
}

void printAdjBoard() {
    int count = 0;
    int row = 1;
    for (int i = 0; i < 9; i++) {
        int temp = numPick - (size * row) - 1 + (i % 3);
        if (i != 4 && adjFillList[temp] != -1) {
            if (((numPick - 1) % size != 0 || (i) % 3 != 0) &&
                (numPick % size != 0 || (i - 2) % 3 != 0)) {
                adjFillList[temp] = temp;
            }
        } else {
            adjFillList[temp] = -1;
        }
        count++;
        if (count % 3 == 0) {
            row--;
        }
    }
    
    count = 0;
    for (int i = 0; i < size * size; i++) {
        int temp = adjFillList[i + 1];
        printf("%3d ", temp);
        count++;
        if (count == size) {
            printf("\n");
            count = 0;
        }
    }
    printf("\n");
}

void initData() {
    printBoard();
    printf("1. user    2. computer: ");
    scanf("%d", &player);
}

void countPlay() {
    playCount++;
    // if (playCount == size * size) {
    if (playCount == 5) {
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
