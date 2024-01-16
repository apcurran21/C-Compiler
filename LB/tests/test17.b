void main() {
    int64 shape
    shape <- 5

    int64[][] arr
    arr <- new Array(shape, shape)

    int64 x, y 
    x <- 0
    while (x < shape) :l0 :d0 
    {
        :l0
        y <- 0
        while (y < shape) :l1 :d1 
        {
            :l1
            int64 st
            st <- x * shape
            st <- st + y
            arr[x][y] <- st
            y <- y + 1
            continue
        }
        :d1
        x <- x + 1
        continue
    }
    :d0

    x <- 0
    while (x < shape) :l2 :d2 
    {
        :l2
        y <- x
        while (y < shape) :l3 :d3 
        {
            :l3
            int64 t0, t1, s
            t0 <- arr[x][y]
            t1 <- arr[y][x]
            s <- t0 + t1
            arr[x][y] <- s
            arr[y][x] <- s
            y <- y + 1
            continue
        }
        :d3
        x <- x + 1
        continue
    }
    :d2

    print(arr)
    return
}
