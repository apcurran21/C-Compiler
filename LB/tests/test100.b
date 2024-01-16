// test "function-as-arg"
// expected: {s:5, 1, 3, 12, 14, 16} 

int64 double (int64 v) {
  v <- v * 2
  return v
}

int64 plus_10 (int64 v) {
  v <- v + 10
  return v
}

void map (int64[] arr, code f) {
  int64 len, i, v
  len <- length arr 0
  i <- 0

  while (i < len) :loop :end
    :loop
    v <- arr[i]
    v <- f(v)
    arr[i] <- v
    i <- i + 1
    continue

  :end
  return
}

void main () {
  int64[] a
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
