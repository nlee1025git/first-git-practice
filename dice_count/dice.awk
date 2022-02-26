#awk -f dice.awk dice.txt   note: need empty dice.txt file so create one
BEGIN{
  A[ 1 SUBSEP 0 ] = 6
  A[ 1 SUBSEP 0 ] = 1
  A[ 1 SUBSEP 1 ] = 1
  A[ 1 SUBSEP 2 ] = 1
  A[ 1 SUBSEP 3 ] = 1
  A[ 1 SUBSEP 4 ] = 1
  A[ 1 SUBSEP 5 ] = 1
  A[ 1 SUBSEP 6 ] = 1

  A[ 2 SUBSEP 0 ] = 6
  A[ 2 SUBSEP 0 ] = 0
  A[ 2 SUBSEP 1 ] = 0
  A[ 2 SUBSEP 2 ] = 0
  A[ 2 SUBSEP 3 ] = 0
  A[ 2 SUBSEP 4 ] = 0
  A[ 2 SUBSEP 5 ] = 0
  A[ 2 SUBSEP 6 ] = 0

  dice_cnt = 2
  A[ 2 SUBSEP 0 ] = 12
  for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
    if (outcome < dice_cnt){
      A[ 2 SUBSEP outcome ] = 0
    } else if (outcome == dice_cnt){
      A[ 2 SUBSEP outcome ] = 1
    } else {
      if (outcome  <= 7){
            A[ 2 SUBSEP outcome ] = outcome -1 
      } else if (outcome <= 12)  {
            A[ 2 SUBSEP outcome ] = 13 - outcome
      }
    }
  }

  #for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
  #  print "out is " outcome  " possibility is " A[ 2 SUBSEP outcome ]
  #}
#------------first try of generalization------------
  dice_cnt = 2
  A[ 22 SUBSEP 0 ] = dice_cnt*6
  for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
    if (outcome < dice_cnt){
      A[ 22 SUBSEP outcome ] = 0
    } else if (outcome == dice_cnt){
      A[ 22 SUBSEP outcome ] = 1
    } else {
      temp_sum =0
      for (i = 1; i <= 6; i++){
        if (outcome -i > 0){           #for case of outcome is 6 then index can be zero but it is now allowed
        temp_sum += A[ 1 SUBSEP outcome - i] 
        #if (outcome == 6 || outcome == 7 ){
        #    print "o[" outcome "] i " i " temp_sum " temp_sum " a[" outcome -i "] store val " A[ 1 SUBSEP outcome - i] 
        #}
      }
    }
      A[ 22 SUBSEP outcome ] = temp_sum
    }
  }
  #for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
  #  print "out is " outcome  " possibility is " A[ 22 SUBSEP outcome ]
  #}

#------------first try of generalization------------



  dice_cnt = 3
  A[ 3 SUBSEP 0 ] = 18
  for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
    if (outcome < dice_cnt){
      A[ 3 SUBSEP outcome ] = 0
    } else if (outcome == dice_cnt){
      A[ 3 SUBSEP outcome ] = 1
    } else {
      temp_sum =0
      for (i = 1; i <= 6; i++){
        temp_sum += A[ 2 SUBSEP outcome - i] 
      }
      A[ 3 SUBSEP outcome ] = temp_sum
    }
  }
  #for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
  #  print "out is " outcome  " possibility is " A[ 3 SUBSEP outcome ]
  #}

  dice_cnt = 4
  A[ 4 SUBSEP 0 ] = dice_cnt*6
  for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
    if (outcome < dice_cnt){
      A[ 4 SUBSEP outcome ] = 0
    } else if (outcome == dice_cnt){
      A[ 4 SUBSEP outcome ] = 1
    } else {
      temp_sum =0
      for (i = 1; i <= 6; i++){
        temp_sum += A[ 3 SUBSEP outcome - i] 
      }
      A[ 4 SUBSEP outcome ] = temp_sum
    }
  }
  #for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
  #  print "out is " outcome  " possibility is " A[ 4 SUBSEP outcome ]
  #}

#     ---------------------real program--------------------------
max_dice = 200
for (dice_cnt =2 ; dice_cnt <= max_dice; dice_cnt++){ 
  #dice_cnt = 2
  A[ dice_cnt SUBSEP 0 ] = dice_cnt*6
  for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
    if (outcome < dice_cnt){
      A[ dice_cnt SUBSEP outcome ] = 0
    } else if (outcome == dice_cnt){
      A[ dice_cnt SUBSEP outcome ] = 1
    } else {
      temp_sum =0
      for (i = 1; i <= 6; i++){
        if (outcome -i > 0){           #for case of outcome is 6 then index can be zero but it is now allowed
        temp_sum += A[ dice_cnt-1 SUBSEP outcome - i] 
      }
    }
      A[ dice_cnt SUBSEP outcome ] = temp_sum
    }
  }
  #for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
  #  print "out is " outcome  " possibility is " A[ 22 SUBSEP outcome ]
  #}
}
dice_cnt= max_dice 
  for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
    print "out is " outcome  " possibility is " A[ dice_cnt SUBSEP outcome ]
  }
}
#     ---------------------real program--------------------------
{  #nothing to do
}



#      # if 3 is expected outcome:  range starts from 1 to  3-1 : 1 to 2( 3 )  1 2
#                                                                              2 1
#      # if 4 is expected outcome:  range starts from 1 to  4-1 : 1 to 3( 4 )  1 2 3
#                                                                              3 2 1
#      # if 5 is expected outcome:  range starts from 1 to  5-1 : 1 to 4( 5 )  1 2 3 4
#                                                                              4 3 2 1
#      # if 6 is expected outcome:  range starts from 1 to  6-1 : 1 to 5( 6 )  1 2 3 4 5
#                                                                              5 4 3 2 1
#      # if 7 is expected outcome:  range starts from 1 to  7-1 : 1 to 6( 7 )  1 2 3 4 5 6
#                                                                              6 5 4 3 2 1
#      # if 8 is expected outcome:  range starts from 1 to  8-1 : 1 to 6( 8 )  1 2 3 4 5 6 [7]  this is limit
#                                                                                6 5 4 3 2 [1]
#      # if 9 is expected outcome:  range starts from 1 to  9-1 : 1 to 6( 9 )  1 2 3 4 5 6 [7 8]
#                                                                                  6 5 4 3 [2 1]
#     # if 10 is expected outcome:  range starts from 1 to 10-1 : 1 to 6(10 )  1 2 3 4 5 6 [7 8 9 ]
#                                                                                    6 5 4 [3 2 1
#     # if 11 is expected outcome:  range starts from 1 to 11-1 : 1 to 6(11 )  1 2 3 4 5 6 [7 8 9 ]A
#                                                                                      6 5 [4 3 2 ]1
#     # if 12 is expected outcome:  range starts from 1 to 12-1 : 1 to 6(12 )  1 2 3 4 5 6 [7 8 9 ]A B
#                                                                                        6 [5 4 3 ]2 1
#if conunt  2  min 1 + 1 = 2
# 1  0 impossible
# 2  1 mod 6 = 1  2 div 6 = 0          1                
# 3  3 mod 6 = 3  3 div 6 = 0    3-1 = 1 2
# 4  4 mod 6 = 4  4 div 6 = 0    4-1 = 1 2 3
# 5  5 mod 6 = 4  5 div 6 = 0    5-1 = 1 2 3 4
# 6  6 mod 6 = 4  6 div 6 = 1    5-1 = 1 2 3 4 5        
# 7  7 mod 6 = 1  7 div 6 = 1          1 2 3 4 5 6      
# 8  8 mod 6 = 2  8 div 6 = 1            2 3 4 5 6      
# 9  9 mod 6 = 3  9 div 6 = 1              3 4 5 6
#10 10 mod 6 = 4 10 div 6 = 1                4 5 6
#11 11 mod 6 = 5 11 div 6 = 1                  5 6
#12 12 mod 6 = 6 12 div 6 = 1                    1



# for 3 dice problem you have intial 1 to 6 outcome and history of a[2, outcome-i]
#case of 9
#Initial number 1        A[2 supsep 8] = 5
#Initial number 2        A[2 supse  7] = 6
#Initial number 3        A[2 supse  6] = 5
#Initial number 4        A[2 supse  5] = 4
#Initial number 5        A[2 supse  4] = 3
#Initial number 6        A[2 supse  3] = 2


