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
function find_max_range(min1, max1, d_cnt){
max = 0
min = 2000 * 6
  for( starti = min1; starti <= max1; starti++){
    for (c=1; c <=6; c++){
      ci = starti -c;
      print "current index is " ci
      max=find_max(max, ci);
      #min=find_min(max, ci);
    }
  #print "in function : min range is " min
  print "in function : max range is " max
  }
  return max
}
function find_min_range(min1, max1, d_cnt){
max = 0
min = 2000 * 6
  for( starti = min1; starti <= max1; starti++){
    for (c=1; c <=6; c++){
      ci = starti -c;
      print "current index is " ci
      #max=find_max(max, ci);
      min=find_min(max, ci);
    }
  print "in function : min range is " min
  #print "in function : max range is " max
  }
  return min
}
BEGIN{

#  for ( outcome = 1; outcome <= dice_cnt*6; outcome++){
outcome=16
dice_cnt=5
maxi = 0
mini = 5 * 6
  for ( cindex = 1; cindex <= 6; cindex ++){
    ci = outcome - cindex
    print "current index is " ci
    maxi=find_max(maxi, ci);
    mini=find_min(maxi, ci);
    #if (outcome < dice_cnt){
    #  A[ dice_cnt-1  SUBSEP outcome-1 ] = 0
    #} else if (outcome == dice_cnt){
    #  A[ dice_cnt-1 SUBSEP outcome-1 ] = 1
    #} else {
    #}
  }
  print "min range is " mini
  print "max range is " maxi
  maxi = find_max_range(mini, maxi, dice_cnt-1);
  mini = find_min_range(mini, maxi, dice_cnt-1);
  print "min range is " mini
  print "max range is " maxi

}
{ #nothing to do
}
