// Test of nested tuple
// Expected outout: Pascal's triangle
// {s:6, {s:1, 1}, {s:2, 1, 1}, {s:3, 1, 2, 1}, {s:4, 1, 3, 3, 1},
// {s:5, 1, 4, 6, 4, 1}, {s:6, 1, 5, 10, 10, 5, 1}}

void main () {
  tuple triangle, row, row_above
  int64 i, j, size
  size <- 6

  triangle <- new Tuple(size)
  i <- 0
  while (i < size) :loop_out :end 
  {
    :loop_out
    int64 row_len, last

    last <- i
    row_len <- i + 1
    row <- new Tuple(row_len)

    row[0] <- 1
    row[last] <- 1
    j <- 1
    
    while (j < last) :loop_in :next 
    {
      :loop_in
      int64 temp, sum, k
      k <- j - 1
      temp <- row_above[k]
      sum <- temp
      temp <- row_above[j]
      sum <- sum + temp
      row[j] <- sum
      j <- j + 1
      continue
    }

    :next
    triangle[i] <- row
    row_above <- row
    i <- i + 1
    continue
  }

  :end
  print(triangle)
  return
}
