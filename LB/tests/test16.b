void main() {
    int64 size
    size <- 10
    int64[] v1, v2
    int64 res
    v1 <- new Array(size)
    v2 <- new Array(size)
    v1[0] <- 1
    v2[0] <- 2
    v1[1] <- 3
    v2[1] <- 4
    v1[2] <- 5
    v2[2] <- 6
    v1[3] <- 7
    v2[3] <- 8
    v1[4] <- 9
    v2[4] <- 10
    v1[5] <- 11
    v2[5] <- 12
    v1[6] <- 13
    v2[6] <- 14
    v1[7] <- 15
    v2[7] <- 16
    v1[8] <- 17
    v2[8] <- 18
    v1[9] <- 19
    v2[9] <- 20
    res <- dot_product(v1, v2, size)
    print(res)
    return
}

int64 dot_product(int64[] v1, int64[] v2, int64 n) {
    int64 prod, idx
    prod <- 0
    idx <- 0

    :loop_start
    while(idx < n) :loop_body :loop_end 
    {

        :loop_body
        int64 tmp1, tmp2, tmp3
        tmp1 <- v1[idx]
        tmp2 <- v2[idx]
        tmp3 <- tmp1 * tmp2
        prod <- prod + tmp3
        idx <- idx + 1
        continue
    }

    :loop_end
    return prod
}
