// This program generates two array of positive integers
// in fact, two **tuples**
// and then concatenate them
// {s:5, 1,2,3,4,5}
// {s:5, 6,7,8,9,10}
// {s:10, 1,2,3,4,5,6,7,8,9,10}

void main () {
  tuple t1, t2, t3
  t1 <- range(1, 6)
  t2 <- range(6, 11)
  t3 <- concat(t1, 5, t2, 5)

  print(t1)
  print(t2)
  print(t3)
  return
}

tuple range (int from, int to) {
  int len
  len <- to - from
  tuple t
  t <- new Tuple(len)

  int num, index
  index <- 0
  num <- from

  while (index < len) {
    t[index] <- num
    index <- index + 1
    num <- num + 1
  }

  return t
}

tuple concat (tuple t1, int len1, tuple t2, int len2) {
  tuple t3
  int len3
  len3 <- len1 + len2
  t3 <- new Tuple(len3)

  int index1, index2, index3, temp
  index1 <- 0
  index2 <- 0
  index3 <- 0

  while (index1 < len1) {
    temp <- t1[index1]
    t3[index3] <- temp
    index1 <- index1 + 1
    index3 <- index3 + 1
  }

  while (0 = 0) {
    if (index2 < len2) {
      temp <- t2[index2]
      t3[index3] <- temp
      index2 <- index2 + 1
      index3 <- index3 + 1
    } else {
      break
    }
  }

  return t3
}