    public static int diceRoll(int n, int outcome) {
        int[][] result = new int[n][];

        for (int i = 0; i < n; i++) {
            result[i] = new int[(i + 1) * 6];
            for (int j = 0; j < (i + 1) * 6; j++) {
                if ((i + 1) == 1) {
                    result[i][j] = 1;
                } else {
                    result[i][j] = totalCount(result, i, j);
                }
            }
        }
        return result[n - 1][outcome - 1];
    }

    private static int totalCount(int[][] array, int row, int col) {
        int count = 0;
        int startCol = col - 6;
        if (startCol < 0) {
            startCol = 0;
        }
        int endCol = col - array[row - 1].length;
        if (endCol < 0) {
            endCol = 0;
        }

        for (int i = row - 1; i < row; i++) {
            for (int j = startCol; j < col - endCol; j++) {
                count += array[i][j];
            }
        }

        return count;
    }
