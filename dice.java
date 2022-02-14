    public static int diceRoll(int n, int outcome) {
        int[][] result = new int[n][];    // n is dice_count

        for (int i = 0; i < n; i++) {     // when i=0 this is first dice
            result[i] = new int[(i + 1) * 6];
            for (int j = 0; j < (i + 1) * 6; j++) {  // j is moving from 0 to 5
                if ((i + 1) == 1) {
                    result[i][j] = 1;                 //if i=0 then all case 1, this covers i=0......
                } else {
                    result[i][j] = totalCount(result, i, j);   //case: dice_count = 2, j move from 0 to 11, i = 1 means two dice
                }
            }
        }
        return result[n - 1][outcome - 1];
    }

    private static int totalCount(int[][] array, int row, int col) {       //case dice 2 j move from 0 to 11 i =1
                                                //  row =i    col=j
        int count = 0;
        int startCol = col - 6;    //startCol = col-6
        if (startCol < 0) {        //special case for startCol is less than zero
            startCol = 0;
        }
        int endCol = col - array[row - 1].length;   //row -1  dice one less  ???
        if (endCol < 0) {
            endCol = 0;
        }

        for (int i = row - 1; i < row; i++) {                          //
            for (int j = startCol; j < col - endCol; j++) {
                count += array[i][j];
            }
        }

        return count;
    }



-------------------------------------------------

BEGIN {
  n = 3;
  outcome = 10;

  for (i = 0; i < n; i++) {
    for (j = 0; j < (i + 1) * 6; j++) {
      if ((i + 1) == 1) {
        A[i SUBSEP j] = 1
      } else {
        A[i SUBSEP j] = (i + 1)
      }
      print A[i SUBSEP j]
    }
    print " "
  }

  print "1) " A[0 SUBSEP 2]
  print "2) " A[2 SUBSEP 17]
  print "3) " A[0 SUBSEP]

  for (i in A) {
    print i, A[i]
  }
}
{}
