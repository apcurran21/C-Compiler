void main() {
  int64 i
  i <- 0

  while (i < 10) :whil :wend 
  {
    i <- 1
    :whil

    print(i)

    i <- i + 1
    continue
  }

  :wend
  return
}
