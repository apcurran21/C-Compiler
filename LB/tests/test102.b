void main ()
{
  int64 i
  i <- 10
  while (i > 0) :new_label0 :new_label1 
    :new_label0
    print(i)
    i <- i - 1
    continue

  :new_label1
  return 
}
