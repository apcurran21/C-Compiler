void main() {
    int64 a
    int64[] arr

    arr <- new Array(1000)

    int64 i 
    i <- -1

    int64 x
    x <- 1

    while (i < 999) :loop :done
    {
        :loop
        i <- i + 1
        x <- x + i
        arr[i] <- x
        continue
    }
    :done
    print(arr)
    return
}