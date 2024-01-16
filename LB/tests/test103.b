void main ()
{
  int64 i
  i <- 10
  while (i > 0) :new_label0 :new_label1 
    :new_label0
    print(i)
    i <- i - 1
    if (i > 2) :true_label :false_label
      :true_label
      break 

      :false_label
      i <- i - 1

    continue

  :new_label1
  return 
}
