BEGIN {
  n = 3;
  outcome = 1..3*6;

  for (i = 0; i < n; i++) {       // dice number
    for (j = 0; j < (i + 1) * 6; j++) {
      if (i == 0) {
        A[i SUBSEP j] = 1
      } else {
        //need to run for 1 to 6
        A[i SUBSEP j] = look at one less dice outcome probability
      }
      print A[i SUBSEP j]
    }
    print " "
  }

 
  for (i in A) {
    print i, A[i]
  }
}
{}
