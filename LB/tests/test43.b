void main (){
  myF(21)
  return 
}

void myF (int64 p){
   int64 v
   v <- p
   {
      int64 v
      v <- p * 2
      {
         int64 v
         v <- 5 
      }
      print(v)
   }
   print(v)
   return
}
