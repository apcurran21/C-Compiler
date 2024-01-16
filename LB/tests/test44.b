void main()
{
   int64 number, exp
   number <- 3
   exp <- 8
   array(number, exp)
   return
}

void array(int64 n, int64 e)
{
   int64 index, value
   index <- -1
   while (index < e) :array_begin :array_end
   :array_begin
   index <- index + 1
   value <- calculate(n, index)
   print (value)
   continue
   :array_end
   return
}

int64 calculate(int64 n, int64 e)
{
   int64 index, output
   output <- 1
   index <- 0
   while (index < e) :loop_begin :loop_end
   :loop_begin
   output <- output * n
   index <- index + 1
   continue
   :loop_end
   return output
}