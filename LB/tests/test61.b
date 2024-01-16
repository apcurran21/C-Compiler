// find index of an element in an array. If not found, return -1

void main() {
    int64[] a
    a <- new Array(10)
    a[0] <- 0
    a[1] <- 1
    a[2] <- 2
    a[3] <- 3
    a[4] <- 4
    int64 i
    i <- indexOf(a, 10, 4)

    // 4
    print(i) 
    return
}

int64 indexOf(int64[] a, int64 len, int64 t) {
    int64 res
    res <- 0
    res <- res - 1
    int64 i
    i <- 0
    
    while (i < len) :intoWhile :exitWhile 
    {
        :intoWhile
        int64 v
        v <- a[i]
        if (v = t) :found :continueWhile
        
        :continueWhile
        i <- i + 1
        continue
    }
    :found
    res <- i
    :exitWhile
    return res
}
