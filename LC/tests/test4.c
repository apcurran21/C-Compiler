void main ( ){

  // Fetch the input size
  int dim
  dim <- input()
  print(dim)

  // Allocate the matrices
  int[][] m1, m2, m3
  m1 <- new Array(dim, dim)
  m2 <- new Array(dim, dim)
  m3 <- new Array(dim, dim)

  // Compute
  computeAndPrint(m1, m2, m3)
}

void computeAndPrint (int[][] m1, int[][] m2, int[][] m3){

  // Initialize the matrices
  initMatrix(m1)
  initMatrix(m2)

  // Multiple the matrices
  matrixMultiplication(m1, m2, m3)
  matrixMultiplication(m3, m2, m1)
  matrixMultiplication(m3, m1, m2)
  matrixMultiplication(m1, m2, m3)
  matrixMultiplication(m3, m2, m1)
  matrixMultiplication(m3, m1, m2)

  // Compute the total sum
  int t
  t <-  totalSum(m1)
  print(t)
  t <-  totalSum(m2)
  print(t)
  t <-  totalSum(m3)
  print(t)
}

void initMatrix (int[][] m){

  // Fetch the lengths
  int l1, l2, index1
  l1 <- length m 0
  l2 <- length m 1

  // Iterate over the rows
  while (index1 < l1) {
    int index2

    // Iterate over the columns
    while (index2 < l2) {
  
      // Compute the value to store
      int valueToStore
      valueToStore <- input()
  
      // Store the value to the current matrix element
      m[index1][index2] <- valueToStore

      index2 <- index2 + 1
    }

    index1 <- index1 + 1
  }
}

void matrixMultiplication (int[][] m1, int[][] m2, int[][] m3){

  // Fetch the lengths
  int m1_l1, m1_l2, m2_l1, m2_l2, m3_l1, m3_l2
  m1_l1 <- length m1 0
  m1_l2 <- length m1 1
  m2_l1 <- length m2 0
  m2_l2 <- length m2 1
  m3_l1 <- length m3 0
  m3_l2 <- length m3 1

  // Check the length
  if (m1_l2 = m2_l1) {
  } else {
    return 
  }
  if (m3_l1 = m1_l1) {
  } else {
    return 
  }
  if (m3_l2 = m2_l2) {
  } else {
    return 
  }

  // Initialize the result matrix
  {
    int i, j
    while (i < m3_l1) {
      j <- 0
      while (j < m3_l2) {
        m3[i][j] <- 0
        j <- j + 1
      }
      i <- i + 1
    }
  }

  // Multiply the matrices
  int tot
  int i, j, k
  while (i < m1_l1) {
    j <- 0
    while (j < m2_l2) {
      k <- 0
      while (k < m1_l2) {
        int A, B, C, D, E, F
        A <- m1[i][k]
        B <- m2[k][j]
        C <- A * B
        D <- m3[i][j]
        E <- D * 4
        E <- E * 3
        E <- E * 3
        E <- E * 3
        E <- E * 3
        E <- E * 3
        F <- E + 2
        F <- F << 1
        F <- F << 1
        F <- F * 2
        F <- F + 1
        F <- F << 1
        F <- F << 1
        F <- F * 2
        F <- F + 1

        m3[i][j] <- F

        k <- k + 1
      }

      j <- j + 1
    }

    i <- i + 1
  }
}

int totalSum (int[][] m){
  int sum
 
  // Fetch the lengths
  int l1, l2, index1
  l1 <- length m 0
  l2 <- length m 1

  // Iterate over the rows
  while (index1 < l1) {
    int index2
    index2 <- 0

    // Iterate over the columns
    while (index2 < l2) {
  
      // Sum the current value
      int temp
      temp <- m[index1][index2]
      sum <- sum + temp

      index2 <- index2 + 1
    }

    index1 <- index1 + 1
  }

  return sum
}
