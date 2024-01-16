// This file contains a bunch of micro tests for LB correctness

void main() {
  // test 1
  print(10000) 
  array_correctly_initialize()

  // test 2
  print(20000) 
  shadow(123)

  // test 3: syntax: using function arguments
  print(30000) 
  fun_arg(1)

  // test 4: syntax: while-true-if-return
  print(40000) 
  while_return()

  // test 5: continue after do-while loop
  print(50000) 
  do_while_in_while()
  return
}

void array_correctly_initialize() {
  int64 i
  i <- 0
  while (i < 10) :do :done 
  {
:do
    // arr should be initialized at this point
    int64[] arr
    if (arr = 0) :then :else 
    {
:then
      goto :fi
    } 
    :else 
    {
      // failed
      print(0) 
      return
    }
:fi
    // this value should not flow to next iteration
    arr <- new Array(10)
    i <- i + 1
    continue
  }
:done
  print(1)
  return
}

void shadow(int64 V) {
  int64 result, icmp, orig_V
  code X
  orig_V <- V * 1
  result <- 1
  {
    V <- V + 5
    {
      int64 V
      int64 X
      {
        int64 fun_arg
        fun_arg <- 456
        V <- fun_arg
        X <- fun_arg
      }
      icmp <- X = 456
      V <- V * 3
      result <- result & icmp
    }
    V <- V - 5
    X <- fun_arg
  }
  icmp <- V = orig_V
  result <- result & icmp
  X(result)
  return
}

void fun_arg(int64 x) {
  int64 y
  y <- x
  print(y)
  return
}

void while_return() {
  int64 i
  i <- 0
  while (1 = 1) :do :done 
  {
:do
    if (i > 5) :then :fi 
    {
:then
      print(1)
      return
    }
:fi
    i <- i + 1
    continue
  }
:done
  return 
}

int64 do_while_in_while() {
  int64 i, sum
  i <- 0
  sum <- 0
  while (i < 5) :whil :wend 
  {
    :whil
    i <- i * 1

    :do 
    {
      sum <- sum + i
    } 
    while (0 = 1) :do :done
    :done

    i <- i + 1
    continue
  }
  :wend
  print(1)
  return sum
}
