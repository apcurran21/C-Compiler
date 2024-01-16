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

int64 prime(int64 arg) {
    int64 inputIs2
    int64 halfarg
    int64 counter
    int64 pstatus
    int64 reloop

    counter <- 1
    if (arg = 2) :is_prime :prime_loop

    while (counter <= halfarg) :prime_loop :is_prime
    :prime_loop
    halfarg <- arg >> 1
    counter <- counter + 1
    pstatus <- mod(arg, counter)
    if (pstatus = 1) :not_prime :maybe_prime

    :maybe_prime
    continue

    :is_prime
    return 1

    :not_prime
    return 0
}


void main() {
    int64 primeCounter
    int64 searchCounter
    int64 result  
    int64 pr

    primeCounter <- 0
    searchCounter <- 0

    while (primeCounter < 58) :loop :done
    :loop
    searchCounter <- searchCounter + 1
    result <- prime(searchCounter)
    if (result = 0) :ct :nloop
    :nloop
    primeCounter <- primeCounter + 1
    :ct
    continue

    :done
    print(searchCounter)
    return
}