// print the Fibonacci sequence (10 elems)
// stored in an array, so the first two are #dim and #len of dim[0]
// expected output:
// {s:12, 1, 10, 0, 1, 1, 2, 3, 5, 8, 13, 21, 34} 

void main () {
  int[] arr
  int input, cursor, cursor_p, cursor_pp
  int temp, sum

  input <- 10
  if (input < 2) {
    return
  } else {
    arr <- new Array(input)
    arr[0] <- 0
    arr[1] <- 1
    cursor <- 2
    while (cursor < input) {
      cursor_pp <- cursor - 2
      cursor_p <- cursor - 1
      temp <- arr[cursor_pp]
      sum <- temp
      temp <- arr[cursor_p]
      sum <- sum + temp
      arr[cursor] <- sum
      cursor <- cursor + 1 
    }
    print(arr)
  }
  return
}