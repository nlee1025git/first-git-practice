#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define size 3
#define lines size * 2 + 2

int player;
int numPick;
int fillNum[size * size] = {0};
int lineNumbers[lines][size] = {0};
int scoreboard[lines][size + 2] = {0};

void initData();
void setNum();
void updateBoard();
void switchPlayer();
int scanBestScore();
int findBestScore(int nextNum, int player);
void updateScore();
void printTableboard(int tempBoard[lines][size + 2], int row, int location);
int calculateComputerWeight(int rowNum, int tempscoreBoard[lines][size + 2]);
int calculateUserWeight(int rowNum, int tempBoard[lines][size + 2]);
void updateTempScore();
int compareTwo(int prevNum, int curNum);
int checkUserPoint(int num);
void printLine(int lineNum, int select);
int pickBestBoardNum();
int twoInARow();
void printPreview(int nextBoard[lines][size + 2]);
void updateTempBoard(int nextPick);
void updateScore2(int pickBestNum);
void print();

int main() {
    int count = 0;
    srand(time(0));
    initData();
    
    while (1) {
        setNum();
        updateBoard();
        updateScore();
        switchPlayer();
        count++;
        if (count == size * size) {
            printf("draw game\n");
            break;
        }
    }
    return 0;
}

int twoInARow() {
    int row = -1;
    for (int i = 0; i < lines; i++) {
        if (scoreboard[i][size] >= 31) {
            row = i;
        // } else if (scoreboard[i][size + 1] >= 31) {
        //     row = i;
        } else if (scoreboard[i][size] >= 15) {
            row = i;
        // } else if (scoreboard[i][size + 1] >= 15) {
        //     row = i;
        }
        for (int j = 0; j < size; j++) {
            if (scoreboard[row][j] == 0 && row >= 0) {
                return lineNumbers[row][j];
            }
        }
    }
    return -1;
}

int scanBestScore() {
    int fillNumCopy[size * size];
    memcpy(fillNumCopy, fillNum, sizeof(fillNum));

    int scoreboardCopy[lines][size + 2] = {0};
    memcpy(scoreboardCopy, scoreboard, sizeof(scoreboard));

    int checkLocation = twoInARow();
    int pickBestLocation = pickBestBoardNum();
    printf("\ncheckLocation is %d\n", checkLocation);
    if (checkLocation > 0) {
        return checkLocation;
    }

    printf("cpu's pickBestLocation is %d\n\n", pickBestLocation);
    fillNum[pickBestLocation - 1] = -1;
    updateScore2(pickBestLocation);
    print();
    updateBoard();
    switchPlayer();

    int userBestLocation = pickBestBoardNum();
    printf("user's pickBestLocation is %d\n\n", userBestLocation);
    fillNum[userBestLocation - 1] = 1;
    updateScore2(userBestLocation);
    print();
    updateBoard();
    switchPlayer();

    int prevPickBestLocation = pickBestLocation;
    pickBestLocation = pickBestBoardNum();
    printf("cpu's pickBestLocation is %d\n\n", pickBestLocation);
    fillNum[pickBestLocation - 1] = -1;
    updateScore2(pickBestLocation);
    print();
    updateBoard();

    memcpy(scoreboard, scoreboardCopy, sizeof(scoreboard));
    memcpy(fillNum, fillNumCopy, sizeof(fillNum));

    return prevPickBestLocation;
}

int pickBestBoardNum() {
    if (player == 1) {
        printf("\n\n*** user turn ***\n\n");
    } else {
        printf("\n\n*** cpu turn ***\n\n");
    }
    int max = -100;
    int location = 0;
    for (int i = 1; i <= size * size; i++) {
        if (fillNum[i - 1] == 0) {
            // printf("--- %d ---\n", i);
            // updateBoard();
            int temp = findBestScore(i, player);
            if (temp == max) {
                location = compareTwo(location, i);
            }
            if (temp > max) {
                max = temp;
                location = i;
            }
        }
    }
    return location;
}

int findBestScore(int num, int player) {
    int maxWeight = 0;
    int row = -1;
    int location = -1;
    int tempScoreboard[lines][size + 2] = {0};
    int tempScoreboardDelta[lines][size + 2] = {0};

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            tempScoreboard[i][j] = scoreboard[i][j];
        }
    }

    // printf("player is %d\n", player);
    
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            tempScoreboardDelta[i][j] = tempScoreboard[i][j];
            if (lineNumbers[i][j] == num && player == 2) {
                tempScoreboard[i][j] = -1;
                row = i;
                location = j;
            } else if (lineNumbers[i][j] == num && player == 1) {
                tempScoreboard[i][j] = 1;
                row = i;
                location = j;
            }
            if (lineNumbers[i][j] == lineNumbers[row][location]) {
                tempScoreboard[i][size] = calculateComputerWeight(i, tempScoreboard);
                tempScoreboard[i][size + 1] = calculateUserWeight(i, tempScoreboard);
                int temp = scoreboard[i][size] - tempScoreboard[i][size];
                int temp1 = scoreboard[i][size + 1] - tempScoreboard[i][size + 1];
                if (temp < 0) {
                    temp = -1 * temp;
                }
                if (temp1 < 0) {
                    temp1 = -1 * temp1;
                }
                tempScoreboardDelta[i][size] = temp;
                tempScoreboardDelta[i][size + 1] = temp1;
                if (maxWeight < temp) {
                    maxWeight = temp;
                }
            }
        }
    }
    // printf("%d's maxWeight: %d\n", num, maxWeight);
    return maxWeight;
}

int checkBestBoardNum() {
    int max = -100;
    int location = -1;
    printf("\nuser turn scanning\n");
    for (int i = 1; i <= size * size; i++) {
        if (fillNum[i - 1] == 0) {
            int temp = findBestScore(i, player);
            // printf("--- %d ---\n", i);
//            printf("%d) temp: %d, max: %d\n", i, temp, max);
            fillNum[i - 1] = 1;
            updateBoard();
            if (temp == max) {
                location = compareTwo(location, i);
            }
            if (temp > max) {
                max = temp;
                location = i;
            }
        }
//        memcpy(fillNum, fillNumCopy2, sizeof(fillNum));
    }
    return 1;
}

void updateTempBoard(int nextPick) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            if (player == 1) {
                if (lineNumbers[i][j] == nextPick) {
                    scoreboard[i][j] = 1;
                }
            } else {
                if (lineNumbers[i][j] == nextPick) {
                    scoreboard[i][j] = -1;
                }
            }
        }
        scoreboard[i][size] = calculateComputerWeight(i, scoreboard);
        scoreboard[i][size + 1] = calculateUserWeight(i, scoreboard);
    }
}

void printPreview(int nextBoard[lines][size + 2]) {
    printf(" ***** nextBoard *****\n");
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", nextBoard[i][j]);
        }
        printf("\n");
    }
    printf(" ***** nextBoard *****\n");    
}

void printLine(int lineNum, int select) {
    for (int i = 0; i < size; i++) {
        if (select == 0) {
            printf("%2d ", lineNumbers[lineNum][i]);
        } else if (select == 1 && fillNum[lineNum - 1] == 0) {
            printf("%2d ", lineNumbers[lineNum][i]);
        }
    }
    printf("\n");
}

int compareTwo(int prevNum, int curNum) {
    // printf("%d and %d\n", prevNum, curNum);
    int prev = 0;
    int cur = 0;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            if (lineNumbers[i][j] == prevNum) {
                for (int k = 0; k < size; k++) {
                    if (scoreboard[i][k] == 0) {
                        prev++;
                    }
                }
            }
            if (lineNumbers[i][j] == curNum) {
                for (int k = 0; k < size; k++) {
                    if (scoreboard[i][k] == 0) {
                        cur++;
                    }
                }
            }
        }
    }
    if (cur > prev) {
        return curNum;
    } else if (prev > cur) {
        return prevNum;
    } else {
        return prevNum;
    }
}

int checkUserPoint(int num) {
    for (int i = 0; i < lines; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < size; j++) {
            printf("%d ", lineNumbers[i][j]);
        }
        printf("\n");
    }
    printf("------\n");

    int count = 0;
    for (int i = 0; i < lines; i++) {
        int line = 0;
        for (int j = 0; j < size; j++) {
            if (lineNumbers[i][j] == num) {
                line = calculateUserWeight(i, scoreboard);
                // printf("line is %d\n", line);
            }
        }
    }
    return count;
}

void printTableboard(int tempBoard[lines][size + 2], int row, int location) {
    for (int i = 0; i < lines; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < size + 2; j++) {
            if (j == size) {
                printf(" csum:");
            }
            if (j == size + 1) {
                printf("usum:");
            }
            if (j >= size) {
                printf("%2d ", tempBoard[i][j]);
            } else if (tempBoard[i][j] == 1) {
                if (lineNumbers[i][j] == lineNumbers[row][location]) {
                    printf("[O]");
                } else {
                    printf(" O ");
                }
            } else if (tempBoard[i][j] == -1) {
                if (lineNumbers[i][j] == lineNumbers[row][location]) {
                    printf("[X]");
                } else {
                    printf(" X ");
                }
            } else {
                if (lineNumbers[i][j] == lineNumbers[row][location]) {
                    printf("[.]");
                } else {
                    printf(" . ");
                }
            }
        }
        printf("  [ ");
        for (int j = 0; j < size; j++) {
            if (scoreboard[i][j] == 0) {
                printf("%d ", lineNumbers[i][j]);
            } else {
                printf(". ");
            }
        }
        printf("]");
        printf("\n");
    }
    printf("\n");
}

void initData() {
    int index = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%2d ", index++);
        }
        printf("\n");
    }
    printf("1. user    2. computer: ");
    scanf("%d", &player);

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            if (i < size) {
                lineNumbers[i][j] = size * i + j + 1;
            } else if (i >= size && i < size * 2) {
                lineNumbers[i][j] = size * j + i % size + 1;
            } else if (i == size * 2) {
                lineNumbers[i][j] = j * size + j % size + 1;
            } else {
                lineNumbers[i][j] = size * (j + 1) - j;
            }
        }
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
        numPick = scanBestScore();
        if (fillNum[numPick - 1] != 0) {
            printf("error: numPick was used\n");
        } else {
            fillNum[numPick - 1] = -1;
        }
        printf("computer picks %d\n", numPick);
    }
}

void updateBoard() {
    for (int i = 0; i < size * size; i++) {
        if (fillNum[i] == 1) {
            printf("%2s ", "o");
        } else if (fillNum[i] == -1) {
            printf("%2s ", "x");
        } else {
            printf("%2d ", i + 1);
        }
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

void updateScore() {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            if (player == 1) {
                if (lineNumbers[i][j] == numPick) {
                    scoreboard[i][j] = 1;
                }
            } else {
                if (lineNumbers[i][j] == numPick) {
                    scoreboard[i][j] = -1;
                }
            }
        }
        scoreboard[i][size] = calculateComputerWeight(i, scoreboard);
        scoreboard[i][size + 1] = calculateUserWeight(i, scoreboard);
    }
}

void updateScore2(int pickBestNum) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            if (player == 1) {
                if (lineNumbers[i][j] == pickBestNum) {
                    scoreboard[i][j] = 1;
                }
            } else {
                if (lineNumbers[i][j] == pickBestNum) {
                    scoreboard[i][j] = -1;
                }
            }
        }
        scoreboard[i][size] = calculateComputerWeight(i, scoreboard);
        scoreboard[i][size + 1] = calculateUserWeight(i, scoreboard);
    }
}

void print() {
    for (int i = 0; i < lines; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < size + 2; j++) {
            printf("%2d ", scoreboard[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // int seq = 1;
    // for (int i = 0; i < 3; i++) {
    //     if (i == 0) {
    //         printf("line#: ");
    //     } else if (i == 1) {
    //         printf("csum:  ");
    //     } else {
    //         printf("usum:  ");
    //     }
    //     for (int j = 0; j < lines; j++) {
    //         if (i == 0) {
    //             printf("%2d ", seq++);
    //         } else {
    //             printf("%2d ", scoreboard[j][size - 1 + i]);
    //         }
    //     }
    //     printf("\n");
    // }
    // printf("\n");
}

int calculateComputerWeight(int rowNum, int tempscoreBoard[lines][size + 2]) {
    int oCount = 0;
    int xCount = 0;
    int nCount = 0;
    int rtnValue = 0;
    for (int i = 0; i < size; i++) {
        if (tempscoreBoard[rowNum][i] == 1) {
            oCount++;
        } else if (tempscoreBoard[rowNum][i] == -1) {
            xCount++;
        } else {
            nCount++;
        }
    }
    if (oCount == 0 && xCount == 0) {
        rtnValue = 1;
    } else if (oCount == 1 && xCount == 0) {
        rtnValue = 3;
    } else if (oCount == 0 && xCount == 1) {
        rtnValue = 7;
    } else if (oCount == 2 && xCount == 0) {
        rtnValue = 15;
    } else if (oCount == 0 && xCount == 2) {
        rtnValue = 31;
    } else if (oCount == 0 && xCount == 3) {
        rtnValue = 63;
    } else if (oCount == 1 && xCount == 1) {
        rtnValue = 0;
    }
    return rtnValue;
}

int calculateUserWeight(int rowNum, int tempscoreBoard[lines][size + 2]) {
    int oCount = 0;
    int xCount = 0;
    int nCount = 0;
    int rtnValue = 0;
    for (int i = 0; i < size; i++) {
        if (tempscoreBoard[rowNum][i] == 1) {
            oCount++;
        } else if (tempscoreBoard[rowNum][i] == -1) {
            xCount++;
        } else {
            nCount++;
        }
    }
    if (oCount == 0 && xCount == 0) {
        rtnValue = 1;
    } else if (oCount == 0 && xCount == 1) {
        rtnValue = 3;
    } else if (oCount == 1 && xCount == 0) {
        rtnValue = 7;
    } else if (oCount == 0 && xCount == 2) {
        rtnValue = 15;
    } else if (oCount == 2 && xCount == 0) {
        rtnValue = 31;
    } else if (oCount == 1 && xCount == 1) {
        rtnValue = 0;
    }
    return rtnValue;
}
