void main() {
    int64 arrSize, i
    int64[] arr

    arrSize <- 50
    arr <- new Array(arrSize)

    arr[0] <- 1
    arr[1] <- 1

    int64 back0, back1
    back0 <- 1
    back1 <- 1

    i <- 2
    while (i < arrSize) :loop :done 
    {
        :loop
        int64 sum
        sum <- back0 + back1
        back0 <- back1
        back1 <- sum
        arr[i] <- sum
        i <- i + 1
        continue
    }
    :done

    print(arr)

    int64 arrsum
    arrsum <- 0
    
    i <- 0
    while (i < arrSize) :loop2 :done2 
    {
        :loop2
        int64 val
        val <- arr[i]
        arrsum <- arrsum + val
        i <- i + 1
        continue
    }
    :done2

    print(arrsum)
    return
}
