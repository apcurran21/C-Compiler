int64 mod(int64 x, int64 y) {
    int64 r
    if (x = 0) :mgood :misneg
    
    :misneg
    if (x > -1) :mloop :ret_early
    :ret_early
    return 0

    :mloop
    x <- x - y
    if (x = 0) :mgood :misneg

    :mgood
    return 1
}

int64 mod_sum(int64 x) {
    int64 original
    int64 sum
    int64 processing
    int64 r
    int64 isMod

    original <- x
    sum <- 0
    processing <- 0

    //I can't easily conver this using the while structure
    :sumloop
    processing <- processing + 1
    if (original <= processing) :done :notdone0

    :notdone0
    isMod <- mod(processing, 3)
    if (isMod = 1) :dosum :notdone1

    :notdone1
    isMod <- mod(processing, 5)
    if (isMod = 0) :sumloop :dosum

    :dosum
    sum <- sum + processing
    goto :sumloop

    :done
    return sum
}

void main() {
    :entry
    int64 v
    v <- mod_sum(1000)
    print(v)
    return
}
