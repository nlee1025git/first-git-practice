BEGIN {
  n = 3;
  outcome = 10;
<<<<<<< HEAD
  range_start = 1
  range_end = n * 6;
=======
  range = 1..3*6;
>>>>>>> 596b6225adfaf148975a4c08ca408e4a1f47d627

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


1st edit

2nd edit
