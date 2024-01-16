void main ()
{
  int64[][] m3
  int64[][] m2
  int64[][] m1
  int64 dim
  dim <- 300
  m1 <- new Array (dim, dim)
  m2 <- new Array (dim, dim)
  m3 <- new Array (dim, dim)
  computeAndPrint(m1, m2, m3, 0)
  return 
}


void computeAndPrint (int64[][] m1, int64[][] m2, int64[][] m3, int64 v1)
{
  initMatrix(m1, v1)
  initMatrix(m2, v1)
  matrixMultiplication(m1, m2, m3)
  int64 t
  t <- totalSum(m1)
  print(t)
  t <- totalSum(m2)
  print(t)
  t <- totalSum(m3)
  print(t)
  return 
}


void initMatrix (int64[][] m, int64 initValue)
{
  int64 index1
  int64 l2
  int64 l1
  l1 <- length m 0
  l2 <- length m 1
  index1 <- 0
  while (index1 < l1) :new_label0 :new_label3 
  :new_label0
  {
    int64 index2
    index2 <- 0
    while (index2 < l2) :new_label1 :new_label2 
    :new_label1
    {
      int64 valueToStore
      valueToStore <- initValue + index1
      valueToStore <- valueToStore + index2
      valueToStore <- valueToStore + index2
      valueToStore <- valueToStore + index2
      valueToStore <- valueToStore + index2
      valueToStore <- valueToStore + index2
      m[index1][index2] <- valueToStore
      index2 <- index2 + 1
    }
    continue
    :new_label2
    index1 <- index1 + 1
  }
  continue
  :new_label3
  return 
}


void matrixMultiplication (int64[][] m1, int64[][] m2, int64[][] m3)
{
  int64 m3_l2
  int64 m3_l1
  int64 m2_l2
  int64 m2_l1
  int64 m1_l2
  int64 m1_l1
  m1_l1 <- length m1 0
  m1_l2 <- length m1 1
  m2_l1 <- length m2 0
  m2_l2 <- length m2 1
  m3_l1 <- length m3 0
  m3_l2 <- length m3 1
  if (m1_l2 = m2_l1) :new_label0 :new_label1 
  :new_label0
  {
  }

  goto :new_label2
  :new_label1
  {
    return 
  }


  :new_label2
  if (m3_l1 = m1_l1) :new_label3 :new_label4 
  :new_label3
  {
  }


  goto :new_label5
  :new_label4
  {
    return 
  }


  :new_label5
  if (m3_l2 = m2_l2) :new_label6 :new_label7 
  :new_label6
  {
  }


  goto :new_label8
  :new_label7
  {
  return 
  }


  :new_label8
  {
    int64 k
    int64 j
    int64 i
    i <- 0
    while (i < m1_l1) :new_label9 :new_label14 
    :new_label9
    {
      j <- 0
      while (j < m2_l2) :new_label10 :new_label13 
      :new_label10
      {
        k <- 0
        while (k < m1_l2) :new_label11 :new_label12 
        :new_label11
        {
	  int64 tmp
	  tmp <- 1
	  tmp <- tmp * 4
	  tmp <- tmp * 4
	  tmp <- tmp * 4
	  tmp <- tmp + 2
	  tmp <- tmp + 2
	  tmp <- tmp + 2
	  tmp <- tmp * 8
	  m3[i][j] <- 0
	  tmp <- m3[i][j]
	  tmp <- tmp + 4
	  tmp <- tmp + 4
	  tmp <- tmp + 4
	  tmp <- tmp + 4
	  m3[i][j] <- tmp
	  tmp <- m3[i][j]
	  tmp <- tmp * 4
	  tmp <- tmp * 4
	  tmp <- tmp * 4
	  tmp <- tmp * 4
	  m3[i][j] <- tmp
	  k <- k + 1
        }
        continue
        :new_label12
        j <- j + 1
      }
      continue
      :new_label13
      i <- i + 1
    }
    continue
    :new_label14
  }

  int64 tot
  int64 k
  int64 j
  int64 i
  i <- 0
  tot <- 0
  while (i < m1_l1) :new_label15 :new_label20 
  :new_label15
  {
    j <- 0
    while (j < m2_l2) :new_label16 :new_label19 
    :new_label16
    {
      k <- 0
      while (k < m1_l2) :new_label17 :new_label18 
      :new_label17
      {
	int64 F
	int64 E
	int64 D
	int64 C
	int64 B
	int64 A
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
	m3[i][j] <- F
	int64 G
	G <- F * 1
	m3[i][j] <- G
	G <- F + 0
	m3[i][j] <- G
	G <- F * 1
	m3[i][j] <- G
	G <- F + 0
	m3[i][j] <- G
	int64 tmp
	tmp <- G
	tmp <- tmp * 4
	tmp <- tmp + 2
	tmp <- tmp * 8
	tmp <- tmp * 4
	tmp <- tmp + 2
	tmp <- tmp * 8
	tmp <- tmp * 3
	tmp <- tmp * 3
	tmp <- tmp * 3
	tmp <- tmp * 3
	tmp <- tmp * 3
	tmp <- tmp * 3
	tmp <- tmp * 3
	tmp <- tmp * 4
	tmp <- tmp + 2
	tmp <- tmp * 8
	tmp <- tmp * 4
	tmp <- tmp + 2
	tmp <- tmp * 8
	tmp <- tmp * 4
	tmp <- tmp + 2
	tmp <- tmp * 8
	tmp <- tmp * 4
	tmp <- tmp + 2
	tmp <- tmp * 8
	tmp <- tmp << 2
	tmp <- tmp + 2
	tmp <- tmp * 8
	tmp <- tmp * 4
	tmp <- tmp << 2
	tmp <- tmp + 2
	tmp <- tmp * 8
	tmp <- tmp * 4
	tmp <- tmp << 4
	tmp <- tmp + 2
	tmp <- tmp >> 2
	tmp <- tmp * 8
	tmp <- tmp * 4
	tmp <- tmp + 2
	tmp <- tmp * 8
	tmp <- tmp * 4
	tmp <- tmp + 2
	tmp <- tmp * 8
	int64 tot3
	int64 tot2
	tot2 <- tot * 4
	tot3 <- tot2 + 2
	tot <- tot
	k <- k + 1
      }
      continue
      :new_label18
      j <- j + 1
    }
    continue
    :new_label19
    i <- i + 1
  }
  continue
  :new_label20
  return 
}


int64 totalSum (int64[][] m)
{
  int64 sum
  int64 index1
  int64 l2
  int64 l1
  l1 <- length m 0
  l2 <- length m 1
  index1 <- 0
  sum <- 0
  while (index1 < l1) :new_label0 :new_label3 
  :new_label0
  {
    int64 index2
    index2 <- 0
    while (index2 < l2) :new_label1 :new_label2 
    :new_label1
    {
      int64 temp
      temp <- m[index1][index2]
      sum <- sum + temp
      index2 <- index2 + 1
    }
    continue
    :new_label2
    index1 <- index1 + 1
  }
  continue
  :new_label3
  return sum
}
