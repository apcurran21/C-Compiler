int64 main() {
    int64 c
    c <- 9
    c <- c * 4
    c <- c + 1
    c <- c << 3
    c <- c - 10
    int64 x, should_lea
    x <- 1623
    should_lea <- c * 4
    should_lea <- should_lea + x
    int64 abc, size
    abc <- return_merge(x)
    size <- abc
    int64[] ptr
    ptr <- new Array(size)
    aliasing_issues(ptr)
    return c
}

int64 return_merge (int64 p) {
 int64 r
 r <- p + 1
 return r
}

int64 aliasing_issues (int64[] p) {
 int64[] v
 v <- p
 p[0] <- 2
 int64 x
 x <- p[0]
 v[0] <- 1
 print(x)
 return 0
}
