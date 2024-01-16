// test "function-as-arg"
// expected: {s:5, 1, 3, 12, 14, 16} 

int double (int v) {
  v <- v * 2
  return v
}

int plus_10 (int v) {
  v <- v + 10
  return v
}

void map (int[] arr, code f) {
  int len, i, v
  len <- length arr 0
  i <- 0

  while (i < len) {
    v <- arr[i]
    v <- f(v)
    arr[i] <- v
    i <- i + 1
    continue
    i <- i + 1 // should not be executed
  }

  return
}

void main () {
  int[] a
  code func

  a <- new Array(3)
  a[0] <- 1
  a[1] <- 2
  a[2] <- 3
  func <- double
  map(a, func)
  func <- plus_10
  map(a, func)

  print(a)
  return
}