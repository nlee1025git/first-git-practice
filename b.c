#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 5
#define lines size * 2 + 3

int board[size][size] = {0};
int filledOne[size * size] = {0};
int lineNumber[lines][size] = {0};
int twoNumber[lines][size] = {0};
int overlapNumber[size][size] = {0};

void initData();
void setLineNums();
void printLineNums();
void setOverlapNums();
void printOverlapNums();
int getHighestNumIndex();
void updateBoard();
void removeLineNum(int pickNum);
int checkTwo();
void insert(int pickNum, int playFirst);
void checkWinner();

int main() {
    srand(time(0));
    initData();
    setLineNums();
    // printLineNums();
    // printf("\n");
    setOverlapNums();
    // printOverlapNums();

    int playFirst;
    int pickNum;
    int count = 0;

    printf("who plays first?\n");
    printf("1.user    2. computer: ");
    scanf("%d", & playFirst);

    while (1) {
        if (playFirst == 1) {
            int con = 0;
            do {
                con = 0;
                printf("enter a num: ");
                scanf("%d", &pickNum);
                if (filledOne[pickNum - 1] == 0) {
                    filledOne[pickNum - 1] = 1;
                    con = 1;
                }
            } while (con == 0);
            // } while (filledOne[pickNum - 1] == 0 || filledOne[pickNum - 1] == 2);
            // printf("user: %d\n\n", pickNum);
        } else if (playFirst == 2) {
            // int temp = checkTwo();
            // printf("temp is %d\n", temp);
            int con = 0;
            do {
                con = 0;
                pickNum = checkTwo();
                // pickNum = getHighestNumIndex();
                if (filledOne[pickNum - 1] == 0) {
                    filledOne[pickNum - 1] = 2;
                    con = 2;
                    // filledOne[pickNum - 1] = 2;
                }
                // printf("inside com: %d\n", pickNum);
            } while(con == 0);
            // } while(filledOne[pickNum - 1] == 0 || filledOne[pickNum - 1] == 1);
            // printf("com: %d\n\n", pickNum);
        }
        insert(pickNum, playFirst);
        updateBoard();
        removeLineNum(pickNum);
        checkWinner();

        // printf("\n---------\n");
        // printOverlapNums();
        // printf("---------\n");

        // printf("=================\n");
        // printOverlapNums();
        // printf("=================\n");

        if (playFirst == 1) {
            playFirst = 2;
        } else if (playFirst == 2) {
            playFirst = 1;
        }

        count++;
        // printf("count is %d\n", count);
        if (count == size * size) {
            printf("\n*** draw game ***\n");
            break;
            // exit(0);
        }
    }

    return 0;
}

void initData() {
    int index = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = index;
            printf("%2d ", board[i][j]);
            index++;
        }
        printf("\n");
    }
    printf("\n");
}

void setLineNums() {
    for (int i = 1; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            if (i <= size) {
                lineNumber[i][j] = board[i - 1][j];
            } else if (i > size && i <= size * 2) {
                lineNumber[i][j] = board[j][(i - 1) % size];
            } else if (i == size * 2 + 1) {
                lineNumber[i][j] = board[j][j];
            } else {
                lineNumber[i][j] = board[j][size - j - 1];
            }
        }
    }
}

void printLineNums() {
    for (int i = 1; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            printf("%2d ", lineNumber[i][j]);
        }
        printf("\n");
    }
}

void setOverlapNums() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            overlapNumber[i][j] = (size - 1) * 2 + 1;
            if (i == j || size - i - 1 == j) {
                overlapNumber[i][j] = (size - 1) * 3 + 1;
            }
        }
    }
    if (size % 2 == 1) {
        overlapNumber[size / 2][size / 2] = (size - 1) * 4 + 1;
    }
}

void printOverlapNums() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%2d ", overlapNumber[i][j]);
        }
        printf("\n");
    }
}

int getHighestNumIndex() {
    int high = 0;
    int count = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (high < overlapNumber[i][j]) {
                if (filledOne[size * i + j] == 0) {
                    high = overlapNumber[i][j];
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (overlapNumber[i][j] == high) {
                if (filledOne[size * i + j] == 0) {
                    count++;
                }
            }
        }
    }

    int highNums[count];
    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (overlapNumber[i][j] == high) {
                if (filledOne[size * i + j] == 0) {
                    highNums[index] = board[i][j];
                    index++;
                }
            }
        }
    }


    // printf("\n**************\n");
    // for (int i = 0; i < count; i++) {
    //     printf("%d ", highNums[i]);
    // }
    // printf("\n**************\n");
    
    int randNum = rand() % count;
    // printf("randnum: %d\n", randNum);
    // printf("count: %d\n", count);
    // printf("highestNum[index]: %d\n", highNums[randNum]);

    return highNums[randNum];
}

void updateBoard() {
    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (filledOne[index] == 1) {
                printf("%2s ", "o");
            } else if (filledOne[index] == 2) {
                printf("%2s ", "x");
            } else {
                printf("%2d ", index + 1);
            }
            index++;
        }
        printf("\n");
    }
    printf("\n");
}

void removeLineNum(int pickNum) {
    if (board[(pickNum - 1) / size][(pickNum - 1) % size] == pickNum) {
        // printf("this is a num: %d\n", board[pickNum / size][(pickNum - 1) % size]);
        overlapNumber[(pickNum - 1) / size][(pickNum - 1) % size] -= 99;
    }

    int count = 0;
    for (int i = 1; i < lines; i++) {
        int line = 0;
        for (int j = 0; j < size; j++) {
            if (lineNumber[i][j] == pickNum) {
                line = i;
                count++;
            }
        }
        
        if (line > 0) {
            for (int j = 0; j < size; j++) {
                // row 1, 2, 3
                if (line <= size) {
                    overlapNumber[line - 1][j] -= 1;
                // col 4, 5, 6
                } else if (line > size && line <= 2 * size) {
                    overlapNumber[j][(line - 1) % size] -= 1;
                // diagonal 7, 8
                } else if (line > 2 * size) {
                    if (line == size * 2 + 1) {
                        overlapNumber[j][j] -= 1;
                    } else if (line == size *2 + 2) {
                        overlapNumber[j][size - 1 - j] -= 1;
                    }
                }
            }
        }
    }
    overlapNumber[(pickNum - 1) / size][(pickNum - 1) % size] += (count - 1);
}

void insert(int pickNum, int playFirst) {
    for (int i = 1; i < lines; i++) {
        for (int j = 0; j < size; j++) {
            if (lineNumber[i][j] == pickNum) {
                twoNumber[i][j] = playFirst;
            }
        }
    }
}

int checkTwo() {
    // printf("============\n");
    // for (int i = 0; i < size * size; i++) {
    //     printf("%d ", filledOne[i]);
    // }
    // printf("\n===========\n");

    // printf("\n===========\n");
    // for (int i = 1; i < lines; i++) {
    //     for (int j = 0; j < size; j++) {
    //         printf("%d ", twoNumber[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n===========\n");

    for (int i = 1; i < lines; i++) {
        int c = 0;
        int x = 0;
        int y = 0;
        for (int j = 0; j < size; j++) {
            if (twoNumber[i][j] == 2) {
                c++;
            } else {
                if (i <= size) {
                    x = (i - 1) % size;
                    y = j;
                } else if (i > size && i <= size * 2) {
                    x = j;
                    y = (i - 1) % size;
                } else if (i == size * 2 + 1) {
                    x = j;
                    y = j;
                } else if (i == size * 2 + 2) {
                    x = j % size;
                    y = (i % size) - j;
                }
            }
        }
        if (c == size - 1 && filledOne[size * x + y] == 0) {
            // printf("2's i: %d\n", i);
            // printf("2's x: %d, y: %d\n", x, y);
            return board[x][y];
        }
    }

    for (int i = 1; i < lines; i++) {
        int c = 0;
        int x = 0;
        int y = 0;
        for (int j = 0; j < size; j++) {
            if (twoNumber[i][j] == 1) {
                c++;
            } else {
                if (i <= size) {
                    x = (i - 1) % size;
                    y = j;
                } else if (i > size && i <= size * 2) {
                    x = j;
                    y = (i - 1) % size;
                } else if (i == size * 2 + 1) {
                    x = j;
                    y = j;
                } else if (i == size * 2 + 2) {
                    x = j % size;
                    y = (i % size) - j;
                }
            }
        }
        // printf("x is %d, y is %d\n", x, y);
        if (c == size - 1 && filledOne[size * x + y] == 0) {
            // printf("1's i: %d\n", i);
            // printf("1's x: %d, y: %d\n", x, y);
            return board[x][y];
        }
    }

    return getHighestNumIndex();
}

void checkWinner() {
    for (int i = 0; i < lines; i++) {
        int user = 0;
        int computer = 0;
        for (int j = 0; j < size; j++) {
            if (twoNumber[i][j] == 1) {
                user++;
            }
            if (twoNumber[i][j] == 2) {
                computer++;
            }
        }
        if (user == size) {
            printf("user wins\n");
            exit(0);
        }
        if (computer == size) {
            printf("computer wins\n");
            exit(0);
        }
    }
}