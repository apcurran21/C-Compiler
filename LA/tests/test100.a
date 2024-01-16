int64[][] newmat(int64 arg1, int64 arg2)
{
    int64[][] rawptr
    rawptr <- new Array(arg1, arg2)
    return rawptr
}

// matset(a,i,j,v) = (a[i][j] := v)
void matset(int64[][] arg1, int64 arg2, int64 arg3, int64 arg4)
{
    arg1[arg2][arg3] <- arg4
    return
}

void main()
{
    int64[][] M
    int64[][] arr
    int64[][] arg1
    int64 arg2
    int64 arg3
    int64 arg4
    arg3 <- 2
    arg4 <- 5
    arr <- newmat(arg3, arg4)
    M <- arr

    arg1 <- M
    print(arg1)

    arg1 <- M
    arg2 <- 0
    arg3 <- 1
    arg4 <- 1
    matset(arg1, arg2, arg3, arg4)

    arg1 <- M
    arg2 <- 0
    arg3 <- 2
    arg4 <- 2
    matset(arg1, arg2, arg3, arg4)

    arg1 <- M
    arg2 <- 0
    arg3 <- 3
    arg4 <- 3
    matset(arg1, arg2, arg3, arg4)

    arg1 <- M
    arg2 <- 1
    arg3 <- 3
    arg4 <- 4
    matset(arg1, arg2, arg3, arg4)

    arg1 <- M
    arg2 <- 1
    arg3 <- 0
    arg4 <- -1
    matset(arg1, arg2, arg3, arg4)

    arg1 <- M
    print(arg1)
    return
}
