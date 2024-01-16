// test array error
// expected: 
// {s:15, 2, 3, 4, 11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34}
// attempted to use position 4 (linearized array length: 15) 

void main () {
  int[][] arr
  arr <- init(3, 4)
  print(arr)

  int v
  v <- arr[1][4] // out of range
  print(v) // should not print arr[2][0] == 31

  return
}

int[][] init (int rows, int cols) {
  int[][] ret
  ret <- new Array(rows, cols)
  int i, j, x
  i <- 0

  while (i < rows) {
    j <- 0
    while (j < cols) {
      x <- i * 10
      x <- x + j
      x <- x + 11
      ret[i][j] <- x
      j <- j + 1
    }
    i <- i + 1
  }

  return ret
}