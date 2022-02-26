#awk -f dice_range.awk dice.txt   note: need empty dice.txt file so create one
function find_max( num1, num2){
    if ( num1 < num2){
      return num2
    }
    return num1
}
function find_min(num1, num2){
    if ( num1 > num2 ){
      return num2
    }
    return num1
}


function find_grid(d_cnt){

    max_d_cnt =200
    # case of 4
    for(dice_cnt = 2 ; dice_cnt<= max_d_cnt; dice_cnt++){ 
         print "start of " dice_cnt
         d_n = dice_cnt -1
         pos = dice_cnt 
         for( j= d_n; j <= 6*d_n ; j++){
           #bline=""
           for( i= 1; i <= 6 ; i++){
             if (d_n == 1) {
                  grid[d_n SUPSEP "count" SUPSEP j ] = 1.0
             }
             j_cnt = grid[d_n SUPSEP "count" SUPSEP j ]
             #bline=bline " "sprintf("[%4.0f-%4.0f](%d)[%4.0f.%4.0f](%d)", i,j,pos,i,j,j_cnt)
             grid[pos SUPSEP i SUPSEP j ] = i + j
             grid[pos SUPSEP "count" SUPSEP i+j ] += j_cnt
           }
           #print "j " bline
         }
         
         for( j= d_n; j <= 6*d_n ; j++){
         aline = ""
           for( i= 1; i <= 6 ; i++){
          #   aline = aline " " sprintf("%4.0f", grid[pos SUPSEP i SUPSEP j ])
             #aline = aline " " sprintf("%4.0f(%4.0f)", grid[pos SUPSEP i SUPSEP j ], grid[pos SUPSEP "count" SUPSEP i+j])
             #aline = aline " " sprintf("%4.0f-%4.0f",grid[pos SUPSEP "count" SUPSEP i+j], grid[pos SUPSEP i SUPSEP j ])
           }
         i#print sprintf("%4.0f",j) ": " aline
         }
         for( j = pos; j <= pos; j++){
              if (pos == 190){
                aline = ""
                for( i= j; i <= 6*j ; i++){
                  aline = aline " " sprintf("%4.0f", grid[pos SUPSEP "count" SUPSEP i ])
                }
                print sprintf("%4.0f",j)  ": " aline
              }
         }
    }
}






#function find_grid(d_cnt){
#    pos = 2
#    for( j = 1; j <= 6; j++){
#      for( i= 1; i <= 6 ; i++){
#        grid[pos SUPSEP i SUPSEP j ] = i + j
#        grid[pos SUPSEP "count" SUPSEP i+j ] += 1
#      }
#    }
#    
#    for( j = 1; j <= 6; j++){
#    aline = ""
#      for( i= 1; i <= 6 ; i++){
#        aline = aline " " sprintf("%3d",      grid[pos SUPSEP i SUPSEP j ])
#        #aline = aline " " sprintf("%3d(%3d)", grid[pos SUPSEP i SUPSEP j ], grid[pos SUPSEP "count" SUPSEP i+j])
#      }
#    print j ": " aline
#    }
#    for( j = 2; j <= 2; j++){
#    aline = ""
#      for( i= j; i <= 6*j ; i++){
#        aline = aline " " sprintf("%3d", grid[pos SUPSEP "count" SUPSEP i ])
#      }
#    print j ": " aline
#    }
# #case of d=3 
#    dice_cnt =3
#    print "start of " dice_cnt
#    d_n = dice_cnt -1
#    pos = dice_cnt 
#    for( j= d_n; j <= 6*d_n ; j++){
#      #bline=""
#      for( i= 1; i <= 6 ; i++){
#        j_cnt = grid[d_n SUPSEP "count" SUPSEP j ]
#        #bline=bline " "sprintf("[%3d-%3d](%d)[%3d.%3d](%d)", i,j,pos,i,j,j_cnt)
#        grid[pos SUPSEP i SUPSEP j ] = i + j
#        grid[pos SUPSEP "count" SUPSEP i+j ] += j_cnt
#      }
#      #print "j " bline
#    }
#    
#    for( j= d_n; j <= 6*d_n ; j++){
#    aline = ""
#      for( i= 1; i <= 6 ; i++){
#        aline = aline " " sprintf("%3d", grid[pos SUPSEP i SUPSEP j ])
#        #aline = aline " " sprintf("%3d(%3d)", grid[pos SUPSEP i SUPSEP j ], grid[pos SUPSEP "count" SUPSEP i+j])
#        #aline = aline " " sprintf("%3d-%3d",grid[pos SUPSEP "count" SUPSEP i+j], grid[pos SUPSEP i SUPSEP j ])
#      }
#    print sprintf("%3d",j) ": " aline
#    }
#    for( j = pos; j <= pos; j++){
#    aline = ""
#      for( i= j; i <= 6*j ; i++){
#        aline = aline " " sprintf("%3d", grid[pos SUPSEP "count" SUPSEP i ])
#      }
#    print sprintf("%3d",j)  ": " aline
#    }
#
#
#
## case of 4
#    dice_cnt =2
#    print "start of " dice_cnt
#    d_n = dice_cnt -1
#    pos = dice_cnt 
#    for( j= d_n; j <= 6*d_n ; j++){
#      #bline=""
#      for( i= 1; i <= 6 ; i++){
#        j_cnt = grid[d_n SUPSEP "count" SUPSEP j ]
#        #bline=bline " "sprintf("[%3d-%3d](%d)[%3d.%3d](%d)", i,j,pos,i,j,j_cnt)
#        grid[pos SUPSEP i SUPSEP j ] = i + j
#        grid[pos SUPSEP "count" SUPSEP i+j ] += j_cnt
#      }
#      #print "j " bline
#    }
#    
#    for( j= d_n; j <= 6*d_n ; j++){
#    aline = ""
#      for( i= 1; i <= 6 ; i++){
#        aline = aline " " sprintf("%3d", grid[pos SUPSEP i SUPSEP j ])
#        #aline = aline " " sprintf("%3d(%3d)", grid[pos SUPSEP i SUPSEP j ], grid[pos SUPSEP "count" SUPSEP i+j])
#        #aline = aline " " sprintf("%3d-%3d",grid[pos SUPSEP "count" SUPSEP i+j], grid[pos SUPSEP i SUPSEP j ])
#      }
#    print sprintf("%3d",j) ": " aline
#    }
#    for( j = pos; j <= pos; j++){
#    aline = ""
#      for( i= j; i <= 6*j ; i++){
#        aline = aline " " sprintf("%3d", grid[pos SUPSEP "count" SUPSEP i ])
#      }
#    print sprintf("%3d",j)  ": " aline
#    }
#
#
#
#}






function find_range(min1, max1, d_cnt){
t[max] = 0
t[min] = 2000 * 6
  for( starti = min1; starti <= max1; starti++){
    print "in function : currnt number is " starti
    for (c=1; c <=6; c++){
      ci = starti -c;
      print "current index is " ci
      t[max]=find_max(t[max], ci);
      t[min]=find_min(t[min], ci);
    }
  print "in function : min range is " t[min]
  print "in function : max range is " t[max]
  }
  return t[max]
}
BEGIN{

#  for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
outcome=16
dice_cnt=5

find_grid(dice_count)
print "Chris Chu"; exit 1;




t[maxi] = 0
t[mini] = 5 * 6
  for ( cindex = 1; cindex <= 6; cindex ++){
    ci = outcome - cindex
    #print "current index is " ci
    t[maxi]=find_max(t[maxi], ci);
    t[maxi]=find_min(t[maxi], ci);
    #if (outcome < dice_cnt){
    #  A[ dice_cnt-1  SUBSEP outcome-1 ] = 0
    #} else if (outcome == dice_cnt){
    #  A[ dice_cnt-1 SUBSEP outcome-1 ] = 1
    #} else {
    #}
  }
  print "before: min range is " mini
  print "before: max range is " maxi
  t = find_range(mini, maxi, dice_cnt-1);
  t[maxi]
  t[mini]
  print "after:  min range is " t[mini]
  print "after:  max range is " t[maxi]

}
{ #nothing to do
}
#function find_min_range(min1, max1, d_cnt){
#max = 0
#min = 2000 * 6
#  for( starti = min1; starti <= max1; starti++){
#    for (c=1; c <=6; c++){
#      ci = starti -c;
#      print "current index is " ci
#      #max=find_max(min, ci);
#      min=find_min(min, ci);
#    }
#  print "in function : min range is " min
#  #print "in function : max range is " max
#  }
#  return min
#}
