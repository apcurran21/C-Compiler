// This program prints out two arrays:
//  an array of square numbers
//  and another with reversed order
//   (each array has 5 elements).
// {s:5,1,4,9,16,25}
// {s:5,25,16,9,4,1}
// We'll use tuple instead of array this time.

void main() {
  tuple t
  int t_len
  t_len <- 5

  t <- init_tuple(t_len)
  print(t)

  reverse_tuple(t, t_len)
  print(t)
  return
}

tuple init_tuple(int t_len) {
  tuple t
  t <- new Tuple(t_len)
  int i
  i <- 0
  while (i < t_len) {
    int x
    x <- i + 1
    x <- x * x
    t[i] <- x
    i <- i + 1
  }
  return t
}

void reverse_tuple(tuple t, int t_len) {
  int i, j
  i <- 0
  j <- t_len - 1
  while (i < j) {
    int x, y
    x <- t[i]
    y <- t[j]
    t[i] <- y
    t[j] <- x
    i <- i + 1
    j <- j - 1
  }
  return
}