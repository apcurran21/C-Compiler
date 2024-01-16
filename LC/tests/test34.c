void main ( ){
  int i
  i <- 10

  while (i > 0) {
    print(i)
    i <- i - 1
    if (i > 2){
      print(3)
      break
    } else {
      print(5)
    }
  }

  return
}
