void main() {
  int64 i
  i <- 0

  while (i < 10) :whil :wend 
  {
    :whil

    :do
    {
      print(i)
    } 
    while (0 = 1) :do :done
    :done

    i <- i + 1
    continue
  }

  :wend
  return
}
