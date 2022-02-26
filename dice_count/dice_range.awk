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
