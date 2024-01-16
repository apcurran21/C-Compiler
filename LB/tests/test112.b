tuple vec_ctor() {
    tuple res
    int64[][] buf
    res <- new Tuple(3)
    res[0] <- 0
    // initialized to 0
    int64[][][] empty_array 
    res[1] <- empty_array
    buf <- new Array(2,2)
    res[2] <- buf
    return res
}

void memcp32(int64[][][] ptr, int64 idx, int64[][] buf) {
    int64 i
    i <- 0
    while (i <= 1) :I :eoi
    {
:I
        int64 j
        j <- 0
        while (j <= 1) :J :eoj
        {
:J
            int64 n
            n <- ptr[idx][i][j]
            buf[i][j] <- n
            j <- j + 1
            continue
        }
:eoj
        i <- i + 1
        continue
    }
:eoi
    return
}

void memcp23(int64[][] buf, int64[][][] qtr, int64 idx) {
    int64 i
    i <- 1
    while (i >= 0) :I :eoi
    {
:I
        int64 j
        j <- 1
        while (j >= 0) :J :eoj
        {
:J
            int64 n
            n <- buf[j][i]
            qtr[idx][j][i] <- n
            j <- j - 1
            continue
        }
:eoj
        i <- i - 1
        continue
    }
:eoi
    return
}

void vec_do_push_back(tuple vec, int64[][] new_val) {
    int64[][][] ptr
    int64 size
    int64 new_size
    size <- vec[0]
    ptr <- vec[1]
    memcp23(new_val, ptr, size)
    new_size <- size + 1
    vec[0] <- new_size
    return
}

void vec_push_back_alloc(tuple vec) {
    int64 icmp
    int64[][][] ptr
    ptr <- vec[1]
    // initially ptr is 0b1 => is_empty = 1
    if (ptr = 0) :alloc_new :check_length_fi
    {
:alloc_new
      int64[][][] arr
      arr <- new Array(1,2,2)
      vec[1] <- arr
      return
    }
:check_length_fi
    int64 size
    int64 capacity
    int64 len
    int64 is_full
    size <- vec[0]
    capacity <- length ptr 0
    if (size < capacity) :has_space_left :extend_fi
    {
      :has_space_left
      return
    }
    :extend_fi
    int64[][][] qtr
    int64 tiida
    tiida <- capacity * 2
    qtr <- new Array(tiida, 2, 2)

    int64 i
    i <- 0
    while (i < capacity) :do :done
    {
:do
      int64[][] buf
      buf <- vec[2]
      memcp32(ptr, i, buf)
      memcp23(buf, qtr, i)
      i <- i + 1
      continue
    }
:done
    vec[1] <- qtr
    return
}

void main() {
    int64 i
    int64 N
    int64[][] mat
    tuple vec
    tuple printing_buf
    printing_buf <- new Tuple(2)
    vec <- vec_ctor()
    i <- 0
    N <- 300000000
    mat <- new Array(2, 2)
    initmat(mat)
    while (1 = 1) :B2 :B6
    {
:B2
      int64 icmp
      i <- 1 + i
      icmp <- i <= N
      icmp <- 1 - icmp
      if (icmp = 1) :B2_5 :B3_fi
      {
:B2_5
        break
      }
:B3_fi
      int64 j
      j <- 1
      if (i <= 10) :B5_then :B3_5_orelse
:B3_5_orelse
      j <- i - 1
      int64 resid
      resid <- j & 33554431
      resid <- resid = 0
      int64 not_resid
      not_resid <- 1 - resid
      if (not_resid = 1) :B4_fi :B5_then
:B5_then
      print(i)
      print(mat)
:B4_fi
      nextfib(mat)
      resid <- j & 2097151
      if (resid = 0) :save :B4_5_fi
      {
:save
        vec_push_back_alloc(vec)
        vec_do_push_back(vec, mat)
        int64 size
        int64 capacity
        int64[][][] ptr
        size <- vec[0]
        printing_buf[0] <- size
        ptr <- vec[1]
        capacity <- length ptr 0
        printing_buf[1] <- capacity
        print(printing_buf)
      }
:B4_5_fi
      continue
    }
:B6
    int64[][][] data
    data <- vec[1]
    print(data)
    return
}

// compute fib by
//   [0 1] n
//   [1 1]
void initmat(int64[][] mat) {
    mat[0][0] <- 0
    mat[0][1] <- 1
    mat[1][0] <- 1
    mat[1][1] <- 1
    return
}

int64 mod10000(int64 n) {
    if (n >= 10000) :mod :nothing
    {
:mod
      n <- n - 10000
      n <- mod10000(n)
    }
:nothing
    return n
}

void nextfib(int64[][] acc) {
    int64 n00, n01, n10, n11
    goto :B1
:B2
    int64 B00
    int64 B01
    int64 B10
    int64 B11
    B00 <- 0
    B01 <- 1
    B10 <- 1
    B11 <- 1
    goto :B3
:B1
    int64 A00
    int64 A01
    int64 A10
    int64 A11
    A00 <- acc[0][0]
    A01 <- acc[0][1]
    A10 <- acc[1][0]
    A11 <- acc[1][1]
    goto :B2
:Bend
    n00 <- mod10000(n00)
    n01 <- mod10000(n10)
    n10 <- mod10000(n10)
    n11 <- mod10000(n11)
    acc[0][0] <- n00
    acc[0][1] <- n01
    acc[1][0] <- n10
    acc[1][1] <- n11
    return
:B3
    int64 a
    int64 b
    a <- A00 * B00
    b <- A01 * B10
    int64 c
    int64 d
    c <- A00 * B01
    d <- A01 * B11
    int64 e
    int64 f
    e <- A10 * B00
    f <- A11 * B10
    int64 g
    int64 h
    g <- A10 * B01
    h <- A11 * B11
    n00 <- a + b
    n01 <- c + d
    n10 <- e + f
    n11 <- g + h
    goto :Bend
}
