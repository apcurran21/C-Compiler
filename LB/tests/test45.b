void main(){
  int64 var1,var2,var3,c1,c2
  var1 <- 5
  print(var1)
  var2 <- 1
  var3 <- 0
  :loop
  if(var1 = 0) :else :cont1
  :cont1
  var2 <- var2 * var1
  var1 <- var1 - 1
  if(var1>1) :loop :cont2
  :cont2
  print(var2)
  return
  :else
  print(3)
  return 
 }
