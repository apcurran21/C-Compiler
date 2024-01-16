 void main(){
  int64 v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11 
  v1 <- 43
  v2 <- 55
  v3 <- 32
  v4 <- 74
  v5 <- 67
  v6 <- 83
  v7 <- 39
  v8 <- 45
  v9 <- 22
  v10 <- 41
  v11 <-  max(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10)
  print(v11)
  return
 }
 int64 max(int64 var0,int64 var1,int64 var2,int64 var3,int64 var4,int64 var5,int64 var6,int64 var7,int64 var8,int64 var9) {
  int64 v0
  v0 <- var0
  if(var1<=v0) :skip1 :cont1
  
  :cont1
  v0 <- var1
  :skip1
  if(var2<=v0) :skip2 :cont2
  
  :cont2
  v0 <- var2
  
  :skip2
  if(var3<=v0) :skip3 :cont3

  :cont3
  v0 <- var5

  :skip3
  if(var4<=v0) :skip4 :cont4
 
  :cont4
  v0 <- var5

  :skip4
  if(var5<=v0) :skip5 :cont5

  :cont5
  v0 <- var5

  :skip5
  if(var6<=v0) :skip6 :cont6

  :cont6
  v0 <- var6

  :skip6
  if(var7<=v0) :skip7 :cont7


  :cont7
  v0 <- var7
  :skip7
  if(var8<=v0) :skip8 :cont8

  :cont8
  v0 <- var8
  :skip8
  if(var9<=v0) :skip9 :cont9

  :cont9
  v0 <- var9
  :skip9
  return v0
 }

